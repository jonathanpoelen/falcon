#ifndef FALCON_MEMORY_REFERENCE_WRAPPER_ALLOCATOR_HPP
#define FALCON_MEMORY_REFERENCE_WRAPPER_ALLOCATOR_HPP

#include <functional>
#include <falcon/memory/mutation_allocator.hpp>

namespace falcon {
	template<typename _T, typename _Alloc = std::allocator<_T>>
	using reference_wrapper_allocator = mutation_allocator<std::reference_wrapper<_T>, typename _Alloc::template rebind<std::reference_wrapper<_T>>::other>;
}

#endif