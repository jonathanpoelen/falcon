#ifndef FALCON_HELPER_RESTRICT_OFF_TYPE_HPP
#define FALCON_HELPER_RESTRICT_OFF_TYPE_HPP

namespace falcon {

template <class T>
struct restrict_off_type
{ typedef typename T::off_type type; };

}

#endif
