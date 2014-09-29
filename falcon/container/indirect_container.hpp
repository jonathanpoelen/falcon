#ifndef FALCON_CONTAINER_INDIRECT_CONTAINER_HPP
#define FALCON_CONTAINER_INDIRECT_CONTAINER_HPP

#include <falcon/type_traits/rebind.hpp>
#include <falcon/container/container_view.hpp>
#include <falcon/iterator/get_accessor_iterator.hpp>

#if __cplusplus >= 201103L
# include <functional>
#endif
#ifndef FALCON_NOT_BOOST
# include <boost/ref.hpp>
#endif

namespace falcon {

namespace _aux {
  template<class Container, class = typename range_access_subtype<Container>::type>
  struct indirect_iterator_access_traits
  {
    template<class Iterator>
    struct builder
    { typedef falcon::iterator::indirect_iterator<Iterator> type; };
  };

#ifndef FALCON_NOT_BOOST
  template<class Container, class T>
  struct indirect_iterator_access_traits<Container, boost::reference_wrapper<T> >
  {
    template<class Iterator>
    struct builder
    : falcon::iterator::build_get_accessor_iterator<Iterator>
    {};
  };
#endif

#if __cplusplus >= 201103L
  template<class Container, class T>
  struct indirect_iterator_access_traits<Container, std::reference_wrapper<T>>
  {
    template<class Iterator>
    struct builder
    : falcon::iterator::build_get_accessor_iterator<Iterator>
    {};
  };
#endif
}

template<class Container, class AccessTraits = range_access_traits<Container> >
class indirect_iterator_access_traits
{
  typedef typename rebind<AccessTraits, Container>::type access_traits;

public:
  typedef range_access_to_iterator_traits<
    Container
  , access_traits
  , typename _aux::indirect_iterator_access_traits<Container>
  ::template builder<typename access_traits::iterator>::type
  > type;
};

template<class Container, class AccessTraits = range_access_traits<Container> >
struct build_indirect_container
{
	typedef container_view<
   Container
  , typename indirect_iterator_access_traits<Container>::type
	> type;
};

template<class Container>
typename build_indirect_container<Container>::type
indirect_container(Container& cont)
{
	typedef typename build_indirect_container<Container>::type result_type;
	return result_type(cont);
}

template<class Container, class AccessTraits>
typename build_indirect_container<Container, AccessTraits>::type
indirect_container(Container& cont, AccessTraits access)
{
	typedef typename build_indirect_container<Container, AccessTraits>::type result_type;
	return result_type(cont, access);
}

#if __cplusplus >= 201103L
template<class Container, class AccessTraits = range_access_traits<Container> >
using indirect_container_view
= typename build_indirect_container<Container, AccessTraits>::type;
#endif

}

#endif
