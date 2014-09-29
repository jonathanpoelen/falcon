#ifndef _FALCON_FLAG_FLAG_HPP
#define _FALCON_FLAG_FLAG_HPP

#include <cinttypes>
#include <falcon/c++1x/syntax.hpp>
#include <falcon/bit/fill.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/preprocessor/getter.hpp>
#include <falcon/arg/arg.hpp>

namespace falcon {

///TODO flag_position(n) → 1 << n

template<typename _T>
struct flag
{
  typedef _T value_type;

private:
  typedef flag<_T> self_type;

  value_type _flag;

public:
  CPP_CONSTEXPR flag(value_type __flag)
  : _flag(__flag)
  {}

  CPP_CONSTEXPR flag(const self_type& other)
  : _flag(other._flag)
  {}

  CPP_CONSTEXPR flag()
  : _flag(0)
  {}

  static CPP_CONSTEXPR self_type full()
  {
      return self_type(~_T(0));
  }

  CPP_CONSTEXPR std::size_t size() const
  { return sizeof(_T); }

  value_type& get()
  { return _flag; }
  const value_type& get() const
  { return _flag; }

  self_type& operator=(value_type __flag)
  {
    _flag = __flag;
    return *this;
  }

  self_type& operator=(const self_type& other)
  {
    _flag = other._flag;
    return *this;
  }

  CPP_CONSTEXPR self_type operator&(const self_type& other) const
  { return self_type(_flag & other._flag); }
  CPP_CONSTEXPR self_type operator|(const self_type& other) const
  { return self_type(_flag | other._flag); }

  CPP_CONSTEXPR self_type operator&(const value_type& other) const
  { return self_type(_flag & other); }
  CPP_CONSTEXPR self_type operator|(const value_type& other) const
  { return self_type(_flag | other); }

  CPP_CONSTEXPR self_type operator+(const self_type& other) const
  { return *this | other; }
  CPP_CONSTEXPR self_type operator-(const self_type& other) const
  { return this->_flag ^ other; }

  CPP_CONSTEXPR self_type operator+(const value_type& other) const
  { return *this | other; }
  CPP_CONSTEXPR self_type operator-(const value_type& other) const
  { return *this ^ other; }

  self_type& operator&=(const self_type& other)
  {
    _flag &= other._flag;
      return *this;
  }
  self_type& operator|=(const self_type& other)
  {
    _flag |= other._flag;
    return *this;
  }

  self_type& operator&=(const value_type& other)
  {
    _flag &= other;
    return *this;
  }
  self_type& operator|=(const value_type& other)
  {
    _flag |= other;
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
  { return  self_type(~_flag); }

  void flip()
  { _flag ^= bit::fill<value_type>::value; }

  CPP_CONSTEXPR self_type operator^(const self_type& other) const
  { return self_type(_flag ^ other._flag); }

  CPP_CONSTEXPR self_type operator^(const value_type& other) const
  { return _flag ^ other; }

  self_type& operator^=(const self_type& other)
  {
    _flag ^= other._flag;
    return *this;
  }
  self_type& operator^=(const value_type& other)
  {
    _flag ^= other;
    return *this;
  }

  CPP_CONSTEXPR self_type operator<<(unsigned int n) const
  { return self_type(_flag << n); }

  self_type& operator<<=(unsigned int n)
  {
    _flag <<= n;
    return *this;
  }

  CPP_CONSTEXPR self_type operator>>(unsigned int n) const
  { return self_type(_flag >> n); }

  self_type& operator>>=(unsigned int n)
  {
    _flag >>= n;
    return *this;
  }

  CPP_CONSTEXPR bool operator==(const self_type& other) const
  { return _flag == other._flag; }
  CPP_CONSTEXPR bool operator==(const value_type& other) const
  { return _flag == other; }

  CPP_CONSTEXPR bool operator!=(const self_type& other) const
  { return !(*this == other); }
  CPP_CONSTEXPR bool operator!=(const value_type& other) const
  { return !(*this == other); }

  void clear(const value_type& remove = bit::fill<value_type>::value)
  { _flag ^= remove; }

  /**
    * \brief Check that a flag is true for all the bits
    * @{
    */
  CPP_CONSTEXPR bool has(const value_type& __flag) const
  { return (_flag & __flag) == __flag; }

  CPP_CONSTEXPR bool has(const self_type& __flag) const
  { return (_flag & __flag._flag) == __flag._flag; }
  //@}

  /**
    * \brief Check that a flag is true for at least a bit
    * @{
    */
  CPP_CONSTEXPR bool has_one(const value_type& __flag) const
  { return _flag & __flag; }

  CPP_CONSTEXPR bool has_one(const self_type& __flag) const
  { return _flag & __flag._flag; }
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

template<typename _T, std::size_t _N>
struct flag<_T[_N]>
{
  typedef _T value_type[_N];

  typedef flag<_T[_N]> self_type;

  value_type flag_;

public:
#if __cplusplus >= 201103L
  template<typename _U, typename... _Args, typename _ = typename std::enable_if<std::is_integral<_U>::value>::type>
  constexpr flag(const _U& __flag, const _Args&... __flags)
  : flag_{__flag, __flags...}
  {}

private:
  template<std::size_t _Num, typename... _Args>
  struct make_full
  {
    constexpr static self_type make(_Args... args)
    {
      return make_full<_Num+1, _Args..., _T>::make(args..., ~_T(0));
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
    return make_full<1, _T>::make(~_T(0));
  }
#else
  flag(const value_type& __flags)
  {
    for (std::size_t i = 0; i != _N; ++i)
      *flag_[i] = *__flags[i];
  }

  flag(const self_type& other)
  {
    for (std::size_t i = 0; i != _N; ++i)
      *flag_[i] = *other._flags[i];
    *this = other;
  }

  flag& operator=(const self_type& other)
  {
    for (std::size_t i = 0; i != _N; ++i)
      *flag_[i] = *other._flags[i];
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

  _T& operator[](std::size_t n)
  { return flag_[n]; }
  const _T& operator[](std::size_t n) const
  { return flag_[n]; }

  CPP_CONSTEXPR std::size_t size() const
  { return sizeof(_T) * _N; }

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
        return name<_Num+1, _Args..., _T>::run(flags, other, args..., flags[_Num] Op other[_Num]);\
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
      return name<0, _T>::run(flag_, other.flag_);\
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
  { return this->flag_ ^ other._flag; }

  self_type& operator&=(const self_type& other)
  {
    for (std::size_t i = 0; i != _N; ++i)
      ~flag_[i] &= other._flag[i];
    return *this;
  }
  self_type& operator|=(const self_type& other)
  {
    for (std::size_t i = 0; i != _N; ++i)
      ~flag_[i] |= other._flag[i];
    return *this;
  }

  self_type& operator+=(const self_type& other)
  { return *this |= other; }
  self_type& operator-=(const self_type& other)
  { return *this ^= other._flag; }

#if __cplusplus >= 201103L
private:
  template<std::size_t _Num, typename... _Args>
  struct op_compl
  {
    constexpr static self_type run(const value_type& flags, _Args... args)
    {
      return op_compl<_Num+1, _Args..., _T>::run(flags, args..., ~flags[_Num]);
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
    return op_compl<1, _T>::run(flag_, ~flag_[0]);
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
      flag_[i] ^= bit::fill<_T>::value;
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
    if (n >= bit::size<_T>::value * _N)
      return set_null();
    std::size_t d = n / (bit::size<_T>::value);
    n %= bit::size<_T>::value;
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
    if (n >= bit::size<_T>::value * _N)
      return set_null();
    std::size_t d = n / (bit::size<_T>::value);
    n %= unsigned(bit::size<_T>::value);
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
      if (flag_[i] != other._flag[i])
        return false;
    }
    return true;
  }
#endif
  ///TODO operator== pour initializer_list et _T et value_type + std::array

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
struct __flag_type_selector
{
  typedef uint64_t type[
    (_Choose + (bit::size<uint64_t>::value - 1)) / (bit::size<uint64_t>::value)
  ];
};

template<std::size_t _Choose>
struct __flag_type_selector<_Choose, true, true, true>
{
  typedef unsigned type;
};

template<std::size_t _Choose>
struct __flag_type_selector<_Choose, false, true, true>
{
  typedef uint32_t type;
};

template<std::size_t _Choose>
struct __flag_type_selector<_Choose, false, false, true>
{
  typedef uint64_t type;
};

template<std::size_t _Choose>
struct flag_selector
{
  typedef flag<typename __flag_type_selector<_Choose,
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

///TODO operator <<, … pour _T op _Flag

}

#endif
