#ifndef _FALCON_TUPLE_TUPLE_TRANSFORM_HPP
#define _FALCON_TUPLE_TUPLE_TRANSFORM_HPP

#include <falcon/tuple/detail/is_tuple.hpp>
#include <falcon/parameter/parameter_index.hpp>

namespace falcon {

template <std::size_t _Index, typename... _Elements, typename... _Functors>
auto __tuple_transform_get(std::tuple<_Elements...>& t,
						   std::tuple<_Functors...>& t_func)
-> decltype(std::get<_Index>(t_func)(std::get<_Index>(t)))
{
	return std::get<_Index>(t_func)(std::get<_Index>(t));
}

template <std::size_t _Index, typename... _Elements, typename... _Functors>
auto __tuple_transform_get(const std::tuple<_Elements...>& t,
						   std::tuple<_Functors...>& t_func)
-> decltype(std::get<_Index>(t_func)(std::get<_Index>(t)))
{
	return std::get<_Index>(t_func)(std::get<_Index>(t));
}

template<typename... _Elements, typename... _Functors, std::size_t... _Indexes,
typename _Tuple = std::tuple<decltype(
	__tuple_transform_get<_Indexes>(
		std::declval<std::tuple<_Elements...>&>(),
		std::declval<std::tuple<_Functors...>&>()
	)
)...>>
constexpr _Tuple tuple_transform(std::tuple<_Elements...>& t,
								 std::tuple<_Functors...> t_func,
								 const parameter_index<_Indexes...>&)
{
	return _Tuple(__tuple_transform_get<_Indexes>(t, t_func)...);
}

template<typename... _Elements, typename... _Functors,
typename _Indexes = typename build_parameter_index<sizeof...(_Elements)>::type>
constexpr auto tuple_transform(std::tuple<_Elements...>& t,
							   std::tuple<_Functors...> t_func)
-> decltype(tuple_transform(t, t_func, _Indexes()))
{
	static_assert(sizeof...(_Elements) == sizeof...(_Functors), "tuples size are different");
	return tuple_transform(t, std::move(t_func), _Indexes());
}


template <std::size_t _Index, typename... _Elements, typename _Functor>
constexpr auto __tuple_transform_get(std::tuple<_Elements...>& t,
									 _Functor& func)
-> decltype(func(std::get<_Index>(t)))
{
	return func(std::get<_Index>(t));
}

template <std::size_t _Index, typename... _Elements, typename _Functor>
constexpr auto __tuple_transform_get(const std::tuple<_Elements...>& t,
									 _Functor& func)
-> decltype(func(std::get<_Index>(t)))
{
	return func(std::get<_Index>(t));
}

template<bool, typename _Functor, typename _Tuple, std::size_t... _Indexes>
struct __tuple_transform_helper
{
	typedef std::tuple<decltype(
		__tuple_transform_get<_Indexes>(
			std::declval<_Tuple&>(),
			std::declval<_Functor&>()
		)
	)...> type;
};

template<typename _Functor, typename _Tuple, std::size_t... _Indexes>
struct __tuple_transform_helper<true, _Functor, _Tuple, _Indexes...>
{};

template<typename... _Elements, typename _Functor, std::size_t... _Indexes,
typename _Tuple = typename __tuple_transform_helper<
	__is_tuple<_Functor>::value,
	_Functor,
	std::tuple<_Elements...>,
	_Indexes...
>::type>
constexpr _Tuple tuple_transform(std::tuple<_Elements...>& t,
								 _Functor func,
								 const parameter_index<_Indexes...>&)
{
	return _Tuple(__tuple_transform_get<_Indexes>(t, func)...);
}

template<typename... _Elements, typename _Functor,
typename _Indexes = typename build_parameter_index<sizeof...(_Elements)>::type>
constexpr auto tuple_transform(std::tuple<_Elements...>& t, _Functor func)
-> decltype(tuple_transform(t, func, _Indexes()))
{
	return tuple_transform(t, std::move(func), _Indexes());
}

}

#endif