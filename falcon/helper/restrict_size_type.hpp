#ifndef FALCON_HELPER_RESTRICT_SIZE_TYPE_HPP
#define FALCON_HELPER_RESTRICT_SIZE_TYPE_HPP

namespace falcon {

template <class T>
struct restrict_size_type
{ typedef typename T::size_type type; };

}

#endif
