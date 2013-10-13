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
	typedef typename std::allocator_traits<AllocBase>::template rebind_alloc<T> __allocator_base;

public:
	typedef typename __allocator_base::pointer pointer;
	typedef typename __allocator_base::size_type size_type;
	typedef typename __allocator_base::const_pointer const_pointer;
	typedef typename __allocator_base::const_reference const_reference;

	template<typename U, typename NewAllocBase = AllocBase>
	struct rebind
	{ typedef generic_allocator<U, NewAllocBase> other; };

	generic_allocator() noexcept(noexcept(__allocator_base())) = default;

	generic_allocator(const generic_allocator& other) noexcept(noexcept(__allocator_base(other))) = default;

	template<typename U>
	generic_allocator(const generic_allocator<U>& other) noexcept(noexcept(__allocator_base(other)))
	: __allocator_base(other)
	{}

	~generic_allocator() noexcept(noexcept(__allocator_base().~__allocator_base()))
	{}

	template<typename U, typename... Args>
	void construct(U* p, Args&&... args) noexcept
	{ ::falcon::construct(p, std::forward<Args>(args)...); }

	template<typename U>
	void destroy(U* p)
	{ ::falcon::destroy(p); }
};

}

#endif
