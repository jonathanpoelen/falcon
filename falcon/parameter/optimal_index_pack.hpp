#ifndef FALCON_PARAMETER_OPTIMAL_INDEX_PACK_HPP
#define FALCON_PARAMETER_OPTIMAL_INDEX_PACK_HPP

#include <falcon/parameter/parameter_pack.hpp>
#include <falcon/parameter/parameter_index.hpp>

namespace falcon {

template<typename _T, std::size_t _I>
struct __parameter_with_index
{
  typedef _T __type;
  static const std::size_t __index = _I;
  static const std::size_t __size = alignof(_T);
};

template<typename _Pack, typename _PackWithIndex = parameter_pack<>, std::size_t _I = 0>
struct __build_parameter_with_index;

template<typename... _ElementsWithIndex, std::size_t _I>
struct __build_parameter_with_index<
  parameter_pack<>,
  parameter_pack<_ElementsWithIndex...>,
  _I
>
{ typedef parameter_pack<_ElementsWithIndex...> __type; };

template<typename _T, typename... _Elements, typename... _ElementsWithIndex, std::size_t _I>
struct __build_parameter_with_index<
  parameter_pack<_T, _Elements...>,
  parameter_pack<_ElementsWithIndex...>,
  _I
>
{
  typedef typename __build_parameter_with_index<
    parameter_pack<_Elements...>,
    parameter_pack<__parameter_with_index<_T, _I>, _ElementsWithIndex...>,
    _I + 1
  >::type type;
};

template <std::size_t _Size, std::size_t _K, std::size_t _I,
  typename _T, typename... _Elements>
struct __maximal_size_element
{
  typedef typename __maximal_size_element<
    (_Size > _T::__size) ? _Size : _T::__size,
    (_Size > _T::__size) ? _K : _I,
    _I + 1,
    _Elements...
  >::type type;
};

template <std::size_t _Size, std::size_t _K, std::size_t _I, typename _T>
struct __maximal_size_element<_Size, _K, _I, _T>
{ static const std::size_t __value = (_Size > _T::__size) ? _K : _I; };

template <typename _Pack, typename _Indexes = parameter_index<>>
struct __optimal_index_pack;

template <typename... _Elements, std::size_t... _Indexes>
struct __optimal_index_pack<
  parameter_pack<_Elements...>,
  parameter_index<_Indexes...>
>
{
  static const std::size_t __max_element = __maximal_size_element<
      0, 0, 0, _Elements...
  >::__value;
  typedef parameter_pack<_Elements...> __pack;
  typedef typename __optimal_index_pack<
    typename parameter::pack_element<
      __pack,
      typename keep_parameter_index<
        ignore_parameter_index_tag<__max_element>,
        sizeof...(_Elements)
      >::type
    >::type,
    parameter_index<
      _Indexes...,
      parameter_element<__max_element, __pack>::type::__index
    >
  >::__indexes __indexes;
};

template <std::size_t... _Indexes>
struct __optimal_index_pack<parameter_pack<>, parameter_index<_Indexes...>>
{ typedef parameter_index<_Indexes...> __indexes; };

template<typename _Pack>
struct optimal_index_pack
{
  typedef typename __optimal_index_pack<
    typename __build_parameter_with_index<_Pack>::__type
  >::__indexes type;
};

}

#endif
