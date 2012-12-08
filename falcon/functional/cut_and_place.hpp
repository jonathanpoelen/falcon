#ifndef _FALCON_FUNCTIONAL_CUT_AND_PLACE_HPP
#define _FALCON_FUNCTIONAL_CUT_AND_PLACE_HPP

#include <cstddef>

#ifdef __GXX_EXPERIMENTAL_CXX0X__
# include <falcon/arg/arg.hpp>
#endif

namespace falcon {

#ifdef __GXX_EXPERIMENTAL_CXX0X__
template<typename _T, std::size_t _Decal, std::size_t _BeginDecal = _Decal>
struct __cut_and_place
{
	template<typename _U, typename... _Args>
	static void impl(const _T& pack, _U& a, _Args&... args)
	{
		a = static_cast<_U>(pack >> (_Decal * __CHAR_BIT__));
		__cut_and_place<_T, _Decal + _BeginDecal, _BeginDecal>::impl(pack, args...);
	}

	template<typename _U>
	static void impl(const _T& pack, _U& a)
	{
		a = static_cast<_U>(pack >> (_Decal * __CHAR_BIT__));
	}
};

template<typename _T, std::size_t _Decal>
struct __cut_and_place<_T, _Decal, _Decal>
{
	template<typename _U, typename _Z, typename... _Args>
	static void impl(const _T& pack, _U& a, _Z& b, _Args&... args)
	{
		a = static_cast<_U>(pack);
		b = static_cast<_Z>(pack >> (_Decal * __CHAR_BIT__));
		__cut_and_place<_T, _Decal*2, _Decal>::impl(pack, args...);
	}

	template<typename _U>
	static void impl(const _T& pack, _U& a)
	{
		a = static_cast<_U>(pack);
	}
};

template<typename _T, std::size_t _Size, typename _U, typename... _Args>
void cut_and_place(const _U& pack, _T& a, _Args&... args)
{
	__cut_and_place<_U, _Size>::impl(pack, a, args...);
}

template<typename _T, typename _U, typename... _Args>
void cut_and_place(const _U& pack, _T& a, _Args&... args)
{
	__cut_and_place<_U, sizeof(_T)>::impl(pack, a, args...);
}

#else

template<typename _T, std::size_t _Size = sizeof(_T), typename _U>
void cut_and_place(const _U& pack, _T& a)
{
	a = pack;
}

template<typename _T, std::size_t _Size = sizeof(_T), typename _U>
void cut_and_place(const _U& pack, _T& a, _T& b)
{
	a = pack;
	b = pack >> (_Size * __CHAR_BIT__);
}

template<typename _T, std::size_t _Size = sizeof(_T), typename _U>
void cut_and_place(const _U& pack, _T& a, _T& b, _T& c)
{
	a = pack;
	b = pack >> (_Size * __CHAR_BIT__);
	c = pack >> (_Size * __CHAR_BIT__ * 2);
}

template<typename _T, std::size_t _Size = sizeof(_T), typename _U>
void cut_and_place(const _U& pack, _T& a, _T& b, _T& c, _T& d)
{
	a = pack;
	b = pack >> (_Size * __CHAR_BIT__);
	c = pack >> (_Size * __CHAR_BIT__ * 2);
	d = pack >> (_Size * __CHAR_BIT__ * 3);
}
#endif

}

#endif
