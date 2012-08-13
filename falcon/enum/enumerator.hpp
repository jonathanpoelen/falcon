#ifndef _FALCON_ENUM_ENUMERATOR_HPP
#define _FALCON_ENUM_ENUMERATOR_HPP

#include <boost/preprocessor/logical/and.hpp>
#include <boost/preprocessor/list/at.hpp>
#include <boost/preprocessor/list/for_each.hpp>
#include <boost/preprocessor/list/for_each_product.hpp>
#include <boost/preprocessor/list/size.hpp>

#include <falcon/preprocessor/d_prefix.hpp>
#include <falcon/preprocessor/d_punctuation.hpp>
#include <falcon/preprocessor/variatic/punctuation.hpp>
#include <falcon/preprocessor/variatic/call.hpp>
#include <falcon/preprocessor/variatic/arg.hpp>
#include <falcon/preprocessor/variatic/enum.hpp>
#include <falcon/preprocessor/variatic/d_values.hpp>
#include <falcon/preprocessor/variatic/size.hpp>
#include <falcon/preprocessor/variatic/is_empty.hpp>
#include <falcon/preprocessor/variatic/has_parenthesis.hpp>

#include <falcon/iterator/nexter_iterator.hpp>
#include <falcon/iterator/not_iterator.hpp>
#include <falcon/functional/compose.hpp>
#include <falcon/functional/operators.hpp>
#include <falcon/enum/operators.hpp>
#include <falcon/container/container_wrapper.hpp>

/**
 * struct Enumerator
 * {
 * 	enum enum_t { ... };
 *
 * 	struct strings
 * 	{
 *		///NOTE char_type is determined
 * 		typedef const char_type* value_type;
 * 		typedef const value_type& const_reference;
 * 		typedef const_reference reference;
 * 		typedef const value_type* const_pointer;
 * 		typedef const_pointer pointer;
 * 		typedef const_pointer iterator;
 * 		typedef iterator const_iterator;
 *
 * 		const_iterator begin();
 * 		const_iterator end();
 *
 * 		value_type operator[](std::size n);
 * 		value_type operator[](enum_t e);
 * 	};
 *
 *	struct enumeration
 * 	{
 * 		typedef enum_t value_type;
 * 		typedef value_type& reference;
 * 		typedef const value_type& const_reference;
 * 		typedef value_type* pointer;
 * 		typedef const value_type* const_pointer;
 * 		typedef ... iterator;
 *
 * 		static iterator begin();
 * 		static iterator end();
 * 	};
 *
 * 	typedef ::falcon::static_container_wrapper<enumeration> enumeration_wrapper;
 *
 * 	static std::size_t enum_to_index_string(enum_t e);
 * };
 *
 * @param name of enumerator class
 * @param rule
 * default: create standard enum
 * For example
 * @code
 * enum enum_t {A, B, C, ...};
 * @endcode
 *
 * linear(start) with start represent first value of enum
 * For example
 * @code
 * enum enum_t {A = start, B, C, ...};
 * @endcode
 *
 * step(n) with n represent step between each value of enum
 * For example
 * @code
 * enum enum_t {A = 0*n, B = 1*n, C = 2*n, ...};
 * @endcode
 *
 * linear_step(start, n) combine linear(start) and step(n)
 * @code
 * enum enum_t {A = start + 0*n, B = start + 1*n, C = start + 2*n, ...};
 * @endcode
 *
 * lbit(start) left shift each value of enum
 * @code
 * enum enum_t {A = start, B = start << 1, C = start << 2, ...};
 * @endcode
 * If start equal 0, the second value equal 1
 * @code
 * enum enum_t {A = 0, B = 1, C = 1 << 1, ...};
 * @endcode
 *
 * rbit(start) right shift each value of enum
 * @code
 * enum enum_t {A = start, B = start >> 1, C = start >> 2, ...};
 * @endcode
 *
 * @param elems... pair value name of enum and string representation or only value name of enum
 * @code
 * FALCON_PP_ENUMERATOR(enumerator1, default, A, (B), (C, "C"))
 * @endcode
 */
#define FALCON_PP_ENUMERATOR(name, rule, elems...)\
	FALCON_PP_TUPLE_ENUMERATOR(name, rule, FALCON_PP_VARIADIC_SIZE(elems), (elems))

#define FALCON_PP_TUPLE_ENUMERATOR(name, rule, n, tuple)\
	__FALCON_PP_LIST_ENUMERATOR(name, rule, n, BOOST_PP_TUPLE_TO_LIST(n, tuple))

#define __FALCON_PP_LIST_ENUMERATOR_STRINGIZE_NAME(r, data, elem)\
	__FALCON_PP_LIST_ENUMERATOR_STRINGIZE_NAME_I(elem),
#define __FALCON_PP_LIST_ENUMERATOR_STRINGIZE_NAME_I(elem)\
	BOOST_PP_CAT(__FALCON_PP_LIST_ENUMERATOR_STRINGIZE_NAME_, FALCON_PP_VARIADIC_HAS_PARENTHESIS(elem))(elem)
#define __FALCON_PP_LIST_ENUMERATOR_STRINGIZE_NAME_0(name) #name
#define __FALCON_PP_LIST_ENUMERATOR_STRINGIZE_NAME_1(elem)\
	BOOST_PP_CAT(__FALCON_PP_LIST_ENUMERATOR_STRINGIZE_NAME_1_, FALCON_PP_VARIADIC_SIZE elem) elem
#define __FALCON_PP_LIST_ENUMERATOR_STRINGIZE_NAME_1_1(name) #name
#define __FALCON_PP_LIST_ENUMERATOR_STRINGIZE_NAME_1_2(name, s) s
#define __FALCON_PP_LIST_ENUMERATOR_ENUM_NAME(elem)\
	BOOST_PP_CAT(__FALCON_PP_LIST_ENUMERATOR_ENUM_NAME_, FALCON_PP_VARIADIC_HAS_PARENTHESIS(elem))(elem)
#define __FALCON_PP_LIST_ENUMERATOR_ENUM_NAME_0(name) name
#define __FALCON_PP_LIST_ENUMERATOR_ENUM_NAME_1(elem) FALCON_PP_VARIADIC_ARG_1 elem

namespace falcon{
namespace detail{
namespace enum_class{
template<typename _EnumIterator, std::size_t _Step>
struct __nexter_step
{
	void operator()(_EnumIterator& it)
	{
		*it = static_cast<typename _EnumIterator::value_type>(*it + _Step);
	}
};

template<typename _Enum, unsigned int _Start>
struct __lbit_trait
{
	static _Enum next(_Enum e)
	{ return static_cast<_Enum>(e << 1); }
	static _Enum prev(_Enum e)
	{ return static_cast<_Enum>(e >> 1); }
};

template<typename _Enum>
struct __lbit_trait<_Enum, 0>
{
	static _Enum next(_Enum e)
	{ return static_cast<_Enum>(e ? (e << 1) : 1); }
	static _Enum prev(_Enum e)
	{ return static_cast<_Enum>(e >> 1); }
};

template<typename _Enum>
struct __rbit_trait
{
	static _Enum next(_Enum e)
	{ return static_cast<_Enum>(e >> 1); }
	static _Enum prev(_Enum e)
	{ return static_cast<_Enum>(e << 1); }
};

template<typename _Enum, typename _BitTrait>
struct __bit_iterator
{
	_Enum _val;

	__bit_iterator()
	: _val()
	{}

	__bit_iterator(_Enum val)
	: _val(val)
	{}

	__bit_iterator& operator=(_Enum val)
	{
		_val = val;
		return *this;
	}

	__bit_iterator& operator=(__bit_iterator other)
	{
		_val = other._val;
		return *this;
	}

	_Enum operator*() const
	{ return _val; }

	__bit_iterator& operator++()
	{
		_val = _BitTrait::next(_val);
		return *this;
	}

	__bit_iterator& operator--()
	{
		_val = _BitTrait::prev(_val);
		return *this;
	}

	__bit_iterator operator++(int) const
	{
		return __bit_iterator(_BitTrait::next(_val));
	}

	__bit_iterator operator--(int) const
	{
		return __bit_iterator(_BitTrait::prev(_val));
	}
};

template<std::size_t _Size>
struct __choose_char
{ typedef wchar_t type; };

template<>
struct __choose_char<8>
{ typedef char type; };

template<typename _Enum>
std::size_t enum_to_index_string_lbit(_Enum e, _Enum start)
{
	if (start == e){
		return 0;
	}
	start = static_cast<_Enum>(start ? start << 1 : 1);
	std::size_t ret = 1;
	while (start != e)
	{
		++ret;
		start = static_cast<_Enum>(start << 1);
	}
	return ret;
}

template<typename _Enum>
std::size_t enum_to_index_string_rbit(_Enum e, _Enum start)
{
	std::size_t ret = 0;
	while (start != e)
	{
		++ret;
		start = static_cast<_Enum>(start >> 1);
	}
	return ret;
}

}
}
}

template<typename _Enum, typename _BitTrait>
bool operator==(const falcon::detail::enum_class::__bit_iterator<_Enum, _BitTrait>& a, const falcon::detail::enum_class::__bit_iterator<_Enum, _BitTrait>& b)
{ return a._val == b._val; }
template<typename _Enum, typename _BitTrait>
bool operator<(const falcon::detail::enum_class::__bit_iterator<_Enum, _BitTrait>& a, const falcon::detail::enum_class::__bit_iterator<_Enum, _BitTrait>& b)
{ return a._val < b._val; }
template<typename _Enum, typename _BitTrait>
bool operator!=(const falcon::detail::enum_class::__bit_iterator<_Enum, _BitTrait>& a, const falcon::detail::enum_class::__bit_iterator<_Enum, _BitTrait>& b)
{ return a._val != b._val; }
template<typename _Enum, typename _BitTrait>
bool operator>(const falcon::detail::enum_class::__bit_iterator<_Enum, _BitTrait>& a, const falcon::detail::enum_class::__bit_iterator<_Enum, _BitTrait>& b)
{ return a._val > b._val; }
template<typename _Enum, typename _BitTrait>
bool operator<=(const falcon::detail::enum_class::__bit_iterator<_Enum, _BitTrait>& a, const falcon::detail::enum_class::__bit_iterator<_Enum, _BitTrait>& b)
{ return a._val <= b._val; }
template<typename _Enum, typename _BitTrait>
bool operator>=(const falcon::detail::enum_class::__bit_iterator<_Enum, _BitTrait>& a, const falcon::detail::enum_class::__bit_iterator<_Enum, _BitTrait>& b)
{ return a._val >= b._val; }

#define __FALCON_PP_LIST_ENUM_RULE_START_linear(n) (n)
#define __FALCON_PP_LIST_ENUM_RULE_STEP_step(n) (n)
#define __FALCON_PP_LIST_ENUM_RULE_START_linear_step(start, step) (start)
#define __FALCON_PP_LIST_ENUM_RULE_STEP_linear_step(start, step) (step)
#define __FALCON_PP_LIST_ENUM_RULE_START_lbit(start) (start)
#define __FALCON_PP_LIST_ENUM_RULE_START_rbit(start) (start)

///TODO utiliser un not_iterator est vraiment util ?

///TODO utiliser un not_iterator<const enum_t> ?
#define __FALCON_PP_ENUMERATOR_CONTAINER_RULE_default(rule)\
	::falcon::iterator::nexter_iterator<\
		::falcon::iterator::not_iterator<enum_t>,\
		::falcon::unary_compose<\
			::falcon::enum_increment<enum_t>,\
			::falcon::pointer<falcon::iterator::not_iterator<enum_t> >\
		>\
	>
#define __FALCON_PP_ENUMERATOR_CONTAINER_RULE_linear(n)\
	__FALCON_PP_ENUMERATOR_CONTAINER_RULE_default
#define __FALCON_PP_ENUMERATOR_CONTAINER_RULE_step(n) __FALCON_PP_ENUMERATOR_CONTAINER_RULE_step_I
#define __FALCON_PP_ENUMERATOR_CONTAINER_RULE_step_I(rule)\
	::falcon::iterator::nexter_iterator<\
		::falcon::iterator::not_iterator<enum_t>,\
		::falcon::detail::enum_class::__nexter_step<\
			::falcon::iterator::not_iterator<enum_t>,\
			__FALCON_PP_LIST_ENUM_RULE_STEP_ ## rule\
		>\
	>
#define __FALCON_PP_ENUMERATOR_CONTAINER_RULE_linear_step(start, step)\
	__FALCON_PP_ENUMERATOR_CONTAINER_RULE_linear_step_I
#define __FALCON_PP_ENUMERATOR_CONTAINER_RULE_linear_step_I(rule)\
	__FALCON_PP_ENUMERATOR_CONTAINER_RULE_step_I(\
		step(__FALCON_PP_LIST_ENUM_RULE_STEP_ ## rule)\
	)
#define __FALCON_PP_ENUMERATOR_CONTAINER_RULE_lbit(rule)\
	__FALCON_PP_ENUMERATOR_CONTAINER_RULE_lbit_I
#define __FALCON_PP_ENUMERATOR_CONTAINER_RULE_lbit_I(rule)\
	::falcon::detail::enum_class::__bit_iterator<enum_t, ::falcon::detail::enum_class::__lbit_trait<enum_t, __FALCON_PP_LIST_ENUM_RULE_START_ ## rule> >
#define __FALCON_PP_ENUMERATOR_CONTAINER_RULE_rbit(rule)\
	__FALCON_PP_ENUMERATOR_CONTAINER_RULE_rbit_I
#define __FALCON_PP_ENUMERATOR_CONTAINER_RULE_rbit_I(rule)\
	::falcon::detail::enum_class::__bit_iterator<enum_t, ::falcon::detail::enum_class::__rbit_trait<enum_t> >

#define __FALCON_PP_LIST_ENUM_VALUES_default(rule, list)\
	BOOST_PP_LIST_FOR_EACH(__FALCON_PP_LIST_ENUMERATOR_ENUM_NAME_default, , list)
#define __FALCON_PP_LIST_ENUMERATOR_ENUM_NAME_default(r, data, elem) \
	BOOST_PP_COMMA_IF(BOOST_PP_NOT_EQUAL(r, 2))\
	__FALCON_PP_LIST_ENUMERATOR_ENUM_NAME(elem)
#define __FALCON_PP_LIST_ENUM_VALUES_rbit(n)\
	__FALCON_PP_LIST_ENUM_VALUES_RIGHT_BINARY
#define __FALCON_PP_LIST_ENUM_VALUE_rbit(n) = n,
#define __FALCON_PP_LIST_ENUM_VALUE2_rbit(n) n
#define __FALCON_PP_LIST_ENUM_VALUES_RIGHT_BINARY(rule, list)\
	__FALCON_PP_LIST_ENUMERATOR_ENUM_NAME(BOOST_PP_LIST_FIRST(list))\
	__FALCON_PP_LIST_ENUM_VALUE_ ## rule\
	BOOST_PP_LIST_FOR_EACH(__FALCON_PP_LIST_ENUMERATOR_ENUM_NAME_rbit, rule, BOOST_PP_LIST_REST(list))
#define __FALCON_PP_LIST_ENUMERATOR_ENUM_NAME_rbit(r, rule, elem) \
	__FALCON_PP_LIST_ENUMERATOR_ENUM_NAME_default(r, (), elem) =\
	__FALCON_PP_LIST_ENUM_VALUE2_ ## rule >> (r-1)

#define __FALCON_PP_LIST_ENUM_VALUES_lbit(n)\
	__FALCON_PP_LIST_ENUM_VALUES_LEFT_BINARY
#define __FALCON_PP_LIST_ENUM_VALUE_lbit(n) = n,
#define __FALCON_PP_LIST_ENUM_VALUE2_lbit(n) n
#define __FALCON_PP_LIST_ENUM_VALUES_LEFT_BINARY(rule, list)\
	__FALCON_PP_LIST_ENUMERATOR_ENUM_NAME(BOOST_PP_LIST_FIRST(list))\
	__FALCON_PP_LIST_ENUM_VALUE_ ## rule\
	BOOST_PP_LIST_FOR_EACH(__FALCON_PP_LIST_ENUMERATOR_ENUM_NAME_lbit, rule, BOOST_PP_LIST_REST(list))
#define __FALCON_PP_LIST_ENUMERATOR_ENUM_NAME_lbit(r, rule, elem) \
	__FALCON_PP_LIST_ENUMERATOR_ENUM_NAME_default(r, (), elem) =\
	__FALCON_PP_LIST_ENUM_VALUE2_ ## rule ? __FALCON_PP_LIST_ENUM_VALUE2_ ## rule << (r-1) : 1 << (r-2)
#define __FALCON_PP_LIST_ENUM_VALUES_linear(n)\
	__FALCON_PP_LIST_ENUM_VALUES_LINEAR
#define __FALCON_PP_LIST_ENUM_VALUES_LINEAR(rule, list)\
	__FALCON_PP_LIST_ENUMERATOR_ENUM_NAME(BOOST_PP_LIST_FIRST(list))\
	__FALCON_PP_LIST_ENUM_VALUE_ ## rule\
	__FALCON_PP_LIST_ENUM_VALUES_default(rule, BOOST_PP_LIST_REST(list))
#define __FALCON_PP_LIST_ENUM_VALUE_linear(n) = n,
#define __FALCON_PP_LIST_ENUM_VALUES_step(n)\
	__FALCON_PP_LIST_ENUM_VALUES_STEP
#define 	__FALCON_PP_LIST_ENUM_VALUES_STEP(rule, list)\
	BOOST_PP_LIST_FOR_EACH(__FALCON_PP_LIST_ENUMERATOR_ENUM_NAME_step, rule, list)
#define __FALCON_PP_LIST_ENUM_VALUE_step(n) n
#define __FALCON_PP_LIST_ENUMERATOR_ENUM_NAME_step(r, rule, elem) \
	__FALCON_PP_LIST_ENUMERATOR_ENUM_NAME_default(r, (), elem) =\
	__FALCON_PP_LIST_ENUM_VALUE_ ## rule * (r-2)
#define __FALCON_PP_LIST_ENUM_VALUES_linear_step(n, step)\
	__FALCON_PP_LIST_ENUM_VALUES_LINEAR_STEP
#define __FALCON_PP_LIST_ENUM_VALUES_LINEAR_STEP(rule, list)\
	BOOST_PP_LIST_FOR_EACH(__FALCON_PP_LIST_ENUMERATOR_ENUM_NAME_linear_step, rule, list)
#define __FALCON_PP_LIST_ENUM_VALUE_linear_step(begin, step) begin
#define __FALCON_PP_LIST_ENUM_VALUE2_linear_step(begin, step) step
#define __FALCON_PP_LIST_ENUMERATOR_ENUM_NAME_linear_step(r, rule, elem) \
	__FALCON_PP_LIST_ENUMERATOR_ENUM_NAME_default(r, (), elem) =\
	__FALCON_PP_LIST_ENUM_VALUE_ ## rule + __FALCON_PP_LIST_ENUM_VALUE2_ ## rule * (r-2)

///TODO faire un FALCON_PP_MAKE_ENUM(rule, e...) et un FALCON_PP_TUPLE_MAKE_ENUM(rule, n, tuple)
///TODO falcon/preprocessor/make_enum.hpp
//NOTE pour pouvoir l'utiliser independemant, il faudrait que cette macro travail sur une liste de nom et donc, ENUMERATOR la créerai. FALCON_PP_LIST_ENUMERATOR_VALUES_TO_ENUM_VALUES ?
#define FALCON_PP_LIST_ENUM_VALUES(rule, list)\
	__FALCON_PP_LIST_ENUM_VALUES_ ## rule(rule, list)
#define __FALCON_PP_ENUMERATOR_CONTAINER_RULE(rule)\
	__FALCON_PP_ENUMERATOR_CONTAINER_RULE_ ## rule(rule)
#define __FALCON_PP_LIST_ENUMERATOR_ARRAY_STRING_RULE(rule, list)\
	BOOST_PP_LIST_FOR_EACH(__FALCON_PP_LIST_ENUMERATOR_STRINGIZE_NAME, (), list)

#define FALCON_PP_LIST_ENUMERATOR_CHECK_NOT_SET(list)\
	void __check_syntax(BOOST_PP_LIST_FOR_EACH(__FALCON_PP_LIST_ENUMERATOR_CHECK_NOT_SET_I, , list) int)
#define __FALCON_PP_LIST_ENUMERATOR_CHECK_NOT_SET_I(r, data, elem)\
	int __FALCON_PP_LIST_ENUMERATOR_ENUM_NAME(elem),

//@{
#define __FALCON_PP_LIST_ENUM_LAST_VALUE_ITERATOR_LINEAR(list, index, add)\
	::falcon::enum_plus<enum_t>()(__FALCON_PP_LIST_ENUMERATOR_ENUM_NAME(BOOST_PP_LIST_AT(list, index)), add)
#define __FALCON_PP_LIST_ENUM_LAST_VALUE_ITERATOR_default(rule, index, list)\
	__FALCON_PP_LIST_ENUM_LAST_VALUE_ITERATOR_LINEAR(list, index, 1)
#define __FALCON_PP_LIST_ENUM_LAST_VALUE_ITERATOR_linear(n)\
	__FALCON_PP_LIST_ENUM_LAST_VALUE_ITERATOR_linear_I
#define __FALCON_PP_LIST_ENUM_LAST_VALUE_ITERATOR_linear_I(rule, index, list)\
	__FALCON_PP_LIST_ENUM_LAST_VALUE_ITERATOR_LINEAR(list, index, 1)
#define __FALCON_PP_LIST_ENUM_LAST_VALUE_ITERATOR_step(n)\
	__FALCON_PP_LIST_ENUM_LAST_VALUE_ITERATOR_step_I
#define __FALCON_PP_LIST_ENUM_LAST_VALUE_ITERATOR_step_I(rule, index, list)\
	__FALCON_PP_LIST_ENUM_LAST_VALUE_ITERATOR_LINEAR(list, index, __FALCON_PP_LIST_ENUM_RULE_STEP_ ## rule)
#define __FALCON_PP_LIST_ENUM_LAST_VALUE_ITERATOR_linear_step(n, p)\
	__FALCON_PP_LIST_ENUM_LAST_VALUE_ITERATOR_linear_step_I
#define __FALCON_PP_LIST_ENUM_LAST_VALUE_ITERATOR_linear_step_I(rule, index, list)\
	__FALCON_PP_LIST_ENUM_LAST_VALUE_ITERATOR_LINEAR(list, index, __FALCON_PP_LIST_ENUM_RULE_STEP_ ## rule)
#define __FALCON_PP_LIST_ENUM_LAST_VALUE_ITERATOR_lbit(start)\
	__FALCON_PP_LIST_ENUM_LAST_VALUE_ITERATOR_lbit_I
#define __FALCON_PP_LIST_ENUM_LAST_VALUE_ITERATOR_lbit_I(rule, index, list)\
	::falcon::enum_left_shift<enum_t>()(__FALCON_PP_LIST_ENUMERATOR_ENUM_NAME(BOOST_PP_LIST_AT(list, index)), 1)
#define __FALCON_PP_LIST_ENUM_LAST_VALUE_ITERATOR_rbit(start)\
	__FALCON_PP_LIST_ENUM_LAST_VALUE_ITERATOR_rbit_I
#define __FALCON_PP_LIST_ENUM_LAST_VALUE_ITERATOR_rbit_I(rule, index, list)\
	::falcon::enum_right_shift<enum_t>()(__FALCON_PP_LIST_ENUMERATOR_ENUM_NAME(BOOST_PP_LIST_AT(list, index)), 1)
//@}

//@{
#define __FALCON_PP_LIST_ENUM_FIRST_VALUE_ITERATOR(rule, list)\
	__FALCON_PP_LIST_ENUMERATOR_ENUM_NAME(BOOST_PP_LIST_FIRST(list))
#define __FALCON_PP_LIST_ENUM_LAST_VALUE_ITERATOR(rule, size, list)\
	__FALCON_PP_LIST_ENUM_LAST_VALUE_ITERATOR_ ## rule(rule, BOOST_PP_DEC(size), list)

#define FALCON_PP_LIST_ENUMERATOR(name, rule, list)\
	__FALCON_PP_LIST_ENUMERATOR(name, rule, BOOST_PP_LIST_SIZE(list), list)
//@}

//@{
#define __FALCON_PP_LIST_ENUMERATOR_VALUE_TO_INDEX_default(rule, n, list)\
	static_cast<std::size_t>(e)
#define __FALCON_PP_LIST_ENUMERATOR_VALUE_TO_INDEX_linear(start)\
	__FALCON_PP_LIST_ENUMERATOR_VALUE_TO_INDEX_LINEAR
#define __FALCON_PP_LIST_ENUMERATOR_VALUE_TO_INDEX_LINEAR(rule, n, list)\
	static_cast<std::size_t>(e) - __FALCON_PP_LIST_ENUM_RULE_START_ ## rule
#define __FALCON_PP_LIST_ENUMERATOR_VALUE_TO_INDEX_step(step)\
	__FALCON_PP_LIST_ENUMERATOR_VALUE_TO_INDEX_STEP
#define __FALCON_PP_LIST_ENUMERATOR_VALUE_TO_INDEX_STEP(rule, n, list)\
	static_cast<std::size_t>(e) / __FALCON_PP_LIST_ENUM_RULE_STEP_ ## rule
#define __FALCON_PP_LIST_ENUMERATOR_VALUE_TO_INDEX_linear_step(start, step)\
	__FALCON_PP_LIST_ENUMERATOR_VALUE_TO_INDEX_LINEAR_STEP
#define __FALCON_PP_LIST_ENUMERATOR_VALUE_TO_INDEX_LINEAR_STEP(rule, n, list)\
	(static_cast<std::size_t>(e) - __FALCON_PP_LIST_ENUM_RULE_START_ ## rule) / __FALCON_PP_LIST_ENUM_RULE_STEP_ ## rule
#define __FALCON_PP_LIST_ENUMERATOR_VALUE_TO_INDEX_lbit(start)\
	__FALCON_PP_LIST_ENUMERATOR_VALUE_TO_INDEX_LBIT
#define __FALCON_PP_LIST_ENUMERATOR_VALUE_TO_INDEX_LBIT(rule, n, list)\
	::falcon::detail::enum_class::enum_to_index_string_lbit(\
		e, __FALCON_PP_LIST_ENUM_FIRST_VALUE_ITERATOR(rule, list)\
	)
#define __FALCON_PP_LIST_ENUMERATOR_VALUE_TO_INDEX_rbit(start)\
	__FALCON_PP_LIST_ENUMERATOR_VALUE_TO_INDEX_RBIT
#define __FALCON_PP_LIST_ENUMERATOR_VALUE_TO_INDEX_RBIT(rule, n, list)\
	::falcon::detail::enum_class::enum_to_index_string_rbit(\
		e, __FALCON_PP_LIST_ENUM_FIRST_VALUE_ITERATOR(rule, list)\
	)

#define __FALCON_PP_LIST_ENUMERATOR_VALUE_TO_INDEX(rule, n, list)\
	__FALCON_PP_LIST_ENUMERATOR_VALUE_TO_INDEX_ ## rule(rule, n, list)
//@}

//@{
#define FALCON_PP_LIST_ENUM_ELEMENT_CHAR_TYPE(elem)\
 	BOOST_PP_CAT(FALCON_PP_LIST_ENUM_ELEMENT_CHAR_TYPE_, FALCON_PP_VARIADIC_HAS_PARENTHESIS(elem))(elem)
#define FALCON_PP_LIST_ENUM_ELEMENT_CHAR_TYPE_0(elem) \
	char
#ifdef __GXX_EXPERIMENTAL_CXX0X__
# define FALCON_PP_LIST_ENUM_ELEMENT_CHAR_TYPE_1(elem)\
	typename std::remove_const<\
		typename std::remove_reference<\
			decltype(*(__FALCON_PP_LIST_ENUMERATOR_STRINGIZE_NAME_I(elem)))\
		>::type\
	>::type
#else
# define FALCON_PP_LIST_ENUM_ELEMENT_CHAR_TYPE_1(elem)\
	::falcon::detail::enum_class::__choose_char<sizeof(__FALCON_PP_LIST_ENUMERATOR_STRINGIZE_NAME_I(elem)[0])>
#endif
//@}

#define __FALCON_PP_ENUMERATOR_OPTIMIZE_RULE_default(rule) rule
#define __FALCON_PP_ENUMERATOR_OPTIMIZE_RULE_lbit(n)\
	__FALCON_PP_ENUMERATOR_OPTIMIZE_RULE_default
#define __FALCON_PP_ENUMERATOR_OPTIMIZE_RULE_rbit(n)\
	__FALCON_PP_ENUMERATOR_OPTIMIZE_RULE_default
#define __FALCON_PP_ENUMERATOR_OPTIMIZE_RULE_step(n)\
	BOOST_PP_IF(\
		BOOST_PP_EQUAL(n, 1),\
		__FALCON_PP_ENUMERATOR_OPTIMIZE_RULE_TO_default,\
		__FALCON_PP_ENUMERATOR_OPTIMIZE_RULE_default\
	)
#define __FALCON_PP_ENUMERATOR_OPTIMIZE_RULE_TO_default(rule) default
#define __FALCON_PP_ENUMERATOR_OPTIMIZE_RULE_linear(n)\
	BOOST_PP_IF(\
		BOOST_PP_EQUAL(n, 0),\
		__FALCON_PP_ENUMERATOR_OPTIMIZE_RULE_TO_default,\
		__FALCON_PP_ENUMERATOR_OPTIMIZE_RULE_default\
	)
#define __FALCON_PP_ENUMERATOR_OPTIMIZE_RULE_linear_step(start, step)\
	BOOST_PP_IF(\
		BOOST_PP_AND(BOOST_PP_EQUAL(start, 0), BOOST_PP_EQUAL(step, 1)),\
		__FALCON_PP_ENUMERATOR_OPTIMIZE_RULE_TO_default,\
		BOOST_PP_IF(\
			BOOST_PP_EQUAL(start, 0),\
			__FALCON_PP_ENUMERATOR_OPTIMIZE_RULE_TO_step,\
			BOOST_PP_IF(\
				BOOST_PP_EQUAL(step, 1),\
				__FALCON_PP_ENUMERATOR_OPTIMIZE_RULE_TO_linear,\
				__FALCON_PP_ENUMERATOR_OPTIMIZE_RULE_default\
			)\
		)\
	)
#define __FALCON_PP_ENUMERATOR_OPTIMIZE_RULE_TO_linear(rule)\
	linear __FALCON_PP_LIST_ENUM_RULE_START_ ## rule
#define __FALCON_PP_ENUMERATOR_OPTIMIZE_RULE_TO_step(rule)\
	step __FALCON_PP_LIST_ENUM_RULE_STEP_ ## rule

#define FALCON_PP_ENUMERATOR_OPTIMIZE_RULE(rule)\
	__FALCON_PP_ENUMERATOR_OPTIMIZE_RULE_ ## rule(rule)

#define __FALCON_PP_LIST_ENUMERATOR(name, rule, n, list)\
	__FALCON_PP_LIST_ENUMERATOR_MAKE(name, FALCON_PP_ENUMERATOR_OPTIMIZE_RULE(rule), n, list)

#ifdef __GXX_EXPERIMENTAL_CXX0X__
#define __FALCON_PP_LIST_ENUMERATOR_ADJACENT_NAME(r, data, elem)\
	BOOST_PP_IF(BOOST_PP_EQUAL(r, 2), ,"\0")\
	__FALCON_PP_LIST_ENUMERATOR_STRINGIZE_NAME_I(elem)
#define __FALCON_PP_LIST_ENUMERATOR_INDEX_NAME(r, state)\
	BOOST_PP_TUPLE_ELEM(3, 1, state),
#define __FALCON_PP_LIST_ENUMERATOR_INDEX_NAME_PRED(r, state)\
	BOOST_PP_NOT_EQUAL(BOOST_PP_TUPLE_ELEM(3, 0, state), 0)
#define __FALCON_PP_LIST_ENUMERATOR_INDEX_NAME_OP(r, state)\
	(\
		BOOST_PP_DEC(BOOST_PP_TUPLE_ELEM(3, 0, state)),\
		BOOST_PP_TUPLE_ELEM(3, 1, state)\
		+ sizeof(__FALCON_PP_LIST_ENUMERATOR_STRINGIZE_NAME_I(\
				BOOST_PP_LIST_FIRST(BOOST_PP_TUPLE_ELEM(3, 2, state))\
		)) / sizeof(char_type),\
		BOOST_PP_LIST_REST(BOOST_PP_TUPLE_ELEM(3, 2, state))\
	)
# define __FALCON_PP_LIST_ENUMERATOR_INNER_STRINGS(rule, n, list)\
	class strings\
	{\
	public:\
		typedef FALCON_PP_LIST_ENUM_ELEMENT_CHAR_TYPE(BOOST_PP_LIST_FIRST(list)) char_type;\
		typedef const char_type* value_type;\
		typedef const value_type& const_reference;\
		typedef const_reference reference;\
		typedef const value_type* const_pointer;\
		typedef const_pointer pointer;\
		typedef ::falcon::detail::enum_class::__iterator<strings> iterator;\
		typedef iterator const_iterator;\
\
	friend class ::falcon::detail::enum_class::__iterator<strings>;\
\
	private:\
		static constexpr const char_type * __adjacent_names =\
			BOOST_PP_LIST_FOR_EACH(__FALCON_PP_LIST_ENUMERATOR_ADJACENT_NAME, , list);\
		const std::size_t __index_adjacent_names[n];\
\
	public:\
		constexpr strings()\
		: __index_adjacent_names{\
			BOOST_PP_FOR(\
				(n, 0, list),\
				__FALCON_PP_LIST_ENUMERATOR_INDEX_NAME_PRED,\
				__FALCON_PP_LIST_ENUMERATOR_INDEX_NAME_OP,\
				__FALCON_PP_LIST_ENUMERATOR_INDEX_NAME\
			)}\
		{}\
\
		constexpr iterator begin() const\
		{ return iterator{__index_adjacent_names}; }\
		constexpr iterator end() const\
		{ return iterator{&__index_adjacent_names[0] + sizeof(__index_adjacent_names) / sizeof(__index_adjacent_names[0])}; }\
\
		value_type operator[](std::size_t __n) const\
		{ return __adjacent_names + __index_adjacent_names[__n]; }\
\
		value_type operator[](enum_t e) const\
		{ return operator[](enum_to_index_string(e)); }\
\
	};

namespace falcon{
namespace detail{
namespace enum_class{
	template<typename _EnumString>
	struct __iterator
	{
		typedef typename _EnumString::value_type value_type;
		typedef typename _EnumString::reference reference;

		const std::size_t * _M_indexes;

		value_type operator*() const
		{ return _EnumString::__adjacent_names + *_M_indexes ; }

		__iterator& operator++()
		{
			++_M_indexes;
			return *this;
		}

		__iterator& operator--()
		{
			--_M_indexes;
			return *this;
		}
	};

	template<typename _EnumString>
	bool operator==(const __iterator<_EnumString>& a, const __iterator<_EnumString>& b)
	{ return a._M_indexes == b._M_indexes; }
	template<typename _EnumString>
	bool operator!=(const __iterator<_EnumString>& a, const __iterator<_EnumString>& b)
	{ return a._M_indexes != b._M_indexes; }
	template<typename _EnumString>
	bool operator<(const __iterator<_EnumString>& a, const __iterator<_EnumString>& b)
	{ return a._M_indexes < b._M_indexes; }
	template<typename _EnumString>
	bool operator<=(const __iterator<_EnumString>& a, const __iterator<_EnumString>& b)
	{ return a._M_indexes <= b._M_indexes; }
	template<typename _EnumString>
	bool operator>=(const __iterator<_EnumString>& a, const __iterator<_EnumString>& b)
	{ return a._M_indexes >= b._M_indexes; }
	template<typename _EnumString>
	bool operator>(const __iterator<_EnumString>& a, const __iterator<_EnumString>& b)
	{ return a._M_indexes > b._M_indexes; }
}
}
}
#else
# define __FALCON_PP_LIST_ENUMERATOR_INNER_STRINGS(rule, n, list)\
	struct __strings\
	{\
		typedef FALCON_PP_LIST_ENUM_ELEMENT_CHAR_TYPE(BOOST_PP_LIST_FIRST(list)) char_type;\
		typedef const char_type* value_type;\
		typedef const value_type& const_reference;\
		typedef const_reference reference;\
		typedef const value_type* const_pointer;\
		typedef const_pointer pointer;\
		typedef const_pointer iterator;\
		typedef iterator const_iterator;\
\
		static const_iterator begin()\
		{\
			static const char_type* a[] = { __FALCON_PP_LIST_ENUMERATOR_ARRAY_STRING_RULE(rule, list) };\
			return a;\
		}\
\
		static const_iterator end()\
		{\
			return strings::begin() + n;\
		}\
	};\
	typedef ::falcon::static_container_wrapper<__strings> strings;
#endif

///TODO cette macro pourrait être couper en plusieurs parties utiles
///NOTE enumeration pourrait utiliser FALCON_CONSTEXPR
#define __FALCON_PP_LIST_ENUMERATOR_MAKE(name, rule, n, list)\
class name\
{\
	FALCON_PP_LIST_ENUMERATOR_CHECK_NOT_SET(list);\
\
public:\
	enum enum_t { FALCON_PP_LIST_ENUM_VALUES(rule, list) };\
\
	__FALCON_PP_LIST_ENUMERATOR_INNER_STRINGS(rule, n, list)\
\
	struct enumeration\
	{\
		typedef enum_t value_type;\
		typedef value_type& reference;\
		typedef const value_type& const_reference;\
		typedef value_type* pointer;\
		typedef const value_type* const_pointer;\
		typedef __FALCON_PP_ENUMERATOR_CONTAINER_RULE(rule) iterator;\
		/*TODO typedef ????? const_iterator;*/\
\
		static /*CPP_CONSTEXPR*/ iterator begin()\
		{\
			return iterator(__FALCON_PP_LIST_ENUM_FIRST_VALUE_ITERATOR(rule, list));\
		}\
\
		static /*CPP_CONSTEXPR*/ iterator end()\
		{\
			return iterator(__FALCON_PP_LIST_ENUM_LAST_VALUE_ITERATOR(rule, n, list));\
		}\
	};\
	typedef ::falcon::static_container_wrapper<enumeration> enumeration_wrapper;\
\
	static std::size_t enum_to_index_string(enum_t e)\
	{\
		return __FALCON_PP_LIST_ENUMERATOR_VALUE_TO_INDEX(rule, n, list);\
	}\
}

///TODO ajouter les operators + et - pour les iterators
///TODO ajouter {r,cr}{begin,end} pour struct enumeration

///TODO ajouter des fonction ou/et pour retourner un container de nom de l'enum et un autre pour valeur et nom

///TODO faire en sorte que cela soit compatible C89 en utilisant FALCON_PP_TUPLE_ENUMERATOR ou FALCON_PP_LIST_ENUMERATOR avec comme element (name, str) ou P(name).

///TODO faire en sorte d'externaliser les mécanisme de construction de l'enum_class: permet de la créé avec un type enum déjà existant
///TODO pour les performances (C99), ne pas créer l'enum en static dans une fonction mais dans un tableau ce trouvant dans un namespace bidon (detail?). Est-ce vraiment mieux ?

///TODO gérer le 'enum class' et 'enum class : _T' en C++11
///TODO la construction d'enum doit pouvoir être fait en C comme en C++ (Pourra toujours être utilisé dans un projet d'école…).

#endif
