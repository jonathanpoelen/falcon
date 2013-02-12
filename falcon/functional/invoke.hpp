#ifndef _FALCON_FUNCTIONAL_INVOKE_HPP
#define _FALCON_FUNCTIONAL_INVOKE_HPP

#include <functional>

namespace falcon {

/**
 * Invoke a function object, which may be either a member pointer or a
 * function object. The first parameter will tell which.
 */
template<typename _Functor, typename... _Args>
inline typename std::enable_if<
	(!std::is_member_pointer<_Functor>::value
	&& !std::is_function<_Functor>::value
	&& !std::is_function<
		typename std::remove_pointer<_Functor>::type
	>::value),
	typename std::result_of<_Functor(_Args&&...)>::type
>::type
invoke(_Functor& __f, _Args&&... __args)
{
	return __f(std::forward<_Args>(__args)...);
}

template<typename _Functor, typename... _Args>
inline typename std::enable_if<
	(std::is_member_pointer<_Functor>::value
	&& !std::is_function<_Functor>::value
	&& !std::is_function<
		typename std::remove_pointer<_Functor>::type
	>::value),
	typename std::result_of<_Functor(_Args&&...)>::type
>::type
invoke(_Functor __f, _Args&&... __args)
{
	return std::mem_fn(__f)(std::forward<_Args>(__args)...);
}

// To pick up function references (that will become function pointers)
template<typename _Functor, typename... _Args>
inline typename std::enable_if<
	(std::is_pointer<_Functor>::value
	&& std::is_function<
		typename std::remove_pointer<_Functor>::type
	>::value),
	typename std::result_of<_Functor(_Args&&...)>::type
>::type
invoke(_Functor __f, _Args&&... __args)
{
	return __f(std::forward<_Args>(__args)...);
}

}

#endif