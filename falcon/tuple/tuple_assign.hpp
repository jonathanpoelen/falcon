#ifndef _FALCON_TUPLE_TUPLE_ASSIGN_HPP
#define _FALCON_TUPLE_TUPLE_ASSIGN_HPP

#include <falcon/tuple/detail/is_tuple.hpp>
#include <falcon/parameter/parameter_index.hpp>

#include <utility>

namespace falcon {

template <typename _Indexes>
struct __tuple_assign
{
	template<typename _T, typename _U, typename _FunctorOrFunctors>
	static void __assign(const _T&, const _U&, const _FunctorOrFunctors&)
	{}
};

template <std::size_t _Index, std::size_t... _Indexes>
struct __tuple_assign<parameter_index<_Index, _Indexes...>>
{
	template<typename _Tuple, typename _Tuple2, typename _Functors>
	static void __impl_assign(std::true_type,
							  _Tuple& t, _Tuple2& t2, _Functors && t_func)
	{ std::get<_Index>(t) = std::get<_Index>(t_func)(std::get<_Index>(t2)); }

	template<typename _Tuple, typename _Tuple2, typename _Functor>
	static void __impl_assign(std::false_type,
							  _Tuple& t, _Tuple2& t2, _Functor && func)
	{ std::get<_Index>(t) = func(std::get<_Index>(t2)); }

	template<typename _Tuple, typename _Tuple2, typename _FunctorOrFunctors>
	static void __assign(_Tuple& t, _Tuple2& t2, _FunctorOrFunctors && t_func)
	{
		__impl_assign(typename is_tuple_impl<_FunctorOrFunctors>::type(),
                      t, t2, std::forward<_FunctorOrFunctors>(t_func));
		__tuple_assign<parameter_index<_Indexes...>>::__assign(t, t2, std::forward<_FunctorOrFunctors>(t_func));
	}
};

template<typename _Tuple, typename _Tuple2, typename _FunctorOrFunctors, std::size_t... _Indexes>
void tuple_assign(const parameter_index<_Indexes...>&,
				  _Tuple& t, _Tuple2& t2, _FunctorOrFunctors && t_func)
{ __tuple_assign<parameter_index<_Indexes...>>::__assign(t, t2, std::forward<_FunctorOrFunctors>(t_func)); }

template<typename _Tuple, typename _Tuple2, typename _FunctorOrFunctors, std::size_t... _Indexes>
void tuple_assign(const parameter_index<_Indexes...>&,
				  const _Tuple& t, _Tuple2& t2, _FunctorOrFunctors && t_func)
{ __tuple_assign<parameter_index<_Indexes...>>::__assign(t, t2, std::forward<_FunctorOrFunctors>(t_func)); }

template<typename _Tuple, typename _Tuple2, typename _FunctorOrFunctors, std::size_t... _Indexes>
void tuple_assign(const parameter_index<_Indexes...>&,
				  _Tuple& t, const _Tuple2& t2, _FunctorOrFunctors && t_func)
{ __tuple_assign<parameter_index<_Indexes...>>::__assign(t, t2, std::forward<_FunctorOrFunctors>(t_func)); }

template<typename _Tuple, typename _Tuple2, typename _FunctorOrFunctors, std::size_t... _Indexes>
void tuple_assign(const parameter_index<_Indexes...>&,
				  const _Tuple& t, const _Tuple2& t2, _FunctorOrFunctors && t_func)
{ __tuple_assign<parameter_index<_Indexes...>>::__assign(t, t2, std::forward<_FunctorOrFunctors>(t_func)); }


template<typename _Tuple, typename _Tuple2, typename _FunctorOrFunctors,
	typename _Indexes = typename build_tuple_index<_Tuple>::type>
void tuple_assign(_Tuple& t, _Tuple2& t2, _FunctorOrFunctors && t_func)
{ __tuple_assign<_Indexes>::__assign(t, t2, std::forward<_FunctorOrFunctors>(t_func)); }

template<typename _Tuple, typename _Tuple2, typename _FunctorOrFunctors,
	typename _Indexes = typename build_tuple_index<_Tuple>::type>
void tuple_assign(const _Tuple& t, _Tuple2& t2, _FunctorOrFunctors && t_func)
{ __tuple_assign<_Indexes>::__assign(t, t2, std::forward<_FunctorOrFunctors>(t_func)); }

template<typename _Tuple, typename _Tuple2, typename _FunctorOrFunctors,
	typename _Indexes = typename build_tuple_index<_Tuple>::type>
void tuple_assign(_Tuple& t, const _Tuple2& t2, _FunctorOrFunctors && t_func)
{ __tuple_assign<_Indexes>::__assign(t, t2, std::forward<_FunctorOrFunctors>(t_func)); }

template<typename _Tuple, typename _Tuple2, typename _FunctorOrFunctors,
	typename _Indexes = typename build_tuple_index<_Tuple>::type>
void tuple_assign(const _Tuple& t, const _Tuple2& t2, _FunctorOrFunctors && t_func)
{ __tuple_assign<_Indexes>::__assign(t, t2, std::forward<_FunctorOrFunctors>(t_func)); }

}

#endif
