#ifndef FALCON_HELPER_RESTRICT_REFERENCE_HPP
#define FALCON_HELPER_RESTRICT_REFERENCE_HPP

namespace falcon {

template <class T>
struct restrict_reference
{ typedef typename T::reference type; };

}

#endif
