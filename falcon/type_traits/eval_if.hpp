#ifndef FALCON_TYPE_TRAITS_EVAL_IF_HPP
#define FALCON_TYPE_TRAITS_EVAL_IF_HPP

#include <falcon/type_traits/if.hpp>

namespace falcon
{

/**
 * _TrueClass::type if c equals true, otherwise _FalseClass::type.
 */
template<bool c, class _TrueClass, class _FalseClass>
struct eval_if
{
	typedef typename if_<c, _TrueClass, _FalseClass>::type __base;
	typedef typename __base::type type;
};

/**
 * _FalseClass::type if c equals true, otherwise _TrueClass::type.
 */
template<bool c, class _TrueClass, class _FalseClass>
struct eval_not_if
: eval_if<!c, _TrueClass, _FalseClass>
{};

/**
 * shorcut notation for eval_if< _T::value, _TrueType, _FalseType>.
 */
template<class _T, class _TrueClass, class _FalseClass>
struct eval_if_c
: eval_if<_T::value, _TrueClass, _FalseClass>
{};

/**
 * shorcut notation for eval_not_if< _T::value, _TrueType, _FalseType>.
 */
template<class _T, class _TrueClass, class _FalseClass>
struct eval_not_if_c
: eval_if<!_T::value, _TrueClass, _FalseClass>
{};

}

#endif