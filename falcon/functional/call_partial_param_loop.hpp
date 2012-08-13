#ifndef _FALCON_FUNCTIONAL_CALL_PARTIAL_PARAM_LOOP_HPP
#define _FALCON_FUNCTIONAL_CALL_PARTIAL_PARAM_LOOP_HPP

#include <utility>
#include <falcon/arg/arg.hpp>
#include <falcon/functional/call.hpp>
#include <falcon/parameter/parameter_index.hpp>
#include <falcon/parameter/manip.hpp>

namespace falcon {

template <typename _Indexes, std::size_t _NumberArg, std::size_t _Current, std::size_t _End, typename _Function, typename... _Args>
struct __call_partial_param_loop_traits_impl;

template <std::size_t... _Indexes, std::size_t _NumberArg, std::size_t _Current, std::size_t _End, typename _Function, typename... _Args>
struct __call_partial_param_loop_traits_impl<parameter_index<_Indexes...>, _NumberArg, _Current, _End, _Function, _Args...>
{
	static const std::size_t __stop = (_Current + _NumberArg < _End ? _Current + _NumberArg : _End);
	typedef __call_partial_param_loop_traits_impl<
		typename build_range_parameter_index<_Current, __stop>::type,
		_NumberArg,
		__stop,
		_End,
		_Function,
		_Args...
	> __impl;
	typedef typename __impl::__result_type __result_type;

	static __result_type __call(_Function& func, _Args&&... args)
	{
		func(arg<_Indexes>(std::forward<_Args>(args)...)...);
		return __impl::__call(func, std::forward<_Args>(args)...);
	}
};

template <std::size_t... _Indexes, std::size_t _NumberArg, std::size_t _End, typename _Function, typename... _Args>
struct __call_partial_param_loop_traits_impl<parameter_index<_Indexes...>, _NumberArg, _End, _End, _Function, _Args...>
{
	typedef parameter_index<_Indexes...> __indexes;
	typedef typename __call_result_of<
		_Function,
		__indexes,
		_Args...
	>::__type __result_type;

	typedef __call_partial_param_loop_traits_impl __impl;

	constexpr static __result_type __call(_Function& func, _Args&&... args)
	{
		return func(arg<_Indexes>(std::forward<_Args>(args)...)...);
	}
};

template <std::size_t _End, typename _Function, typename... _Args>
struct __call_partial_param_loop_traits_impl<parameter_pack<>, 0, 0, _End, _Function, _Args...>
: __call_partial_param_loop_traits_impl<parameter_pack<>, 0, 0, 0, _Function, _Args...>
{};

template <typename _Function, typename... _Args>
struct __call_partial_param_loop_traits_impl<parameter_pack<>, 0, 0, 0, _Function, _Args...>
{
	typedef parameter_pack<> __indexes;
	typedef void __result_type;

	typedef __call_partial_param_loop_traits_impl __impl;

	constexpr static void __call(_Function&)
	{}
};

template<std::size_t _NumberArg, typename _Function, typename... _Args>
struct __call_partial_param_loop_traits
{
	typedef __call_partial_param_loop_traits_impl<
		parameter_index<>,
		_NumberArg,
		0,
		sizeof...(_Args),
		_Function,
		_Args...
	> __traits_impl;
	typedef typename __traits_impl::__impl __impl;
	typedef typename __traits_impl::__result_type __result_type;
};

/**
 * \brief Call \c func with \c _NumberArg arguments at the same time.
 * \return Last operations.
 *
 * \code
 * int n = call_partial_param_loop<2>(accu_t(), 1,2,3,4,5,6);
 * \endcode
 * equivalent to
 * \code
 * accu_t accu;
 * accu(1,2);
 * accu(3,4);
 * int n = accu(5,6);
 * \endcode
 *
 * \ingroup call-arguments
 */
template<std::size_t _NumberArg, typename _Function, typename... _Args,
typename _Traits = __call_partial_param_loop_traits<_NumberArg, _Function, _Args...>>
constexpr typename _Traits::__result_type call_partial_param_loop(_Function func, _Args&&... args)
{
	return _Traits::__impl::__call(func, std::forward<_Args>(args)...);
}

}

#endif
