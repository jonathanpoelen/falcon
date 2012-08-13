#ifndef FALCON_ARG_ARG_HPP
#define FALCON_ARG_ARG_HPP

#include <falcon/preprocessor/not_ide_parser.hpp>
#include <falcon/parameter/parameter_element.hpp>

namespace falcon {

template <typename... _Args>
struct arg_size
{
	static const int value = sizeof...(_Args);
};

template <unsigned int __i, typename... _Args>
struct arg_element
{
	typedef typename parameter_element<__i, parameter_pack<_Args...>>::type type;
};


template<unsigned int __i, typename _Result>
struct __arg
{
	template<typename _T, typename... _Args>
	inline static constexpr _Result arg(_T&&, _Args&&... __args)
	{
		return __arg<__i-1, _Result>::arg(__args...);
	}
};

template<typename _Result>
struct __arg<0, _Result>
{
	template<typename _T, typename... _Args>
	inline static constexpr _Result arg(_T&& a, _Args&&... FALCON_PP_NOT_IDE_PARSER())
	{
		return a;
	}
};

template<unsigned int __i, typename... _Args>
constexpr typename arg_element<__i, _Args...>::type arg(_Args&&... __args)
{
	return __arg<__i, typename arg_element<__i, _Args...>::type>::arg(__args...);
}

}

#endif
