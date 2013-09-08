#ifndef FALCON_PARAMETER_PARAMETER_INDEX_HPP
#define FALCON_PARAMETER_PARAMETER_INDEX_HPP

#include <cstddef>

namespace falcon {

/// Stores a arguments of indices.
template<std::size_t... Indexes>
struct parameter_index
{};


template<std::size_t... Indexes>
struct __Parameter_index
{
	typedef __Parameter_index<Indexes..., sizeof...(Indexes)> __next;
	typedef parameter_index<Indexes...> __parameter_index;
};

template<std::size_t Num>
struct __Build_parameter_index
{
	typedef typename __Build_parameter_index<Num-1>::__type::__next __type;
};

template<>
struct __Build_parameter_index<0>
{
	typedef __Parameter_index<> __type;
};

/// Builds an parameter_index<0, 1, 2, ..., Num-1>.
template<std::size_t Num>
struct build_parameter_index
{
	typedef typename __Build_parameter_index<Num>::__type::__parameter_index type;
};

template<std::size_t Num>
using build_parameter_index_t = typename build_parameter_index<Num>::type;


template<std::size_t Start, std::size_t Current, std::size_t Stop, std::size_t Step, typename Indexes>
struct __Build_range_parameter_index;

template<
	std::size_t Start, std::size_t Current, std::size_t Stop,
	std::size_t Step, std::size_t... Indexes
>
struct __Build_range_parameter_index<
	Start, Current, Stop,
	Step, parameter_index<Indexes...>
> : __Build_range_parameter_index<
	Start,
	((Current + Step) < Stop ? Current+Step : Stop),
	Stop,
	Step,
	parameter_index<Indexes..., Current>
>
{};

template<std::size_t Start, std::size_t Stop, std::size_t Step, std::size_t... Indexes>
struct __Build_range_parameter_index<
	Start, Stop, Stop,
	Step, parameter_index<Indexes...>
>
{
	typedef parameter_index<Indexes...> __type;
};

/// Builds an parameter_index<Start, ..., Stop-1>.
template<std::size_t Start, std::size_t Stop, std::size_t Step = 1>
struct build_range_parameter_index
{
	static_assert(Start <= Stop, "Start > Stop");
	static_assert(Step, "Step is zero");

	typedef typename __Build_range_parameter_index<Start, Start, Stop, Step, parameter_index<>>::__type type;
};

template<std::size_t Start, std::size_t Stop, std::size_t Step = 1>
using build_range_parameter_index_t = typename build_range_parameter_index<Start, Stop, Step>::type;

template<typename... Indexes>
class __parameter_index_cat;

template<std::size_t... Indexes, std::size_t... Indexes2, typename... _Others>
struct __parameter_index_cat<parameter_index<Indexes...>, parameter_index<Indexes2...>, _Others...>
: __parameter_index_cat<parameter_index<Indexes..., Indexes2...>, _Others...>
{};

template<std::size_t... Indexes, std::size_t... Indexes2>
struct __parameter_index_cat<parameter_index<Indexes...>, parameter_index<Indexes2...>>
{
	typedef parameter_index<Indexes..., Indexes2...> type;
};

template<std::size_t... Indexes>
struct __parameter_index_cat<parameter_index<Indexes...>>
{
	typedef parameter_index<Indexes...> type;
};

template<typename... Indexes>
struct parameter_index_cat
{
	typedef typename __parameter_index_cat<Indexes...>::type type;
};


template <typename Indexes, typename Indexes2>
struct __parameter_index_reverse;

template <std::size_t... Indexes, std::size_t _Index, std::size_t... IndexesOther>
struct __parameter_index_reverse<parameter_index<Indexes...>, parameter_index<_Index, IndexesOther...>>
: __parameter_index_reverse<
parameter_index<_Index, Indexes...>,
parameter_index<IndexesOther...>
>
{};

template <std::size_t... Indexes>
struct __parameter_index_reverse<parameter_index<Indexes...>, parameter_index<>>
{
	typedef parameter_index<Indexes...> __type;
};

/**
 * @brief Reverse indexes of Indexes
 * _Pack must is a @ref parameter_index
 */
template <typename Indexes>
struct parameter_index_reverse
{ typedef typename __parameter_index_reverse<parameter_index<>, Indexes>::__type type; };


template<typename, std::size_t>
struct __parameter_index_increment;

template<std::size_t... Indexes, std::size_t N>
struct __parameter_index_increment<parameter_index<Indexes...>, N>
{ typedef parameter_index<N + Indexes...> __type; };

/**
 * @brief Increment each index of N
 */
template<typename Indexes, std::size_t N = 1>
struct parameter_index_increment
{ typedef typename __parameter_index_increment<Indexes, N>::__type type; };

/**
 * @brief Decrement each index of N
 */
template<typename Indexes, std::size_t N = 1>
struct parameter_index_decrement
{ typedef typename __parameter_index_increment<Indexes, -N>::__type type; };


namespace parameter {
  template<std::size_t... Indexes>
  using indexes = parameter_index<Indexes...>;

  template<std::size_t Num>
  using build_indexes = build_parameter_index<Num>;

  template<std::size_t Num>
  using build_indexes_t = typename build_parameter_index<Num>::type;

  template<std::size_t Start, std::size_t Stop, std::size_t Step = 1>
  using build_range_index = build_range_parameter_index<Start, Stop, Step>;

  template<std::size_t Start, std::size_t Stop, std::size_t Step = 1>
  using build_range_index_t = typename build_range_parameter_index<Start, Stop, Step>::type;

  template<typename... Indexes>
  using indexes_cat = parameter_index_cat<Indexes...>;

  template <typename Indexes>
  using indexes_reverse = parameter_index_reverse<Indexes>;

  template<typename Indexes, std::size_t N = 1>
  using indexes_increment = parameter_index_increment<Indexes, N>;

  template<typename Indexes, std::size_t N = 1>
  using indexes_decrement = parameter_index_decrement<Indexes, N>;
}

}

#endif
