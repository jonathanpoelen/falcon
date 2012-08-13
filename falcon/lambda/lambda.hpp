#ifndef _FALCON_LAMBDA_LAMBDA_HPP
#define _FALCON_LAMBDA_LAMBDA_HPP

#include <falcon/functional/std_placeholder.hpp>
#include <falcon/functional/operators.hpp>
#include <falcon/functional/call.hpp>
#include <falcon/parameter/keep_parameter_index.hpp>
#include <falcon/arg/arg.hpp>
#include <falcon/preprocessor/not_ide_parser.hpp>

namespace falcon {
namespace lambda {
namespace operators {
class binder;
}

class __placearg;

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
	typedef typename std_placeholder<_Num>::type std_placeholder_type;

	template<typename _Index>
	inline constexpr ___lambda<index<late_parameter_t, _Index>, placeholder<_Num>, const _Index&> operator[](const _Index& idx)
	{
		return CPP0X(index<late_parameter_t, _Index>{}, idx);
	}

	/* use std::bind ?
	template<typename... _Args>
	inline ___lambda<functional_operators::function<_Args...>, placeholder<_Num> > bind(_Args&&... args)
	{ return CPP0X(std::tuple<_Args...>(std::forward<_Args>(args)...)); }*/

	template<typename... _Args>
	inline CPP0X_DELEGATE_FUNCTION(operator()(_Args&&... args), arg<_Num-1>(args...))

	template<typename _T>
	inline constexpr ___lambda<late_affect, placeholder<_Num>, const _T&> operator=(const _T& v)
	{
		return CPP0X(late_affect{}, v);
	}

	template<int _Num2>
	inline constexpr ___lambda<late_affect, placeholder<_Num>, placeholder<_Num2> > operator=(const placeholder<_Num2>&)
	{
		return CPP0X(late_affect{});
	}

	constexpr std_placeholder_type to_std_placeholderight() const
	{
		return std_placeholder_type();
	}

	template<typename _T, typename _Class>
	inline constexpr ___lambda<decltype(std::mem_fn(std::declval<_T _Class::*>())), placeholder<_Num>> operator FALCON_PP_NOT_IDE_PARSER(->*)(_T _Class::* mem)
	{
		return CPP0X(std::mem_fn(mem));
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
	CPP0X_DELEGATE_FUNCTION(operator()(_Args&&... args), function(left(std::forward<_Args>(args)...), right(std::forward<_Args>(args)...)))
};

template<typename _Func, typename _FuncL, typename _Left, typename _Right, int _Num>
struct ___lambda<_Func, ___lambda<_FuncL, _Left, _Right>, placeholder<_Num> >
{
	_Func function;
	___lambda<_FuncL, _Left, _Right> left;

	template<typename... _Args>
	CPP0X_DELEGATE_FUNCTION(operator()(_Args&&... args), function(left(std::forward<_Args>(args)...), arg<_Num-1>(args...)))
};

template<typename _Func, typename _FuncL, typename _Left, typename _Right, int _Num>
struct ___lambda<_Func, placeholder<_Num>, ___lambda<_FuncL, _Left, _Right> >
{
	_Func function;
	___lambda<_FuncL, _Left, _Right> right;

	template<typename... _Args>
	CPP0X_DELEGATE_FUNCTION(operator()(_Args&&... args), function(arg<_Num-1>(args...), right(std::forward<_Args>(args)...)))
};

template<typename _Func, typename _FuncL, typename _Left, typename _Right, typename _T>
struct ___lambda<_Func, ___lambda<_FuncL, _Left, _Right>, _T>
{
	_Func function;
	___lambda<_FuncL, _Left, _Right> left;
	_T right;

	template<typename... _Args>
	CPP0X_DELEGATE_FUNCTION(operator()(_Args&&... args), function(left(std::forward<_Args>(args)...), right))
};

template<typename _Func, typename _FuncL, typename _Left, typename _Right>
struct ___lambda<_Func, ___lambda<_FuncL, _Left, _Right>, __placearg>
{
	_Func function;
	___lambda<_FuncL, _Left, _Right> left;

	template<typename... _Args>
	CPP0X_DELEGATE_FUNCTION(operator()(_Args&&... args), function(left(std::forward<_Args>(args)...)/*, std::forward<_Args>(args)...*/))
};

template<typename _Func, typename _FuncL, typename _Left, typename _Right, typename _T>
struct ___lambda<_Func, _T, ___lambda<_FuncL, _Left, _Right> >
{
	_Func function;
	_T left;
	___lambda<_FuncL, _Left, _Right> right;

	template<typename... _Args>
	CPP0X_DELEGATE_FUNCTION(operator()(_Args&&... args), function(left, right(std::forward<_Args>(args)...)))
};

template<typename _Func, int _Num>
struct ___lambda<_Func, placeholder<_Num>, __placearg>
{
	_Func function;

	template<typename... _Args>
	CPP0X_DELEGATE_FUNCTION(operator()(_Args&&... args), call<_Func&>(
		typename keep_parameter_index<
			ignore_parameter_index_tag<_Num, 1>,
			sizeof...(_Args)+1
		>::type(), function, arg<_Num-1>(args...), std::forward<_Args>(args)...)
	)
};

template<typename _Func>
struct ___lambda<_Func, placeholder<1>, __placearg>
{
	_Func function;

	template<typename _T, typename... _Args>
	CPP0X_DELEGATE_FUNCTION(operator()(_T&& a, _Args&&... args), function(a, std::forward<_Args>(args)...))
};

template<typename _Func, int _Num>
struct ___lambda<_Func, __placearg, placeholder<_Num> >
{
	_Func function;

	template<typename... _Args>
	CPP0X_DELEGATE_FUNCTION(operator()(_Args&&... args),call<_Func&>(
		typename keep_parameter_index<
			ignore_parameter_index_tag<_Num, 1>,
			sizeof...(_Args)+1
		>::type(), function, arg<_Num-1>(args...), std::forward<_Args>(args)...)
	)
};

template<typename _Func>
struct ___lambda<_Func, __placearg, placeholder<1> >
{
	_Func function;

	template<typename _T, typename... _Args>
	CPP0X_DELEGATE_FUNCTION(operator()(_T&& a, _Args&&... args), function(a, std::forward<_Args>(args)...))
};

template<typename _Func, int _Num, typename _Right>
struct ___lambda<_Func, placeholder<_Num>, _Right>
{
	_Func function;
	_Right right;

	template<typename... _Args>
	CPP0X_DELEGATE_FUNCTION(operator()(_Args&&... args), function(arg<_Num-1>(args...), right))
};

template<typename _Func, typename _Left, int _Num>
struct ___lambda<_Func, _Left, placeholder<_Num> >
{
	_Func function;
	_Left left;

	template<typename... _Args>
	CPP0X_DELEGATE_FUNCTION(operator()(_Args&&... args), function(left, arg<_Num-1>(args...)))
};

template<typename _Func, int _Num, int _Num2>
struct ___lambda<_Func, placeholder<_Num>, placeholder<_Num2> >
{
	_Func function;

	template<typename... _Args>
	CPP0X_DELEGATE_FUNCTION(operator()(_Args&&... args), function(arg<_Num-1>(args...), arg<_Num2-1>(args...)))
};

template<typename _T>
struct ___lambda<void, _T, __placearg>
{
	_T val;

	template<typename... _Args>
	_T& operator()(_Args&&... FALCON_PP_NOT_IDE_PARSER())
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
	CPP0X_DELEGATE_FUNCTION(operator()(_Args&&... args), function(bind(std::forward<_Args>(args)...)))
};

template<typename _Func, typename _Bind, typename _Bind2>
struct ___lambda<_Func, ___lambda<operators::binder, _Bind, _Bind2>, operators::binder>
{
	_Func function;
	_Bind left;
	_Bind2 right;

	template<typename... _Args>
	CPP0X_DELEGATE_FUNCTION(operator()(_Args&&... args), function(left(std::forward<_Args>(args)...), right(std::forward<_Args>(args)...)))
};

template<typename _Func, typename _Bind, int _Num>
struct ___lambda<_Func, __pair<_Bind, placeholder<_Num> >, operators::binder>
{
	_Func function;
	_Bind right;

	template<typename... _Args>
	CPP0X_DELEGATE_FUNCTION(operator()(_Args&&... args), function(arg<_Num-1>(args...), right(std::forward<_Args>(args)...)))
};

template<typename _Func, typename _Bind, int _Num>
struct ___lambda<_Func, __pair<placeholder<_Num>, _Bind>, operators::binder>
{
	_Func function;
	_Bind left;

	template<typename... _Args>
	CPP0X_DELEGATE_FUNCTION(operator()(_Args&&... args), function(left(std::forward<_Args>(args)...), arg<_Num-1>(args...)))
};

template<typename _Bind>
struct ___lambda<operators::binder, _Bind, void>
{
	_Bind bind;

	template<typename... _Args>
	CPP0X_DELEGATE_FUNCTION(operator()(_Args&&... args), bind(std::forward<_Args>(args)...))
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
#define __FALCON_NAME_OPERATOR late_plus
#define __FALCON_SIGN_OPERATOR +
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_minus
#define __FALCON_SIGN_OPERATOR -
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_multiplies
#define __FALCON_SIGN_OPERATOR *
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_modulus
#define __FALCON_SIGN_OPERATOR %
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_divides
#define __FALCON_SIGN_OPERATOR /
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_bit_and
#define __FALCON_SIGN_OPERATOR &
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_bit_or
#define __FALCON_SIGN_OPERATOR |
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_bit_xor
#define __FALCON_SIGN_OPERATOR ^
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

//@}

// #undef __FALCON_RETURN_TYPE_OPERATOR
// #define __FALCON_RETURN_TYPE_OPERATOR(_Sign) bool

//@{
#define __FALCON_NAME_OPERATOR late_equal_to
#define __FALCON_SIGN_OPERATOR ==
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_not_equal_to
#define __FALCON_SIGN_OPERATOR !=
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_greater
#define __FALCON_SIGN_OPERATOR >
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_greater_equal
#define __FALCON_SIGN_OPERATOR >=
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_less
#define __FALCON_SIGN_OPERATOR <
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_less_equal
#define __FALCON_SIGN_OPERATOR <=
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_logical_and
#define __FALCON_SIGN_OPERATOR &&
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_logical_or
#define __FALCON_SIGN_OPERATOR ||
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR
//@}

// #undef __FALCON_RETURN_TYPE_OPERATOR
#undef __FALCON_CALIFIER_FIRST_PARAM
// #define __FALCON_RETURN_TYPE_OPERATOR(_Sign) _T&
#define __FALCON_CALIFIER_FIRST_PARAM

//@{
#define __FALCON_NAME_OPERATOR late_plus_equal
#define __FALCON_SIGN_OPERATOR +=
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_minus_equal
#define __FALCON_SIGN_OPERATOR -=
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_multiplies_equal
#define __FALCON_SIGN_OPERATOR *=
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_modulus_equal
#define __FALCON_SIGN_OPERATOR %=
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_divides_equal
#define __FALCON_SIGN_OPERATOR /=
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_bit_and_equal
#define __FALCON_SIGN_OPERATOR &=
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_bit_or_equal
#define __FALCON_SIGN_OPERATOR |=
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_bit_xor_equal
#define __FALCON_SIGN_OPERATOR ^=
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_left_shift
#define __FALCON_SIGN_OPERATOR <<
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_right_shift
#define __FALCON_SIGN_OPERATOR >>
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_left_shift_equal
#define __FALCON_SIGN_OPERATOR <<=
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_right_shift_equal
#define __FALCON_SIGN_OPERATOR >>=
#include <falcon/lambda/binary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR
//@}

// #undef __FALCON_RETURN_TYPE_OPERATOR
// #define __FALCON_RETURN_TYPE_OPERATOR(_Sign) decltype(_Sign std::declval<_T&>())

//@{
#define __FALCON_NAME_OPERATOR late_pointer
#define __FALCON_SIGN_OPERATOR *
#include <falcon/lambda/unary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_unary_negate
#define __FALCON_SIGN_OPERATOR -
#include <falcon/lambda/unary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_unary_plus
#define __FALCON_SIGN_OPERATOR +
#include <falcon/lambda/unary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_increment
#define __FALCON_SIGN_OPERATOR ++
#include <falcon/lambda/unary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_decrement
#define __FALCON_SIGN_OPERATOR --
#include <falcon/lambda/unary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR

#define __FALCON_NAME_OPERATOR late_complement
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
#define __FALCON_NAME_OPERATOR late_binary_negate
#define __FALCON_SIGN_OPERATOR !
#include <falcon/lambda/unary_operator.tcc>
#undef __FALCON_NAME_OPERATOR
#undef __FALCON_SIGN_OPERATOR
//@}


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

template<int _N>
struct to_std_placeholder<lambda::placeholder<_N> >
{
	typedef typename lambda::placeholder<_N>::std_placeholder_type type;
};

}

using namespace falcon::lambda::operators;

#endif
