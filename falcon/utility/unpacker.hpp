#ifndef FALCON_UTILITY_UNPACKER_HPP
#define FALCON_UTILITY_UNPACKER_HPP

#include <falcon/parameter/parameter_index.hpp>
#include <falcon/c++1x/unpack.hpp>
#include <tuple>

namespace falcon {

namespace detail {
  template<class T>
  struct unpack_assigner
  {
    template<class Tuple>
    static void impl(Tuple & t, T && x)
    {
      static_assert(std::tuple_size<Tuple>::value == std::tuple_size<T>::value,
                    "The size must be equal.");
      impl_(t, std::forward<T>(x), build_parameter_index_t<std::tuple_size<Tuple>::value>());
    }

    template<class Tuple>
    static void impl(Tuple & t, T & x)
    {
      static_assert(std::tuple_size<Tuple>::value == std::tuple_size<T>::value,
                    "The size must be equal.");
      impl_(t, x, build_parameter_index_t<std::tuple_size<Tuple>::value>());
    }

  private:
    template<class Tuple, std::size_t... Indexes>
    static void impl_(Tuple & t, T && x, parameter_index<Indexes...>)
    {
      using std::get;
      CPP1X_UNPACK(get<Indexes>(t) = get<Indexes>(std::forward<T>(x)));
    }

    template<class Tuple, std::size_t... Indexes>
    static void impl_(Tuple & t, T & x, parameter_index<Indexes...>)
    {
      using std::get;
      CPP1X_UNPACK(get<Indexes>(t) = get<Indexes>(x));
    }
  };

  template<class... Ts>
  struct unpack_assigner<std::tuple<Ts...>>
  {
    template<class Tuple, class Tuple2>
    static void impl(Tuple t, Tuple2 && x)
    { t = std::forward<Tuple2>(x); }
  };

  template<class T, class U>
  struct unpack_assigner<std::pair<T, U>>
  {
    template<class Tuple, class Pair>
    static void impl(Tuple t, Pair && x)
    { t = std::forward<Pair>(x); }
  };

  template<class T, std::size_t N>
  struct unpack_assigner<T[N]>
  {
    template<class Tuple, class Array>
    static void impl(Tuple t, Array&& x)
    {
      static_assert(std::tuple_size<Tuple>::value == N, "The size must be equal.");
      impl_(t, x, build_parameter_index_t<std::tuple_size<Tuple>::value>(),
            std::integral_constant<bool, std::is_lvalue_reference<Array>::value>());
    }

  private:
    template<class Tuple, std::size_t... Indexes>
    static void impl_(Tuple & t, T (&x)[N], parameter_index<Indexes...>, std::true_type)
    {
      using std::get;
      CPP1X_UNPACK(get<Indexes>(t) = x[Indexes]);
    }

    template<class Tuple, std::size_t... Indexes>
    static void impl_(Tuple & t, T (&x)[N], parameter_index<Indexes...>, std::false_type)
    {
      using std::get;
      CPP1X_UNPACK(get<Indexes>(t) = std::move(x[Indexes]));
    }
  };
}

template<class... Ts>
class unpack_wrapper
{
  std::tuple<Ts&...> t;

public:
  unpack_wrapper(Ts&... args)
  : t(args...)
  {}

  template <class T>
  void operator=(T&& x) const
  {
    detail::unpack_assigner<typename std::remove_reference<T>::type>
    ::impl(t, std::forward<T>(x));
  }
};


template<class... Ts>
unpack_wrapper<Ts...> unpacker(Ts&... args)
{ return {args...}; }

}

#endif
