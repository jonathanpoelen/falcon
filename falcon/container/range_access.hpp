#ifndef FALCON_CONTAINER_RANGE_ACCESS_HPP
#define FALCON_CONTAINER_RANGE_ACCESS_HPP

#include <falcon/iterator/range.hpp>

#include <type_traits>


namespace falcon {

template<class Container>
struct range_access_iterator
{
  typedef decltype(begin(std::declval<Container&>())) type;
};

template<class Container>
struct range_access_reverse_iterator
{
  typedef decltype(rbegin(std::declval<Container&>())) type;
};


template<class Container>
struct range_access_subtype
{
  typedef typename std::iterator_traits<
    typename range_access_iterator<Container>::type
  >::value_type type;
};

}

#endif
