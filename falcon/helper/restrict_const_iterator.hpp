#ifndef FALCON_HELPER_RESTRICT_CONST_ITERATOR_HPP
#define FALCON_HELPER_RESTRICT_CONST_ITERATOR_HPP

namespace falcon {

template <class T>
struct restrict_const_iterator
{ typedef typename T::const_iterator type; };

}

#endif
