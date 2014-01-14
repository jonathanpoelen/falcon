#ifndef FALCON_HELPER_RESTRICT_SECOND_TYPE_HPP
#define FALCON_HELPER_RESTRICT_SECOND_TYPE_HPP

namespace falcon {

template <class T>
struct restrict_second_type
{ typedef typename T::second_type type; };

}

#endif
