#ifndef FALCON_FUNCTIONAL_ARGUMENTS_WRAPPER_HPP
#define FALCON_FUNCTIONAL_ARGUMENTS_WRAPPER_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/c++/constexpr.hpp>
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
struct arguments_wrapper
: std::tuple<Elements...>
{
	typedef std::tuple<Elements...> tuple_type;


public:
	using std::tuple<Elements...>::tuple;
  using std::tuple<Elements...>::operator=;

  constexpr const tuple_type& tuple() const
  { return *this; }

  CPP_CONSTEXPR_NOT_CONST tuple_type& tuple()
  { return *this; }

  template<typename F>
  constexpr CPP1X_DELEGATE_FUNCTION(
    operator()(F && func) const
  , tuple_apply(std::forward<F>(func), this->tuple()))

  template<typename F, std::size_t... Is>
  constexpr CPP1X_DELEGATE_FUNCTION(
    operator()(F && func, parameter_index<Is...> indexes) const
    , tuple_apply(indexes, std::forward<F>(func), this->tuple()))
};


template<typename... Elements>
constexpr arguments_wrapper<typename decay_and_strip<Elements>::type...>
make_arguments(Elements&&... args)
{
  return arguments_wrapper<typename decay_and_strip<Elements>::type...>{
    std::forward<Elements>(args)...
  };
}


template<typename... Elements>
constexpr arguments_wrapper<Elements&&...>
forward_as_arguments(Elements&&... args) noexcept
{ return arguments_wrapper<Elements&&...>(std::forward<Elements>(args)...); }


///Creates a @c arguments_wrapper of lvalue references on tuple values
template<typename... Elements>
arguments_wrapper<Elements...>& arguments_wrapper_cast(std::tuple<Elements...>& t)
{ return static_cast<arguments_wrapper<Elements...>&>(t); }

///Creates a const @c arguments_wrapper of lvalue references on tuple values
template<typename... Elements>
const arguments_wrapper<Elements...>&
arguments_wrapper_cast(const std::tuple<Elements...>& t)
{ return static_cast<const arguments_wrapper<Elements...>&>(t); }

///Creates a @c arguments_wrapper of rvalue references on tuple values
template<typename... Elements>
arguments_wrapper<Elements...>&&
arguments_wrapper_cast(std::tuple<Elements...>&& t)
{ return static_cast<arguments_wrapper<Elements...>&&>(t); }


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
