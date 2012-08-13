#ifndef _FALCON_FUNCTIONAL_CALL_PARTIAL_RECURSIVE_PARAM_HPP
#define _FALCON_FUNCTIONAL_CALL_PARTIAL_RECURSIVE_PARAM_HPP

#include <falcon/functional/call.hpp>
#include <falcon/parameter/manip.hpp>
#include <falcon/preprocessor/not_ide_parser.hpp>

namespace falcon {

template <bool, typename _PackIndexes, std::size_t _NumberArg, std::size_t _Current, std::size_t _End, typename _CurrentResult, typename _Function, typename... _Args>
struct __call_partial_recursive_param_loop_traits_impl;

template <std::size_t... _Indexes, std::size_t _NumberArg, std::size_t _Current, std::size_t _End, typename _CurrentResult, typename _Function, typename... _Args>
struct __call_partial_recursive_param_loop_traits_impl<
	true,
	parameter_index<_Indexes...>,
	_NumberArg,
	_Current,
	_End,
	_CurrentResult,
	_Function,
	_Args...
>
{
	static const std::size_t __stop = (_Current + _NumberArg - 1 < _End ? _Current + _NumberArg - 1 : _End);
	typedef typename build_range_parameter_index<
		_Current,
		__stop
	>::type __impl_indexes;
	typedef typename parameter::result_pack_of<
		_Function,
		typename parameter::pack_cat<
			parameter_pack<_CurrentResult&&>,
			typename parameter::pack_element<
				parameter_pack<_Args&&...>,
				__impl_indexes
			>::type
		>::type
	>::type __impl_result_type;
	typedef __call_partial_recursive_param_loop_traits_impl<
		true,
		__impl_indexes,
		_NumberArg,
		__stop,
		_End,
		__impl_result_type,
		_Function,
		_Args...
	> __impl;
	typedef typename __impl::__result_type __result_type;

	constexpr static __result_type __call(_Function& func, _CurrentResult&& v, _Args&&... args)
	{
		return __impl
		::__call(func,
				 func(std::forward<_CurrentResult>(v),
					  arg<_Indexes>(std::forward<_Args>(args)...)...),
				 std::forward<_Args>(args)...);
	}
};

template <std::size_t... _Indexes, std::size_t _NumberArg, std::size_t _End, typename _Function, typename _CurrentResult, typename... _Args>
struct __call_partial_recursive_param_loop_traits_impl<true, parameter_index<_Indexes...>, _NumberArg, _End, _End, _CurrentResult, _Function, _Args...>
{
	typedef parameter_index<_Indexes...> __indexes;
	typedef typename parameter::result_pack_of<
		_Function,
		typename parameter::pack_cat<
			parameter_pack<_CurrentResult&&>,
			typename parameter::pack_element<
				parameter_pack<_Args&&...>,
				__indexes
			>::type
		>::type
	>::type __result_type;

	typedef __call_partial_recursive_param_loop_traits_impl __impl;

	constexpr static __result_type __call(_Function& func, _CurrentResult&& v, _Args&&... args)
	{
		return func(std::forward<_CurrentResult>(v),
					arg<_Indexes>(std::forward<_Args>(args)...)...);
	}
};

struct __call_partial_recursive_param_loop_first_call;

template <std::size_t... _Indexes, std::size_t _NumberArg, typename _Function, typename... _Args>
struct __call_partial_recursive_param_loop_traits_impl<false, parameter_index<_Indexes...>, _NumberArg, 0, 0, _Function, __call_partial_recursive_param_loop_first_call, _Args...>
{
	typedef void __result_type;

	constexpr static __result_type __call(_Function&, _Args&&... FALCON_PP_NOT_IDE_PARSER())
	{}
};

template <std::size_t _NumberArg, std::size_t _End, typename _Function, typename... _Args>
struct __call_partial_recursive_param_loop_traits_impl<
	false,
	parameter_index<>,
	_NumberArg,
	0,
	_End,
	__call_partial_recursive_param_loop_first_call,
	_Function,
	_Args...
>
{
	static_assert(_NumberArg != 0 && !(_NumberArg == 1 && _End > 1), "_NumberArg != 0 && !(_NumberArg == 1 && _End > 1)");
	static const std::size_t __stop = (_NumberArg < _End ? _NumberArg : _End);
	typedef typename build_parameter_index<__stop>::type __impl_indexes;
	typedef typename __call_result_of<
		_Function,
		__impl_indexes,
		_Args...
	>::__type __result_type;

	constexpr static __result_type __call(_Function& func, _Args&&... args)
	{
		return call<_Function&>(__impl_indexes(),
								func, std::forward<_Args>(args)...);
	}
};

template <std::size_t _NumberArg, std::size_t _End, typename _Function, typename... _Args>
struct __call_partial_recursive_param_loop_traits_impl<
	true,
	parameter_index<>,
	_NumberArg,
	0,
	_End,
	__call_partial_recursive_param_loop_first_call,
	_Function,
	_Args...
>
{
	typedef __call_partial_recursive_param_loop_traits_impl<
		false,
		parameter_index<>,
		_NumberArg,
		0,
		_End,
		__call_partial_recursive_param_loop_first_call,
		_Function,
		_Args...
	> __basic_type;
	typedef typename __basic_type::__impl_indexes __impl_indexes;
	typedef typename __basic_type::__result_type __impl_result_type;
	typedef __call_partial_recursive_param_loop_traits_impl<
		true,
		__impl_indexes,
		_NumberArg,
		__basic_type::__stop,
		_End,
		__impl_result_type,
		_Function,
		_Args...
	> __next_impl;
	typedef typename __next_impl::__result_type __result_type;

	constexpr static __result_type __call(_Function& func, _Args&&... args)
	{
		return __next_impl::__impl
		::__call(func,
				 call<_Function&>(__impl_indexes(),
								  func, std::forward<_Args>(args)...),
				 std::forward<_Args>(args)...);
	}
};

template<std::size_t _NumberArg, typename _Function, typename... _Args>
struct __call_partial_recursive_param_loop_traits
{
	typedef __call_partial_recursive_param_loop_traits_impl<
		(sizeof...(_Args) > _NumberArg),
		parameter_index<>,
		_NumberArg,
		0,
		sizeof...(_Args),
		__call_partial_recursive_param_loop_first_call,
		_Function,
		_Args...
	> __impl;
	typedef typename __impl::__result_type __result_type;
};

/**
 * \brief Call \c func with \c _NumberArg arguments. The return of \c func is the first argument of next call.
 * \return Last operations.
 *
 * \code
 * int n = call_partial_param_loop<2>(accu_t(), 1,2,3,4,5,6);
 * \endcode
 * equivalent to
 * \code
 * accu_t accu;
 * int n = accu(accu(accu(accu(accu(1,2),3),4),5),6);
 * \endcode
 *
 * \ingroup call-arguments
 */
template<std::size_t _NumberArg, typename _Function, typename... _Args, typename _Traits = __call_partial_recursive_param_loop_traits<_NumberArg, _Function, _Args...>>
constexpr typename _Traits::__result_type call_partial_recursive_param_loop(_Function func, _Args&&... args)
{
	return _Traits::__impl::__call(func, std::forward<_Args>(args)...);
}

}

#endif
