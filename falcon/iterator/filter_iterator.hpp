#ifndef FALCON_ITERATOR_FILTER_ITERATOR_HPP
#define FALCON_ITERATOR_FILTER_ITERATOR_HPP

#include <falcon/iterator/iterator_handler.hpp>
#include <falcon/iterator/minimal_iterator_category.hpp>

namespace falcon {
namespace iterator {

template<
  class Iterator
, class Predicate
, class Category = std::bidirectional_iterator_tag>
class filter_iterator;

namespace detail
{
  template<class Iterator, class Predicate, class Category>
  struct filter_iterator_base
  {
    typedef typename iterator_handler_types<
      filter_iterator<Iterator, Predicate, Category>
    , Iterator
    , typename minimal_iterator_category_for<Iterator, Category>::type
    >::type type;
  };
}

template<class Iterator, class Predicate, class Category>
class filter_iterator
: public detail::filter_iterator_base<Iterator, Predicate, Category>::type
{
  friend class iterator_core_access;

  typedef typename detail::filter_iterator_base<
    Iterator, Predicate, Category>::type inherit_type;

public:
  typedef Predicate predicate_type;
  typedef typename inherit_type::iterator_type iterator_type;

private:
  predicate_type predicate_;
  iterator_type end_;

public:
  filter_iterator()
  {}

  filter_iterator(iterator_type x)
  : inherit_type(x)
  {
    satisfy_predicate();
  }

  filter_iterator(iterator_type x, iterator_type xend)
  : inherit_type(x)
  , end_(xend)
  {
    satisfy_predicate();
  }

  filter_iterator(iterator_type x, iterator_type xend, Predicate pred)
  : inherit_type(x)
  , end_(xend)
  , predicate_(pred)
  {
    satisfy_predicate();
  }

  filter_iterator(iterator_type x, Predicate pred)
  : inherit_type(x)
  , predicate_(pred)
  {
    satisfy_predicate();
  }

  using inherit_type::operator=;

  predicate_type predicate() const
  { return predicate_; }
  iterator_type end() const
  { return end_; }

private:
  void increment()
  {
    ++(this->base_reference());
    satisfy_predicate();
  }

  void decrement()
  {
    while(!this->predicate_(*--(this->base_reference()))){};
  }

  void satisfy_predicate()
  {
    while (this->base_reference() != this->end_
    && !this->predicate_(*this->base_reference())) {
      ++(this->base_reference());
    }
  }
};

template <class Predicate, class Iterator>
filter_iterator<Iterator,Predicate>
make_filter_iterator(Iterator x, Iterator end, Predicate pred)
{ return filter_iterator<Iterator,Predicate>(x, end, pred); }

template <class Predicate, class Iterator>
filter_iterator<Iterator,Predicate>
make_filter_iterator(Iterator x, Predicate pred)
{ return filter_iterator<Iterator,Predicate>(x, pred); }

template <class Predicate, class Iterator>
filter_iterator<Iterator,Predicate>
make_filter_iterator(Iterator x)
{ return filter_iterator<Iterator,Predicate>(x); }

template <class Predicate, class Iterator>
filter_iterator<Iterator,Predicate>
make_filter_iterator(Iterator x, Iterator end)
{ return filter_iterator<Iterator,Predicate>(x, end); }

}}

#endif
