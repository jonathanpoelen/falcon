#ifndef FALCON_DETAIL_INNER_REFERENCE_HPP
#define FALCON_DETAIL_INNER_REFERENCE_HPP

namespace falcon {
namespace __detail {

template<class T>
struct inner_reference
{ typedef typename T::reference type; };

template<class T>
struct inner_reference<volatile T>
{ typedef typename T::reference type; };

template<class T>
struct inner_reference<const T>
{ typedef typename T::const_reference type; };

template<class T>
struct inner_reference<const volatile T>
{ typedef typename T::const_reference type; };

}
}

#endif
