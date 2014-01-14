#ifndef FALCON_HELPER_RESTRICT_ITERATOR_HPP
#define FALCON_HELPER_RESTRICT_ITERATOR_HPP

namespace falcon {

template <class T>
struct restrict_iterator
{ typedef typename T::iterator type; };

}

#endif
