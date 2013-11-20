#ifndef FALCON_MPL_MAP_HPP
#define FALCON_MPL_MAP_HPP

#include <falcon/mpl/detail/fwd.hpp>
#include <falcon/mpl/detail/assoc_at.hpp>
#include <falcon/mpl/detail/assoc_erase.hpp>
#include <falcon/mpl/detail/assoc_insert.hpp>
#include <falcon/mpl/detail/iterator.hpp>
#include <falcon/mpl/detail/insert.hpp>
#include <falcon/mpl/detail/erase.hpp>
#include <falcon/mpl/detail/has_key.hpp>
#include <falcon/mpl/detail/count.hpp>
#include <falcon/mpl/detail/order.hpp>
#include <falcon/mpl/integral.hpp>
#include <falcon/mpl/deref.hpp>

namespace falcon {
namespace mpl {

template<typename... Args>
struct map
: detail::mpl_container_def
{
  using type = map;
};

namespace aux {

template<typename... Ts>
struct size<map<Ts...>>
{ static const std::size_t value = sizeof...(Ts); };

template<typename... Ts>
struct empty<map<Ts...>>
{ static const bool value = !sizeof...(Ts); };

template<typename... Ts>
struct begin<map<Ts...>>
{
  using type = detail::iterator_impl<
    map<Ts...>
  , uint_<0>
  , std::random_access_iterator_tag
  >;
};

template<typename... Ts>
struct end<map<Ts...>>
{
  using type = detail::iterator_impl<
    map<Ts...>
  , uint_<sizeof...(Ts)>
  , std::random_access_iterator_tag
  >;
};

template<typename T, typename... Ts>
struct front<map<T, Ts...>>
{ using type = T; };

template<typename... Ts, typename T>
struct key_type<map<Ts...>, T>
{ using type = typename T::first; };

template<typename... Ts, typename T>
struct value_type<map<Ts...>, T>
{ using type = typename T::second; };

template<typename... Ts, typename Key>
struct has_key<map<Ts...>, Key>
{ using type = typename detail::has_key_impl<map<Ts...>, Key>::type; };

template<typename... Ts, typename Key>
struct count<map<Ts...>, Key>
{ using type = typename detail::count_impl<map<Ts...>, Key>::type; };

template<typename... Ts, typename Key>
struct order<map<Ts...>, Key>
{ using type = typename detail::order_impl<map<Ts...>, Key>::type; };

template<typename... Ts, typename Key, typename Default>
struct at<map<Ts...>, Key, Default>
{ using type = typename detail::assoc_at_impl<map<Ts...>, Key, Default>::type; };

template<typename... Ts, typename Pos, typename T>
struct insert<map<Ts...>, Pos, T>
{ using type = typename detail::assoc_insert_impl<map<Ts...>, T>::type; };

template<typename... Ts, typename T>
struct insert<map<Ts...>, T, detail::na>
{ using type = typename detail::assoc_insert_impl<map<Ts...>, T>::type; };

template<typename... Ts, typename T>
struct erase<map<Ts...>, T, detail::na>
{ using type = typename detail::assoc_erase_impl<map<Ts...>, T>::type; };

template<typename... Ts, typename T>
struct erase_key<map<Ts...>, T>
{ using type = typename detail::assoc_erase_impl<map<Ts...>, deref_t<T>>::type; };

}

}
}

#endif
