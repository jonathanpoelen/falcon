#ifndef FALCON_CONTAINER_UNORDERED_VECTOR_HPP
#define FALCON_CONTAINER_UNORDERED_VECTOR_HPP

#include <vector>

namespace falcon {

/**
 * \ingroup sequence
 */
template<typename T, typename Allocator = std::allocator<T> >
class unordered_vector : protected std::vector<T, Allocator>
{
  typedef std::vector<T, Allocator> container_type;

public:
  typedef typename container_type::value_type value_type;
  typedef typename container_type::pointer pointer;
  typedef typename container_type::const_pointer const_pointer;
  typedef typename container_type::reference reference;
  typedef typename container_type::const_reference const_reference;

  typedef typename container_type::iterator iterator;
  typedef typename container_type::const_iterator const_iterator;
  typedef typename container_type::reverse_iterator reverse_iterator;
  typedef typename container_type::const_reverse_iterator const_reverse_iterator;

  typedef typename container_type::size_type size_type;
  typedef typename container_type::difference_type difference_type;
  typedef typename container_type::allocator_type allocator_type;

#if __cplusplus >= 201103L
  using container_type::vector;
#else
  explicit unordered_vector( const Allocator& alloc = Allocator() )
  : container_type(alloc)
  {}

  explicit unordered_vector(size_type count,
                            const T& value = T(),
                            const Allocator& alloc = Allocator())
  : container_type(count, value, alloc)
  {}

  template< class InputIt >
  unordered_vector( InputIt first, InputIt last,
                    const Allocator& alloc = Allocator() )
  : container_type(first, last, alloc)
  {}

  unordered_vector( const unordered_vector& other )
  : container_type(other.c)
  {}

  unordered_vector( const container_type& other )
  : container_type(other)
  {}
#endif

  unordered_vector& operator=(const unordered_vector& other)
  {
    container_type::operator=(other.c);
    return *this;
  }

  unordered_vector& operator=(const container_type & other)
  {
    container_type::operator=(other);
    return *this;
  }

#if __cplusplus >= 201103L
  unordered_vector& operator=(unordered_vector && other) noexcept
  {
    container_type::operator=(other.c);
    return *this;
  }

  unordered_vector& operator=(container_type && other) noexcept
  {
    container_type::operator=(other);
    return *this;
  }

  unordered_vector& operator=( std::initializer_list<T> ilist )
  {
    container_type::operator=(ilist);
    return *this;
  }
#endif

  using container_type::assign;
  using container_type::get_allocator;

  using container_type::at;
  using container_type::operator[];
  using container_type::front;
  using container_type::back;

  using container_type::begin;
  using container_type::end;
  using container_type::rbegin;
  using container_type::rend;

  using container_type::empty;
  using container_type::size;
  using container_type::max_size;
  using container_type::capacity;
  using container_type::reserve;

  using container_type::clear;
  using container_type::resize;
  using container_type::swap;

#if __cplusplus >= 201103L
  using container_type::data;
  using container_type::cbegin;
  using container_type::cend;
  using container_type::crbegin;
  using container_type::crend;

  using container_type::shrink_to_fit;
#endif

#if __cplusplus >= 201103L
  iterator erase( const_iterator pos )
#else
  iterator erase( iterator pos )
#endif
  {
    if (pos + 1 != end()) {
#if __cplusplus >= 201103L
      *const_cast<pointer>(pos.base()) = std::move(back());
#else
      *pos = back();
#endif
    }
    this->pop_back();
    return pos;
  }

#if __cplusplus >= 201103L
  iterator erase( const_iterator first, const_iterator last )
#else
  iterator erase( iterator first, iterator last )
#endif
  {
    if (last = end()) {
      return container_type::erase(first, last);
    }

    difference_type dis = last - first;
    difference_type rem = end() - last;
    if (rem <= dis) {
      return container_type::erase(first, last);
    }

    for (iterator pos = end()-dis; first != last; ++first, ++pos) {
#if __cplusplus >= 201103L
      *const_cast<pointer>(first.base()) = std::move(*pos);
#else
      *first = *pos;
#endif
    }
    return container_type::erase(end() - dis, end());
  }

#if __cplusplus >= 201103L
  template<typename... Args>
  void emplace(Args&&... args)
  { emplace_back(cend(), std::forward<Args>(args)...); }

  void insert(T && value)
  { container_type::push_back(std::move(value)); }

  void insert( std::initializer_list<T> ilist )
  { container_type::insert(end(), ilist); }
#endif

  void insert( size_type count, const T& value )
  { container_type::insert(end(), count, value); }

  template< class InputIt >
  void insert( InputIt first, InputIt last )
  { container_type::insert(end(), first, last); }

  void insert(const T & value)
  { container_type::push_back(value); }
};


template<typename T, typename Allocator>
std::vector< T, Allocator > &
sequence_unordered_vector(unordered_vector<T, Allocator> & x)
{ return reinterpret_cast<std::vector< T, Allocator > &>(x); }

template<typename T, typename Allocator>
const std::vector< T, Allocator > &
sequence_unordered_vector(const unordered_vector<T, Allocator> & x)
{ return reinterpret_cast<const std::vector< T, Allocator > &>(x); }


template<typename T, typename Allocator>
bool operator==(const unordered_vector<T, Allocator> & x,
                const unordered_vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) == sequence_unordered_vector(y); }

template<typename T, typename Allocator>
bool operator==(const std::vector<T, Allocator> & x,
                const unordered_vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) == sequence_unordered_vector(y); }

template<typename T, typename Allocator>
bool operator==(const unordered_vector<T, Allocator> & x,
                const std::vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) == sequence_unordered_vector(y); }


template<typename T, typename Allocator>
bool operator!=(const unordered_vector<T, Allocator> & x,
                const unordered_vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) != sequence_unordered_vector(y); }

template<typename T, typename Allocator>
bool operator!=(const std::vector<T, Allocator> & x,
                const unordered_vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) != sequence_unordered_vector(y); }

template<typename T, typename Allocator>
bool operator!=(const unordered_vector<T, Allocator> & x,
                const std::vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) != sequence_unordered_vector(y); }


template<typename T, typename Allocator>
bool operator<(const unordered_vector<T, Allocator> & x,
                const unordered_vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) < sequence_unordered_vector(y); }

template<typename T, typename Allocator>
bool operator<(const std::vector<T, Allocator> & x,
                const unordered_vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) < sequence_unordered_vector(y); }

template<typename T, typename Allocator>
bool operator<(const unordered_vector<T, Allocator> & x,
                const std::vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) < sequence_unordered_vector(y); }


template<typename T, typename Allocator>
bool operator<=(const unordered_vector<T, Allocator> & x,
                const unordered_vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) <= sequence_unordered_vector(y); }

template<typename T, typename Allocator>
bool operator<=(const std::vector<T, Allocator> & x,
                const unordered_vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) <= sequence_unordered_vector(y); }

template<typename T, typename Allocator>
bool operator<=(const unordered_vector<T, Allocator> & x,
                const std::vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) <= sequence_unordered_vector(y); }


template<typename T, typename Allocator>
bool operator>(const unordered_vector<T, Allocator> & x,
                const unordered_vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) > sequence_unordered_vector(y); }

template<typename T, typename Allocator>
bool operator>(const std::vector<T, Allocator> & x,
                const unordered_vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) > sequence_unordered_vector(y); }

template<typename T, typename Allocator>
bool operator>(const unordered_vector<T, Allocator> & x,
                const std::vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) > sequence_unordered_vector(y); }


template<typename T, typename Allocator>
bool operator>=(const unordered_vector<T, Allocator> & x,
                const unordered_vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) >= sequence_unordered_vector(y); }

template<typename T, typename Allocator>
bool operator>=(const std::vector<T, Allocator> & x,
                const unordered_vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) >= sequence_unordered_vector(y); }

template<typename T, typename Allocator>
bool operator>=(const unordered_vector<T, Allocator> & x,
                const std::vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) >= sequence_unordered_vector(y); }

}

#endif
