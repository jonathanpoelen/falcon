#ifndef FALCON_HELPER_RESTRICT_COMPARE_TYPE_HPP
#define FALCON_HELPER_RESTRICT_COMPARE_TYPE_HPP

namespace falcon {

template <class T>
struct restrict_compare_type
{ typedef typename T::compare_type type; };

}

#endif
