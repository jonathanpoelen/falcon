#ifndef FALCON_ARG_ROTATE_ARG_HPP
#define FALCON_ARG_ROTATE_ARG_HPP

#include <utility> //std::swap
#if __cplusplus >= 201103L
# include <falcon/arg/arg.hpp>
# include <falcon/preprocessor/not_ide_parser.hpp>
# include <falcon/parameter/parameter_index.hpp>
#endif
#include <falcon/type_traits/normalize_index.hpp>

namespace falcon {

#if __cplusplus >= 201103L

template <std::size_t _ShiftRight, std::size_t _N>
struct __rotate_arg
{
	template <std::size_t _Nm, int _Current, typename _Indexes>
	struct __build_index;

	template <std::size_t _Nm, int _Current, std::size_t... _Indexes>
	struct __build_index<_Nm, _Current, parameter_index<_Indexes...>>
	: __build_index<_Nm-1, _Current - _ShiftRight, parameter_index<_Indexes..., normalize_index<_Current, _N>::value>>
	{};

	template <int _Current, std::size_t... _Indexes>
	struct __build_index<0, _Current, parameter_index<_Indexes...>>
	{
		typedef parameter_index<_Indexes...> __type;
	};

	template<typename... _Args>
	static void __rotate(_Args&... args)
	{
		constexpr std::size_t number_swap = (_ShiftRight&1)
		? (sizeof...(_Args) % _ShiftRight
			? 1
			: _ShiftRight
		) : (sizeof...(_Args)&1
			? 1
			: ((sizeof...(_Args)-1) % _ShiftRight + 1)
		);
		typedef typename build_range_parameter_index<0, number_swap>::type _BuildIndex;
		__rotate<number_swap>(_BuildIndex(), args...);
	}

	template<std::size_t number_swap, typename... _Args, std::size_t _Index, std::size_t... _Indexes>
	static void __rotate(const parameter_index<_Index, _Indexes...>&, _Args&... args)
	{
		typedef typename __build_index<_N / number_swap, _Index, parameter_index<>>::__type _BuildIndex;
		auto tmp = std::move<>(arg<_Index>(args...));
		__rotate_impl<>(_BuildIndex(), tmp, args...);
		__rotate<number_swap>(parameter_index<_Indexes...>(), args...);
	}

	template<std::size_t number_swap, typename... _Args>
	static void __rotate(const parameter_index<>&, _Args&... FALCON_PP_NOT_IDE_PARSER())
	{}

	template<typename _T, typename... _Args, std::size_t... _Indexes>
	static void __rotate_impl(const parameter_index<_Indexes...>&, _T& tmp, _Args&... args)
	{
		__rotate_impl<>(tmp, arg<_Indexes>(args...)...);
	}

	template<typename _T, typename _U, typename _V, typename... _Args>
	static void __rotate_impl(_T& tmp, _U& a, _V& b, _Args&... args)
	{
		a = std::move<>(b);
		__rotate_impl(tmp, b, args...);
	}

	template<typename _T, typename _U>
	static void __rotate_impl(_T& tmp, _U& a)
	{
		a = std::move<>(tmp);
	}
};

template <std::size_t _N>
struct __rotate_arg<0, _N>
{
	template<typename... _Args>
	static void __rotate(_Args&... FALCON_PP_NOT_IDE_PARSER())
	{}
};

template<int shift_right = 1, typename... _Args>
inline void rotate_arg(_Args&... args)
{
	__rotate_arg<
		normalize_index<shift_right, sizeof...(args)>::value,
		sizeof...(args)
	>::__rotate(args...);
}

template<int shift_right = 1, typename _T>
inline void rotate_arg(_T&)
{}

template<int shift_right = 1>
inline void rotate_arg()
{}

#else

template<int shift_right = 1, typename _T>
inline void rotate_arg(_T&)
{}

template<int shift_right, typename _T>
struct __rotate_arg;

template<typename _T>
struct __rotate_arg<0, _T>
{
	inline void rotate_arg(_T&, _T&)
	{}

	inline void rotate_arg(_T&, _T&, _T&)
	{}

	inline void rotate_arg(_T&, _T&, _T&, _T&)
	{}
};

template<typename _T>
struct __rotate_arg<1, _T>
{
	inline void rotate_arg(_T& a, _T& b)
	{
		std::swap<>(a, b);
	}

	inline void rotate_arg(_T& a, _T& b, _T& c)
	{
		_T tmp = c;
		c = b;
		b = a;
		a = tmp;
	}

	inline void rotate_arg(_T& a, _T& b, _T& c, _T& d)
	{
		_T tmp = d;
		d = c;
		c = b;
		b = a;
		a = tmp;
	}
};

template<typename _T>
struct __rotate_arg<2, _T>
{
	inline void rotate_arg(_T& a, _T& b, _T& c)
	{
		_T tmp = a;
		a = b;
		b = c;
		c = tmp;
	}

	inline void rotate_arg(_T& a, _T& b, _T& c, _T& d)
	{
		std::swap<>(a, c);
		std::swap<>(b, d);
	}
};

template<typename _T>
struct __rotate_arg<3, _T>
{
	inline void rotate_arg(_T& a, _T& b, _T& c, _T& d)
	{
		__rotate_arg<1, _T>::rotate_arg(d,c,b,a);
	}
};

template<int shift_right = 1, typename _T>
inline void rotate_arg(_T& a, _T& b)
{
	__rotate_arg<normalize_index<shift_right, 1>::value, _T>::rotate_arg(a,b);
}

template<int shift_right = 1, typename _T>
inline void rotate_arg(_T& a, _T& b, _T& c)
{
	__rotate_arg<normalize_index<shift_right, 1>::value, _T>::rotate_arg(a,b,c);
}

template<int shift_right = 1, typename _T>
inline void rotate_arg(_T& a, _T& b, _T& c, _T& d)
{
	__rotate_arg<normalize_index<shift_right, 1>::value, _T>::rotate_arg(a,b,c,d);
}

#endif

}

#endif
