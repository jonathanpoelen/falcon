#ifndef FALCON_ITERATOR_SUBRANGE_ACCESS_ITERATOR_HPP
#define FALCON_ITERATOR_SUBRANGE_ACCESS_ITERATOR_HPP

#include <falcon/container/range_access.hpp>
#include <falcon/type_traits/subtype.hpp>

namespace falcon {

template<class T>
struct subrange_access_iterator
{ typedef typename range_access_iterator<typename subtype<T>::type>::type type; };

}

#endif
