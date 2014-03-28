#ifndef FALCON_MEMORY_TEMPORARY_BUFFER_HPP
#define FALCON_MEMORY_TEMPORARY_BUFFER_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/assignable.hpp>
#include <falcon/memory/destroy.hpp>

#include <iterator>
#include <utility>

namespace falcon {

/**
 * Wrapper of the standard functions std::get_temporary_buffer()
 * and std::return_temporary_buffer()
 */
template<class T>
class temporary_buffer
{
public:
  typedef T               value_type;
  typedef T *             pointer;
  typedef const T *       const_pointer;
  typedef T &             reference;
  typedef const T &       const_reference;
  typedef std::ptrdiff_t  difference_type;
  typedef std::ptrdiff_t  size_type;

  typedef pointer       iterator;
  typedef const_pointer const_iterator;

  typedef std::reverse_iterator<iterator>       reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;


public:
  /// Requests storage large enough to hold a copy of [first,last).
  template<class ForwardIterator>
  temporary_buffer(ForwardIterator first, ForwardIterator last)
  : original_len_(std::distance(first, last))
  , buf_(original_len_)
  {
    std::uninitialized_copy(begin(), end(), first);
  }

  template<class ForwardIterator>
  temporary_buffer(ForwardIterator first, std::ptrdiff_t count)
  : original_len_(count)
  , buf_(original_len_)
  {
    std::uninitialized_copy_n(data(), size(), first);
  }

#if __cplusplus >= 201103L
  temporary_buffer(temporary_buffer&& other) noexcept
  : original_len_(other.original_len_)
  , buf_(other.buf_)
  {
    other.buf_.pair_.first = 0;
    other.buf_.pair_.second = 0;
  }

  temporary_buffer& operator=(temporary_buffer&& other) noexcept
  {
    original_len_ = other.original_len_;
    buf_ = other.buf_;
    other.buf_.pair_.first = 0;
    other.buf_.pair_.second = 0;
    return *this;
  }
#endif

  ~temporary_buffer()
  { destroy(begin(), end()); }

  size_type size() const CPP_NOEXCEPT
  { return buf_.pair_.second; }

  size_type max_size() const CPP_NOEXCEPT
  { return size(); }

  size_type requested_size() const CPP_NOEXCEPT
  { return original_len_; }

  // Iterators.
  iterator begin() CPP_NOEXCEPT
  { return iterator(data()); }

  const_iterator begin() const CPP_NOEXCEPT
  { return const_iterator(data()); }

  iterator end() CPP_NOEXCEPT
  { return iterator(data() + size()); }

  const_iterator end() const CPP_NOEXCEPT
  { return const_iterator(data() + size()); }

  reverse_iterator rbegin() CPP_NOEXCEPT
  { return reverse_iterator(end()); }

  const_reverse_iterator rbegin() const CPP_NOEXCEPT
  { return const_reverse_iterator(end()); }

  reverse_iterator rend() CPP_NOEXCEPT
  { return reverse_iterator(begin()); }

  const_reverse_iterator rend() const CPP_NOEXCEPT
  { return const_reverse_iterator(begin()); }

#if __cplusplus >= 201103L
  const_iterator cbegin() const noexcept
  { return const_iterator(data()); }

  const_iterator cend() const noexcept
  { return const_iterator(data() + size()); }

  const_reverse_iterator crbegin() const noexcept
  { return const_reverse_iterator(end()); }

  const_reverse_iterator crend() const noexcept
  { return const_reverse_iterator(begin()); }
#endif

  const_pointer data() const CPP_NOEXCEPT
  { return buf_.pair_.first; }

  pointer data() CPP_NOEXCEPT
  { return buf_.pair_.first; }

  void swap(temporary_buffer& other) CPP_NOEXCEPT
  {
    using std::swap;
    swap(original_len_, other.original_len_);
    swap(buf_.pair_, other.buf_.pair_);
  }

  CPP_DELETE_SGI_ASSIGNABLE(temporary_buffer);

private:
  size_type  original_len_;
  struct TemporaryBuffer {
    std::pair<pointer, size_type> pair_;

    TemporaryBuffer(std::ptrdiff_t len) CPP_NOEXCEPT
    : pair_(std::get_temporary_buffer<value_type>(len))
    {}

    ~TemporaryBuffer() CPP_NOEXCEPT
    { std::return_temporary_buffer(pair_.first); }
  } buf_;
};


template<class T>
void swap(temporary_buffer<T>& x, temporary_buffer<T>& y) CPP_NOEXCEPT
{ x.swap(y); }


template<class ForwardIterator>
temporary_buffer<typename std::iterator_traits<ForwardIterator>::value_type>
make_temporary_buffer(ForwardIterator first, ForwardIterator last)
{ return temporary_buffer<typename std::iterator_traits<ForwardIterator>::value_type>(first, last); }

template<class ForwardIterator>
temporary_buffer<typename std::iterator_traits<ForwardIterator>::value_type>
make_temporary_buffer(ForwardIterator first,
                      typename std::iterator_traits<ForwardIterator>::difference_type len)
{ return temporary_buffer<typename std::iterator_traits<ForwardIterator>::value_type>(first, len); }

}

#endif
