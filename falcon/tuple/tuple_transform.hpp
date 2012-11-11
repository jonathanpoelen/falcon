#ifndef _FALCON_TUPLE_TUPLE_TRANSFORM_HPP
#define _FALCON_TUPLE_TUPLE_TRANSFORM_HPP

#include <falcon/tuple/detail/is_tuple.hpp>
#include <falcon/parameter/parameter_index.hpp>

namespace falcon {

template <std::size_t _Index, typename _T, typename _U>
auto __tuple_transform_get(std::true_type, _T& t, _U& t_func)
-> decltype(std::get<_Index>(t_func)(std::get<_Index>(t)))
{
	return std::get<_Index>(t_func)(std::get<_Index>(t));
}

template <std::size_t _Index, typename _T, typename _Functor>
constexpr auto __tuple_transform_get(std::false_type, _T& t, _Functor& func)
-> decltype(func(std::get<_Index>(t)))
{
	return func(std::get<_Index>(t));
}

template<typename _T, typename _U, std::size_t... _Indexes,
typename _Tuple = std::tuple<decltype(
	__tuple_transform_get<_Indexes>(
		typename detail::has_tuple_impl<_U>::type(),
		std::declval<_T&>(),
		std::declval<_U&>()
	)
)...>>
constexpr _Tuple tuple_transform(_T& t, _U x, const parameter_index<_Indexes...>&)
{
	return _Tuple(__tuple_transform_get<_Indexes>(typename detail::has_tuple_impl<_U>::type(), t, x)...);
}

template<typename _T, typename _U,
	typename _Indexes = typename build_tuple_index<_T>::type>
constexpr auto tuple_transform(_T& t, _U x)
-> decltype(tuple_transform(t, x, _Indexes()))
{
	return tuple_transform(t, std::move(x), _Indexes());
}

}

#endif