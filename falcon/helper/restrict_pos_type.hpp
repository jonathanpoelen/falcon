#ifndef FALCON_HELPER_RESTRICT_POS_TYPE_HPP
#define FALCON_HELPER_RESTRICT_POS_TYPE_HPP

namespace falcon {

template <class T>
struct restrict_pos_type
{ typedef typename T::pos_type type; };

}

#endif
