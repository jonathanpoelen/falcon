#ifndef FALCON_LOGICAL_LOGICAL_HPP
#define FALCON_LOGICAL_LOGICAL_HPP

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
template<typename T, typename U, typename... Args>
constexpr bool equal_to_or(const T& a, const U& b, const Args&... args);

template<typename T, typename U, typename... Args>
inline constexpr bool equal_to_and(const T& a, const U& b, const Args&... args);

template<typename T, typename U, typename... Args>
constexpr bool not_equal_to_or(const T& a, const U& b, const Args&... args);

template<typename T, typename U, typename... Args>
constexpr bool not_equal_to_and(const T& a, const U& b, const Args&... args);

template<typename T, typename U, typename... Args>
constexpr bool greater_or(const T& a, const U& b, const Args&... args);

template<typename T, typename U, typename... Args>
constexpr bool greater_and(const T& a, const U& b, const Args&... args);

template<typename T, typename U, typename... Args>
constexpr bool less_equal_or(const T& a, const U& b, const Args&... args);

template<typename T, typename U, typename... Args>
constexpr bool less_equal_and(const T& a, const U& b, const Args&... args);

template<typename T, typename U, typename... Args>
constexpr bool greater_or(const T& a, const U& b, const Args&... args);

template<typename T, typename U, typename... Args>
constexpr bool greater_and(const T& a, const U& b, const Args&... args);

template<typename T, typename U, typename... Args>
constexpr bool greater_equal_or(const T& a, const U& b, const Args&... args);

template<typename T, typename U, typename... Args>
constexpr bool greater_equal_and(const T& a, const U& b, const Args&... args);

template<typename _Predicate, typename T, typename U, typename... Args>
constexpr bool equal_if_or(_Predicate, const T& a, const U& b, const Args&... args);

template<typename _Predicate, typename T, typename U, typename... Args>
constexpr bool equal_if_and(_Predicate, const T& a, const U& b, const Args&... args);

template<typename _Predicate, typename T, typename U, typename... Args>
constexpr bool not_equal_if_or(_Predicate, const T& a, const U& b, const Args&... args);

template<typename _Predicate, typename T, typename U, typename... Args>
constexpr bool not_equal_if_and(_Predicate, const T& a, const U& b, const Args&... args);


template<typename T, typename U>
constexpr bool equal_to_or(const T& a, const U& b);

template<typename T, typename U>
constexpr bool equal_to_and(const T& a, const U& b);

template<typename T, typename U>
constexpr bool not_equal_to_or(const T& a, const U& b);

template<typename T, typename U>
constexpr bool not_equal_to_and(const T& a, const U& b);

template<typename T, typename U>
constexpr bool greater_or(const T& a, const U& b);

template<typename T, typename U>
constexpr bool greater_and(const T& a, const U& b);

template<typename T, typename U>
constexpr bool less_equal_or(const T& a, const U& b);

template<typename T, typename U>
constexpr bool less_equal_and(const T& a, const U& b);

template<typename T, typename U>
constexpr bool greater_or(const T& a, const U& b);

template<typename T, typename U>
constexpr bool greater_and(const T& a, const U& b);

template<typename T, typename U>
constexpr bool greater_equal_or(const T& a, const U& b);

template<typename T, typename U>
constexpr bool greater_equal_and(const T& a, const U& b);

template<typename _Predicate, typename T, typename U>
constexpr bool equal_if_or(_Predicate, const T& a, const U& b);

template<typename _Predicate, typename T, typename U>
constexpr bool equal_if_and(_Predicate, const T& a, const U& b);

template<typename _Predicate, typename T, typename U>
constexpr bool not_equal_if_or(_Predicate, const T& a, const U& b);

template<typename _Predicate, typename T, typename U>
constexpr bool not_equal_if_and(_Predicate, const T& a, const U& b);


template <typename T>
struct equal_to_or_wrapper;

template <typename T>
struct equal_to_and_wrapper;

template <typename T>
struct not_equal_to_or_wrapper;

template <typename T>
struct not_equal_to_and_wrapper;

template <typename T>
struct greater_or_wrapper;

template <typename T>
struct greater_and_wrapper;

template <typename T>
struct less_equal_or_wrapper;

template <typename T>
struct less_equal_and_wrapper;

template <typename T>
struct greater_or_wrapper;

template <typename T>
struct greater_and_wrapper;

template <typename T>
struct greater_equal_or_wrapper;

template <typename T>
struct greater_equal_and_wrapper;

template <typename _Predicate, typename T>
struct equal_if_or_wrapper;

template <typename _Predicate, typename T>
struct equal_if_and_wrapper;

template <typename _Predicate, typename T>
struct not_equal_if_or_wrapper;

template <typename _Predicate, typename T>
struct not_equal_if_and_wrapper;
//@}


template <typename _Predicate, typename T>
equal_if_or_wrapper<_Predicate, T> make_equal_if_or(_Predicate, T&&);

template <typename _Predicate, typename T>
equal_if_or_wrapper<_Predicate, T> make_equal_if_or(T&&);

template <typename _Predicate, typename T>
equal_if_and_wrapper<_Predicate, T> make_equal_if_and(_Predicate, T&&);

template <typename _Predicate, typename T>
equal_if_and_wrapper<_Predicate, T> make_equal_if_and(T&&);

template <typename _Predicate, typename T>
not_equal_if_or_wrapper<_Predicate, T> make_not_equal_if_or(_Predicate, T&&);

template <typename _Predicate, typename T>
not_equal_if_or_wrapper<_Predicate, T> make_not_equal_if_or(T&&);

template <typename _Predicate, typename T>
not_equal_if_and_wrapper<_Predicate, T> make_not_equal_if_and(_Predicate, T&&);

template <typename _Predicate, typename T>
not_equal_if_and_wrapper<_Predicate, T> make_not_equal_if_and(T&&);


#define __FALCON_MAKE_LOGICAL_FUNC(name, op, op_name)\
	template<typename T, typename U>\
	inline constexpr bool name##_##op_name(const T& a, const U& b)\
	{ return a == b; }\
	\
	template<typename T, typename U, typename... Args>\
	constexpr bool name##_##op_name(const T& a, const U& b, const Args&... args)\
	{ return a == b op_name name##_##op_name(a, args...); }\
	\
	template <typename T>\
	struct name##_##op_name##_wrapper\
	{\
		T _value;\
		\
		constexpr bool operator()() const\
		{ return false; }\
		\
		template <typename... Args>\
		constexpr bool operator()(const Args&... args) const\
		{ return name##_##op_name<Args...>(_value, args...); }\
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
template<typename _Predicate, typename T, typename U>\
	inline constexpr bool __##prefix_op##_##equal_if_##op(_Predicate & pred, const T& a, const U& b)\
	{ return prefix_op pred(a,b); }\
	\
	template<typename _Predicate, typename T, typename U, typename... Args>\
	constexpr bool __##prefix_op##_##equal_if_##op(_Predicate & pred, const T& a, const U& b, const Args&... args)\
	{ return (prefix_op pred(a,b)) op __##prefix_op##_##equal_if_##op(a, args...); }\
	\
	template<typename _Predicate, typename T, typename U>\
	inline constexpr bool name##_##op(_Predicate pred, const T& a, const U& b)\
	{ return pred(a,b); }\
	\
	template<typename _Predicate, typename T, typename U, typename... Args>\
	constexpr bool name##_##op(_Predicate pred, const T& a, const U& b, const Args&... args)\
	{ return pred(a,b) op __##prefix_op##_##equal_if_##op(a, args...); }\
	\
	template <typename _Predicate, typename T>\
	struct __FALCON_LOGICAL_NAME(prefix_op##_##equal_if_##op##_wrapper)\
	{\
		_Predicate _pred;\
		T _value;\
	\
		constexpr bool operator()() const\
		{ return false; }\
	\
		template <typename... Args>\
		constexpr bool operator()(const Args&... args) const\
		{ return __##prefix_op##_##equal_if_##op<Args...>(_pred, _value, args...); }\
	};\
	\
	template <typename _Predicate, typename T>\
	prefix_op##_##equal_if_##op##_wrapper<_Predicate, T>\
	make_##prefix_op##_##equal_if_##op(_Predicate pred, T&& v)\
	{ return {pred, std::forward<T>(v)}; }\
	\
	template <typename _Predicate, typename T>\
	prefix_op##_##equal_if_##op##_wrapper<_Predicate, T>\
	make_##prefix_op##_##equal_if_##op(T&& v)\
	{ return {_Predicate(), std::forward<T>(v)}; }

__FALCON_MAKE_LOGICAL_FUNC(or,,)
__FALCON_MAKE_LOGICAL_FUNC(and,,)
__FALCON_MAKE_LOGICAL_FUNC(or, not, _)
__FALCON_MAKE_LOGICAL_FUNC(and, not, _)

#undef __FALCON_MAKE_LOGICAL_FUNC
#undef __FALCON_LOGICAL_NAME

}
}

#endif
