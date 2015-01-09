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

template<class Tag = void, class Ch = void>
struct pad_proxy {
  std::streamsize n_;
  Ch c_;
};

template<class Tag>
struct pad_proxy<Tag, void> {
  std::streamsize n_;
};

template<class Ch>
struct pad_proxy<pad_specified, Ch> {
  std::streamsize n_;
  std::ios_base::fmtflags adjustfield_;
  Ch c_;
};

template<>
struct pad_proxy<pad_specified, void> {
  std::streamsize n_;
  std::ios_base::fmtflags adjustfield_;
};

template<class Ch, class Tr, class Tag>
Ch pad_getc(std::basic_ios<Ch, Tr>& os, pad_proxy<Tag> const &)
{ return os.widen(' '); }

template<class Ch, class Tr, class Tag>
Ch const& pad_getc(std::basic_ios<Ch, Tr>&, pad_proxy<Tag, Ch> const & p)
{ return p.c_; }

template<class Ch, class Tr, class Tag, class C>
void pad_impl(std::basic_ios<Ch, Tr> & io, pad_proxy<Tag, C> const & x)
{
  io.fill(pad_getc(io, x));
  io.width(std::streamsize(x.n_));
}

template<class Ch, class Tr, class Tag, class C>
void pad_impl(
  std::basic_ios<Ch, Tr> & io
, pad_proxy<Tag, C> const & x
, bool is_left)
{
  io.fill(pad_getc(io, x));
  io.width(std::streamsize(x.n_));
  io.setf(
    is_left ? std::ios_base::left : std::ios_base::right
  , std::ios_base::adjustfield);
}


template<class Ch, class Tr, class C>
std::basic_ostream<Ch, Tr>&
operator<<(std::basic_ostream<Ch, Tr>& os, pad_proxy<void, C> const & x)
{
  pad_impl(os, x);
  return os;
}

template<class Ch, class Tr, class C>
std::basic_istream<Ch, Tr>&
operator>>(std::basic_istream<Ch, Tr>& is, pad_proxy<void, C> const & x)
{
  pad_impl(is, x);
  return is;
}


template<class Ch, class Tr, class C>
std::basic_ostream<Ch, Tr>&
operator<<(
  std::basic_ostream<Ch, Tr>& os
, pad_proxy<pad_specified, C> const & x)
{
  pad_impl(os, x, x.adjustfield_ == std::ios_base::left);
  return os;
}

template<class Ch, class Tr, class C>
std::basic_istream<Ch, Tr>&
operator<<(
  std::basic_istream<Ch, Tr>& is
, pad_proxy<pad_specified, C> const & x)
{
  pad_impl(is, x, x.adjustfield_ == std::ios_base::left);
  return is;
}


template<class Ch, class Tr, class Tag, class C>
std::basic_ostream<Ch, Tr>&
operator<<(std::basic_ostream<Ch, Tr>& os, pad_proxy<Tag, C> const & x)
{
  pad_impl(os, x, std::is_same<Tag, pad_left>::value);
  return os;
}

template<class Ch, class Tr, class Tag, class C>
std::basic_istream<Ch, Tr>&
operator<<(std::basic_istream<Ch, Tr>& is, pad_proxy<Tag, C> const & x)
{
  pad_impl(is, x, std::is_same<Tag, pad_left>::value);
  return is;
}

}


inline
aux_::pad_proxy<>
pad(unsigned n) noexcept
{ return {n}; }

template<class Ch>
aux_::pad_proxy<void, Ch>
pad(unsigned n, Ch c) noexcept
{ return {n, c}; }

inline
aux_::pad_proxy<aux_::pad_specified>
pad(std::ios_base::fmtflags adjustfield, unsigned n) noexcept
{ return {n, adjustfield}; }

template<class Ch>
aux_::pad_proxy<aux_::pad_specified, Ch>
pad(std::ios_base::fmtflags adjustfield, unsigned n, Ch c) noexcept
{ return {n, adjustfield, c}; }


inline
aux_::pad_proxy<aux_::pad_left>
padl(unsigned n) noexcept
{ return {n}; }

template<class Ch>
aux_::pad_proxy<aux_::pad_left, Ch>
padl(unsigned n, Ch c) noexcept
{ return {n, c}; }


inline
aux_::pad_proxy<aux_::pad_right>
padr(unsigned n) noexcept
{ return {n}; }

template<class Ch>
aux_::pad_proxy<aux_::pad_right, Ch>
padr(unsigned n, Ch c) noexcept
{ return {n, c}; }


}
}

#endif
