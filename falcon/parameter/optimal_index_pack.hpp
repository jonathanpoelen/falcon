#ifndef FALCON_PARAMETER_OPTIMALINDEX_PACK_HPP
#define FALCON_PARAMETER_OPTIMALINDEX_PACK_HPP

#include <falcon/parameter/pack_element.hpp>
#include <falcon/parameter/parameter_pack.hpp>
#include <falcon/parameter/parameter_index.hpp>
#include <falcon/parameter/parameter_element.hpp>
#include <falcon/parameter/keep_parameter_index.hpp>

namespace falcon {

template<typename T, std::size_t I>
struct __parameter_with_index
{
  typedef T __type;
  static const std::size_t __index = I;
  static const std::size_t __size = alignof(T);
};

template<typename Pack, typename PackWithIndex = parameter_pack<>, std::size_t I = 0>
struct __build_parameter_with_index;

template<typename... ElementsWithIndex, std::size_t I>
struct __build_parameter_with_index<
  parameter_pack<>,
  parameter_pack<ElementsWithIndex...>,
  I
>
{ typedef parameter_pack<ElementsWithIndex...> __type; };

template<typename T, typename... Elements, typename... ElementsWithIndex, std::size_t I>
struct __build_parameter_with_index<
  parameter_pack<T, Elements...>,
  parameter_pack<ElementsWithIndex...>,
  I
>
{
  typedef typename __build_parameter_with_index<
    parameter_pack<Elements...>,
    parameter_pack<__parameter_with_index<T, I>, ElementsWithIndex...>,
    I + 1
  >::__type __type;
};

template <std::size_t Size, std::size_t K, std::size_t I,
  typename T, typename... Elements>
struct __maximal_size_element
: __maximal_size_element<
  (Size > T::__size) ? Size : T::__size,
  (Size > T::__size) ? K : I,
  I + 1,
  Elements...
>::__type
{};

template <std::size_t Size, std::size_t K, std::size_t I, typename T>
struct __maximal_size_element<Size, K, I, T>
{
  static const std::size_t __value = (Size > T::__size) ? K : I;
  typedef __maximal_size_element __type;
};

template <typename Pack, typename Indexes = parameter_index<>>
struct __optimal_index_pack;

template <typename... Elements, std::size_t... Indexes>
struct __optimal_index_pack<
  parameter_pack<Elements...>,
  parameter_index<Indexes...>
>
{
  static const std::size_t __max_element = __maximal_size_element<
      0, 0, 0, Elements...
  >::__value;
  typedef parameter_pack<Elements...> __pack;
  typedef typename __optimal_index_pack<
    typename pack_element<
      __pack,
      typename keep_parameter_index<
        ignore_parameter_index_tag<__max_element>,
        sizeof...(Elements)
      >::type
    >::type,
    parameter_index<
      Indexes...,
      parameter_element<__max_element, __pack>::type::__index
    >
  >::__indexes __indexes;
};

template <std::size_t... Indexes>
struct __optimal_index_pack<parameter_pack<>, parameter_index<Indexes...>>
{ typedef parameter_index<Indexes...> __indexes; };

template<typename Pack>
struct optimal_index_pack
{
  typedef typename __optimal_index_pack<
    typename __build_parameter_with_index<Pack>::__type
  >::__indexes type;
};

}

#endif
