#ifndef FALCON_HELPER_RESTRICT_FIRST_ARGUMENT_TYPE_HPP
#define FALCON_HELPER_RESTRICT_FIRST_ARGUMENT_TYPE_HPP

namespace falcon {

template <class T>
struct restrict_first_argument_type
{ typedef typename T::first_argument_type type; };

}

#endif
