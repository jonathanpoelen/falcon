#ifndef FALCON_FUNCTIONAL_COMPOSE_HPP
#define FALCON_FUNCTIONAL_COMPOSE_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/reference.hpp>
#include <falcon/utility/move.hpp>
#if __cplusplus >= 201103L
# include <falcon/arg/arg.hpp>
# include <falcon/helper/has_argument_type.hpp>
# include <falcon/helper/has_result_type.hpp>
# include <falcon/tuple/detail/is_tuple.hpp>
# include <falcon/tuple/tuple_compose.hpp>
# include <tuple>
#endif

#include <functional>

namespace falcon {

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
#if __cplusplus < 201103L
template <class Operation1, class Operation2>
struct unary_compose
: public std::unary_function<
	typename Operation2::argument_type,
	typename Operation1::result_type
>
{
protected:
	Operation1 _M_fn1;
	Operation2 _M_fn2;

public:
	unary_compose(const Operation1& x, const Operation2& y)
	: _M_fn1(x)
	, _M_fn2(y)
	{}

	unary_compose()
	: _M_fn1()
	, _M_fn2()
	{}

	typename Operation1::result_type
	operator()(typename Operation2::argument_type& x) const
	{ return _M_fn1(_M_fn2(x)); }
};

#else

struct __compose_empty_base {};


template <class WrapArgument, class WrapResult>
struct __unary_compose_check_type
{
  static const bool value = (
    has_argument_type<
      typename std::remove_reference<WrapArgument>::type
    >::value
    && has_result_type<
      typename std::remove_reference<WrapResult>::type
    >::value
  );
};

template <class Operation1, class Operation2>
struct __unary_compose_base
: public std::unary_function<
  typename Operation2::argument_type,
  typename Operation1::result_type
>
{};

template <typename Operation1, typename Operation2>
class unary_compose
: public std::conditional<
  __unary_compose_check_type<Operation2, Operation1>::value,
  __unary_compose_base<Operation2, Operation1>,
  __compose_empty_base
>::type
{
  Operation1 fn1;
  Operation2 fn2;

public:
  constexpr unary_compose() = default;
  constexpr unary_compose(const unary_compose&) = default;
  constexpr unary_compose(unary_compose&&) = default;
  unary_compose& operator=(const unary_compose&) = default;
  unary_compose& operator=(unary_compose&&) = default;

  constexpr unary_compose(Operation1&& x)
  : fn1(std::forward<Operation1>(x))
  , fn2()
  {}

	template<typename OperationT, typename OperationU>
	constexpr unary_compose(OperationT&& x, OperationU&& y)
	: fn1(std::forward<OperationT>(x))
	, fn2(std::forward<OperationU>(y))
	{}

	template<typename T>
	auto operator()(T&& x) const
	-> decltype(this->fn1(this->fn2(std::forward<T>(x))))
  { return fn1(fn2(std::forward<T>(x))); }

};

#endif

template <class Operation1, class Operation2>
unary_compose<Operation1, Operation2>
compose1(Operation1 CPP_RVALUE_OR_CONST_REFERENCE fn1,
         Operation2 CPP_RVALUE_OR_CONST_REFERENCE fn2)
{
	return unary_compose<Operation1,Operation2>(
		FALCON_FORWARD(Operation1, fn1),
		FALCON_FORWARD(Operation2, fn2)
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
#if __cplusplus < 201103L
template <class Operation1, class Operation2, class Operation3 = Operation2>
struct binary_compose
: public std::unary_function<
	typename Operation2::argument_type,
	typename Operation1::result_type
> {
protected:
	Operation1 _M_fn1;
	Operation2 _M_fn2;
	Operation3 _M_fn3;

public:
	binary_compose(const Operation1& x, const Operation2& y,
				   const Operation3& z)
	: _M_fn1(x)
	, _M_fn2(y)
	, _M_fn3(z)
	{}

	binary_compose()
	: _M_fn1()
	, _M_fn2()
	, _M_fn3()
	{}

	typename Operation1::result_type
	operator()(typename Operation2::argument_type& x) const
	{ return _M_fn1(_M_fn2(x), _M_fn3(x)); }
};

#else

template <class Operation1, class Operation2, class Operation3 = Operation2>
class binary_compose
: public std::conditional<
  __unary_compose_check_type<Operation2, Operation1>::value,
  __unary_compose_base<Operation2, Operation1>,
  __compose_empty_base
>::type
{
  Operation1 fn1;
  Operation2 fn2;
  Operation3 fn3;

public:
  constexpr binary_compose() = default;
  constexpr binary_compose(const binary_compose&) = default;
  constexpr binary_compose(binary_compose&&) = default;
  binary_compose& operator=(const binary_compose&) = default;
  binary_compose& operator=(binary_compose&&) = default;

  template<typename OperationT, typename OperationU, typename OperationZ>
  constexpr binary_compose(OperationT&& x, OperationU&& y, OperationZ&& z)
	: fn1(std::forward<OperationT>(x))
	, fn2(std::forward<OperationU>(y))
	, fn3(std::forward<OperationZ>(z))
  {}

  template<typename OperationResult>
  constexpr binary_compose(OperationResult&& x)
  : fn1(std::forward<OperationResult>(x))
  , fn2()
  , fn3()
  {}

  template<typename T>
  auto operator()(T&& x) const
  -> decltype(this->fn1(this->fn2(std::forward<T>(x)), this->fn3(std::forward<T>(x))))
  { return fn1(fn2(std::forward<T>(x)), fn3(std::forward<T>(x))); }
};
//@}

#endif

template <class Operation1, class Operation2, class Operation3>

binary_compose<Operation1, Operation2, Operation3>
compose2(Operation1 CPP_RVALUE_OR_CONST_REFERENCE fn1,
         Operation2 CPP_RVALUE_OR_CONST_REFERENCE fn2,
         Operation3 CPP_RVALUE_OR_CONST_REFERENCE fn3)
{
	return binary_compose<Operation1,Operation2,Operation3>(
		FALCON_FORWARD(Operation1, fn1),
		FALCON_FORWARD(Operation2, fn2),
		FALCON_FORWARD(Operation3, fn3)
	);
}

template <class Operation1, class Operation2>
binary_compose<Operation1, Operation2, Operation2>
compose2(Operation1 CPP_RVALUE_OR_CONST_REFERENCE fn1,
         Operation2 CPP_RVALUE_OR_CONST_REFERENCE fn2)
{
	return binary_compose<Operation1, Operation2, Operation2>(
		FALCON_FORWARD(Operation1, fn1),
		FALCON_FORWARD(Operation2, fn2)
	);
}


#if __cplusplus >= 201103L

/** The @c mulary_compose is constructed from tuple functors, @c f, @c t.
 * Its @c operator() returns @c f(std::get<0>(t)(x), ...).
 * The function  @c compose takes f, t and constructs the @c mulary_compose
 * instance for you.  For example, if @c f returns an int, then
 * \code
 * int answer = (composex(f,g1,g2,g3))(x);
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
template<class Operation, class Operations>
class mulary_compose
: public std::conditional<
  __unary_compose_check_type<
    typename std::tuple_element<0, Operations>::type,
    Operation
  >::value,
  __unary_compose_base<typename std::tuple_element<0, Operations>::type, Operation>,
  __compose_empty_base
>
{
  Operation fn;
  Operations fns;

public:
  constexpr mulary_compose() = default;
  constexpr mulary_compose(const mulary_compose&) = default;
  constexpr mulary_compose(mulary_compose&&) = default;
  mulary_compose& operator=(const mulary_compose&) = default;
  mulary_compose& operator=(mulary_compose&&) = default;

  template<typename Op, typename Ops>
  constexpr mulary_compose(Op&& x, Ops&& y)
  : fn(std::forward<Op>(x))
  , fns(std::forward<Ops>(y))
  {}

  template<typename Op>
  constexpr mulary_compose(Op&& x)
  : fn(std::forward<Op>(x))
  , fns()
  {}

  constexpr mulary_compose(Operations&& y)
  : fn()
  , fns(std::forward<Operations>(y))
  {}

  template<typename T>
  constexpr auto operator()(T&& x) const
  -> decltype(tuple_compose<const Operation &>(
      parameter_index<0>(),
      fn,
      fns,
      std::forward_as_tuple(x)
    ))
  {
    return tuple_compose<const Operation &>(
      parameter_index<0>(),
      fn,
      fns,
      std::forward_as_tuple(x)
    );
  }
};

template<typename Operation, typename Operations>
constexpr mulary_compose<Operation,
  typename std::conditional<
    is_tuple_impl<Operations>::value,
    Operations,
    std::tuple<Operation>
  >::type
>
composex(Operation&& fn1, Operations&& fns)
{
  return {
    std::forward<Operation>(fn1),
    std::forward<Operations>(fns)
  };
}

template<typename Operation, typename OperationT, typename... Operations>
constexpr mulary_compose<Operation, std::tuple<OperationT, Operations...>>
composex(Operation&& fn1, OperationT && fn2, Operations&&... fns)
{
  return {
    std::forward<Operation>(fn1),
    std::tuple<OperationT, Operations...>(
      std::forward<OperationT>(fn2),
      std::forward<Operations>(fns)...
    )
  };
}
//@}

/** The @c function_compose is constructed from tuple functors, @c f, @c t.
 * Its @c operator() returns @c f(std::get<0>(t)(x), ...).
 * The function  @c compose takes f, t and constructs the @c function_compose
 * instance for you.  For example, if @c f returns an int, then
 * \code
 * int answer = (composef(f,g1,g2,g3))(x,y);
 * \endcode
 * is equivalent to
 * \code
 * int temp1 = g1(x,y);
 * int temp2 = g2(x,y);
 * int temp3 = g3(x,y);
 * int answer = f(temp1,temp2,temp3);
 * \endcode
 * @{
 */
template<class Operation, class Operations>
class function_compose
{
	Operation fn;
	Operations fns;

public:
  constexpr function_compose() = default;
  constexpr function_compose(const function_compose&) = default;
  constexpr function_compose(function_compose&&) = default;
  function_compose& operator=(const function_compose&) = default;
  function_compose& operator=(function_compose&&) = default;

  template<typename Op, typename Ops>
	constexpr function_compose(Op&& x, Ops&& y)
	: fn(std::forward<Op>(x))
	, fns(std::forward<Ops>(y))
	{}

  template<typename Op>
  constexpr function_compose(Op&& x)
  : fn(std::forward<Op>(x))
  , fns()
  {}

	constexpr function_compose(Operations&& y)
	: fn()
  , fns(std::forward<Operations>(y))
	{}

  template<typename... Args>
  constexpr auto operator()(Args&&... args) const
  -> decltype(tuple_compose<const Operation &>(
      parameter_index<0>(),
      fn,
      fns,
      std::forward_as_tuple(std::forward<Args>(args)...)
    ))
  {
    return tuple_compose<const Operation &>(
      parameter_index<0>(),
      fn,
      fns,
      std::forward_as_tuple(std::forward<Args>(args)...)
    );
  }
};

template<typename Operation, typename Operations>
constexpr function_compose<Operation,
  typename std::conditional<
    is_tuple_impl<Operations>::value,
    Operations,
    std::tuple<Operation>
  >::type
>
composex(Operation&& fn1, Operations&& fns)
{
  return {
    std::forward<Operation>(fn1),
    std::forward<Operations>(fns)
  };
}

template<typename Operation, typename OperationT, typename... Operations>
constexpr function_compose<Operation, std::tuple<OperationT, Operations...>>
composex(Operation&& fn1, OperationT && fn2, Operations&&... fns)
{
	return {
		std::forward<Operation>(fn1),
    std::tuple<OperationT, Operations...>(
      std::forward<OperationT>(fn2),
      std::forward<Operations>(fns)...
    )
	};
}
//@}

#endif
// @}

}

#endif
