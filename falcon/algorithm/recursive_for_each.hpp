#ifndef FALCON_ALGORITHM_RECURSIVE_FOR_EACH_HPP
#define FALCON_ALGORITHM_RECURSIVE_FOR_EACH_HPP

#include <falcon/c++/reference.hpp>
#include <falcon/c++/conditional_cpp.hpp>
#include <falcon/iterator/subrange_access_iterator.hpp>
#include <falcon/type_traits/dimension.hpp>
#include <falcon/type_traits/ignore.hpp>
#include <falcon/utility/move.hpp>

namespace falcon {
namespace algorithm {
namespace _aux {

template <class Function, class T, bool Break = true>
struct break_off
{
  Function function;
  T value;

#if __cplusplus < 201103L
  break_off(const Function& function, const T& value)
  : function(function)
  , value(value)
  {}
#endif
};

template <class Function, class Functor, bool Break = true>
struct break_if
{
  Function function;
  Functor functor;

#if __cplusplus < 201103L
  break_if(const Function& function, const T& functor)
  : function(function)
  , functor(functor)
  {}
#endif
};

template <class Function, class T, bool Break = true>
struct return_off
{
  Function function;
  T value;

#if __cplusplus < 201103L
  return_off(const Function& function, const T& value)
  : function(function)
  , value(value)
  {}
#endif
};

template <class Function, class Functor, bool Break = true>
struct return_if
{
  Function function;
  Functor functor;

#if __cplusplus < 201103L
  return_if(const Function& function, const T& functor)
  : function(function)
  , functor(functor)
  {}
#endif
};

template <std::size_t Dimension>
struct recursive_for_each
{
  template<class Iterator, class Function>
  static void for_each(Iterator first, Iterator last, Function& f)
  {
    for (; first != last; ++first) {
      recursive_for_each<Dimension-1>::for_each(begin(*first), end(*first), f);
    }
  }

  template<class Iterator, class Function, class T, bool Break>
  static bool for_each(Iterator first, Iterator last, return_off<Function, T, Break>& w)
  {
    for (; first != last; ++first) {
      if (!recursive_for_each<Dimension-1>::for_each(begin(*first), end(*first), w)) {
        return false;
      }
    }
    return true;
  }

  template<class Iterator, class Function, class Functor, bool Break>
  static bool for_each(Iterator first, Iterator last, return_if<Function, Functor, Break>& w)
  {
    for (; first != last; ++first) {
      if (!recursive_for_each<Dimension-1>::for_each(begin(*first), end(*first), w)) {
        return false;
      }
    }
    return true;
  }
};

template <>
struct recursive_for_each<0>
{
  template<class Iterator, class Function>
  static void for_each(Iterator first, Iterator last, Function& f)
  {
    for (; first != last; ++first) {
      f(*first);
    }
  }

  template<class Iterator, class Function, class T, bool B>
  static void for_each(Iterator first, Iterator last, break_off<Function, T, B>& w)
  {
    for (; first != last && (B ? *first != w.value : *first != w.value); ++first) {
      w.function(*first);
    }
  }

  template<class Iterator, class Function, class Functor, bool B>
  static void for_each(Iterator first, Iterator last, break_if<Function, Functor, B>& w)
  {
    for (; first != last && B == w.functor(*first); ++first) {
      w.function(*first);
    }
  }

  template<class Iterator, class Function, class T, bool B>
  static bool for_each(Iterator first, Iterator last, return_off<Function, T, B>& w)
  {
    for (; first != last; ++first) {
      if (B ? *first == w.value : *first != w.value) {
        return false;
      }
      w.function(*first);
    }
    return true;
  }

  template<class Iterator, class Function, class Functor, bool B>
  static bool for_each(Iterator first, Iterator last, return_if<Function, Functor, B>& w)
  {
    for (; first != last; ++first) {
      if (B != w.functor(*first)) {
        return false;
      }
      w.function(*first);
    }
    return true;
  }
};

template<class Preface, class Function, class Postface, std::size_t Dimension>
class recursive_intermediate;

}

#if __cplusplus >= 201103L
template <class Function, class T>
inline _aux::break_off<Function, T> break_off(Function&& function, T&& value)
{ return {std::forward<Function>(function), std::forward<T>(value)}; }

template <class Function, class T>
inline _aux::break_off<Function, T, false> break_off_not(Function&& function, T&& value)
{ return {std::forward<Function>(function), std::forward<T>(value)}; }

template <class Function, class Functor>
inline _aux::break_if<Function, Functor> break_if(Function&& function, Functor&& functor)
{ return {std::forward<Function>(function), std::forward<Functor>(functor)}; }

template <class Function, class Functor>
inline _aux::break_if<Function, Functor, false> break_if_not(Function&& function, Functor&& functor)
{ return {std::forward<Function>(function), std::forward<Functor>(functor)}; }
#else
template <class Function, class T>
inline _aux::break_off<Function, T> break_off(Function function, const T& value)
{ return _aux::break_off<Function, T>(function, value); }

template <class Function, class T>
inline _aux::break_off<Function, T, false> break_off_not(Function function, const T& value)
{ return _aux::break_off<Function, T, false>(function, value); }

template <class Function, class Functor>
inline _aux::break_if<Function, Functor> break_if(Function function, Functor functor)
{ return _aux::break_if<Function, Functor>(function, functor); }

template <class Function, class Functor>
inline _aux::break_if<Function, Functor, false> break_if_not(Function function, Functor functor)
{ return _aux::break_if<Function, Functor, false>(function, functor); }
#endif

#if __cplusplus >= 201103L
template <class Function, class T>
inline _aux::return_off<Function, T> return_off(Function&& function, T&& value)
{ return {std::forward<Function>(function), std::forward<T>(value)}; }

template <class Function, class T>
inline _aux::return_off<Function, T, false> return_off_not(Function&& function, T&& value)
{ return {std::forward<Function>(function), std::forward<T>(value)}; }

template <class Function, class Functor>
inline _aux::return_if<Function, Functor> return_if(Function&& function, Functor&& functor)
{ return {std::forward<Function>(function), std::forward<Functor>(functor)}; }

template <class Function, class Functor>
inline _aux::return_if<Function, Functor, false> return_if_not(Function&& function, Functor&& functor)
{ return {std::forward<Function>(function), std::forward<Functor>(functor)}; }
#else
template <class Function, class T>
inline _aux::return_off<Function, T> return_off(Function function, const T& value)
{ return _aux::return_off<Function, T>(function, value); }

template <class Function, class T>
inline _aux::return_off<Function, T, false> return_off_not(Function function, const T& value)
{ return _aux::return_off<Function, T, false>(function, value); }

template <class Function, class Functor>
inline _aux::return_if<Function, Functor> return_if(Function function, Functor functor)
{ return _aux::return_if<Function, Functor>(function, functor); }

template <class Function, class Functor>
inline _aux::return_if<Function, Functor, false> return_if_not(Function function, Functor functor)
{ return _aux::return_if<Function, Functor, false>(function, functor); }
#endif

template <class Iterator, class Function>
Function recursive_for_each(Iterator first, Iterator last, Function f)
{
  _aux::recursive_for_each<dimension<
#if __cplusplus >= 201103L
    decltype(*std::declval<Iterator>())
#else
    std::iterator_traits<Iterator>::type
#endif
  >::value - 1>::for_each(first, last, f);
  return FALCON_FORWARD(Function, f);
}

template <std::size_t Dimension, class Iterator, class Function>
Function recursive_for_each(Iterator first, Iterator last, Function f)
{
  _aux::recursive_for_each<
    (Dimension == -1u ? dimension<
#if __cplusplus >= 201103L
      decltype(*std::declval<Iterator>())
#else
      std::iterator_traits<Iterator>::type
#endif
    >::value : Dimension) - 1
  >::for_each(first, last, f);
  return FALCON_FORWARD(Function, f);
}

template <class Container, class Function>
Function recursive_for_each(Container CPP_RVALUE_OR_REFERENCE container, Function f)
{
  _aux::recursive_for_each<dimension<Container>::value - 1>
    ::for_each(begin(container), end(container), f);
  return FALCON_FORWARD(Function, f);
}

template <std::size_t Dimension, class Container, class Function>
Function recursive_for_each(Container CPP_RVALUE_OR_REFERENCE container, Function f)
{
  _aux::recursive_for_each<
    (Dimension == -1u ? dimension<Container>::value : Dimension) - 1
  >::for_each(begin(container), end(container), f);
  return FALCON_FORWARD(Function, f);
}

template<class Preface, class Function, class Postface CPP_IF_CPP11(= ignore_t)>
_aux::recursive_intermediate<Preface, Function, Postface, -1u>
recursive_intermediate(Preface CPP_RVALUE preface, Function CPP_RVALUE functor,
                       Postface CPP_RVALUE postface = Postface())
{
#if __cplusplus >= 201103L
  return {
    std::forward<Preface>(preface)
  , std::forward<Function>(functor)
  , std::forward<Postface>(postface)
  };
#else
  return _aux::recursive_intermediate<Preface, Function, Postface, -1u>(
    preface, functor, postface);
#endif
}

template<std::size_t Dimension, class Preface, class Function, class Postface CPP_IF_CPP11(= ignore_t)>
_aux::recursive_intermediate<Preface, Function, Postface, Dimension>
recursive_intermediate(Preface CPP_RVALUE preface, Function CPP_RVALUE functor,
                       Postface CPP_RVALUE postface = Postface())
{
#if __cplusplus >= 201103L
  return {
    std::forward<Preface>(preface)
  , std::forward<Function>(functor)
  , std::forward<Postface>(postface)
  };
#else
  return _aux::recursive_intermediate<Preface, Function, Postface, Dimension>(
    preface, functor, postface);
#endif
}

namespace _aux {

template<class Preface, class Function, class Postface, std::size_t Dimension>
struct recursive_intermediate
{
  Preface preface;
  Function functor;
  Postface postface;

#if __cplusplus < 201103L
    recursive_intermediate(Preface preface, Function functor, Postface postface)
  : preface(preface)
  , functor(functor)
  , postface(postface)
  {}
#endif

  template<class Container>
  void operator()(Container& v)
  {
    preface();
    ::falcon::algorithm::recursive_for_each<Dimension>(v, functor);
    postface();
  }
};

template<class Function, class Postface, std::size_t Dimension>
struct recursive_intermediate<ignore_t, Function, Postface, Dimension>
{
  Function functor;
  Postface postface;

#if __cplusplus < 201103L
  recursive_intermediate(const ignore_t&, Function functor, Postface postface)
  : functor(functor)
  , postface(postface)
  {}
#endif

  template<class Container>
  void operator()(Container& v)
  {
    ::falcon::algorithm::recursive_for_each<Dimension>(v, functor);
    postface();
  }
};

template<class Preface, class Function, std::size_t Dimension>
struct recursive_intermediate<Preface, Function, ignore_t, Dimension>
{
  Preface preface;
  Function functor;

#if __cplusplus < 201103L
  recursive_intermediate(Preface preface, Function functor, const ignore_t&)
  : preface(preface)
  , functor(functor)
  {}
#endif

  template<class Container>
  void operator()(Container& v)
  {
    preface();
    ::falcon::algorithm::recursive_for_each<Dimension>(v, functor);
  }
};

template<class Function, std::size_t Dimension>
struct recursive_intermediate<ignore_t, Function, ignore_t, Dimension>
{
  Function functor;

#if __cplusplus < 201103L
  recursive_intermediate(const ignore_t&, Function functor, const ignore_t&)
  : functor(functor)
  {}
#endif

  template<class Container>
  void operator()(Container& v)
  {
    ::falcon::algorithm::recursive_for_each<Dimension>(v, functor);
  }
};

}

}
}

#endif
