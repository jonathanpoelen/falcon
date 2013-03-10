#ifndef _FALCON_TUPLE_TUPLE_TRANSFORM_HPP
#define _FALCON_TUPLE_TUPLE_TRANSFORM_HPP

#include <falcon/tuple/detail/is_tuple.hpp>
#include <falcon/parameter/parameter_index.hpp>

namespace falcon {

template <std::size_t _Index, typename _Tuple, typename _FunctionOrFunctions>
auto __tuple_transform_get(std::true_type, _Tuple&& t, _FunctionOrFunctions&& t_func)
-> decltype(std::get<_Index>(t_func)(std::get<_Index>(t)))
{
	return std::get<_Index>(t_func)(std::get<_Index>(t));
}

template <std::size_t _Index, typename _Tuple, typename _Functor>
constexpr auto __tuple_transform_get(std::false_type, _Tuple&& t, _Functor&& func)
-> decltype(func(std::get<_Index>(t)))
{
	return func(std::get<_Index>(t));
}

template<typename _Tuple, typename _FunctionOrFunctions, std::size_t... _Indexes,
typename _Tupleuple = std::tuple<decltype(
	__tuple_transform_get<_Indexes>(
		typename detail::has_tuple_impl<_FunctionOrFunctions>::type(),
		std::declval<_Tuple>(),
		std::declval<_FunctionOrFunctions>()
	)
)...>>
constexpr _Tupleuple tuple_transform(_Tuple&& t, _FunctionOrFunctions&& funcs, const parameter_index<_Indexes...>&)
{
	return _Tupleuple(__tuple_transform_get<_Indexes>(typename detail::has_tuple_impl<_FunctionOrFunctions>::type(),
																										std::forward<_Tuple>(t),
																										std::forward<_FunctionOrFunctions>(funcs))...);
}

template<typename _Tuple, typename _FunctionOrFunctions,
	typename _Indexes = typename build_tuple_index<_Tuple>::type>
constexpr auto tuple_transform(_Tuple&& t, _FunctionOrFunctions && funcs)
-> decltype(tuple_transform(t, funcs, _Indexes()))
{
	return tuple_transform(std::forward<_Tuple>(t),
												 std::forward<_FunctionOrFunctions>(funcs),
												 _Indexes());
}

}

#endif