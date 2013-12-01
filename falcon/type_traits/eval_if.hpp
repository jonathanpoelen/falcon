#ifndef FALCON_TYPE_TRAITS_EVAL_IF_HPP
#define FALCON_TYPE_TRAITS_EVAL_IF_HPP

#include <falcon/type_traits/if.hpp>

namespace falcon
{

/**
 * TrueClass::type if c equals true, otherwise FalseClass::type.
 */
template<bool c, class TrueClass, class FalseClass>
struct eval_if
{
	typedef typename if_<c, TrueClass, FalseClass>::type::type type;
};

/**
 * FalseClass::type if c equals true, otherwise TrueClass::type.
 */
template<bool c, class TrueClass, class FalseClass>
struct eval_not_if
{
  typedef typename eval_if<!c, TrueClass, FalseClass>::type type;
};

/**
 * shorcut notation for eval_if< T::value, TrueType, _FalseType>.
 */
template<class T, class TrueClass, class FalseClass>
struct eval_if_c
{
  typedef typename eval_if<T::value, TrueClass, FalseClass>::type type;
};

/**
 * shorcut notation for eval_not_if< T::value, TrueType, _FalseType>.
 */
template<class T, class TrueClass, class FalseClass>
struct eval_not_if_c
{
  typedef typename eval_if<!T::value, TrueClass, FalseClass>::type type;
};

#if __cplusplus >= 201103L
template<bool c, class TrueClass, class FalseClass>
using eval_if_t = typename eval_if<c, TrueClass, FalseClass>::type;

template<bool c, class TrueClass, class FalseClass>
using eval_not_if_t = typename eval_not_if<c, TrueClass, FalseClass>::type;

template<class T, class TrueClass, class FalseClass>
using eval_if_c_t = typename eval_if_c<T, TrueClass, FalseClass>::type;

template<class T, class TrueClass, class FalseClass>
using eval_not_if_c_t = typename eval_not_if_c<T, TrueClass, FalseClass>::type;
#endif



}

#endif
