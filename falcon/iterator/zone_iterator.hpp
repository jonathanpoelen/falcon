#ifndef FALCON_ITERATOR_ZONE_ITERATOR_HPP
#define FALCON_ITERATOR_ZONE_ITERATOR_HPP

#include <falcon/iterator/iterator_handler.hpp>

namespace falcon {
namespace iterator {

template <class Iterator>
class zone_iterator;

namespace detail
{
  template <class Iterator>
  struct zone_base
  {
    typedef typename iterator_handler_types<
      zone_iterator<Iterator>
    , Iterator
    >::type type;
  };
}

template <class Iterator>
class zone_iterator
: public detail::zone_base<Iterator>::type
{
  friend class iterator_core_access;

  typedef typename zone_iterator::handler_type inherit_type;

public:
  typedef typename inherit_type::iterator_type iterator_type;
  typedef typename inherit_type::difference_type difference_type;

private:
  iterator_type end_;
  difference_type n_;
  difference_type step_;

public:
  zone_iterator(iterator_type x)
  : inherit_type(x)
  {}

  zone_iterator(iterator_type x, difference_type width__, difference_type sub_width)
  : inherit_type(x)
  , end_(x + width__ - sub_width)
  , n_(sub_width - 1)
  , step_(width__ - sub_width + 1)
  {}

  zone_iterator(iterator_type x, iterator_type end,
                difference_type width__, difference_type sub_width)
  : inherit_type(x)
  , end_(end)
  , n_(sub_width - 1)
  , step_(width__ - sub_width + 1)
  {}

  using inherit_type::operator=;

  difference_type real_width() const
  { return step_ + n_; }

  difference_type width() const
  { return n_ + 1; }

protected:
  void increment()
  {
    if (this->base_reference() == end_)
    {
      this->base_reference() = end_ + step_;
      end_ = this->base_reference() + n_;
    }
    else
      ++this->base_reference();
  }

  void decrement()
  {
    if (this->base_reference() == end_ - n_)
    {
      end_ -= step_;
      this->base_reference() = end_;
    }
    else
      --this->base_reference();
  }

  void advance(difference_type n)
  {
    if (n < 0)
      _recoil(-n);
    else
      _advance(n);
  }

  void recoil(difference_type n)
  {
    if (n < 0)
      _advance(-n);
    else
      _recoil(n);
  }

  difference_type difference(const zone_iterator& other) const
  {
    difference_type d = this->base_reference() - other.base_reference();
    if (other.end_ != end_)
      d -= d / (n_ + step_) * (step_-1);
    return d;
  }

private:
  void _advance(difference_type n)
  {
    difference_type d = end_ - this->base_reference();
    if (n > d)
    {
      n -= d + 1;
      difference_type t = n / (n_ + 1) * (step_ + n_) + step_;
      this->base_reference() = end_ + (t + n % (n_ + 1));
      end_ += t + n_;
    }
    else
      this->base_reference() += n;
  }

  void _recoil(difference_type n)
  {
    difference_type d = this->base_reference() - (end_ - n_);
    if (n > d)
    {
      n -= d + 1;
      difference_type t = n / (n_ + 1) * (step_ + n_) + step_ + n_;
      this->base_reference() = end_ - (t + n % (n_ + 1));
      end_ -= t;
    }
    else
      this->base_reference() -= n;
  }
};

template <class Iterator>
zone_iterator<Iterator>
make_zone_iterator(Iterator x,
                   typename zone_iterator<Iterator>::difference_type width,
                   typename zone_iterator<Iterator>::difference_type sub_width)
{ return zone_iterator<Iterator>(x, width, sub_width); }

template <class Iterator>
zone_iterator<Iterator>
make_zone_iterator(Iterator x, Iterator end,
                   typename zone_iterator<Iterator>::difference_type width,
                   typename zone_iterator<Iterator>::difference_type sub_width)
{ return zone_iterator<Iterator>(x, end, width, sub_width); }

}}

#endif
