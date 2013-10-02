#ifndef FALCON_TUPLE_ISTREAM_HPP
#define FALCON_TUPLE_ISTREAM_HPP

#include <falcon/c++1x/unpack.hpp>
#include <falcon/istream/ignore.hpp>
#include <falcon/tuple/parameter_index.hpp>
#include <falcon/tuple/detail/septuple.hpp>
#include <falcon/tuple/detail/tuplefwd.hpp>
#include <falcon/type_traits/is_tuple.hpp>

#include <type_traits>
#include <iosfwd>

namespace falcon {

template<typename CharT, typename Traits, typename Tuple, typename Sep = const CharT*>
void __istream_tuple(parameter_index<>,
                     std::basic_istream<CharT, Traits>&,
                     const Tuple&,
                     const Sep& = Sep())
{}

template<typename CharT, typename Traits, typename Tuple, typename Sep>
void __istream_tuple(parameter_index<0>,
                     std::basic_istream<CharT, Traits>& is,
                     Tuple& t,
                     const Sep&)
{ is >> get<0>(t); }

template<typename CharT, typename Traits, typename Tuple, std::size_t... Indexes>
void __istream_tuple(parameter_index<Indexes...>,
                     std::basic_istream<CharT, Traits>& is,
                     Tuple& t)
{
  CPP1X_UNPACK(is >> get<Indexes>(t));
}

template<typename CharT, typename Traits, typename Tuple, typename Sep,
         std::size_t... Indexes>
void __istream_tuple(parameter_index<0, Indexes...>,
                     std::basic_istream<CharT, Traits>& is,
                     Tuple& t,
                     const Sep& sep)
{
  is >> get<0>(t);
  CPP1X_UNPACK(::falcon::istream::ignore(is, sep) >> get<Indexes>(t));
}

template<typename CharT, typename Traits, typename Tuple>
std::basic_istream<CharT, Traits>&
get_tuple(std::basic_istream<CharT, Traits>& is, Tuple&& t)
{
  __istream_tuple(build_tuple_index_t<Tuple>(), is, t);
  return is;
}

template<typename CharT, typename Traits, typename Tuple, typename Sep>
std::basic_istream<CharT, Traits>&
get_tuple(std::basic_istream<CharT, Traits>& is, Tuple&& t, const Sep& sep)
{
  __istream_tuple(build_tuple_index_t<Tuple>(), is, t, sep);
  return is;
}

namespace tuple {

using ::falcon::get_tuple;

namespace istream {

template<typename CharT, typename Traits, typename Tuple>
typename std::enable_if<::falcon::is_tuple_impl<Tuple>::value
, std::basic_istream<CharT, Traits>&>::type
operator>>(std::basic_istream<CharT, Traits>& is, Tuple&& t)
{
  return ::falcon::get_tuple(is, t);
}

template<typename CharT, typename Traits, typename Tuple, typename Sep>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is, ::falcon::__iotuple<Tuple,Sep> t)
{
  return ::falcon::get_tuple(is, t.__t, t.__s);
}

}
}
}

#endif
