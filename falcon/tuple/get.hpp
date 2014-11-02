#ifndef FALCON_TUPLE_GET_HPP
#define FALCON_TUPLE_GET_HPP

#include <array>

namespace falcon_tuple_get_impl {
  using std::get;

  template<std::size_t I, class T>
  constexpr auto tuple_get_impl(T & a) noexcept ->
  decltype(get<I>(a))
  { return get<I>(a); }

  template<std::size_t I, class T>
  constexpr auto tuple_get_impl(T && a) noexcept ->
  decltype(get<I>(std::move(a)))
  { return get<I>(std::move(a)); }
}

namespace falcon {

template<std::size_t I, class T>
constexpr auto get(T& t) noexcept ->
decltype(::falcon_tuple_get_impl::tuple_get_impl<I>(t))
{ return ::falcon_tuple_get_impl::tuple_get_impl<I>(t); }

template<std::size_t I, class T>
constexpr auto get(T&& t) noexcept ->
decltype(::falcon_tuple_get_impl::tuple_get_impl<I>(std::move(t)))
{ return ::falcon_tuple_get_impl::tuple_get_impl<I>(std::move(t)); }

}

#endif
