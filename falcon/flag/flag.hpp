#ifndef FALCON_FLAG_FLAG_HPP
#define FALCON_FLAG_FLAG_HPP

#if __cplusplus >= 201103L
# include <functional> // std:hash
#endif
#include <ios>
#include <iosfwd>
#include <cstring>
#include <limits>
#include <string>
#include <cstdio>
#include <stdexcept>
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
#include <falcon/type_traits/if.hpp>
#include <falcon/type_traits/eval_if.hpp>
#include <falcon/type_traits/use.hpp>

namespace falcon {

namespace aux_ {
  class integral_flag;
  class enum_flag;
  class other_flag;

  // TODO internal typedef const_reference_flag (T or T const&)

  template<class T, class Tag
  = typename eval_if_c<
      std::is_integral<T>
    , use<integral_flag>
    , if_c<
        std::is_enum<T>
        , enum_flag
        , other_flag
      >
    >::type
  >
  struct bitflag_impl
  {
    typedef typename T::reference reference;
    typedef const T & const_value_type;

    bitflag_impl()
    : x_()
    {}

    template<class U>
    bitflag_impl(U CPP_RVALUE_OR_CONST_REFERENCE x)
    : x_(FALCON_FORWARD(U, x))
    {}

    bitflag_impl(bitflag_impl const & other)
  #if __cplusplus >= 201103L
      = default;
  #else
    : x_(other.x_)
    {}
  #endif

    void do_and(const bitflag_impl& other) CPP_NOEXCEPT
    { x_ &= other.x_; }

    void do_or(const bitflag_impl& other) CPP_NOEXCEPT
    { x_ |= other.x_; }

    void do_xor(const bitflag_impl& other) CPP_NOEXCEPT
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

    bool is_equal(const bitflag_impl& other) const CPP_NOEXCEPT
    { return x_ == other.x_; }

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

    unsigned long do_to_ulong() const
    { return x_.to_ulong(); }

  #if __cplusplus >= 201103L
    unsigned long long do_to_ullong() const
    { return x_.to_ullong(); }
  #endif

  private:
    T x_;
  };


  template<class Flags>
  class flag_reference
  {
    friend Flags;

    typename Flags::word_type * wp_;
    std::size_t bpos_;

    flag_reference() CPP_IF_CPP1X(= delete);

  public:
    flag_reference(Flags & f, std::size_t pos) CPP_NOEXCEPT
    : wp_(&f.getword(pos))
    , bpos_(f.whichbit(pos))
    {}

    // For b[i] = x;
    flag_reference& operator=(bool x) CPP_NOEXCEPT
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
    flag_reference& operator=(const flag_reference & j) CPP_NOEXCEPT
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
    flag_reference& flip() CPP_NOEXCEPT
    {
      *wp_ ^= Flags::maskbit(bpos_);
      return *this;
    }
  };


  template<class T>
  struct flag_traits
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


  template<class T>
  struct bitflag_impl<T, integral_flag>
  {
    typedef flag_reference<bitflag_impl> reference;
    typedef T const_value_type;

    friend class flag_reference<bitflag_impl>;

    bitflag_impl(T x = 0)
    : x_(x)
    {}

    void do_and(const bitflag_impl& other) CPP_NOEXCEPT
    { x_ &= other.x_; }

    void do_or(const bitflag_impl& other) CPP_NOEXCEPT
    { x_ |= other.x_; }

    void do_xor(const bitflag_impl& other) CPP_NOEXCEPT
    { x_ ^= other.x_; }

    void do_set()
    { x_ = ~static_cast<T>(0); }

    void do_set(std::size_t pos, bool val)
    {
      flag_traits<T>::check(pos, "bitflag_impl<T,integral_flag>::do_set");
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
    {
      flag_traits<T>::check(pos, "bitflag_impl<T,integral_flag>::do_reset");
      this->getword(pos) &= ~this->maskbit(pos);
    }

    void do_flip() CPP_NOEXCEPT
    { x_ = ~x_; }

    void do_flip(std::size_t pos)
    {
      flag_traits<T>::check(pos, "bitflag_impl<T,integral_flag>::do_flip");
      this->getword(pos) ^= ~this->maskbit(pos);
    }

    reference do_at(std::size_t pos)
    {
      flag_traits<T>::check(pos, "bitflag_impl<T,integral_flag>::do_at");
      return reference(*this, pos);
    }

    std::size_t do_count() const CPP_NOEXCEPT
    { return bit::count(x_); }

    CPP_CONSTEXPR std::size_t do_size() const CPP_NOEXCEPT
    { return std::numeric_limits<T>::digits; }

    bool is_equal(const bitflag_impl& other) const CPP_NOEXCEPT
    { return x_ == other.x_; }

    bool do_test(std::size_t pos) const CPP_NOEXCEPT
    {
      flag_traits<T>::check(pos, "bitflag_impl<T,integral_flag>::do_test");
      return (this->getword(pos) & this->maskbit(pos)) != static_cast<T>(0);
    }

    bool are_all() const CPP_NOEXCEPT
    { return x_ == ~static_cast<T>(0); }

    bool is_any() const CPP_NOEXCEPT
    { return x_ != static_cast<T>(0); }

    T do_get() const CPP_NOEXCEPT
    { return x_; }

    T & do_get() CPP_NOEXCEPT
    { return x_; }

    unsigned long do_to_ulong() const
    { return static_cast<unsigned long>(x_); }

#if __cplusplus >= 201103L
    unsigned long long do_to_ullong() const
    { return static_cast<unsigned long long>(x_); }
#endif

  private:
    typedef std::size_t word_type;

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

  template<class T>
  struct bitflag_impl<T, enum_flag>
  {
    typedef flag_reference<bitflag_impl> reference;
    typedef T const_value_type;

    friend class flag_reference<bitflag_impl>;

#if __cplusplus >= 201103L
    typedef typename std::underlying_type<T>::type integral_type;
#else
    typedef int integral_type;
#endif

    bitflag_impl()
    : x_()
    {}

    bitflag_impl(T x)
    : x_(x)
    {}

    void do_and(const bitflag_impl& other) CPP_NOEXCEPT
    { this->getword() &= other.getword(); }

    void do_or(const bitflag_impl& other) CPP_NOEXCEPT
    { this->getword() |= other.getword(); }

    void do_xor(const bitflag_impl& other) CPP_NOEXCEPT
    { this->getword() ^= other.getword(); }

    void do_set()
    { this->getword() = ~static_cast<integral_type>(0); }

    void do_set(std::size_t pos, bool val)
    {
      flag_traits<T>::check(pos, "bitflag_impl<T,enum_flag>::do_set");
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
    {
      flag_traits<T>::check(pos, "bitflag_impl<T,enum_flag>::do_reset");
      this->getword(pos) &= ~this->maskbit(pos);
    }

    void do_flip() CPP_NOEXCEPT
    { this->getword() = (~this->getword()
    & static_cast<integral_type>(flag_traits<T>::full())); }

    void do_flip(std::size_t pos)
    {
      flag_traits<T>::check(pos, "bitflag_impl<T,enum_flag>::do_flip");
      this->getword(pos) ^= ~this->maskbit(pos);
    }

    reference do_at(std::size_t pos)
    {
      flag_traits<T>::check(pos, "bitflag_impl<T,enum_flag>::do_at");
      return reference(*this, pos);
    }

    std::size_t do_count() const CPP_NOEXCEPT
    { return bit::count(this->getword()); }

    CPP_CONSTEXPR std::size_t do_size() const CPP_NOEXCEPT
    { return flag_traits<T>::size(); }

    bool is_equal(const bitflag_impl& other) const CPP_NOEXCEPT
    { return x_ == other.x_; }

    bool do_test(std::size_t pos) const CPP_NOEXCEPT
    {
      flag_traits<T>::check(pos, "bitflag_impl<T,enum_flag>::do_test");
      return (this->getword(pos) & this->maskbit(pos)) != static_cast<T>(0);
    }

    bool are_all() const CPP_NOEXCEPT
    // TODO flag_traits<T> ?
    { return x_ == flag_traits<T>::full(); }

    bool is_any() const CPP_NOEXCEPT
    { return x_ != static_cast<T>(0); }

    T do_get() const CPP_NOEXCEPT
    { return x_; }

    T & do_get() CPP_NOEXCEPT
    { return x_; }

    unsigned long do_to_ulong() const
    { return static_cast<unsigned long>(getword()); }

#if __cplusplus >= 201103L
    unsigned long long do_to_ullong() const
    { return static_cast<unsigned long long>(getword()); }
#endif

  private:
    typedef integral_type word_type;

    static CPP_CONSTEXPR std::size_t whichbit(std::size_t pos) CPP_NOEXCEPT
    // TODO flag_traits<T> ?
    { return pos % (__CHAR_BIT__ * sizeof(T)); }

    static CPP_CONSTEXPR T maskbit(std::size_t pos) CPP_NOEXCEPT
    { return static_cast<integral_type>(1) << whichbit(pos); }

    integral_type& getword() CPP_NOEXCEPT
    { return reinterpret_cast<integral_type&>(x_); }

    CPP_CONSTEXPR integral_type getword() const CPP_NOEXCEPT
    { return reinterpret_cast<const integral_type&>(x_); }

    integral_type& getword(std::size_t) CPP_NOEXCEPT
    { return getword(); }

    CPP_CONSTEXPR integral_type getword(std::size_t) const CPP_NOEXCEPT
    { return getword(); }

    T x_;
  };
}


template<typename T>
struct bitflag
: private aux_::bitflag_impl<T>
{
  typedef T value_type;
  typedef typename aux_::bitflag_impl<T>::reference reference;

  bitflag()
  : aux_::bitflag_impl<T>()
  {}

  bitflag(T const & x)
  : aux_::bitflag_impl<T>(x)
  {}

#if __cplusplus >= 201103L
  bitflag(T && x)
  : aux_::bitflag_impl<T>(std::move(x))
  {}
#endif

  template<class U>
  bitflag(U CPP_RVALUE_OR_CONST_REFERENCE x)
  : aux_::bitflag_impl<T>(FALCON_FORWARD(U, x))
  {}

  bitflag& operator&=(const bitflag& rhs) CPP_NOEXCEPT
  {
    this->do_and(rhs);
    return *this;
  }

  bitflag& operator|=(const bitflag& rhs) CPP_NOEXCEPT
  {
    this->do_or(rhs);
    return *this;
  }

  bitflag& operator^=(const bitflag& rhs) CPP_NOEXCEPT
  {
    this->do_xor(rhs);
    return *this;
  }

  bitflag& set() CPP_NOEXCEPT
  {
    this->do_set();
    return *this;
  }

  bitflag& set(std::size_t pos, bool val = true)
  {
    this->do_set(pos, val);
    return *this;
  }

  bitflag& reset() CPP_NOEXCEPT
  {
    this->do_reset();
    return *this;
  }

  bitflag& reset(std::size_t pos)
  {
    this->do_reset(pos);
    return *this;
  }

  bitflag& flip() CPP_NOEXCEPT
  {
    this->do_flip();
    return *this;
  }

  bitflag& flip(std::size_t pos)
  {
    this->do_flip(pos);
    return *this;
  }

  bitflag operator~() const CPP_NOEXCEPT
  {
    bitflag res(*this);
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

  bool operator==(const bitflag& rhs) const CPP_NOEXCEPT
  { return this->is_equal(rhs); }

  bool operator!=(const bitflag& rhs) const CPP_NOEXCEPT
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

  // TODO getter_type
  typename aux_::bitflag_impl<T>::const_value_type
  get() const CPP_NOEXCEPT
  { return this->do_get(); }

  T & get() CPP_NOEXCEPT
  { return this->do_get(); }

  operator FALCON_IF_NOT_IN_IDE_PARSER(typename)
    aux_::bitflag_impl<T>::const_value_type () const
  { return this->do_get(); }

  unsigned long to_ulong() const
  { return this->do_to_ulong(); }

#if __cplusplus >= 201103L
  unsigned long long to_ullong() const
  { return this->do_to_ullong(); }
#endif
};

template<class T>
bitflag<T>
operator&(bitflag<T> x, const bitflag<T>& y) CPP_NOEXCEPT
{
  x &= y;
  return x;
}

template<class T>
bitflag<T>
operator|(bitflag<T> x, const bitflag<T>& y) CPP_NOEXCEPT
{
  x |= y;
  return x;
}

template <class T>
bitflag<T>
operator^(bitflag<T> x, const bitflag<T>& y) CPP_NOEXCEPT
{
  x ^= y;
  return x;
}

template<class T>
bitflag<T>
operator&(bitflag<T> x, const T& y) CPP_NOEXCEPT
{ return x & bitflag<T>(y); }

template<class T>
bitflag<T>
operator|(bitflag<T> x, const T& y) CPP_NOEXCEPT
{ return x | bitflag<T>(y); }

template <class T>
bitflag<T>
operator^(bitflag<T> x, const T& y) CPP_NOEXCEPT
{ return x ^ bitflag<T>(y); }


template<class T>
bitflag<T> &
operator+=(bitflag<T>& x, const bitflag<T>& y) CPP_NOEXCEPT
{
  x |= y;
  return x;
}

template<class T>
bitflag<T> &
operator-=(bitflag<T>& x, bitflag<T> y) CPP_NOEXCEPT
{
  y.flip();
  x &= y;
  return x;
}

template <class T>
bitflag<T>
operator+(bitflag<T> x, const bitflag<T>& y) CPP_NOEXCEPT
{
  x += y;
  return x;
}

template <class T>
bitflag<T>
operator-(bitflag<T> x, bitflag<T> y) CPP_NOEXCEPT
{
  y.flip();
  x &= y;
  return x;
}


template<class T>
bitflag<T> &
operator+=(bitflag<T>& x, const T& y) CPP_NOEXCEPT
{ return x += bitflag<T>(y); }

template<class T>
bitflag<T> &
operator-=(bitflag<T>& x, const T& y) CPP_NOEXCEPT
{ return x -= bitflag<T>(y); }

template <class T>
bitflag<T>
operator+(bitflag<T> x, const T& y) CPP_NOEXCEPT
{ return x + bitflag<T>(y); }

template <class T>
bitflag<T>
operator-(bitflag<T> x, const T& y) CPP_NOEXCEPT
{ return x - bitflag<T>(y); }


// TODO bitflag_io.hpp and binary representation
template<class CharT, class Traits, class T>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> & os, bitflag<T> const & f)
{
  os.setf(std::ios_base::hex, std::ios_base::basefield);
  return os << f.get();
}

template<class CharT, class Traits, class T>
std::basic_istream<CharT, Traits> &
operator>>(std::basic_istream<CharT, Traits> & is, bitflag<T> & f)
{
  is.setf(std::ios_base::hex, std::ios_base::basefield);
  return is << f.get();
}

}

#if __cplusplus >= 201103L
namespace std {
  template<class T>
  struct hash< ::falcon::bitflag<T>>
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
