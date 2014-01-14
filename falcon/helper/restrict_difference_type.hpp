#ifndef FALCON_HELPER_RESTRICT_DIFFERENCE_TYPE_HPP
#define FALCON_HELPER_RESTRICT_DIFFERENCE_TYPE_HPP

namespace falcon {

template <class T>
struct restrict_difference_type
{ typedef typename T::difference_type type; };

}

#endif
