#ifndef FALCON_MEMORY_FREE_LIST_ALLOCATOR_HPP
#define FALCON_MEMORY_FREE_LIST_ALLOCATOR_HPP

#include <falcon/algorithm/dichotomic_algorithm.hpp>
#include <falcon/memory/allocator_rebind.hpp>
#include <falcon/type_traits/if.hpp>
#include <falcon/bit/byte_cast.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(aligned_storage)

#include <falcon/memory/allocator_rebind.hpp>
#include <falcon/bit/byte_cast.hpp>
#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(aligned_storage)

#include <memory>
#if __cplusplus > 201100L
#include <utility>
#endif

namespace falcon {

template<typename T>
class free_list
{
	struct Node
	{
		Node * next;
		unsigned char data[1];
	};

	static const bool _S_align = FALCON_BOOST_OR_STD_NAMESPACE::alignment_of<T>::value;
	static const bool _S_heap = (_S_align > sizeof(Node)) ? _S_align : sizeof(Node);

public:
	typedef std::allocator<T>::value_type value_type;
	typedef std::allocator<T>::pointer pointer;

public:
	explicit free_list(std::size_t size_alloc) CPP_NOEXCEPT
	: m_node(0)
	, m_size_alloc(size_alloc)
	{}

#if __cplusplus > 201100L
	free_list(free_list&& other) CPP_NOEXCEPT
	: m_node(other.m_node)
	, m_size_alloc(other.m_size_alloc)
	{ other.m_node = 0; }

	free_list(const free_list&) = delete;
	free_list& operator=(const free_list&) = delete;
#else
private:
	free_list(const free_list&);
	free_list& operator=(const free_list&);
public:
#endif

	~free_list() CPP_NOEXCEPT
	{
		clear();
	}

	pointer alloc()
	{
		if (m_node) {
			return static_cast<pointer>(::operator new(_S_heap + m_size_alloc * sizeof(T)));
		}
		pointer ret = reinterpret_cast<pointer>(m_node->data);
		m_node = m_node->next;
		return ret;
	}

	void free(pointer p)
	{
		free_list_node * tmp = m_node;
		m_node = reinterpret_cast<>(byte_cast(p) - _S_heap);
		m_node->next = tmp;
	}

	void clear() CPP_NOEXCEPT
	{
		while (m_node) {
			free_list_node * node = m_node->next;
			::operator delete(_S_heap + m_fixed_size * sizeof(T));
			m_node = node;
		}
	}

private:
	Node * m_node;
	std::size_t m_size_alloc;
};


template<typename T, typename AllocBase = std::allocator<T> >
class free_list_allocator
#if defined(IN_IDE_PARSER)
: public std::allocator<T>
#else
: public allocator_rebind<AllocBase, T>::type
#endif
{
	typedef typename allocator_rebind<AllocBase, T>::type __allocator_base;

public:
	typedef typename __allocator_base::pointer pointer;
	typedef typename __allocator_base::size_type size_type;
	typedef typename __allocator_base::const_pointer const_pointer;

#if __cplusplus > 201100L
	using propagate_on_container_copy_assignment = std::false_type;
	using propagate_on_container_move_assignment = std::true_type;
	using propagate_on_container_swap = std::true_type;
#endif

	template<typename U, typename AllocBase2 = AllocBase>
	struct rebind
	{ typedef free_list_allocator<U, AllocBase2> other; };

	explicit free_list_allocator(size_type size)
	: __allocator_base()
	, m_list(size)
	{}

	free_list_allocator(const free_list_allocator& other)
	: __allocator_base(other)
	, m_list(other.node_size())
	{}

#if __cplusplus > 201100L
	free_list_allocator(free_list_allocator&& other)
	: __allocator_base(std::forward<__allocator_base>(other))
	, m_list(std::forward<free_list<T>>(other.m_list))
	{}
#endif

	template<typename U, typename AllocBase2>
	free_list_allocator(const free_list_allocator<U, AllocBase2>& other)
	: __allocator_base(other)
	, m_fixed_size(other.node_size())
	{}

	free_list_allocator& operator=(const free_list_allocator& other)
	{
		__allocator_base::operator=(other);
		return *this;
	}

	pointer allocate(size_type /*n*/, const void * = 0)
	{ return m_list->alloc(); }

	void deallocate(pointer p, size_type /*n*/)
	{ return m_list->free(p); }

	void clear()
	{ m_list->clear(); }

private:
	free_list<T> * m_list;
};

}

#endif
