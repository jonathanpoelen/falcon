#ifndef FALCON_TUPLE_GET_TUPLE_HPP
#define FALCON_TUPLE_GET_TUPLE_HPP

#include <falcon/utility/unpack.hpp>
#include <falcon/istream/ignore.hpp>
#include <falcon/string/is_character.hpp>
#include <falcon/string/cstring.hpp>
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
  FALCON_UNPACK(is >> get<Indexes>(t));
}

template<typename CharT, typename Traits, typename Tuple, typename Sep,
         std::size_t... Indexes>
void __istream_tuple(parameter_index<0, Indexes...>,
                     std::basic_istream<CharT, Traits>& is,
                     Tuple& t,
                     const Sep& sep)
{
  is >> get<0>(t);
  using Remove = typename std::remove_cv<Sep>::type;
  using RemovePointer = typename std::remove_pointer<Remove>::type;
  using OptimizeSep = typename std::conditional<
    (sizeof...(Indexes)
      && std::is_pointer<Remove>::value
      && is_character<RemovePointer>::value),
    const build_basic_cstring<const CharT>,
    const Sep&
  >::type;
  OptimizeSep osep = sep;
  FALCON_UNPACK(::falcon::istream::ignore(is, osep) >> get<Indexes>(t));
}

template<typename Tuple>
struct __get_tuple
{ Tuple & t; };

template<typename Tuple,  typename Sep>
struct __get_tuple2
{ Tuple & t; const Sep & sep; };

template<typename Tuple>
__get_tuple<Tuple> get_tuple(Tuple& t)
{ return {t}; }

template<typename Tuple, typename Sep>
__get_tuple2<Tuple, Sep> get_tuple(Tuple& t, const Sep& sep)
{ return {t, sep}; }

template<typename CharT, typename Traits, typename Tuple>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is, __get_tuple<Tuple> t)
{
  const CharT c(' ');
  __istream_tuple(build_tuple_index_t<Tuple>(), is, t.t,
                  basic_const_cstring<CharT>(&c, 1));
  return is;
}

template<typename CharT, typename Traits, typename Tuple, typename Sep>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is, __get_tuple2<Tuple, Sep> t)
{
  __istream_tuple(build_tuple_index_t<Tuple>(), is, t.t, t.sep);
  return is;
}

}

#endif
