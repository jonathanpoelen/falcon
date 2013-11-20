#ifndef FALCON_MPL_SET_HPP
#define FALCON_MPL_SET_HPP

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
struct set
: detail::mpl_container_def
{
  using type = set;
};

namespace aux {

template<typename... Ts>
struct size<set<Ts...>>
{ static const std::size_t value = sizeof...(Ts); };

template<typename... Ts>
struct empty<set<Ts...>>
{ static const bool value = !sizeof...(Ts); };

template<typename... Ts>
struct begin<set<Ts...>>
{
  using type = detail::iterator_impl<
    set<Ts...>
  , uint_<0>
  , std::random_access_iterator_tag
  >;
};

template<typename... Ts>
struct end<set<Ts...>>
{
  using type = detail::iterator_impl<
    set<Ts...>
  , uint_<sizeof...(Ts)>
  , std::random_access_iterator_tag
  >;
};

template<typename T, typename... Ts>
struct front<set<T, Ts...>>
{ using type = T; };

template<typename... Ts, typename T>
struct key_type<set<Ts...>, T>
{ using type = T; };

template<typename... Ts, typename T>
struct value_type<set<Ts...>, T>
{ using type = T; };

template<typename... Ts, typename Key>
struct has_key<set<Ts...>, Key>
{ using type = typename detail::has_key_impl<set<Ts...>, Key>::type; };

template<typename... Ts, typename Key>
struct count<set<Ts...>, Key>
{ using type = typename detail::count_impl<set<Ts...>, Key>::type; };

template<typename... Ts, typename Key>
struct order<set<Ts...>, Key>
{ using type = typename detail::order_impl<set<Ts...>, Key>::type; };

template<typename... Ts, typename Key, typename Default>
struct at<set<Ts...>, Key, Default>
{ using type = typename detail::assoc_at_impl<set<Ts...>, Key, Default>::type; };

template<typename... Ts, typename Pos, typename T>
struct insert<set<Ts...>, Pos, T>
{ using type = typename detail::assoc_insert_impl<set<Ts...>, T>::type; };

template<typename... Ts, typename T>
struct insert<set<Ts...>, T, detail::na>
{ using type = typename detail::assoc_insert_impl<set<Ts...>, T>::type; };

template<typename... Ts, typename T>
struct erase<set<Ts...>, T, detail::na>
{ using type = typename detail::assoc_erase_impl<set<Ts...>, T>::type; };

template<typename... Ts, typename T>
struct erase_key<set<Ts...>, T>
{ using type = typename detail::assoc_erase_impl<set<Ts...>, deref_t<T>>::type; };

}

}
}

#endif
