#ifndef FALCON_HELPER_RESTRICT_VALUE_COMPARE_HPP
#define FALCON_HELPER_RESTRICT_VALUE_COMPARE_HPP

namespace falcon {

template <class T>
struct restrict_value_compare
{ typedef typename T::value_compare type; };

}

#endif
