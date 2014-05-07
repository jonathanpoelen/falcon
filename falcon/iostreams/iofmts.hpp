#ifndef FALCON_IOSTREAMS_IOFMTS_HPP
#define FALCON_IOSTREAMS_IOFMTS_HPP

#include <ostream>
#include <istream>

namespace falcon {
namespace iostreams {

namespace _aux {
  struct io_flags_saver
  {
    std::ios_base & io_;
    std::ios_base::fmtflags flags_;

    io_flags_saver(
      std::ios_base & io) noexcept
    : io_(io)
    , flags_(io.flags())
    {}

    io_flags_saver(
      std::ios_base & io
    , std::ios_base::fmtflags flags) noexcept
    : io_(io)
    , flags_(io.flags(flags))
    {}

    ~io_flags_saver() noexcept
    { io_.flags(flags_); }
  };

  template<class CharT, class Traits>
  struct io_fill_saver
  {
    std::basic_ios<CharT, Traits> & io_;
    CharT c_;

    io_fill_saver(
      std::basic_ios<CharT, Traits> & io
    , CharT c) noexcept
    : io_(io)
    , c_(io.fill(std::move(c)))
    {}

    ~io_fill_saver() noexcept
    { io_.fill(std::move(c_)); }
  };

  struct io_precision_saver
  {
    std::ios_base & io_;
    std::streamsize p_;

    io_precision_saver(
      std::ios_base & io
    , std::streamsize p) noexcept
    : io_(io)
    , p_(io.precision(p))
    {}

    ~io_precision_saver() noexcept
    { io_.precision(p_); }
  };

  template<class Tag, class T, class F = void>
  struct basic_ioflags
  {
    T x;

    constexpr std::ios_base::fmtflags
    flags() const noexcept
    { return F::value; }
  };

  template<class Tag, class T>
  struct basic_ioflags<Tag, T, void>
  {
    std::ios_base::fmtflags flags_;
    T x;

    std::ios_base::fmtflags
    flags() const noexcept
    { return flags_; }
  };


  template<std::ios_base::fmtflags F>
  using fmtflags_constant = std::integral_constant<std::ios_base::fmtflags, F>;


  struct flags_tag {};
  struct setf_tag {};
  struct unsetf_tag {};

  template<class T, class F = void>
  using ioflags = basic_ioflags<flags_tag, T, F>;

  template<class T, class F = void>
  using iosetf = basic_ioflags<setf_tag, T, F>;

  template<class T, class F = void>
  using iounsetf = basic_ioflags<unsetf_tag, T, F>;


  template<class T, class M = void, class F = void>
  struct iosetflags
  {
    T x;

    constexpr std::ios_base::fmtflags
    flags() const noexcept
    { return F::value; }

    constexpr std::ios_base::fmtflags
    mask() const noexcept
    { return M::value; }
  };

  template<class T, class M>
  struct iosetflags<T, M, void>
  {
    std::ios_base::fmtflags flags_;
    T x;

    std::ios_base::fmtflags
    flags() const noexcept
    { return flags_; }

    constexpr std::ios_base::fmtflags
    mask() const noexcept
    { return M::value; }
  };

  template<class T>
  struct iosetflags<T, void, void>
  {
    std::ios_base::fmtflags flags_;
    std::ios_base::fmtflags mask_;
    T x;

    std::ios_base::fmtflags
    flags() const noexcept
    { return flags_; }

    std::ios_base::fmtflags
    mask() const noexcept
    { return mask_; }
  };
}


constexpr struct ioflags_t {
  template<class T>
  _aux::ioflags<T>
  operator()(
    T && x
  , std::ios_base::fmtflags flags)
  const noexcept
  { return {flags, std::forward<T>(x)}; }
} ioflags;

constexpr struct iosetflags_t {
template<class T>
  _aux::iosetf<T>
  operator()(
    T && x
  , std::ios_base::fmtflags flags)
  const noexcept
  { return {flags, std::forward<T>(x)}; }

  template<class T>
  _aux::iosetflags<T>
  operator()(
    T && x
  , std::ios_base::fmtflags flags
  , std::ios_base::fmtflags mask)
  const noexcept
  { return {flags, mask, std::forward<T>(x)}; }
} iosetflags;

constexpr struct iounsetflags_t {
  template<class T>
  _aux::iounsetf<T>
  operator()(
    T && x
  , std::ios_base::fmtflags flags)
  const noexcept
  { return {flags, std::forward<T>(x)}; }
} iounsetflags;


template<class CharT, class Traits, class T, class F>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> & os, _aux::ioflags<T, F> && x)
{
  _aux::io_flags_saver saver(os, x.flags());
  return os << x.x;
}

template<class CharT, class Traits, class T, class F>
std::basic_istream<CharT, Traits> &
operator>>(std::basic_istream<CharT, Traits> & is, _aux::ioflags<T, F> && x)
{
  _aux::io_flags_saver saver(is, x.flags());
  return is >> x.x;
}


template<class CharT, class Traits, class T, class F>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> & os, _aux::iosetf<T, F> && x)
{
  _aux::io_flags_saver saver(os);
  os.setf(x.flags());
  return os << x.x;
}

template<class CharT, class Traits, class T, class F>
std::basic_istream<CharT, Traits> &
operator>>(std::basic_istream<CharT, Traits> & is, _aux::iosetf<T, F> && x)
{
  _aux::io_flags_saver saver(is);
  is.setf(x.flags());
  return is >> x.x;
}


template<class CharT, class Traits, class T, class F>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> & os, _aux::iounsetf<T, F> && x)
{
  _aux::io_flags_saver saver(os);
  os.unsetf(x.flags());
  return os << x.x;
}

template<class CharT, class Traits, class T, class F>
std::basic_istream<CharT, Traits> &
operator>>(std::basic_istream<CharT, Traits> & is, _aux::iounsetf<T, F> && x)
{
  _aux::io_flags_saver saver(is);
  is.unsetf(x.flags());
  return is >> x.x;
}


template<class CharT, class Traits, class T, class M, class F>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> & os, _aux::iosetflags<T, M, F> && x)
{
  _aux::io_flags_saver saver(os, x.flags());
  os.setf(x.flags(), x.mask());
  return os << x.x;
}

template<class CharT, class Traits, class T, class M, class F>
std::basic_istream<CharT, Traits> &
operator>>(std::basic_istream<CharT, Traits> & is, _aux::iosetflags<T, M, F> && x)
{
  _aux::io_flags_saver saver(is, x.flags());
  is.setf(x.flags(), x.mask());
  return is >> x.x;
}


#define FALCON_IOFMT(name, mask)                    \
  constexpr struct io##name##_t {                   \
    template<class T>                               \
    _aux::iosetflags<                               \
      T                                             \
    , _aux::fmtflags_constant<mask>                 \
    , _aux::fmtflags_constant<std::ios_base::name>> \
    operator()(T && x) const noexcept               \
    { return {std::forward<T>(x)}; }                \
  } io##name;

FALCON_IOFMT(dec, std::ios_base::basefield)
FALCON_IOFMT(oct, std::ios_base::basefield)
FALCON_IOFMT(hex, std::ios_base::basefield)

FALCON_IOFMT(left, std::ios_base::adjustfield)
FALCON_IOFMT(right, std::ios_base::adjustfield)
FALCON_IOFMT(internal, std::ios_base::adjustfield)

FALCON_IOFMT(scientific, std::ios_base::floatfield)

FALCON_IOFMT(fixed, std::ios_base::floatfield)

# undef FALCON_IOFMT

#define FALCON_IOFMT(name)                                          \
  constexpr struct io##name##_t {                                   \
    template<class T>                                               \
    _aux::iosetf<T, _aux::fmtflags_constant<std::ios_base::name>>   \
    operator()(T && x) const noexcept                               \
    { return {std::forward<T>(x)}; }                                \
  } io##name;                                                       \
                                                                    \
  constexpr struct iono##name##_t {                                 \
    template<class T>                                               \
    _aux::iounsetf<T, _aux::fmtflags_constant<std::ios_base::name>> \
    operator()(T && x) const noexcept                               \
    { return {std::forward<T>(x)}; }                                \
  } iono##name;

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

constexpr struct  iosetbase_t {
  template<class T>
  _aux::iosetflags<T, _aux::fmtflags_constant<std::ios_base::basefield>>
  operator()(int base, T && x) const noexcept
  {
    return {base ==  8 ? std::ios_base::oct :
    base == 10 ? std::ios_base::dec :
    base == 16 ? std::ios_base::hex :
    std::ios_base::fmtflags(0), std::forward<T>(x)};
  }
} iosetbase;


namespace _aux {
  template<class CharT, class T>
  struct iosetfill
  { CharT c ; T x; };

  template<class T>
  struct iosetprecision
  { std::streamsize n ; T x; };

  template<class T>
  struct iosetwidth
  { std::streamsize n ; T x; };

  template<class T>
  struct iows
  { T x; };
}


constexpr struct iosetfill_t {
  template<class CharT, class T>
  _aux::iosetfill<CharT, T>
  operator()(
    T && x
  , CharT c)
  const noexcept
  { return {c, std::forward<T>(x)}; }
} iosetfill;

constexpr struct iosetprecision_t {
  template<class CharT, class T>
  _aux::iosetprecision<T>
  operator()(
    T && x
  , std::streamsize n)
  const noexcept
  { return {n, std::forward<T>(x)}; }
} iosetprecision;

constexpr struct iosetw_t {
  template<class T>
  _aux::iosetwidth<T>
  operator()(
    T && x
  , std::streamsize n)
  const noexcept
  { return {n, std::forward<T>(x)}; }
} iosetw;

constexpr struct iows_t {
  template<class T>
  _aux::iows<T>
  operator()(T && x)
  const noexcept
  { return {std::forward<T>(x)}; }
} iows;


template<class CharT, class Traits, typename CharT2, class T>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> & os, _aux::iosetfill<CharT2, T> && x)
{
  _aux::io_fill_saver<CharT, Traits> saver(os, x.c);
  return os << x.x;
}

template<class CharT, class Traits, typename CharT2, class T>
std::basic_istream<CharT, Traits> &
operator>>(std::basic_istream<CharT, Traits> & is, _aux::iosetfill<CharT2, T> && x)
{
  _aux::io_fill_saver<CharT, Traits> saver(is, x.c);
  return is >> x.x;
}


template<class CharT, class Traits, class T>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> & os, _aux::iosetprecision<T> && x)
{
  _aux::io_precision_saver saver(os, x.n);
  return os << x.x;
}

template<class CharT, class Traits, class T>
std::basic_istream<CharT, Traits> &
operator>>(std::basic_istream<CharT, Traits> & is, _aux::iosetprecision<T> && x)
{
  _aux::io_precision_saver saver(is, x.n);
  return is >> x.x;
}


template<class CharT, class Traits, class T>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> & os, _aux::iosetwidth<T> && x)
{
  os.width(x.n);
  return os << x.x;
}

template<class CharT, class Traits, class T>
std::basic_istream<CharT, Traits> &
operator>>(std::basic_istream<CharT, Traits> & is, _aux::iosetwidth<T> && x)
{
  is.width(x.n);
  return is >> x.x;
}


template<class CharT, class Traits, class T>
std::basic_istream<CharT, Traits> &
operator>>(std::basic_istream<CharT, Traits> & is, _aux::iows<T> && x)
{ return is >> std::ws >> x.x; }


template<std::ios_base::fmtflags F>
struct iofmt
{
  template<class T>
  _aux::ioflags<T, _aux::fmtflags_constant<F>> operator()(T && x) const  noexcept
  { return {std::forward<T>(x)}; }

  template<class T>
  _aux::ioflags<T> operator()(std::ios_base::fmtflags flags, T && x) const  noexcept
  { return {F|flags, std::forward<T>(x)}; }
};


template<std::ios_base::fmtflags F
, std::ios_base::fmtflags M = std::ios_base::fmtflags(0)>
struct iosetfmt
{
  template<class T>
  _aux::iosetflags<T, _aux::fmtflags_constant<M>, _aux::fmtflags_constant<F>>
  operator()(T && x) const  noexcept
  { return {std::forward<T>(x)}; }

  template<class T>
  _aux::iosetflags<T, _aux::fmtflags_constant<M>>
  operator()(T && x, std::ios_base::fmtflags flags) const  noexcept
  { return {F|flags, std::forward<T>(x)}; }

  template<class T>
  _aux::iosetflags<T>
  operator()(
    T && x
  , std::ios_base::fmtflags mask
  , std::ios_base::fmtflags flags) const  noexcept
  { return {F|flags, M|mask, std::forward<T>(x)}; }
};


template<std::ios_base::fmtflags F>
struct iounsetfmt
{
  template<class T>
  _aux::iounsetf<T, _aux::fmtflags_constant<F>> operator()(T && x) const  noexcept
  { return {std::forward<T>(x)}; }

  template<class T>
  _aux::iounsetf<T> operator()(T && x, std::ios_base::fmtflags flags) const  noexcept
  { return {F|flags, std::forward<T>(x)}; }
};


namespace iofmts {
  constexpr ::falcon::iostreams::ioflags_t flags;
  constexpr ::falcon::iostreams::iosetflags_t setflags;
  constexpr ::falcon::iostreams::iounsetflags_t unsetflags;

  constexpr ::falcon::iostreams::iodec_t dec;
  constexpr ::falcon::iostreams::iooct_t oct;
  constexpr ::falcon::iostreams::iohex_t hex;
  constexpr ::falcon::iostreams::ioleft_t left;
  constexpr ::falcon::iostreams::ioright_t right;
  constexpr ::falcon::iostreams::iointernal_t internal;
  constexpr ::falcon::iostreams::ioscientific_t scientific;
  constexpr ::falcon::iostreams::iofixed_t fixed;
  constexpr ::falcon::iostreams::iosetbase_t setbase;
  constexpr ::falcon::iostreams::iosetfill_t setfill;
  constexpr ::falcon::iostreams::iosetprecision_t setprecision;
  constexpr ::falcon::iostreams::iosetw_t setw;
  constexpr ::falcon::iostreams::iows_t ws;

  constexpr ::falcon::iostreams::iobasefield_t basefield;
  constexpr ::falcon::iostreams::ioadjustfield_t adjustfield;
  constexpr ::falcon::iostreams::iofloatfield_t floatfield;
  constexpr ::falcon::iostreams::ioboolalpha_t boolalpha;
  constexpr ::falcon::iostreams::ioshowbase_t showbase;
  constexpr ::falcon::iostreams::ioshowpoint_t showpoint;
  constexpr ::falcon::iostreams::ioshowpos_t showpos;
  constexpr ::falcon::iostreams::ioskipws_t skipws;
  constexpr ::falcon::iostreams::iounitbuf_t unitbuf;
  constexpr ::falcon::iostreams::iouppercase_t uppercase;

  constexpr ::falcon::iostreams::ionobasefield_t nobasefield;
  constexpr ::falcon::iostreams::ionoadjustfield_t noadjustfield;
  constexpr ::falcon::iostreams::ionofloatfield_t nofloatfield;
  constexpr ::falcon::iostreams::ionoboolalpha_t noboolalpha;
  constexpr ::falcon::iostreams::ionoshowbase_t noshowbase;
  constexpr ::falcon::iostreams::ionoshowpoint_t noshowpoint;
  constexpr ::falcon::iostreams::ionoshowpos_t noshowpos;
  constexpr ::falcon::iostreams::ionoskipws_t noskipws;
  constexpr ::falcon::iostreams::ionounitbuf_t nounitbuf;
  constexpr ::falcon::iostreams::ionouppercase_t nouppercase;

  template<std::ios_base::fmtflags F>
  using iofmt = ::falcon::iostreams::iofmt<F>;

  template<std::ios_base::fmtflags F
  , std::ios_base::fmtflags M = std::ios_base::fmtflags(0)>
  using iosetfmt = ::falcon::iostreams::iosetfmt<F, M>;

  template<std::ios_base::fmtflags F>
  using iounsetfmt = ::falcon::iostreams::iounsetfmt<F>;
}

}
}

#endif
