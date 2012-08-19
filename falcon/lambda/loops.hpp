#ifndef _FALCON_LAMBDA_LOOPS_HPP
#define _FALCON_LAMBDA_LOOPS_HPP

#include <utility>
#include <falcon/lambda/lambda.hpp>

namespace falcon {
namespace lambda {

template<typename _Init, typename _Functor, typename _End, typename _State>
struct forloop
{
	_Init init;
	_Functor condition;
	_End  endf;
	_State f;

	template<typename... _Args>
	inline void operator()(_Args&&... args)
	{
		for (auto v = init(std::forward<_Args>(args)...); condition(v, std::forward<_Args>(args)...); endf(v, std::forward<_Args>(args)...))
			f(v, std::forward<_Args>(args)...);
	}
};

template<typename _Functor, typename _State>
struct whileloop
{
	_Functor condition;
	_State f;

	template<typename... _Args>
	inline void operator()(_Args&&... args)
	{
		while (condition(std::forward<_Args>(args)...))
			f(std::forward<_Args>(args)...);
	}
};

template<typename _Functor, typename _State>
struct do_whileloop
{
	_Functor condition;
	_State f;

	template<typename... _Args>
	inline void operator()(_Args&&... args)
	{
		do {
			f(std::forward<_Args>(args)...);
		} while (condition(std::forward<_Args>(args)...));
	}
};

template<typename _Init, typename _Functor, typename _End, typename _State>
inline ___lambda<operators::binder, forloop<_Init, _Functor, _End, _State>, void> for_loop(_Init init, _Functor condition, _End endf, _State f)
{
	return {{init, condition, endf, f}};
}

template<typename _Functor, typename _State>
inline ___lambda<operators::binder, whileloop<_Functor, _State>, void> while_loop(_Functor condition, _State f)
{
	return {{condition, f}};
}

template<typename _Functor, typename _State>
inline ___lambda<operators::binder, do_whileloop<_Functor, _State>, void> do_while_loop(_Functor condition, _State f)
{
	return {{condition, f}};
}

}
}

#endif
