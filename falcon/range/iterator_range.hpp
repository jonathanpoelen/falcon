#ifndef FALCON_RANGE_ITERATOR_RANGE_HPP
#define FALCON_RANGE_ITERATOR_RANGE_HPP

#include <falcon/c++/assignable.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/reference.hpp>
#include <falcon/type_traits/decay_and_strip.hpp>
#include <falcon/container/range_access.hpp>
#include <falcon/utility/move.hpp>

#include <iterator>
#include <algorithm>
#include <cassert>

namespace falcon {

template<typename Iterator>
struct iterator_range
{
  typedef typename std::iterator_traits<Iterator>::value_type value_type;
  typedef typename std::iterator_traits<Iterator>::difference_type difference_type;
  typedef typename std::iterator_traits<Iterator>::pointer pointer;
  typedef typename std::iterator_traits<Iterator>::reference reference;
  typedef std::size_t size_type;
  typedef Iterator const_iterator;
  typedef Iterator iterator;


  CPP_CONSTEXPR iterator_range()
  : m_begin()
  , m_end()
  { }

  template<class IteratorT>
  CPP_CONSTEXPR iterator_range(IteratorT Begin, IteratorT End)
  : m_begin(Begin)
  , m_end(End)
  {}

  template<class Range>
  CPP_CONSTEXPR iterator_range(const Range & r)
  : m_begin(::falcon::begin(r))
  , m_end(::falcon::end(r))
  {}

  template<class Range>
  CPP_CONSTEXPR iterator_range(Range & r)
  : m_begin(::falcon::begin(r))
  , m_end(::falcon::end(r))
  {}

#if __cplusplus >= 201103L
  iterator_range(const iterator_range & r) = default;
  iterator_range& operator=(const iterator_range & r) = default;
  iterator_range& operator=(iterator_range && r) = default;
#endif

  template<class Range>
  iterator_range& operator=(Range & r)
  {
    m_begin = ::falcon::begin(r);
    m_end = ::falcon::end(r);
    return *this;
  }

  template<class Range>
  iterator_range& operator=(const Range & r)
  {
    m_begin = ::falcon::begin(r);
    m_end = ::falcon::end(r);
    return *this;
  }

  CPP_CONSTEXPR Iterator begin() const
  {
    return m_begin;
  }

  CPP_CONSTEXPR Iterator end() const
  {
    return m_end;
  }

  CPP_CONSTEXPR bool empty() const
  {
    return m_begin == m_end;
  }

  CPP_CONSTEXPR difference_type size() const
  {
    return m_end - m_begin;
  }

  CPP_CONSTEXPR reference front() const
  {
#if __cplusplus > 201103L
    assert( !empty() );
#endif
    return *m_begin;
  }

  CPP_CONSTEXPR reference back() const
  {
#if __cplusplus > 201103L
    assert( !empty() );
#endif
    return *--Iterator(m_end);
  }

  void pop_front()
  {
#if __cplusplus > 201103L
    assert( !empty() );
#endif
    ++m_begin;
  }

  void pop_back()
  {
#if __cplusplus > 201103L
    assert( !empty() );
#endif
    --m_end;
  }

  CPP_CONSTEXPR reference operator[](difference_type at) const
  {
#if __cplusplus > 201103L
    assert( at >= 0 && at < size() );
#endif
    return m_begin[at];
  }

  iterator_range& advance_begin(difference_type n)
  {
    std::advance(m_begin, n);
    return *this;
  }

  iterator_range& advance_end(difference_type n)
  {
    std::advance(m_end, n);
    return *this;
  }

  CPP_CONSTEXPR operator bool() const
  {
    return m_begin != m_end;
  }

  CPP_CONSTEXPR bool operator!() const
  {
    return empty();
  }

  CPP_CONSTEXPR bool equal(const iterator_range& r) const
  {
    return r.m_begin == m_begin && r.m_end == m_end;
  }

  bool operator==(const iterator_range& r) const
  {
    return r.size() == size() && std::equal(m_begin, m_end, r.m_begin);
  }

  template<typename Range>
  bool operator==(const Range& r) const
  {
    return r.size() == size() && std::equal(m_begin, m_end, ::falcon::begin(r));
  }

  bool operator<(const iterator_range& r) const
  {
    return std::lexicographical_compare(m_begin, m_end, r.m_begin, r.m_end);
  }

  template<typename Range>
  bool operator<(const Range& r) const
  {
    return std::lexicographical_compare(m_begin, m_end, ::falcon::begin(r), ::falcon::end(r));
  }

private:
  Iterator m_begin;
  Iterator m_end;
};


template<class Iterator1T, class Iterator2T >
bool operator==(const iterator_range<Iterator1T>& l, const iterator_range<Iterator2T>& r )
{
  return l.size() == r.size() && std::equal(l.begin(), l.end(), r.begin(), r.end());
}

template<class Iterator, class ForwardRange>
bool operator==(const iterator_range<Iterator>& l, const ForwardRange& r)
{
  return l.size() == r.size() && std::equal(l.begin(), l.end(), r.begin(), r.end());
}

template<class Iterator, class ForwardRange>
bool operator==(const ForwardRange& l, const iterator_range<Iterator>& r)
{
  return l.size() == r.size() && std::equal(l.begin(), l.end(), ::falcon::begin(r));
}


template<class Iterator1T, class Iterator2T >
bool operator!=(const iterator_range<Iterator1T>& l, const iterator_range<Iterator2T>& r )
{
  return !(l == r);
}

template<class Iterator, class ForwardRange>
bool operator!=(const iterator_range<Iterator>& l, const ForwardRange& r)
{
  return !(l == r);
}

template<class Iterator, class ForwardRange>
bool operator!=(const ForwardRange& l, const iterator_range<Iterator>& r)
{
  return !(l == r);
}


template<class Iterator1T, class Iterator2T >
bool operator<(const iterator_range<Iterator1T>& l, const iterator_range<Iterator2T>& r )
{
  return std::lexicographical_compare(
    ::falcon::begin(l), ::falcon::end(l), r.begin(), r.end());
}

template<class Iterator, class ForwardRange>
bool operator<(const iterator_range<Iterator>& l, const ForwardRange& r)
{
  return std::lexicographical_compare(
    ::falcon::begin(l), ::falcon::end(l), r.begin(), r.end());
}

template<class Iterator, class ForwardRange>
bool operator<(const ForwardRange& l, const iterator_range<Iterator>& r)
{
  return std::lexicographical_compare(
    ::falcon::begin(l), ::falcon::end(l), r.begin(), r.end());
}


template<class Iterator1T, class Iterator2T >
bool operator<=(const iterator_range<Iterator1T>& l, const iterator_range<Iterator2T>& r )
{
  return !(r < l);
}

template<class Iterator, class ForwardRange>
bool operator<=(const iterator_range<Iterator>& l, const ForwardRange& r)
{
  return !(r < l);
}

template<class Iterator, class ForwardRange>
bool operator<=( const ForwardRange& l, const iterator_range<Iterator>& r)
{
  return !(r < l);
}


template<class Iterator1T, class Iterator2T >
bool operator>(const iterator_range<Iterator1T>& l, const iterator_range<Iterator2T>& r )
{
  return (r < l);
}

template<class Iterator, class ForwardRange>
bool operator>(const iterator_range<Iterator>& l, const ForwardRange& r)
{
  return (r < l);
}

template<class Iterator, class ForwardRange>
bool operator>(const ForwardRange& l, const iterator_range<Iterator>& r)
{
  return (r < l);
}


template<class Iterator1T, class Iterator2T >
bool operator>=(const iterator_range<Iterator1T>& l, const iterator_range<Iterator2T>& r )
{
  return !(l < r);
}

template<class Iterator, class ForwardRange>
bool operator>=(const iterator_range<Iterator>& l, const ForwardRange& r)
{
  return !(l < r);
}

template<class Iterator, class ForwardRange>
bool operator>=( const ForwardRange& l, const iterator_range<Iterator>& r)
{
  return !(l < r);
}


template<class T>
CPP_CONSTEXPR iterator_range<typename decay_and_strip<T>::type>
make_iterator_range(T CPP_RVALUE x, T CPP_RVALUE y)
{
  typedef iterator_range<typename decay_and_strip<T>::type> iterator_range_type;
  return iterator_range_type(FALCON_FORWARD(T, x), FALCON_FORWARD(T, y));
}

}

#endif
