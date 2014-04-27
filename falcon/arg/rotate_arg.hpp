#ifndef FALCON_ARG_ROTATE_ARG_HPP
#define FALCON_ARG_ROTATE_ARG_HPP

#if __cplusplus >= 201103L
# include <falcon/arg/arg.hpp>
# include <falcon/parameter/parameter_index.hpp>
#else
# include <algorithm> //std::swap
#endif
#include <falcon/type_traits/normalize_index.hpp>

namespace falcon {

#if __cplusplus >= 201103L
namespace _aux {
  template <std::size_t ShiftRight, std::size_t N>
  struct rotate_arg
  {
    template <std::size_t Nm, int Current, class Indexes = parameter_index<>>
    struct build_index;

    template <std::size_t Nm, int Current, std::size_t... Indexes>
    struct build_index<Nm, Current, parameter_index<Indexes...>>
    : build_index<
      Nm-1, Current - ShiftRight
    , parameter_index<Indexes..., normalize_index<Current, N>::value>
    >
    {};

    template <int Current, std::size_t... Indexes>
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

template<int shift_right = 1, class... Args>
void rotate_arg(Args&... args)
{
  _aux::rotate_arg<
    normalize_index<shift_right, sizeof...(args)>::value,
    sizeof...(args)
  >::impl(args...);
}

template<int shift_right = 1, class T>
void rotate_arg(T&)
{}

template<int shift_right = 1>
void rotate_arg()
{}

#else

template<int shift_right = 1, class T>
void impl(T&)
{}

namespace _aux {
  template<int shift_right, class T>
  struct rotate_arg;

  template<class T>
  struct rotate_arg<0, T>
  {
    void impl(T&, T&)
    {}

    void impl(T&, T&, T&)
    {}

    void impl(T&, T&, T&, T&)
    {}
  };

  template<class T>
  struct rotate_arg<1, T>
  {
    void impl(T& a, T& b)
    {
      using std::swap;
      swap(a, b);
    }

    void impl(T& a, T& b, T& c)
    {
      T tmp = c;
      c = b;
      b = a;
      a = tmp;
    }

    void impl(T& a, T& b, T& c, T& d)
    {
      T tmp = d;
      d = c;
      c = b;
      b = a;
      a = tmp;
    }
  };

  template<class T>
  struct rotate_arg<2, T>
  {
    void impl(T& a, T& b, T& c)
    {
      T tmp = a;
      a = b;
      b = c;
      c = tmp;
    }

    void impl(T& a, T& b, T& c, T& d)
    {
      using std::swap;
      swap(a, c);
      swap(b, d);
    }
  };

  template<class T>
  struct rotate_arg<3, T>
  {
    void impl(T& a, T& b, T& c, T& d)
    {
      rotate_arg<1, T>::impl(d,c,b,a);
    }
  };
}

template<int shift_right = 1, class T>
void rotate_arg(T& a, T& b)
{
  _aux::rotate_arg<normalize_index<shift_right, 1>::value, T>::impl(a,b);
}

template<int shift_right = 1, class T>
void rotate_arg(T& a, T& b, T& c)
{
  _aux::rotate_arg<normalize_index<shift_right, 1>::value, T>::impl(a,b,c);
}

template<int shift_right = 1, class T>
void rotate_arg(T& a, T& b, T& c, T& d)
{
  _aux::rotate_arg<normalize_index<shift_right, 1>::value, T>::impl(a,b,c,d);
}

#endif

}

#endif
