#ifndef _FALCON_UTILITY_SWAP_PROXY_HPP
#define _FALCON_UTILITY_SWAP_PROXY_HPP

#include <utility>
#include <falcon/preprocessor/move.hpp>
#ifdef __GXX_EXPERIMENTAL_CXX0X__
# include<type_traits>
#else
# include <boost/type_traits/remove_all_extents.hpp>
#endif
#include <falcon/detail/dep_nspace.hpp>

namespace falcon {

template <typename _T1, typename _T2, typename _Intermediary>
struct __swap_proxy
{
	static void swap_proxy(_T1& a, _T2& b)
	{
		_Intermediary tmp = static_cast<_Intermediary>(a);
		a = static_cast<_T1>(b);
		b = static_cast<_T2>(tmp);
	}
};

template <typename _T>
struct __swap_proxy<_T, _T, _T>
{
	static void swap_proxy(_T& a, _T& b)
	{
		std::swap<>(a, b);
	}
};


///Swap for different type
template <typename _T1, typename _T2, typename _Intermediary = typename _FALCON_DEP_NSPACE(remove_all_extents)<_T1>::type>
void swap_proxy(_T1& a, _T2& b)
{
	__swap_proxy<_T1, _T2, _Intermediary>::swap_proxy(a,b);
}

///Swap for different type array
template <typename _T1, typename _T2, std::size_t _N, typename _Intermediary = typename _FALCON_DEP_NSPACE(remove_all_extents)<_T1>::type>
void swap_proxy(_T1 (&a) [_N], _T2 (&b) [_N])
{
	for (std::size_t i = 0; i < _N; ++i)
		swap_proxy<_T1, _T2, _Intermediary>(a[i], b[i]);
}
}

#endif
