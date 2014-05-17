#ifndef FALCON_ITERATOR_PSEUDO_ITERATOR_HPP
#define FALCON_ITERATOR_PSEUDO_ITERATOR_HPP

#include <falcon/preprocessor/getter.hpp>
#include <falcon/c++/reference.hpp>
#include <falcon/utility/move.hpp>
#include <iterator>

namespace falcon {

namespace iterator {

template<class T>
struct pseudo_iterator
{
  typedef T value_type;
  typedef value_type* pointer;
  typedef value_type& reference;
  typedef std::random_access_iterator_tag iterator_category;
  typedef std::ptrdiff_t difference_type;


  pseudo_iterator()
  {}

  pseudo_iterator(const value_type& value)
  : value_(value)
  {}

  pseudo_iterator& operator=(const value_type& value)
  {
    value_ = value;
    return *this;
  }

#if __cplusplus >= 201103L
  pseudo_iterator(value_type&& value)
  : value_(std::move(value))
  {}

  pseudo_iterator& operator=(value_type&& value)
  {
    value_ = std::move(value);
    return *this;
  }
#endif

  FALCON_MEMBER_GETTER(value_type, operator*, value_)
  FALCON_MEMBER_GETTER(pointer, operator->, &value_)

  pseudo_iterator& operator++()
  { return *this; }
  pseudo_iterator& operator++(int)
  { return *this; }
  pseudo_iterator& operator--()
  { return *this; }
  pseudo_iterator& operator--(int)
  { return *this; }
  template<class I>
  pseudo_iterator& operator+=(const I&)
  { return *this; }
  template<class I>
  pseudo_iterator& operator-=(const I&)
  { return *this; }

  bool operator==(const pseudo_iterator &) const
  { return false; }

  bool operator!=(const pseudo_iterator &) const
  { return true; }

  difference_type operator-(const pseudo_iterator &) const
  { return 0; }

private:
  value_type value_;
};

template <class T>
pseudo_iterator<T>
make_pseudo_iterator(T CPP_RVALUE_OR_CONST_REFERENCE value) {
  return pseudo_iterator<T>(FALCON_FORWARD(T, value));
}

}

}

#endif
