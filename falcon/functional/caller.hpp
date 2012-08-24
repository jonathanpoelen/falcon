#ifndef _FALCON_FUNCTIONAL_CALLER_HPP
#define _FALCON_FUNCTIONAL_CALLER_HPP

#include <falcon/functional/call.hpp>
#include <falcon/functional/call_partial_param_loop.hpp>
#include <falcon/functional/call_partial_recursive_param_loop.hpp>
#include <falcon/parameter/keep_parameter_index.hpp>

namespace falcon {

///\brief Tag for used @p call_partial_param_loop() with @c caller
template<std::size_t _NumberArg>
struct caller_partial_param_loop_tag {};

///\brief Tag for used @p call_partial_recursive_param_loop() with @c caller
template<std::size_t _NumberArg>
struct caller_partial_recursive_param_loop_tag {};


/**
 * \brief Functor for used \link call-arguments \p call(), \p call_partial_param_loop() and \p call_partial_recursive_param_loop() \endlink
 *
 * Tag is \p caller_partial_param_loop_tag for used \p call_partial_param_loop(), \p caller_partial_recursive_param_loop_tag for used \p call_partial_recursive_param_loop(), each tag of \link indexes-tag indexes-tag \endlink or \p parameter_index
 * @{
 */
template <typename _Functor, typename _Tag = full_parameter_index_tag>
struct caller
{
	_Functor _M_func;

private:
	typename parameter_index_or_tag_to_tag<_Tag>::type __tag;

public:
	template<typename... _Args, typename _BuildIndexes = typename keep_parameter_index<__tag, sizeof...(_Args)>::type>
	constexpr typename __call_result_of<
		const _Functor,
		_BuildIndexes,
		_Args...
	>::__type operator()(_Args&&... args) const
	{
		return call<const _Functor&>(_BuildIndexes(), _M_func,
									 std::forward<_Args>(args)...);
	}

	template<typename... _Args, typename _BuildIndexes = typename keep_parameter_index<__tag, sizeof...(_Args)>::type>
	typename __call_result_of<
		_Functor,
		_BuildIndexes,
		_Args...
	>::__type operator()(_Args&&... args)
	{
		return call<_Functor&>(_BuildIndexes(), _M_func,
							   std::forward<_Args>(args)...);
	}
};

template <typename _Functor, std::size_t _NumberArg>
struct caller<_Functor, caller_partial_param_loop_tag<_NumberArg>>
{
	_Functor _M_func;

	template<typename... _Args>
	constexpr typename __call_partial_param_loop_traits<_NumberArg, const _Functor, _Args...>::__result_type operator()(_Args&&... args) const
	{
		return call_partial_param_loop<_NumberArg, const _Functor&>(
			_M_func, std::forward<_Args>(args)...);
	}

	template<typename... _Args>
	typename __call_partial_param_loop_traits<_NumberArg, _Functor, _Args...>::__result_type operator()(_Args&&... args)
	{
		return call_partial_param_loop<_NumberArg, _Functor&>(
			_M_func, std::forward<_Args>(args)...);
	}
};

template <typename _Functor, std::size_t _NumberArg>
struct caller<_Functor, caller_partial_recursive_param_loop_tag<_NumberArg>>
{
	_Functor _M_func;

	template<typename... _Args>
	constexpr typename __call_partial_recursive_param_loop_traits<_NumberArg, const _Functor, _Args...>::__result_type operator()(_Args&&... args) const
	{
		return call_partial_recursive_param_loop<_NumberArg, const _Functor&>(
			_M_func, std::forward<_Args>(args)...);
	}

	template<typename... _Args>
	typename __call_partial_recursive_param_loop_traits<_NumberArg, _Functor, _Args...>::__result_type operator()(_Args&&... args)
	{
		return call_partial_recursive_param_loop<_NumberArg, _Functor&>(
			_M_func, std::forward<_Args>(args)...);
	}
};

//@}

}

namespace std {
template <typename _Functor, typename _Tag>
void swap(falcon::caller<_Functor, _Tag>& a, falcon::caller<_Functor, _Tag>& b)
{
	std::swap(a._M_func, b._M_func);
}
}

#endif
