#ifndef FALCON_HELPER_RESTRICT_FUNCTOR_TYPE_HPP
#define FALCON_HELPER_RESTRICT_FUNCTOR_TYPE_HPP

namespace falcon {

template <class T>
struct restrict_functor_type
{ typedef typename T::functor_type type; };

}

#endif
