#ifndef _FALCON_LOGICAL_VALUE_CONDITION_HPP
#define _FALCON_LOGICAL_VALUE_CONDITION_HPP

// #ifdef __GXX_EXPERIMENTAL_CXX0X__
// # include <utility>
// #endif

namespace falcon {

#ifdef __GXX_EXPERIMENTAL_CXX0X__
template<typename _T>
inline constexpr _T& first_true(_T& a)
{
	return a;
}

template<typename _T, typename... _Args>
inline constexpr _T& first_true(_T& a, _Args&... args)
{
	return a ? a : first_true<_T>(args...);
}

/*template<typename _T>
inline _T&& first_true(_T&& a)
{ return a; }

template<typename _T, typename... _Args>
inline _T first_true(_T&& a, _Args&&... args)
{ return a ? a : first_true<_T>(std::forward<_Args>(args)...); }*/
#else
template<typename _T>
inline _T& first_true(_T& a, _T& b)
{
	return a ? a : b;
}
#endif

#ifdef __GXX_EXPERIMENTAL_CXX0X__
template<typename _T>
inline constexpr _T& first_false(_T& a)
{
	return a;
}

template<typename _T, typename... _Args>
inline constexpr _T& first_false(_T& a, _Args&... args)
{
	return a ? first_false<_T>(args...) : a;
}

/*template<typename _T>
inline _T first_false(_T&& a)
{ return a; }

template<typename _T, typename... _Args>
inline _T first_false(_T&& a, _Args&&... args)
{ return a ? first_false<_T>(std::forward<_Args>(args)...) : a; }*/
#else
template<typename _T>
inline _T& first_false(_T& a, _T& b)
{
	return a ? b : a;
}
#endif

}

#endif
