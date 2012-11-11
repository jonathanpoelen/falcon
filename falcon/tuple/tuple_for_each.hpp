#ifndef _FALCON_TUPLE_TUPLE_FOR_EACH_HPP
#define _FALCON_TUPLE_TUPLE_FOR_EACH_HPP

#include <utility>
#include <falcon/tuple/detail/tuplefwd.hpp>

namespace falcon {

template<std::size_t _N, std::size_t _Len>
struct __tuple_for_each
{
	template<typename _Functor, typename _Tuple>
	static void __impl(_Tuple& t, _Functor& func)
	{
		func(std::get<_N>(t));
		__tuple_for_each<_N+1, _Len>::__impl(t, func);
	}
};

template<std::size_t _N>
struct __tuple_for_each<_N, _N>
{
	template<typename _Functor, typename _Tuple>
	static void __impl(const _Tuple& , _Functor& )
	{}
};

template<typename _Functor, typename _Tuple>
_Functor tuple_for_each(_Tuple& t, _Functor func)
{
	__tuple_for_each<0, std::tuple_size<_Tuple>::value>::__impl(t, func);
	return std::move<>(func);
}

template<typename _Functor, typename _Tuple>
_Functor tuple_for_each(const _Tuple& t, _Functor func)
{
	__tuple_for_each<0, std::tuple_size<_Tuple>::value>::__impl(t, func);
	return std::move<>(func);
}

}

#endif