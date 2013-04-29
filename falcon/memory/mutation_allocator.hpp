#ifndef FALCON_MEMORY_MUTATION_ALLOCATOR_HPP
#define FALCON_MEMORY_MUTATION_ALLOCATOR_HPP

#include <memory>
#include <falcon/c++/noexcept.hpp>
#if __cplusplus >= 201103L
# include <type_traits>
#endif

namespace falcon {

/**
 *  @brief allocator with @c value_type = @p _T::type, @c reference = @c value_type & and @c const_reference = @c value_type const &.
 *
 *  @ingroup allocators
 *
 *  @tparam _T  Type of allocated object.
 *  @tparam _AllocBase  Allocator base type, defaults to allocator<_T>.
 */
template<typename _T, typename _AllocBase = std::allocator<_T> >
class mutation_allocator
: public _AllocBase::template rebind<_U>::other
{
	typedef typename _AllocBase::template rebind<_U>::other __allocator_base;

public:
	typedef typename _T::type value_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;

	template<typename _U, typename _NewAllocBase = _AllocBase>
	struct rebind
	{ typedef mutation_allocator<_U, _NewAllocBase> other; };

	mutation_allocator()
	CPP_NOEXCEPT_OPERATOR2(__allocator_base())
	: __allocator_base()
	{}

	mutation_allocator(const mutation_allocator& __a)
	CPP_NOEXCEPT_OPERATOR2(__allocator_base(__a))
	: __allocator_base(__a)
	{}

	template<typename _Tp1>
	mutation_allocator(const mutation_allocator<_Tp1>& other)
	CPP_NOEXCEPT_OPERATOR2(__allocator_base(other))
	: __allocator_base(other)
	{}

	~mutation_allocator()
	CPP_NOEXCEPT_OPERATOR2(__allocator_base().~__allocator_base())
	{}
};

}

#endif