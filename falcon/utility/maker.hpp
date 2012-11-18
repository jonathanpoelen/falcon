#ifndef _FALCON_UTILITY_MAKER_HPP
#define _FALCON_UTILITY_MAKER_HPP

#ifdef __GXX_EXPERIMENTAL_CXX0X__
# include <utility>
# include <falcon/utility/detail/construct_category.hpp>
#endif
#include <falcon/c++/constexpr.hpp>

namespace falcon {

#ifdef __GXX_EXPERIMENTAL_CXX0X__
template<typename _T, typename _Tag = typename detail::construct_category<_T>::type>
struct __delegate_maker
{
	template<typename... _Args>
	constexpr static _T __impl(_Args&&... args)
	{ return _T{std::forward<_Args>(args)...}; }
};

template<typename _T>
struct __delegate_maker<_T, ::falcon::detail::initilizer_list_construct_tag>
{
	template<typename... _Args>
	constexpr static _T __impl(_Args&&... args)
	{ return _T{{std::forward<_Args>(args)...}}; }
};

///wrapper of construct object
template <template<typename...> class _Template>
struct late_maker
{
	constexpr late_maker()
	{}

	template<template<typename...> class _UTemplate>
	constexpr late_maker(const late_maker<_UTemplate>&)
	{}

	constexpr _Template<> operator()() const
	{ return _Template<>(); }

	template<typename... _Args>
	constexpr _Template<_Args...> operator()(_Args&&... args) const
	{ return __delegate_maker<_Template<_Args...>>::__impl(args...); }
};
#endif

///wrapper of construct object
template<typename _Tp>
struct maker
{
	CPP_CONSTEXPR maker()
	{}

	template<typename _Up>
	CPP_CONSTEXPR maker(const maker<_Up>&)
	{}

	CPP_CONSTEXPR _Tp operator()() const
	{ return _Tp(); }

	CPP_CONSTEXPR _Tp operator()(const _Tp& v) const
	{ return _Tp(v); }

	template<typename _U>
	CPP_CONSTEXPR _Tp operator()(const _U& v) const
	{ return _Tp(v); }

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	template<typename... _Args>
	constexpr _Tp operator()(_Args&&... args) const
	{ return __delegate_maker<_Tp>::__impl(args...); }
#endif
};

}

#endif
