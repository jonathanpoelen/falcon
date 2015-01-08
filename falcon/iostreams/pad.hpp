#ifndef FALCON_IOSTREAMS_PAD_HPP
#define FALCON_IOSTREAMS_PAD_HPP

#include <falcon/io/ios_state.hpp>

#include <iosfwd>

namespace falcon {
namespace iostreams {

namespace aux_ {

class pad_specified;
class pad_right;
class pad_left;

template<class Tag, class T, class Ch = void>
struct pad_proxy {
  std::streamsize n_;
  T x_;
  Ch c_;
};

template<class Tag, class T>
struct pad_proxy<Tag, T, void> {
  std::streamsize n_;
  T x_;
};

template<class T, class Ch>
struct pad_proxy<pad_specified, T, Ch> {
  std::streamsize n_;
  T x_;
  std::ios::fmtflags adjustfield_;
  Ch c_;
};

template<class T>
struct pad_proxy<pad_specified, T, void> {
  T x_;
  std::ios::fmtflags adjustfield_;
  std::streamsize n_;
};

template<class Ch, class Tr, class Tag, class T>
Ch pad_getc(std::basic_ostream<Ch, Tr>& os, pad_proxy<Tag, T> const &)
{ return os.widen(' '); }

template<class Ch, class Tr, class Tag, class T>
Ch const& pad_getc(std::basic_ostream<Ch, Tr>&, pad_proxy<Tag, T, Ch> const & p)
{ return p.c_; }


template<class Ch, class Tr, class T, class C>
std::basic_ostream<Ch, Tr>&
operator<<(std::basic_ostream<Ch, Tr>& os, pad_proxy<void, T, C> const & x)
{
  io::basic_ios_fill_saver<Ch, Tr> fill_saver(os, pad_getc(os, x));
  os.width(std::streamsize(x.n_));
  return os << x.x_;
}

template<class Ch, class Tr, class T, class C>
std::basic_ostream<Ch, Tr>&
operator<<(
  std::basic_ostream<Ch, Tr>& os
, pad_proxy<pad_specified, T, C> const & x)
{
  io::basic_ios_fill_saver<Ch, Tr> fill_saver(os, pad_getc(os, x));
  os.width(std::streamsize(x.n_));
  if (x.adjustfield_ == std::ios::left) {
    std::right(os);
  }
  else {
    std::left(os);
  }
  return os << x.x_;
}

template<class Ch, class Tr, class Tag, class T, class C>
std::basic_ostream<Ch, Tr>&
operator<<(std::basic_ostream<Ch, Tr>& os, pad_proxy<Tag, T, C> const & x)
{
  io::basic_ios_fill_saver<Ch, Tr> fill_saver(os, pad_getc(os, x));
  os.width(std::streamsize(x.n_));
  if (std::is_same<Tag, pad_left>::value) {
    std::right(os);
  }
  else {
    std::left(os);
  }
  return os << x.x_;
}

}


template<class T>
aux_::pad_proxy<void, T const &>
pad(T const & x, unsigned n) noexcept
{ return {n, x}; }

template<class T, class Ch>
aux_::pad_proxy<void, T const &, Ch>
pad(T const & x, unsigned n, Ch c) noexcept
{ return {n, x, c}; }


template<class T>
aux_::pad_proxy<aux_::pad_specified, T const &>
pad(std::ios::fmtflags adjustfield, T const & x, unsigned n) noexcept
{ return {n, x, adjustfield}; }

template<class T, class Ch>
aux_::pad_proxy<aux_::pad_specified, T const &, Ch>
pad(std::ios::fmtflags adjustfield, T const & x, unsigned n, Ch c) noexcept
{ return {n, x, adjustfield, c}; }


template<class T>
aux_::pad_proxy<aux_::pad_left, T const &>
padl(T const & x, unsigned n) noexcept
{ return {n, x}; }

template<class T, class Ch>
aux_::pad_proxy<aux_::pad_left, T const &, Ch>
padl(T const & x, unsigned n, Ch c) noexcept
{ return {n, x, c}; }


template<class T>
aux_::pad_proxy<aux_::pad_right, T const &>
padr(T const & x, unsigned n) noexcept
{ return {n, x}; }

template<class T, class Ch>
aux_::pad_proxy<aux_::pad_right, T const &, Ch>
padr(T const & x, unsigned n, Ch c) noexcept
{ return {n, x, c}; }

}
}

#endif
