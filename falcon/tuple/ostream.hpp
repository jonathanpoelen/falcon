#ifndef FALCON_TUPLE_OSTREAM_HPP
#define FALCON_TUPLE_OSTREAM_HPP

#include <falcon/tuple/detail/septuple.hpp>
#include <falcon/tuple/put_tuple.hpp>
#include <falcon/type_traits/is_tuple.hpp>

#include <type_traits>
#include <iosfwd>

namespace falcon {

namespace tuple {

using ::falcon::put_tuple;

namespace ostream {

template<typename CharT, typename Traits, typename Tuple>
typename std::enable_if<::falcon::is_tuple_impl<Tuple>::value
, std::basic_ostream<CharT, Traits>&>::type
operator<<(std::basic_ostream<CharT, Traits>& os, const Tuple& t)
{
	return os << ::falcon::put_tuple(t);
}

template<typename CharT, typename Traits, typename Tuple, typename Sep>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, ::falcon::__iotuple<Tuple,Sep> t)
{
  return os << ::falcon::put_tuple(t.__t, t.__s);
}

}
}

}

#endif
