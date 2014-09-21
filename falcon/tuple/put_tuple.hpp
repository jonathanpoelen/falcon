#ifndef FALCON_TUPLE_PUT_TUPLE_HPP
#define FALCON_TUPLE_PUT_TUPLE_HPP

#include <falcon/utility/unpack.hpp>
#include <falcon/string/cstring.hpp>
#include <falcon/string/local_const_string_optimized.hpp>
#include <falcon/tuple/parameter_index.hpp>

#include <type_traits>
#include <iosfwd>
#include <tuple>

namespace falcon {

using std::get;

namespace aux_ {
  template<class Ostream, class Tuple, class Sep>
  void ostream_tuple(parameter_index<>, Ostream&, const Tuple&, const Sep&)
  {}

  template<
    class CharT, class Traits, class Tuple, class Sep, std::size_t ... Indexes>
  void ostream_tuple(
    parameter_index<0, Indexes...>, std::basic_ostream<CharT, Traits>& os,
    Tuple& t, const Sep& sep)
  {
    os << get<0>(t);
    const auto & osep = ::falcon::string::local_const_string_optimized(sep);
    FALCON_UNPACK(os << osep << get<Indexes>(t));
  }

  template<class Tuple>
  struct ostream_put_tuple_t
  { const Tuple & tuple; };

  template<class Tuple,  class Sep>
  struct ostream_put_tuple_2_t
  { const Tuple & tuple; const Sep & sep; };


  template<class CharT, class Traits, class Tuple>
  std::basic_ostream<CharT, Traits>&
  operator<<(
    std::basic_ostream<CharT, Traits>& os, ostream_put_tuple_t<Tuple> t)
  {
    const CharT c(' ');
    ostream_tuple(
      build_tuple_index_t<Tuple>(), os, t.tuple,
      basic_const_cstring<CharT>(&c, 1));
    return os;
  }

  template<class CharT, class Traits, class Tuple, class Sep>
  std::basic_ostream<CharT, Traits>&
  operator<<(
    std::basic_ostream<CharT, Traits>& os,
    ostream_put_tuple_2_t<Tuple, Sep> t)
  {
    ostream_tuple(build_tuple_index_t<Tuple>(), os, t.tuple, t.sep);
    return os;
  }
}

template<class Tuple>
aux_::ostream_put_tuple_t<Tuple>
put_tuple(const Tuple& t)
{ return {t}; }

template<class Tuple, class Sep>
aux_::ostream_put_tuple_2_t<Tuple, Sep>
put_tuple(const Tuple& t, const Sep& sep)
{ return {t, sep}; }

}

#endif
