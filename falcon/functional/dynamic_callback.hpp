#ifndef FALCON_FUNCTIONAL_DYNAMIC_CALLBACK_HPP
#define FALCON_FUNCTIONAL_DYNAMIC_CALLBACK_HPP

#include <falcon/parameter/parameter_element.hpp>

#include <type_traits>

namespace falcon {

using std::size_t;

template<std::size_t N, std::size_t Max, typename Result, typename... Elements>
struct __dynamic_callback
{
  template<typename Callback, typename... Args>
  constexpr static Result impl(size_t id, Callback& callback, Args&&... args)
  {
    typedef parameter_pack<Elements...> pack;
    typedef typename parameter::at<N, pack>::type elem;
    return (N == id)
      ? callback(elem(), args...)
      : __dynamic_callback<N+1, Max, Result, Elements...>
        ::impl(id, callback, args...);
  }

  template<typename Callback, typename... Args>
  static Result impl(bool& err, size_t id, Callback& callback, Args&&... args)
  {
    typedef parameter_pack<Elements...> pack;
    typedef typename parameter::at<N, pack>::type elem;
    return (N == id)
      ? callback(elem(), args...)
      : __dynamic_callback<N+1, Max, Result, Elements...>
        ::impl(err, id, callback, args...);
  }
};

template<std::size_t Max, typename Result, typename... Elements>
struct __dynamic_callback<Max, Max, Result, Elements...>
{
  template<typename Callback, typename... Args>
  constexpr static Result impl(size_t , const Callback&, const Args&... )
  { return Result(); }

  template<typename Callback, typename... Args>
  static Result impl(bool& err, size_t , const Callback&, const Args&... )
  {
    err = true;
    return Result();
  }
};


template<typename... Elements, typename Callback, typename... Args,
  typename Result = typename std::result_of<
    Callback(typename parameter::element<0, Elements...>::type(), Args()...)
  >::type
>
constexpr Result dynamic_callback(size_t id, Callback callback, Args&&... args)
{
  return __dynamic_callback<0, sizeof...(Elements), Result, Elements...>
  ::impl(id, callback, args...);
}

template<typename... Elements, typename Callback, typename... Args,
  typename Result = typename std::result_of<
    Callback(typename parameter::element<0, Elements...>::type(), Args()...)
  >::type
>
Result dynamic_callback(bool& err, size_t id, Callback callback, Args&&... args)
{
  err = false;
  return __dynamic_callback<0, sizeof...(Elements), Result, Elements...>
  ::impl(err, id, callback, args...);
}

}

#endif
