#ifndef _FALCON_FUNCTIONAL_SPECIAL_CALL_HPP
#define _FALCON_FUNCTIONAL_SPECIAL_CALL_HPP

#include <falcon/functional/call.hpp>
#include <falcon/parameter/keep_parameter_index.hpp>

namespace falcon {

/**
 * \ingroup call-arguments
 * @{
 */
/**
 * \brief Specification of \p call()
 * @{
 */
template<std::size_t _Keep = 1, typename _Function, typename... _Args,
typename _Indexes = typename keep_parameter_index<
	first_parameter_index_tag<_Keep>, sizeof...(_Args)
>::type>
constexpr typename __call_result_of<_Function, _Indexes, _Args...>::__type
call_first_param(_Function func, _Args&&... args)
{
	return call<_Function&>(_Indexes(), func, std::forward<_Args>(args)...);
}

template<std::size_t _Keep = 1, typename _Function, typename... _Args,
typename _Indexes = typename keep_parameter_index<
	last_parameter_index_tag<_Keep>, sizeof...(_Args)
>::type>
constexpr typename __call_result_of<_Function, _Indexes, _Args...>::__type
call_last_param(_Function func, _Args&&... args)
{
	return call<_Function&>(_Indexes(), func, std::forward<_Args>(args)...);
}

template<std::size_t _Start, std::size_t _Len, typename _Function, typename... _Args,
typename _Indexes = typename keep_parameter_index<
	range_parameter_index_tag<_Start, _Len>, sizeof...(_Args)
>::type>
constexpr typename __call_result_of<_Function, _Indexes, _Args...>::__type
call_range_param(_Function func, _Args&&... args)
{
	return call<_Function&>(_Indexes(), func, std::forward<_Args>(args)...);
}

template<std::size_t _Pos, std::size_t _Ignore = 1, typename _Function, typename... _Args,
typename _Indexes = typename keep_parameter_index<
	ignore_parameter_index_tag<_Pos, _Ignore>, sizeof...(_Args)
>::type>
constexpr typename __call_result_of<_Function, _Indexes, _Args...>::__type
call_ignore_param(_Function func, _Args&&... args)
{
	return call<_Function&>(_Indexes(), func, std::forward<_Args>(args)...);
}

template<std::size_t _Start = 0, std::size_t _Len = -1, typename _Function, typename... _Args,
typename _Indexes = typename keep_parameter_index<
	reverse_parameter_index_tag<_Start, _Len>, sizeof...(_Args)
>::type>
constexpr typename __call_result_of<_Function, _Indexes, _Args...>::__type
call_reverse_param(_Function func, _Args&&... args)
{
	return call<_Function&>(_Indexes(), func, std::forward<_Args>(args)...);
}
//@}
//@}

}

#endif