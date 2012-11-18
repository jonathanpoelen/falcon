#ifndef _FALCON_CAST_UNRELIABLE_POINTER_CAST_HPP
#define _FALCON_CAST_UNRELIABLE_POINTER_CAST_HPP

namespace falcon {

template<typename _T>
_T* unreliable_pointer_cast(void *p)
{ return static_cast<_T*>(p); }

}

#endif