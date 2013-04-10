#ifndef _FALCON_UTILITY_MAKER_HPP
#define _FALCON_UTILITY_MAKER_HPP

#if __cplusplus > 201100L
# include <utility>
# include <falcon/utility/detail/construct_category.hpp>
#endif
#include <falcon/c++/constexpr.hpp>

namespace falcon {

#if __cplusplus > 201100L
template<typename _T, typename _Tag = typename ::falcon::detail::construct_category<_T>::type>
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

	template<typename... _Args>
	constexpr _Template<_Args...> operator()(_Args&&... args) const
	{ return __delegate_maker<_Template<_Args...>>::__impl(std::forward<_Args>(args)...); }
};
#endif

///wrapper of construct object
template<typename _Tp>
struct maker
{
	typedef _Tp result_type;

	CPP_CONSTEXPR maker()
	{}

	template<typename _Up>
	CPP_CONSTEXPR maker(const maker<_Up>&)
	{}

	CPP_CONSTEXPR _Tp operator()() const
	{ return _Tp(); }

	CPP_CONSTEXPR _Tp operator()(const _Tp& v) const
	{ return _Tp(v); }

#if __cplusplus > 201100L
	template<typename... _Args>
	constexpr _Tp operator()(_Args&&... args) const
	{ return __delegate_maker<_Tp>::__impl(std::forward<_Args>(args)...); }
#else
	template<typename _U>
	_Tp operator()(const _U& v) const
	{ return _Tp(v); }
#endif
};

}

#endif
