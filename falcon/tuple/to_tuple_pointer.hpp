#ifndef FALCON_TUPLE_TO_TUPLE_POINTER_HPP
#define FALCON_TUPLE_TO_TUPLE_POINTER_HPP

#include <falcon/tuple/parameter_index.hpp>
#include <falcon/tuple/build_tuple_pointer.hpp>

#include <utility>
#include <tuple>

namespace falcon {

/// Pointer tuple element
template <typename T, std::size_t... Indexes>
typename build_tuple_const_pointer<
  T, parameter_index<Indexes...>
>::type
to_tuple_pointer(const T & t, const parameter_index<Indexes...>&)
{
  return build_tuple_const_pointer_t<
    T, parameter_index<Indexes...>
  >(&std::get<Indexes>(t)...);
}

/// Pointer tuple element
template <typename T, std::size_t... Indexes>
typename build_tuple_pointer<
  T, parameter_index<Indexes...>
>::type
to_tuple_pointer(T& t, const parameter_index<Indexes...>&)
{
  return build_tuple_pointer_t<
    T, parameter_index<Indexes...>
  >(&std::get<Indexes>(t)...);
}


/// Pointer tuple element
template <typename T>
typename build_tuple_const_pointer<
  T, build_tuple_index_t<T>
>::type
to_tuple_pointer(const T& t)
{ return to_tuple_pointer(t, build_tuple_index_t<T>()); }

/// Pointer tuple element
template <typename T>
typename build_tuple_pointer<
  T, build_tuple_index_t<T>
>::type
to_tuple_pointer(T& t)
{ return to_tuple_pointer(t, build_tuple_index_t<T>()); }

}

#endif
