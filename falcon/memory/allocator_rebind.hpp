#ifndef FALCON_MEMORY_ALLOCATOR_REBIND_HPP
#define FALCON_MEMORY_ALLOCATOR_REBIND_HPP

#if __cplusplus <= 201103L
#include <memory>
#endif

namespace falcon {

template<class Alloc, class T>
struct allocator_rebind
{
  typedef typename
#if __cplusplus >= 201103L
		std::allocator_traits<Alloc>::template rebind_alloc<T>
#else
		Alloc::template rebind<T>::other
#endif
	type;
};

#if __cplusplus >= 201103L
template<class Alloc, class T>
using allocator_rebind_t = typename allocator_rebind<Alloc, T>::type;
#endif

}

#endif
