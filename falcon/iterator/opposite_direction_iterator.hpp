#ifndef FALCON_ITERATOR_OPPOSITE_DIRECTION_ITERATOR_HPP
#define FALCON_ITERATOR_OPPOSITE_DIRECTION_ITERATOR_HPP

#include <falcon/iterator/iterator_handler.hpp>

namespace falcon {
namespace iterator {

template <class Iterator>
class opposite_direction_iterator;

namespace detail {
  template <class Iterator>
  struct opposite_direction_base
  {
    typedef typename iterator_handler_types<
      opposite_direction_iterator<Iterator>
    , Iterator
    >::type type;
  };
}

template <class Iterator>
class opposite_direction_iterator
: public detail::opposite_direction_base<Iterator>::type
{
  friend class iterator_core_access;

  typedef typename detail::opposite_direction_base<Iterator>::type inherit_type;

public:
  typedef typename inherit_type::iterator_type iterator_type;
  typedef typename inherit_type::difference_type difference_type;


public:
  opposite_direction_iterator()
  : inherit_type()
  {}

  opposite_direction_iterator(iterator_type x)
  : inherit_type(x)
  {}

  using inherit_type::operator=;

protected:
  void increment()
  { --this->base_reference(); }

  void decrement()
  { ++this->base_reference(); }

  difference_type difference(const opposite_direction_iterator& x) const
  { return x.inherit_type::difference(*this); }

  void advance(difference_type n)
  { this->base_reference() -= n; }

  void recoil(difference_type n)
  { this->base_reference() += n; }
};

template <class Iterator>
opposite_direction_iterator<Iterator>
make_opposite_direction_iterator(Iterator x)
{ return opposite_direction_iterator<Iterator>(x); }

}
}

#endif
