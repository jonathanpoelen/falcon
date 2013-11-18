#ifndef FALCON_MPL_VECTOR_HPP
#define FALCON_MPL_VECTOR_HPP

#include <falcon/mpl/detail/fwd.hpp>
#include <falcon/mpl/detail/iterator.hpp>
#include <falcon/mpl/detail/at.hpp>
#include <falcon/mpl/detail/insert.hpp>
#include <falcon/mpl/detail/erase.hpp>

namespace falcon {
namespace mpl {

// class vector_tag;

template<typename... Args>
struct vector
: detail::mpl_container_def
{
  using type = vector;
//   using sequence_tag = vector_tag;
//   using iterator_tag = std::random_access_iterator_tag;
};

namespace aux {

template<typename... Ts>
struct size<vector<Ts...>>
{
  static const std::size_t value = sizeof...(Ts);
};

template<typename... Ts>
struct empty<vector<Ts...>>
{
  static const bool value = !sizeof...(Ts);
};

template<typename... Ts>
struct begin<vector<Ts...>>
{
  using type = detail::iterator_impl<
    vector<Ts...>
  , uint_<0>
  , std::random_access_iterator_tag
  >;
};

template<typename... Ts>
struct end<vector<Ts...>>
{
  using type = detail::iterator_impl<
    vector<Ts...>
  , uint_<sizeof...(Ts)>
  , std::random_access_iterator_tag
  >;
};

template<typename T, typename... Ts>
struct front<vector<T, Ts...>>
{ using type = T; };

template<typename... Ts>
struct back<vector<Ts...>>
{ using type = typename detail::at_impl<vector<Ts...>, sizeof...(Ts)-1>::type; };

template<typename... Ts, typename Pos>
struct at<vector<Ts...>, Pos, void_>
{ using type = typename detail::at_impl<vector<Ts...>, Pos::value>::type; };

template<typename... Ts, typename Pos, typename T>
struct insert<vector<Ts...>, Pos, T>
{ using type = typename detail::insert_impl<vector<Ts...>, Pos::pos, T>::type; };

template<typename... Ts, typename Pos, typename Range>
struct insert_range<vector<Ts...>, Pos, Range>
{ using type = typename detail::insert_range_impl<vector<Ts...>, Pos::pos, Range>::type; };

template<typename... Ts, typename Pos>
struct erase<vector<Ts...>, Pos, detail::na>
{ using type = typename detail::erase_impl<
  vector<Ts...>
, Pos::pos
, Pos::next::value>::type;
};

template<typename... Ts, typename Pos, typename Last>
struct erase<vector<Ts...>, Pos, Last>
{ using type = typename detail::erase_impl<vector<Ts...>, Pos::pos, Last::pos>::type; };

template<typename... Ts>
struct clear<vector<Ts...>>
{ using type = vector<>; };

template<typename... Ts, typename T>
struct push_back<vector<Ts...>, T>
{ using type = vector<Ts..., T>; };

template<typename... Ts, typename T>
struct push_front<vector<Ts...>, T>
{ using type = vector<T, Ts...>; };

template<typename... Ts>
struct pop_back<vector<Ts...>>
{ using type = detail::erase_impl<vector<Ts...>, sizeof...(Ts)-1, sizeof...(Ts)>; };

template<typename T, typename... Ts>
struct pop_front<vector<T, Ts...>>
{ using type = vector<Ts...>; };

}
}
}

#endif
