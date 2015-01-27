#ifndef FALCON_FUNCTIONAL_FINALLY_HPP
#define FALCON_FUNCTIONAL_FINALLY_HPP

#include <utility>

namespace falcon {

/**
 * \brief Call Functor when @p finally is destroy.
 *
 * @code
 * {
 *   T * v = new T;
 *   auto finally = falcon::make_finally([v](){ delete v; });
 *   //...
 *   if (condition)
 *     throw std::runtime_error("...");
 * }
 * @endcode
 * equivalent to
 * @code
 * {
 *   T * v = new T;
 *   try {
 *     //...
 *     if (condition)
 *       throw std::runtime_error("...");
 *   }
 *   catch (...) {
 *     delete v;
 *     throw;
 *   }
 *   delete v;
 * }
 * @endcode
 */
template <class Functor>
struct finally
{
	finally()
	: functor_()
	{}

#if __cplusplus >= 201103L
	finally(Functor&& func)
	: functor_(std::forward<Functor>(func))
	{}

  finally(finally&&)=default;
  finally& operator=(finally&&)=default;
  finally& operator=(finally const&)=default;

  finally& operator=(Functor && func)
  {
    functor_ = std::forward<Functor>(func);
    return *this;
  }
#else
	finally(Functor func)
	: functor_(func)
  {}

  finally& operator=(Functor func)
  {
    functor_ = func;
    return *this;
  }
#endif

	~finally()
	{
		functor_();
	}

private:
  Functor functor_;
};

template<typename Functor>
finally<Functor> make_finally(Functor&& func)
{ return {std::forward<Functor>(func)}; }


/// \attention finally must not throw an exception
template<class F, class Finally>
auto try_except(F&& f, Finally && finally)
-> decltype(f())
{
  finally<Finally&> d{finally};
  return f();
}

namespace aux_ {
  template<class F, class R = decltype(std::declval<F>()())>
  struct try_except_result
  { using no_void_type = R; };

  template<class F>
  struct try_except_result<F, void>
  { using void_type = void; };
}


template<class F, class Finally>
typename aux_::try_except_result<F>::no_void_type
rethrow_try_except(F&& f, Finally && finally)
{
  if (noexcept(finally())) {
    finally<Finally&> d{finally};
    return f();
  }

  decltype(f()) ret;
  try {
    ret = f();
  }
  catch(...) {
    finally();
    throw;
  }
  finally();
  return ret;
}

template<class F, class Finally>
typename aux_::try_except_result<F>::void_type
rethrow_try_except(F&& f, Finally && finally)
{
  if (noexcept(finally())) {
    finally<Finally&> d{finally};
    return f();
  }

  try {
    f();
  }
  catch(...) {
    finally();
    throw;
  }
  finally();
}

}

#endif
