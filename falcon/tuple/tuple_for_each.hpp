#ifndef _FALCON_TUPLE_TUPLE_FOR_EACH_HPP
#define _FALCON_TUPLE_TUPLE_FOR_EACH_HPP

#include <tuple>

namespace falcon {

template<std::size_t _N, std::size_t _Len>
struct __tuple_for_each
{
	template<typename _Functor, typename... _Elements>
	static void __impl(std::tuple<_Elements...>& t, _Functor& func)
	{
		func(std::get<_N>(t));
		__tuple_for_each<_N+1, _Len>::__impl(t, func);
	}
};

template<std::size_t _N>
struct __tuple_for_each<_N, _N>
{
	template<typename _Functor, typename... _Elements>
	static void __impl(std::tuple<_Elements...>& , _Functor& )
	{}
};

template<typename _Functor, typename... _Elements>
_Functor tuple_for_each(std::tuple<_Elements...>& t, _Functor func)
{
	__tuple_for_each<0, sizeof...(_Elements)>::__impl(t, func);
	return std::move<>(func);
}

}

#endif