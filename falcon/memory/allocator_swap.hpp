#ifndef FALCON_MEMORY_ALLOCATOR_SWAP_HPP
#define FALCON_MEMORY_ALLOCATOR_SWAP_HPP

#if __cplusplus > 201100L

#include <memory>

namespace falcon {

namespace detail {
	template<typename Allocator>
	void allocator_swap_impl(Allocator&, Allocator&, std::false_type)
	{}

	template<typename Allocator>
	void allocator_swap_impl(Allocator& a, Allocator& b, std::true_type)
	{ std::swap(a, b); }
}

template<typename Allocator>
void allocator_swap(Allocator& a, Allocator& b)
{
	::falcon::detail::allocator_swap_impl(
		a, b, typename std::allocator_traits<Allocator>::propagate_on_container_swap()
	);
}

}

#else

#include <falcon/sfinae/has_type.hpp>

namespace falcon {

namespace detail {
	FALCON_CLASS_HAS_TYPE(propagate_on_container_swap);
	template<typename Allocator,
		bool = has_propagate_on_container_swap<Allocator>::value>
	struct allocator_swap_impl
	{
		static void swap(Allocator&, Allocator&)
		{}
	};

	template<typename Allocator>
	struct allocator_swap_impl<Allocator, true>
	{
		static void swap_impl(Allocator& a, Allocator& b, std::true_type)
		{ std::swap(a, b); }
		static void swap_impl(Allocator&, Allocator&, std::false_type)
		{}
		static void swap(Allocator& a, Allocator& b)
		{
			typedef typename Allocator::propagate_on_container_swap propagate;
			swap_impl(a, b, propagate());
		}
	};
}

template<typename Allocator>
void allocator_swap(Allocator& a, Allocator& b)
{ ::falcon::detail::allocator_swap_impl<Allocator>::swap(a, b); }

}

#endif

#endif
