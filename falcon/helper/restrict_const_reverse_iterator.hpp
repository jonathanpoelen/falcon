#ifndef FALCON_HELPER_RESTRICT_CONST_REVERSE_ITERATOR_HPP
#define FALCON_HELPER_RESTRICT_CONST_REVERSE_ITERATOR_HPP

namespace falcon {

template <class T>
struct restrict_const_reverse_iterator
{ typedef typename T::const_reverse_iterator type; };

}

#endif
