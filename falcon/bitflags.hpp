#ifndef FALCON_BITFLAGS_HPP
#define FALCON_BITFLAGS_HPP

#include <ios>
#include <limits>
#include <cstdio>
#include <stdexcept>
#if __cplusplus >= 201103L
# include <functional> // std:hash
#endif

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/reference.hpp>
#include <falcon/c++/conditional_cpp.hpp>
#include <falcon/bit/count.hpp>
#include <falcon/utility/move.hpp>
#include <falcon/type_traits/if.hpp>
#include <falcon/type_traits/eval_if.hpp>
#include <falcon/type_traits/use.hpp>

namespace falcon {

template<class T>
struct bitflags_traits
{
  CPP_CONSTEXPR static T full() CPP_NOEXCEPT
  {
    return static_cast<T>(~
#if __cplusplus >= 201103L
      eval_if_c_t<std::is_enum<T>, std::underlying_type<T>, use<T>>
#else
      int
#endif
      (0));
  }

  CPP_CONSTEXPR static std::size_t size() CPP_NOEXCEPT
  { return sizeof(T); }

  static void check(std::size_t pos, const char * s)
  {
    if (pos >= size()) {
#if __cplusplus >= 201103L
      char n[std::numeric_limits<std::size_t>::digits10 + 2];
#else
      char n[21];
#endif
      std::string str;
      str.reserve(80 + sizeof(n) * 2);
      str += s;
      str += ": position (which is ";
#ifdef __GNUC__
      std::sprintf(n, "%zu", pos);
#else
      std::snprintf(n, "%ul", ulong(pos));
#endif
      str += n;
      str += ") >= N (which is";
#ifdef __GNUC__
      std::sprintf(n, "%zu", size());
#else
      std::snprintf(n, "%ul", ulong(size()));
#endif
      str += n;
      str += ')';
      throw std::out_of_range(s);
    }
  }
};

namespace aux_ {
  class bitflags_integral_tag;
  class bitflags_enum_tag;
  class bitflags_other_tag;

  template<class T, class Tag
  = typename eval_if_c<
      std::is_integral<T>
    , use<bitflags_integral_tag>
    , if_c<
        std::is_enum<T>
        , bitflags_enum_tag
        , bitflags_other_tag
      >
    >::type
  >
  struct bitflags_impl;

  template<class T>
  struct bitflags_impl<T, bitflags_other_tag>
  {
    typedef typename T::reference reference;
    typedef const T & const_value_type;

    bitflags_impl()
    : x_()
    {}

    template<class U>
    bitflags_impl(U CPP_RVALUE_OR_CONST_REFERENCE x)
    : x_(FALCON_FORWARD(U, x))
    {}

    bitflags_impl(bitflags_impl const & other)
  #if __cplusplus >= 201103L
      = default;
  #else
    : x_(other.x_)
    {}
  #endif

    void do_and(const bitflags_impl& other) CPP_NOEXCEPT
    { x_ &= other.x_; }

    void do_or(const bitflags_impl& other) CPP_NOEXCEPT
    { x_ |= other.x_; }

    void do_xor(const bitflags_impl& other) CPP_NOEXCEPT
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

    CPP_CONSTEXPR std::size_t do_size() const CPP_NOEXCEPT
    { return x_.size(); }

    bool is_equal(const bitflags_impl& other) const CPP_NOEXCEPT
    { return x_ == other.x_; }

    bool is_equal(const T& other) const CPP_NOEXCEPT
    { return x_ == other; }

    bool do_test(std::size_t pos) const CPP_NOEXCEPT
    { return x_.test(pos); }

    bool are_all() const CPP_NOEXCEPT
    { return x_.all(); }

    bool is_any() const CPP_NOEXCEPT
    { return x_.any(); }

    const T & do_get() const CPP_NOEXCEPT
    { return x_; }

    T & do_get() CPP_NOEXCEPT
    { return x_; }

    unsigned long do_to_ulong() const CPP_NOEXCEPT
    { return x_.to_ulong(); }

  #if __cplusplus >= 201103L
    unsigned long long do_to_ullong() const CPP_NOEXCEPT
    { return x_.to_ullong(); }
  #endif

  private:
    T x_;
  };


  template<class Flags>
  class bitflags_reference
  {
    friend Flags;

    typename Flags::word_type * wp_;
    std::size_t bpos_;

    bitflags_reference() CPP_IF_CPP1X(= delete);

  public:
    bitflags_reference(Flags & f, std::size_t pos) CPP_NOEXCEPT
    : wp_(&f.getword(pos))
    , bpos_(f.whichbit(pos))
    {}

    // For b[i] = x;
    bitflags_reference& operator=(bool x) CPP_NOEXCEPT
    {
      if (x) {
        *wp_ |= Flags::maskbit(bpos_);
      }
      else {
        *wp_ &= ~Flags::maskbit(bpos_);
      }
      return *this;
    }

    // For b[i] = b[j];
    bitflags_reference& operator=(const bitflags_reference & j) CPP_NOEXCEPT
    {
      if (*(j.wp_) & Flags::maskbit(j.bpos_)) {
        *wp_ |= Flags::maskbit(bpos_);
      }
      else {
        *wp_ &= ~Flags::maskbit(bpos_);
      }
      return *this;
    }

    // Flips the bit
    bool operator~() const CPP_NOEXCEPT
    { return (*(wp_) & Flags::maskbit(bpos_)) == 0; }

    // For x = b[i];
    operator bool() const CPP_NOEXCEPT
    { return (*(wp_) & Flags::maskbit(bpos_)) != 0; }

    // For b[i].flip();
    bitflags_reference& flip() CPP_NOEXCEPT
    {
      *wp_ ^= Flags::maskbit(bpos_);
      return *this;
    }
  };


  template<class T, class EnumTag>
  struct bitflags_impl_base
  : bitflags_traits<T>
  {
#if __cplusplus >= 201103L
    typedef typename std::underlying_type<T>::type word_type;
#else
    typedef int word_type;
#endif

    CPP_CONSTEXPR bitflags_impl_base(T x)
    : x_(x)
    {}

  protected:
    void sanitize()
    {
      this->getword() &= static_cast<word_type>(bitflags_traits<T>::full());
    }

    static CPP_CONSTEXPR std::size_t whichbit(std::size_t pos) CPP_NOEXCEPT
    {
      return (bitflags_traits<T>::check(pos, "bitflags_impl_base::whichbit"),
        (pos % (__CHAR_BIT__ * sizeof(T)))
      );
    }

    static CPP_CONSTEXPR word_type maskbit(std::size_t pos) CPP_NOEXCEPT
    { return static_cast<word_type>(1) << whichbit(pos); }

    word_type& getword() CPP_NOEXCEPT
    { return reinterpret_cast<word_type&>(x_); }

    CPP_CONSTEXPR word_type getword() const CPP_NOEXCEPT
    { return reinterpret_cast<const word_type&>(x_); }

    word_type& getword(std::size_t) CPP_NOEXCEPT
    { return getword(); }

    CPP_CONSTEXPR word_type getword(std::size_t) const CPP_NOEXCEPT
    { return getword(); }

    T x_;
  };

  template<class T>
  struct bitflags_impl_base<T, bitflags_integral_tag>
  {
    typedef T word_type;

    CPP_CONSTEXPR bitflags_impl_base(T x)
    : x_(x)
    {}

    CPP_CONSTEXPR static T full() CPP_NOEXCEPT
    { return ~T(0); }

    CPP_CONSTEXPR static std::size_t size() CPP_NOEXCEPT
    { return std::numeric_limits<T>::digits + 1; }

    static void check(std::size_t, const char *)
    {}

  protected:
    void sanitize()
    {}

    static CPP_CONSTEXPR std::size_t whichbit(std::size_t pos) CPP_NOEXCEPT
    { return pos % (__CHAR_BIT__ * sizeof(T)); }

    static CPP_CONSTEXPR T maskbit(std::size_t pos) CPP_NOEXCEPT
    { return static_cast<T>(1) << whichbit(pos); }

    T& getword(std::size_t) CPP_NOEXCEPT
    { return x_; }

    CPP_CONSTEXPR T getword(std::size_t) const CPP_NOEXCEPT
    { return x_; }

    T& getword() CPP_NOEXCEPT
    { return reinterpret_cast<word_type&>(x_); }

    CPP_CONSTEXPR T getword() const CPP_NOEXCEPT
    { return reinterpret_cast<const word_type&>(x_); }

    T x_;
  };

  template<class T, class Tag>
  struct bitflags_impl
  : bitflags_impl_base<T, Tag>
  {
    typedef bitflags_reference<bitflags_impl> reference;
    typedef T const_value_type;

    friend class bitflags_reference<bitflags_impl>;

    bitflags_impl(T x = T())
    : bitflags_impl_base<T, Tag>(x)
    {}

    template<class U>
    bitflags_impl(U x)
    : bitflags_impl_base<T, Tag>(static_cast<T>(x))
    {}

#if __cplusplus >= 201103L
    bitflags_impl(const bitflags_impl &) = default;
#else
    bitflags_impl(const bitflags_impl & x)
    : bitflags_impl_base<T, Tag>(x)
    {}
#endif

    void do_and(const bitflags_impl& other) CPP_NOEXCEPT
    { this->getword() &= other.getword(); }

    void do_or(const bitflags_impl& other) CPP_NOEXCEPT
    { this->getword() |= other.getword(); }

    void do_xor(const bitflags_impl& other) CPP_NOEXCEPT
    { this->getword() ^= other.getword(); }

    void do_set()
    { this->getword() = bitflags_traits<T>::full(); }

    void do_set(std::size_t pos, bool val)
    {
      bitflags_traits<T>::check(pos, "bitflags_impl::do_set");
      if (val) {
        this->getword(pos) |= this->maskbit(pos);
      }
      else {
        this->getword(pos) &= ~this->maskbit(pos);
      }
    }

    void do_reset() CPP_NOEXCEPT
    { this->x_ = T(); }

    void do_reset(std::size_t pos)
    {
      bitflags_traits<T>::check(pos, "bitflags_impl::do_reset");
      this->getword(pos) &= ~this->maskbit(pos);
    }

    void do_flip() CPP_NOEXCEPT
    {
      void(this->getword() = ~this->getword()), this->sanitize();
    }

    void do_flip(std::size_t pos)
    {
      bitflags_traits<T>::check(pos, "bitflags_impl::do_flip");
      this->getword(pos) ^= ~this->maskbit(pos);
    }

    reference do_at(std::size_t pos)
    {
      bitflags_traits<T>::check(pos, "bitflags_impl::do_at");
      return reference(*this, pos);
    }

    std::size_t do_count() const CPP_NOEXCEPT
    { return bit::count(this->getword()); }

    CPP_CONSTEXPR std::size_t do_size() const CPP_NOEXCEPT
    { return bitflags_traits<T>::size(); }

    bool is_equal(const bitflags_impl& other) const CPP_NOEXCEPT
    { return this->x_ == other.x_; }

    bool is_equal(const T& other) const CPP_NOEXCEPT
    { return this->x_ == other; }

    bool do_test(std::size_t pos) const CPP_NOEXCEPT
    {
      bitflags_traits<T>::check(pos, "bitflags_impl::do_test");
      return (this->getword(pos) & this->maskbit(pos)) != static_cast<T>(0);
    }

    bool are_all() const CPP_NOEXCEPT
    { return this->x_ == bitflags_traits<T>::full(); }

    bool is_any() const CPP_NOEXCEPT
    { return this->x_ != T(); }

    T do_get() const CPP_NOEXCEPT
    { return this->x_; }

    T & do_get() CPP_NOEXCEPT
    { return this->x_; }

    unsigned long do_to_ulong() const CPP_NOEXCEPT
    { return static_cast<unsigned long>(this->getword()); }

#if __cplusplus >= 201103L
    unsigned long long do_to_ullong() const CPP_NOEXCEPT
    { return static_cast<unsigned long long>(this->getword()); }
#endif
  };
}

/**
 *  The %bitflags class represents a type of bits.
 *
 *  f1 + f2 is equivalent to f1 | f2
 *  f1 - f2 is equivalent to f1 & ~f2
 *
 *  @code
 *     #include <iostream>
 *     #include <falcon/bitflags.hpp>
 *
 *     using namespace std;
 *     using namespace falcon;
 *
 *     int main()
 *     {
 *         bitflags<unsigned> f(0xff);
 *         f -= 0x11u;
 *         f -= 0x11u;
 *
 *         cout << f << " == 0xee" endl;
 *     }
 *  @endcode
 */
template<class T>
struct bitflags
: private aux_::bitflags_impl<T>
{
  typedef T value_type;
  typedef typename aux_::bitflags_impl<T>::reference reference;

  bitflags()
  : aux_::bitflags_impl<T>()
  {}

  bitflags(const T & x)
  : aux_::bitflags_impl<T>(x)
  {}

#if __cplusplus >= 201103L
  bitflags(T && x)
  : aux_::bitflags_impl<T>(std::move(x))
  {}
#endif

  template<class U>
  bitflags(U CPP_RVALUE_OR_CONST_REFERENCE x)
  : aux_::bitflags_impl<T>(FALCON_FORWARD(U, x))
  {}

  bitflags& operator&=(const bitflags& rhs) CPP_NOEXCEPT
  {
    this->do_and(rhs);
    return *this;
  }

  bitflags& operator|=(const bitflags& rhs) CPP_NOEXCEPT
  {
    this->do_or(rhs);
    return *this;
  }

  bitflags& operator^=(const bitflags& rhs) CPP_NOEXCEPT
  {
    this->do_xor(rhs);
    return *this;
  }

  bitflags& set() CPP_NOEXCEPT
  {
    this->do_set();
    return *this;
  }

  bitflags& set(std::size_t pos, bool val = true)
  {
    this->do_set(pos, val);
    return *this;
  }

  bitflags& reset() CPP_NOEXCEPT
  {
    this->do_reset();
    return *this;
  }

  bitflags& reset(std::size_t pos)
  {
    this->do_reset(pos);
    return *this;
  }

  bitflags& flip() CPP_NOEXCEPT
  {
    this->do_flip();
    return *this;
  }

  bitflags& flip(std::size_t pos)
  {
    this->do_flip(pos);
    return *this;
  }

  bitflags operator~() const CPP_NOEXCEPT
  {
    bitflags res(*this);
    res.flip();
    return res;
  }

  reference operator[](std::size_t pos)
  { return this->do_at(pos); }

  CPP_CONSTEXPR bool operator[](std::size_t pos) const
  { return this->do_test(pos); }

  /// Returns the number of bits which are set.
  std::size_t count() const CPP_NOEXCEPT
  { return this->do_count(); }

  /// Returns the total number of bits.
  CPP_CONSTEXPR std::size_t size() const CPP_NOEXCEPT
  { return this->do_size(); }

  bool operator==(const bitflags& rhs) const CPP_NOEXCEPT
  { return this->is_equal(rhs); }

  template<class U>
  bool operator==(const bitflags<U>& rhs) const CPP_IF_CPP1X(=delete);

  bool operator==(const T& rhs) const
  { return this->is_equal(rhs); }

  bool operator!=(const bitflags& rhs) const CPP_NOEXCEPT
  { return !this->is_equal(rhs); }

  template<class U>
  bool operator!=(const bitflags<U>& rhs) const CPP_IF_CPP1X(=delete);

  bool operator!=(const T& rhs) const
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

  typename aux_::bitflags_impl<T>::const_value_type
  get() const CPP_NOEXCEPT
  { return this->do_get(); }

  T & get() CPP_NOEXCEPT
  { return this->do_get(); }

  operator FALCON_IF_NOT_IN_IDE_PARSER(typename)
    aux_::bitflags_impl<T>::const_value_type () const
  { return this->do_get(); }

  unsigned long to_ulong() const CPP_NOEXCEPT
  { return this->do_to_ulong(); }

#if __cplusplus >= 201103L
  unsigned long long to_ullong() const CPP_NOEXCEPT
  { return this->do_to_ullong(); }
#endif
};

template<class T>
bitflags<T>
operator&(bitflags<T> x, const bitflags<T>& y) CPP_NOEXCEPT
{
  x &= y;
  return x;
}

template<class T>
bitflags<T>
operator|(bitflags<T> x, const bitflags<T>& y) CPP_NOEXCEPT
{
  x |= y;
  return x;
}

template <class T>
bitflags<T>
operator^(bitflags<T> x, const bitflags<T>& y) CPP_NOEXCEPT
{
  x ^= y;
  return x;
}

template<class T>
bitflags<T>
operator&(bitflags<T> x, const T& y) CPP_NOEXCEPT
{ return x & bitflags<T>(y); }

template<class T>
bitflags<T>
operator|(bitflags<T> x, const T& y) CPP_NOEXCEPT
{ return x | bitflags<T>(y); }

template <class T>
bitflags<T>
operator^(bitflags<T> x, const T& y) CPP_NOEXCEPT
{ return x ^ bitflags<T>(y); }


template<class T>
bitflags<T> &
operator+=(bitflags<T>& x, const bitflags<T>& y) CPP_NOEXCEPT
{
  x |= y;
  return x;
}

template<class T>
bitflags<T> &
operator-=(bitflags<T>& x, bitflags<T> y) CPP_NOEXCEPT
{
  y.flip();
  x &= y;
  return x;
}

template <class T>
bitflags<T>
operator+(bitflags<T> x, const bitflags<T>& y) CPP_NOEXCEPT
{
  x += y;
  return x;
}

template <class T>
bitflags<T>
operator-(bitflags<T> x, bitflags<T> y) CPP_NOEXCEPT
{
  y.flip();
  x &= y;
  return x;
}

template<class T>
bitflags<T> &
operator+=(bitflags<T>& x, const T& y) CPP_NOEXCEPT
{ return x += bitflags<T>(y); }

template<class T>
bitflags<T> &
operator-=(bitflags<T>& x, const T& y) CPP_NOEXCEPT
{ return x -= bitflags<T>(y); }

template <class T>
bitflags<T>
operator+(bitflags<T> x, const T& y) CPP_NOEXCEPT
{ return x + bitflags<T>(y); }

template <class T>
bitflags<T>
operator-(bitflags<T> x, const T& y) CPP_NOEXCEPT
{ return x - bitflags<T>(y); }


template<class CharT, class Traits, class T>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> & os, bitflags<T> const & f)
{
  std::ios_base::fmtflags old
    = os.setf(std::ios_base::hex, std::ios_base::basefield);
  os << f.get();
  os.setf(old);
  return os;
}

template<class CharT, class Traits, class T>
std::basic_istream<CharT, Traits> &
operator>>(std::basic_istream<CharT, Traits> & is, bitflags<T> & f)
{
  std::ios_base::fmtflags old
    = is.setf(std::ios_base::hex, std::ios_base::basefield);
  is << f.get();
  is.setf(old);
  return is;
}

}

#if __cplusplus >= 201103L
namespace std {
  template<class T>
  struct hash< ::falcon::bitflags<T>>
  : std::hash<T>
  {
    typedef typename std::hash<T>::result_type result_type;
    typedef typename std::hash<T>::argument_type argument_type;

    result_type operator()(argument_type const & f) const noexcept
    { return std::hash<T>::operator()(f); }
  };
}
#endif

#endif
