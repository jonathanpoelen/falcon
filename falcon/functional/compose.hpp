#ifndef _FALCON_FUNCTIONAL_COMPOSE_HPP
#define _FALCON_FUNCTIONAL_COMPOSE_HPP

#include <functional>
#include <falcon/c++/constexpr.hpp>
#include <falcon/preprocessor/move.hpp>
#ifdef __GXX_EXPERIMENTAL_CXX0X__
# include <falcon/arg/arg.hpp>
# include <falcon/tuple/tuple_compose.hpp>
# include <falcon/helper/has_result_type.hpp>
# include <falcon/helper/has_argument_type.hpp>
#endif

namespace falcon {

#ifdef __GXX_EXPERIMENTAL_CXX0X__
template <class _WrapArgument, class _WrapResult>
struct __compose_check_type
{
	static const bool value = (
		helper::has_argument_type<_WrapArgument>::value
		&& helper::has_result_type<_WrapResult>::value
	);
};
#endif

/**
 * @defgroup functors Function Objects
 * @ingroup utilities
 * @{
 */

/** The @c unary_compose functor is constructed from two functions/functors,
 * @c f and @c g.  Calling @c operator() with a single argument @c x
 * returns @c f(g(x)).  The function @c compose1 takes the two functions
 * and constructs a @c unary_compose variable for you.
 * @{
 */
#ifndef __GXX_EXPERIMENTAL_CXX0X__
template <class _Operation1, class _Operation2>
struct unary_compose
: public std::unary_function<
	typename _Operation2::argument_type,
	typename _Operation1::result_type
>
{
protected:
	_Operation1 _M_fn1;
	_Operation2 _M_fn2;

public:
	unary_compose(const _Operation1& __x, const _Operation2& __y)
	: _M_fn1(__x)
	, _M_fn2(__y)
	{}

	unary_compose()
	: _M_fn1()
	, _M_fn2()
	{}

	typename _Operation1::result_type
	operator()(typename _Operation2::argument_type& __x) const
	{ return _M_fn1(_M_fn2(__x)); }

	typename _Operation1::result_type
	operator()(typename _Operation2::argument_type& __x)
	{ return _M_fn1(_M_fn2(__x)); }
};

#else

template <class _Operation1, class _Operation2,
bool = __compose_check_type<_Operation2, _Operation1>::value>
struct unary_compose
: public std::unary_function<
	typename _Operation2::argument_type,
	typename _Operation1::result_type
>
{
	typedef typename _Operation2::argument_type argument_type;
	typedef typename _Operation1::result_type result_type;

protected:
	_Operation1 _M_fn1;
	_Operation2 _M_fn2;

public:
	constexpr unary_compose(const _Operation1& __x, const _Operation2& __y)
	: _M_fn1(__x)
	, _M_fn2(__y)
	{}

	constexpr unary_compose() = default;

	constexpr unary_compose(_Operation1&& __x, const _Operation2& __y)
	: _M_fn1(std::forward<_Operation1>(__x))
	, _M_fn2(__y)
	{}

	constexpr unary_compose(const _Operation1& __x, _Operation2&& __y)
	: _M_fn1(__x)
	, _M_fn2(std::forward<_Operation2>(__y))
	{}

	constexpr unary_compose(_Operation1&& __x, _Operation2&& __y)
	: _M_fn1(std::forward<_Operation1>(__x))
	, _M_fn2(std::forward<_Operation2>(__y))
	{}

	result_type operator()(argument_type& __x) const
	{ return _M_fn1(_M_fn2(__x)); }
};

template <class _Operation1, class _Operation2>
struct unary_compose<_Operation1, _Operation2, false>
{
protected:
	_Operation1 _M_fn1;
	_Operation2 _M_fn2;

public:
	constexpr unary_compose(const _Operation1& __x, const _Operation2& __y)
	: _M_fn1(__x)
	, _M_fn2(__y)
	{}

	constexpr unary_compose() = default;

	constexpr unary_compose(_Operation1&& __x, const _Operation2& __y)
	: _M_fn1(std::forward<_Operation1>(__x))
	, _M_fn2(__y)
	{}

	constexpr unary_compose(const _Operation1& __x, _Operation2&& __y)
	: _M_fn1(__x)
	, _M_fn2(std::forward<_Operation2>(__y))
	{}

	constexpr unary_compose(_Operation1&& __x, _Operation2&& __y)
	: _M_fn1(std::forward<_Operation1>(__x))
	, _M_fn2(std::forward<_Operation2>(__y))
	{}

	template<typename _T>
	constexpr typename std::result_of<const _Operation1&(
		typename std::result_of<const _Operation2&(_T&)>::type
	)>::type operator()(_T& __x) const
	{ return _M_fn1(_M_fn2(__x)); }

	template<typename _T>
	typename std::result_of<_Operation1&(
		typename std::result_of<_Operation2&(_T&)>::type
	)>::type operator()(_T& __x)
	{ return _M_fn1(_M_fn2(__x)); }
};

#endif

template <class _Operation1, class _Operation2>
inline unary_compose<_Operation1, _Operation2>
compose1(FALCON_RVALUE(_Operation1) __fn1,
		 FALCON_RVALUE(_Operation2) __fn2)
{
	return unary_compose<_Operation1,_Operation2>(
		FALCON_FORWARD(_Operation1, __fn1),
		FALCON_FORWARD(_Operation2, __fn2)
	);
}
//@}

/** The @c binary_compose is constructed from three functors, @c f, @c g1,
 * and @c g2.  Its @c operator() returns @c f(g1(x),g2(x)).  The function
 * @c compose2 takes f, g1, and g2, and constructs the @c binary_compose
 * instance for you.  For example, if @c f returns an int, then
 * \code
 * int answer = (compose2(f,g1,g2))(x);
 * \endcode
 * is equivalent to
 * \code
 * int temp1 = g1(x);
 * int temp2 = g2(x);
 * int answer = f(temp1,temp2);
 * \endcode
 * But the first form is more compact, and can be passed around as a
 * functor to other algorithms.
 * @{
 */
#ifndef __GXX_EXPERIMENTAL_CXX0X__
template <class _Operation1, class _Operation2, class _Operation3>
struct binary_compose
: public std::unary_function<
	typename _Operation2::argument_type,
	typename _Operation1::result_type
> {
protected:
	_Operation1 _M_fn1;
	_Operation2 _M_fn2;
	_Operation3 _M_fn3;

public:
	binary_compose(const _Operation1& __x, const _Operation2& __y,
				   const _Operation3& __z)
	: _M_fn1(__x)
	, _M_fn2(__y)
	, _M_fn3(__z)
	{}

	binary_compose()
	: _M_fn1()
	, _M_fn2()
	, _M_fn3()
	{}

	typename _Operation1::result_type
	operator()(typename _Operation2::argument_type& __x) const
	{ return _M_fn1(_M_fn2(__x), _M_fn3(__x)); }
};

#else

template <class _Operation1, class _Operation2, class _Operation3,
bool = __compose_check_type<_Operation2, _Operation1>::value>
struct binary_compose
: public std::unary_function<
	typename _Operation2::argument_type,
	typename _Operation1::result_type
> {
protected:
	_Operation1 _M_fn1;
	_Operation2 _M_fn2;
	_Operation3 _M_fn3;

public:
	constexpr binary_compose(const _Operation1& __x,
							 const _Operation2& __y,
							 const _Operation3& __z)
	: _M_fn1(__x)
	, _M_fn2(__y)
	, _M_fn3(__z)
	{}

	constexpr binary_compose() = default;

	constexpr binary_compose(_Operation1&& __x, _Operation2&& __y,
							 _Operation3&& __z)
	: _M_fn1(std::forward<_Operation1>(__x))
	, _M_fn2(std::forward<_Operation2>(__y))
	, _M_fn3(std::forward<_Operation2>(__z))
	{}

	typename _Operation1::result_type
	operator()(typename _Operation2::argument_type& __x) const
	{ return _M_fn1(_M_fn2(__x), _M_fn3(__x)); }
};

template <class _Operation1, class _Operation2, class _Operation3>
struct binary_compose<_Operation1, _Operation2, _Operation3, false>
{
protected:
	_Operation1 _M_fn1;
	_Operation2 _M_fn2;
	_Operation3 _M_fn3;

public:
	constexpr binary_compose(const _Operation1& __x,
							 const _Operation2& __y,
							 const _Operation3& __z)
	: _M_fn1(__x)
	, _M_fn2(__y)
	, _M_fn3(__z)
	{}

	constexpr binary_compose() = default;

	constexpr binary_compose(_Operation1&& __x, _Operation2&& __y,
							 _Operation3&& __z)
	: _M_fn1(std::forward<_Operation1>(__x))
	, _M_fn2(std::forward<_Operation2>(__y))
	, _M_fn3(std::forward<_Operation2>(__z))
	{}

	template<typename _T>
	constexpr typename std::result_of<const _Operation1&(
		const _Operation2&(_T&),
		const _Operation3&(_T&)
	)>::type operator()(_T& __x) const
	{ return _M_fn1(_M_fn2(__x), _M_fn3(__x)); }

	template<typename _T>
	constexpr typename std::result_of<_Operation1&(
		_Operation2&(_T&),
		_Operation3&(_T&)
	)>::type operator()(_T& __x)
	{ return _M_fn1(_M_fn2(__x), _M_fn3(__x)); }
};
//@}

#endif

template <class _Operation1, class _Operation2, class _Operation3>
inline binary_compose<_Operation1, _Operation2, _Operation3>
compose2(FALCON_RVALUE(_Operation1) __fn1,
		 FALCON_RVALUE(_Operation2) __fn2,
		 FALCON_RVALUE(_Operation3) __fn3)
{
	return binary_compose<_Operation1,_Operation2,_Operation3>(
		FALCON_FORWARD(_Operation1, __fn1),
		FALCON_FORWARD(_Operation2, __fn2),
		FALCON_FORWARD(_Operation3, __fn3)
	);
}


#ifdef __GXX_EXPERIMENTAL_CXX0X__

/** The @c mulary_compose is constructed from tuple functors, @c f, @c t.
 * Its @c operator() returns @c f(std::get<0>(t)(x), ...).
 * The function  @c compose takes f, t and constructs the @c mulary_compose
 * instance for you.  For example, if @c f returns an int, then
 * \code
 * int answer = (compose2(f,g1,g2,g3))(x);
 * \endcode
 * is equivalent to
 * \code
 * int temp1 = g1(x);
 * int temp2 = g2(x);
 * int temp3 = g3(x);
 * int answer = f(temp1,temp2,temp3);
 * \endcode
 * @{
 */
template<class _Operation, class _Operations,
bool = __compose_check_type<
	typename std::tuple_element<0, _Operations>::type,
	_Operation
>::value>
struct mulary_compose;

template<class _Operation, class... _Operations>
struct mulary_compose<_Operation, std::tuple<_Operations...>, true>
: public std::unary_function<
	typename arg_element<0, _Operations...>::type::argument_type,
	typename _Operation::result_type
> {
protected:
	_Operation _M_fn;
	std::tuple<_Operations...> _M_fns;

public:
	constexpr mulary_compose() = default;

	constexpr mulary_compose(_Operation&& __x,
							 std::tuple<_Operations...>&& __y)
	: _M_fn(std::forward<_Operation>(__x))
	, _M_fns(std::forward<std::tuple<_Operations...>>(__y))
	{}

	constexpr mulary_compose(_Operation&& __x,
							 std::tuple<_Operations&&...> __y)
	: _M_fn(std::forward<_Operation>(__x))
	, _M_fns(__y)
	{}

	constexpr mulary_compose(std::tuple<_Operations&&...> __y)
	: _M_fn()
	, _M_fns(__y)
	{}

	constexpr mulary_compose(std::tuple<_Operations...>&& __y)
	: _M_fn()
	, _M_fns(std::forward<std::tuple<_Operations...>>(__y))
	{}

	template<typename _Functor, typename... _Functors>
	constexpr mulary_compose(_Functor&& __x, _Functors&&... __y)
	: _M_fn(std::forward<_Functors>(__x)...)
	, _M_fns(std::forward<_Functors>(__y)...)
	{}

	constexpr typename _Operation::result_type
	operator()(const typename arg_element<0, _Operations...>::type::argument_type& __x) const
	{
		return tuple_compose<_Operation&>(
			parameter_index<0>(),
			_M_fn,
			_M_fns,
			std::tuple<const typename arg_element<
				0,
				_Operations...
			>::type::argument_type&>(__x)
		);
	}
};

template<class _Operation, class... _Operations>
struct mulary_compose<_Operation, std::tuple<_Operations...>, false>
{
protected:
	_Operation _M_fn;
	std::tuple<_Operations...> _M_fns;

public:
	constexpr mulary_compose() = default;

	constexpr mulary_compose(_Operation&& __x,
							 std::tuple<_Operations...>&& __y)
	: _M_fn(std::forward<_Operation>(__x))
	, _M_fns(std::forward<std::tuple<_Operations...>>(__y))
	{}

	constexpr mulary_compose(_Operation&& __x,
							 std::tuple<_Operations&&...> __y)
	: _M_fn(std::forward<_Operation>(__x))
	, _M_fns(__y)
	{}

	constexpr mulary_compose(std::tuple<_Operations&&...> __y)
	: _M_fn()
	, _M_fns(__y)
	{}

	constexpr mulary_compose(std::tuple<_Operations...>&& __y)
	: _M_fn()
	, _M_fns(std::forward<std::tuple<_Operations...>>(__y))
	{}

	template<typename _Functor, typename... _Functors>
	constexpr mulary_compose(_Functor&& __x, _Functors&&... __y)
	: _M_fn(std::forward<_Functor>(__x))
	, _M_fns(std::forward<_Functors>(__y)...)
	{}

	template<typename _T>
	constexpr typename __tuple_compose<
		0, sizeof...(_Operations), const _Operation,
		const std::tuple<_Operations...>,
		const std::tuple<_T&>,
		parameter_index<0>
	>::__result_type operator()(_T& __x) const
	{
		return tuple_compose<const _Operation&>(
			parameter_index<0>(),
			_M_fn,
			_M_fns,
			std::tuple<_T&>(__x)
		);
	}

	template<typename _T>
	typename __tuple_compose<
		0, sizeof...(_Operations), _Operation,
		std::tuple<_Operations...>,
		const std::tuple<_T&>,
		parameter_index<0>
	>::__result_type operator()(_T& __x)
	{
		return tuple_compose<_Operation&>(
			parameter_index<0>(),
			_M_fn,
			_M_fns,
			std::tuple<_T&>(__x)
		);
	}
};

template<class _Operation, class... _Operations>
constexpr inline mulary_compose<_Operation, std::tuple<_Operations...>>
compose(_Operation&& __fn1, _Operations&&... __fns)
{
	return {
		std::forward<_Operation>(__fn1),
		std::forward<_Operations>(__fns)...
	};
}

template<class _Operation, class... _Operations>
constexpr inline mulary_compose<_Operation, std::tuple<_Operations...>>
compose(_Operation&& __fn1, std::tuple<_Operations...>&& __fns)
{
	return {
		std::forward<_Operation>(__fn1),
		std::forward<_Operations>(__fns)...
	};
}

template<class _Operation, class... _Operations>
constexpr inline mulary_compose<_Operation, std::tuple<_Operations...>>
compose(_Operation&& __fn1, std::tuple<_Operations&&...> __fns)
{
	return {
		std::forward<_Operation>(__fn1),
		__fns
	};
}
//@}

#endif
// @}

}

#endif