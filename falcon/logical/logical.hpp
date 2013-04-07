#ifndef _FALCON_LOGICAL_LOGICAL_HPP
#define _FALCON_LOGICAL_LOGICAL_HPP

#include <type_traits>
#include <utility>

namespace falcon {
namespace logical {

//@{
/**
* equal_to_or(5,5,1,2) different to (5 == 5 || 5 == 1 || 5 == 2) because all values are instanciat.
* With not
* @code
* int ref = 5, a = 5, b = 1, c = 2;
* equal_to_or(ref, a, b, c);
* @endcode
* because values pass to reference
*/
template<typename _T, typename _U, typename... _Args>
constexpr bool equal_to_or(const _T& a, const _U& b, const _Args&... args);

template<typename _T, typename _U, typename... _Args>
inline constexpr bool equal_to_and(const _T& a, const _U& b, const _Args&... args);

template<typename _T, typename _U, typename... _Args>
constexpr bool not_equal_to_or(const _T& a, const _U& b, const _Args&... args);

template<typename _T, typename _U, typename... _Args>
constexpr bool not_equal_to_and(const _T& a, const _U& b, const _Args&... args);

template<typename _T, typename _U, typename... _Args>
constexpr bool greater_or(const _T& a, const _U& b, const _Args&... args);

template<typename _T, typename _U, typename... _Args>
constexpr bool greater_and(const _T& a, const _U& b, const _Args&... args);

template<typename _T, typename _U, typename... _Args>
constexpr bool less_equal_or(const _T& a, const _U& b, const _Args&... args);

template<typename _T, typename _U, typename... _Args>
constexpr bool less_equal_and(const _T& a, const _U& b, const _Args&... args);

template<typename _T, typename _U, typename... _Args>
constexpr bool greater_or(const _T& a, const _U& b, const _Args&... args);

template<typename _T, typename _U, typename... _Args>
constexpr bool greater_and(const _T& a, const _U& b, const _Args&... args);

template<typename _T, typename _U, typename... _Args>
constexpr bool greater_equal_or(const _T& a, const _U& b, const _Args&... args);

template<typename _T, typename _U, typename... _Args>
constexpr bool greater_equal_and(const _T& a, const _U& b, const _Args&... args);

template<typename _Predicate, typename _T, typename _U, typename... _Args>
constexpr bool equal_if_or(_Predicate, const _T& a, const _U& b, const _Args&... args);

template<typename _Predicate, typename _T, typename _U, typename... _Args>
constexpr bool equal_if_and(_Predicate, const _T& a, const _U& b, const _Args&... args);

template<typename _Predicate, typename _T, typename _U, typename... _Args>
constexpr bool not_equal_if_or(_Predicate, const _T& a, const _U& b, const _Args&... args);

template<typename _Predicate, typename _T, typename _U, typename... _Args>
constexpr bool not_equal_if_and(_Predicate, const _T& a, const _U& b, const _Args&... args);


template<typename _T, typename _U>
constexpr bool equal_to_or(const _T& a, const _U& b);

template<typename _T, typename _U>
constexpr bool equal_to_and(const _T& a, const _U& b);

template<typename _T, typename _U>
constexpr bool not_equal_to_or(const _T& a, const _U& b);

template<typename _T, typename _U>
constexpr bool not_equal_to_and(const _T& a, const _U& b);

template<typename _T, typename _U>
constexpr bool greater_or(const _T& a, const _U& b);

template<typename _T, typename _U>
constexpr bool greater_and(const _T& a, const _U& b);

template<typename _T, typename _U>
constexpr bool less_equal_or(const _T& a, const _U& b);

template<typename _T, typename _U>
constexpr bool less_equal_and(const _T& a, const _U& b);

template<typename _T, typename _U>
constexpr bool greater_or(const _T& a, const _U& b);

template<typename _T, typename _U>
constexpr bool greater_and(const _T& a, const _U& b);

template<typename _T, typename _U>
constexpr bool greater_equal_or(const _T& a, const _U& b);

template<typename _T, typename _U>
constexpr bool greater_equal_and(const _T& a, const _U& b);

template<typename _Predicate, typename _T, typename _U>
constexpr bool equal_if_or(_Predicate, const _T& a, const _U& b);

template<typename _Predicate, typename _T, typename _U>
constexpr bool equal_if_and(_Predicate, const _T& a, const _U& b);

template<typename _Predicate, typename _T, typename _U>
constexpr bool not_equal_if_or(_Predicate, const _T& a, const _U& b);

template<typename _Predicate, typename _T, typename _U>
constexpr bool not_equal_if_and(_Predicate, const _T& a, const _U& b);


template <typename _T>
struct equal_to_or_wrapper;

template <typename _T>
struct equal_to_and_wrapper;

template <typename _T>
struct not_equal_to_or_wrapper;

template <typename _T>
struct not_equal_to_and_wrapper;

template <typename _T>
struct greater_or_wrapper;

template <typename _T>
struct greater_and_wrapper;

template <typename _T>
struct less_equal_or_wrapper;

template <typename _T>
struct less_equal_and_wrapper;

template <typename _T>
struct greater_or_wrapper;

template <typename _T>
struct greater_and_wrapper;

template <typename _T>
struct greater_equal_or_wrapper;

template <typename _T>
struct greater_equal_and_wrapper;

template <typename _Predicate, typename _T>
struct equal_if_or_wrapper;

template <typename _Predicate, typename _T>
struct equal_if_and_wrapper;

template <typename _Predicate, typename _T>
struct not_equal_if_or_wrapper;

template <typename _Predicate, typename _T>
struct not_equal_if_and_wrapper;
//@}


template <typename _Predicate, typename _T>
equal_if_or_wrapper<_Predicate, _T> make_equal_if_or(_Predicate, _T&&);

template <typename _Predicate, typename _T>
equal_if_or_wrapper<_Predicate, _T> make_equal_if_or(_T&&);

template <typename _Predicate, typename _T>
equal_if_and_wrapper<_Predicate, _T> make_equal_if_and(_Predicate, _T&&);

template <typename _Predicate, typename _T>
equal_if_and_wrapper<_Predicate, _T> make_equal_if_and(_T&&);

template <typename _Predicate, typename _T>
not_equal_if_or_wrapper<_Predicate, _T> make_not_equal_if_or(_Predicate, _T&&);

template <typename _Predicate, typename _T>
not_equal_if_or_wrapper<_Predicate, _T> make_not_equal_if_or(_T&&);

template <typename _Predicate, typename _T>
not_equal_if_and_wrapper<_Predicate, _T> make_not_equal_if_and(_Predicate, _T&&);

template <typename _Predicate, typename _T>
not_equal_if_and_wrapper<_Predicate, _T> make_not_equal_if_and(_T&&);


#define __FALCON_MAKE_LOGICAL_FUNC(name, op, op_name)\
	template<typename _T, typename _U>\
	inline constexpr bool name##_##op_name(const _T& a, const _U& b)\
	{ return a == b; }\
	\
	template<typename _T, typename _U, typename... _Args>\
	constexpr bool name##_##op_name(const _T& a, const _U& b, const _Args&... args)\
	{ return a == b op_name name##_##op_name(a, args...); }\
	\
	template <typename _T>\
	struct name##_##op_name##_wrapper\
	{\
		_T _value;\
		\
		constexpr bool operator()() const\
		{ return false; }\
		\
		template <typename... _Args>\
		constexpr bool operator()(const _Args&... args) const\
		{ return name##_##op_name<_Args...>(_value, args...); }\
	};

#define __FALCON_MAKE2_LOGICAL_FUNC(name, op)\
	__FALCON_MAKE_LOGICAL_FUNC(name, op, or)\
	__FALCON_MAKE_LOGICAL_FUNC(name, op, and)

__FALCON_MAKE2_LOGICAL_FUNC(equal_to, ==)
__FALCON_MAKE2_LOGICAL_FUNC(not_equal_to, !=)
__FALCON_MAKE2_LOGICAL_FUNC(less, <)
__FALCON_MAKE2_LOGICAL_FUNC(greater, >)
__FALCON_MAKE2_LOGICAL_FUNC(less_equal, <=)
__FALCON_MAKE2_LOGICAL_FUNC(greater_equal, >=)

#undef __FALCON_MAKE2_LOGICAL_FUNC
#undef __FALCON_MAKE_LOGICAL_FUNC

#define __FALCON_LOGICAL_NAME(x) x
#define __FALCON_MAKE_LOGICAL_FUNC(op, prefix_op, _)\
template<typename _Predicate, typename _T, typename _U>\
	inline constexpr bool __##prefix_op##_##equal_if_##op(_Predicate & pred, const _T& a, const _U& b)\
	{ return prefix_op pred(a,b); }\
	\
	template<typename _Predicate, typename _T, typename _U, typename... _Args>\
	constexpr bool __##prefix_op##_##equal_if_##op(_Predicate & pred, const _T& a, const _U& b, const _Args&... args)\
	{ return (prefix_op pred(a,b)) op __##prefix_op##_##equal_if_##op(a, args...); }\
	\
	template<typename _Predicate, typename _T, typename _U>\
	inline constexpr bool name##_##op(_Predicate pred, const _T& a, const _U& b)\
	{ return pred(a,b); }\
	\
	template<typename _Predicate, typename _T, typename _U, typename... _Args>\
	constexpr bool name##_##op(_Predicate pred, const _T& a, const _U& b, const _Args&... args)\
	{ return pred(a,b) op __##prefix_op##_##equal_if_##op(a, args...); }\
	\
	template <typename _Predicate, typename _T>\
	struct __FALCON_LOGICAL_NAME(prefix_op##_##equal_if_##op##_wrapper)\
	{\
		_Predicate _pred;\
		_T _value;\
	\
		constexpr bool operator()() const\
		{ return false; }\
	\
		template <typename... _Args>\
		constexpr bool operator()(const _Args&... args) const\
		{ return __##prefix_op##_##equal_if_##op<_Args...>(_pred, _value, args...); }\
	};\
	\
	template <typename _Predicate, typename _T>\
	prefix_op##_##equal_if_##op##_wrapper<_Predicate, _T>\
	make_##prefix_op##_##equal_if_##op(_Predicate pred, _T&& v)\
	{ return {pred, std::forward<_T>(v)}; }\
	\
	template <typename _Predicate, typename _T>\
	prefix_op##_##equal_if_##op##_wrapper<_Predicate, _T>\
	make_##prefix_op##_##equal_if_##op(_T&& v)\
	{ return {_Predicate(), std::forward<_T>(v)}; }

__FALCON_MAKE_LOGICAL_FUNC(or,,)
__FALCON_MAKE_LOGICAL_FUNC(and,,)
__FALCON_MAKE_LOGICAL_FUNC(or, not, _)
__FALCON_MAKE_LOGICAL_FUNC(and, not, _)

#undef __FALCON_MAKE_LOGICAL_FUNC
#undef __FALCON_LOGICAL_NAME

}
}

#endif
