#ifndef FALCON_ITERATOR_COUNTING_ITERATOR_HPP
#define FALCON_ITERATOR_COUNTING_ITERATOR_HPP

#include <falcon/iterator/iterator_handler.hpp>
#if __cplusplus >= 201103L
# include <type_traits>
#else
# include <boost/type_traits/remove_pointer.hpp>
#endif

namespace falcon {
namespace iterator {

struct count_comparison_tag {};
struct count_and_iterator_comparison_tag {};

template <
  class Iterator
, class ComparisonTag = count_comparison_tag>
class counting_iterator;

namespace detail {

  template <class Iterator, class ComparisonTag>
  struct counting_iterator_base
  {
    typedef typename iterator_handler_types<
      counting_iterator<Iterator, ComparisonTag>
    , Iterator
    >::type type;
  };

}

template <class Iterator, class ComparisonTag>
class counting_iterator
: public detail::counting_iterator_base<Iterator, ComparisonTag>::type
{
  friend class iterator_core_access;

  typedef typename detail::counting_iterator_base<
    Iterator, ComparisonTag>::type inherit_type;

public:
  typedef typename inherit_type::iterator_type iterator_type;
  typedef typename inherit_type::difference_type difference_type;

private:
  int count_;

public:
  counting_iterator(int count__ = 0)
  : count_(count__)
  {}

  counting_iterator(iterator_type x, int count__ = 0)
  : inherit_type(x)
  , count_(count__)
  {}

  counting_iterator(int count__, iterator_type x)
  : inherit_type(x)
  , count_(count__)
  {}

  using inherit_type::operator=;

  int count() const
  { return count_; }

private:
  void increment()
  {
    inherit_type::increment();
    ++count_;
  }

  void decrement()
  {
    inherit_type::decrement();
    --count_;
  }

  difference_type _dispath_difference(const counting_iterator& other,
                                      count_comparison_tag) const
  { return other.count_ - count_; }

  difference_type _dispath_difference(const counting_iterator& other,
                                      count_and_iterator_comparison_tag) const
  { return std::min(other.count_ - count_, inherit_type::difference(other)); }

  difference_type difference(const counting_iterator& other) const
  { return _dispath_difference(other, ComparisonTag()); }

  bool _dispath_equal(const counting_iterator&, count_comparison_tag) const
  { return false; }

  bool _dispath_equal(const counting_iterator& other,
                      count_and_iterator_comparison_tag) const
  { return inherit_type::equal(other); }

  bool equal(const counting_iterator& other) const
  { return count_ == other.count_ || _dispath_equal(other, ComparisonTag()); }

  bool _dispath_less(const counting_iterator&, count_comparison_tag) const
  { return true; }

  bool _dispath_less(const counting_iterator& other, count_and_iterator_comparison_tag) const
  { return inherit_type::less(other); }

  bool less(const counting_iterator& other) const
  { return count_ < other.count_ && _dispath_less(other, ComparisonTag()); }
};


template <class Iterator>
counting_iterator<Iterator>
make_counting_iterator(int count, Iterator x)
{ return counting_iterator<Iterator>(x, count); }

template <class Iterator>
counting_iterator<Iterator>
make_counting_iterator(Iterator x, int count = 0)
{ return counting_iterator<Iterator>(x, count); }

template <class Iterator, class ComparisonTag>
counting_iterator<Iterator>
make_counting_iterator(int count, Iterator x, ComparisonTag)
{ return counting_iterator<Iterator, ComparisonTag>(x, count); }

template <class Iterator, class ComparisonTag>
counting_iterator<Iterator>
make_counting_iterator(Iterator x, int count, ComparisonTag)
{ return counting_iterator<Iterator, ComparisonTag>(x, count); }

template <class Iterator>
counting_iterator<Iterator, count_comparison_tag>
make_counting_iterator(Iterator x, count_comparison_tag)
{ return counting_iterator<Iterator, count_comparison_tag>(x); }

template <class Iterator>
counting_iterator<Iterator, count_and_iterator_comparison_tag>
make_counting_iterator(Iterator x, count_and_iterator_comparison_tag)
{ return counting_iterator<Iterator, count_and_iterator_comparison_tag>(x); }

}}

#endif
