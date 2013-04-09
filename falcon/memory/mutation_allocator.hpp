#ifndef FALCON_MEMORY_MUTATION_ALLOCATOR_HPP
#define FALCON_MEMORY_MUTATION_ALLOCATOR_HPP

#include <memory>

namespace falcon {

template<typename _T, typename _AllocBase = std::allocator<_T> >
class mutation_allocator
: public _AllocBase
{
public:
	typedef typename _T::type value_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;

	template<typename _U>
	struct rebind
	{ typedef mutation_allocator<_U, typename _AllocBase::template rebind<_U>::other> other; };

	mutation_allocator() throw()
	{}

	mutation_allocator(const mutation_allocator& __a) throw()
	: _AllocBase(__a)
	{}

	template<typename _Tp1>
	mutation_allocator(const mutation_allocator<_Tp1>&) throw()
	{}

	~mutation_allocator() throw()
	{}
};

}

#endif