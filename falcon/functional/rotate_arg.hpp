#ifndef FALCON_FUNCTIONAL_ROTATE_ARG_HPP
#define FALCON_FUNCTIONAL_ROTATE_ARG_HPP

#include <falcon/functional/arg.hpp>
#include <falcon/parameter/parameter_index.hpp>
#include <falcon/type_traits/normalize_index.hpp>
#include <utility>

namespace falcon {

namespace aux_ {

  template <std::size_t ShiftRight, std::size_t N>
  struct rotate_arg
  {
    template <std::size_t Nm, unormalized_index_t Current, class Indexes = parameter_index<>>
    struct build_index;

    template <std::size_t Nm, unormalized_index_t Current, std::size_t... Indexes>
    struct build_index<Nm, Current, parameter_index<Indexes...>>
    : build_index<
      Nm-1, int(Current - ShiftRight)
    , parameter_index<Indexes..., normalize_index<(Current % N), N>::value>
    >
    {};

    template <unormalized_index_t Current, std::size_t... Indexes>
    struct build_index<0, Current, parameter_index<Indexes...>>
    {
      typedef parameter_index<Indexes...> type;
    };

    template<class... Args>
    static void impl(Args&... args)
    {
      constexpr std::size_t number_swap = (ShiftRight&1)
      ? (sizeof...(Args) % ShiftRight
        ? 1
        : ShiftRight
      ) : (sizeof...(Args)&1
        ? 1
        : ((sizeof...(Args)-1) % ShiftRight + 1)
      );
      typedef typename build_range_parameter_index<0, number_swap>::type BuildIndex;
      impl<number_swap>(BuildIndex(), args...);
    }

    template<std::size_t number_swap, class... Args
    , std::size_t Index, std::size_t... Indexes>
    static void impl(const parameter_index<Index, Indexes...>&, Args&... args)
    {
      typedef typename build_index<N / number_swap, Index>::type BuildIndex;
      auto tmp = std::move(falcon::arg<Index>(args...));
      rotate_impl(BuildIndex(), tmp, args...);
      impl<number_swap>(parameter_index<Indexes...>(), args...);
    }

    template<std::size_t number_swap, class... Args>
    static void impl(const parameter_index<>&, Args&...)
    {}

    template<class T, class... Args, std::size_t... Indexes>
    static void rotate_impl(const parameter_index<Indexes...>&, T& tmp, Args&... args)
    {
      rotate_impl(tmp, falcon::arg<Indexes>(args...)...);
    }

    template<class T, class U, class V, class... Args>
    static void rotate_impl(T& tmp, U& a, V& b, Args&... args)
    {
      a = std::move(b);
      rotate_impl(tmp, b, args...);
    }

    template<class T, class U>
    static void rotate_impl(T& tmp, U& a)
    {
      a = std::move(tmp);
    }
  };

  template <std::size_t N>
  struct rotate_arg<0, N>
  {
    template<class... Args>
    static void impl(Args&...)
    {}
  };
}

template<unormalized_index_t shift_right = 1, class... Args>
void rotate_arg(Args&... args)
{
  aux_::rotate_arg<
    normalize_index<(shift_right % sizeof...(args)), sizeof...(args)>::value
  , sizeof...(args)
  >::impl(args...);
}

template<unormalized_index_t shift_right = 1, class T, class U>
void rotate_arg(T & a, U & b)
{
  using std::swap;
  swap(a, b);
}

template<unormalized_index_t shift_right = 1, class T>
void rotate_arg(T&)
{}

template<unormalized_index_t shift_right = 1>
void rotate_arg()
{}

}

#endif
