#ifndef _FALCON_TUPLE_TUPLE_ASSIGN_HPP
#define _FALCON_TUPLE_TUPLE_ASSIGN_HPP

#include <falcon/tuple/detail/is_tuple.hpp>
#include <falcon/parameter/parameter_index.hpp>

namespace falcon {

template <typename _Indexes>
struct __tuple_assign{
	template<typename... _Elements, typename... _Elements2, typename... _Functors>
	static void __assign(const std::tuple<_Elements...>&,
						 const std::tuple<_Elements2...>&,
						 const std::tuple<_Functors...>&)
	{}

	template<typename... _Elements, typename... _Elements2, typename _Functor>
	static void __assign(const std::tuple<_Elements...>&,
						 const std::tuple<_Elements2...>&,
						 const _Functor&)
	{}
};

template <std::size_t _Index, std::size_t... _Indexes>
struct __tuple_assign<parameter_index<_Index, _Indexes...>>
{
	template<typename... _Elements, typename... _Elements2, typename... _Functors>
	static void __assign(std::tuple<_Elements...>& t,
						 std::tuple<_Elements2...>& t2,
						 std::tuple<_Functors...>& t_func)
	{
		std::get<_Index>(t) = std::get<_Index>(t_func)(std::get<_Index>(t2));
		__tuple_assign<parameter_index<_Indexes...>>::__assign(t, t2, t_func);
	}

	template<typename... _Elements, typename... _Elements2, typename... _Functors>
	static void __assign(const std::tuple<_Elements...>& t,
						 std::tuple<_Elements2...>& t2,
						 std::tuple<_Functors...>& t_func)
	{
		std::get<_Index>(t) = std::get<_Index>(t_func)(std::get<_Index>(t2));
		__tuple_assign<parameter_index<_Indexes...>>::__assign(t, t2, t_func);
	}

	template<typename... _Elements, typename... _Elements2, typename... _Functors>
	static void __assign(std::tuple<_Elements...>& t,
						 const std::tuple<_Elements2...>& t2,
						 std::tuple<_Functors...>& t_func)
	{
		std::get<_Index>(t) = std::get<_Index>(t_func)(std::get<_Index>(t2));
		__tuple_assign<parameter_index<_Indexes...>>::__assign(t, t2, t_func);
	}

	template<typename... _Elements, typename... _Elements2, typename... _Functors>
	static void __assign(const std::tuple<_Elements...>& t,
						 const std::tuple<_Elements2...>& t2,
						 std::tuple<_Functors...>& t_func)
	{
		std::get<_Index>(t) = std::get<_Index>(t_func)(std::get<_Index>(t2));
		__tuple_assign<parameter_index<_Indexes...>>::__assign(t, t2, t_func);
	}


	template<typename... _Elements, typename... _Elements2, typename _Functor>
	static void __assign(std::tuple<_Elements...>& t,
						 std::tuple<_Elements2...>& t2,
						 _Functor& func)
	{
		std::get<_Index>(t) = func(std::get<_Index>(t2));
		__tuple_assign<parameter_index<_Indexes...>>::__assign(t, t2, func);
	}

	template<typename... _Elements, typename... _Elements2, typename _Functor>
	static void __assign(const std::tuple<_Elements...>& t,
						 std::tuple<_Elements2...>& t2,
						 _Functor& func)
	{
		std::get<_Index>(t) = func(std::get<_Index>(t2));
		__tuple_assign<parameter_index<_Indexes...>>::__assign(t, t2, func);
	}

	template<typename... _Elements, typename... _Elements2, typename _Functor>
	static void __assign(std::tuple<_Elements...>& t,
						 const std::tuple<_Elements2...>& t2,
						 _Functor& func)
	{
		std::get<_Index>(t) = func(std::get<_Index>(t2));
		__tuple_assign<parameter_index<_Indexes...>>::__assign(t, t2, func);
	}

	template<typename... _Elements, typename... _Elements2, typename _Functor>
	static void __assign(const std::tuple<_Elements...>& t,
						 const std::tuple<_Elements2...>& t2,
						 _Functor& func)
	{
		std::get<_Index>(t) = func(std::get<_Index>(t2));
		__tuple_assign<parameter_index<_Indexes...>>::__assign(t, t2, func);
	}
};

template<typename... _Elements, typename... _Elements2, typename... _Functors, std::size_t... _Indexes>
void tuple_assign(std::tuple<_Elements...>& t,
				  std::tuple<_Elements2...>& t2,
				  std::tuple<_Functors...> t_func,
				  const parameter_index<_Indexes...>&
 				)
{
	__tuple_assign<parameter_index<_Indexes...>>::__assign(t, t2, t_func);
}

template<typename... _Elements, typename... _Elements2, typename... _Functors, std::size_t... _Indexes>
void tuple_assign(const std::tuple<_Elements...>& t,
				  std::tuple<_Elements2...>& t2,
				  std::tuple<_Functors...> t_func,
				  const parameter_index<_Indexes...>&)
{
	__tuple_assign<parameter_index<_Indexes...>>::__assign(t, t2, t_func);
}

template<typename... _Elements, typename... _Elements2, typename... _Functors, std::size_t... _Indexes>
void tuple_assign(std::tuple<_Elements...>& t,
				  const std::tuple<_Elements2...>& t2,
				  std::tuple<_Functors...> t_func,
				  const parameter_index<_Indexes...>&)
{
	__tuple_assign<parameter_index<_Indexes...>>::__assign(t, t2, t_func);
}

template<typename... _Elements, typename... _Elements2, typename... _Functors, std::size_t... _Indexes>
void tuple_assign(const std::tuple<_Elements...>& t,
				  const std::tuple<_Elements2...>& t2,
				  std::tuple<_Functors...> t_func,
				  const parameter_index<_Indexes...>&)
{
	__tuple_assign<parameter_index<_Indexes...>>::__assign(t, t2, t_func);
}


template<typename... _Elements, typename... _Elements2, typename... _Functors,
typename _Indexes = typename build_parameter_index<sizeof...(_Elements)>::type>
void tuple_assign(std::tuple<_Elements...>& t,
				  std::tuple<_Elements2...>& t2,
				  std::tuple<_Functors...> t_func)
{
	static_assert(sizeof...(_Elements) == sizeof...(_Elements2) & sizeof...(_Elements) == sizeof...(_Functors), "tuples size are different");
	__tuple_assign<_Indexes>::__assign(t, t2, t_func);
}

template<typename... _Elements, typename... _Elements2, typename... _Functors,
typename _Indexes = typename build_parameter_index<sizeof...(_Elements)>::type>
void tuple_assign(const std::tuple<_Elements...>& t,
				  std::tuple<_Elements2...>& t2,
				  std::tuple<_Functors...> t_func)
{
	static_assert(sizeof...(_Elements) == sizeof...(_Elements2) & sizeof...(_Elements) == sizeof...(_Functors), "tuples size are different");
	__tuple_assign<_Indexes>::__assign(t, t2, t_func);
}

template<typename... _Elements, typename... _Elements2, typename... _Functors,
typename _Indexes = typename build_parameter_index<sizeof...(_Elements)>::type>
void tuple_assign(std::tuple<_Elements...>& t,
				  const std::tuple<_Elements2...>& t2,
				  std::tuple<_Functors...> t_func)
{
	static_assert(sizeof...(_Elements) == sizeof...(_Elements2) & sizeof...(_Elements) == sizeof...(_Functors), "tuples size are different");
	__tuple_assign<_Indexes>::__assign(t, t2, t_func);
}

template<typename... _Elements, typename... _Elements2, typename... _Functors,
typename _Indexes = typename build_parameter_index<sizeof...(_Elements)>::type>
void tuple_assign(const std::tuple<_Elements...>& t,
				  const std::tuple<_Elements2...>& t2,
				  std::tuple<_Functors...> t_func)
{
	static_assert(sizeof...(_Elements) == sizeof...(_Elements2) & sizeof...(_Elements) == sizeof...(_Functors), "tuples size are different");
	__tuple_assign<_Indexes>::__assign(t, t2, t_func);
}


template<typename... _Elements, typename... _Elements2, typename _Functor,
std::size_t... _Indexes>
void tuple_assign(std::tuple<_Elements...>& t,
				  std::tuple<_Elements2...>& t2,
				  _Functor func,
				  const parameter_index<_Indexes...>&)
{
	__tuple_assign<parameter_index<_Indexes...>>::__assign(t, t2, func);
}

template<typename... _Elements, typename... _Elements2, typename _Functor,
std::size_t... _Indexes>
void tuple_assign(const std::tuple<_Elements...>& t,
				  std::tuple<_Elements2...>& t2,
				  _Functor func,
				  const parameter_index<_Indexes...>&)
{
	__tuple_assign<parameter_index<_Indexes...>>::__assign(t, t2, func);
}

template<typename... _Elements, typename... _Elements2, typename _Functor,
std::size_t... _Indexes>
void tuple_assign(std::tuple<_Elements...>& t,
				  const std::tuple<_Elements2...>& t2,
				  _Functor func,
				  const parameter_index<_Indexes...>&)
{
	__tuple_assign<parameter_index<_Indexes...>>::__assign(t, t2, func);
}

template<typename... _Elements, typename... _Elements2, typename _Functor,
std::size_t... _Indexes>
void tuple_assign(const std::tuple<_Elements...>& t,
				  const std::tuple<_Elements2...>& t2,
				  _Functor func,
				  const parameter_index<_Indexes...>&)
{
	__tuple_assign<parameter_index<_Indexes...>>::__assign(t, t2, func);
}

template<typename... _Elements, typename... _Elements2, typename _Functor,
typename _Indexes = typename build_parameter_index<sizeof...(_Elements)>::type>
void tuple_assign(std::tuple<_Elements...>& t,
				  std::tuple<_Elements2...>& t2,
				  _Functor func)
{
	static_assert(sizeof...(_Elements) == sizeof...(_Elements2), "tuples size are different");
	__tuple_assign<_Indexes>::__assign(t, t2, func);
}

template<typename... _Elements, typename... _Elements2, typename _Functor,
typename _Indexes = typename build_parameter_index<sizeof...(_Elements)>::type>
void tuple_assign(const std::tuple<_Elements...>& t,
				  std::tuple<_Elements2...>& t2,
				  _Functor func)
{
	static_assert(sizeof...(_Elements) == sizeof...(_Elements2), "tuples size are different");
	__tuple_assign<_Indexes>::__assign(t, t2, func);
}

template<typename... _Elements, typename... _Elements2, typename _Functor,
typename _Indexes = typename build_parameter_index<sizeof...(_Elements)>::type>
void tuple_assign(std::tuple<_Elements...>& t,
				  const std::tuple<_Elements2...>& t2,
				  _Functor func)
{
	static_assert(sizeof...(_Elements) == sizeof...(_Elements2), "tuples size are different");
	__tuple_assign<_Indexes>::__assign(t, t2, func);
}

template<typename... _Elements, typename... _Elements2, typename _Functor,
typename _Indexes = typename build_parameter_index<sizeof...(_Elements)>::type>
void tuple_assign(const std::tuple<_Elements...>& t,
				  const std::tuple<_Elements2...>& t2,
				  _Functor func)
{
	static_assert(sizeof...(_Elements) == sizeof...(_Elements2), "tuples size are different");
	__tuple_assign<_Indexes>::__assign(t, t2, func);
}

}

#endif