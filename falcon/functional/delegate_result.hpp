#ifndef FALCON_FUNCTIONAL_DELEGATE_RESULT_HPP
#define FALCON_FUNCTIONAL_DELEGATE_RESULT_HPP

#include <functional>
#include <falcon/preprocessor/move.hpp>
#if __cplusplus > 201100L
# include <falcon/c++0x/syntax.hpp>
# include <falcon/type_traits/if.hpp>
# include <falcon/type_traits/has.hpp>
#endif

namespace falcon {

namespace detail {
template<typename _Delegate, typename _Functor>
struct delegate_result
{
	typedef typename _Delegate::result_type result_type;

private:
	_Delegate m_f;
	_Functor m_g;

public:
	delegate_result()
	: m_f()
	, m_g()
	{}

	delegate_result(FALCON_RVALUE(_Delegate) f)
	: m_f(FALCON_FORWARD(_Delegate, f))
	, m_g()
	{}

	delegate_result(FALCON_RVALUE(_Delegate) f, FALCON_RVALUE(_Functor) g)
	: m_f(FALCON_FORWARD(_Delegate, f))
	, m_g(FALCON_FORWARD(_Functor, g))
	{}

#if __cplusplus > 201100L
	template<typename _Delegate2, typename _Functor2>
	delegate_result(_Delegate2&& f, _Functor2&& g)
	: m_f(std::forward<_Delegate2>(f))
	, m_g(std::forward<_Functor2>(g))
	{}

	template<typename _Delegate2>
	delegate_result(_Delegate2&& f)
	: m_f(std::forward<_Delegate2>(f))
	, m_g()
	{}
#endif

	result_type operator()()
	{ return m_f(m_g()); }

	result_type operator()() const
	{ return m_f(m_g()); }

#if __cplusplus > 201100L
	template<typename... _Args>
	result_type operator()(_Args&&... args)
	{ return m_f(m_g(std::forward<_Args>(args)...)); }

	template<typename... _Args>
	result_type operator()(_Args&&... args) const
	{ return m_f(m_g(std::forward<_Args>(args)...)); }
#endif
};
}

/**
 * @defgroup gtors Function Objects
 * @ingroup utilities
 */

#if __cplusplus <= 201100L
/**
 * The @c delegate_result functor is constructed from two functions/functors,
 * @c f and @c g.  Calling @c operator() without argument returns @c f(g()).
 * The function @c delegate takes the two functions
 * and constructs a @c unary_delegate_result variable for you.
 */
using detail::delegate_result;
#endif

/**
 * The @c unary_delegate_result functor is constructed from two functions/functors,
 * @c f and @c g.  Calling @c operator() with a single argument @c x
 * returns @c f(g(x)).  The function @c delegate1 takes the two functions
 * and constructs a @c unary_delegate_result variable for you.
 */
template<typename _Delegate, typename _Functor>
struct unary_delegate_result
{
	typedef typename _Delegate::result_type result_type;
	typedef typename _Functor::argument_type argument_type;

private:
	_Delegate m_f;
	_Functor m_g;

public:
	unary_delegate_result()
	: m_f()
	, m_g()
	{}

	unary_delegate_result(FALCON_RVALUE(_Delegate) f)
	: m_f(FALCON_FORWARD(_Delegate, f))
	, m_g()
	{}

	unary_delegate_result(FALCON_RVALUE(_Delegate) f,
												FALCON_RVALUE(_Functor) g)
	: m_f(FALCON_FORWARD(_Delegate, f))
	, m_g(FALCON_FORWARD(_Functor, g))
	{}

#if __cplusplus > 201100L
	template<typename _Delegate2, typename _Functor2>
	unary_delegate_result(_Delegate2&& f, _Functor2&& g)
	: m_f(std::forward<_Delegate2>(f))
	, m_g(std::forward<_Functor2>(g))
	{}

	template<typename _Delegate2>
	unary_delegate_result(_Delegate2&& f)
	: m_f(std::forward<_Delegate2>(f))
	, m_g()
	{}
#endif

	result_type operator()(const argument_type& x)
	{ return m_f(m_g(x)); }

	result_type operator()(const argument_type& x) const
	{ return m_f(m_g(x)); }
};

/**
 * The @c binary_delegate_result functor is constructed from two functions/functors,
 * @c f and @c g.  Its @c operator() returns @c f(g(x, y)).  The function @c delegate2
 * takes the two functions and constructs a @c binary_delegate_result variable for you.
 */
template<typename _Delegate, typename _Functor>
struct binary_delegate_result
{
	typedef typename _Delegate::result_type result_type;
	typedef typename _Functor::first_argument_type first_argument_type;
	typedef typename _Functor::second_argument_type second_argument_type;

private:
	_Delegate m_f;
	_Functor m_g;

public:
	binary_delegate_result()
	: m_f()
	, m_g()
	{}

	binary_delegate_result(FALCON_RVALUE(_Delegate) f)
	: m_f(FALCON_FORWARD(_Delegate, f))
	, m_g()
	{}

	binary_delegate_result(FALCON_RVALUE(_Delegate) f,
												 FALCON_RVALUE(_Functor) g)
	: m_f(FALCON_FORWARD(_Delegate, f))
	, m_g(FALCON_FORWARD(_Functor, g))
	{}

#if __cplusplus > 201100L
	template<typename _Delegate2, typename _Functor2>
	binary_delegate_result(_Delegate2&& f, _Functor2&& g)
	: m_f(std::forward<_Delegate2>(f))
	, m_g(std::forward<_Functor2>(g))
	{}

	template<typename _Delegate2>
	binary_delegate_result(_Delegate2&& f)
	: m_f(std::forward<_Delegate2>(f))
	, m_g()
	{}
#endif

	result_type operator()(const first_argument_type& x, const second_argument_type& y)
	{ return m_f(m_g(x,y)); }

	result_type operator()(const first_argument_type& x, const second_argument_type& y) const
	{ return m_f(m_g(x,y)); }
};

#if __cplusplus > 201100L
template<typename _Delegate, typename _Functor>
struct __delegate_result
{
	_Delegate _m_f;
	_Functor _m_g;

	__delegate_result() = default;

	__delegate_result(_Delegate&& f)
	: _m_f(std::forward<_Delegate>(f))
	, _m_g()
	{}

	__delegate_result(_Delegate&& f, _Functor&& g)
	: _m_f(std::forward<_Delegate>(f))
	, _m_g(std::forward<_Functor>(g))
	{}

	template<typename _Delegate2, typename _Functor2>
	__delegate_result(_Delegate2&& f, _Functor2&& g)
	: _m_f(std::forward<_Delegate2>(f))
	, _m_g(std::forward<_Functor2>(g))
	{}

	template<typename _Delegate2>
	__delegate_result(_Delegate2&& f)
	: _m_f(std::forward<_Delegate2>(f))
	, _m_g()
	{}

	template<typename... _Args>
	CPP0X_DELEGATE_FUNCTION(operator()(_Args&&... args),
													this->_m_f(this->_m_g(std::forward<_Args>(args)...)))

	template<typename... _Args>
	CPP0X_DELEGATE_FUNCTION(operator()(_Args&&... args) const,
													this->_m_f(this->_m_g(std::forward<_Args>(args)...)))
};

/**
 * The @c delegate_result functor is constructed from two functions/functors,
 * @c f and @c g.  Calling @c operator() without argument returns @c f(g()).
 * The function @c delegate takes the two functions
 * and constructs a @c unary_delegate_result variable for you.
 */
template<typename _Delegate, typename _Functor>
using delegate_result = typename if_c<
	has_result_type<_Delegate>,
	typename if_c<
		has_argument_type<_Functor>,
		unary_delegate_result<_Delegate, _Functor>,
		typename if_<
			has_first_argument_type<_Functor>() && has_second_argument_type<_Functor>(),
			binary_delegate_result<_Delegate, _Functor>,
			detail::delegate_result<_Delegate, _Functor>
		>::type
	>::type,
	__delegate_result<_Delegate, _Functor>
>::type;
#endif

template<typename _Delegate, typename _Functor>
delegate_result<_Delegate, _Functor>
delegate(_Delegate f, _Functor g)
#if __cplusplus > 201100L
{ return {f, g}; }
#else
{ return delegate_result<_Delegate, _Functor>(f, g); }
#endif

template<typename _Delegate, typename _Functor>
unary_delegate_result<_Delegate, _Functor>
delegate1(_Delegate f, _Functor g)
#if __cplusplus > 201100L
{ return {f, g}; }
#else
{ return unary_delegate_result<_Delegate, _Functor>(f, g); }
#endif

template<typename _Delegate, typename _Functor>
binary_delegate_result<_Delegate, _Functor>
delegate2(_Delegate f, _Functor g)
#if __cplusplus > 201100L
{ return {f, g}; }
#else
{ return binary_delegate_result<_Delegate, _Functor>(f, g); }
#endif

}

#endif