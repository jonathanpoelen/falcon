#ifndef FALCON_IOSTREAMS_IOFLAGS_HPP
#define FALCON_IOSTREAMS_IOFLAGS_HPP

#include <ostream>
#include <istream>

namespace falcon {

template<std::ios_base::fmtflags F, typename T>
struct __ioflags
{ T && x; };

template<typename T>
struct __ioflags2
{ std::ios_base::fmtflags flags; T && x; };

template<typename T>
__ioflags2<T> ioflags(std::ios_base::fmtflags flags, T && x)
{ return {flags, std::forward<T>(x)}; }

template <typename CharT, typename Traits, std::ios_base::fmtflags F, typename T>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> & os, __ioflags<F, T> x)
{
  std::ios_base::fmtflags flags = os.flags(F);
  os << x.x;
  os.flags(flags);
  return os;
}

template <typename CharT, typename Traits, std::ios_base::fmtflags F, typename T>
std::basic_istream<CharT, Traits> &
operator>>(std::basic_istream<CharT, Traits> & is, __ioflags<F, T> x)
{
  std::ios_base::fmtflags flags = is.flags(F);
  is >> x.x;
  is.flags(flags);
  return is;
}

template <typename CharT, typename Traits, typename T>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> & os, __ioflags2<T> x)
{
  std::ios_base::fmtflags flags = os.flags(x.flags);
  os << x.x;
  os.flags(flags);
  return os;
}

template <typename CharT, typename Traits, typename T>
std::basic_istream<CharT, Traits> &
operator>>(std::basic_istream<CharT, Traits> & is, __ioflags2<T> x)
{
  std::ios_base::fmtflags flags = is.flags(x.flags);
  is >> x.x;
  is.flags(flags);
  return is;
}


template<std::ios_base::fmtflags F, typename T>
struct __iounsetflags
{ T && x; };

template<typename T>
struct __iounsetflags2
{ std::ios_base::fmtflags flags; T && x; };

template<typename T>
__iounsetflags2<T> iounsetflags(std::ios_base::fmtflags flags, T && x)
{ return {flags, std::forward<T>(x)}; }

template <typename CharT, typename Traits, std::ios_base::fmtflags F, typename T>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> & os, __iounsetflags<F, T> x)
{
  std::ios_base::fmtflags flags = os.flags(F);
  os << x.x;
  os.flags(flags);
  return os;
}

template <typename CharT, typename Traits, std::ios_base::fmtflags F, typename T>
std::basic_istream<CharT, Traits> &
operator>>(std::basic_istream<CharT, Traits> & is, __iounsetflags<F, T> x)
{
  std::ios_base::fmtflags flags = is.flags(F);
  is >> x.x;
  is.flags(flags);
  return is;
}

template <typename CharT, typename Traits, typename T>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> & os, __iounsetflags2<T> x)
{
  std::ios_base::fmtflags flags = os.flags(x.flags);
  os << x.x;
  os.flags(flags);
  return os;
}

template <typename CharT, typename Traits, typename T>
std::basic_istream<CharT, Traits> &
operator>>(std::basic_istream<CharT, Traits> & is, __iounsetflags2<T> x)
{
  std::ios_base::fmtflags flags = is.flags(x.flags);
  is >> x.x;
  is.flags(flags);
  return is;
}


template<std::ios_base::fmtflags F, std::ios_base::fmtflags M, typename T>
struct __iosetflags
{ T && x; };

template<std::ios_base::fmtflags M, typename T>
struct __iosetflags2
{ std::ios_base::fmtflags flags; T && x; };

template<typename T>
struct __iosetflags3
{ std::ios_base::fmtflags flags; std::ios_base::fmtflags mask; T && x; };

template<typename T>
__iosetflags3<T>
iosetflags(std::ios_base::fmtflags flags, std::ios_base::fmtflags mask, T && x)
{ return {flags, mask, std::forward<T>(x)}; }

template <typename CharT, typename Traits, std::ios_base::fmtflags F, std::ios_base::fmtflags M, typename T>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> & os, __iosetflags<F, M, T> x)
{
  std::ios_base::fmtflags flags = os.setf(F, M);
  os << x.x;
  os.flags(flags);
  return os;
}

template <typename CharT, typename Traits, std::ios_base::fmtflags F, std::ios_base::fmtflags M, typename T>
std::basic_istream<CharT, Traits> &
operator>>(std::basic_istream<CharT, Traits> & is, __iosetflags<F, M, T> x)
{
  std::ios_base::fmtflags flags = is.setf(F, M);
  is >> x.x;
  is.flags(flags);
  return is;
}

template <typename CharT, typename Traits, std::ios_base::fmtflags M, typename T>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> & os, __iosetflags2<M, T> x)
{
  std::ios_base::fmtflags flags = os.setf(x.flags, M);
  os << x.x;
  os.flags(flags);
  return os;
}

template <typename CharT, typename Traits, std::ios_base::fmtflags M, typename T>
std::basic_istream<CharT, Traits> &
operator>>(std::basic_istream<CharT, Traits> & is, __iosetflags2<M, T> x)
{
  std::ios_base::fmtflags flags = is.setf(x.flags, M);
  is >> x.x;
  is.flags(flags);
  return is;
}

template <typename CharT, typename Traits, typename T>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> & os, __iosetflags3<T> x)
{
  std::ios_base::fmtflags flags = os.setf(x.flags, x.mask);
  os << x.x;
  os.flags(flags);
  return os;
}

template <typename CharT, typename Traits, typename T>
std::basic_istream<CharT, Traits> &
operator>>(std::basic_istream<CharT, Traits> & is, __iosetflags3<T> x)
{
  std::ios_base::fmtflags flags = is.setf(x.flags, x.mask);
  is >> x.x;
  is.flags(flags);
  return is;
}


template<std::ios_base::fmtflags F, typename T>
struct __iostrictsetflags
{ T && x; };

template<typename T>
struct __iostrictsetflags2
{ std::ios_base::fmtflags flags; T && x; };

template<typename T>
__iostrictsetflags2<T> iosetflags(std::ios_base::fmtflags flags, T && x)
{ return {flags, std::forward<T>(x)}; }

template <typename CharT, typename Traits, std::ios_base::fmtflags F, typename T>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> & os, __iostrictsetflags<F, T> x)
{
  std::ios_base::fmtflags flags = os.setf(F);
  os << x.x;
  os.flags(flags);
  return os;
}

template <typename CharT, typename Traits, std::ios_base::fmtflags F, typename T>
std::basic_istream<CharT, Traits> &
operator>>(std::basic_istream<CharT, Traits> & is, __iostrictsetflags<F, T> x)
{
  std::ios_base::fmtflags flags = is.setf(F);
  is >> x.x;
  is.flags(flags);
  return is;
}

template <typename CharT, typename Traits, typename T>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> & os, __iostrictsetflags2<T> x)
{
  std::ios_base::fmtflags flags = os.setf(x.flags);
  os << x.x;
  os.flags(flags);
  return os;
}

template <typename CharT, typename Traits, typename T>
std::basic_istream<CharT, Traits> &
operator>>(std::basic_istream<CharT, Traits> & is, __iostrictsetflags2<T> x)
{
  std::ios_base::fmtflags flags = is.setf(x.flags);
  is >> x.x;
  is.flags(flags);
  return is;
}


#define FALCON_IOFMT(name, mask)                               \
  template<typename T>                                         \
  __iosetflags<std::ios_base::name, mask, T> io##name (T && x) \
  { return {std::forward<T>(x)}; }

FALCON_IOFMT(dec, std::ios_base::basefield)
FALCON_IOFMT(oct, std::ios_base::basefield)
FALCON_IOFMT(hex, std::ios_base::basefield)

FALCON_IOFMT(left, std::ios_base::adjustfield)
FALCON_IOFMT(right, std::ios_base::adjustfield)
FALCON_IOFMT(internal, std::ios_base::adjustfield)

FALCON_IOFMT(scientific, std::ios_base::floatfield)

FALCON_IOFMT(fixed, std::ios_base::floatfield)

# undef FALCON_IOFMT

#define FALCON_IOFMT(name)                                     \
  template<typename T>                                         \
  __iostrictsetflags<std::ios_base::name, T> io##name (T && x) \
  { return {std::forward<T>(x)}; }                             \
                                                               \
  template<typename T>                                         \
  __iounsetflags<std::ios_base::name, T> iono##name (T && x)   \
  { return {std::forward<T>(x)}; }

FALCON_IOFMT(basefield)
FALCON_IOFMT(adjustfield)
FALCON_IOFMT(floatfield)

FALCON_IOFMT(boolalpha)

FALCON_IOFMT(showbase)
FALCON_IOFMT(showpoint)
FALCON_IOFMT(showpos)
FALCON_IOFMT(skipws)
FALCON_IOFMT(unitbuf)
FALCON_IOFMT(uppercase)

#undef FALCON_IOFMT

template<typename T>
__iosetflags2<std::ios_base::basefield, T> iosetbase(int base, T && x)
{
  return {base ==  8 ? std::ios_base::oct :
  base == 10 ? std::ios_base::dec :
  base == 16 ? std::ios_base::hex :
  std::ios_base::fmtflags(0), std::forward<T>(x)};
}


template<typename CharT, typename T>
struct __iosetfill
{ CharT c ; T && x; };

template<typename CharT, typename T>
__iosetfill<CharT, T> iosetfill(CharT c, T && x)
{ return {c, std::forward<T>(x)}; }

template <typename CharT, typename Traits, typename CharT2, typename T>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> & os, __iosetfill<CharT2, T> x)
{
  CharT c = os.fill(x.c);
  os << x.x;
  os.fill(c);
  return os;
}

template <typename CharT, typename Traits, typename CharT2, typename T>
std::basic_istream<CharT, Traits> &
operator>>(std::basic_istream<CharT, Traits> & is, __iosetfill<CharT2, T> x)
{
  CharT c = is.fill(x.c);
  is >> x.x;
  is.fill(c);
  return is;
}


template<typename T>
struct __iosetprecision
{ int n ; T && x; };

template<typename CharT, typename T>
__iosetprecision<T> iosetprecision(int n, T && x)
{ return {n, std::forward<T>(x)}; }

template <typename CharT, typename Traits, typename T>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> & os, __iosetprecision<T> x)
{
  int n = os.precision(x.n);
  os << x.x;
  os.precision(n);
  return os;
}

template <typename CharT, typename Traits, typename T>
std::basic_istream<CharT, Traits> &
operator>>(std::basic_istream<CharT, Traits> & is, __iosetprecision<T> x)
{
  int n = is.precision(x.n);
  is >> x.x;
  is.precision(n);
  return is;
}


template<typename T>
struct __iosetwidth
{ int n ; T && x; };

template<typename T>
__iosetwidth<T> iosetw(int n, T && x)
{ return {n, std::forward<T>(x)}; }

template <typename CharT, typename Traits, typename T>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> & os, __iosetwidth<T> x)
{
  os.width(x.n);
  return os << x.x;
}

template <typename CharT, typename Traits, typename T>
std::basic_istream<CharT, Traits> &
operator>>(std::basic_istream<CharT, Traits> & is, __iosetwidth<T> x)
{
  is.width(x.n);
  return is >> x.x;
}


template<typename T>
struct __iows
{ T && x; };

template<typename T>
__iows<T> iows(T && x)
{ return {std::forward<T>(x)}; }

template <typename CharT, typename Traits, typename T>
std::basic_istream<CharT, Traits> &
operator>>(std::basic_istream<CharT, Traits> & is, __iows<T> x)
{ return is >> std::ws >> x.x; }


template<std::ios_base::fmtflags F>
struct iofmt
{
  template<typename T>
  __ioflags<F, T> operator()(T && x) const
  { return {std::forward<T>(x)}; }

  template<typename T>
  __ioflags2<T> operator()(std::ios_base::fmtflags flags, T && x) const
  { return {F|flags, std::forward<T>(x)}; }
};


template<std::ios_base::fmtflags F>
struct iounsetfmt
{
  template<typename T>
  __iounsetflags<F, T> operator()(T && x) const
  { return {std::forward<T>(x)}; }

  template<typename T>
  __iounsetflags2<T> operator()(std::ios_base::fmtflags flags, T && x) const
  { return {F|flags, std::forward<T>(x)}; }
};


template<std::ios_base::fmtflags F, std::ios_base::fmtflags M = std::ios_base::fmtflags()>
struct iosetfmt
{
  template<typename T>
  __iosetflags<F, M, T> operator()(T && x) const
  { return {std::forward<T>(x)}; }

  template<typename T>
  __iosetflags2<M, T> operator()(std::ios_base::fmtflags flags, T && x) const
  { return {F|flags, std::forward<T>(x)}; }

  template<typename T>
  __iosetflags3<T>
  operator()(std::ios_base::fmtflags flags, std::ios_base::fmtflags mask, T && x) const
  { return {F|flags, M|mask, std::forward<T>(x)}; }
};


template<std::ios_base::fmtflags F>
struct iosetfmt<F, std::ios_base::fmtflags(0)>
{
  template<typename T>
  __iostrictsetflags<F, T> operator()(T && x) const
  { return {std::forward<T>(x)}; }

  template<typename T>
  __iostrictsetflags2<T> operator()(std::ios_base::fmtflags flags, T && x) const
  { return {F|flags, std::forward<T>(x)}; }

  template<typename T>
  __iosetflags3<T>
  operator()(std::ios_base::fmtflags flags, std::ios_base::fmtflags mask, T && x) const
  { return {F|flags, mask, std::forward<T>(x)}; }
};

}

#endif
