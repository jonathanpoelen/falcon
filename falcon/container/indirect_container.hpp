#ifndef FALCON_CONTAINER_INDIRECT_CONTAINER_HPP
#define FALCON_CONTAINER_INDIRECT_CONTAINER_HPP

#include <falcon/type_traits/rebind.hpp>
#include <falcon/container/container_view.hpp>
#include <falcon/container/range_access.hpp>
#include <falcon/iterator/get_accessor_iterator.hpp>


namespace falcon {

namespace _aux {
  template<class Cont, class = typename range_access_subtype<Cont>::type>
  struct indirect_iterator_access_traits
  {
    template<class Iterator>
    using iterator = falcon::iterator::get_accessor_iterator<Iterator>;
  };

  template<class Cont, class T>
  struct indirect_iterator_access_traits<Cont, T*>
  {
    template<class Iterator>
    using iterator = falcon::iterator::indirect_iterator<Iterator>;
  };
}

template<class Cont, class AccessTraits = range_access_traits>
using indirect_iterator_access_traits = iterator_range_access_traits<
  typename _aux::indirect_iterator_access_traits<Cont>
::template iterator<range_access_to_iterator<AccessTraits, Cont>>
, AccessTraits
>;

template<class Cont, class AccessTraits = range_access_traits>
using indirect_container_view = container_view<
  Cont, indirect_iterator_access_traits<Cont, AccessTraits>
>;

/**
 * container_view with a indirect_iterator
 *
 * @see container_view
 * @see indirect_iterator
 */
template<class Cont>
indirect_container_view<Cont>
indirect_container(Cont& cont)
{ return indirect_container_view<Cont>(cont); }

/**
 * reverse_container_view with a indirect_iterator
 *
 * @see container_view
 * @see indirect_iterator
 */
template<class Cont>
indirect_container_view<Cont, reverse_range_access_traits>
indirect_reverse_container(Cont& cont)
{ return indirect_container_view<Cont, reverse_range_access_traits>(cont); }


template<class Cont, class Proxy, class AccessTraits = range_access_traits>
using container_proxy_view = container_view<
  Cont
, iterator_range_access_traits<
    falcon::iterator::indirect_iterator<
      range_access_to_iterator<AccessTraits, Cont>
    , Proxy
    >
  , AccessTraits
  , Proxy
  >
>;

/**
 * container_view with a indirect_iterator
 *
 * @see container_view
 * @see indirect_iterator
 */
template<class Cont, class Proxy>
container_proxy_view<Cont, Proxy>
indirect_container(Cont& cont, Proxy proxy)
{ return container_proxy_view<Cont, Proxy>(cont, std::move(proxy)); }

/**
 * container_view with a indirect_iterator
 *
 * @see reverse_container_view
 * @see indirect_iterator
 */
template<class Cont, class Proxy>
container_proxy_view<Cont, Proxy, reverse_range_access_traits>
indirect_reverse_container(Cont& cont, Proxy proxy)
{ return container_proxy_view<Cont, Proxy, reverse_range_access_traits>(
  cont, std::move(proxy)
); }

}

#endif
