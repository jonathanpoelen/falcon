#ifndef _FALCON_FUNCTIONAL_OPERATORS_HPP
#define _FALCON_FUNCTIONAL_OPERATORS_HPP

#include <iosfwd>
#include <utility>
#include <type_traits>
#include <falcon/c++0x/syntax.hpp>
#include <falcon/functional/late_parameter.hpp>

namespace falcon {

/**
 * Arithmetic operations
 * @{
 */
template<typename _T, typename _U = _T>
struct plus;
template<typename _T, typename _U = _T>
struct minus;
template<typename _T, typename _U = _T>
struct multiplies;
template<typename _T, typename _U = _T>
struct modulus;
template<typename _T, typename _U = _T>
struct divides;

template<typename _T, typename _U = _T>
struct plus_equal;
template<typename _T, typename _U = _T>
struct minus_equal;
template<typename _T, typename _U = _T>
struct multiplies_equal;
template<typename _T, typename _U = _T>
struct modulus_equal;
template<typename _T, typename _U = _T>
struct divides_equal;

template<typename _T>
struct increment;
template<typename _T>
struct decrement;
template<typename _T>
struct post_increment;
template<typename _T>
struct post_decrement;

template<typename _T>
struct unary_negate;
template<typename _T>
struct unary_plus;
//@}

/**
 * Lazy Arithmetic operations
 * @{
 */
typedef plus<late_parameter_t> late_plus;
typedef minus<late_parameter_t> late_minus;
typedef multiplies<late_parameter_t> late_multiplies;
typedef modulus<late_parameter_t> late_modulus;
typedef divides<late_parameter_t> late_divides;

typedef plus_equal<late_parameter_t> late_plus_equal;
typedef minus_equal<late_parameter_t> late_minus_equal;
typedef multiplies_equal<late_parameter_t> late_multiplies_equal;
typedef modulus_equal<late_parameter_t> late_modulus_equal;
typedef divides_equal<late_parameter_t> late_divides_equal;

typedef increment<late_parameter_t> late_increment;
typedef decrement<late_parameter_t> late_decrement;
typedef post_increment<late_parameter_t> late_post_increment;
typedef post_decrement<late_parameter_t> late_post_decrement;

typedef unary_negate<late_parameter_t> late_unary_negate;
typedef unary_plus<late_parameter_t> late_unary_plus;
//@}

/**
 * Comparisons
 * @{
 */
template<typename _T, typename _U = _T>
struct equal_to;
template<typename _T, typename _U = _T>
struct not_equal_to;
template<typename _T, typename _U = _T>
struct greater;
template<typename _T, typename _U = _T>
struct less;
template<typename _T, typename _U = _T>
struct greater_equal;
template<typename _T, typename _U = _T>
struct less_equal;
template<typename _T, typename _U = _T>
struct equivalent;
//@}

/**
 * Lazy comparisons
 * @{
 */
typedef equal_to<late_parameter_t> late_equal_to;
typedef not_equal_to<late_parameter_t> late_not_equal_to;
typedef greater<late_parameter_t> late_greater;
typedef less<late_parameter_t> late_less;
typedef greater_equal<late_parameter_t> late_greater_equal;
typedef less_equal<late_parameter_t> late_less_equal;
typedef equivalent<late_parameter_t> late_equivalent;
//@}

/**
 * Logical operations
 * @{
 */
template<typename _T, typename _U = _T>
struct logical_and;
template<typename _T, typename _U = _T>
struct logical_or;
//@}

/**
 * Lazy logical operations
 * @{
 */
typedef logical_and<late_parameter_t> late_logical_and;
typedef logical_or<late_parameter_t> late_logical_or;
//@}

/**
 * Bitwise operations
 * @{
 */
template<typename _T, typename _U = _T>
struct bit_and;
template<typename _T, typename _U = _T>
struct bit_or;
template<typename _T, typename _U = _T>
struct bit_xor;
template<typename _T, typename _U = _T>
struct left_shift;
template<typename _T, typename _U = _T>
struct right_shift;

template<typename _T, typename _U = _T>
struct bit_and_equal;
template<typename _T, typename _U = _T>
struct bit_or_equal;
template<typename _T, typename _U = _T>
struct bit_xor_equal;
template<typename _T, typename _U = _T>
struct left_shift_equal;
template<typename _T, typename _U = _T>
struct right_shift_equal;

template<typename _T>
struct complement;
//@}

/**
 * Lazy bitwise operations
 * @{
 */
typedef bit_and<late_parameter_t> late_bit_and;
typedef bit_or<late_parameter_t> late_bit_or;
typedef bit_xor<late_parameter_t> late_bit_xor;
typedef left_shift<late_parameter_t> late_left_shift;
typedef right_shift<late_parameter_t> late_right_shift;

typedef bit_and_equal<late_parameter_t> late_bit_and_equal;
typedef bit_or_equal<late_parameter_t> late_bit_or_equal;
typedef bit_xor_equal<late_parameter_t> late_bit_xor_equal;
typedef left_shift_equal<late_parameter_t> late_left_shift_equal;
typedef right_shift_equal<late_parameter_t> late_right_shift_equal;

typedef complement<late_parameter_t> late_complement;
//@}

/**
 * Negators
 * @{
 */
template<typename _T>
struct binary_negate;
//@}

/**
 * Lazy negators
 * @{
 */
typedef binary_negate<late_parameter_t> late_binary_negate;
//@}

/**
 * Accessor operations
 * @{
 */
template<typename _T>
struct pointer;
template<typename _T>
struct address;
template<typename _T>
struct arrow;
template<typename _T, typename _Index>
struct index;
template<typename _T, typename _Index>
struct index_emulation;
template<typename _T>
struct dereference;
//@}

/**
 * Lazy accessor operations
 * @{
 */
typedef pointer<late_parameter_t> late_pointer;
typedef address<late_parameter_t> late_address;
typedef arrow<late_parameter_t> late_arrow;
typedef index<late_parameter_t, late_parameter_t> late_index;
typedef index_emulation<late_parameter_t, late_parameter_t> late_index_emulation;
typedef dereference<late_parameter_t> late_dereference;
//@}

/**
 * Affectation
 * @{
 */
template<typename _T, typename _U>
struct affect;
//@}

/**
 * Lazy affectation
 * @{
 */
typedef affect<late_parameter_t, late_parameter_t> late_affect;
//@}

/**
 * @{
 */
template<typename _T, typename _U>
struct comma;
template<typename _T, typename _Member>
struct pointer_to_member;
template<typename _T>
struct parenthesis;

typedef comma<late_parameter_t, late_parameter_t> late_comma;
typedef pointer_to_member<late_parameter_t, late_parameter_t> late_pointer_to_member;
typedef parenthesis<late_parameter_t> late_parenthesis;
//@}


#define __FALCON_CREATE_FUNCTIONAL_OPERATORS(name, op, T1, T2, _M)\
	template<typename _T, typename _U>\
	struct name\
	{\
		inline constexpr _M(operator()(T1& a, T2& b) const, a op b)\
	};\
	template<typename _T>\
	struct name<_T, late_parameter_t>\
	{\
		template<typename _U>\
		inline constexpr _M(operator()(T1& a, T2& b) const, a op b)\
	};\
	template<typename _U>\
	struct name<late_parameter_t, _U>\
	{\
		template<typename _T>\
		inline constexpr _M(operator()(T1& a, T2& b) const, a op b)\
	};\
	template<>\
	struct name<late_parameter_t, late_parameter_t>\
	{\
		template<typename _T, typename _U>\
		inline constexpr _M(operator()(T1& a, T2& b) const, a op b)\
	};

#define __FALCON_FUNCTIONAL_OPERATORS_TRANSFORM(_Proto, _Code) _T& _Proto { return _Code; }

#define _FALCON_CREATE_FUNCTIONAL_OPERATORS(name, op)\
	__FALCON_CREATE_FUNCTIONAL_OPERATORS(name, op, const _T, const _U, CPP0X_DELEGATE_FUNCTION)\
	__FALCON_CREATE_FUNCTIONAL_OPERATORS(name##_equal, op##=, _T, const _U, __FALCON_FUNCTIONAL_OPERATORS_TRANSFORM)

_FALCON_CREATE_FUNCTIONAL_OPERATORS(plus      , +)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(minus     , -)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(multiplies, *)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(modulus   , %)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(divides   , /)

_FALCON_CREATE_FUNCTIONAL_OPERATORS(bit_and    , &)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(bit_or     , |)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(bit_xor    , ^)

template<typename _T, typename _U>
struct left_shift
{
	inline constexpr auto operator()(const _T& a, const _U& b) -> decltype(a<<b)
	{ return a << b; }
};

template<typename _CharT, typename _Traits, typename _T>
struct left_shift<std::basic_ostream<_CharT, _Traits>, _T>
{
	typedef std::basic_ostream<_CharT, _Traits> __ostream_type;

	inline __ostream_type& operator()(__ostream_type& os, const _T& b)
	{ return os << b; }
};

template<typename _T>
struct left_shift<_T, late_parameter_t>
{
	template<typename _U>
	inline constexpr auto operator()(const _T& a, const _U& b) -> decltype(a<<b)
	{ return a << b; }
};

template<typename _CharT, typename _Traits>
struct left_shift<std::basic_ostream<_CharT, _Traits>, late_parameter_t>
{
	typedef std::basic_ostream<_CharT, _Traits> __ostream_type;

	template<typename _T>
	inline __ostream_type& operator()(__ostream_type& os, const _T& b)
	{ return os << b; }

	inline __ostream_type& operator()(__ostream_type& os,
																		__ostream_type&(*manipulator)(__ostream_type&))
	{ return manipulator(os); }
};

template<>
struct left_shift<late_parameter_t, late_parameter_t>
{
	template<typename _T, typename _U>
	inline constexpr auto operator()(const _T& a, const _U& b) -> decltype(a<<b)
	{ return a << b; }

	template<typename _CharT, typename _Traits, typename _T>
	inline std::basic_ostream<_CharT, _Traits>& operator()(std::basic_ostream<_CharT, _Traits>& os, const _T& b)
	{ return os << b; }
};

template<typename _T, typename _U>
struct right_shift
{
	inline constexpr auto operator()(const _T& a, const _U& b) -> decltype(a>>b)
	{ return a >> b; }
};

template<typename _CharT, typename _Traits, typename _T>
struct right_shift<std::basic_istream<_CharT, _Traits>, _T>
{
	typedef std::basic_istream<_CharT, _Traits> __istream_type;

	inline __istream_type& operator()(__istream_type& is, _T& b)
	{ return is >> b; }
};

template<typename _T>
struct right_shift<_T, late_parameter_t>
{
	template<typename _U>
	inline constexpr auto operator()(const _T& a, const _U& b) -> decltype(a>>b)
	{ return a >> b; }
};

template<typename _CharT, typename _Traits>
struct right_shift<std::basic_istream<_CharT, _Traits>, late_parameter_t>
{
	typedef std::basic_istream<_CharT, _Traits> __istream_type;

	template<typename _T>
	inline __istream_type& operator()(__istream_type& is, _T& b)
	{ return is >> b; }

	inline __istream_type& operator()(__istream_type& os,
																		__istream_type&(*manipulator)(__istream_type&))
	{ return manipulator(os); }
};

template<>
struct right_shift<late_parameter_t, late_parameter_t>
{
	template<typename _T, typename _U>
	inline constexpr auto operator()(const _T& a, const _U& b) -> decltype(a>>b)
	{ return a >> b; }

	template<typename _CharT, typename _Traits, typename _T>
	inline std::basic_istream<_CharT, _Traits>& operator()(std::basic_istream<_CharT, _Traits>& is, _T& b)
	{ return is >> b; }
};

#undef __FALCON_FUNCTIONAL_OPERATORS_TRANSFORM

#define _FALCON_QUALIFIER_FUNCTIONAL_OPERATORS const

#undef _FALCON_CREATE_FUNCTIONAL_OPERATORS
#define _FALCON_CREATE_FUNCTIONAL_OPERATORS(name, op)\
	__FALCON_CREATE_FUNCTIONAL_OPERATORS(name, op, _FALCON_QUALIFIER_FUNCTIONAL_OPERATORS _T, const _U, CPP0X_DELEGATE_FUNCTION)\

_FALCON_CREATE_FUNCTIONAL_OPERATORS(equal_to     , ==)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(not_equal_to , !=)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(greater      , >)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(less         , <)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(greater_equal, >=)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(less_equal   , <=)

_FALCON_CREATE_FUNCTIONAL_OPERATORS(logical_and, &&)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(logical_or , ||)

#undef __FALCON_CREATE_FUNCTIONAL_OPERATORS
#define __FALCON_CREATE_FUNCTIONAL_OPERATORS(name, op, T)\
	template<typename _T>\
	struct name\
	{\
		inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(T& a) const, op(a))\
	};\
	template<>\
	struct name<late_parameter_t>\
	{\
		template<typename _T>\
		inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(T& a) const, op(a))\
	};

#undef _FALCON_CREATE_FUNCTIONAL_OPERATORS
#define _FALCON_CREATE_FUNCTIONAL_OPERATORS(name, op)\
	__FALCON_CREATE_FUNCTIONAL_OPERATORS(name, op, _FALCON_QUALIFIER_FUNCTIONAL_OPERATORS _T)

_FALCON_CREATE_FUNCTIONAL_OPERATORS(unary_negate , -)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(unary_plus   , +)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(binary_negate, !)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(complement   , ~)


#undef _FALCON_CREATE_FUNCTIONAL_OPERATORS
#define _FALCON_CREATE_FUNCTIONAL_OPERATORS(name, op)\
	__FALCON_CREATE_FUNCTIONAL_OPERATORS(name, op, _FALCON_QUALIFIER_FUNCTIONAL_OPERATORS _T)

#undef _FALCON_QUALIFIER_FUNCTIONAL_OPERATORS
#define _FALCON_QUALIFIER_FUNCTIONAL_OPERATORS

_FALCON_CREATE_FUNCTIONAL_OPERATORS(increment, ++)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(decrement, --)

#undef _FALCON_QUALIFIER_FUNCTIONAL_OPERATORS
#undef __FALCON_CREATE_FUNCTIONAL_OPERATORS
#undef _FALCON_CREATE_FUNCTIONAL_OPERATORS

#define _FALCON_CREATE_FUNCTIONAL_OPERATORS(name, op)\
	template<typename _T>\
	struct name\
	{\
		inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a) const, op(a))\
		inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(const _T& a) const, op(a))\
	};\
	template<>\
	struct name<late_parameter_t>\
	{\
		template<typename _T>\
		inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a) const, op(a))\
		template<typename _T>\
		inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(const _T& a) const, op(a))\
	};

_FALCON_CREATE_FUNCTIONAL_OPERATORS(address    , &)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(pointer    , *)
_FALCON_CREATE_FUNCTIONAL_OPERATORS(dereference, *&)

#undef _FALCON_CREATE_FUNCTIONAL_OPERATORS


template<typename _T, typename _U>
struct affect
{
	inline _T& operator()(_T& a, const _U& b) const
	{
		return a = b;
	}
};
template<typename _T>
struct affect<_T, late_parameter_t>
{
	template<typename _U>
	inline _T& operator()(_T& a, const _U& b) const
	{
		return a = b;
	}
};
template<typename _U>
struct affect<late_parameter_t, _U>
{
	template<typename _T>
	inline _T& operator()(_T& a, const _U& b) const
	{
		return a = b;
	}
};
template<>
struct affect<late_parameter_t, late_parameter_t>
{
	template<typename _T, typename _U>
	inline _T& operator()(_T& a, const _U& b) const
	{
		return a = b;
	}
};

template<typename _T, typename _U>
struct equivalent
{
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(const _T& a, const _U& b) const, !(a < b || a > b))
};
template<typename _T>
struct equivalent<_T, late_parameter_t>
{
	template<typename _U>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(const _T& a, const _U& b) const, !(a < b || a > b))
};
template<typename _U>
struct equivalent<late_parameter_t, _U>
{
	template<typename _T>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(const _T& a, const _U& b) const, !(a < b || a > b))
};
template<>
struct equivalent<late_parameter_t, late_parameter_t>
{
	template<typename _T, typename _U>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(const _T& a, const _U& b) const, !(a < b || a > b))
};

template<typename _T>
struct post_increment
{
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a) const, a++)
};
template<>
struct post_increment<late_parameter_t>
{
	template<typename _T>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a) const, a++)
};

template<typename _T>
struct post_decrement
{
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a) const, a--)
};
template<>
struct post_decrement<late_parameter_t>
{
	template<typename _T>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a) const, a--)
};

template<typename _T>
struct arrow
{
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a) const, a.operator->())
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(const _T& a) const, a.operator->())
};
template<>
struct arrow<late_parameter_t>
{
	template<typename _T>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a) const, a.operator->())
};

template<typename _T, typename _Index = int>
struct index
{
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a, const _Index& __index) const, a[__index])
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(const _T& a, const _Index& __index) const, a[__index])
};
template<typename _T>
struct index<_T, late_parameter_t>
{
	template<typename _Index>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a, const _Index& __index) const, a[__index])
};
template<typename _Index>
struct index<late_parameter_t, _Index>
{
	template<typename _T>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a, const _Index& __index) const, a[__index])
};
template<>
struct index<late_parameter_t, late_parameter_t>
{
	template<typename _T, typename _Index>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a, const _Index& __index) const, a[__index])
};

template<typename _T, typename _Index = int>
struct index_emulation
{
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a, const _Index& index) const, *(a + index))
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(const _T& a, const _Index& index) const, *(a + index))
};
template<typename _T>
struct index_emulation<_T, late_parameter_t>
{
	template<typename _Index>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a, const _Index& index) const, *(a + index))
};
template<typename _Index>
struct index_emulation<late_parameter_t, _Index>
{
	template<typename _T>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a, const _Index& index) const, *(a + index))
};
template<>
struct index_emulation<late_parameter_t, late_parameter_t>
{
	template<typename _T, typename _Index>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a, const _Index& index) const, *(a + index))
};


template<typename _T, typename _U>
struct comma
{
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a, _U& b) const, (a , b))
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a, const _U& b) const, (a , b))
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(const _T& a, _U& b) const, (a , b))
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(const _T& a, const _U& b) const, (a , b))
};
template<typename _T>
struct comma<_T, late_parameter_t>
{
	template<typename _U>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a, _U& b) const, (a , b))
};
template<typename _U>
struct comma<late_parameter_t, _U>
{
	template<typename _T>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a, _U& b) const, (a , b))
};
template<>
struct comma<late_parameter_t, late_parameter_t>
{
	template<typename _T, typename _U>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a, _U& b) const, (a , b))
};

template<typename _T, typename _Member>
struct pointer_to_member
{
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a, _Member m) const, ((a.*m)()))

	template<typename... _Args>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a, _Member m, _Args&&... args) const, (a.*m)(std::forward<_Args>(args)...))
};
template<typename _T>
struct pointer_to_member<_T, late_parameter_t>
{
	template<typename _Member>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a, _Member m) const, ((a.*m)()))

	template<typename _Member, typename... _Args>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a, _Member m, _Args&&... args) const, (a.*m)(std::forward<_Args>(args)...))
};
template<>
struct pointer_to_member<late_parameter_t, late_parameter_t>
{
	template<typename _T, typename _Member>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a, _Member m) const, ((a.*m)()))

	template<typename _T, typename _Member, typename... _Args>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& a, _Member m, _Args&&... args) const, (a.*m)(std::forward<_Args>(args)...))
};
template<typename _Result, typename _T, typename... _Args>
struct pointer_to_member<late_parameter_t, _Result(_T::*)(_Args...)>
: pointer_to_member<_T, _Result(_T::*)(_Args...)>
{};
template<typename _Result, typename _T, typename... _Args>
struct pointer_to_member<late_parameter_t, _Result(_T::*)(_Args...) const>
: pointer_to_member<_T, _Result(_T::*)(_Args...) const>
{};

template<typename _T>
struct parenthesis
{
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& f) const, f())

	template<typename... _Args>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& f, _Args&&... args) const, f(std::forward<_Args>(args)...))

	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(const _T& f) const, f())

	template<typename... _Args>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(const _T& f, _Args&&... args) const, f(std::forward<_Args>(args)...))
};
template<>
struct parenthesis<late_parameter_t>
{
	template<typename _T>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& f) const, f())

	template<typename _T, typename... _Args>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(_T& f, _Args&&... args) const, f(std::forward<_Args>(args)...))

	template<typename _T>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(const _T& f) const, f())

	template<typename _T, typename... _Args>
	inline constexpr CPP0X_DELEGATE_FUNCTION(operator()(const _T& f, _Args&&... args) const, f(std::forward<_Args>(args)...))
};

}

#endif
