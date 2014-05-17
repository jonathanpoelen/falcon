#ifndef FALCON_ITERATOR_SYNCHRONIZE_ITERATOR_HPP
#define FALCON_ITERATOR_SYNCHRONIZE_ITERATOR_HPP

#include <falcon/iterator/minimal_iterator_category.hpp>
#include <falcon/iterator/iterator_handler.hpp>
#include <falcon/utility/synchronizer.hpp>

#include <falcon/parameter/manip.hpp>
#include <falcon/parameter/pack_reference.hpp>
#include <falcon/parameter/is_parameter_index_tag.hpp>

#include <falcon/helper/restrict_iterator_category.hpp>
#include <falcon/helper/restrict_value_type.hpp>
#include <falcon/helper/restrict_reference.hpp>
#include <falcon/helper/restrict_pointer.hpp>

#include <falcon/type_traits/build_class.hpp>
#include <falcon/type_traits/disable_if.hpp>
#include <falcon/type_traits/enable_if.hpp>
#include <falcon/type_traits/eval_if.hpp>

#include <type_traits>
#include <tuple>

namespace falcon {
namespace iterator {

template <class... Iterators>
class synchronize_iterator;

namespace detail {
  template<class... Categories>
  class synchronize_iterator_category;

  template<class Category, class Category2, class... Categories>
  struct synchronize_iterator_category<Category, Category2, Categories...>
  : synchronize_iterator_category<
    typename if_<
      (_aux::rank_category<Category>::rank < _aux::rank_category<Category2>::rank)
    , Category
    , Category2
    >::type
  , Categories...
  >
  {};

  template<class Category>
  struct synchronize_iterator_category<Category>
  { typedef Category iterator_category; };

  template<class... Iterators>
  struct synchronize_iterator_base
  {
    static_assert(sizeof...(Iterators) != 0, "none iterator");

    typedef ::falcon::parameter_pack<Iterators...> parameter_pack;

    typedef typename parameter_element<
      sizeof...(Iterators) - 1
    , parameter_pack
    >::type last;

    static const bool is_tag = is_parameter_index_or_tag<last>();

    static_assert(is_tag ? sizeof...(Iterators) != 1 : true, "none iterator");

    typedef typename parameter_index_or_tag_to_tag<
      typename if_<
        is_tag
      , last
      , full_parameter_index_tag
      >::type
    >::type parameter_index_tag;

    struct iterators_with_tag
    {
      typedef typename parameter::elements<
        parameter_pack
      , typename build_parameter_index<sizeof...(Iterators) - 1>::type
      >::type type;
    };

    typedef typename eval_if<
      is_tag
    , iterators_with_tag
    , use<parameter_pack>
    >::type iterators;

    typedef typename keep_parameter_index<
      parameter_index_tag
    , sizeof...(Iterators) - (is_tag ? 1 : 0)
    >::type cmp_parameter_index;

    static const bool cmp_iterators_is_full = std::is_same<
      typename build_parameter_index<sizeof...(Iterators)>::type
    , cmp_parameter_index
    >::value;

    typedef typename parameter::wrap<
      std::iterator_traits
    , iterators
    >::type pack_traits;

    template<template<class...>class W>
    struct subtype
    : build_class<
      synchronizer
    , typename parameter::modifier<W, pack_traits>::type
    >
    {};

    struct no_dimension {};

    typedef typename iterator_handler_types<
      synchronize_iterator<Iterators...>
    , typename build_class<synchronizer, iterators>::type
    , typename build_class<
        synchronize_iterator_category
      , typename parameter::modifier<restrict_iterator_category, pack_traits>::type
      >::type::iterator_category
    , typename subtype<restrict_value_type>::type
    , no_dimension
    , typename subtype<restrict_pointer>::type
    , typename subtype<restrict_reference>::type
    >::type type;
  };
}

/**
 * synchronize_iterator< Iterators...[, \link indexes-tag parameter_index_tag]>
 */
template <class... Iterators>
class synchronize_iterator
: public detail::synchronize_iterator_base<Iterators...>::type
{
  friend class iterator_core_access;

  typedef detail::synchronize_iterator_base<Iterators...> detail;
  typedef typename detail::type inherit_type;

public:
  typedef typename inherit_type::iterator_type iterator_type;
  typedef typename iterator_type::tuple_type iterator_tuple;

public:
  synchronize_iterator()
  {}

  synchronize_iterator(iterator_type&& x)
  : inherit_type(std::forward<iterator_type>(x), 1)
  {}

  template<class... Args>
  synchronize_iterator(std::tuple<Args...>&& x)
  : inherit_type(std::forward<iterator_type>(x), 1)
  {}

  template<class... Args>
  synchronize_iterator(Args&&... args)
  : inherit_type(std::piecewise_construct, std::forward<Args>(args)...)
  {}

  using inherit_type::operator=;

  iterator_tuple& iterators()
  { return this->base_reference().tuple(); }

  const iterator_tuple& iterators() const
  { return this->base_reference().tuple(); }

private:
  const iterator_tuple& cmp_iterator(std::true_type) const
  { return iterators(); }

  CPP1X_DELEGATE_FUNCTION(
    cmp_iterator(std::false_type) const
  , to_tuple_reference(typename detail::cmp_parameter_index(), this->iterators())
  )

  typedef std::integral_constant<bool, detail::cmp_iterators_is_full> cmp_type;

  bool equal(const synchronize_iterator& other) const
  { return cmp_iterator(cmp_type()) == other.cmp_iterator(cmp_type()); }

  bool less(const synchronize_iterator& other) const
  { return cmp_iterator(cmp_type()) < other.cmp_iterator(cmp_type()); }
};


template <class IteratorOrTag, class... Iterators>
typename enable_if_c<
  is_parameter_index_or_tag<IteratorOrTag>
, synchronize_iterator<Iterators..., IteratorOrTag>
>::type make_synchronize_iterator(IteratorOrTag, Iterators... x)
{ return {x...}; }

template <class IteratorOrTag, class... Iterators>
typename disable_if_c<
  is_parameter_index_or_tag<IteratorOrTag>
, synchronize_iterator<Iterators..., IteratorOrTag>
>::type make_synchronize_iterator(IteratorOrTag x, Iterators... others)
{ return {x, others...}; }

}
}

#endif
