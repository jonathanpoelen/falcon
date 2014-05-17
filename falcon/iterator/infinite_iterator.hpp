#ifndef FALCON_ITERATOR_INFINITE_ITERATOR_HPP
#define FALCON_ITERATOR_INFINITE_ITERATOR_HPP

#include <falcon/infinite.hpp>
#include <falcon/container/range_access.hpp>
#include <falcon/container/range_access_traits.hpp>
#include <falcon/iterator/iterator_handler.hpp>

namespace falcon {
namespace iterator {

template <class Iterator,
  class Category = typename std::iterator_traits<Iterator>::iterator_category
> class infinite_iterator;

namespace detail {

  template <class Iterator, class Category>
  struct infinite_iterator_base
  {
    typedef typename iterator_handler_types<
      infinite_iterator<Iterator, Category>
    , Iterator
    , Category
    >::type type;
  };

}

template <class Iterator, class Category>
struct infinite_iterator
: detail::infinite_iterator_base<Iterator, Category>::type
{
  friend class iterator_core_access;

  typedef typename detail::infinite_iterator_base<Iterator, Category>::type inherit_type;

public:
  typedef typename inherit_type::iterator_type iterator_type;
  typedef typename inherit_type::difference_type difference_type;
  typedef typename inherit_type::iterator_category iterator_category;

private:
  iterator_type first_;
  iterator_type last_;

public:
  infinite_iterator()
  {}

  infinite_iterator(iterator_type begin, iterator_type end)
  : inherit_type(begin)
  , first_(begin)
  , last_(end)
  {}

  infinite_iterator(iterator_type begin, iterator_type end, iterator_type it)
  : inherit_type(it)
  , first_(begin)
  , last_(end)
  {}

  template <class Container>
  infinite_iterator(Container& container)
  : inherit_type(range_access_traits<Container>::begin(container))
  , first_(this->base_reference())
  , last_(range_access_traits<Container>::end(container))
  {}

  template <class Container>
  infinite_iterator(Container& container, iterator_type it)
  : inherit_type(range_access_traits<Container>::begin(container))
  , first_(it)
  , last_(range_access_traits<Container>::end(container))
  {}

  using inherit_type::operator=;

private:
  void increment()
  {
    if (++this->base_reference() == last_) {
      this->base_reference() = first_;
    }
  }

  void decrement()
  {
    if (this->base_reference() == first_) {
      this->base_reference() = last_;
    }
    --this->base_reference();
  }

  void difference(infinite_iterator);

  void advance(difference_type n)
  {
    if (n < 0)
      recoil(-n);
    difference_type diff = last_ - this->base_reference();
    if (diff < n)
      this->base_reference() = first_ + (n - diff) % (last_ - first_);
    else
      this->base_reference() += n;
  }

  void recoil(difference_type n)
  {
    if (n < 0)
      advance(-n);
    difference_type diff = this->base_reference() - first_;
    if (diff < n)
      this->base_reference() = last_ - (n - diff) % (last_ - first_);
    else
      this->base_reference() -= n;
  }

  bool equal(const infinite_iterator&) const
  { return false; }

  bool less(const infinite_iterator&) const
  { return true; }
};

template <class Container>
infinite_iterator<typename range_access_iterator<Container>::type>
make_infinite_iterator(Container& c)
{ return infinite_iterator<typename range_access_iterator<Container>::type>(c); }

template <class Container, class Iterator>
infinite_iterator<Iterator>
make_infinite_iterator(Container& c, Iterator it)
{ return infinite_iterator<Iterator>(c, it); }

template <class Iterator>
infinite_iterator<Iterator>
make_infinite_iterator(Iterator begin, Iterator end)
{ return infinite_iterator<Iterator>(begin, end); }

template <class Iterator>
infinite_iterator<Iterator>
make_infinite_iterator(Iterator begin, Iterator end, Iterator it)
{ return infinite_iterator<Iterator>(begin, end, it); }

}}

#endif
