#ifndef FALCON_IOSTREAMS_IOFMTS_HPP
#define FALCON_IOSTREAMS_IOFMTS_HPP

#include <falcon/type_traits/static_const.hpp>

#include <ios>
#include <istream>

namespace falcon {
namespace iostreams {

#define FALCON_IOSTREAMS_GLOBAL_OBJECT_(name, type) \
  } FALCON_GLOBAL_OBJECT(name, iostreams::type); namespace iostreams {

namespace aux_ {
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

  template<class CharT, class Traits, class T, class F>
  std::basic_ostream<CharT, Traits> &
  operator<<(std::basic_ostream<CharT, Traits> & os, ioflags<T, F> && x)
  {
    io_flags_saver saver(os, x.flags());
    return os << x.x;
  }

  template<class CharT, class Traits, class T, class F>
  std::basic_istream<CharT, Traits> &
  operator>>(std::basic_istream<CharT, Traits> & is, ioflags<T, F> && x)
  {
    io_flags_saver saver(is, x.flags());
    return is >> std::forward<T>(x.x);
  }


  template<class CharT, class Traits, class T, class F>
  std::basic_ostream<CharT, Traits> &
  operator<<(std::basic_ostream<CharT, Traits> & os, iosetf<T, F> && x)
  {
    io_flags_saver saver(os);
    os.setf(x.flags());
    return os << x.x;
  }

  template<class CharT, class Traits, class T, class F>
  std::basic_istream<CharT, Traits> &
  operator>>(std::basic_istream<CharT, Traits> & is, iosetf<T, F> && x)
  {
    io_flags_saver saver(is);
    is.setf(x.flags());
    return is >> std::forward<T>(x.x);
  }


  template<class CharT, class Traits, class T, class F>
  std::basic_ostream<CharT, Traits> &
  operator<<(std::basic_ostream<CharT, Traits> & os, iounsetf<T, F> && x)
  {
    io_flags_saver saver(os);
    os.unsetf(x.flags());
    return os << x.x;
  }

  template<class CharT, class Traits, class T, class F>
  std::basic_istream<CharT, Traits> &
  operator>>(std::basic_istream<CharT, Traits> & is, iounsetf<T, F> && x)
  {
    io_flags_saver saver(is);
    is.unsetf(x.flags());
    return is >> std::forward<T>(x.x);
  }


  template<class CharT, class Traits, class T, class M, class F>
  std::basic_ostream<CharT, Traits> &
  operator<<(std::basic_ostream<CharT, Traits> & os, iosetflags<T, M, F> && x)
  {
    io_flags_saver saver(os, x.flags());
    os.setf(x.flags(), x.mask());
    return os << x.x;
  }

  template<class CharT, class Traits, class T, class M, class F>
  std::basic_istream<CharT, Traits> &
  operator>>(std::basic_istream<CharT, Traits> & is, iosetflags<T, M, F> && x)
  {
    io_flags_saver saver(is, x.flags());
    is.setf(x.flags(), x.mask());
    return is >> std::forward<T>(x.x);
  }
}


struct ioflags_fn {
  constexpr ioflags_fn() noexcept {}

  template<class T>
  aux_::ioflags<T&&>
  operator()(T && x, std::ios_base::fmtflags flags) const noexcept
  { return {flags, std::forward<T>(x)}; }
};
FALCON_IOSTREAMS_GLOBAL_OBJECT_(ioflags, ioflags_fn);

struct iosetflags_fn {
  constexpr iosetflags_fn() noexcept {}

  template<class T>
  aux_::iosetf<T&&>
  operator()(T && x, std::ios_base::fmtflags flags) const noexcept
  { return {flags, std::forward<T>(x)}; }

  template<class T>
  aux_::iosetflags<T&&>
  operator()(
    T && x
  , std::ios_base::fmtflags flags
  , std::ios_base::fmtflags mask)
  const noexcept
  { return {flags, mask, std::forward<T>(x)}; }
};
FALCON_IOSTREAMS_GLOBAL_OBJECT_(iosetflags, iosetflags_fn);

struct iounsetflags_fn {
  constexpr iounsetflags_fn() noexcept {}

  template<class T>
  aux_::iounsetf<T&&>
  operator()(T && x, std::ios_base::fmtflags flags) const noexcept
  { return {flags, std::forward<T>(x)}; }
};
FALCON_IOSTREAMS_GLOBAL_OBJECT_(iounsetflags, iounsetflags_fn);

#define FALCON_IOFMT(name, mask)                    \
  struct io##name##_fn {                            \
    constexpr io##name##_fn() noexcept {}           \
    template<class T>                               \
    aux_::iosetflags<                               \
      T &&                                          \
    , aux_::fmtflags_constant<mask>                 \
    , aux_::fmtflags_constant<std::ios_base::name>> \
    operator()(T && x) const noexcept               \
    { return {std::forward<T>(x)}; }                \
  };                                                \
  FALCON_IOSTREAMS_GLOBAL_OBJECT_(io##name, io##name##_fn);

FALCON_IOFMT(dec, std::ios_base::basefield)
FALCON_IOFMT(oct, std::ios_base::basefield)
FALCON_IOFMT(hex, std::ios_base::basefield)

FALCON_IOFMT(left, std::ios_base::adjustfield)
FALCON_IOFMT(right, std::ios_base::adjustfield)
FALCON_IOFMT(internal, std::ios_base::adjustfield)

FALCON_IOFMT(scientific, std::ios_base::floatfield)

FALCON_IOFMT(fixed, std::ios_base::floatfield)

# undef FALCON_IOFMT

#define FALCON_IOFMT(name)                                            \
  struct io##name##_fn {                                              \
    constexpr io##name##_fn() noexcept {}                             \
    template<class T>                                                 \
    aux_::iosetf<T&&, aux_::fmtflags_constant<std::ios_base::name>>   \
    operator()(T && x) const noexcept                                 \
    { return {std::forward<T>(x)}; }                                  \
  };                                                                  \
  FALCON_IOSTREAMS_GLOBAL_OBJECT_(io##name, io##name##_fn);           \
                                                                      \
  struct iono##name##_fn {                                            \
    constexpr iono##name##_fn() noexcept {}                           \
    template<class T>                                                 \
    aux_::iounsetf<T&&, aux_::fmtflags_constant<std::ios_base::name>> \
    operator()(T && x) const noexcept                                 \
    { return {std::forward<T>(x)}; }                                  \
  };                                                                  \
  FALCON_IOSTREAMS_GLOBAL_OBJECT_(iono##name, iono##name##_fn);       \

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

struct iosetbase_fn {
  constexpr iosetbase_fn() noexcept {}

  template<class T>
  aux_::iosetflags<T&&, aux_::fmtflags_constant<std::ios_base::basefield>>
  operator()(int base, T && x) const noexcept
  {
    return {base ==  8 ? std::ios_base::oct :
    base == 10 ? std::ios_base::dec :
    base == 16 ? std::ios_base::hex :
    std::ios_base::fmtflags(0), std::forward<T>(x)};
  }
};
FALCON_IOSTREAMS_GLOBAL_OBJECT_(iosetbase, iosetbase_fn);


namespace aux_ {
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


  template<class CharT, class Traits, typename CharT2, class T>
  std::basic_ostream<CharT, Traits> &
  operator<<(std::basic_ostream<CharT, Traits> & os, iosetfill<CharT2, T> && x)
  {
    aux_::io_fill_saver<CharT, Traits> saver(os, x.c);
    return os << x.x;
  }

  template<class CharT, class Traits, typename CharT2, class T>
  std::basic_istream<CharT, Traits> &
  operator>>(std::basic_istream<CharT, Traits> & is, iosetfill<CharT2, T> && x)
  {
    aux_::io_fill_saver<CharT, Traits> saver(is, x.c);
    return is >> std::forward<T>(x.x);
  }

  template<class CharT, class Traits, class T>
  std::basic_ostream<CharT, Traits> &
  operator<<(std::basic_ostream<CharT, Traits> & os, iosetprecision<T> && x)
  {
    io_precision_saver saver(os, x.n);
    return os << x.x;
  }

  template<class CharT, class Traits, class T>
  std::basic_istream<CharT, Traits> &
  operator>>(std::basic_istream<CharT, Traits> & is, iosetprecision<T> && x)
  {
    io_precision_saver saver(is, x.n);
    return is >> std::forward<T>(x.x);
  }


  template<class CharT, class Traits, class T>
  std::basic_ostream<CharT, Traits> &
  operator<<(std::basic_ostream<CharT, Traits> & os, iosetwidth<T> && x)
  {
    os.width(x.n);
    return os << x.x;
  }

  template<class CharT, class Traits, class T>
  std::basic_istream<CharT, Traits> &
  operator>>(std::basic_istream<CharT, Traits> & is, iosetwidth<T> && x)
  {
    is.width(x.n);
    return is >> std::forward<T>(x.x);
  }


  template<class CharT, class Traits, class T>
  std::basic_istream<CharT, Traits> &
  operator>>(std::basic_istream<CharT, Traits> & is, iows<T> && x)
  { return is >> std::ws >> std::forward<T>(x.x); }
}


struct iosetfill_fn {
  constexpr iosetfill_fn() noexcept {}

  template<class CharT, class T>
  aux_::iosetfill<CharT, T&&>
  operator()(T && x, CharT c) const noexcept
  { return {c, std::forward<T>(x)}; }
};
FALCON_IOSTREAMS_GLOBAL_OBJECT_(iosetfill, iosetfill_fn);

struct iosetprecision_fn {
  constexpr iosetprecision_fn() noexcept {}

  template<class CharT, class T>
  aux_::iosetprecision<T&&>
  operator()(T && x, std::streamsize n) const noexcept
  { return {n, std::forward<T>(x)}; }
};
FALCON_IOSTREAMS_GLOBAL_OBJECT_(iosetprecision, iosetprecision_fn);

struct iosetw_fn {
  constexpr iosetw_fn() noexcept {}

  template<class T>
  aux_::iosetwidth<T&&>
  operator()(T && x, std::streamsize n) const noexcept
  { return {n, std::forward<T>(x)}; }
};
FALCON_IOSTREAMS_GLOBAL_OBJECT_(iosetw, iosetw_fn);

struct iows_fn {
  constexpr iows_fn() noexcept {}

  template<class T>
  aux_::iows<T&&>
  operator()(T && x) const noexcept
  { return {std::forward<T>(x)}; }
};
FALCON_IOSTREAMS_GLOBAL_OBJECT_(iows, iows_fn);


template<std::ios_base::fmtflags F>
struct iofmt
{
  template<class T>
  aux_::ioflags<T&&, aux_::fmtflags_constant<F>>
  operator()(T && x) const noexcept
  { return {std::forward<T>(x)}; }

  template<class T>
  aux_::ioflags<T&&>
  operator()(std::ios_base::fmtflags flags, T && x) const noexcept
  { return {F|flags, std::forward<T>(x)}; }
};


template<
  std::ios_base::fmtflags F
, std::ios_base::fmtflags M = std::ios_base::fmtflags(0)>
struct iosetfmt
{
  template<class T>
  aux_::iosetflags<T&&, aux_::fmtflags_constant<M>, aux_::fmtflags_constant<F>>
  operator()(T && x) const noexcept
  { return {std::forward<T>(x)}; }

  template<class T>
  aux_::iosetflags<T&&, aux_::fmtflags_constant<M>>
  operator()(T && x, std::ios_base::fmtflags flags) const noexcept
  { return {F|flags, std::forward<T>(x)}; }

  template<class T>
  aux_::iosetflags<T&&>
  operator()(
    T && x
  , std::ios_base::fmtflags mask
  , std::ios_base::fmtflags flags) const noexcept
  { return {F|flags, M|mask, std::forward<T>(x)}; }
};


template<std::ios_base::fmtflags F>
struct iounsetfmt
{
  template<class T>
  aux_::iounsetf<T&&, aux_::fmtflags_constant<F>>
  operator()(T && x) const noexcept
  { return {std::forward<T>(x)}; }

  template<class T>
  aux_::iounsetf<T&&>
  operator()(T && x, std::ios_base::fmtflags flags) const noexcept
  { return {F|flags, std::forward<T>(x)}; }
};

#undef FALCON_IOSTREAMS_GLOBAL_OBJECT_

namespace iofmts {
  constexpr auto const & flags = ioflags;
  constexpr auto const & setflags = iosetflags;
  constexpr auto const & unsetflags = iounsetflags;

  constexpr auto const & dec = iodec;
  constexpr auto const & oct = iooct;
  constexpr auto const & hex = iohex;
  constexpr auto const & left = ioleft;
  constexpr auto const & right = ioright;
  constexpr auto const & internal = iointernal;
  constexpr auto const & scientific = ioscientific;
  constexpr auto const & fixed = iofixed;
  constexpr auto const & setbase = iosetbase;
  constexpr auto const & setfill = iosetfill;
  constexpr auto const & setprecision = iosetprecision;
  constexpr auto const & setw = iosetw;
  constexpr auto const & ws = iows;

  constexpr auto const & basefield = iobasefield;
  constexpr auto const & adjustfield = ioadjustfield;
  constexpr auto const & floatfield = iofloatfield;
  constexpr auto const & boolalpha = ioboolalpha;
  constexpr auto const & showbase = ioshowbase;
  constexpr auto const & showpoint = ioshowpoint;
  constexpr auto const & showpos = ioshowpos;
  constexpr auto const & skipws = ioskipws;
  constexpr auto const & unitbuf = iounitbuf;
  constexpr auto const & uppercase = iouppercase;

  constexpr auto const & nobasefield = ionobasefield;
  constexpr auto const & noadjustfield = ionoadjustfield;
  constexpr auto const & nofloatfield = ionofloatfield;
  constexpr auto const & noboolalpha = ionoboolalpha;
  constexpr auto const & noshowbase = ionoshowbase;
  constexpr auto const & noshowpoint = ionoshowpoint;
  constexpr auto const & noshowpos = ionoshowpos;
  constexpr auto const & noskipws = ionoskipws;
  constexpr auto const & nounitbuf = ionounitbuf;
  constexpr auto const & nouppercase = ionouppercase;

  template<std::ios_base::fmtflags F>
  using fmt = iostreams::iofmt<F>;

  template<std::ios_base::fmtflags F
  , std::ios_base::fmtflags M = std::ios_base::fmtflags(0)>
  using setfmt = iostreams::iosetfmt<F, M>;

  template<std::ios_base::fmtflags F>
  using unsetfmt = iostreams::iounsetfmt<F>;
}

}
}

#endif
