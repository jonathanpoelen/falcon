#ifndef FALCON_RANGE_ITERATOR_RANGE_HPP
#define FALCON_RANGE_ITERATOR_RANGE_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/reference.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include <falcon/type_traits/enable_if.hpp>
#include <falcon/container/range_access.hpp>

#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <cassert>
#include FALCON_BOOST_OR_STD_TRAITS(is_integral)

namespace falcon {

/**
 * @brief Container between two iterators
 *
 * @ingroup sequences
 */
template<typename Iterator>
class iterator_range
{
  typedef std::iterator_traits<Iterator> traits_;
public:
  typedef typename traits_::value_type value_type;
  typedef typename traits_::pointer pointer;
  typedef typename traits_::reference reference;
  typedef typename traits_::difference_type difference_type;

  typedef std::size_t size_type;
  typedef Iterator const_iterator;
  typedef Iterator iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef reverse_iterator const_reverse_iterator;


#if __cplusplus >= 201103L
  iterator_range() = default;
  iterator_range(const iterator_range & r) = default;
  iterator_range(iterator_range &&) = default;
#else
  iterator_range()
  : first_()
  , last_()
  {}

  iterator_range(const iterator_range & r)
  : first_(r.first_)
  , last_(r.last_)
  {}
#endif

  template<class IteratorT>
  CPP_CONSTEXPR iterator_range(IteratorT first, IteratorT last)
  : first_(first)
  , last_(last)
  {}

  template<class IteratorT>
  iterator_range(IteratorT first, difference_type n)
  : first_(first)
#if __cplusplus >= 201103L
  , last_(std::next(first, n))
#else
  , last_(first+n)
#endif
  {}

  template<
    class IteratorT , class Integral
  , class = typename enable_if_c<
    FALCON_BOOST_OR_STD_NAMESPACE::is_integral<Integral> >::type>
  iterator_range(IteratorT first, Integral n)
  : first_(first)
#if __cplusplus >= 201103L
  , last_(std::next(first, difference_type(n)))
#else
  , last_(first+difference_type(n))
#endif
  {}

  template<class Range>
  CPP_CONSTEXPR iterator_range(const Range & r)
  : first_(::falcon::begin(r))
  , last_(::falcon::end(r))
  {}

  template<class Range>
  CPP_CONSTEXPR iterator_range(Range & r)
  : first_(::falcon::begin(r))
  , last_(::falcon::end(r))
  {}

#if __cplusplus >= 201103L
  iterator_range& operator=(const iterator_range & r) = default;
  iterator_range& operator=(iterator_range && r) = default;
#endif

  template<class Range>
  iterator_range& operator=(Range & r)
  {
    first_ = ::falcon::begin(r);
    last_ = ::falcon::end(r);
    return *this;
  }

  template<class Range>
  iterator_range& operator=(const Range & r)
  {
    first_ = ::falcon::begin(r);
    last_ = ::falcon::end(r);
    return *this;
  }

  CPP_CONSTEXPR iterator begin() const CPP_NOEXCEPT
  { return first_; }

  CPP_CONSTEXPR iterator end() const CPP_NOEXCEPT
  { return last_; }

  CPP_CONSTEXPR reverse_iterator rbegin() const CPP_NOEXCEPT
  { return reverse_iterator(last_); }

  CPP_CONSTEXPR reverse_iterator rend() const CPP_NOEXCEPT
  { return reverse_iterator(first_); }

  CPP_CONSTEXPR bool empty() const CPP_NOEXCEPT
  { return first_ == last_; }

  CPP_CONSTEXPR difference_type size() const CPP_NOEXCEPT
  { return std::distance(last_ - first_); }

  CPP_CONSTEXPR_NOT_CONST reference front() const
  {
    assert( !empty() );
    return *first_;
  }

  CPP_CONSTEXPR_NOT_CONST reference back() const
  {
    assert( !empty() );
    return *--Iterator(last_);
  }

  CPP_CONSTEXPR_NOT_CONST reference operator[](difference_type at)
  {
    assert( at >= 0 && at < size() );
    return first_[at];
  }

  CPP_CONSTEXPR_NOT_CONST reference operator[](difference_type at) const
  {
    assert( at >= 0 && at < size() );
    return first_[at];
  }

  CPP_CONSTEXPR_NOT_CONST reference at(size_type n)
  {
    if (n < size()) {
      throw std::out_of_range("iterator_range::at");
    }
    return first_[n];
  }

  CPP_CONSTEXPR_NOT_CONST reference at(size_type n) const
  {
    if (n < size()) {
      throw std::out_of_range("iterator_range::at");
    }
    return first_[n];
  }

#if __cplusplus >= 201103L
  explicit constexpr operator bool() const noexcept
  { return !empty(); }

  constexpr bool operator!() const noexcept
  { return empty(); }
#else
  operator void *() const
  { return !empty(); }
#endif

  CPP_CONSTEXPR bool equal(const iterator_range& r) const CPP_NOEXCEPT
  { return r.first_ == first_ && r.last_ == last_; }

  bool operator==(const iterator_range& r) const
  { return r.size() == size() && std::equal(first_, last_, r.first_); }

  template<typename Range>
  bool operator==(const Range& r) const
  { return r.size() == size()
  && std::equal(first_, last_, ::falcon::begin(r)); }

  bool operator<(const iterator_range& r) const
  { return std::lexicographical_compare(first_, last_, r.first_, r.last_); }

  template<typename Range>
  bool operator<(const Range& r) const
  {
    return std::lexicographical_compare(
      first_, last_, ::falcon::begin(r), ::falcon::end(r));
  }

private:
  Iterator first_;
  Iterator last_;
};


namespace aux_ { namespace iterator_range {
  // TODO equal(I1, I1, I2, I2)
  template<class I1, class I2>
  bool equal(
    I1 first1, I1 last1, I2 first2, I2 last2,
    std::random_access_iterator_tag, std::random_access_iterator_tag)
  {
    if (std::distance(first1, last1) != std::distance(first2, last2)) {
      return false;
    }
    return std::equal(first1, last1, first2);
  }

  template<class I1, class I2, class T1, class T2>
  bool equal(I1 first1, I1 last1, I2 first2, I2 last2, T1, T2)
  {
    for (; first1 != last1 && first2 != last2; ++first1, ++first2){
      if (!(*first1 == *first2)) {
        return false;
      }
    }
    return first1 == last1 && first2 == last2;
  }
} }

/**
 * @brief  iterator_range equality comparison.
 * @param  x  A %iterator_range.
 * @param  y  A %iterator_range of the same type as @a x.
 * @return  True iff the size and elements of the iterator_ranges are equal.
 *
 * This is an equivalence relation.  It is linear in the size of the
 * iterator_ranges. Range_containers are considered equivalent if their sizes are equal (if iterator is random_access_iterator_tag),
 * and if corresponding elements compare equal.
 */
template<class Iterator1, class Iterator2>
bool operator==(
  const iterator_range<Iterator1>& l, const iterator_range<Iterator2>& r)
{
#if __cplusplus > 201103L
  return std::equal(l.begin(), l.end(), r.begin(), r.end());
#else
  return aux_::iterator_range::equal(
    l.begin(), l.end(), r.begin(), r.end(),
    typename std::iterator_traits<Iterator1>::iterator_category(),
    typename std::iterator_traits<Iterator2>::iterator_category()
  );
#endif
}

/**
 * @brief  iterator_range ordering relation.
 * @param  x  A %iterator_range.
 * @param  y  A %iterator_range of the same type as @a x.
 * @return  True iff @a x is lexicographically less than @a y.
 *
 * This is a total ordering relation.  It is linear in the size of the
 * iterator_ranges.  The elements must be comparable with @c <.
 */
template<class Iterator1, class Iterator2>
bool operator<(
  const iterator_range<Iterator1>& l, const iterator_range<Iterator2>& r)
{ return std::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end()); }

template<class Iterator1, class Iterator2>
bool operator!=(
  const iterator_range<Iterator1>& l, const iterator_range<Iterator2>& r)
{ return !(l == r); }

template<class Iterator1, class Iterator2>
bool operator<=(
  const iterator_range<Iterator1>& l, const iterator_range<Iterator2>& r)
{ return !(r < l); }

template<class Iterator1, class Iterator2>
bool operator>(
  const iterator_range<Iterator1>& l, const iterator_range<Iterator2>& r)
{ return (r < l); }

template<class Iterator1, class Iterator2>
bool operator>=(
  const iterator_range<Iterator1>& l, const iterator_range<Iterator2>& r)
{ return !(l < r); }


template<class Iterator>
CPP_CONSTEXPR iterator_range<Iterator>
make_iterator_range(Iterator x, Iterator y)
{ return iterator_range<Iterator>(x, y); }

template<class Iterator>
iterator_range<Iterator>
make_iterator_range(
  Iterator first, typename std::iterator_traits<Iterator>::difference_type n)
{ return iterator_range<Iterator>(first, n); }

template<class Container>
iterator_range<typename range_access_iterator<Container>::type>
make_iterator_range(Container& cont)
{
  return iterator_range<
    typename range_access_iterator<Container>::type
  >(begin(cont), end(cont));
}

template<class Container>
iterator_range<typename range_access_iterator<const Container>::type>
make_iterator_range(const Container& cont)
{
  return iterator_range<
    typename range_access_iterator<const Container>::type
  >(begin(cont), end(cont));
}

template<class Iterator>
iterator_range<std::reverse_iterator<Iterator> >
make_reverse_iterator_range(
  Iterator first, typename std::iterator_traits<Iterator>::difference_type n)
{
  typedef std::reverse_iterator<Iterator> iter;
  typename iter::iterator_type iter_base;
#if __cplusplus >= 201103L
  return iterator_range<iter>(iter(std::next(first, n)), iter(first));
#else
  iter_base last = first;
  std::advance(last, n);
  return iterator_range<iter>(iter(last), iter(first));
#endif
}

template<class Container>
iterator_range<typename range_access_reverse_iterator<Container>::type>
make_reverse_iterator_range(Container& cont)
{
  return iterator_range<
    typename range_access_reverse_iterator<Container>::type
  >(rbegin(cont), rend(cont));
}

template<class Container>
iterator_range<typename range_access_reverse_iterator<const Container>::type>
make_reverse_iterator_range(const Container& cont)
{
  return iterator_range<
    typename range_access_reverse_iterator<const Container>::type
  >(rbegin(cont), rend(cont));
}

}

#endif
