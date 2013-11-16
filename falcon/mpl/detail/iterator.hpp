#ifndef FALCON_MPL_DETAIL_ITERATOR_HPP
#define FALCON_MPL_DETAIL_ITERATOR_HPP

#include <falcon/mpl/detail/fwd.hpp>
#include <falcon/mpl/detail/at.hpp>
#include <falcon/mpl/protect.hpp>
#include <falcon/mpl/integral.hpp>
#include <falcon/type_traits/eval_if.hpp>

#include <iterator>

namespace falcon {
namespace mpl {
namespace detail {

struct mpl_iterator_def
{
  using mpl_iterator = std::true_type;
};

class na;

template<typename Seq, typename Key, typename Tag>
class iterator_impl;


template<typename Seq, typename Key, typename Tag = std::forward_iterator_tag>
class forward_iterator_impl;

template<template<class...> class Temp, typename... Args, typename Key, typename Tag>
struct forward_iterator_impl<Temp<Args...>, Key, Tag>
: mpl_iterator_def
{
  static const unsigned pos = Key::value;
  using type = typename ::falcon::eval_if<
    (pos >= sizeof...(Args)),
    protect<na>,
    at_impl<Temp<Args...>, Key::value>
  >::type;
  using next = iterator_impl<Temp<Args...>, uint_<pos+1>, Tag>;
};

template<typename Seq, typename Key>
struct iterator_impl<Seq, Key, std::forward_iterator_tag>
: forward_iterator_impl<Seq, Key>
{};

template<typename Seq, typename Key, typename Tag = std::bidirectional_iterator_tag>
struct bidirectional_iterator_impl
: forward_iterator_impl<Seq, Key, Tag>
{
  using prior = iterator_impl<Seq, uint_<Key::value-1>, Tag>;
};

template<typename Seq, typename Key>
struct iterator_impl<Seq, Key, std::bidirectional_iterator_tag>
: bidirectional_iterator_impl<Seq, Key>
{};

template<typename Seq, typename Key, typename Tag = std::random_access_iterator_tag>
struct random_access_iterator_impl
: bidirectional_iterator_impl<Seq, Key, Tag>
{
  template<typename T>
  struct advance
  { using type = iterator_impl<Seq, uint_<Key::value+T::value>, Tag>; };

  template<typename T>
  struct recoil
  { using type = iterator_impl<Seq, uint_<Key::value-T::value>, Tag>; };
};

template<typename Seq, typename Key>
struct iterator_impl<Seq, Key, std::random_access_iterator_tag>
: random_access_iterator_impl<Seq, Key>
{};

}

}
}

#endif
