#ifndef FALCON_HELPER_RESTRICT_ELEMENT_TYPE_HPP
#define FALCON_HELPER_RESTRICT_ELEMENT_TYPE_HPP

namespace falcon {

template <class T>
struct restrict_element_type
{ typedef typename T::element_type type; };

}

#endif
