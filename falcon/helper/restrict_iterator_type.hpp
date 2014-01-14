#ifndef FALCON_HELPER_RESTRICT_ITERATOR_TYPE_HPP
#define FALCON_HELPER_RESTRICT_ITERATOR_TYPE_HPP

namespace falcon {

template <class T>
struct restrict_iterator_type
{ typedef typename T::iterator_type type; };

}

#endif
