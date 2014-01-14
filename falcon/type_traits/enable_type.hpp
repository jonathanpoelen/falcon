#ifndef FALCON_TYPE_TRAITS_ENABLE_TYPE_HPP
#define FALCON_TYPE_TRAITS_ENABLE_TYPE_HPP

namespace falcon {

template<class, class R = void>
struct enable_type
{ typedef R type; };

#if __cplusplus >= 201103L
template<class T, class R = void>
using enable_type_t = typename enable_type<T, R>::type;
#endif

}

#endif
