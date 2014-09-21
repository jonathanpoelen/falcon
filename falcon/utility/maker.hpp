#ifndef FALCONUTILITY_MAKER_HPP
#define FALCONUTILITY_MAKER_HPP

#include <falcon/config.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/parameter/parameter_index.hpp>
#if __cplusplus >= 201103L
# include <falcon/memory/construct_category.hpp>
# include <utility>
# include <tuple>
#endif

namespace falcon {

#if __cplusplus >= 201103L
template<typename T, typename Tag = typename construct_category<T>::type>
struct __delegate_maker
{
	template<typename... Args>
	constexpr static T __impl(Args&&... args)
	{ return T(std::forward<Args>(args)...); }
};

template<typename T>
struct __delegate_maker<T, brace_init_tag>
{
	template<typename... Args>
	constexpr static T __impl(Args&&... args)
	{ return T{std::forward<Args>(args)...}; }

	constexpr static T __impl(T&& val)
	{ return T(std::forward<T>(val)); }

	constexpr static T __impl(const T& val)
	{ return T(val); }
};

template<typename T>
struct __delegate_maker<T, double_brace_init_tag>
{
	template<typename... Args>
	constexpr static T __impl(Args&&... args)
	{ return T{{std::forward<Args>(args)...}}; }
};

template<typename T>
struct __delegate_maker<T, dispatch_index_tag>
{
	template<std::size_t... Indexes>
	constexpr static T __dispatch_impl(T&& val, falcon::parameter_index<Indexes...>)
	{ return T{get<Indexes>(std::forward<T>(val))...}; }

	constexpr static T __impl(T&& val)
	{
		return __dispatch_impl(
			std::forward<T>(val),
			typename falcon::build_parameter_index<std::tuple_size<T>::value>::type()
		);
	}

	template<std::size_t... Indexes>
	constexpr static T __dispatch_impl(const T& val, falcon::parameter_index<Indexes...>)
	{ return T{get<Indexes>(std::forward<T>(val))...}; }

	constexpr static T __impl(const T& val)
	{
		return __dispatch_impl(
			val,
			typename falcon::build_parameter_index<std::tuple_size<T>::value>::type()
		);
	}

	template<typename... Args>
	constexpr static T __impl(Args&&... args)
	{ return T{std::forward<Args>(args)...}; }
};

///wrapper of construct object
template <template<typename...> class Template>
struct late_maker
{
	constexpr late_maker()
	{}

	template<template<typename...> class UTemplate>
	constexpr late_maker(const late_maker<UTemplate>&)
	{}

	template<typename... Args>
	constexpr Template<Args...> operator()(Args&&... args) const
	{ return __delegate_maker<Template<Args...>>::__impl(std::forward<Args>(args)...); }
};
#endif

///wrapper of construct object
template<typename Tp>
struct maker
{
	typedef Tp result_type;

	CPP_CONSTEXPR maker()
	{}

	template<typename Up>
	CPP_CONSTEXPR maker(const maker<Up>&)
	{}

	CPP_CONSTEXPR Tp operator()() const
	{ return Tp(); }

	CPP_CONSTEXPR Tp operator()(const Tp& v) const
	{ return Tp(v); }

#if __cplusplus >= 201103L
	template<typename... Args>
	constexpr Tp operator()(Args&&... args) const
	{ return __delegate_maker<Tp>::__impl(std::forward<Args>(args)...); }
#else
	template<typename U>
	Tp operator()(const U& v) const
	{ return Tp(v); }
#endif
};

}

#endif
