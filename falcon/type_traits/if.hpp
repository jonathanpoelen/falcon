#ifndef FALCON_TYPE_TRAITS_IF_HPP
#define FALCON_TYPE_TRAITS_IF_HPP

#include <falcon/type_traits/integral_constant.hpp>

namespace falcon
{

/**
 * TrueType if @p c equals true, otherwise FalseType
 */
template<bool c, typename TrueType, typename FalseType>
struct if_
{ typedef TrueType type; };

template<typename TrueType, typename FalseType>
struct if_<false, TrueType, FalseType>
{ typedef FalseType type; };

/**
 * FalseType if @p c equals true, otherwise TrueType
 */
template<bool c, typename TrueType, typename FalseType>
struct not_if
{ typedef typename if_<!c, TrueType, FalseType>::type type;};

/**
 * shorcut notation for if_< T::value, TrueType, FalseType>.
 */
template<typename T, typename TrueType, typename FalseType>
struct if_c
{ typedef typename if_<T::value, TrueType, FalseType>::type type; };

/**
 * shorcut notation for not_if< T::value, TrueType, FalseType>.
 */
template<typename T, typename TrueType, typename FalseType>
struct not_if_c
{ typedef typename if_<!T::value, TrueType, FalseType>::type type; };

}

#endif
