#ifndef FALCON_MEMORY_GENERIC_ALLOCATOR_HPP
#define FALCON_MEMORY_GENERIC_ALLOCATOR_HPP

#include <falcon/parameter/parameter_index.hpp>
#include <falcon/memory/construct.hpp>
#include <falcon/memory/destroy.hpp>

#include <memory>

namespace falcon {

template<typename T, typename AllocBase = std::allocator<T> >
class generic_allocator
: public std::allocator_traits<AllocBase>::template rebind_alloc<T>
{
	typedef typename std::allocator_traits<AllocBase>::template rebind_alloc<T> allocator_base;

public:
	typedef typename allocator_base::pointer pointer;
	typedef typename allocator_base::size_type size_type;
	typedef typename allocator_base::const_pointer const_pointer;
	typedef typename allocator_base::const_reference const_reference;

	template<typename U, typename NewAllocBase = AllocBase>
	struct rebind
	{ typedef generic_allocator<U, NewAllocBase> other; };

	generic_allocator() noexcept(noexcept(allocator_base())) = default;

	generic_allocator(const generic_allocator& other) noexcept(noexcept(allocator_base(other))) = default;

	template<typename U>
	generic_allocator(const generic_allocator<U>& other) noexcept(noexcept(allocator_base(other)))
	: allocator_base(other)
	{}

	template<typename U, typename... Args>
	void construct(U* p, Args&&... args)
	{ ::falcon::construct(p, std::forward<Args>(args)...); }

	template<typename U>
	void destroy(U* p)
	{ ::falcon::destroy(p); }
};

}

#endif
