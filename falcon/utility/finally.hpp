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
template <typename Functor>
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

#if __cplusplus >= 201103L
template<typename Functor>
finally<Functor> make_finally(Functor&& func)
{ return {std::forward<Functor>(func)}; }
#else
template<typename Functor>
finally<Functor> make_finally(Functor func)
{ return finally<Functor>(func); }
#endif

}

#endif
