#ifndef FALCON_FUNCTIONAL_INVOKE_HPP
#define FALCON_FUNCTIONAL_INVOKE_HPP

#include <functional>
#include <type_traits>

namespace falcon {

/**
 * Invoke a function object, which may be either a member pointer or a
 * function object. The first parameter will tell which.
 */
template<typename Functor, typename... Args>
inline typename std::enable_if<
	(!std::is_member_pointer<Functor>::value
	&& !std::is_function<Functor>::value
	&& !std::is_function<
		typename std::remove_pointer<Functor>::type
	>::value),
	typename std::result_of<Functor(Args&&...)>::type
>::type
invoke(Functor& func, Args&&... args)
{
	return func(std::forward<Args>(args)...);
}

template<typename Functor, typename... Args>
inline typename std::enable_if<
	(std::is_member_pointer<Functor>::value
	&& !std::is_function<Functor>::value
	&& !std::is_function<
		typename std::remove_pointer<Functor>::type
	>::value),
	typename std::result_of<Functor(Args&&...)>::type
>::type
invoke(Functor func, Args&&... args)
{
	return std::mem_fn(func)(std::forward<Args>(args)...);
}

// To pick up function references (that will become function pointers)
template<typename Functor, typename... Args>
inline typename std::enable_if<
	(std::is_pointer<Functor>::value
	&& std::is_function<
		typename std::remove_pointer<Functor>::type
	>::value),
	typename std::result_of<Functor(Args&&...)>::type
>::type
invoke(Functor func, Args&&... args)
{
	return func(std::forward<Args>(args)...);
}

}

#endif
