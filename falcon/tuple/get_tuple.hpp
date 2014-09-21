#ifndef FALCON_TUPLE_GET_TUPLE_HPP
#define FALCON_TUPLE_GET_TUPLE_HPP

#include <falcon/utility/unpack.hpp>
#include <falcon/iostreams/ignore.hpp>
#include <falcon/string/cstring.hpp>
#include <falcon/string/local_const_string_optimized.hpp>
#include <falcon/tuple/parameter_index.hpp>

#include <type_traits>
#include <iosfwd>
#include <tuple>

namespace falcon {

  using std::get;

namespace aux_ {
  template<class IStream, class Tuple, class Sep>
  void istream_tuple(parameter_index<>, IStream&, const Tuple)
  {}

  template<
    class CharT, class Traits, class Tuple, class Sep, std::size_t... Indexes>
  void istream_tuple(
    parameter_index<0, Indexes...>, std::basic_istream<CharT, Traits>& istream,
    Tuple& tuple, const Sep& sep)
  {
    using ::falcon::get;
    istream >> get<0>(tuple);
    const auto & osep = ::falcon::string::local_const_string_optimized(sep);
    FALCON_UNPACK(
      ::falcon::iostreams::ignore(istream, osep) >> get<Indexes>(tuple)
    );
  }

  template<class Tuple>
  struct istream_get_tuple_t
  { Tuple & tuple; };

  template<class Tuple,  typename Sep>
  struct istream_get_tuple_2_t
  { Tuple & tuple; const Sep & sep; };


  template<class CharT, class Traits, class Tuple>
  std::basic_istream<CharT, Traits>&
  operator>>(
    std::basic_istream<CharT, Traits>& istream,
    istream_get_tuple_t<Tuple> gtuple)
  {
    const CharT c(' ');
    istream_tuple(
      build_tuple_index_t<Tuple>(), istream, gtuple.tuple,
      basic_const_cstring<CharT>(&c, 1));
    return istream;
  }

  template<class CharT, class Traits, class Tuple, class Sep>
  std::basic_istream<CharT, Traits>&
  operator>>(
    std::basic_istream<CharT, Traits>& istream,
    istream_get_tuple_2_t<Tuple, Sep> gtuple)
  {
    istream_tuple(
      build_tuple_index_t<Tuple>(), istream, gtuple.tuple, gtuple.sep);
    return istream;
  }
}

template<class Tuple>
aux_::istream_get_tuple_t<Tuple>
get_tuple(Tuple& tuple)
{ return {tuple}; }

template<class Tuple, class Sep>
aux_::istream_get_tuple_2_t<Tuple, Sep>
get_tuple(Tuple& tuple, const Sep& sep)
{ return {tuple, sep}; }

}

#endif
