#ifndef FALCON_MEMORY_ALLOCATOR_REBIND_HPP
#define FALCON_MEMORY_ALLOCATOR_REBIND_HPP

#if __cplusplus > 201100L
#include <memory>
#endif

namespace falcon {

template<typename Alloc, typename T>
struct allocator_rebind
{
	typedef typename
#if __cplusplus > 201100L
		std::allocator_traits<Alloc>::template rebind_alloc<T>::other
#else
		Alloc::template rebind<T>::other
#endif
	type;
};

}

#endif
