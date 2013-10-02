#ifndef FALCON_TUPLE_TO_TUPLE_REFERENCE_HPP
#define FALCON_TUPLE_TO_TUPLE_REFERENCE_HPP

#include <falcon/tuple/parameter_index.hpp>
#include <falcon/tuple/build_tuple_reference.hpp>

#include <utility>
#include <tuple>

namespace falcon {

/// Reference tuple element
template <typename T, std::size_t... Indexes>
typename build_tuple_const_reference<
  T, parameter_index<Indexes...>
>::type
to_tuple_reference(parameter_index<Indexes...>, const T & t)
{
  return build_tuple_const_reference_t<
    T, parameter_index<Indexes...>
  >(std::get<Indexes>(t)...);
}

/// Reference tuple element
template <typename T, std::size_t... Indexes>
typename build_tuple_reference<
  T, parameter_index<Indexes...>
>::type
to_tuple_reference(parameter_index<Indexes...>, T& t)
{
  return build_tuple_reference_t<
    T, parameter_index<Indexes...>
  >(std::get<Indexes>(t)...);
}


/// Reference tuple element
template <typename T>
typename build_tuple_const_reference<
  T, build_tuple_index_t<T>
>::type
to_tuple_reference(const T& t)
{ return to_tuple_reference(build_tuple_index_t<T>(), t); }

/// Reference tuple element
template <typename T>
typename build_tuple_reference<
  T, build_tuple_index_t<T>
>::type
to_tuple_reference(T& t)
{ return to_tuple_reference(build_tuple_index_t<T>(), t); }

}

#endif
