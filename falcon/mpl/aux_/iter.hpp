#ifndef FALCON_MPL_DETAIL_ITER_HPP
#define FALCON_MPL_DETAIL_ITER_HPP

#include <falcon/mpl/detail/na.hpp>
#include <falcon/mpl/detail/s_at.hpp>
#include <falcon/mpl/detail/s_size.hpp>
#include <falcon/mpl/protect.hpp>
#include <falcon/mpl/integral_c.hpp>
#include <falcon/mpl/advance_fwd.hpp>
#include <falcon/mpl/distance_fwd.hpp>
#include <falcon/mpl/iterator_tags.hpp>
#include <falcon/type_traits/eval_if.hpp>
#include <falcon/type_traits/use.hpp>

namespace falcon {
namespace mpl {
namespace aux {

template<typename Seq, typename Key>
using deref_iter_t = typename ::falcon::eval_if<
  (Key::value >= detail::s_size<Seq>::value),
  protect<detail::na>,
  detail::s_at<Seq, Key::value>
>::type;

template<typename Seq, typename Key>
class forward_iterator_impl
{
  using category = forward_iterator_tag;
  using type = deref_iter_t<Seq, Key>;
  using next = forward_iterator_impl<Seq, uint_<Key::value+1> >;
};

template<typename Seq, typename Key>
struct bidirectional_iterator_impl
{
  using category = bidirectional_iterator_tag;
  using type = deref_iter_t<Seq, Key>;
  using next = bidirectional_iterator_impl<Seq, uint_<Key::value+1> >;
  using prior = bidirectional_iterator_impl<Seq, uint_<Key::value-1> >;
};

template<typename Seq, typename Key>
struct random_access_iterator_impl
{
  using category = random_access_iterator_tag;
  using type = deref_iter_t<Seq, Key>;
  using next = random_access_iterator_impl<Seq, uint_<Key::value+1> >;
  using prior = random_access_iterator_impl<Seq, uint_<Key::value-1> >;
//   template<typename T>
//   struct advance
//   { using type = random_access_iterator_impl<Seq, uint_<Key::value+T::value> >; };
//
//   template<typename T>
//   struct recoil
//   { using type = random_access_iterator_impl<Seq, uint_<Key::value-T::value> >; };
};

template<typename Seq, typename Key, typename Tag>
using iterator_impl = ::falcon::eval_if_c<
  std::is_same<Tag, forward_iterator_tag>
, use<forward_iterator_impl<Seq, Key>>
, ::falcon::eval_if_c<
    std::is_same<Tag, bidirectional_iterator_tag>
  , use<bidirectional_iterator_impl<Seq, Key>>
  , ::falcon::if_c<
      std::is_same<Tag, random_access_iterator_tag>
    , random_access_iterator_impl<Seq, Key>
    , detail::na
    >
  >
>;

template<typename Iterator>
struct reverse_iterator
: Iterator
{
  using next = typename Iterator::prior;
  using prior = typename Iterator::next;
};

template<template<class, class> class IterClass, typename Iterator, typename N>
class iter_advance;

template<template<class, class> class IterClass
, typename Seq, typename Key, typename N>
struct iter_advance<IterClass, IterClass<Seq, Key>, N>
{ using type = IterClass<Seq, uint_<Key::value + N::value> >; };

template<template<class, class> class IterClass
, typename Seq, typename Key, typename N>
struct iter_advance<IterClass, reverse_iterator<IterClass<Seq, Key>>, N>
{ using type = IterClass<Seq, uint_<Key::value - N::value> >; };

template<template<class, class> class IterClass, typename First, typename Last>
class iter_distance;

template<template<class, class> class IterClass
, typename Seq, typename Key, typename Key2>
struct iter_distance<IterClass, IterClass<Seq, Key>, IterClass<Seq, Key2>>
{ using type = long_<Key2::value - Key::value>; };

template<template<class, class> class IterClass
, typename Seq, typename Key, typename Key2>
struct iter_distance<IterClass, reverse_iterator<IterClass<Seq, Key>>, IterClass<Seq, Key2>>
{ using type = long_<Key::value - Key2::value>; };

}


template<>
struct advance_impl<forward_iterator_tag>
{
  template<typename Iterator, typename N>
  using apply = aux::iter_advance<aux::forward_iterator_impl, Iterator, N>;
};

template<>
struct advance_impl<bidirectional_iterator_tag>
{
  template<typename Iterator, typename N>
  using apply = aux::iter_advance<aux::bidirectional_iterator_impl, Iterator, N>;
};

template<>
struct advance_impl<random_access_iterator_tag>
{
  template<typename Iterator, typename N>
  using apply = aux::iter_advance<aux::random_access_iterator_impl, Iterator, N>;
};


template<>
struct distance_impl<forward_iterator_tag>
{
  template<typename First, typename Last>
  using apply = aux::iter_distance<aux::forward_iterator_impl, First, Last>;
};

template<>
struct distance_impl<bidirectional_iterator_tag>
{
  template<typename First, typename Last>
  using apply = aux::iter_distance<aux::bidirectional_iterator_impl, First, Last>;
};

template<>
struct distance_impl<random_access_iterator_tag>
{
  template<typename First, typename Last>
  using apply = aux::iter_distance<aux::random_access_iterator_impl, First, Last>;
};

}
}

#endif
