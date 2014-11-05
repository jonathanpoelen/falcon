#ifndef _FALCON_LAMBDA_LAMBDA_HPP
#define _FALCON_LAMBDA_LAMBDA_HPP

#include <falcon/config.hpp>
#include <falcon/functional/operators.hpp>
#include <falcon/functional/call.hpp>
#include <falcon/parameter/keep_parameter_index.hpp>
#include <falcon/arg/arg.hpp>
#include <falcon/preprocessor/not_ide_parser.hpp>
#include <falcon/iostreams/is_ios.hpp>

#include <functional>

namespace falcon {
namespace lambda {
namespace operators {
class binder;
}

class __placearg;
class __force_placearg;

template<typename _T, typename _U>
class __pair;

template<typename _Func, typename _Left = __placearg, typename _Right = __placearg>
class ___lambda;


template<typename _T>
struct is_lambda_expression
: public std::false_type
{};
template<typename _Operation, typename _T, typename _U>
struct is_lambda_expression<___lambda<_Operation, _T, _U> >
: public std::true_type
{};


template<int _Num>
struct placeholder
{
	template<typename _Index>
	constexpr ___lambda<index<>, placeholder<_Num>, const _Index&> operator[](const _Index& idx) const
	{
		return CPP1X(index<>{}, idx);
	}

	/* use std::bind ?
	template<typename... _Args>
	___lambda<functional_operators::function<_Args...>, placeholder<_Num> > bind(_Args&&... args)
	{ return CPP1X(std::tuple<_Args...>(std::forward<_Args>(args)...)); }*/

	template<typename... _Args>
	CPP1X_DELEGATE_FUNCTION(operator()(_Args&&... args) const, arg<_Num-1>(args...))

	template<typename _T>
  constexpr ___lambda<assign<>, placeholder<_Num>, const _T&> operator=(const _T& v) const
	{
		return CPP1X(assign<>{}, v);
	}

	template<typename _T>
  constexpr ___lambda<assign<>, placeholder<_Num>, _T> operator=(_T&& v) const
	{
		return CPP1X(assign<>{}, v);
	}

	template<int _Num2>
  constexpr ___lambda<assign<>, placeholder<_Num>, placeholder<_Num2> > operator=(const placeholder<_Num2>&) const
	{
		return CPP1X(assign<>{});
	}

	template<typename _T, typename _Class>
	constexpr ___lambda<
   decltype(std::mem_fn(std::declval<_T _Class::*>())), placeholder<_Num>
#ifdef IN_IDE_PARSER
 , __force_placearg> operator ->(_T _Class::* mem) const
#else
 , __force_placearg> operator ->*(_T _Class::* mem) const
#endif
	{
		return CPP1X(std::mem_fn(mem));
	}
};

template<typename>
struct is_placeholder
: std::false_type
{};

template<int _Num>
struct is_placeholder<placeholder<_Num> >
: std::true_type
{};

template<typename _Func, typename _FuncL, typename _Left, typename _Right, typename _FuncL2, typename _Left2, typename _Right2>
struct ___lambda<_Func, ___lambda<_FuncL, _Left, _Right>, ___lambda<_FuncL2, _Left2, _Right2> >
{
	_Func function;
	___lambda<_FuncL, _Left, _Right> left;
	___lambda<_FuncL2, _Left2, _Right2> right;

	template<typename... _Args>
	CPP1X_DELEGATE_FUNCTION(operator()(_Args&&... args), function(left(std::forward<_Args>(args)...), right(std::forward<_Args>(args)...)))
};

template<typename _Func, typename _FuncL, typename _Left, typename _Right, int _Num>
struct ___lambda<_Func, ___lambda<_FuncL, _Left, _Right>, placeholder<_Num> >
{
	_Func function;
	___lambda<_FuncL, _Left, _Right> left;

	template<typename... _Args>
	CPP1X_DELEGATE_FUNCTION(operator()(_Args&&... args), function(left(std::forward<_Args>(args)...), arg<_Num-1>(args...)))
};

template<typename _Func, typename _FuncL, typename _Left, typename _Right, int _Num>
struct ___lambda<_Func, placeholder<_Num>, ___lambda<_FuncL, _Left, _Right> >
{
	_Func function;
	___lambda<_FuncL, _Left, _Right> right;

	template<typename... _Args>
	CPP1X_DELEGATE_FUNCTION(operator()(_Args&&... args), function(arg<_Num-1>(args...), right(std::forward<_Args>(args)...)))
};

template<typename _Func, typename _FuncL, typename _Left, typename _Right, typename _T>
struct ___lambda<_Func, ___lambda<_FuncL, _Left, _Right>, _T>
{
	_Func function;
	___lambda<_FuncL, _Left, _Right> left;
	_T right;

	template<typename... _Args>
	CPP1X_DELEGATE_FUNCTION(operator()(_Args&&... args), function(left(std::forward<_Args>(args)...), right))
};

template<typename _Func, typename _FuncL, typename _Left, typename _Right>
struct ___lambda<_Func, ___lambda<_FuncL, _Left, _Right>, __placearg>
{
	_Func function;
	___lambda<_FuncL, _Left, _Right> left;

	template<typename... _Args>
	CPP1X_DELEGATE_FUNCTION(operator()(_Args&&... args), function(left(std::forward<_Args>(args)...)/*, std::forward<_Args>(args)...*/))
};

template<typename _Func, typename _FuncL, typename _Left, typename _Right, typename _T>
struct ___lambda<_Func, _T, ___lambda<_FuncL, _Left, _Right> >
{
	_Func function;
	_T left;
	___lambda<_FuncL, _Left, _Right> right;

	template<typename... _Args>
	CPP1X_DELEGATE_FUNCTION(operator()(_Args&&... args), function(left, right(std::forward<_Args>(args)...)))
};

template<typename _Func, int _Num>
struct ___lambda<_Func, placeholder<_Num>, __force_placearg>
{
	_Func function;

	template<typename... _Args>
	CPP1X_DELEGATE_FUNCTION(operator()(_Args&&... args), call(
		typename keep_parameter_index<
			ignore_parameter_index_tag<_Num, 1>,
			sizeof...(_Args)+1
		>::type(), function, arg<_Num-1>(args...), std::forward<_Args>(args)...)
	)
};

template<typename _Func>
struct ___lambda<_Func, placeholder<1>, __force_placearg>
{
	_Func function;

	template<typename _T, typename... _Args>
	CPP1X_DELEGATE_FUNCTION(operator()(_T&& a, _Args&&... args), function(a, std::forward<_Args>(args)...))
};

template<typename _Func, int _Num>
struct ___lambda<_Func, placeholder<_Num>, __placearg>
{
	_Func function;

	template<typename _T, typename... _Args>
	auto operator()(_T&& a, _Args&&... args)
	-> decltype(function(a))
	{
		return function(a);
		(void)sizeof...(args);
	}
};

// template<typename _Func, int _Num>
// struct ___lambda<_Func, __placearg, placeholder<_Num> >
// {
// 	_Func function;
//
// 	template<typename... _Args>
// 	CPP1X_DELEGATE_FUNCTION(operator()(_Args&&... args),call(
// 		typename keep_parameter_index<
// 			ignore_parameter_index_tag<_Num, 1>,
// 			sizeof...(_Args)+1
// 		>::type(), function, arg<_Num-1>(args...), std::forward<_Args>(args)...)
// 	)
// };
//
// template<typename _Func>
// struct ___lambda<_Func, __placearg, placeholder<1> >
// {
// 	_Func function;
//
// 	template<typename _T, typename... _Args>
// 	CPP1X_DELEGATE_FUNCTION(operator()(_T&& a, _Args&&... args), function(a, std::forward<_Args>(args)...))
// };

template<typename _Func, int _Num, typename _Right>
struct ___lambda<_Func, placeholder<_Num>, _Right>
{
	_Func function;
	_Right right;

	template<typename... _Args>
	CPP1X_DELEGATE_FUNCTION(operator()(_Args&&... args), function(arg<_Num-1>(args...), right))
};

template<typename _Func, typename _Left, int _Num>
struct ___lambda<_Func, _Left, placeholder<_Num> >
{
	_Func function;
	_Left left;

	template<typename... _Args>
	CPP1X_DELEGATE_FUNCTION(operator()(_Args&&... args), function(left, arg<_Num-1>(args...)))
};

template<typename _Func, int _Num, int _Num2>
struct ___lambda<_Func, placeholder<_Num>, placeholder<_Num2> >
{
	_Func function;

	template<typename... _Args>
	CPP1X_DELEGATE_FUNCTION(operator()(_Args&&... args), function(arg<_Num-1>(args...), arg<_Num2-1>(args...)))
};

template<typename _T>
struct ___lambda<void, _T, __placearg>
{
	_T val;

	template<typename... _Args>
	_T& operator()(_Args&&...)
	{
		return val;
	}
};

template<typename _Func, typename _Bind>
struct ___lambda<_Func, _Bind, operators::binder>
{
	_Func function;
	_Bind bind;

	template<typename... _Args>
	CPP1X_DELEGATE_FUNCTION(operator()(_Args&&... args), function(bind(std::forward<_Args>(args)...)))
};

template<typename _Func, typename _Bind, typename _Bind2>
struct ___lambda<_Func, ___lambda<operators::binder, _Bind, _Bind2>, operators::binder>
{
	_Func function;
	_Bind left;
	_Bind2 right;

	template<typename... _Args>
	CPP1X_DELEGATE_FUNCTION(operator()(_Args&&... args), function(left(std::forward<_Args>(args)...), right(std::forward<_Args>(args)...)))
};

template<typename _Func, typename _Bind, int _Num>
struct ___lambda<_Func, __pair<_Bind, placeholder<_Num> >, operators::binder>
{
	_Func function;
	_Bind right;

	template<typename... _Args>
	CPP1X_DELEGATE_FUNCTION(operator()(_Args&&... args), function(arg<_Num-1>(args...), right(std::forward<_Args>(args)...)))
};

template<typename _Func, typename _Bind, int _Num>
struct ___lambda<_Func, __pair<placeholder<_Num>, _Bind>, operators::binder>
{
	_Func function;
	_Bind left;

	template<typename... _Args>
	CPP1X_DELEGATE_FUNCTION(operator()(_Args&&... args), function(left(std::forward<_Args>(args)...), arg<_Num-1>(args...)))
};

template<typename _Bind>
struct ___lambda<operators::binder, _Bind, void>
{
	_Bind bind;

	template<typename... _Args>
	CPP1X_DELEGATE_FUNCTION(operator()(_Args&&... args), bind(std::forward<_Args>(args)...))
};

namespace placeholders {
	constexpr placeholder<1> _1 = {};
	constexpr placeholder<2> _2 = {};
	constexpr placeholder<3> _3 = {};
	constexpr placeholder<4> _4 = {};
	constexpr placeholder<5> _5 = {};
	constexpr placeholder<6> _6 = {};
	constexpr placeholder<7> _7 = {};
	constexpr placeholder<8> _8 = {};
	constexpr placeholder<9> _9 = {};
	constexpr placeholder<10> _10 = {};
	constexpr placeholder<11> _11 = {};
	constexpr placeholder<12> _12 = {};
	constexpr placeholder<13> _13 = {};
	constexpr placeholder<14> _14 = {};
	constexpr placeholder<15> _15 = {};
	constexpr placeholder<16> _16 = {};
	constexpr placeholder<17> _17 = {};
	constexpr placeholder<18> _18 = {};
	constexpr placeholder<19> _19 = {};
	constexpr placeholder<20> _20 = {};
	constexpr placeholder<21> _21 = {};
	constexpr placeholder<22> _22 = {};
	constexpr placeholder<23> _23 = {};
	constexpr placeholder<24> _24 = {};
	constexpr placeholder<25> _25 = {};
	constexpr placeholder<26> _26 = {};
	constexpr placeholder<27> _27 = {};
	constexpr placeholder<28> _28 = {};
	constexpr placeholder<29> _29 = {};
}

#define __FALCON_CALIFIER_FIRST_PARAM const

//@{
#define __FALCON_NAME_OPERATOR plus<>
#define __FALCON_SIGN_OPERATOR +
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR minus<>
#define __FALCON_SIGN_OPERATOR -
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR multiplies<>
#define __FALCON_SIGN_OPERATOR *
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR modulus<>
#define __FALCON_SIGN_OPERATOR %
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR divides<>
#define __FALCON_SIGN_OPERATOR /
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR bit_and<>
#define __FALCON_SIGN_OPERATOR &
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR bit_or<>
#define __FALCON_SIGN_OPERATOR |
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR bit_xor<>
#define __FALCON_SIGN_OPERATOR ^
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

//@}

// #undef __FALCON_RETURN_TYPE_OPERATOR
// #define __FALCON_RETURN_TYPE_OPERATOR(_Sign) bool

//@{
#define __FALCON_NAME_OPERATOR equal_to<>
#define __FALCON_SIGN_OPERATOR ==
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR not_equal_to<>
#define __FALCON_SIGN_OPERATOR !=
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR greater<>
#define __FALCON_SIGN_OPERATOR >
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR greater_equal<>
#define __FALCON_SIGN_OPERATOR >=
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR less<>
#define __FALCON_SIGN_OPERATOR <
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR less_equal<>
#define __FALCON_SIGN_OPERATOR <=
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR logical_and<>
#define __FALCON_SIGN_OPERATOR &&
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR logical_or<>
#define __FALCON_SIGN_OPERATOR ||
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR
//@}


//@{
struct ___lambda_comma
{
	template<typename _T, typename _U>
	auto operator()(_T& a, _U& b) -> decltype(b())
	{
		a();
		return b();
	}
};

template<typename _FuncL, typename _Left, typename _Right, typename _FuncL2, typename _Left2, typename _Right2>
struct ___lambda<___lambda_comma, ___lambda<_FuncL, _Left, _Right>, ___lambda<_FuncL2, _Left2, _Right2> >
{
	___lambda_comma f;
	___lambda<_FuncL, _Left, _Right> left;
	___lambda<_FuncL2, _Left2, _Right2> right;

	template<typename... _Args>
	auto operator()(_Args&&... args)
	-> decltype(right(std::forward<_Args>(args)...))
	{
		left(std::forward<_Args>(args)...);
		return right(std::forward<_Args>(args)...);
	}
};

template<typename _FuncL, typename _Left, typename _Right, int _Num>
struct ___lambda<___lambda_comma, ___lambda<_FuncL, _Left, _Right>, placeholder<_Num> >
{
	___lambda_comma f;
	___lambda<_FuncL, _Left, _Right> left;

	template<typename... _Args>
	auto operator()(_Args&&... args)
	-> decltype(arg<_Num-1>(args...))
	{
		left(std::forward<_Args>(args)...);
		return arg<_Num-1>(args...);
	}
};

template<typename _FuncL, typename _Left, typename _Right, int _Num>
struct ___lambda<___lambda_comma, placeholder<_Num>, ___lambda<_FuncL, _Left, _Right> >
{
	___lambda_comma f;
	___lambda<_FuncL, _Left, _Right> right;

	template<typename... _Args>
	auto operator()(_Args&&... args)
	-> decltype(right(std::forward<_Args>(args)...))
	{
		return right(std::forward<_Args>(args)...);
	}
};

template<std::size_t _Num, std::size_t _Num2>
struct ___lambda<___lambda_comma, placeholder<_Num>, placeholder<_Num2>>
{
	___lambda_comma f;

	template<typename... _Args>
	auto operator()(_Args&&... args)
	-> decltype(arg<_Num2-1>(args...))
	{
		return arg<_Num2-1>(args...);
	}
};

#define __FALCON_NAME_OPERATOR ___lambda_comma
#define __FALCON_SIGN_OPERATOR ,
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR
//@}

// #undef __FALCON_RETURN_TYPE_OPERATOR
#undef __FALCON_CALIFIER_FIRST_PARAM
// #define __FALCON_RETURN_TYPE_OPERATOR(_Sign) _T&
#define __FALCON_CALIFIER_FIRST_PARAM

//@{
#define __FALCON_NAME_OPERATOR plus_equal<>
#define __FALCON_SIGN_OPERATOR +=
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR minus_equal<>
#define __FALCON_SIGN_OPERATOR -=
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR multiplies_equal<>
#define __FALCON_SIGN_OPERATOR *=
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR modulus_equal<>
#define __FALCON_SIGN_OPERATOR %=
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR divides_equal<>
#define __FALCON_SIGN_OPERATOR /=
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR bit_and_equal<>
#define __FALCON_SIGN_OPERATOR &=
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR bit_or_equal<>
#define __FALCON_SIGN_OPERATOR |=
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR bit_xor_equal<>
#define __FALCON_SIGN_OPERATOR ^=
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR left_shift<>
#define __FALCON_SIGN_OPERATOR <<
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR right_shift<>
#define __FALCON_SIGN_OPERATOR >>
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR left_shift_equal<>
#define __FALCON_SIGN_OPERATOR <<=
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR right_shift_equal<>
#define __FALCON_SIGN_OPERATOR >>=
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR
//@}

// #undef __FALCON_RETURN_TYPE_OPERATOR
// #define __FALCON_RETURN_TYPE_OPERATOR(_Sign) decltype(_Sign std::declval<_T&>())

//@{
#define __FALCON_NAME_OPERATOR dereference<>
#define __FALCON_SIGN_OPERATOR *
#include <falcon/lambda/unary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR negate<>
#define __FALCON_SIGN_OPERATOR -
#include <falcon/lambda/unary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR unary_plus<>
#define __FALCON_SIGN_OPERATOR +
#include <falcon/lambda/unary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR increment<>
#define __FALCON_SIGN_OPERATOR ++
#include <falcon/lambda/unary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR decrement<>
#define __FALCON_SIGN_OPERATOR --
#include <falcon/lambda/unary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR bit_not<>
#define __FALCON_SIGN_OPERATOR ~
#include <falcon/lambda/unary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR
//@}

// #undef __FALCON_RETURN_TYPE_OPERATOR
#undef __FALCON_CALIFIER_FIRST_PARAM

// #define __FALCON_RETURN_TYPE_OPERATOR(_Sign) bool
#define __FALCON_CALIFIER_FIRST_PARAM const

//@{
#define __FALCON_NAME_OPERATOR logical_not<>
#define __FALCON_SIGN_OPERATOR !
#include <falcon/lambda/unary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR
//@}


//support manipulator ios
namespace operators {

template<typename _T,
bool = iostreams::is_istream<_T>::value,
bool = iostreams::is_ostream<_T>::value,
bool = iostreams::is_ios<_T>::value>
struct __deduce_iostream_lambda
{
	static const bool __value = false;
	typedef void __iomanip_type;
};

template<template<class, class> class _T, typename _Char, typename _Traits>
struct __deduce_iostream_lambda<_T<_Char, _Traits>, true, false, true>
{
	static const bool __value = true;
	typedef std::basic_istream<_Char, _Traits> __ios_type;
	typedef __ios_type&(*__iomanip_type)(__ios_type&);
};

template<template<class, class> class _T, typename _Char, typename _Traits>
struct __deduce_iostream_lambda<_T<_Char, _Traits>, false, true, true>
{
	static const bool __value = true;
	typedef std::basic_ostream<_Char, _Traits> __ios_type;
	typedef __ios_type&(*__iomanip_type)(__ios_type&);
};

template<template<class, class> class _T, typename _Char, typename _Traits>
struct __deduce_iostream_lambda<_T<_Char, _Traits>, false, false, true>
{
	static const bool __value = true;
	typedef std::basic_ios<_Char, _Traits> __ios_type;
	typedef __ios_type&(*__iomanip_type)(__ios_type&);
};

template<template<class, class, class> class _T, typename _Char, typename _Traits, typename _Allocator>
struct __deduce_iostream_lambda<_T<_Char, _Traits, _Allocator>, true, false, true>
{
	static const bool __value = true;
	typedef std::basic_istream<_Char, _Traits> __ios_type;
	typedef __ios_type&(*__iomanip_type)(__ios_type&);
};

template<template<class, class, class> class _T, typename _Char, typename _Traits, typename _Allocator>
struct __deduce_iostream_lambda<_T<_Char, _Traits, _Allocator>, false, true, true>
{
	static const bool __value = true;
	typedef std::basic_ostream<_Char, _Traits> __ios_type;
	typedef __ios_type&(*__iomanip_type)(__ios_type&);
};

template<template<class, class, class> class _T, typename _Char, typename _Traits, typename _Allocator>
struct __deduce_iostream_lambda<_T<_Char, _Traits, _Allocator>, false, false, true>
{
	static const bool __value = true;
	typedef std::basic_ios<_Char, _Traits> __ios_type;
	typedef __ios_type&(*__iomanip_type)(__ios_type&);
};

typedef __deduce_iostream_lambda<void, false, false, false> __bad_ios_lambda;


template<typename _Lambda>
struct __is_ostream_lambda
: __bad_ios_lambda
{};

template<typename _T>
struct __is_ostream_lambda<___lambda<void, _T&>>
: __deduce_iostream_lambda<_T, false, iostreams::is_ostream<_T>::value>
{};

template<typename _Lambda1, typename _Lambda2>
struct __is_ostream_lambda<___lambda<left_shift<>, _Lambda1, _Lambda2>>
: __is_ostream_lambda<_Lambda1>
{};


template<typename _Lambda>
struct __is_istream_lambda
: __bad_ios_lambda
{};

template<typename _T>
struct __is_istream_lambda<___lambda<void, _T&>>
: __deduce_iostream_lambda<_T, iostreams::is_istream<_T>::value, false>
{};

template<typename _Lambda1, typename _Lambda2>
struct __is_istream_lambda<___lambda<left_shift<>, _Lambda1, _Lambda2>>
: __is_istream_lambda<_Lambda1>
{};

template<typename _Operation, typename _TL, typename _TR>
typename std::enable_if<
	__is_ostream_lambda<
		___lambda<_Operation, _TL, _TR>
	>::__value,
	___lambda<
		left_shift<>,
		___lambda<_Operation, _TL, _TR>,
		typename __is_ostream_lambda<
			___lambda<_Operation, _TL, _TR>
		>::__iomanip_type
	>
>::type
operator<<(___lambda<_Operation, _TL, _TR> l,
		   typename __is_ostream_lambda<___lambda<_Operation, _TL, _TR>>::__iomanip_type __pf)
{ return {left_shift<>(), l, __pf}; }

template<typename _Operation, typename _TL, typename _TR>
typename std::enable_if<
	__is_istream_lambda<
		___lambda<_Operation, _TL, _TR>
	>::__value,
	___lambda<
		right_shift<>,
		___lambda<_Operation, _TL, _TR>,
		typename __is_istream_lambda<
			___lambda<_Operation, _TL, _TR>
		>::__iomanip_type
	>
>::type
operator>>(___lambda<_Operation, _TL, _TR> l,
		   typename __is_istream_lambda<___lambda<_Operation, _TL, _TR>>::__iomanip_type __pf)
{ return {right_shift<>(), l, __pf}; }

}


template<typename _T>
constexpr typename std::enable_if<std::is_lvalue_reference<_T&>::value, ___lambda<void, _T&> >::type lambda(_T& ref)
{
	return {ref};
}

template<typename _T>
constexpr typename std::enable_if<std::is_rvalue_reference<_T&&>::value, ___lambda<void, _T>>::type lambda(_T&& rvalue)
{
	return {rvalue};
}

template<typename _T>
constexpr typename std::enable_if<std::is_lvalue_reference<_T&>::value, ___lambda<operators::binder, _T&, void> >::type lambda_bind(_T& ref)
{
	return {ref};
}

template<typename _T>
constexpr typename std::enable_if<std::is_rvalue_reference<_T&&>::value, ___lambda<operators::binder, _T, void>>::type lambda_bind(_T&& rvalue)
{
	return {rvalue};
}

}

}

using namespace falcon::lambda::operators;

#endif
