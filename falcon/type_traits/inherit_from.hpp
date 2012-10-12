#ifndef _FALCON_TYPE_TRAITS_INHERIT_FROM_HPP
#define _FALCON_TYPE_TRAITS_INHERIT_FROM_HPP

#include <type_traits>
#include <falcon/type_traits/yes_no_type.hpp>

namespace falcon {

template<typename _T, typename _Inherit>
struct __inherit_from
{
	static yes_type __test(_Inherit&);
	static no_type __test(...);
};

template<typename _T, typename _Inherit>
struct __inherit_from<const _T, _Inherit>
{
	static yes_type __test(const _Inherit&);
	static no_type __test(...);
};

/**
 *  Use SFINAE to determine if the type @p _T has a publicly-accessible
 *  inherited from @p _Inherit or is convertible to _Inherit& (or const _Inherit& if _T is const).
 */
template<typename _T, typename _Inherit>
struct inherit_from
{
	static const bool value = is_yes_type<
#ifdef __GXX_EXPERIMENTAL_CXX0X__
		decltype(__inherit_from<_T, _Inherit>::__test(std::declval<_T&>()))
#else
		typeof(__inherit_from<_T, _Inherit>::__test(*static_cast<_T*>(static_cast<void*>(0))))
#endif
	>::value;
};

}

#endif