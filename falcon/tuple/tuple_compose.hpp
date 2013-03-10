#ifndef _FALCON_TUPLE_TUPLE_COMPOSE_HPP
#define _FALCON_TUPLE_TUPLE_COMPOSE_HPP

#include <tuple>
#include <type_traits>
#include <falcon/tuple/tuple_apply.hpp>
#include <falcon/type_traits/cv_selector.hpp>
#include <falcon/parameter/result_pack_of.hpp>
#include <falcon/parameter/manip.hpp>

namespace falcon {

template <std::size_t _I, typename _Tuple>
struct __tuple_compose_function
{
	typedef typename match_cv_qualifiers<
		_Tuple,
		typename std::tuple_element<
			_I,
			typename std::decay<
				typename std::remove_cv<_Tuple>::type
			>::type
		>::type
	>::type __type;
};

template<typename _Function, typename _Tuple, typename _TupleArgs, typename _Indexes,
	typename _IndexElements = typename build_tuple_index<typename std::decay<_Tuple>::type>::type>
class __tuple_compose_result;

template<typename _Function, typename _Tuple, typename _TupleArgs, typename _Indexes,
	std::size_t... _IndexElements>
struct __tuple_compose_result<
	_Function, _Tuple, _TupleArgs, _Indexes, parameter_index<_IndexElements...>>
{
	template<std::size_t _I>
	struct __result_element
	{
		typedef typename __tuple_compose_function<_I, _Tuple>::__type __func_type;
		typedef decltype(tuple_apply(
			_Indexes(), std::declval<__func_type>(), std::declval<_TupleArgs>()
		)) type;
	};

	typedef typename parameter::pack_use_type<
		parameter_pack<__result_element<_IndexElements>...>
	>::type __pack;
	typedef typename parameter::result_pack_of<_Function, __pack>::type __type;
};

template <std::size_t _I, std::size_t _N, typename _Function,
	typename _Tuple, typename _TupleArgs, typename _Indexes,
	typename _Result = typename __tuple_compose_result<
		_Function, _Tuple, _TupleArgs, _Indexes
	>::__type
>
struct __tuple_compose_base
{
	typedef _Result __result_type;

	template<typename... _Args>
	constexpr static _Result
	__call(_Function&& __func, _Tuple&& __t, _TupleArgs&& __targs, _Args&&... __args)
	{
		return __tuple_compose_base<
			_I+1, _N,
			_Function, _Tuple,
			_TupleArgs, _Indexes,
			_Result
		>::__call(std::forward<_Function>(__func),
							std::forward<_Tuple>(__t),
							std::forward<_TupleArgs>(__targs),
							std::forward<_Args>(__args)...,
							tuple_apply(_Indexes(),
													std::get<_I>(std::forward<_Tuple>(__t)),
													std::forward<_TupleArgs>(__targs)));
	}
};

template <std::size_t _N, typename _Function,
	typename _Tuple, typename _TupleArgs, typename _Indexes, typename _Result
>
struct __tuple_compose_base<_N, _N, _Function, _Tuple, _TupleArgs, _Indexes, _Result>
{
	typedef _Result __result_type;

	template<typename... _Args>
	constexpr static _Result
	__call(_Function&& __func, _Tuple&&, _TupleArgs&&, _Args&&... __args)
	{ return __func(std::forward<_Args>(__args)...); }
};


template <typename _Operations,
	typename _Function, typename _ArgElements,
	typename _Indexes = typename build_tuple_index<typename std::decay<_ArgElements>::type>::type
>
struct __tuple_compose
: __tuple_compose_base<
	0,
	std::tuple_size<typename std::decay<_Operations>::type>::value,
	_Function,
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
 * int answer = tuple_compose(parameter_index<0,2>(),
 *                            function,
 *                            std::forward_as_tuple(g1,g2,g3),
 *                            std::forward_as_tuple(x,y,z));
 * \endcode
 * is equivalent to
 * \code
 * int temp1 = g1(x,z);
 * int temp2 = g2(x,z);
 * int temp3 = g3(x,z);
 * int answer = function(temp1,temp2,temp3);
 * \endcode
 * @{
 */
template <typename _Function, typename _Operations,
	typename _ArgElements, std::size_t... _Indexes>
constexpr typename __tuple_compose<
	_Operations, _Function, _ArgElements,
	parameter_index<_Indexes...>
>::__result_type
tuple_compose(const parameter_index<_Indexes...>&,
							_Function&& __func,
							_Operations&& __t,
							_ArgElements&& __targs)
{
	return __tuple_compose<
		_Operations, _Function, _ArgElements,
		parameter_index<_Indexes...>
		>::__call(std::forward<_Function>(__func));
}


template <typename _Function, typename _Operations>
constexpr typename __tuple_compose<
	_Operations, _Function, const std::tuple<>
>::__result_type
tuple_compose(_Function&& __func, _Operations&& __t)
{
	return __tuple_compose<
		_Operations, _Function, const std::tuple<>
	>::__call(std::forward<_Function>(__func),
						std::forward<_Operations>(__t),
						std::tuple<>());
}


template <typename _Function, typename _Operations,
	typename _ArgElements>
constexpr typename __tuple_compose<
	_Operations, _Function, _ArgElements
>::__result_type
tuple_compose(_Function&& __func, _Operations&& __t, _ArgElements&& __targs)
{
	return __tuple_compose<
		_Operations, _Function, _ArgElements
	>::__call(std::forward<_Function>(__func),
						std::forward<_Operations>(__t),
						std::forward<_ArgElements>(__targs));
}
//@}

}

#endif