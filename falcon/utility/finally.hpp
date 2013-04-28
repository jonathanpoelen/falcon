#ifndef _FALCON_FUNCTIONAL_FINALLY_HPP
#define _FALCON_FUNCTIONAL_FINALLY_HPP

#include <utility>

namespace falcon {

/**
 * \brief Call _Functor when @p finally is destroy.
 *
 * @code
 * {
 *   T * v = new T;
 *   auto finally = falcon::make_finally<>([v](){ delete v; });
 *   //...
 *   if (condition)
 *     throw std::runtime_error("...");
 * }
 * @endcode
 * equivalent to
 * @code
 * {
 *   T * v = new T;
 *   //...
 *   if (condition)
 *   {
 *     delete v;
 *     throw std::runtime_error("...");
 *   }
 *   delete v;
 * }
 * @endcode
 */
template <typename _Functor>
struct finally
{
	_Functor _M_functor;

	finally()
	: _M_functor()
	{}

#if __cplusplus >= 201103L
	finally(_Functor&& func)
	: _M_functor(std::forward<_Functor>(func))
	{}
#else
	finally(_Functor func)
	: _M_functor(func)
	{}
#endif

	~finally()
	{
		_M_functor();
	}
};

#if __cplusplus >= 201103L
template<typename _Functor>
finally<_Functor> make_finally(_Functor&& func)
{
	return {std::forward<_Functor>(func)};
}
#else
template<typename _Functor>
finally<_Functor> make_finally(_Functor func)
{
	return finally<_Functor>(func);
}
#endif

}

#endif