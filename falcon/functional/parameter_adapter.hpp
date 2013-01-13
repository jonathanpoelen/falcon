#ifndef FALCON_FUNCTIONAL_PARAMETER_ADAPTER_HPP
#define FALCON_FUNCTIONAL_PARAMETER_ADAPTER_HPP

#include <falcon/functional/call.hpp>
#include <falcon/functional/call_partial_param_loop.hpp>
#include <falcon/functional/call_partial_recursive_param_loop.hpp>
#include <falcon/parameter/keep_parameter_index.hpp>

namespace falcon {

///\brief Tag for used @p call_partial_param_loop() with @c parameter_adapter
template<std::size_t _NumberArg>
struct call_partial_param_loop_tag {};

///\brief Tag for used @p call_partial_recursive_param_loop() with @c parameter_adapter
template<std::size_t _NumberArg>
struct call_partial_recursive_param_loop_tag {};


/**
 * \brief Functor for used \link call-arguments \p call(), \p call_partial_param_loop() and \p call_partial_recursive_param_loop() \endlink
 *
 * Tag is \p call_partial_param_loop_tag for used \p call_partial_param_loop(), \p call_partial_recursive_param_loop_tag for used \p call_partial_recursive_param_loop(), each tag of \link indexes-tag indexes-tag \endlink or \p parameter_index
 * @{
 */
template <typename _Functor, typename _Tag = full_parameter_index_tag>
struct parameter_adapter
{
	_Functor _M_func;

private:
	typedef typename parameter_index_or_tag_to_tag<_Tag>::type __tag;

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

	void swap(parameter_adapter& other)
	{ std::swap(_M_func, other._M_func); }

	template<typename _Tag2>
	void swap(parameter_adapter<_Functor, _Tag2>& other)
	{ std::swap(_M_func, other._M_func); }
};

template <typename _Functor, std::size_t _NumberArg>
struct parameter_adapter<_Functor, call_partial_param_loop_tag<_NumberArg>>
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

	void swap(parameter_adapter& other)
	{ std::swap(_M_func, other._M_func); }

	template<typename _Tag2>
	void swap(parameter_adapter<_Functor, _Tag2>& other)
	{ std::swap(_M_func, other._M_func); }
};

template <typename _Functor, std::size_t _NumberArg>
struct parameter_adapter<_Functor, call_partial_recursive_param_loop_tag<_NumberArg>>
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

	void swap(parameter_adapter& other)
	{ std::swap(_M_func, other._M_func); }

	template<typename _Tag2>
	void swap(parameter_adapter<_Functor, _Tag2>& other)
	{ std::swap(_M_func, other._M_func); }
};

//@}

}

namespace std {
template <typename _Functor, typename _Tag>
void swap(falcon::parameter_adapter<_Functor, _Tag>& a, falcon::parameter_adapter<_Functor, _Tag>& b)
{ a.swap(b); }
template <typename _Functor, typename _Tag, typename _Tag2>
void swap(falcon::parameter_adapter<_Functor, _Tag>& a, falcon::parameter_adapter<_Functor, _Tag2>& b)
{ a.swap(b); }
}

#endif
