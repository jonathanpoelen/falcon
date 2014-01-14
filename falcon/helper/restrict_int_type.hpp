#ifndef FALCON_HELPER_RESTRICT_INT_TYPE_HPP
#define FALCON_HELPER_RESTRICT_INT_TYPE_HPP

namespace falcon {

template <class T>
struct restrict_int_type
{ typedef typename T::int_type type; };

}

#endif
