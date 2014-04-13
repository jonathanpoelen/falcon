#ifndef FALCON_ACCESSOR_RANGE_HPP
#define FALCON_ACCESSOR_RANGE_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/boost_or_std.hpp>

#include <falcon/type_traits/eval_if.hpp>
#include <falcon/type_traits/default_or_type.hpp>

#include <falcon/helper/use_iterator.hpp>
#include <falcon/helper/use_const_iterator.hpp>
#include <falcon/helper/use_reverse_iterator.hpp>
#include <falcon/helper/use_const_reverse_iterator.hpp>

#include <falcon/container/range_access.hpp>

#include FALCON_BOOST_OR_STD_TRAITS(is_const)

namespace falcon {
namespace accessors {

template <class T = void, class Result = void>
struct begin
{
  typedef T argument_type;
  typedef typename default_or_type<
    eval_if_c<
      FALCON_BOOST_OR_STD_NAMESPACE::is_const<T>
    , use_const_iterator<T>
    , use_iterator<T>
    >
  , Result
  , void
  >::type result_type;

  result_type operator()(argument_type& cont) const
  CPP_NOEXCEPT_OPERATOR2(begin(cont))
  {
    using ::falcon::begin;
    return begin(cont);
  }
};

template <class T = void, class Result = void>
struct rbegin
{
  typedef T argument_type;
  typedef typename default_or_type<
    eval_if_c<
      FALCON_BOOST_OR_STD_NAMESPACE::is_const<T>
    , use_const_reverse_iterator<T>
    , use_reverse_iterator<T>
    >
  , Result
  , void
  >::type result_type;

  result_type operator()(argument_type& cont) const
  CPP_NOEXCEPT_OPERATOR2(rbegin(cont))
  {
    using ::falcon::rbegin;
    return rbegin(cont);
  }
};

template <class T = void, class Result = void>
struct cbegin
{
  typedef T argument_type;
  typedef typename default_or_type<use_const_iterator<T>, Result, void>::type result_type;

  result_type operator()(argument_type& cont) const
  CPP_NOEXCEPT_OPERATOR2(cbegin(cont))
  {
    using ::falcon::cbegin;
    return cbegin(cont);
  }
};

template <class T = void, class Result = void>
struct crbegin
{
  typedef T argument_type;
  typedef typename default_or_type<use_const_reverse_iterator<T>, Result, void>::type result_type;

  result_type operator()(argument_type& cont) const
  CPP_NOEXCEPT_OPERATOR2(crbegin(cont))
  {
    using ::falcon::crbegin;
    return crbegin(cont);
  }
};


template <class T = void, class Result = void>
struct end
{
  typedef T argument_type;
  typedef typename default_or_type<
    eval_if_c<
      FALCON_BOOST_OR_STD_NAMESPACE::is_const<T>
    , use_const_iterator<T>
    , use_iterator<T>
    >
  , Result
  , void
  >::type result_type;

  result_type operator()(argument_type& cont) const
  CPP_NOEXCEPT_OPERATOR2(end(cont))
  {
    using ::falcon::end;
    return end(cont);
  }
};

template <class T = void, class Result = void>
struct rend
{
  typedef T argument_type;
  typedef typename default_or_type<
    eval_if_c<
      FALCON_BOOST_OR_STD_NAMESPACE::is_const<T>
    , use_const_reverse_iterator<T>
    , use_reverse_iterator<T>
    >
  , Result
  , void
  >::type result_type;

  result_type operator()(argument_type& cont) const
  CPP_NOEXCEPT_OPERATOR2(rend(cont))
  {
    using ::falcon::rend;
    return rend(cont);
  }
};

template <class T = void, class Result = void>
struct cend
{
  typedef T argument_type;
  typedef typename default_or_type<use_const_iterator<T>, Result, void>::type result_type;

  result_type operator()(argument_type& cont) const
  CPP_NOEXCEPT_OPERATOR2(cend(cont))
  {
    using ::falcon::cend;
    return cend(cont);
  }
};

template <class T = void, class Result = void>
struct crend
{
  typedef T argument_type;
  typedef typename default_or_type<use_const_reverse_iterator<T>, Result, void>::type result_type;

  result_type operator()(argument_type& cont) const
  CPP_NOEXCEPT_OPERATOR2(crend(cont))
  {
    using ::falcon::crend;
    return crend(cont);
  }
};


#if __cplusplus >= 201103L
# define MAKE_ACCESS_VOID(name) \
  template<>                    \
  struct name<void>             \
  {                             \
    template<class T>           \
    auto operator()(T& x) const \
    -> decltype(x.name())       \
    { return x.name(); }        \
  }
#else
# define MAKE_ACCESS_VOID(name)   \
  template<>                      \
  struct name<void>               \
  {                               \
    template<class T>             \
    typename name<T>::result_type \
    operator()(T& x) const        \
    { return name<T>()(); }       \
  }
#endif

MAKE_ACCESS_VOID(begin);
MAKE_ACCESS_VOID(cbegin);
MAKE_ACCESS_VOID(rbegin);
MAKE_ACCESS_VOID(crbegin);

MAKE_ACCESS_VOID(end);
MAKE_ACCESS_VOID(cend);
MAKE_ACCESS_VOID(rend);
MAKE_ACCESS_VOID(crend);

# undef MAKE_ACCESS_VOID

CPP_GLOBAL_CONSTEXPR begin<> begin_f;
CPP_GLOBAL_CONSTEXPR cbegin<> cbegin_f;
CPP_GLOBAL_CONSTEXPR rbegin<> rbegin_f;
CPP_GLOBAL_CONSTEXPR crbegin<> crbegin_f;

CPP_GLOBAL_CONSTEXPR end<> end_f;
CPP_GLOBAL_CONSTEXPR cend<> cend_f;
CPP_GLOBAL_CONSTEXPR rend<> rend_f;
CPP_GLOBAL_CONSTEXPR crend<> crend_f;

}
}

#endif
