#ifndef _FALCON_TUPLE_TUPLE_COMPOSE_HPP
#define _FALCON_TUPLE_TUPLE_COMPOSE_HPP

#include <tuple>
#include <type_traits>
#include <falcon/tuple/tuple_apply.hpp>
#include <falcon/type_traits/cv_selector.hpp>
#include <falcon/tuple/parameter_index.hpp>

namespace falcon {

template <std::size_t _I, std::size_t _N, typename _Function,
	typename _Tuple, typename _TupleArgs, typename _Indexes
>
struct __tuple_compose_base
{
	typedef typename match_cv_qualifiers<
		_Tuple,
		typename std::tuple_element<
			_I,
			typename std::remove_cv<_Tuple>::type
		>::type
	>::type __func_type;
	typedef __tuple_compose_base<
		_I+1, _N,
		_Function, _Tuple,
		_TupleArgs, _Indexes
	> __impl;

	template<typename... _Args>
	struct _Result_type
	{
		typedef typename __impl:: template _Result_type<
			_Args...,
			decltype(tuple_apply<__func_type&>(
				_Indexes(), std::declval<__func_type&>(), std::declval<_TupleArgs&>()
			))
		>::__type __type;
	};

	typedef typename _Result_type<>::__type __result_type;

	template<typename... _Args>
	constexpr static __result_type
	__call(_Function& __func, _Tuple& __t,
		   _TupleArgs& __targs, _Args&&... __args)
	{
		return __impl::__call(__func, __t, __targs,
							  std::forward<_Args>(__args)...,
							  tuple_apply<__func_type&>(_Indexes(),
														std::get<_I>(__t),
														__targs));
	}
};

template <std::size_t _N, typename _Function,
	typename _Tuple, typename _TupleArgs, typename _Indexes
>
struct __tuple_compose_base<_N, _N, _Function, _Tuple, _TupleArgs, _Indexes>
{
	template<typename... _Args>
	struct _Result_type
	{
		typedef decltype(std::declval<_Function&>()(std::declval<_Args&&>()...)) __type;
	};

	template<typename... _Args>
	constexpr static decltype(std::declval<_Function&>()(std::declval<_Args&&>()...))
	__call(_Function& __func, _Tuple&,
		   _TupleArgs&, _Args&&... __args)
	{
		return __func(std::forward<_Args>(__args)...);
	}
};


template <typename _OperationsForSize,
	typename _Operations, typename _Function, typename _ArgElements,
	typename _Indexes = typename build_tuple_index<_ArgElements>::type
>
struct __tuple_compose
: __tuple_compose_base<
	0, std::tuple_size<_Operations>::value, _Function,
	_Operations, _ArgElements,
	_Indexes
>
{};


/**
 * \brief Call functors on tuple
 *
 * \param _Indexes... indexes arguments of @p targs
 * \param func functor for the results of @p t
 * \param t tuple functor
 * \param targs tuple arguments for each element of @p t
 *
 * \code
 * int answer = (tuple_compose(parameter_index<0,2>(),
 *                             f, std::forward_as_tuple(g1,g2,g3),
 *                             std::forward_as_tuple(x,y,z));
 * \endcode
 * is equivalent to
 * \code
 * int temp1 = g1(x,z);
 * int temp2 = g2(x,z);
 * int temp3 = g3(x,z);
 * int answer = f(temp1,temp2,temp3);
 * \endcode
 * @{
 */
template <typename _Function, typename _Operations,
	typename _ArgElements, std::size_t... _Indexes>
constexpr typename __tuple_compose<
	_Operations, _Operations, _Function, _ArgElements,
	parameter_index<_Indexes...>
>::__result_type
tuple_compose(const parameter_index<_Indexes...>&, _Function __func,
			  _Operations& __t, _ArgElements& __targs)
{
	return __tuple_compose<
		_Operations, _Operations, _Function, _ArgElements,
		parameter_index<_Indexes...>
	>::__call(__func, __t, __targs);
}

template <typename _Function, typename _Operations,
	typename _ArgElements, std::size_t... _Indexes>
constexpr typename __tuple_compose<
	_Operations, const _Operations, _Function, _ArgElements,
	parameter_index<_Indexes...>
>::__result_type
tuple_compose(const parameter_index<_Indexes...>&, _Function __func,
			  const _Operations& __t, _ArgElements& __targs)
{
	return __tuple_compose<
		_Operations, const _Operations, _Function, _ArgElements,
		parameter_index<_Indexes...>
	>::__call(__func, __t, __targs);
}

template <typename _Function, typename _Operations,
	typename _ArgElements, std::size_t... _Indexes>
constexpr typename __tuple_compose<
	_Operations, _Operations, _Function, const _ArgElements,
	parameter_index<_Indexes...>
>::__result_type
tuple_compose(const parameter_index<_Indexes...>&, _Function __func,
			  _Operations& __t, const _ArgElements& __targs)
{
	return __tuple_compose<
		_Operations, _Operations, _Function, const _ArgElements,
		parameter_index<_Indexes...>
	>::__call(__func, __t, __targs);
}

template <typename _Function, typename _Operations,
	typename _ArgElements, std::size_t... _Indexes>
constexpr typename __tuple_compose<
	_Operations, const _Operations, _Function, const _ArgElements,
	parameter_index<_Indexes...>
>::__result_type
tuple_compose(const parameter_index<_Indexes...>&, _Function __func,
			  const _Operations& __t, const _ArgElements& __targs)
{
	return __tuple_compose<
		_Operations, const _Operations, _Function, const _ArgElements,
		parameter_index<_Indexes...>
	>::__call(__func, __t, __targs);
}


template <typename _Function, typename _Operations>
constexpr typename __tuple_compose<
	_Operations, _Operations, _Function, const std::tuple<>
>::__result_type
tuple_compose(_Function __func, _Operations& __t)
{
	return __tuple_compose<
		_Operations, _Operations, _Function, const std::tuple<>
	>::__call(__func, __t, std::tuple<>());
}

template <typename _Function, typename _Operations>
constexpr typename __tuple_compose<
	_Operations, const _Operations, _Function, const std::tuple<>
>::__result_type
tuple_compose(_Function __func, const _Operations& __t)
{
	return __tuple_compose<
		_Operations, const _Operations, _Function, const std::tuple<>
	>::__call(__func, __t, std::tuple<>());
}


template <typename _Function, typename _Operations,
	typename _ArgElements>
constexpr typename __tuple_compose<
	_Operations, _Operations, _Function, _ArgElements
>::__result_type
tuple_compose(_Function __func, _Operations& __t, _ArgElements& __targs)
{
	return __tuple_compose<
		_Operations, _Operations, _Function, _ArgElements
	>::__call(__func, __t, __targs);
}

template <typename _Function, typename _Operations,
	typename _ArgElements>
constexpr typename __tuple_compose<
	_Operations, const _Operations, _Function, _ArgElements
>::__result_type
tuple_compose(_Function __func, const _Operations& __t, _ArgElements& __targs)
{
	return __tuple_compose<
		_Operations, const _Operations, _Function, _ArgElements
	>::__call(__func, __t, __targs);
}

template <typename _Function, typename _Operations,
	typename _ArgElements>
constexpr typename __tuple_compose<
	_Operations, _Operations, _Function, const _ArgElements
>::__result_type
tuple_compose(_Function __func, _Operations& __t, const _ArgElements& __targs)
{
	return __tuple_compose<
		_Operations, _Operations, _Function, const _ArgElements
	>::__call(__func, __t, __targs);
}

template <typename _Function, typename _Operations,
	typename _ArgElements>
constexpr typename __tuple_compose<
	_Operations, const _Operations, _Function, const _ArgElements
>::__result_type
tuple_compose(_Function __func, const _Operations& __t, const _ArgElements& __targs)
{
	return __tuple_compose<
		_Operations, const _Operations, _Function, const _ArgElements
	>::__call(__func, __t, __targs);
}
//@}

}

#endif