#ifndef FALCON_FUNCTIONAL_DELEGATE_RESULT_HPP
#define FALCON_FUNCTIONAL_DELEGATE_RESULT_HPP

#include <functional>
#include <falcon/utility/move.hpp>
#include <falcon/c++/reference.hpp>
#if __cplusplus >= 201103L
# include <falcon/c++1x/syntax.hpp>
# include <falcon/type_traits/if.hpp>
# include <falcon/type_traits/has.hpp>
#endif

namespace falcon {

namespace detail {
template<typename Delegate, typename Functor>
struct delegate_result
{
	typedef typename Delegate::result_type result_type;

private:
	Delegate m_f;
	Functor m_g;

public:
	delegate_result()
	: m_f()
	, m_g()
	{}

	delegate_result(Delegate CPP_RVALUE_OR_CONST_REFERENCE f)
	: m_f(FALCON_FORWARD(Delegate, f))
	, m_g()
	{}

	delegate_result(Delegate CPP_RVALUE_OR_CONST_REFERENCE f,
                    Functor CPP_RVALUE_OR_CONST_REFERENCE g)
	: m_f(FALCON_FORWARD(Delegate, f))
	, m_g(FALCON_FORWARD(Functor, g))
	{}

#if __cplusplus >= 201103L
	template<typename Delegate2, typename Functor2>
	delegate_result(Delegate2&& f, Functor2&& g)
	: m_f(std::forward<Delegate2>(f))
	, m_g(std::forward<Functor2>(g))
	{}

	template<typename Delegate2>
	delegate_result(Delegate2&& f)
	: m_f(std::forward<Delegate2>(f))
	, m_g()
	{}
#endif

	result_type operator()() const
	{ return m_f(m_g()); }

#if __cplusplus >= 201103L
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

#if __cplusplus < 201103L
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
template<typename Delegate, typename Functor>
struct unary_delegate_result
{
	typedef typename Delegate::result_type result_type;
	typedef typename Functor::argument_type argument_type;

private:
	Delegate m_f;
	Functor m_g;

public:
	unary_delegate_result()
	: m_f()
	, m_g()
	{}

	unary_delegate_result(Delegate CPP_RVALUE_OR_CONST_REFERENCE f)
	: m_f(FALCON_FORWARD(Delegate, f))
	, m_g()
	{}

	unary_delegate_result(Delegate CPP_RVALUE_OR_CONST_REFERENCE f,
                          Functor CPP_RVALUE_OR_CONST_REFERENCE g)
	: m_f(FALCON_FORWARD(Delegate, f))
	, m_g(FALCON_FORWARD(Functor, g))
	{}

#if __cplusplus >= 201103L
	template<typename Delegate2, typename Functor2>
	unary_delegate_result(Delegate2&& f, Functor2&& g)
	: m_f(std::forward<Delegate2>(f))
	, m_g(std::forward<Functor2>(g))
	{}

	template<typename Delegate2>
	unary_delegate_result(Delegate2&& f)
	: m_f(std::forward<Delegate2>(f))
	, m_g()
	{}
#endif

	result_type operator()(const argument_type& x) const
	{ return m_f(m_g(x)); }
};

/**
 * The @c binary_delegate_result functor is constructed from two functions/functors,
 * @c f and @c g.  Its @c operator() returns @c f(g(x, y)).  The function @c delegate2
 * takes the two functions and constructs a @c binary_delegate_result variable for you.
 */
template<typename Delegate, typename Functor>
struct binary_delegate_result
{
	typedef typename Delegate::result_type result_type;
	typedef typename Functor::first_argument_type first_argument_type;
	typedef typename Functor::second_argument_type second_argument_type;

private:
	Delegate m_f;
	Functor m_g;

public:
	binary_delegate_result()
	: m_f()
	, m_g()
	{}

	binary_delegate_result(Delegate CPP_RVALUE_OR_CONST_REFERENCE f)
	: m_f(FALCON_FORWARD(Delegate, f))
	, m_g()
	{}

	binary_delegate_result(Delegate CPP_RVALUE_OR_CONST_REFERENCE f,
                           Functor CPP_RVALUE_OR_CONST_REFERENCE g)
	: m_f(FALCON_FORWARD(Delegate, f))
	, m_g(FALCON_FORWARD(Functor, g))
	{}

#if __cplusplus >= 201103L
	template<typename Delegate2, typename Functor2>
	binary_delegate_result(Delegate2&& f, Functor2&& g)
	: m_f(std::forward<Delegate2>(f))
	, m_g(std::forward<Functor2>(g))
	{}

	template<typename Delegate2>
	binary_delegate_result(Delegate2&& f)
	: m_f(std::forward<Delegate2>(f))
	, m_g()
	{}
#endif

	result_type operator()(const first_argument_type& x, const second_argument_type& y) const
	{ return m_f(m_g(x,y)); }
};

#if __cplusplus >= 201103L
template<typename Delegate, typename Functor>
struct __delegate_result
{
	Delegate _m_f;
	Functor _m_g;

	__delegate_result() = default;

	__delegate_result(Delegate&& f)
	: _m_f(std::forward<Delegate>(f))
	, _m_g()
	{}

	__delegate_result(Delegate&& f, Functor&& g)
	: _m_f(std::forward<Delegate>(f))
	, _m_g(std::forward<Functor>(g))
	{}

	template<typename Delegate2, typename Functor2>
	__delegate_result(Delegate2&& f, Functor2&& g)
	: _m_f(std::forward<Delegate2>(f))
	, _m_g(std::forward<Functor2>(g))
	{}

	template<typename Delegate2>
	__delegate_result(Delegate2&& f)
	: _m_f(std::forward<Delegate2>(f))
	, _m_g()
	{}

	template<typename... _Args>
	CPP1X_DELEGATE_FUNCTION(operator()(_Args&&... args) const,
                            this->_m_f(this->_m_g(std::forward<_Args>(args)...)))
};

/**
 * The @c delegate_result functor is constructed from two functions/functors,
 * @c f and @c g.  Calling @c operator() without argument returns @c f(g()).
 * The function @c delegate takes the two functions
 * and constructs a @c unary_delegate_result variable for you.
 */
template<typename Delegate, typename Functor>
using delegate_result = typename if_c<
	has_result_type<Delegate>,
	typename if_c<
		has_argument_type<Functor>,
		unary_delegate_result<Delegate, Functor>,
		typename if_<
			has_first_argument_type<Functor>() && has_second_argument_type<Functor>(),
			binary_delegate_result<Delegate, Functor>,
			detail::delegate_result<Delegate, Functor>
		>::type
	>::type,
	__delegate_result<Delegate, Functor>
>::type;
#endif

template<typename Delegate, typename Functor>
delegate_result<Delegate, Functor>
delegate(Delegate f, Functor g)
#if __cplusplus >= 201103L
{ return {f, g}; }
#else
{ return delegate_result<Delegate, Functor>(f, g); }
#endif

template<typename Delegate, typename Functor>
unary_delegate_result<Delegate, Functor>
delegate1(Delegate f, Functor g)
#if __cplusplus >= 201103L
{ return {f, g}; }
#else
{ return unary_delegate_result<Delegate, Functor>(f, g); }
#endif

template<typename Delegate, typename Functor>
binary_delegate_result<Delegate, Functor>
delegate2(Delegate f, Functor g)
#if __cplusplus >= 201103L
{ return {f, g}; }
#else
{ return binary_delegate_result<Delegate, Functor>(f, g); }
#endif

}

#endif
