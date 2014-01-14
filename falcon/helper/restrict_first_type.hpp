#ifndef FALCON_HELPER_RESTRICT_FIRST_TYPE_HPP
#define FALCON_HELPER_RESTRICT_FIRST_TYPE_HPP

namespace falcon {

template <class T>
struct restrict_first_type
{ typedef typename T::first_type type; };

}

#endif
