#ifndef FALCON_FLAG_FLAG_HPP
#define FALCON_FLAG_FLAG_HPP

#include <cinttypes>
#include <cstring>
#include <limits>
#include <sys/types.h>
#include <falcon/c++1x/syntax.hpp>
#include <falcon/bit/fill.hpp>
#include <falcon/bit/count.hpp>
#include <falcon/c++/conditional_cpp.hpp>
#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/reference.hpp>
#include <falcon/utility/move.hpp>
#include <falcon/preprocessor/getter.hpp>
#include <falcon/arg/arg.hpp>

namespace falcon {

namespace aux_ {

class integral_flag;
class enum_flag;
class other_flag;

template<class T, class Tag>
struct flag_base_impl
{
  typedef typename T::reference reference;

  void do_and(const flag_base_impl& other) CPP_NOEXCEPT
  { x_ &= other.x_; }

  void do_or(const flag_base_impl& other) CPP_NOEXCEPT
  { x_ |= other.x_; }

  void do_xor(const flag_base_impl& other) CPP_NOEXCEPT
  { x_ ^= other.x_; }

  void do_set()
  { x_.set(); }

  void do_set(std::size_t pos, bool val)
  { x_.set(pos, val); }

  void do_reset() CPP_NOEXCEPT
  { x_.reset(); }

  void do_reset(std::size_t pos)
  { x_.reset(pos); }

  void do_flip() CPP_NOEXCEPT
  { x_.flip(); }

  void do_flip(std::size_t pos)
  { x_.flip(pos); }

  reference do_at(std::size_t pos)
  { return x_[pos]; }

  std::size_t do_count() const CPP_NOEXCEPT
  { return x_.count(); }

  /// Returns the total number of bits.
  CPP_CONSTEXPR std::size_t do_size() const CPP_NOEXCEPT
  { return x_.size(); }

  bool is_equal(const flag_base_impl& other) const CPP_NOEXCEPT
  { return x_ == other.x_; }

  bool do_test(std::size_t pos) const CPP_NOEXCEPT
  { return x_.test(pos); }

  bool are_all() const CPP_NOEXCEPT
  { return x_.all(); }

  bool is_any() const CPP_NOEXCEPT
  { return x_.any(); }

private:
  T x_;
};

template<class T, std::size_t N, class Tag>
struct flag_base_impl<T[N], Tag>
{
  typedef typename T::reference reference;

  void do_and(const flag_base_impl& other) CPP_NOEXCEPT
  {
    for (std::size_t i = 0; i < N; ++i) {
      x_[i] &= other.x_[i];
    }
  }

  void do_or(const flag_base_impl& other) CPP_NOEXCEPT
  {
    for (std::size_t i = 0; i < N; ++i) {
      x_[i] |= other.x_[i];
    }
  }

  void do_xor(const flag_base_impl& other) CPP_NOEXCEPT
  {
    for (std::size_t i = 0; i < N; ++i) {
      x_[i] ^= other.x_[i];
    }
  }

  void do_set()
  {
    for (std::size_t i = 0; i < N; ++i) {
      x_[i] = ~static_cast<T>(0);
    }
  }

  void do_set(std::size_t pos, bool val)
  {
    if (val) {
      this->getword(pos) |= this->maskbit(pos);
    }
    else {
      this->getword(pos) &= ~this->maskbit(pos);
    }
  }

  void do_reset() CPP_NOEXCEPT
  { std::memset(x_, 0, sizeof(T) * N); }

  void do_reset(std::size_t pos)
  { this->getword(pos) &= ~this->maskbit(pos); }

  void do_flip() CPP_NOEXCEPT
  {
    for (std::size_t i = 0; i < N; ++i) {
      x_[i] = ~x_[i];
    }
  }

  void do_flip(std::size_t pos)
  { this->getword(pos) ^= ~this->maskbit(pos); }

  reference do_at(std::size_t pos)
  { return reference(*this, pos); }

  std::size_t do_count() const CPP_NOEXCEPT
  {
    std::size_t result = 0;
    for (std::size_t i = 0; i < N; ++i) {
      result += bit::count(x_[i]);
    }
    return result;
  }

  /// Returns the total number of bits.
  CPP_CONSTEXPR std::size_t do_size() const CPP_NOEXCEPT
  { return std::numeric_limits<T>::digits * N; }

  bool is_equal(const flag_base_impl& other) const CPP_NOEXCEPT
  {
    for (std::size_t i = 0; i < N; ++i) {
      if (x_[i] != other.x_[i]) {
        return false;
      }
    }
    return true;
  }

  bool do_test(std::size_t pos) const CPP_NOEXCEPT
  { return (this->getword(pos) & this->maskbit(pos)) != static_cast<T>(0); }

  bool are_all() const CPP_NOEXCEPT
  {
    for (std::size_t i = 0; i < N; ++i) {
      if (x_[i] != ~static_cast<T>(0)) {
        return false;
      }
    }
    return true;
  }

  bool is_any() const CPP_NOEXCEPT
  {
    for (std::size_t i = 0; i < N; ++i) {
      if (x_[i] != static_cast<T>(0)) {
        return true;
      }
    }
    return false;
  }

private:
  static CPP_CONSTEXPR std::size_t whichbit(std::size_t pos) CPP_NOEXCEPT
  { return pos % (__CHAR_BIT__ * sizeof(T)); }

  static CPP_CONSTEXPR T maskbit(std::size_t pos) CPP_NOEXCEPT
  { return static_cast<T>(1) << whichbit(pos); }

  static CPP_CONSTEXPR std::size_t
  whichword(std::size_t pos) CPP_NOEXCEPT
  { return pos / (sizeof(T) * N); }

  T& getword(std::size_t pos) CPP_NOEXCEPT
  { return x_[whichword(pos)]; }

  CPP_CONSTEXPR T getword(std::size_t pos) const CPP_NOEXCEPT
  { return x_[whichword(pos)]; }

  T x_;
};

template<class T>
struct flag_base_impl<T, integral_flag>
{
  typedef typename T::reference reference;

  void do_and(const flag_base_impl& other) CPP_NOEXCEPT
  { x_ &= other.x_; }

  void do_or(const flag_base_impl& other) CPP_NOEXCEPT
  { x_ |= other.x_; }

  void do_xor(const flag_base_impl& other) CPP_NOEXCEPT
  { x_ ^= other.x_; }

  void do_set()
  { x_ = ~static_cast<T>(0); }

  void do_set(std::size_t pos, bool val)
  {
    if (val) {
      this->getword(pos) |= this->maskbit(pos);
    }
    else {
      this->getword(pos) &= ~this->maskbit(pos);
    }
  }

  void do_reset() CPP_NOEXCEPT
  { x_ = 0; }

  void do_reset(std::size_t pos)
  { this->getword(pos) &= ~this->maskbit(pos); }

  void do_flip() CPP_NOEXCEPT
  { x_ = ~x_; }

  void do_flip(std::size_t pos)
  { this->getword(pos) ^= ~this->maskbit(pos); }

  reference do_at(std::size_t pos)
  { return reference(*this, pos); }

  std::size_t do_count() const CPP_NOEXCEPT
  { return bit::count(x_); }

  /// Returns the total number of bits.
  CPP_CONSTEXPR std::size_t do_size() const CPP_NOEXCEPT
  { return std::numeric_limits<T>::digits; }

  bool is_equal(const flag_base_impl& other) const CPP_NOEXCEPT
  { return x_ == other.x_; }

  bool do_test(std::size_t pos) const CPP_NOEXCEPT
  { return (this->getword(pos) & this->maskbit(pos)) != static_cast<T>(0); }

  bool are_all() const CPP_NOEXCEPT
  { return x_ == ~static_cast<T>(0); }

  bool is_any() const CPP_NOEXCEPT
  { return x_ != static_cast<T>(0); }

private:
  static CPP_CONSTEXPR std::size_t whichbit(std::size_t pos) CPP_NOEXCEPT
  { return pos % (__CHAR_BIT__ * sizeof(T)); }

  static CPP_CONSTEXPR T maskbit(std::size_t pos) CPP_NOEXCEPT
  { return static_cast<T>(1) << whichbit(pos); }

  T& getword(std::size_t) CPP_NOEXCEPT
  { return x_; }

  CPP_CONSTEXPR T getword(std::size_t) const CPP_NOEXCEPT
  { return x_; }

  T x_;
};


// void check(std::size_t pos, const char * s) const
// {
//   if (pos >= N)
//   throw_out_of_range_fmt(
//     "%s: position (which is %zu) >= N (which is %zu)", s, pos, N);
// }

template<class T>
struct flag_base_impl<T, enum_flag>
{
  typedef typename T::reference reference;
  typedef enum_to_integral_t<T> integral_type;

  void do_and(const flag_base_impl& other) CPP_NOEXCEPT
  { this->getword() &= other.getword(); }

  void do_or(const flag_base_impl& other) CPP_NOEXCEPT
  { this->getword() |= other.getword(); }

  void do_xor(const flag_base_impl& other) CPP_NOEXCEPT
  { this->getword() ^= other.getword(); }

  void do_set()
  { this->getword() = ~static_cast<integral_type>(0); }

  void do_set(std::size_t pos, bool val)
  {
    if (val) {
      this->getword(pos) |= this->maskbit(pos);
    }
    else {
      this->getword(pos) &= ~this->maskbit(pos);
    }
  }

  void do_reset() CPP_NOEXCEPT
  { x_ = static_cast<T>(0); }

  void do_reset(std::size_t pos)
  { this->getword(pos) &= ~this->maskbit(pos); }

  void do_flip() CPP_NOEXCEPT
  { this->getword() = ~this->getword(); }

  void do_flip(std::size_t pos)
  { this->getword(pos) ^= ~this->maskbit(pos); }

  reference do_at(std::size_t pos)
  { return reference(*this, pos); }

  std::size_t do_count() const CPP_NOEXCEPT
  { return bit::count(this->getword()); }

  /// Returns the total number of bits.
  CPP_CONSTEXPR std::size_t do_size() const CPP_NOEXCEPT
  // TODO flag_traits<T> ?
  { return std::numeric_limits<integral_type>::digits; }

  bool is_equal(const flag_base_impl& other) const CPP_NOEXCEPT
  { return x_ == other.x_; }

  bool do_test(std::size_t pos) const CPP_NOEXCEPT
  { return (this->getword(pos) & this->maskbit(pos)) != static_cast<T>(0); }

  bool are_all() const CPP_NOEXCEPT
  // TODO flag_traits<T> ?
  { return x_ == static_cast<T>(~integral_type(0)); }

  bool is_any() const CPP_NOEXCEPT
  { return x_ != static_cast<T>(0); }

private:
  static CPP_CONSTEXPR std::size_t whichbit(std::size_t pos) CPP_NOEXCEPT
  // TODO flag_traits<T> ?
  { return pos % (__CHAR_BIT__ * sizeof(T)); }

  static CPP_CONSTEXPR T maskbit(std::size_t pos) CPP_NOEXCEPT
  { return static_cast<integral_type>(1) << whichbit(pos); }

  integral_type& getword() CPP_NOEXCEPT
  { return reinterpret_cast<integral_type&>(x_); }

  CPP_CONSTEXPR integral_type getword() const CPP_NOEXCEPT
  { return reinterpret_cast<integral_type>(x_); }

  integral_type& getword(std::size_t) CPP_NOEXCEPT
  { return getword(); }

  CPP_CONSTEXPR integral_type getword(std::size_t) const CPP_NOEXCEPT
  { return getword(); }

  T x_;
};


template<typename T>
struct flag_base
: flag_base_impl<T>
{
  typedef T value_type;

  class reference
  {
    friend class flag_base;

    T* wp_;
    std::size_t bpos_;

    // left undefined
    reference() CPP_IF_CPP1X(= delete);

  public:
    reference(flag_base& b, std::size_t pos) CPP_NOEXCEPT
    {
      wp_ = &b.getword(pos);
      bpos_ = whichbit(pos);
    }

    // For b[i] = x;
    reference& operator=(bool x) CPP_NOEXCEPT
    {
      if (x) {
        *wp_ |= maskbit(bpos_);
      }
      else {
        *wp_ &= ~maskbit(bpos_);
      }
      return *this;
    }

    // For b[i] = b[j];
    reference& operator=(const reference& j) CPP_NOEXCEPT
    {
      if (*(j.wp_) & maskbit(j.bpos_)) {
        *wp_ |= maskbit(bpos_);
      }
      else {
        *wp_ &= ~maskbit(bpos_);
      }
      return *this;
    }

    // Flips the bit
    bool operator~() const CPP_NOEXCEPT
    { return (*(wp_) & maskbit(bpos_)) == 0; }

    // For x = b[i];
    operator bool() const CPP_NOEXCEPT
    { return (*(wp_) & maskbit(bpos_)) != 0; }

    // For b[i].flip();
    reference& flip() CPP_NOEXCEPT
    {
      *wp_ ^= maskbit(bpos_);
      return *this;
    }
  };

  flag_base(T const & x)
  : x_(x)
  {}

#if __cplusplus >= 201103L
  flag_base(T && x)
  : x_(std::move(x))
  {}
#endif

  flag_base()
  : x_()
  {}

  flag_base& operator&=(const flag_base& rhs) CPP_NOEXCEPT
  {
    this->do_and(rhs);
    return *this;
  }

  flag_base& operator|=(const flag_base& rhs) CPP_NOEXCEPT
  {
    this->do_or(rhs);
    return *this;
  }

  flag_base& operator^=(const flag_base& rhs) CPP_NOEXCEPT
  {
    this->do_xor(rhs);
    return *this;
  }

  flag_base& set() CPP_NOEXCEPT
  {
    this->do_set();
    return *this;
  }

  flag_base& set(std::size_t pos, bool val = true)
  {
    this->do_set(pos, val);
    return *this;
  }

  flag_base& reset() CPP_NOEXCEPT
  {
    this->do_reset();
    return *this;
  }

  flag_base& reset(std::size_t pos)
  {
    this->do_reset(pos);
    return *this;
  }

  flag_base& flip() CPP_NOEXCEPT
  {
    this->do_flip();
    return *this;
  }

  flag_base& flip(std::size_t pos)
  {
    this->do_flip();
    return *this;
  }

  flag_base operator~() const CPP_NOEXCEPT
  {
    flag_base res(*this);
    res.flip();
    return res;
  }

  reference operator[](std::size_t pos)
  { return this->do_at(pos); }

  CPP_CONSTEXPR bool operator[](std::size_t pos) const
  { return test(pos); }

  /// Returns the number of bits which are set.
  std::size_t count() const CPP_NOEXCEPT
  { return this->do_count(); }

  /// Returns the total number of bits.
  CPP_CONSTEXPR std::size_t size() const CPP_NOEXCEPT
  { return this->do_size(); }

  bool operator==(const flag_base& rhs) const CPP_NOEXCEPT
  { return this->is_equal(rhs); }

  bool operator!=(const flag_base& rhs) const CPP_NOEXCEPT
  { return !this->is_equal(rhs); }

  bool test(std::size_t pos) CPP_NOEXCEPT
  { return this->do_test(pos); }

  /**
   *  @brief Tests whether all the bits are on.
   *  @return  True if all the bits are set.
   */
  bool all() const CPP_NOEXCEPT
  { return this->are_all(); }

  /**
   *  @brief Tests whether any of the bits are on.
   *  @return  True if at least one bit is set.
   */
  bool any() const CPP_NOEXCEPT
  { return this->is_any(); }

  /**
   *  @brief Tests whether any of the bits are on.
   *  @return  True if none of the bits are set.
   */
  bool none() const CPP_NOEXCEPT
  { return !this->is_any(); }

private:
  static CPP_CONSTEXPR std::size_t whichbit(std::size_t pos) CPP_NOEXCEPT
  { return pos % sizeof(T); }

  static CPP_CONSTEXPR T maskbit(std::size_t pos) CPP_NOEXCEPT
  { return static_cast<T>(1) << whichbit(pos); }

  T& getword(std::size_t /*pos*/) CPP_NOEXCEPT
  { return x_; }

  const T& getword(std::size_t /*pos*/) CPP_NOEXCEPT
  { return x_; }

  T x_;
};

template<class T>
inline flag_base
operator&(const flag_base& x, const flag_base& y) CPP_NOEXCEPT
{
  flag_base res(x);
  res &= y;
  return res;
}

template<class T>
inline flag_base
operator|(const flag_base& x, const flag_base& y) CPP_NOEXCEPT
{
  flag_base res(x);
  res |= y;
  return res;
}

template <class T>
inline flag_base
operator^(const flag_base& x, const flag_base& y) CPP_NOEXCEPT
{
  flag_base res(x);
  res ^= y;
  return res;
}

// TODO std::hash

}

///TODO flag_position(n) → 1 << n

template<typename T>
struct flag
{
  typedef T value_type;

private:
  typedef flag<T> self_type;

  value_type flag_;

public:
  CPP_CONSTEXPR flag(value_type x)
  : flag_(x)
  {}

  CPP_CONSTEXPR flag(const self_type& other)
  : flag_(other.flag_)
  {}

  CPP_CONSTEXPR flag()
  : flag_(0)
  {}

  static CPP_CONSTEXPR self_type full()
  { return self_type(~T(0)); }

  CPP_CONSTEXPR std::size_t size() const
  { return sizeof(T); }

  value_type& get()
  { return flag_; }
  const value_type& get() const
  { return flag_; }

  self_type& operator=(value_type x)
  {
    flag_ = x;
    return *this;
  }

  self_type& operator=(const self_type& other)
  {
    flag_ = other.flag_;
    return *this;
  }

  CPP_CONSTEXPR self_type operator&(const self_type& other) const
  { return self_type(flag_ & other.flag_); }
  CPP_CONSTEXPR self_type operator|(const self_type& other) const
  { return self_type(flag_ | other.flag_); }

  CPP_CONSTEXPR self_type operator&(const value_type& other) const
  { return self_type(flag_ & other); }
  CPP_CONSTEXPR self_type operator|(const value_type& other) const
  { return self_type(flag_ | other); }

  CPP_CONSTEXPR self_type operator+(const self_type& other) const
  { return *this | other; }
  CPP_CONSTEXPR self_type operator-(const self_type& other) const
  { return this->flag_ ^ other; }

  CPP_CONSTEXPR self_type operator+(const value_type& other) const
  { return *this | other; }
  CPP_CONSTEXPR self_type operator-(const value_type& other) const
  { return *this ^ other; }

  self_type& operator&=(const self_type& other)
  {
    flag_ &= other.flag_;
      return *this;
  }
  self_type& operator|=(const self_type& other)
  {
    flag_ |= other.flag_;
    return *this;
  }

  self_type& operator&=(const value_type& other)
  {
    flag_ &= other;
    return *this;
  }
  self_type& operator|=(const value_type& other)
  {
    flag_ |= other;
    return *this;
  }

  self_type& operator+=(const self_type& other)
  { return *this |= other; }
  self_type& operator-=(const self_type& other)
  { return *this &= ~other; }

  self_type& operator+=(const value_type& other)
  { return *this |= other; }
  self_type& operator-=(const value_type& other)
  { return *this ^= other; }

  CPP_CONSTEXPR self_type operator~() const
  { return  self_type(~flag_); }

  void flip()
  { flag_ ^= bit::fill<value_type>::value; }

  CPP_CONSTEXPR self_type operator^(const self_type& other) const
  { return self_type(flag_ ^ other.flag_); }

  CPP_CONSTEXPR self_type operator^(const value_type& other) const
  { return flag_ ^ other; }

  self_type& operator^=(const self_type& other)
  {
    flag_ ^= other.flag_;
    return *this;
  }
  self_type& operator^=(const value_type& other)
  {
    flag_ ^= other;
    return *this;
  }

  CPP_CONSTEXPR self_type operator<<(unsigned int n) const
  { return self_type(flag_ << n); }

  self_type& operator<<=(unsigned int n)
  {
    flag_ <<= n;
    return *this;
  }

  CPP_CONSTEXPR self_type operator>>(unsigned int n) const
  { return self_type(flag_ >> n); }

  self_type& operator>>=(unsigned int n)
  {
    flag_ >>= n;
    return *this;
  }

  CPP_CONSTEXPR bool operator==(const self_type& other) const
  { return flag_ == other.flag_; }
  CPP_CONSTEXPR bool operator==(const value_type& other) const
  { return flag_ == other; }

  CPP_CONSTEXPR bool operator!=(const self_type& other) const
  { return !(*this == other); }
  CPP_CONSTEXPR bool operator!=(const value_type& other) const
  { return !(*this == other); }

  void clear(const value_type& remove = bit::fill<value_type>::value)
  { flag_ ^= remove; }

  /**
    * \brief Check that a flag is true for all the bits
    * @{
    */
  CPP_CONSTEXPR bool has(const value_type& x) const
  { return (flag_ & x) == x; }

  CPP_CONSTEXPR bool has(const self_type& x) const
  { return (flag_ & x.flag_) == x.flag_; }
  //@}

  /**
    * \brief Check that a flag is true for at least a bit
    * @{
    */
  CPP_CONSTEXPR bool has_one(const value_type& x) const
  { return flag_ & x; }

  CPP_CONSTEXPR bool has_one(const self_type& x) const
  { return flag_ & x.flag_; }
  //@}
};

template<>
struct flag<void>
{
  typedef void value_type;

private:
  typedef flag<void> self_type;

public:
  static CPP_CONSTEXPR self_type full()
  {
      return self_type();
  }

  CPP_CONSTEXPR unsigned int size() const
  { return 0; }

  void flip()
  {  }

  /**
    * \brief Check that a flag is true for all the bits
    * @{
    */
  CPP_CONSTEXPR bool has(const self_type&) const
  { return false; }

  CPP_CONSTEXPR bool has(unsigned long) const
  { return false; }
  //@}

  /**
    * \brief Check that a flag is true for at least a bit
    * @{
    */
  CPP_CONSTEXPR bool has_one(const self_type&) const
  { return false; }

  CPP_CONSTEXPR bool has_one(unsigned long) const
  { return false; }
  //@}

  CPP_CONSTEXPR operator bool () const
  { return false; }

  CPP_CONSTEXPR bool operator==(const self_type& /*other*/) const
  { return true; }
  CPP_CONSTEXPR bool operator==(std::size_t other) const
  { return static_cast<bool>(other); }

  CPP_CONSTEXPR bool operator!=(const self_type& /*other*/) const
  { return false; }
  CPP_CONSTEXPR bool operator!=(std::size_t other) const
  { return !(*this == other); }

  self_type operator|(const self_type&) const
  { return *this; }
  self_type operator|(std::size_t) const
  { return *this; }

  self_type operator^(const self_type&) const
  { return *this; }
  self_type operator^(std::size_t) const
  { return *this; }

  self_type operator&(const self_type&) const
  { return *this; }
  self_type operator&(std::size_t) const
  { return *this; }

  self_type operator<<(const self_type&) const
  { return *this; }
  self_type operator<<(std::size_t) const
  { return *this; }

  self_type operator>>(const self_type&) const
  { return *this; }
  self_type operator>>(std::size_t) const
  { return *this; }

  self_type operator+(const self_type&) const
  { return *this; }
  self_type operator+(std::size_t) const
  { return *this; }

  self_type operator-(const self_type&) const
  { return *this; }
  self_type operator-(std::size_t) const
  { return *this; }

  self_type& operator|=(const self_type&)
  { return *this; }
  self_type& operator|=(std::size_t)
  { return *this; }

  self_type& operator^=(const self_type&)
  { return *this; }
  self_type& operator^=(std::size_t)
  { return *this; }

  self_type& operator&=(const self_type&)
  { return *this; }
  self_type& operator&=(std::size_t)
  { return *this; }

  self_type& operator<<=(const self_type&)
  { return *this; }
  self_type& operator<<=(std::size_t)
  { return *this; }

  self_type& operator>>=(const self_type&)
  { return *this; }
  self_type& operator>>=(std::size_t)
  { return *this; }

  self_type& operator+=(const self_type&)
  { return *this; }
  self_type& operator+=(std::size_t)
  { return *this; }

  self_type& operator-=(const self_type&)
  { return *this; }
  self_type& operator-=(std::size_t)
  { return *this; }

  void clear(unsigned int = 0)
  { }
};

template<typename T, std::size_t _N>
struct flag<T[_N]>
{
  typedef T value_type[_N];

  typedef flag<T[_N]> self_type;

  value_type flag_;

public:
#if __cplusplus >= 201103L
  template<typename _U, typename... _Args, typename _ = typename std::enable_if<std::is_integral<_U>::value>::type>
  constexpr flag(const _U& x, const _Args&... xs)
  : flag_{x, xs...}
  {}

private:
  template<std::size_t _Num, typename... _Args>
  struct make_full
  {
    constexpr static self_type make(_Args... args)
    {
      return make_full<_Num+1, _Args..., T>::make(args..., ~T(0));
    }
  };
  template<typename... _Args>
  struct make_full<_N, _Args...>
  {
    constexpr static self_type make(_Args... args)
    {
      return flag(args...);
    }
  };

public:
  constexpr static self_type full()
  {
    return make_full<1, T>::make(~T(0));
  }
#else
  flag(const value_type& xs)
  {
    for (std::size_t i = 0; i != _N; ++i)
      *flag_[i] = *xs[i];
  }

  flag(const self_type& other)
  {
    for (std::size_t i = 0; i != _N; ++i)
      *flag_[i] = *other.flag_s[i];
    *this = other;
  }

  flag& operator=(const self_type& other)
  {
    for (std::size_t i = 0; i != _N; ++i)
      *flag_[i] = *other.flag_s[i];
    return *this;
  }

  static self_type full()
  {
    self_type ret;
    ret.flip();
    return ret;
  }
#endif

  ///TODO constructeur avec initializer_list + array
  CPP_CONSTEXPR flag()
  : flag_ CPP1X()
  {}

  T& operator[](std::size_t n)
  { return flag_[n]; }
  const T& operator[](std::size_t n) const
  { return flag_[n]; }

  CPP_CONSTEXPR std::size_t size() const
  { return sizeof(T) * _N; }

  value_type& get()
  { return flag_; }
  const value_type& get() const
  { return flag_; }

#if __cplusplus >= 201103L
      ///TODO move algorithm : namespace constexpr_algorithm ? namespce cexpr ?
#define _FALCON_FLAG_MAKE_BINARY_OPERATOR(name, Op)\
  private:\
    template<std::size_t _Num, typename... _Args>\
    struct name\
    {\
      constexpr static self_type run(const value_type& flags, const value_type& other, _Args... args)\
      {\
        return name<_Num+1, _Args..., T>::run(flags, other, args..., flags[_Num] Op other[_Num]);\
      }\
    };\
    template<typename... _Args>\
    struct name<_N, _Args...>\
    {\
      constexpr static self_type run(const value_type&, const value_type&, _Args... args)\
      {\
        return self_type(args...);\
      }\
    };\
  public:\
    constexpr self_type operator Op(const self_type& other) const\
    {\
      return name<0, T>::run(flag_, other.flag_);\
    }
#else
#define _FALCON_FLAG_MAKE_BINARY_OPERATOR(name, Op)\
  self_type operator Op(const self_type& other) const\
  {\
    self_type ret(*this);\
    ret Op##= other;\
    return ret;\
  }
#endif

  _FALCON_FLAG_MAKE_BINARY_OPERATOR(op_and, &)
  _FALCON_FLAG_MAKE_BINARY_OPERATOR(op_or, |)
  _FALCON_FLAG_MAKE_BINARY_OPERATOR(op_xor, ^)

  CPP_CONSTEXPR self_type operator+(const self_type& other) const
  { return *this | other; }
  CPP_CONSTEXPR self_type operator-(const self_type& other) const
  { return this->flag_ ^ other.flag_; }

  self_type& operator&=(const self_type& other)
  {
    for (std::size_t i = 0; i != _N; ++i)
      ~flag_[i] &= other.flag_[i];
    return *this;
  }
  self_type& operator|=(const self_type& other)
  {
    for (std::size_t i = 0; i != _N; ++i)
      ~flag_[i] |= other.flag_[i];
    return *this;
  }

  self_type& operator+=(const self_type& other)
  { return *this |= other; }
  self_type& operator-=(const self_type& other)
  { return *this ^= other.flag_; }

#if __cplusplus >= 201103L
private:
  template<std::size_t _Num, typename... _Args>
  struct op_compl
  {
    constexpr static self_type run(const value_type& flags, _Args... args)
    {
      return op_compl<_Num+1, _Args..., T>::run(flags, args..., ~flags[_Num]);
    }
  };
  template<typename... _Args>
  struct op_compl<_N, _Args...>
  {
    constexpr static self_type run(const value_type&, _Args... args)
    {
      return self_type(args...);
    }
  };
public:
  constexpr self_type operator~() const
  {
    return op_compl<1, T>::run(flag_, ~flag_[0]);
  }
#else
  self_type operator~(const self_type& other) const
  {
    self_type ret(*this);
    ret.flip();
    return ret;
  }
#endif

  void flip()
  {
    for (std::size_t i = 0; i != _N; ++i)
      flag_[i] ^= bit::fill<T>::value;
  }

  void clear(const self_type& remove)
  { flag_ ^= remove; }

  void clear()
  {
    for (std::size_t i = 0; i != _N; ++i)
      flag_[0] = 0;
  }

private:
  self_type& set_null()
  {
    clear();
    return *this;
  }

public:
  ///TODO le faire en constexpr
  self_type operator<<(unsigned int n) const
  {
    self_type ret(*this);
    ret <<= n;
    return ret;
  }

  self_type& operator<<=(std::size_t n)
  {
    if (n >= bit::size<T>::value * _N)
      return set_null();
    std::size_t d = n / (bit::size<T>::value);
    n %= bit::size<T>::value;
    flag_[0] = flag_[d] << n;
    for (std::size_t i = d; i != _N; ++i)
    {
      flag_[i-d-1] |= flag_[i] << n >> n;
      flag_[i] <<= n;
    }
    while (d)
      flag_[_N - d--] = 0;
    return *this;
  }

  ///TODO le faire en constexpr
  self_type operator>>(unsigned int n) const
  {
    self_type ret(*this);
    ret >>= n;
    return ret;
  }

  self_type& operator>>=(unsigned int n)
  {
    if (n >= bit::size<T>::value * _N)
      return set_null();
    std::size_t d = n / (bit::size<T>::value);
    n %= unsigned(bit::size<T>::value);
    for (std::size_t i = _N-1; i != _N-1-d; --i)
    {
      flag_[i] = flag_[i-d] >> n;
      flag_[i] |= flag_[i-1-d] >> n << n;
    }
    flag_[d] >>= n;
    while (d)
      flag_[--d] = 0;
    return *this;
  }


#if __cplusplus >= 201103L
private:
  template<std::size_t _Num, typename _U>
  struct op_eq
  {
    constexpr static bool run(const _U& flags, const _U& other)
    {
      return flags[_Num] == other[_Num] ? op_eq<_Num+1, _U>::run(flags, other) : false;
    }
  };
  template<typename _U>
  struct op_eq<_N, _U>
  {
    constexpr static bool run(const _U&, const _U&)
    {
      return true;
    }
  };
public:
  constexpr bool operator==(const self_type& other) const
  {
    return op_eq<0, value_type>::run(flag_, other.flag_);
  }
#else
  bool operator==(const self_type& other) const
  {
    for (std::size_t i = 0; i != _N; ++i)
    {
      if (flag_[i] != other.flag_[i])
        return false;
    }
    return true;
  }
#endif
  ///TODO operator== pour initializer_list et T et value_type + std::array

  CPP_CONSTEXPR bool operator!=(const self_type& other) const
  { return !(*this == other); }

  /**
   * \brief Check that a flag is true for all the bits
   * @{
   */
  ///TODO not optimal
  CPP_CONSTEXPR bool has(const self_type& other) const
  { return (*this & other) == other; }
  CPP_CONSTEXPR bool has(std::size_t other) const
  { return (flag_[_N-1] & other) == other; }
  //@}

  /**
   * \brief Check that a flag is true for at least a bit
   * @{
   */
  CPP_CONSTEXPR bool has_one(const self_type& other) const
  { return *this & other; }
  CPP_CONSTEXPR bool has_one(std::size_t other) const
  { return flag_[_N-1] & other; }
  //@}
};

typedef flag<void> flag0;
typedef flag<uint32_t> flag32;
typedef flag<uint64_t> flag64;
typedef flag<uint64_t[2]> flag128;
typedef flag<uint64_t[3]> flag192;
typedef flag<uint64_t[4]> flag256;

///TODO int pas forcement egal a 32, le prevoir por selectionner un int si possible
template<std::size_t _Choose, bool u, bool u32, bool u64>
struct x_type_selector
{
  typedef uint64_t type[
    (_Choose + (bit::size<uint64_t>::value - 1)) / (bit::size<uint64_t>::value)
  ];
};

template<std::size_t _Choose>
struct x_type_selector<_Choose, true, true, true>
{
  typedef unsigned type;
};

template<std::size_t _Choose>
struct x_type_selector<_Choose, false, true, true>
{
  typedef uint32_t type;
};

template<std::size_t _Choose>
struct x_type_selector<_Choose, false, false, true>
{
  typedef uint64_t type;
};

template<std::size_t _Choose>
struct flag_selector
{
  typedef flag<typename x_type_selector<_Choose,
    (bit::size<unsigned>::value >= _Choose),
    (bit::size<uint32_t>::value >= _Choose),
    (bit::size<uint64_t>::value >= _Choose)
  >::type> type;
};

template<>
struct flag_selector<0>
{
  typedef flag<void> type;
};

///TODO operator <<, … pour T op _Flag

}

#endif
