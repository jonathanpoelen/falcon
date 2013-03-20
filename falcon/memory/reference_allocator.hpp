#ifndef FALCON_MEMORY_REFERENCE_ALLOCATOR_HPP
#define FALCON_MEMORY_REFERENCE_ALLOCATOR_HPP

#include <memory>

namespace falcon {

template<typename _T, typename _AllocBase = std::allocator<_T> >
struct reference_allocator
: _AllocBase
{
	typedef typename _T::type value_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;

	template<typename _U>
	struct rebind
	{ typedef reference_allocator<_U, typename _AllocBase::template rebind<_U>::other> other; };
};

}

#endif