#ifndef FALCON_HELPER_RESTRICT_SECOND_ARGUMENT_TYPE_HPP
#define FALCON_HELPER_RESTRICT_SECOND_ARGUMENT_TYPE_HPP

namespace falcon {

template <class T>
struct restrict_second_argument_type
{ typedef typename T::second_argument_type type; };

}

#endif
