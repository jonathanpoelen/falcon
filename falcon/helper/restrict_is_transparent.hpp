#ifndef FALCON_HELPER_RESTRICT_IS_TRANSPARENT_HPP
#define FALCON_HELPER_RESTRICT_IS_TRANSPARENT_HPP

namespace falcon {

template <class T>
struct restrict_is_transparent
{ typedef typename T::is_transparent type; };

}

#endif
