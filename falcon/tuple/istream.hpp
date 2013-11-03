#ifndef FALCON_TUPLE_ISTREAM_HPP
#define FALCON_TUPLE_ISTREAM_HPP

# include <falcon/tuple/detail/septuple.hpp>
# include <falcon/tuple/get_tuple.hpp>
# include <falcon/type_traits/is_tuple.hpp>

# include <type_traits>
# include <iosfwd>

namespace tuple {

using ::falcon::get_tuple;

namespace istream {

template<typename CharT, typename Traits, typename Tuple>
typename std::enable_if<::falcon::is_tuple_impl<Tuple>::value
, std::basic_istream<CharT, Traits>&>::type
operator>>(std::basic_istream<CharT, Traits>& is, Tuple&& t)
{
  return is >> ::falcon::get_tuple(t);
}

template<typename CharT, typename Traits, typename Tuple, typename Sep>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is, ::falcon::__iotuple<Tuple,Sep> t)
{
  return is >> ::falcon::get_tuple(t.__t, t.__s);
}

}
}

#endif
