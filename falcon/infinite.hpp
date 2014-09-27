#ifndef FALCON_INFINITE_HPP
#define FALCON_INFINITE_HPP

#include <falcon/c++/constexpr.hpp>
#if __cplusplus >= 201103L
#include <utility>
#endif
#include <cstddef>
#include <cassert>

namespace falcon {

template <typename T>
struct infinite
{
  typedef T value_type;


public:
  CPP_CONSTEXPR infinite(const value_type& x, const value_type& last)
  : current_(x)
  , first_()
  , last_(last)
  {}

  CPP_CONSTEXPR infinite(
    const value_type& first, const value_type& x, const value_type& last)
  : current_(x)
  , first_(first)
  , last_(last)
  {}

#if __cplusplus >= 201103L
  template<class U1, class U2>
  constexpr infinite(U1 && x, U2 && last)
  : current_(std::forward<U1>(x))
  , first_()
  , last_(std::forward<U2>(last))
  {}

  template<class U1, class U2, class U3>
  constexpr infinite(U1 && first, U2 && x, U3 && last)
  : current_(std::forward<U1>(first))
  , first_(std::forward<U2>(x))
  , last_(std::forward<U3>(last))
  {}

  operator const value_type & () const
  { return current_; }

  void set(value_type && x)
  {
    current_ = std::move(x);
    assert(first_ <= current_ && current_ <= last_);
  }

  infinite& operator=(value_type && x)
  {
    set(std::move(x));
    return *this;
  }
#endif

  void set(const value_type& x)
  {
    current_ = x;
    assert(first_ <= current_ && current_ <= last_);
  }

  infinite& operator=(const value_type & x)
  {
    set(x);
    return *this;
  }

  const value_type& get() const
  { return current_; }

  const value_type& min() const
  { return first_; }

  const value_type& max() const
  { return last_; }

  value_type & operator-> ()
  { return current_; }

  const value_type & operator-> () const
  { return current_; }

  infinite& operator++()
  {
    if (++current_ == last_) {
      current_ = first_;
    }
    return *this;
  }

  infinite operator++(int)
  {
    infinite ret = *this;
    ++*this;
    return ret;
  }

  infinite& operator--()
  {
    if (current_ == first_) {
      current_ = last_;
    }
    --current_;
    return *this;
  }

  infinite operator--(int)
  {
    infinite ret = *this;
    --*this;
    return ret;
  }

  infinite& operator+=(const T& n)
  {
    if (n < 0) {
      prev_(-n);
    }
    if (n > 0) {
      next_(n);
    }
    return *this;
  }

  infinite& operator-=(const T& n)
  {
    if (n < 0) {
      next_(n);
    }
    if (n > 0) {
      prev_(-n);
    }
    return *this;
  }

  infinite& operator+=(std::size_t n)
  {
    next_(n);
    return *this;
  }

  infinite& operator-=(std::size_t n)
  {
    prev_(n);
    return *this;
  }

  infinite operator+(const T& n)
  {
    infinite ret = *this;
    ret += n;
    return ret;
  }

  infinite operator-(const T& n)
  {
    infinite ret = *this;
    ret -= n;
    return ret;
  }

  infinite operator+(const std::size_t& n)
  {
    infinite ret = *this;
    ret += n;
    return ret;
  }

  infinite operator-(const std::size_t& n)
  {
    infinite ret = *this;
    ret -= n;
    return ret;
  }

private:
  template<typename Distance>
  void next_(Distance n)
  {
    Distance d = last_ - current_;
    if (n < d)
      current_ += n;
    else
      current_ = first_ + (n - d) % (last_ - first_);
  }

  template<typename Distance>
  void prev_(Distance n)
  {
    Distance d = current_ - first_;
    if (n <= d)
      current_ -= n;
    else
      current_ = last_ - (n - d) % (last_ - first_);
  }

private:
  value_type current_;
  value_type first_;
  value_type last_;
};

}

#endif
