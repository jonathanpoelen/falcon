#ifndef FALCON_HELPER_RESTRICT_RESULT_TYPE_HPP
#define FALCON_HELPER_RESTRICT_RESULT_TYPE_HPP

namespace falcon {

template <class T>
struct restrict_result_type
{ typedef typename T::result_type type; };

}

#endif
