#ifndef _FALCON_TUPLE_DETAIL_OPERATORS_HPP
#define _FALCON_TUPLE_DETAIL_OPERATORS_HPP

namespace falcon {

namespace tuple {

namespace operators {

#define __FALCON_TUPLE_OPERATOR(name)\
	template<unsigned i, unsigned len, typename _Tuple>\
	struct __##name;\
	template<unsigned i, unsigned len, typename _Tuple>\
	void name(const _Tuple& t);\
	template<typename _Tuple>\
	void name(const _Tuple& t);

__FALCON_TUPLE_OPERATOR(reduce_plus)
__FALCON_TUPLE_OPERATOR(reduce_minus)
__FALCON_TUPLE_OPERATOR(reduce_multiplies)
__FALCON_TUPLE_OPERATOR(reduce_divides)
__FALCON_TUPLE_OPERATOR(reduce_modulus)

__FALCON_TUPLE_OPERATOR(reduce_equals)
__FALCON_TUPLE_OPERATOR(reduce_not_equals)

__FALCON_TUPLE_OPERATOR(reduce_logical_and)
__FALCON_TUPLE_OPERATOR(reduce_logical_or)

__FALCON_TUPLE_OPERATOR(reduce_bit_and)
__FALCON_TUPLE_OPERATOR(reduce_bit_or)
__FALCON_TUPLE_OPERATOR(reduce_bit_xor)

#undef __FALCON_TUPLE_OPERATOR

#define __FALCON_TUPLE_OPERATOR(name)\
	template<unsigned i, unsigned len, typename _Tuple>\
	struct __##name;\
	template<unsigned i, unsigned len, typename _Tuple>\
	_Tuple name(const _Tuple& t);\
	template<typename _Tuple>\
	_Tuple name(const _Tuple& t);

__FALCON_TUPLE_OPERATOR(increment)
__FALCON_TUPLE_OPERATOR(decrement)

#undef __FALCON_TUPLE_OPERATOR

#define __FALCON_TUPLE_OPERATOR(name)\
	template<unsigned i, unsigned len, typename _T, typename _Tuple>\
	struct __##name;\
	template<unsigned i, unsigned len, typename _T, typename _Tuple>\
	_Tuple name(const _Tuple& t, const _T& v);\
	template<typename _T, typename _Tuple>\
	_Tuple name(const _Tuple& t, const _T& v);

__FALCON_TUPLE_OPERATOR(plus_equal)
__FALCON_TUPLE_OPERATOR(minus_equal)
__FALCON_TUPLE_OPERATOR(multiplies_equal)
__FALCON_TUPLE_OPERATOR(divides_equal)
__FALCON_TUPLE_OPERATOR(modulus_equal)

__FALCON_TUPLE_OPERATOR(bit_and_equal)
__FALCON_TUPLE_OPERATOR(bit_or_equal)
__FALCON_TUPLE_OPERATOR(bit_xor_equal)

#undef __FALCON_TUPLE_OPERATOR

#define __FALCON_TUPLE_OPERATOR(name)\
	template<unsigned i, unsigned len, typename _Tuple>\
	struct __##name;\
	template<unsigned i, unsigned len, typename _Tuple>\
	bool name(const _Tuple& t, const _Tuple& t2);\
	template<typename _Tuple>\
	bool name(const _Tuple& t, const _Tuple& t2);

__FALCON_TUPLE_OPERATOR(each_equal)
__FALCON_TUPLE_OPERATOR(each_not_equal)
__FALCON_TUPLE_OPERATOR(each_less)
__FALCON_TUPLE_OPERATOR(each_greater)
__FALCON_TUPLE_OPERATOR(each_less_equal)
__FALCON_TUPLE_OPERATOR(each_greater_equal)

#undef __FALCON_TUPLE_OPERATOR

template<unsigned i, unsigned len, typename _Tuple, typename _Binary, typename _T>
struct __binary_function;

template<unsigned i, unsigned len, typename _Tuple, typename _Binary>
void binary_function(_Tuple& t, _Binary binary);

template<typename _Tuple, typename _Binary>
void binary_function(_Tuple& t, _Binary binary);

}

}

}

#endif