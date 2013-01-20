#ifndef FALCON_TYPE_TRAITS_BUILD_CLASS_HPP
#define FALCON_TYPE_TRAITS_BUILD_CLASS_HPP

#include <falcon/parameter/parameter_pack.hpp>

namespace falcon
{

template <template<typename...> class _W, typename _Pack>
class __build_class;

template <template<typename...> class _W, typename... _Elements>
struct __build_class<_W, parameter_pack<_Elements...>>
{ typedef _W<_Elements...> type; };

template <template<typename...> class _W, typename _Pack>
struct build_class
{ typedef typename __build_class<_W, _Pack>::type type; };

template <template<typename...> class _W, typename... _Elements>
struct build_class2
{ typedef _W<_Elements...> type; };

template <typename _T, template<_T...> class _W, typename _Pack>
class __build_class_by_value;

template <typename _T, template<_T...> class _W, typename... _Elements>
struct __build_class_by_value<_T, _W, parameter_pack<_Elements...>>
{ typedef _W<_Elements::value...> type; };

template <typename _T, template<_T...> class _W, typename _Pack>
struct build_class_by_value
{ typedef typename __build_class_by_value<_T, _W, _Pack>::type type; };

}

#endif