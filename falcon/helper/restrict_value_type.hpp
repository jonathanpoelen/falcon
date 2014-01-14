#ifndef FALCON_HELPER_RESTRICT_VALUE_TYPE_HPP
#define FALCON_HELPER_RESTRICT_VALUE_TYPE_HPP

namespace falcon {

template <class T>
struct restrict_value_type
{ typedef typename T::value_type type; };

}

#endif
