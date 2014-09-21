#ifndef FALCON_TUPLE_TUPLE_IO_HPP
#define FALCON_TUPLE_TUPLE_IO_HPP

#include <falcon/tuple/is_tuple_like.hpp>
#include <falcon/tuple/get_tuple.hpp>
#include <falcon/tuple/put_tuple.hpp>

#include <type_traits>
#include <iosfwd>

namespace falcon { namespace tuple {

namespace aux_ {
  template<typename Tuple, typename Sep>
  struct iotuple
  {
    Tuple tuple;
    const Sep& sep;
  };
}

template<typename Tuple, typename Sep>
aux_::iotuple<Tuple&, Sep>
septuple(Tuple& t, const Sep& sep)
{ return {t,sep}; }

template<typename Tuple, typename Sep>
aux_::iotuple<const Tuple&, Sep>
septuple(const Tuple& t, const Sep& sep)
{ return {t,sep}; }


template<typename CharT, typename Traits, typename Tuple>
typename std::enable_if<
  is_tuple_like<Tuple>::value, std::basic_istream<CharT, Traits>&>::type
operator>>(std::basic_istream<CharT, Traits>& is, Tuple&& t)
{ return is >> ::falcon::get_tuple(t); }

template<typename CharT, typename Traits, typename Tuple, typename Sep>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is, aux_::iotuple<Tuple,Sep> t)
{ return is >> ::falcon::get_tuple(t.tuple, t.sep); }


template<typename CharT, typename Traits, typename Tuple>
typename std::enable_if<
  is_tuple_like<Tuple>::value, std::basic_ostream<CharT, Traits>&>::type
operator<<(std::basic_ostream<CharT, Traits>& os, const Tuple& t)
{ return os << ::falcon::put_tuple(t); }

template<typename CharT, typename Traits, typename Tuple, typename Sep>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, aux_::iotuple<Tuple,Sep> t)
{ return os << ::falcon::put_tuple(t.tuple, t.sep); }

} }

#endif
