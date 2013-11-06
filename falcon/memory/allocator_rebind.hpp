#ifndef FALCON_MEMORY_ALLOCATOR_REBIND_HPP
#define FALCON_MEMORY_ALLOCATOR_REBIND_HPP

#include <falcon/config.hpp>
#if __cplusplus <= 201103L
#include <memory>
#endif

namespace falcon {

template<typename Alloc, typename T>
struct allocator_rebind
{
	typedef typename
#if __cplusplus <= 201103L
		std::allocator_traits<Alloc>::template rebind_alloc<T>
#else
		Alloc::template rebind<T>::other
#endif
	type;
};

}

#endif
