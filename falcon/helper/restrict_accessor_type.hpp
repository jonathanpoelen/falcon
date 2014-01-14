#ifndef FALCON_HELPER_RESTRICT_ACCESSOR_TYPE_HPP
#define FALCON_HELPER_RESTRICT_ACCESSOR_TYPE_HPP

namespace falcon {

template <class T>
struct restrict_accessor_type
{ typedef typename T::accessor_type type; };

}

#endif
