#ifndef FALCON_MEMORY_MUTATION_ALLOCATOR_HPP
#define FALCON_MEMORY_MUTATION_ALLOCATOR_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/memory/allocator_rebind.hpp>

#include <memory>

namespace falcon {

/**
 *  @brief allocator with @c value_type = @p T::type, @c reference = @c value_type & and @c const_reference = @c value_type const &.
 *
 *  @ingroup allocators
 *
 *  @tparam T  Type of allocated object.
 *  @tparam AllocBase  Allocator base type, defaults to allocator<T>.
 */
template<typename T, typename AllocBase = std::allocator<T> >
class mutation_allocator
: public allocator_rebind<AllocBase, T>::type
{
	typedef typename allocator_rebind<AllocBase, T>::type allocator_base_;

public:
	typedef typename T::type value_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;

	template<typename U, typename NewAllocBase = AllocBase>
	struct rebind
	{ typedef mutation_allocator<U, NewAllocBase> other; };

	mutation_allocator()
	CPP_NOEXCEPT_OPERATOR2(allocator_base_())
	: allocator_base_()
	{}

	mutation_allocator(const mutation_allocator& a)
	CPP_NOEXCEPT_OPERATOR2(allocator_base_(a))
	: allocator_base_(a)
	{}

	template<typename Tp1>
	mutation_allocator(const mutation_allocator<Tp1>& other)
	CPP_NOEXCEPT_OPERATOR2(allocator_base_(other))
	: allocator_base_(other)
	{}
};

}

#endif
