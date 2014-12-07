#ifndef FALCON_CONTAINER_PTR_CONTAINER_HPP
#define FALCON_CONTAINER_PTR_CONTAINER_HPP

#include <falcon/iterator/normal_iterator.hpp>

#include <iterator>
#include <algorithm>
#include <stdexcept>

namespace falcon {

/**
 * @brief Container between two pointers
 *
 * @ingroup sequences
 */
template<class T>
class ptr_container
{
public:
  typedef T value_type;
  typedef T * pointer;
  typedef const T * const_pointer;
  typedef T & reference;
  typedef const T & const_reference;
  typedef std::ptrdiff_t difference_type;

  typedef std::size_t size_type;

  typedef ::falcon::iterator::normal_iterator<pointer> iterator;
  typedef ::falcon::iterator::normal_iterator<const_pointer> const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

private:
  pointer first_ = nullptr;
  pointer last_ = nullptr;

public:
  constexpr ptr_container() = default;

  constexpr ptr_container(pointer first, pointer last) noexcept
  : first_(first)
  , last_(last)
  {}

  constexpr ptr_container(pointer first, size_type n) noexcept
  : first_(first)
  , last_(first + n)
  {}

  constexpr ptr_container(const ptr_container& other) = default;
  ptr_container& operator=(const ptr_container& other) = default;

  void begin(pointer first) noexcept
  { first_ = first; }

  void end(pointer last) noexcept
  { last_ = last; }

  // Iterators.
  iterator begin() noexcept
  { return iterator(first_); }

  const_iterator begin() const noexcept
  { return const_iterator(first_); }

  iterator end() noexcept
  { return iterator(last_); }

  const_iterator end() const noexcept
  { return const_iterator(last_); }

  reverse_iterator rbegin() noexcept
  { return reverse_iterator(end()); }

  const_reverse_iterator rbegin() const noexcept
  { return const_reverse_iterator(end()); }

  reverse_iterator rend() noexcept
  { return reverse_iterator(begin()); }

  const_reverse_iterator rend() const noexcept
  { return const_reverse_iterator(begin()); }

  const_iterator cbegin() const noexcept
  { return const_iterator(first_); }

  const_iterator cend() const noexcept
  { return const_iterator(last_); }

  const_reverse_iterator crbegin() const noexcept
  { return const_reverse_iterator(end()); }

  const_reverse_iterator crend() const noexcept
  { return const_reverse_iterator(begin()); }

  // Capacity.
  constexpr size_type size() const noexcept
  { return last_ - first_; }

  constexpr size_type max_size() const noexcept
  { return size(); }

  constexpr bool empty() const noexcept
  { return first_ == last_; }

  // Element access.
  reference operator[](size_type n) noexcept
  { return first_[n]; }

  constexpr const_reference operator[](size_type n) const noexcept
  { return first_[n]; }

  reference at(size_type n)
  {
    if (n >= size()) {
      std::out_of_range("ptr_container::at");
    }
    return first_[n];
  }

  constexpr const_reference at(size_type n) const
  {
    // Result of conditional expression must be an lvalue so use
    // boolean ? lvalue : (throw-expr, lvalue)
    return n < size() ? first_[n]
    : (std::out_of_range("ptr_container::at"), first_[0]);
  }

  reference front() noexcept
  { return *first_; }

  constexpr const_reference front() const noexcept
  { return *first_; }

  reference back() noexcept
  { return empty() ? *last_ : *(last_ - 1); }

  constexpr const_reference back() const noexcept
  { return empty() ? *last_ : *(last_ - 1); }

  void swap(ptr_container& other) noexcept
  {
    using std::swap;
    swap(first_, other.first_);
    swap(last_, other.last_);
  }
};

/**
 * @brief  Ptr_container equality comparison.
 * @param  x  A %ptr_container.
 * @param  y  A %ptr_container of the same type as @a x.
 * @return  True iff the size and elements of the ptr_containers are equal.
 *
 * This is an equivalence relation.  It is linear in the size of the
 * ptr_containers. Ptr_containers are considered equivalent if their sizes are equal,
 * and if corresponding elements compare equal.
 */
template<class T>
bool operator==(const ptr_container<T>& x, const ptr_container<T>& y) noexcept
{ return (x.size() == y.size()
&& std::equal(x.begin().base(), x.end().base(), y.begin().base())); }

/**
 * @brief  Ptr_container ordering relation.
 * @param  x  A %ptr_container.
 * @param  y  A %ptr_container of the same type as @a x.
 * @return  True iff @a x is lexicographically less than @a y.
 *
 * This is a total ordering relation.  It is linear in the size of the
 * ptr_containers.  The elements must be comparable with @c <.
 *
 * See std::lexicographical_compare() for how the determination is made.
 */
template<class T>
bool operator<(const ptr_container<T>& x, const ptr_container<T>& y) noexcept
{ return std::lexicographical_compare(
  x.begin().base(), x.end().base(), y.begin().base(), y.end().base()
); }

/// Based on operator==
template<class T>
bool operator!=(const ptr_container<T>& x, const ptr_container<T>& y) noexcept
{ return !(x == y); }

/// Based on operator<
template<class T>
bool operator>(const ptr_container<T>& x, const ptr_container<T>& y) noexcept
{ return y < x; }

/// Based on operator<
template<class T>
bool operator<=(const ptr_container<T>& x, const ptr_container<T>& y) noexcept
{ return !(y < x); }

/// Based on operator<
template<class T>
bool operator>=(const ptr_container<T>& x, const ptr_container<T>& y) noexcept
{ return !(x < y); }

template<class T>
ptr_container<T> make_ptr_container(T * first, T * last) noexcept
{ return ptr_container<T>(first, last); }

template<class T>
ptr_container<T> make_ptr_container(T * first, std::size_t n) noexcept
{ return ptr_container<T>(first, n); }

template<class T>
ptr_container<const T>
make_ptr_container(const T * first, const T * last) noexcept
{ return ptr_container<const T>(first, last); }

template<class T>
ptr_container<const T>
make_ptr_container(const T * first, std::size_t n) noexcept
{ return ptr_container<const T>(first, n); }

template<class T, std::size_t N>
ptr_container<T>
make_ptr_container(T(&cont)[N]) noexcept
{ return ptr_container<const T>(&cont[0], &cont[N]); }

template<class T, std::size_t N>
ptr_container<const T>
make_ptr_container(const T(&cont)[N]) noexcept
{ return ptr_container<const T>(&cont[0], &cont[N]); }

template<class T>
void swap(ptr_container<T>& x, ptr_container<T>& y) noexcept
{ x.swap(y); }

}

#endif
