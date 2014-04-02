#ifndef FALCON_FUNCTIONAL_BIND_HPP
#define FALCON_FUNCTIONAL_BIND_HPP

#include <falcon/c++/conditional_cpp.hpp>
#include <falcon/functional/placeholders.hpp>
#include <type_traits>
#include <functional>

namespace falcon {

namespace detail {

template<class... Ts> struct bind_params
{ static const std::size_t size = sizeof...(Ts); };

template<class R, class C, class... Args>
bind_params<Args...> decl_params(R(C::*)(Args...));

template<class R, class C, class... Args>
bind_params<Args...> decl_params(R(C::*)(Args...) const);

template<class R, class C, class... Args>
bind_params<Args...> decl_params(R(C::*)(Args...) const &);

template<class R, class... Args>
bind_params<Args...> decl_params(R(*)(Args...));

template<class C>
decltype(decl_params(&C::operator())) decl_params(C&&);


template<int...> struct use_indexes {};

template<class Indexes, int...> struct filter_index
{ typedef Indexes type; };

template<int... UIs, int I, int... Is>
struct filter_index<use_indexes<UIs...>, I, Is...>
: filter_index<use_indexes<UIs..., I>, Is...>
{};

template<int... UIs, int... Is>
struct filter_index<use_indexes<UIs...>, 0, Is...>
: filter_index<use_indexes<UIs...>, Is...>
{};


template<class Indexes, int>
struct contains_index
{ static const bool value = false; };

template<int... UIs, int I>
struct contains_index<use_indexes<I, UIs...>, I>
{ static const bool value = true; };

template<int UI, int... UIs, int I>
struct contains_index<use_indexes<UI, UIs...>, I>
: contains_index<use_indexes<UIs...>, I>
{};

template<int P, class Is, bool = contains_index<Is, P>::value>
struct next_index
{ static const int value = P; };

template<int P, class Is>
struct next_index<P, Is, true>
{ static const int value = next_index<P+1, Is>::value; };

template<class Params, class Indexes, std::size_t N, int Pn = 1>
struct deduce_other_indexes;

template<int... OIs, int... Is, int Pn>
struct deduce_other_indexes<use_indexes<OIs...>, use_indexes<Is...>, 0, Pn>
{ typedef use_indexes<OIs...> type; };

template<int... OIs, int... Is, std::size_t N, int Pn>
struct deduce_other_indexes<use_indexes<OIs...>, use_indexes<Is...>, N, Pn>
{
  static const int next = next_index<Pn, use_indexes<Is...>>::value;
  typedef typename deduce_other_indexes<
    use_indexes<OIs..., next>
  , use_indexes<Is...>
  , N-1
  , next+1
  >::type type;
};


template<bool IsMemberFunction, class... Args>
struct get_index_placeholder
: filter_index<
  use_indexes<>
, std::is_placeholder<typename std::decay<Args>::type>::value...
> {};

template<class T, class... Args>
struct get_index_placeholder<true, T, Args...>
: filter_index<
  use_indexes<>
, std::is_placeholder<typename std::decay<Args>::type>::value...
> {};


template<class F, class... Args>
struct other_indexes
{
  template<class T> static bind_params<Args...> get_params(T, unsigned);
  template<class T> static
  decltype(decl_params(std::declval<typename std::decay<T>::type>()))
  get_params(T, int);

  typedef decltype(get_params(std::declval<F>(), 0)) params;
  static const bool is_member_function = std::is_member_function_pointer<F>::value;
  typedef typename deduce_other_indexes<
    use_indexes<>
  , typename get_index_placeholder<is_member_function, Args...>::type
  , params::size - sizeof...(Args) + is_member_function
  >::type type;
};

template<class F, class... Args, int... Is>
auto bind(use_indexes<Is...>, F&& f, Args&&... args)
#ifndef IN_IDE_PARSER
CPP_IF_CPP11(->decltype(std::bind(std::forward<F>(f)
, std::forward<Args>(args)..., placeholder<Is>()...)))
# endif
{
  return std::bind(std::forward<F>(f)
  , std::forward<Args>(args)..., placeholder<Is>()...);
}

template<class R, class F, class... Args, int... Is>
auto bind(use_indexes<Is...>, F&& f, Args&&... args)
#ifndef IN_IDE_PARSER
CPP_IF_CPP11(->decltype(std::bind<R>(std::forward<F>(f)
, std::forward<Args>(args)..., placeholder<Is>()...)))
# endif
{
  return std::bind<R>(std::forward<F>(f)
  , std::forward<Args>(args)..., placeholder<Is>()...);
}

}

/**
 * helper for std::bind. If possible falcon::bind, completed arguments with std::placeholder< N >. Not possible with template parameters.
 * @{
 */
template< class F, class... Args >
auto bind( F&& f, Args&&... args )
CPP_IF_CPP11(
->decltype(detail::bind(typename detail::other_indexes<F, Args...>::type()
, std::forward<F>(f), std::forward<Args>(args)...))
) {
  return detail::bind(typename detail::other_indexes<F, Args...>::type()
  , std::forward<F>(f), std::forward<Args>(args)...);
}

template< class R, class F, class... Args >
auto bind( F&& f, Args&&... args )
CPP_IF_CPP11(
->decltype(detail::bind<R>(typename detail::other_indexes<F, Args...>::type()
, std::forward<F>(f), std::forward<Args>(args)...))
) {
  return detail::bind<R>(typename detail::other_indexes<F, Args...>::type()
  , std::forward<F>(f), std::forward<Args>(args)...);
}
// @}
}

#endif
