#ifndef FALCON_TYPE_TRAITS_IF_HPP
#define FALCON_TYPE_TRAITS_IF_HPP

#include <falcon/type_traits/integral_constant.hpp>

namespace falcon
{

/**
 * _TrueType if @p c equals true, otherwise _FalseType
 */
template<bool c, typename _TrueType, typename _FalseType>
struct if_
{ typedef _TrueType type; };

template<typename _TrueType, typename _FalseType>
struct if_<false, _TrueType, _FalseType>
{ typedef _FalseType type; };

/**
 * _FalseType if @p c equals true, otherwise _TrueType
 */
template<bool c, typename _TrueType, typename _FalseType>
struct not_if
{ typedef typename if_<!c, _TrueType, _FalseType>::type type;};

/**
 * shorcut notation for if_< _T::value, _TrueType, _FalseType>.
 */
template<typename _T, typename _TrueType, typename _FalseType>
struct if_c
{ typedef typename if_<_T::value, _TrueType, _FalseType>::type type; };

/**
 * shorcut notation for not_if< _T::value, _TrueType, _FalseType>.
 */
template<typename _T, typename _TrueType, typename _FalseType>
struct not_if_c
{ typedef typename if_<!_T::value, _TrueType, _FalseType>::type type; };

}

#endif