#ifndef FALCON_ITERATOR_NEXTER_ITERATOR_HPP
#define FALCON_ITERATOR_NEXTER_ITERATOR_HPP

#include <falcon/iterator/iterator_handler.hpp>
#include <falcon/iterator/minimal_iterator_category.hpp>

namespace falcon {
namespace iterator {

template<class Iterator, class Nexter, bool ContentsDistance = false>
class nexter_iterator;

namespace detail
{
  template<class Iterator, class Nexter, bool ContentsDistance>
  struct nexter_iterator_base
  {
    typedef typename iterator_handler_types<
      nexter_iterator<Iterator, Nexter, ContentsDistance>
    , Iterator
    >::type type;
  };
}

template<class Iterator, class Nexter, bool ContentsDistance>
class nexter_iterator
: public detail::nexter_iterator_base<Iterator, Nexter, ContentsDistance>::type
{
  friend class iterator_core_access;

  typedef typename detail::nexter_iterator_base<
    Iterator, Nexter, ContentsDistance>::type inherit_iterator;

public:
  typedef Nexter nexter_type;
  typedef typename inherit_iterator::iterator_type iterator_type;
  typedef typename inherit_iterator::difference_type difference_type;

private:
  nexter_type nexter_;

public:
  nexter_iterator(nexter_type fn)
  : nexter_(fn)
  {}

  nexter_iterator(iterator_type x)
  : inherit_iterator(x)
  {}

  nexter_iterator(iterator_type x, nexter_type fn)
  : inherit_iterator(x)
  , nexter_(fn)
  {}

  using inherit_iterator::operator=;

  nexter_type nexter() const
  { return nexter_; }

private:
  void increment()
  { nexter_(this->base_reference()); }

  void decrement()
  { nexter_(this->base_reference(), -1); }

  void advance(difference_type n)
  { nexter_(this->base_reference(), n); }

  difference_type difference(const nexter_iterator& other, true_type) const
  { return nexter_(this->base_reference(), other.base_reference()); }

  difference_type difference(const nexter_iterator& other, false_type) const
  { return inherit_iterator::difference(other); }

  difference_type difference(const nexter_iterator& other) const
  { return difference(other, integral_constant<bool, ContentsDistance>()); }
};

template<class Iterator, class Nexter>
nexter_iterator<Iterator, Nexter>
make_nexter_iterator(Iterator x, Nexter fn)
{ return nexter_iterator<Iterator, Nexter>(x, fn); }

}}

#endif
