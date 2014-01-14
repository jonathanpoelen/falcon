#ifndef FALCON_HELPER_RESTRICT_ARGUMENT_TYPE_HPP
#define FALCON_HELPER_RESTRICT_ARGUMENT_TYPE_HPP

namespace falcon {

template <class T>
struct restrict_argument_type
{ typedef typename T::argument_type type; };

}

#endif
