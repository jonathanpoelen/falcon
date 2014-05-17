#ifndef FALCON_ITERATOR_OUTPUT_ITERATOR_HPP
#define FALCON_ITERATOR_OUTPUT_ITERATOR_HPP

#include <falcon/c++/reference.hpp>
#include <falcon/c++/pack.hpp>
#include <falcon/utility/move.hpp>
#include <falcon/helper/use_argument_type.hpp>
#include <falcon/type_traits/use_if.hpp>
#if __cplusplus < 201103L
# include <boost/typeof/typeof.hpp>
#endif
#include <iterator>

namespace falcon {
namespace iterator {

template<class Iterator>
class output_iterator_base
: public std::iterator<std::output_iterator_tag, void, void, void, void>
{
  Iterator& downcast()
  { return static_cast<Iterator&>(*this); }

public:
  output_iterator_base()
  {}

  /// Simply returns *this.
  Iterator& operator*()
  { return downcast(); }

  /// Simply returns *this.  (This %iterator does not @a move.)
  Iterator& operator++()
  { return downcast(); }

  /// Simply returns *this.  (This %iterator does not @a move.)
  Iterator& operator++(int)
  { return downcast(); }
};

namespace _aux {
  template<class>
  struct get_argument_type_dispatch2;

  template<class Result, class F, class Arg CPP_OPTIONAL_PACK(Args)>
  struct get_argument_type_dispatch2<Result(F::*)(Arg CPP_USE_OPTIONAL_PACK(Args))>
  { typedef Arg type; };

  template<class Result, class F, class Arg CPP_OPTIONAL_PACK(Args)>
  struct get_argument_type_dispatch2<Result(F::*)(Arg CPP_USE_OPTIONAL_PACK(Args)) const>
  { typedef Arg type; };

  template<class F>
  struct get_argument_type_dispatch
#if __cplusplus >= 201103L
  : get_argument_type_dispatch2<decltype(&F::operator())>
#else
  : get_argument_type_dispatch2<BOOST_TYPEOF(&F::operator())>
#endif
  {};

  template<class F>
  struct get_argument_type
  : use_if<use_argument_type<F>, get_argument_type_dispatch<F> >::type
  {};
}

template<class Functor, class T = typename _aux::get_argument_type<Functor>::type>
struct output_iterator
: output_iterator_base<output_iterator<Functor, T> >
{
    Functor functor_;

public:
  output_iterator()
  : functor_()
  {}

  output_iterator(Functor func)
  : functor_(func)
  {}

  template<class Func>
  output_iterator(const Func& func)
  : functor_(func)
  {}

  output_iterator& operator=(T CPP_RVALUE_OR_REFERENCE x)
  {
    functor_(FALCON_MOVE(x));
    return *this;
  }

  output_iterator& operator=(const T& x)
  {
    functor_(x);
    return *this;
  }
};

template<class F>
output_iterator<F>
make_output_iterator(F func)
{ return output_iterator<F>(FALCON_MOVE(func)); }

}}

#endif
