#ifndef FALCON_MPL_SEQ_HPP
#define FALCON_MPL_SEQ_HPP

#include <falcon/parameter/parameter_pack.hpp>
#include <falcon/parameter/parameter_index.hpp>
#include <falcon/type_traits/if.hpp>
#include <falcon/type_traits/eval_if.hpp>
#include <falcon/type_traits/use.hpp>
#include <type_traits>

namespace falcon {
namespace mpl {

template<typename... Args>
struct seq
{
  typedef seq type;
};

template <typename>
class pack2seq;

template <template <class...> class T, typename... Args>
struct pack2seq<T<Args...>>
{
  typedef seq<Args...> type;
};

template <typename>
class seq2pack;

template <template <class...> class T, typename... Args>
struct seq2pack<T<Args...>>
{
  typedef parameter_pack<Args...> type;
};

template <typename>
struct iterator_category
{
  typedef void type;
};


template <typename>
class size_impl;

template <template <class...> class Seq, typename... Args>
struct size_impl<Seq<Args...>>
{
  static const size_t value = sizeof...(Args);
};


template <typename Seq, typename T>
class push_back_impl;

template <template <class...> class Seq, typename T, typename... Args>
struct push_back_impl<Seq<Args...>, T>
{
  typedef Seq<Args..., T> type;
};


template <typename Seq, typename T>
class push_front_impl;

template <template <class...> class Seq, typename T, typename... Args>
struct push_front_impl<Seq<Args...>, T>
{
  typedef Seq<T, Args...> type;
};


template <typename Seq>
class pop_back_impl;

template <template <class...> class Seq, typename T, typename... Args>
struct pop_back_impl<Seq<Args..., T>>
{
  typedef Seq<Args...> type;
};


template <typename Seq>
class pop_front_impl;

template <template <class...> class Seq, typename T, typename... Args>
struct pop_front_impl<Seq<T, Args...>>
{
  typedef Seq<Args...> type;
};


template <typename Seq>
class back_impl;

template <template <class...> class Seq, typename T, typename... Args>
struct back_impl<Seq<Args..., T>>
{
  typedef T type;
};


template <typename Seq>
class front_impl;

template <template <class...> class Seq, typename T, typename... Args>
struct front_impl<Seq<T, Args...>>
{
  typedef T type;
};


template <typename Seq>
struct empty_impl
: std::true_type
{};

template <template <class...> class Seq, typename T, typename... Args>
struct empty_impl<Seq<T, Args...>>
: std::false_type
{};


template <typename Seq, std::size_t Pos>
class at_c_impl;

template <template <class...> class Seq, typename T, typename... Args, std::size_t Pos>
struct at_c_impl<Seq<T, Args...>, Pos>
{
  typedef typename at_c_impl<Seq<Args...>, Pos-1>::type type;
};

template <template <class...> class Seq, typename T, typename... Args>
struct at_c_impl<Seq<T, Args...>, 0>
{
  typedef T type;
};


template <typename Seq, std::size_t N, typename Seq2 = seq<>>
class move_front_impl
{
  typedef Seq first;
  typedef Seq2 second;
};

template <
  template <class...> class Seq , typename T, typename... Args,
  std::size_t N,
  template <class...> class Seq2, typename... Args2
>
struct move_front_impl<Seq<T, Args...>, N, Seq2<Args2...>>
: move_front_impl<Seq<Args...>, N-1, Seq2<T, Args2...>>
{};

template <
  template <class...> class Seq , typename T, typename... Args,
  template <class...> class Seq2, typename... Args2
>
struct move_front_impl<Seq<T, Args...>, 0, Seq2<Args2...>>
{
  typedef Seq<T, Args...> first;
  typedef Seq2<Args2...> second;
};


template <typename Seq, std::size_t N>
struct erase_front_impl
{
  typedef Seq type;
};

template <template <class...> class Seq, typename T, typename... Args, std::size_t N>
struct erase_front_impl<Seq<T, Args...>, N>
: erase_front_impl<Seq<Args...>, N-1>
{};

template <template <class...> class Seq, typename T, typename... Args>
struct erase_front_impl<Seq<T, Args...>, 0>
{
  typedef Seq<T, Args...> type;
};


template <typename Seq, typename Seq2>
class cat_impl;

template <
  template <class...> class Seq, typename... Args,
  template <class...> class Seq2, typename... Args2
>
struct cat_impl<Seq<Args...>, Seq2<Args2...>>
{
  typedef Seq<Args..., Args2...> type;
};


template <typename Seq, std::size_t Pos, std::size_t N, typename NewSeq = seq<>>
struct erase_c_impl
{
  typedef move_front_impl<Seq, Pos, NewSeq> range1;
  typedef typename cat_impl<
    typename range1::second,
    typename erase_front_impl<typename range1::first, N>::type
  >::type type;
};


template<typename F>
constexpr bool has_apply_class_impl(int, const typename F::apply& = typename F::apply())
{
  return 1;
}

template<typename F>
constexpr bool has_apply_class_impl(unsigned)
{
  return 0;
}


template<typename F, bool = has_apply_class_impl<F>(1)>
struct apply_wrap0_impl
{
  typedef typename F::apply::type type;
};

template<typename F>
struct apply_wrap0_impl<F, true>
{
  typedef typename F::template apply<>::type type;
};

template<typename F, typename... Args>
struct apply_wrap_impl
{
  typedef typename F::template apply<Args...>::type type;
};

template<typename F>
struct apply_wrap_impl<F>
{
  typedef typename apply_wrap0_impl<F>::type type;
};

namespace placeholders {
  template<unsigned N>
  struct placeholder
  {
    typedef placeholder type;

    template<typename... Args>
    using apply = at_c_impl<seq<Args...>, N-1>;
  };

  using _1 = placeholder<1>;
  using _2 = placeholder<2>;
  using _3 = placeholder<3>;
  using _4 = placeholder<4>;
  using _5 = placeholder<5>;
  using _6 = placeholder<6>;
  using _7 = placeholder<7>;
  using _8 = placeholder<8>;
  using _9 = placeholder<9>;
}

template<typename Seq, typename T>
struct get_value_impl
{ typedef T type; };

template<typename Seq, unsigned N>
struct get_value_impl<Seq, placeholders::placeholder<N>>
{ typedef typename at_c_impl<Seq, N-1>::type type; };


template <typename T, bool, typename... Args>
struct apply_or_type_impl
{
  using type = T;
};

template <typename T, typename... Args>
struct apply_or_type_impl<T, true, Args...>
{
  using type = typename T::template mpl_apply<Args...>::type;
};


template <template<class...>class T>
struct quote
{
  template <typename... Args>
  struct apply
  {
    using type = typename T<Args...>::type;
  };
};


template<typename T, typename Integral = typename T::mpl_type>
constexpr bool has_mpl_type_impl(int, const Integral& = Integral())
{
  return Integral::value;
}

template<typename T>
constexpr bool has_mpl_type_impl(unsigned)
{
  return 0;
}

template<typename T>
using is_mpl_type = std::integral_constant<bool, (has_mpl_type_impl<T>(1))>;


template <typename T, typename... Args>
struct apply_or_type_decay_impl
{
  typedef typename get_value_impl<seq<Args...>, T>::type value_type;
  typedef typename apply_or_type_impl<
    value_type,
    has_mpl_type_impl<value_type>(1),
    Args...
  >::type type;
};

template <typename T, typename... Args>
using apply_or_type_impl_t = typename apply_or_type_decay_impl<T, Args...>::type;


template<typename T>
struct protect
{ using type = T; };


template<typename F, typename... Args>
class apply_impl;

template <typename T, typename... Args>
struct apply_impl<protect<T>, Args...>
{ using type = protect<T>; };

template <template <class...> class T, typename... Args, typename... Args2>
struct apply_impl<T<Args...>, Args2...>
{ using type = typename T<apply_or_type_impl_t<Args, Args2...>...>::type; };

template <template <typename U, U, class...> class T, typename U, U V,
  typename... Args, typename... Args2>
struct apply_impl<T<U, V, Args...>, Args2...>
{ using type = typename T<U, V, apply_or_type_impl_t<Args, Args2...>...>::type; };

template <template <bool, class...> class T, bool V, typename... Args, typename... Args2>
struct apply_impl<T<V, Args...>, Args2...>
{ using type = typename T<V, apply_or_type_impl_t<Args, Args2...>...>::type; };


template<typename F, typename... Args>
struct apply
{ using type = typename apply_impl<F, Args...>::type; };



template <unsigned N>
struct arg
{
  template <typename... Args>
  struct apply
  {
    using type = typename at_c_impl<seq<Args...>, N-1>::type;
  };

  using type = arg;
};


template<typename T, bool = T::value>
constexpr bool has_bool_value_impl(int)
{
  return 1;
}

template<typename T>
constexpr bool has_bool_value_impl(unsigned)
{
  return 0;
}


template<typename T>
struct mpl_apply_def
{
  using mpl_type = std::true_type;
  template <typename... Args>
  using mpl_apply = apply_impl<T, Args...>;
};


template<typename T1, typename T2>
struct pair
: mpl_apply_def<pair<T1,T2>>
{
  typedef pair type;
  typedef T1 first;
  typedef T2 second;
};



template<typename C, typename TrueT, typename FalseT>
struct if_
: mpl_apply_def<::falcon::if_c<C, TrueT, FalseT>>
{
  using type = typename ::falcon::eval_if<
    has_bool_value_impl<C>(1),
    ::falcon::if_c<C, TrueT, FalseT>,
    ::falcon::use<FalseT>
  >::type;
};


template<bool c, typename TrueT, typename FalseT>
struct if_c
: mpl_apply_def<::falcon::if_<c, TrueT, FalseT>>
{
  using type = typename ::falcon::if_<c, TrueT, FalseT>::type;
};


template<typename C, typename TrueT, typename FalseT>
struct eval_if_
: mpl_apply_def<::falcon::eval_if_c<C, TrueT, FalseT>>
{
  using type = typename ::falcon::if_<
    has_bool_value_impl<C>(1),
    ::falcon::if_c<C, TrueT, FalseT>,
    FalseT
  >::type::type;
};


template<bool c, typename TrueT, typename FalseT>
struct eval_if_c
: mpl_apply_def<::falcon::eval_if<c, TrueT, FalseT>>
{
  using type = typename ::falcon::eval_if<c, TrueT, FalseT>::type;
};


template <typename T>
class next
{
  using type = typename T::next;
};

template <typename T, T N>
struct next<std::integral_constant<T, N>>
{
  using type = std::integral_constant<T, N+1>;
};


template <typename T>
class prior
{
  using type = typename T::prior;
};

template <typename T, T N>
struct prior<std::integral_constant<T, N>>
{
  using type = std::integral_constant<T, N-1>;
};




}
}

#endif
