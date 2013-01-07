#ifndef _FALCON_PARAMETER_PARAMETER_INDEX_HPP
#define _FALCON_PARAMETER_PARAMETER_INDEX_HPP

#include <cstddef>

namespace falcon {

/// Stores a arguments of indices.
template<std::size_t... _Indexes>
struct parameter_index
{};


template<std::size_t... _Indexes>
struct __Parameter_index
{
	typedef __Parameter_index<_Indexes..., sizeof...(_Indexes)> __next;
	typedef parameter_index<_Indexes...> __parameter_index;
};

template<std::size_t _Num>
struct __Build_parameter_index
{
	typedef typename __Build_parameter_index<_Num-1>::__type::__next __type;
};

template<>
struct __Build_parameter_index<0>
{
	typedef __Parameter_index<> __type;
};

/// Builds an parameter_index<0, 1, 2, ..., _Num-1>.
template<std::size_t _Num>
struct build_parameter_index
{
	typedef typename __Build_parameter_index<_Num>::__type::__parameter_index type;
};


template<std::size_t _Start, std::size_t _Current, std::size_t _Stop, std::size_t _Step, typename _Indexes>
struct __Build_range_parameter_index;

template<
	std::size_t _Start, std::size_t _Current, std::size_t _Stop,
	std::size_t _Step, std::size_t... _Indexes
>
struct __Build_range_parameter_index<
	_Start, _Current, _Stop,
	_Step, parameter_index<_Indexes...>
> : __Build_range_parameter_index<
	_Start,
	((_Current + _Step) < _Stop ? _Current+_Step : _Stop),
	_Stop,
	_Step,
	parameter_index<_Indexes..., _Current>
>
{};

template<std::size_t _Start, std::size_t _Stop, std::size_t _Step, std::size_t... _Indexes>
struct __Build_range_parameter_index<
	_Start, _Stop, _Stop,
	_Step, parameter_index<_Indexes...>
>
{
	typedef parameter_index<_Indexes...> __type;
};

/// Builds an parameter_index<_Start, ..., _Stop-1>.
template<std::size_t _Start, std::size_t _Stop, std::size_t _Step = 1>
struct build_range_parameter_index
{
	static_assert(_Start <= _Stop, "_Start <= _Stop");
	static_assert(_Step, "_Step is zero");

	typedef typename __Build_range_parameter_index<_Start, _Start, _Stop, _Step, parameter_index<>>::__type type;
};

template<typename... _Indexes>
class __parameter_index_cat;

template<std::size_t... _Indexes, std::size_t... _Indexes2, typename... _Others>
struct __parameter_index_cat<parameter_index<_Indexes...>, parameter_index<_Indexes2...>, _Others...>
: __parameter_index_cat<parameter_index<_Indexes..., _Indexes2...>, _Others...>
{};

template<std::size_t... _Indexes, std::size_t... _Indexes2>
struct __parameter_index_cat<parameter_index<_Indexes...>, parameter_index<_Indexes2...>>
{
	typedef parameter_index<_Indexes..., _Indexes2...> type;
};

template<std::size_t... _Indexes>
struct __parameter_index_cat<parameter_index<_Indexes...>>
{
	typedef parameter_index<_Indexes...> type;
};

template<typename... _Indexes>
struct parameter_index_cat
{
	typedef typename __parameter_index_cat<_Indexes...>::type type;
};


template <typename _Indexes, typename _Indexes2>
struct __parameter_index_reverse;

template <std::size_t... _Indexes, std::size_t _Index, std::size_t... _IndexesOther>
struct __parameter_index_reverse<parameter_index<_Indexes...>, parameter_index<_Index, _IndexesOther...>>
: __parameter_index_reverse<
parameter_index<_Index, _Indexes...>,
parameter_index<_IndexesOther...>
>
{};

template <std::size_t... _Indexes>
struct __parameter_index_reverse<parameter_index<_Indexes...>, parameter_index<>>
{
	typedef parameter_index<_Indexes...> __type;
};

/**
 * @brief Reverse indexes of _Indexes
 * _Pack must is a @ref parameter_index
 */
template <typename _Indexes>
struct parameter_index_reverse
{ typedef typename __parameter_index_reverse<parameter_index<>, _Indexes>::__type type; };


template<typename, std::size_t>
struct __parameter_index_increment;

template<std::size_t... _Indexes, std::size_t _N>
struct __parameter_index_increment<parameter_index<_Indexes...>, _N>
{ typedef parameter_index<_N + _Indexes...> __type; };

/**
 * @brief Increment each index of _N
 */
template<typename _Indexes, std::size_t _N = 1>
struct parameter_index_increment
{ typedef typename __parameter_index_increment<_Indexes, _N>::__type type; };

/**
 * @brief Decrement each index of _N
 */
template<typename _Indexes, std::size_t _N = 1>
struct parameter_index_decrement
{ typedef typename __parameter_index_increment<_Indexes, -_N>::__type type; };

}

#endif