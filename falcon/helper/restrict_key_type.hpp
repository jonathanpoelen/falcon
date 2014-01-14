#ifndef FALCON_HELPER_RESTRICT_KEY_TYPE_HPP
#define FALCON_HELPER_RESTRICT_KEY_TYPE_HPP

namespace falcon {

template <class T>
struct restrict_key_type
{ typedef typename T::key_type type; };

}

#endif
