#ifndef FALCON_HELPER_RESTRICT_ALLOCATOR_TYPE_HPP
#define FALCON_HELPER_RESTRICT_ALLOCATOR_TYPE_HPP

namespace falcon {

template <class T>
struct restrict_allocator_type
{ typedef typename T::allocator_type type; };

}

#endif
