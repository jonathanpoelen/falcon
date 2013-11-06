#ifndef FALCON_TUPLE_PUT_TUPLE_HPP
#define FALCON_TUPLE_PUT_TUPLE_HPP

#include <falcon/c++1x/unpack.hpp>
#include <falcon/string/is_character.hpp>
#include <falcon/string/cstring.hpp>
#include <falcon/tuple/detail/tuplefwd.hpp>
#include <falcon/tuple/parameter_index.hpp>

#include <type_traits>
#include <iosfwd>

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
  os << get<0>(t);
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
  CPP1X_UNPACK(os << osep << get<Indexes>(t));
}

template<typename Tuple>
struct __put_tuple
{ const Tuple & t; };

template<typename Tuple,  typename Sep>
struct __put_tuple2
{ const Tuple & t; const Sep & sep; };

template<typename Tuple>
__put_tuple<Tuple> put_tuple(const Tuple& t)
{ return {t}; }

template<typename Tuple, typename Sep>
__put_tuple2<Tuple, Sep> put_tuple(const Tuple& t, const Sep& sep)
{ return {t, sep}; }

template<typename CharT, typename Traits, typename Tuple>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, __put_tuple<Tuple> t)
{
  const CharT c(' ');
  __ostream_tuple(build_tuple_index_t<Tuple>(), os, t.t,
                  basic_const_cstring<CharT>(&c, 1));
  return os;
}

template<typename CharT, typename Traits, typename Tuple, typename Sep>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, __put_tuple2<Tuple, Sep> t)
{
  __ostream_tuple(build_tuple_index_t<Tuple>(), os, t.t, t.sep);
  return os;
}



}

#endif
