#ifndef FALCON_HELPER_RESTRICT_CHAR_TYPE_HPP
#define FALCON_HELPER_RESTRICT_CHAR_TYPE_HPP

namespace falcon {

template <class T>
struct restrict_char_type
{ typedef typename T::char_type type; };

}

#endif
