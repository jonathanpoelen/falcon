#ifndef FALCON_MEMORY_REFERENCE_WRAPPER_ALLOCATOR_HPP
#define FALCON_MEMORY_REFERENCE_WRAPPER_ALLOCATOR_HPP

#include <functional>
#include <falcon/memory/mutation_allocator.hpp>

namespace falcon {
	template<class T, class Alloc = std::allocator<T>>
	using reference_wrapper_allocator =
    mutation_allocator<
      std::reference_wrapper<T>,
      typename Alloc::template rebind<std::reference_wrapper<T>>::other
    >;
}

#endif
