#ifndef FALCON_HELPER_RESTRICT_TYPE_HPP
#define FALCON_HELPER_RESTRICT_TYPE_HPP

namespace falcon {

template <class T>
struct restrict_type
{ typedef typename T::type type; };

}

#endif
