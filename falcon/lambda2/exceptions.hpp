#ifndef FALCON_LAMBDA2_EXCEPTIONS_HPP
#define FALCON_LAMBDA2_EXCEPTIONS_HPP

#include <falcon/lambda2/lambda.hpp>

namespace falcon {
namespace lambda2 {

namespace _aux {

template<class E, class F>
struct catch_ {
  typedef E exception_type;
  F f;
};

template<class F>
struct catch_all { F f; };

template<class...>
class try_t;

template<class F, class Catch1, class Catch2, class Catch3
, class Catch4, class Catch5, class Catch6>
struct lambda<try_t<Catch1, Catch2, Catch3, Catch4, Catch5, Catch6>, F>
: lambda_with_tuple<F, Catch1, Catch2, Catch3, Catch4, Catch5, Catch6>
{
  using lambda::with_tuple_type::lambda_with_tuple;

  template<class... Args>
  void operator()(const Args &&... args) const
  {
    try {
      std::get<0>(this->t)(std::forward<Args>(args)...);
    }
    catch (typename Catch1::exception_type & e) {
      std::get<1>(this->t).f(std::forward<Args>(args)...);
    }
    catch (typename Catch2::exception_type & e) {
      std::get<2>(this->t).f(std::forward<Args>(args)...);
    }
    catch (typename Catch3::exception_type & e) {
      std::get<3>(this->t).f(std::forward<Args>(args)...);
    }
    catch (typename Catch4::exception_type & e) {
      std::get<4>(this->t).f(std::forward<Args>(args)...);
    }
    catch (typename Catch5::exception_type & e) {
      std::get<5>(this->t).f(std::forward<Args>(args)...);
    }
    catch (typename Catch6::exception_type & e) {
      std::get<6>(this->t).f(std::forward<Args>(args)...);
    }
  }
};

template<class F, class Catch1, class Catch2, class Catch3, class Catch4, class Catch5>
struct lambda<try_t<Catch1, Catch2, Catch3, Catch4, Catch5>, F>
: lambda_with_tuple<F, Catch1, Catch2, Catch3, Catch4, Catch5>
{
  using lambda::with_tuple_type::lambda_with_tuple;

  template<class... Args>
  void operator()(const Args &&... args) const
  {
    try {
      std::get<0>(this->t)(std::forward<Args>(args)...);
    }
    catch (typename Catch1::exception_type & e) {
      std::get<1>(this->t).f(std::forward<Args>(args)...);
    }
    catch (typename Catch2::exception_type & e) {
      std::get<2>(this->t).f(std::forward<Args>(args)...);
    }
    catch (typename Catch3::exception_type & e) {
      std::get<3>(this->t).f(std::forward<Args>(args)...);
    }
    catch (typename Catch4::exception_type & e) {
      std::get<4>(this->t).f(std::forward<Args>(args)...);
    }
    catch (typename Catch5::exception_type & e) {
      std::get<5>(this->t).f(std::forward<Args>(args)...);
    }
  }
};

template<class F, class Catch1, class Catch2
, class Catch3, class Catch4, class Catch5, class CatchAll>
struct lambda<try_t<Catch1, Catch2, Catch3, Catch4, Catch5, catch_all<CatchAll>>, F>
: lambda_with_tuple<F, Catch1, Catch2, Catch3, Catch4, Catch5, catch_all<CatchAll>>
{
  using lambda::with_tuple_type::lambda_with_tuple;

  template<class... Args>
  void operator()(const Args &&... args) const
  {
    try {
      std::get<0>(this->t)(std::forward<Args>(args)...);
    }
    catch (typename Catch1::exception_type & e) {
      std::get<1>(this->t).f(std::forward<Args>(args)...);
    }
    catch (typename Catch2::exception_type & e) {
      std::get<2>(this->t).f(std::forward<Args>(args)...);
    }
    catch (typename Catch3::exception_type & e) {
      std::get<3>(this->t).f(std::forward<Args>(args)...);
    }
    catch (typename Catch4::exception_type & e) {
      std::get<4>(this->t).f(std::forward<Args>(args)...);
    }
    catch (typename Catch5::exception_type & e) {
      std::get<5>(this->t).f(std::forward<Args>(args)...);
    }
    catch (...) {
      std::get<6>(this->t).f(std::forward<Args>(args)...);
    }
  }
};

template<class F, class Catch1, class Catch2, class Catch3, class Catch4>
struct lambda<try_t<Catch1, Catch2, Catch3, Catch4>, F>
: lambda_with_tuple<F, Catch1, Catch2, Catch3, Catch4>
{
  using lambda::with_tuple_type::lambda_with_tuple;

  template<class... Args>
  void operator()(const Args &&... args) const
  {
    try {
      std::get<0>(this->t)(std::forward<Args>(args)...);
    }
    catch (typename Catch1::exception_type & e) {
      std::get<1>(this->t).f(std::forward<Args>(args)...);
    }
    catch (typename Catch2::exception_type & e) {
      std::get<2>(this->t).f(std::forward<Args>(args)...);
    }
    catch (typename Catch3::exception_type & e) {
      std::get<3>(this->t).f(std::forward<Args>(args)...);
    }
    catch (typename Catch4::exception_type & e) {
      std::get<4>(this->t).f(std::forward<Args>(args)...);
    }
  }
};

template<class F, class Catch1, class Catch2, class Catch3, class Catch4, class CatchAll>
struct lambda<try_t<Catch1, Catch2, Catch3, Catch4, catch_all<CatchAll>>, F>
: lambda_with_tuple<F, Catch1, Catch2, Catch3, Catch4, catch_all<CatchAll>>
{
  using lambda::with_tuple_type::lambda_with_tuple;

  template<class... Args>
  void operator()(const Args &&... args) const
  {
    try {
      std::get<0>(this->t)(std::forward<Args>(args)...);
    }
    catch (typename Catch1::exception_type & e) {
      std::get<1>(this->t).f(std::forward<Args>(args)...);
    }
    catch (typename Catch2::exception_type & e) {
      std::get<2>(this->t).f(std::forward<Args>(args)...);
    }
    catch (typename Catch3::exception_type & e) {
      std::get<3>(this->t).f(std::forward<Args>(args)...);
    }
    catch (typename Catch4::exception_type & e) {
      std::get<4>(this->t).f(std::forward<Args>(args)...);
    }
    catch (...) {
      std::get<5>(this->t).f(std::forward<Args>(args)...);
    }
  }
};

template<class F, class Catch1, class Catch2, class Catch3>
struct lambda<try_t<Catch1, Catch2, Catch3>, F>
: lambda_with_tuple<F, Catch1, Catch2, Catch3>
{
  using lambda::with_tuple_type::lambda_with_tuple;

  template<class... Args>
  void operator()(const Args &&... args) const
  {
    try {
      std::get<0>(this->t)(std::forward<Args>(args)...);
    }
    catch (typename Catch1::exception_type & e) {
      std::get<1>(this->t).f(std::forward<Args>(args)...);
    }
    catch (typename Catch2::exception_type & e) {
      std::get<2>(this->t).f(std::forward<Args>(args)...);
    }
    catch (typename Catch3::exception_type & e) {
      std::get<3>(this->t).f(std::forward<Args>(args)...);
    }
  }
};

template<class F, class Catch1, class Catch2, class Catch3, class CatchAll>
struct lambda<try_t<Catch1, Catch2, Catch3, catch_all<CatchAll>>, F>
: lambda_with_tuple<F, Catch1, Catch2, Catch3, catch_all<CatchAll>>
{
  using lambda::with_tuple_type::lambda_with_tuple;

  template<class... Args>
  void operator()(const Args &&... args) const
  {
    try {
      std::get<0>(this->t)(std::forward<Args>(args)...);
    }
    catch (typename Catch1::exception_type & e) {
      std::get<1>(this->t).f(std::forward<Args>(args)...);
    }
    catch (typename Catch2::exception_type & e) {
      std::get<2>(this->t).f(std::forward<Args>(args)...);
    }
    catch (typename Catch3::exception_type & e) {
      std::get<3>(this->t).f(std::forward<Args>(args)...);
    }
    catch (...) {
      std::get<4>(this->t).f(std::forward<Args>(args)...);
    }
  }
};

template<class F, class Catch1, class Catch2>
struct lambda<try_t<Catch1, Catch2>, F>
: lambda_with_tuple<F, Catch1, Catch2>
{
  using lambda::with_tuple_type::lambda_with_tuple;

  template<class... Args>
  void operator()(const Args &&... args) const
  {
    try {
      std::get<0>(this->t)(std::forward<Args>(args)...);
    }
    catch (typename Catch1::exception_type & e) {
      std::get<1>(this->t).f(std::forward<Args>(args)...);
    }
    catch (typename Catch2::exception_type & e) {
      std::get<2>(this->t).f(std::forward<Args>(args)...);
    }
  }
};

template<class F, class Catch1, class Catch2, class CatchAll>
struct lambda<try_t<Catch1, Catch2, catch_all<CatchAll>>, F>
: lambda_with_tuple<F, Catch1, Catch2, catch_all<CatchAll>>
{
  using lambda::with_tuple_type::lambda_with_tuple;

  template<class... Args>
  void operator()(const Args &&... args) const
  {
    try {
      std::get<0>(this->t)(std::forward<Args>(args)...);
    }
    catch (typename Catch1::exception_type & e) {
      std::get<1>(this->t).f(std::forward<Args>(args)...);
    }
    catch (typename Catch2::exception_type & e) {
      std::get<2>(this->t).f(std::forward<Args>(args)...);
    }
    catch (...) {
      std::get<3>(this->t).f(std::forward<Args>(args)...);
    }
  }
};

template<class F, class Catch1>
struct lambda<try_t<Catch1>, F>
: lambda_with_tuple<F, Catch1>
{
  using lambda::with_tuple_type::lambda_with_tuple;

  template<class... Args>
  void operator()(const Args &&... args) const
  {
    try {
      std::get<0>(this->t)(std::forward<Args>(args)...);
    }
    catch (typename Catch1::exception_type & e) {
      std::get<1>(this->t).f(std::forward<Args>(args)...);
    }
  }
};

template<class F, class Catch1, class CatchAll>
struct lambda<try_t<Catch1, catch_all<CatchAll>>, F>
: lambda_with_tuple<F, Catch1, catch_all<CatchAll>>
{
  using lambda::with_tuple_type::lambda_with_tuple;

  template<class... Args>
  void operator()(const Args &&... args) const
  {
    try {
      std::get<0>(this->t)(std::forward<Args>(args)...);
    }
    catch (typename Catch1::exception_type & e) {
      std::get<1>(this->t).f(std::forward<Args>(args)...);
    }
    catch (...) {
      std::get<2>(this->t).f(std::forward<Args>(args)...);
    }
  }
};

template<class F, class CatchAll>
struct lambda<try_t<catch_all<CatchAll>>, F>
: lambda_with_tuple<F, catch_all<CatchAll>>
{
  using lambda::with_tuple_type::lambda_with_tuple;

  template<class... Args>
  void operator()(const Args &&... args) const
  {
    try {
      std::get<0>(this->t)(std::forward<Args>(args)...);
    }
    catch (...) {
      std::get<1>(this->t).f(std::forward<Args>(args)...);
    }
  }
};

class rethrow_t;

template<>
struct lambda<rethrow_t>
{
  template<class... Args>
  [[noreturn]] void operator()(const Args &&... args) const
  { throw; }
};

}

template<class F>
_aux::lambda<_aux::func_t<F>> try_catch(F&& f)
{ return {std::forward<F>(f)}; }

template<class F, class Catch1, class Catch2, class Catch3
, class Catch4, class Catch5, class Catch6>
_aux::lambda<_aux::try_t<Catch1, Catch2, Catch3, Catch4, Catch5, Catch6>, F>
try_catch(F&& f
, Catch1 && catch1, Catch2 && catch2, Catch3 && catch3
, Catch4 && catch4, Catch5 && catch5, Catch6 && catch6)
{ return {
  std::forward<F>(f)
, std::forward<Catch1>(catch1)
, std::forward<Catch2>(catch2)
, std::forward<Catch3>(catch3)
, std::forward<Catch4>(catch4)
, std::forward<Catch5>(catch5)
, std::forward<Catch6>(catch6)
}; }

template<class F, class Catch1, class Catch2, class Catch3, class Catch4, class Catch5>
_aux::lambda<_aux::try_t<Catch1, Catch2, Catch3, Catch4, Catch5>, F>
try_catch(F&& f
, Catch1 && catch1, Catch2 && catch2, Catch3 && catch3
, Catch4 && catch4, Catch5 && catch5)
{ return {
  std::forward<F>(f)
, std::forward<Catch1>(catch1)
, std::forward<Catch2>(catch2)
, std::forward<Catch3>(catch3)
, std::forward<Catch4>(catch4)
, std::forward<Catch5>(catch5)
}; }

template<class F, class Catch1, class Catch2, class Catch3, class Catch4>
_aux::lambda<_aux::try_t<Catch1, Catch2, Catch3, Catch4>, F>
try_catch(F&& f, Catch1 && catch1, Catch2 && catch2, Catch3 && catch3, Catch4 && catch4)
{ return {
  std::forward<F>(f)
, std::forward<Catch1>(catch1)
, std::forward<Catch2>(catch2)
, std::forward<Catch3>(catch3)
, std::forward<Catch4>(catch4)
}; }

template<class F, class Catch1, class Catch2, class Catch3>
_aux::lambda<_aux::try_t<Catch1, Catch2, Catch3>, F>
try_catch(F&& f, Catch1 && catch1, Catch2 && catch2, Catch3 && catch3)
{ return {
  std::forward<F>(f)
, std::forward<Catch1>(catch1)
, std::forward<Catch2>(catch2)
, std::forward<Catch3>(catch3)
}; }

template<class F, class Catch1, class Catch2>
_aux::lambda<_aux::try_t<Catch1, Catch2>, F>
try_catch(F&& f, Catch1 && catch1, Catch2 && catch2)
{ return {
  std::forward<F>(f)
, std::forward<Catch1>(catch1)
, std::forward<Catch2>(catch2)
}; }

template<class F, class Catch1>
_aux::lambda<_aux::try_t<Catch1>, F>
try_catch(F&& f, Catch1 && catch1)
{ return {std::forward<F>(f), std::forward<Catch1>(catch1)}; }

template<class Exceptiion, class F>
_aux::catch_<Exceptiion, F> catch_exception(F && f)
{ return {std::forward<F>(f)}; }

template<class F>
_aux::catch_all<F> catch_all(F && f)
{ return {std::forward<F>(f)}; }

template<class F>
_aux::lambda<_aux::rethrow_t> rethrow()
{ return {}; }

}
}

#endif
