#ifndef FALCON_TUPLE_OSTREAM_HPP
#define FALCON_TUPLE_OSTREAM_HPP

#include <falcon/c++1x/unpack.hpp>
#include <falcon/tuple/parameter_index.hpp>
#include <falcon/tuple/detail/septuple.hpp>
#include <falcon/string/is_character.hpp>
#include <falcon/string/basic_cstring.hpp>

#include <type_traits>
#include <iosfwd>
#include <tuple>

namespace falcon {

template<typename CharT, typename Traits, typename Tuple, typename Sep>
void __ostream_tuple(parameter_index<>,
                     std::basic_ostream<CharT, Traits>&,
                     const Tuple&,
                     const Sep&)
{}

template<typename CharT, typename Traits, typename Tuple, typename Sep,
         std::size_t ... Indexes>
void __ostream_tuple(parameter_index<0, Indexes...>,
                     std::basic_ostream<CharT, Traits>& os,
                     Tuple& t,
                     const Sep& sep)
{
  os << std::get<0>(t);
  using Remove = typename std::remove_cv<Sep>::type;
  using RemovePointer = typename std::remove_pointer<Remove>::type;
  using OptimizeSep = typename std::conditional<
    (sizeof...(Indexes)
    && std::is_pointer<Remove>::value
    && is_character<RemovePointer>::value),
    const basic_cstring<const CharT>,
    const Sep&
  >::type;
  OptimizeSep osep = sep;
  CPP1X_UNPACK(os << osep << std::get<Indexes>(t));
}

template<typename CharT, typename Traits, typename Tuple, typename Sep = const char *>
std::basic_ostream<CharT, Traits>&
put_tuple(std::basic_ostream<CharT, Traits>& os, const Tuple& t, const Sep& sep = " ")
{
  __ostream_tuple(build_tuple_index_t<Tuple>(), os, t, sep);
  return os;
}

namespace tuple {

using ::falcon::put_tuple;

namespace ostream {

template<typename CharT, typename Traits, typename Tuple>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const Tuple& t)
{
	return ::falcon::put_tuple(os, t);
}

template<typename CharT, typename Traits, typename Tuple, typename Sep>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& is, ::falcon::__iotuple<Tuple,Sep> t)
{
  return ::falcon::put_tuple(is, t.__t, t.__s);
}

}
}

}

#endif
