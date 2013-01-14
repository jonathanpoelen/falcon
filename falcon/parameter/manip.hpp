#ifndef _FALCON_PARAMETER_MANIP_HPP
#define _FALCON_PARAMETER_MANIP_HPP

#include <cstddef>
#include <falcon/parameter/parameter_pack.hpp>

namespace falcon {
namespace parameter {

template<typename _Pack>
class pack_size;

template<typename... _Elements>
struct pack_size<parameter_pack<_Elements...> >
{
	static const std::size_t value = sizeof...(_Elements);
};

template <typename _Pack, typename... _Args>
class __pack_add_left;

template <typename... _Elements, typename... _Args>
struct __pack_add_left<parameter_pack<_Elements...>, _Args...>
{
	typedef parameter_pack<_Args..., _Elements...> __type;
};

/**
 * @brief Add @a _Args to left a _Pack
 * _Pack must is a @ref parameter_pack
 */
template <typename _Pack, typename... _Args>
struct pack_add_left
{
	typedef typename __pack_add_left<_Pack, _Args...>::__type type;
};


template <typename _Pack, typename... _Args>
class __pack_add_right;

template <typename... _Elements, typename... _Args>
struct __pack_add_right<parameter_pack<_Elements...>, _Args...>
{
	typedef parameter_pack<_Elements..., _Args...> __type;
};

/**
 * @brief Add @a _Args to right a _Pack
 * _Pack must is a @ref parameter_pack
 */
template <typename _Pack, typename... _Args>
struct pack_add_right
{
	typedef typename __pack_add_right<_Pack, _Args...>::__type type;
};


template <typename... _Pack>
class __pack_cat;

template <typename... _Elements, typename... _Elements2, typename... _OtherPack>
struct __pack_cat<parameter_pack<_Elements...>, parameter_pack<_Elements2...>, _OtherPack...>
: __pack_cat<parameter_pack<_Elements..., _Elements2...>, _OtherPack...>
{};

template <typename... _Elements>
struct __pack_cat<parameter_pack<_Elements...>>
{
	typedef parameter_pack<_Elements...> __type;
};

/**
 * @brief concat two _Pack or more
 * _Pack must is a @ref parameter_pack
 */
template <typename... _Pack>
struct pack_cat
{ typedef typename __pack_cat<_Pack...>::__type type; };


template <template<class...> class _Wrapper, typename _Pack>
class __pack_wrapper;

template <template<class...> class _Wrapper, typename... _Elements>
struct __pack_wrapper<_Wrapper, parameter_pack<_Elements...> >
{
	typedef parameter_pack<_Wrapper<_Elements>...> __type;
};

/**
 * @brief Wrap each value of _Pack with _Wrapper
 * _Pack must is a @ref parameter_pack
 */
template <template<class...> class _Wrapper, typename _Pack>
struct pack_wrapper
{
	typedef typename __pack_wrapper<_Wrapper, _Pack>::__type type;
};


template <typename _Pack>
struct __pack_use_type;

template <typename... _Elements>
struct __pack_use_type<parameter_pack<_Elements...>>
{
	typedef parameter_pack<typename _Elements::type...> __type;
};

/**
 * @brief Get each inner type of _Pack
 * _Pack must is a @ref parameter_pack
 */
template <typename _Pack>
struct pack_use_type
{
	typedef typename __pack_use_type<_Pack>::__type type;
};

/**
 * @brief Use _Modifier each value of _Pack
 * _Pack must is a @ref parameter_pack
 */
template <template<class...> class _Modifier, typename _Pack>
struct pack_modifier
{
	typedef typename __pack_use_type<
		typename pack_wrapper<_Modifier, _Pack>::type
	>::__type type;
};


template <typename _Pack, typename _T, std::size_t _N>
struct __build_pack;

template <typename... _Elements, typename _T, std::size_t _N>
struct __build_pack<parameter_pack<_Elements...>, _T, _N>
: __build_pack<parameter_pack<_Elements..., _T>, _T, _N-1>
{};

template <typename... _Elements, typename _T>
struct __build_pack<parameter_pack<_Elements...>, _T, 0>
{
	typedef parameter_pack<_Elements...> __type;
};

/// Build parameter_pack with number _N of type _T
template <typename _T, std::size_t _N>
struct build_pack
{
	typedef typename __build_pack<parameter_pack<>, _T, _N>::__type type;
};


template <typename _Pack, typename _Pack2>
struct __pack_reverse;

template <typename... _Elements, typename _Element, typename... _ElementsOther>
struct __pack_reverse<parameter_pack<_Elements...>, parameter_pack<_Element, _ElementsOther...>>
: __pack_reverse<
parameter_pack<_Element, _Elements...>,
parameter_pack<_ElementsOther...>
>
{};

template <typename... _Elements>
struct __pack_reverse<parameter_pack<_Elements...>, parameter_pack<>>
{
	typedef parameter_pack<_Elements...> __type;
};

/**
 * @brief Reverse element of _Pack
 * _Pack must is a @ref parameter_pack
 */
template <typename _Pack>
struct pack_reverse
{ typedef typename __pack_reverse<parameter_pack<>, _Pack>::__type type; };

}
}

#endif