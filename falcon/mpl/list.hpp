#ifndef FALCON_MPL_VECTOR_HPP
#define FALCON_MPL_VECTOR_HPP

#include <falcon/mpl/detail/fwd.hpp>
#include <falcon/mpl/detail/iterator.hpp>
#include <falcon/mpl/detail/insert.hpp>
#include <falcon/mpl/detail/erase.hpp>

namespace falcon {
namespace mpl {

// class list_tag;

template<typename... Args>
struct list
: detail::mpl_container_def
{
  using type = list;
//   using sequence_tag = list_tag;
//   using iterator_tag = std::random_access_iterator_tag;
};

namespace aux {

template<typename... Ts>
struct size<list<Ts...>>
{ static const std::size_t value = sizeof...(Ts); };

template<typename... Ts>
struct empty<list<Ts...>>
{ static const bool value = !sizeof...(Ts); };

template<typename... Ts>
struct begin<list<Ts...>>
{
  using type = detail::iterator_impl<
    list<Ts...>
  , uint_<0>
  , std::bidirectional_iterator_tag
  >;
};

template<typename... Ts>
struct end<list<Ts...>>
{
  using type = detail::iterator_impl<
    list<Ts...>
  , uint_<sizeof...(Ts)>
  , std::bidirectional_iterator_tag
  >;
};

template<typename T, typename... Ts>
struct front<list<T, Ts...>>
{ using type = T; };

template<typename... Ts, typename Pos, typename T>
struct insert<list<Ts...>, Pos, T>
{ using type = typename detail::insert_impl<list<Ts...>, Pos::pos, T>::type; };

template<typename... Ts, typename Pos, typename Range>
struct insert_range<list<Ts...>, Pos, Range>
{ using type = typename detail::insert_range_impl<list<Ts...>, Pos::pos, Range>::type; };

template<typename... Ts, typename Pos>
struct erase<list<Ts...>, Pos, na>
{ using type = typename detail::erase_impl<
  list<Ts...>
, Pos::pos
, Pos::next::value>::type;
};

template<typename... Ts, typename Pos, typename Last>
struct erase<list<Ts...>, Pos, Last>
{ using type = typename detail::erase_impl<list<Ts...>, Pos::pos, Last::pos>::type; };

template<typename... Ts>
struct clear<list<Ts...>>
{ using type = list<>; };

template<typename... Ts, typename T>
struct push_front<list<Ts...>, T>
{ using type = list<T, Ts...>; };

template<typename T, typename... Ts>
struct pop_front<list<T, Ts...>>
{ using type = list<Ts...>; };

}
}
}

#endif
