#ifndef FALCON_HELPER_RESTRICT_REVERSE_ITERATOR_HPP
#define FALCON_HELPER_RESTRICT_REVERSE_ITERATOR_HPP

namespace falcon {

template <class T>
struct restrict_reverse_iterator
{ typedef typename T::reverse_iterator type; };

}

#endif
