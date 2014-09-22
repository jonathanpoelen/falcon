#ifndef FALCONUTILITY_MAKER_HPP
#define FALCONUTILITY_MAKER_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/parameter/parameter_index.hpp>
#if __cplusplus >= 201103L
# include <falcon/memory/construct_category.hpp>
# include <utility>
# include <tuple>
#endif

namespace falcon {

#if __cplusplus >= 201103L
namespace aux_ {
  template<typename T, typename Tag = typename construct_category<T>::type>
  struct delegate_maker
  {
    template<typename... Args>
    constexpr static T impl(Args&&... args)
    { return T(std::forward<Args>(args)...); }
  };

  template<typename T>
  struct delegate_maker<T, brace_init_tag>
  {
    template<typename... Args>
    constexpr static T impl(Args&&... args)
    { return T{std::forward<Args>(args)...}; }

    constexpr static T impl(T&& val)
    { return T(std::forward<T>(val)); }

    constexpr static T impl(const T& val)
    { return T(val); }
  };

  template<typename T>
  struct delegate_maker<T, double_brace_init_tag>
  {
    template<typename... Args>
    constexpr static T impl(Args&&... args)
    { return T{{std::forward<Args>(args)...}}; }
  };

  template<typename T>
  struct delegate_maker<T, dispatch_index_tag>
  {
    template<std::size_t... Indexes>
    constexpr static T dispatch_impl(
      T&& val, falcon::parameter_index<Indexes...>)
    { using std::get; return T{get<Indexes>(std::forward<T>(val))...}; }

    constexpr static T impl(T&& val)
    {
      return dispatch_impl(
        std::forward<T>(val),
        falcon::build_parameter_index_t<std::tuple_size<T>::value>()
      );
    }

    template<std::size_t... Indexes>
    constexpr static T dispatch_impl(
      const T& val, falcon::parameter_index<Indexes...>)
    { using std::get; return T{get<Indexes>(std::forward<T>(val))...}; }

    constexpr static T impl(const T& val)
    {
      return dispatch_impl(
        val,
        falcon::build_parameter_index_t<std::tuple_size<T>::value>()
      );
    }

    template<typename... Args>
    constexpr static T impl(Args&&... args)
    { return T{std::forward<Args>(args)...}; }
  };
}

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
	{
   return aux_::delegate_maker<Template<Args...>>::impl(
     std::forward<Args>(args)...);
  }
};
#endif

///wrapper of construct object
template<typename T>
struct maker
{
	typedef T result_type;

	CPP_CONSTEXPR maker()
	{}

	template<typename U>
	CPP_CONSTEXPR maker(const maker<U>&)
	{}

	CPP_CONSTEXPR T operator()() const
	{ return T(); }

	CPP_CONSTEXPR T operator()(const T& v) const
	{ return T(v); }

#if __cplusplus >= 201103L
	template<typename... Args>
	constexpr T operator()(Args&&... args) const
	{ return aux_::delegate_maker<T>::impl(std::forward<Args>(args)...); }
#else
	template<typename U>
	T operator()(const U& v) const
	{ return T(v); }
#endif
};

}

#endif
