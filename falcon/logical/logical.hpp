#ifndef _FALCON_LOGICAL_LOGICAL_HPP
#define _FALCON_LOGICAL_LOGICAL_HPP

#include <initializer_list>
#include <type_traits>

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
//@}

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
		bool operator()()\
		{ return false; }\
		\
		template <typename... _Args>\
		bool operator()(const _Args&... args)\
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

}
}

#endif
