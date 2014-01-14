#ifndef FALCON_HELPER_RESTRICT_TRAITS_TYPE_HPP
#define FALCON_HELPER_RESTRICT_TRAITS_TYPE_HPP

namespace falcon {

template <class T>
struct restrict_traits_type
{ typedef typename T::traits_type type; };

}

#endif
