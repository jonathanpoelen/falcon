#ifndef FALCON_ITERATOR_NORMAL_ITERATOR_HPP
#define FALCON_ITERATOR_NORMAL_ITERATOR_HPP

#include <falcon/iterator/iterator_handler.hpp>

namespace falcon {
namespace iterator {

template<
  class Iterator
, class T = use_default
, class Category = use_default
, class Reference = use_default
, class Distance = use_default
, class Pointer = use_default
>
class normal_iterator;

namespace detail {
  template<
    class Iterator
  , class T
  , class Category
  , class Reference
  , class Distance
  , class Pointer
  >
  struct normal_iterator_base
  {
    typedef typename iterator_handler_types<
      normal_iterator<Iterator, T, Category, Reference, Distance, Pointer>
    , Iterator
    , Category
    , T
    , Distance
    , Pointer
    , Reference
    >::type type;
  };
}

template<
  class Iterator
, class T
, class Category
, class Reference
, class Distance
, class Pointer
>
class normal_iterator
: public detail::normal_iterator_base<
  Iterator, T, Category, Reference, Distance, Pointer>::type
{
  friend class iterator_core_access;

  typedef typename normal_iterator::handler_type inherit_type;

public:
  typedef typename inherit_type::iterator_type iterator_type;


  normal_iterator()
  : inherit_type()
  {}

  normal_iterator(iterator_type x)
  : inherit_type(x)
  {}

  using inherit_type::operator=;
};

template<class Iterator>
normal_iterator<Iterator>
make_normal_iterator(Iterator x)
{ return normal_iterator<Iterator>(x); }

}}

#endif
