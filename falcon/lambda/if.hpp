#ifndef _FALCON_LAMBDA_IF_HPP
#define _FALCON_LAMBDA_IF_HPP

#include <falcon/lambda/lambda.hpp>

namespace falcon {
namespace lambda {

template<typename _Functor, typename _TrueFunctor>
struct ifthen
{
	_Functor condition;
	_TrueFunctor true_f;

	template<typename... _Args>
	inline void operator()(_Args&&... args)
	{
		if(condition(std::forward<_Args>(args)...))
			true_f(std::forward<_Args>(args)...);
	}
};

template<typename _Functor, typename _TrueFunctor, typename _FalseFunctor>
struct ifthen_else
{
	_Functor condition;
	_TrueFunctor true_f;
	_FalseFunctor false_f;

	template<typename... _Args>
	inline void operator()(_Args&&... args)
	{
		if(condition(std::forward<_Args>(args)...))
			true_f(std::forward<_Args>(args)...);
		else
			false_f(std::forward<_Args>(args)...);
	}
};

template<typename _Functor, typename _TrueFunctor, typename _FalseFunctor>
struct ifthen_else_return
{
	_Functor condition;
	_TrueFunctor true_f;
	_FalseFunctor false_f;

	template<typename... _Args, typename _Result = typename std::common_type<decltype(true_f(std::declval<_Args>()...)), decltype(false_f(std::declval<_Args>()...))>::type>
	inline _Result operator()(_Args&&... args)
	{
		if (condition(std::forward<_Args>(args)...))
			return true_f(std::forward<_Args>(args)...);
		return false_f(std::forward<_Args>(args)...);
	}
};

template<typename _Functor, typename _TrueFunctor, typename _FalseFunctor>
struct ifthen_return
{
	_Functor condition;
	_TrueFunctor true_f;
	_FalseFunctor f;

	template<typename... _Args, typename _Result = decltype(f(std::declval<_Args>()...))>
	inline _Result operator()(_Args&&... args)
	{
		if(condition(std::forward<_Args>(args)...))
			true_f(std::forward<_Args>(args)...);
		return f(std::forward<_Args>(args)...);
	}
};

template<typename _Functor, typename _TrueFunctor>
inline ___lambda<operators::binder, ifthen<_Functor, _TrueFunctor> > if_then(_Functor condition, _TrueFunctor f)
{
	return {{condition, f}};
}

template<typename _Functor, typename _TrueFunctor, typename _FalseFunctor>
inline ___lambda<operators::binder, ifthen_else<_Functor, _TrueFunctor, _FalseFunctor> > if_then_else(_Functor condition, _TrueFunctor true_f, _FalseFunctor false_f)
{
	return {{condition, true_f, false_f}};
}

template<typename _Functor, typename _TrueFunctor, typename _FalseFunctor>
inline ___lambda<operators::binder, ifthen_else_return<_Functor, _TrueFunctor, _FalseFunctor> > if_then_else_return(_Functor condition, _TrueFunctor true_f, _FalseFunctor false_f)
{
	return {{condition, true_f, false_f}};
}

template<typename _Functor, typename _TrueFunctor, typename _FalseFunctor>
inline ___lambda<operators::binder, ifthen_return<_Functor, _TrueFunctor, _FalseFunctor> > if_then_return(_Functor condition, _TrueFunctor true_f, _FalseFunctor f)
{
	return {{condition, true_f, f}};
}

}
}

#endif
