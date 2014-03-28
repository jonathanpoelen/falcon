#ifndef FALCON_ACCESSOR_RANGE_HPP
#define FALCON_ACCESSOR_RANGE_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include <falcon/c++/conditional_cpp.hpp>

#include <falcon/type_traits/use.hpp>
#include <falcon/type_traits/eval_if.hpp>

#include <falcon/helper/use_iterator.hpp>
#include <falcon/helper/use_const_iterator.hpp>
#include <falcon/helper/use_reverse_iterator.hpp>
#include <falcon/helper/use_const_reverse_iterator.hpp>

#include <falcon/container/range_access.hpp>

#include FALCON_BOOST_OR_STD_TRAITS(is_const)

namespace falcon {
namespace accessors {

template <class T CPP_IF_CPP1X(=void), class Result = use_default>
struct begin_t
{
  typedef T argument_type;
  typedef typename default_or_type<
    eval_if_c<
      FALCON_BOOST_OR_STD_NAMESPACE::is_const<T>
    , use_const_iterator<T>
    , use_iterator<T>
    >
  , Result>::type result_type;

  CPP_CONSTEXPR result_type operator()(argument_type& cont) const
  CPP_NOEXCEPT_OPERATOR2(begin(cont))
  { return begin(cont); }
};

template <class T CPP_IF_CPP1X(=void), class Result = use_default>
struct rbegin_t
{
  typedef T argument_type;
  typedef typename default_or_type<
    eval_if_c<
      FALCON_BOOST_OR_STD_NAMESPACE::is_const<T>
    , use_const_reverse_iterator<T>
    , use_reverse_iterator<T>
    >
  , Result>::type result_type;

  CPP_CONSTEXPR result_type operator()(argument_type& cont) const
  CPP_NOEXCEPT_OPERATOR2(rbegin(cont))
  { return rbegin(cont); }
};

template <class T CPP_IF_CPP1X(=void), class Result = use_default>
struct cbegin_t
{
  typedef T argument_type;
  typedef typename default_or_type<use_const_iterator<T>, Result>::type result_type;

  CPP_CONSTEXPR result_type operator()(argument_type& cont) const
  CPP_NOEXCEPT_OPERATOR2(cbegin(cont))
  { return cbegin(cont); }
};

#if __cplusplus >= 201103L
template <class T CPP_IF_CPP1X(=void), class Result = use_default>
struct crbegin_t
{
  typedef T argument_type;
  typedef typename default_or_type<use_const_reverse_iterator<T>, Result>::type result_type;

  CPP_CONSTEXPR result_type operator()(argument_type& cont) const
  CPP_NOEXCEPT_OPERATOR2(crbegin(cont))
  { return crbegin(cont); }
};
#endif


template <class T CPP_IF_CPP1X(=void), class Result = use_default>
struct end_t
{
  typedef T argument_type;
  typedef typename default_or_type<
    eval_if_c<
      FALCON_BOOST_OR_STD_NAMESPACE::is_const<T>
    , use_const_iterator<T>
    , use_iterator<T>
    >
  , Result>::type result_type;

  CPP_CONSTEXPR result_type operator()(argument_type& cont) const
  CPP_NOEXCEPT_OPERATOR2(end(cont))
  { return end(cont); }
};

template <class T CPP_IF_CPP1X(=void), class Result = use_default>
struct rend_t
{
  typedef T argument_type;
  typedef typename default_or_type<
    eval_if_c<
      FALCON_BOOST_OR_STD_NAMESPACE::is_const<T>
    , use_const_reverse_iterator<T>
    , use_reverse_iterator<T>
    >
  , Result>::type result_type;

  CPP_CONSTEXPR result_type operator()(argument_type& cont) const
  CPP_NOEXCEPT_OPERATOR2(rend(cont))
  { return rend(cont); }
};

template <class T CPP_IF_CPP1X(=void), class Result = use_default>
struct cend_t
{
  typedef T argument_type;
  typedef typename default_or_type<use_const_iterator<T>, Result>::type result_type;

  CPP_CONSTEXPR result_type operator()(argument_type& cont) const
  CPP_NOEXCEPT_OPERATOR2(cend(cont))
  { return cend(cont); }
};

#if __cplusplus >= 201103L
template <class T CPP_IF_CPP1X(=void), class Result = use_default>
struct crend_t
{
  typedef T argument_type;
  typedef typename default_or_type<use_const_reverse_iterator<T>, Result>::type result_type;

  CPP_CONSTEXPR result_type operator()(argument_type& cont) const
  CPP_NOEXCEPT_OPERATOR2(crend(cont))
  { return crend(cont); }
};
#endif


#if __cplusplus >= 201103L
# define MAKE_ACCESS_VOID(name) \
  template<>                    \
  struct name##_t<void>         \
  {                             \
    template<class T>           \
    auto operator()(T& x) const \
    -> decltype(x.name())       \
    { return x.name(); }        \
  }

MAKE_ACCESS_VOID(begin);
MAKE_ACCESS_VOID(cbegin);
MAKE_ACCESS_VOID(rbegin);
MAKE_ACCESS_VOID(crbegin);

MAKE_ACCESS_VOID(end);
MAKE_ACCESS_VOID(cend);
MAKE_ACCESS_VOID(rend);
MAKE_ACCESS_VOID(crend);

# undef MAKE_ACCESS_VOID

CPP_GLOBAL_CONSTEXPR begin_t<> begin;
CPP_GLOBAL_CONSTEXPR cbegin_t<> cbegin;
CPP_GLOBAL_CONSTEXPR rbegin_t<> rbegin;
CPP_GLOBAL_CONSTEXPR crbegin_t<> crbegin;

CPP_GLOBAL_CONSTEXPR end_t<> end;
CPP_GLOBAL_CONSTEXPR cend_t<> cend;
CPP_GLOBAL_CONSTEXPR rend_t<> rend;
CPP_GLOBAL_CONSTEXPR crend_t<> crend;

#endif

}
}

#endif
