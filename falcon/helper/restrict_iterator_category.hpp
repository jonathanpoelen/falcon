#ifndef FALCON_HELPER_RESTRICT_ITERATOR_CATEGORY_HPP
#define FALCON_HELPER_RESTRICT_ITERATOR_CATEGORY_HPP

namespace falcon {

template <class T>
struct restrict_iterator_category
{ typedef typename T::iterator_category type; };

}

#endif
