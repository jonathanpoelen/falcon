#ifndef _FALCON_PARAMETER_MANIP_HPP
#define _FALCON_PARAMETER_MANIP_HPP

#include <cstddef>
#include <falcon/parameter/parameter_pack.hpp>

namespace falcon {

template<typename Pack>
class pack_size;

template<typename... Elements>
struct pack_size<parameter_pack<Elements...> >
{
	static const std::size_t value = sizeof...(Elements);
};

template <typename Pack, typename... Args>
class __pack_push_front;

template <typename... Elements, typename... Args>
struct __pack_push_front<parameter_pack<Elements...>, Args...>
{
	typedef parameter_pack<Args..., Elements...> __type;
};

/**
 * @brief Add @a Args to left a Pack
 * Pack must is a @ref parameter_pack
 */
template <typename Pack, typename... Args>
struct pack_push_front
{
	typedef typename __pack_push_front<Pack, Args...>::__type type;
};


template <typename Pack, typename... Args>
class __pack_push_back;

template <typename... Elements, typename... Args>
struct __pack_push_back<parameter_pack<Elements...>, Args...>
{
	typedef parameter_pack<Elements..., Args...> __type;
};

/**
 * @brief Add @a Args to right a Pack
 * Pack must is a @ref parameter_pack
 */
template <typename Pack, typename... Args>
struct pack_push_back
{
	typedef typename __pack_push_back<Pack, Args...>::__type type;
};


template <typename... Pack>
class __pack_cat;

template <typename... Elements, typename... Elements2, typename... _OtherPack>
struct __pack_cat<parameter_pack<Elements...>, parameter_pack<Elements2...>, _OtherPack...>
: __pack_cat<parameter_pack<Elements..., Elements2...>, _OtherPack...>
{};

template <typename... Elements>
struct __pack_cat<parameter_pack<Elements...>>
{
	typedef parameter_pack<Elements...> __type;
};

/**
 * @brief concat two Pack or more
 * Pack must is a @ref parameter_pack
 */
template <typename... Pack>
struct pack_cat
{ typedef typename __pack_cat<Pack...>::__type type; };


template <template<class...> class Wrapper, typename Pack>
class __pack_wrap;

template <template<class...> class Wrapper, typename... Elements>
struct __pack_wrap<Wrapper, parameter_pack<Elements...> >
{
	typedef parameter_pack<Wrapper<Elements>...> __type;
};

/**
 * @brief Wrap each value of Pack with Wrapper
 * Pack must is a @ref parameter_pack
 */
template <template<class...> class Wrapper, typename Pack>
struct pack_wrap
{
	typedef typename __pack_wrap<Wrapper, Pack>::__type type;
};


template <typename Pack>
struct __pack_use_type;

template <typename... Elements>
struct __pack_use_type<parameter_pack<Elements...>>
{
	typedef parameter_pack<typename Elements::type...> __type;
};

/**
 * @brief Get each inner type of Pack
 * Pack must is a @ref parameter_pack
 */
template <typename Pack>
struct pack_use_type
{
	typedef typename __pack_use_type<Pack>::__type type;
};

/**
 * @brief Use Modifier each value of Pack
 * Pack must is a @ref parameter_pack
 */
template <template<class...> class Modifier, typename Pack>
struct pack_modifier
{
	typedef typename __pack_use_type<
		typename pack_wrap<Modifier, Pack>::type
	>::__type type;
};


template <typename Pack, typename T, std::size_t N>
struct __build_pack;

template <typename... Elements, typename T, std::size_t N>
struct __build_pack<parameter_pack<Elements...>, T, N>
: __build_pack<parameter_pack<Elements..., T>, T, N-1>
{};

template <typename... Elements, typename T>
struct __build_pack<parameter_pack<Elements...>, T, 0>
{
	typedef parameter_pack<Elements...> __type;
};

/// Build parameter_pack with number N of type T
template <typename T, std::size_t N>
struct build_pack
{
	typedef typename __build_pack<parameter_pack<>, T, N>::__type type;
};


template <typename Pack, typename Pack2>
struct __pack_reverse;

template <typename... Elements, typename Element, typename... ElementsOther>
struct __pack_reverse<parameter_pack<Elements...>, parameter_pack<Element, ElementsOther...>>
: __pack_reverse<
parameter_pack<Element, Elements...>,
parameter_pack<ElementsOther...>
>
{};

template <typename... Elements>
struct __pack_reverse<parameter_pack<Elements...>, parameter_pack<>>
{
	typedef parameter_pack<Elements...> __type;
};

/**
 * @brief Reverse element of Pack
 * Pack must is a @ref parameter_pack
 */
template <typename Pack>
struct pack_reverse
{ typedef typename __pack_reverse<parameter_pack<>, Pack>::__type type; };


namespace parameter {
  template<typename Pack>
  using size = pack_size<Pack>;

  template <typename Pack, typename... Args>
  using push_front = pack_push_front<Pack, Args...>;

  template <typename Pack, typename... Args>
  using push_back = pack_push_back<Pack, Args...>;

  template <typename... Pack>
  using cat = pack_cat<Pack...>;

  template <template<class...> class Wrapper, typename Pack>
  using wrap = pack_wrap<Wrapper, Pack>;

  template <typename Pack>
  using use_type = pack_use_type<Pack>;

  template <template<class...> class Modifier, typename Pack>
  using modifier = pack_modifier<Modifier, Pack>;

  template <typename T, std::size_t N>
  using build =  build_pack<T, N>;

  template <typename Pack>
  using reverse = pack_reverse<Pack>;
}

}

#endif
