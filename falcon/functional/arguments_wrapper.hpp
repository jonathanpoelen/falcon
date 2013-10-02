#ifndef FALCON_FUNCTIONAL_ARGUMENTS_WRAPPER_HPP
#define FALCON_FUNCTIONAL_ARGUMENTS_WRAPPER_HPP

#include <falcon/tuple/tuple_apply.hpp>
#include <falcon/type_traits/decay_and_strip.hpp>

#include <tuple>

namespace falcon
{

/**
 * \code
 * int a = 2, b = 3;
 * arguments_wrapper<int&, int> args(a, b);
 * args(f);
 * \endcode
 * equivalent to
 * \code
 * int a = 2, b = 3;
 * f(a,b);
 * \endcode
 */
template <typename... Elements>
class arguments_wrapper
: public std::tuple<Elements...>
{
	typedef std::tuple<Elements...> __base;

public:
	typedef __base tuple_type;


public:
	using std::tuple<Elements...>::tuple;
	using std::tuple<Elements...>::operator=;

	const tuple_type& tuple() const
	{ return *this; }

	tuple_type& tuple()
	{ return *this; }

	template<typename Functor>
	auto operator()(Functor func) const
	-> decltype(tuple_apply(func, this->tuple()))
	{    return tuple_apply(func, tuple()); }

	template<typename Functor, std::size_t... _Indexes>
	auto operator()(const parameter_index<_Indexes...>& indexes, Functor func) const
	-> decltype(tuple_apply(indexes, func, this->tuple()))
	{    return tuple_apply(indexes, func, tuple()); }

	void swap(arguments_wrapper& other)
	{
        using std::swap;
        swap(tuple(), other.tuple());
    }
};

template<typename... Elements>
constexpr arguments_wrapper<typename decay_and_strip<Elements>::type...>
make_arguments(Elements&&... args)
{
	return arguments_wrapper<
		typename decay_and_strip<Elements>::type...
	>(std::forward<Elements>(args)...);
}


template<std::size_t I, typename... Elements>
auto get(arguments_wrapper<Elements...>& t) noexcept
-> decltype(std::get<I>(t))
{ return std::get<I>(t); }

template<std::size_t I, typename... Elements>
auto get(const arguments_wrapper<Elements...>& t) noexcept
-> decltype(std::get<I>(t))
{ return std::get<I>(t); }

template<std::size_t I, typename... Elements>
auto get(arguments_wrapper<Elements...>&& t) noexcept
-> decltype(std::get<I>(std::forward<arguments_wrapper<Elements...>>(t)))
{ return std::get<I>(std::forward<arguments_wrapper<Elements...>>(t)); }


template<typename... Elements>
constexpr arguments_wrapper<Elements&&...>
forward_as_arguments(Elements&&... args) noexcept
{ return arguments_wrapper<Elements&&...>(std::forward<Elements>(args)...); }

template<typename... Elements>
void swap(arguments_wrapper<Elements...>& x, arguments_wrapper<Elements...>& y)
{ x.swap(y); };

}

namespace std
{
	template<typename... Elements>
	struct tuple_size<falcon::arguments_wrapper<Elements...>>
	{ static const int value = sizeof...(Elements); };

	template<std::size_t _Index, typename... Elements>
	struct tuple_element<_Index, falcon::arguments_wrapper<Elements...>>
	: tuple_element<_Index, std::tuple<Elements...>>
	{};
}

#endif
