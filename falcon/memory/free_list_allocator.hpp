#ifndef FALCON_MEMORY_FREE_LIST_ALLOCATOR_HPP
#define FALCON_MEMORY_FREE_LIST_ALLOCATOR_HPP

#include <falcon/memory/free_list.hpp>
#include <falcon/memory/allocator_rebind.hpp>
#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/extend_pack.hpp>
#include <falcon/preprocessor/move.hpp>

namespace falcon {

template<typename T, typename AllocBase = std::allocator<T> >
class free_list_allocator
: public std::allocator<T>
{
	typedef typename allocator_rebind<AllocBase, T>::type __allocator_base;

public:
	typedef free_list<T, AllocBase> free_list_type;
	typedef typename __allocator_base::pointer pointer;
	typedef typename __allocator_base::const_pointer const_pointer;
	typedef typename std::allocator<T>::size_type size_type;

#if __cplusplus > 201100L
	using propagate_on_container_copy_assignment = std::false_type;
	using propagate_on_container_move_assignment = std::true_type;
	using propagate_on_container_swap = std::true_type;
#endif

	template<typename U, typename AllocBase2 = AllocBase>
	struct rebind
	{ typedef free_list_allocator<U, AllocBase2> other; };

	explicit free_list_allocator(size_type size)
	CPP_NOEXCEPT_OPERATOR2(free_list_type(size))
	: m_list(size)
	{}

	free_list_allocator(const free_list_allocator& other)
	CPP_NOEXCEPT_OPERATOR2(free_list_type(other.node_size(), other.m_allocator))
	: m_list(other.node_size(), other.m_allocator)
	{}

	template<typename CPP_EXTEND_PACK Args>
	free_list_allocator(size_type size, FALCON_RVALUE(Args)CPP_EXTEND_PACK args)
	CPP_NOEXCEPT_OPERATOR2(allocator_type(FALCON_FORWARD(Args, args)CPP_EXTEND_PACK))
	: m_list(size, FALCON_FORWARD(Args, args)CPP_EXTEND_PACK)
	{}

#if __cplusplus > 201100L
	free_list_allocator(free_list_allocator&& other)
	CPP_NOEXCEPT_OPERATOR2(free_list_type(std::forward<free_list<T>>(other.m_list)))
	: m_list(std::forward<free_list<T>>(other.m_list))
	{}
#endif

	template<typename U, typename AllocBase2>
	free_list_allocator(const free_list_allocator<U, AllocBase2>& other)
	CPP_NOEXCEPT_OPERATOR2(free_list_type(other.node_size(), other.m_allocator))
	: m_list(other.node_size(), other.m_allocator)
	{}

	free_list_allocator& operator=(const free_list_allocator& other) CPP_NOEXCEPT
	{ return *this; }

	pointer allocate(const void * = 0)
	{ return m_list.alloc(); }

	pointer allocate(size_type /*n*/, const void * = 0)
	{ return m_list.alloc(); }

	void deallocate(pointer p)
	{ return m_list.free(p); }

	void deallocate(pointer p, size_type /*n*/)
	{ return m_list.free(p); }

	free_list_type& freelist() CPP_NOEXCEPT
	{ return m_list; }

	const free_list_type& freelist() const CPP_NOEXCEPT
	{ return m_list; }

private:
	free_list_type m_list;
};

}

#endif
