#ifndef _FALCON_TEST_TYPE_TRAITS_TEST_HPP
#define _FALCON_TEST_TYPE_TRAITS_TEST_HPP

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <type_traits>
#include <boost/static_assert.hpp>
#include <falcon/c++0x/keywords.hpp>


#define __FALCON_TEST_TO_MAIN(func_test_name) int main() { func_test_name(); return 0;}
#define __FALCON_USELESS_TEST_TO_MAIN(func_test_name)

#ifndef FALCON_ALL_TEST
# ifndef FALCON_GROUP_TEST
#  define FALCON_GROUP_TEST_TO_MAIN __FALCON_USELESS_TEST_TO_MAIN
#  define FALCON_TEST_TO_MAIN __FALCON_TEST_TO_MAIN
# else
#  define FALCON_GROUP_TEST_TO_MAIN __FALCON_TEST_TO_MAIN
#  define FALCON_TEST_TO_MAIN __FALCON_USELESS_TEST_TO_MAIN
# endif
#else
# define FALCON_TEST_TO_MAIN __FALCON_USELESS_TEST_TO_MAIN
# define FALCON_GROUP_TEST_TO_MAIN __FALCON_USELESS_TEST_TO_MAIN
#endif


#define STATIC_ASSERT(...) BOOST_STATIC_ASSERT((__VA_ARGS__))

#define CHECK_NOTYPENAME_TYPE(_T, ...) STATIC_ASSERT(std::is_same<_T, __VA_ARGS__>::value)

#define CHECK_TYPE(_T, ...) CHECK_NOTYPENAME_TYPE(_T, typename __VA_ARGS__::type)

#define CHECKNO_TYPENAME_TYPE(_T, ...) STATIC_ASSERT(!std::is_same<_T, __VA_ARGS__>::value)

#define CHECKNO_TYPE(_T, ...) CHECKNO_TYPENAME_TYPE(_T, typename __VA_ARGS__::type)

#define STATIC_CHECK_VALUE(_T, ...) STATIC_ASSERT(_T == (__VA_ARGS__::value))
#define STATIC_CHECKNO_VALUE(_T, ...) STATIC_ASSERT(_T != (__VA_ARGS__::value))

//NOTE std::cerr for don't touch std::cout (use in tests)
#define PASSED() std::cerr << __FILE__ " line " << __LINE__ << ' ' << "passed" << std::endl

#define __END_CHECK else PASSED()

#define CHECK(r) if (!(r)){\
	std::stringstream _Oss;\
	_Oss << "bad check in " __FILE__ " line " << __LINE__;\
	throw std::runtime_error(_Oss.str());\
} __END_CHECK

template<typename _T>
std::ostream& __show_value_test(std::ostream& oss, const _T& v)
{ return oss << v; }

inline std::ostream& __show_value_test(std::ostream& oss, std::nullptr_t&)
{ return oss << "null"; }

#define CHECK_VALUE(op, a, ...) do{\
auto tmp_CHECK_VALUE = (a);\
auto tmp_CHECK_VALUE2 = (__VA_ARGS__);\
if (!(tmp_CHECK_VALUE op tmp_CHECK_VALUE2)){\
	std::stringstream _Oss;\
	_Oss << "bad check for [ " #a " " #op " " #__VA_ARGS__ " ] in " __FILE__ " at line " << __LINE__ << "\n value is: ";\
	__show_value_test(_Oss, tmp_CHECK_VALUE) << "\n------------------------\nresult is: ";\
	__show_value_test(_Oss, tmp_CHECK_VALUE2);\
	throw std::runtime_error(_Oss.str());\
} __END_CHECK;}while(0)

#define CHECK_EQUAL_VALUE(a, ...) CHECK_VALUE(==, a, __VA_ARGS__)

#endif