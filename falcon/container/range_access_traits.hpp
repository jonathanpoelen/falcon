#ifndef FALCON_CONTAINER_RANGE_ACCESS_TRAITS_HPP
#define FALCON_CONTAINER_RANGE_ACCESS_TRAITS_HPP

#include <falcon/container/range_access.hpp>

namespace falcon {

template<typename Container>
struct range_access_traits
{
	typedef Container container_type;
  typedef typename range_access_iterator<Container>::type iterator;

	template<class OtherContainer>
	struct rebind
	{ typedef range_access_traits<OtherContainer> other; };

  static iterator begin(container_type& cont)
  {
    using falcon::begin;
    return begin(cont);
  }

  static iterator end(container_type& cont)
  {
    using falcon::end;
    return end(cont);
  }
};

template<typename Container>
struct reverse_range_access_traits
{
	typedef Container container_type;
  typedef typename range_access_reverse_iterator<Container>::type iterator;

  template<class OtherContainer>
  struct rebind
  { typedef reverse_range_access_traits<OtherContainer> other; };

  static iterator begin(container_type& cont)
  {
    using falcon::rbegin;
    return rbegin(cont);
  }

  static iterator end(container_type& cont)
  {
    using falcon::rend;
    return rend(cont);
  }
};


template<class Container, class AccessIteratorTraits, class ToIterator>
struct range_access_to_iterator_traits
{
  typedef typename AccessIteratorTraits::container_type container_type;
  typedef ToIterator iterator;

  template<class OtherContainer>
  struct rebind
  {
    typedef range_access_to_iterator_traits<
      OtherContainer
    , typename AccessIteratorTraits::template rebind<OtherContainer>::other
    , ToIterator
    > other;
  };

  ToIterator begin(container_type& cont) const
  { return ToIterator(_access.begin(cont)); }

  ToIterator end(container_type& cont) const
  { return ToIterator(_access.end(cont)); }

private:
  AccessIteratorTraits _access;
};

}

#endif
