#ifndef FALCON_HELPER_RESTRICT_KEY_COMPARE_HPP
#define FALCON_HELPER_RESTRICT_KEY_COMPARE_HPP

namespace falcon {

template <class T>
struct restrict_key_compare
{ typedef typename T::key_compare type; };

}

#endif
