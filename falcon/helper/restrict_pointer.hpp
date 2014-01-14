#ifndef FALCON_HELPER_RESTRICT_POINTER_HPP
#define FALCON_HELPER_RESTRICT_POINTER_HPP

namespace falcon {

template <class T>
struct restrict_pointer
{ typedef typename T::pointer type; };

}

#endif
