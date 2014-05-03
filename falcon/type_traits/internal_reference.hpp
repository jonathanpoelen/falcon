#ifndef FALCON_TYPE_TRAITS_INTERNAL_REFERENCE_HPP
#define FALCON_TYPE_TRAITS_INTERNAL_REFERENCE_HPP

namespace falcon {

template<class T>
struct internal_reference
{ typedef typename T::reference type; };

template<class T>
struct internal_reference<const T>
{ typedef typename T::const_reference type; };

}

#endif
