#ifndef FALCON_HELPER_RESTRICT_CONST_REFERENCE_HPP
#define FALCON_HELPER_RESTRICT_CONST_REFERENCE_HPP

namespace falcon {

template <class T>
struct restrict_const_reference
{ typedef typename T::const_reference type; };

}

#endif
