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
#include <falcon/c++/extend_pack.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include <falcon/preprocessor/move.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(aligned_storage)

#include <memory>
#if __cplusplus > 201100L
#include <utility>
#endif
#include <stdexcept>

namespace falcon {

template<typename T, typename AllocBase = std::allocator<T> >
class free_list_allocator;

template<typename T, typename Alloc = std::allocator<T> >
class free_list
{
	friend free_list_allocator<T, Alloc>;

	struct Node
	{
		Node * next;
		unsigned char data[1];
	};

public:
	static const bool _S_align = FALCON_BOOST_OR_STD_NAMESPACE::alignment_of<T>::value;
	static const bool _S_heap = (_S_align > sizeof(Node)) ? _S_align : sizeof(Node);

public:
	typedef typename allocator_rebind<Alloc, byte_t>::type allocator_type;
	typedef typename allocator_rebind<Alloc, T>::type::value_type value_type;
	typedef typename allocator_rebind<Alloc, T>::type::pointer pointer;
	typedef typename allocator_rebind<Alloc, T>::type::size_type size_type;

public:
	explicit free_list(size_type size_alloc) CPP_NOEXCEPT_OPERATOR2(allocator_type())
	: m_node(0)
	, m_size_alloc(size_alloc)
	, m_allocator()
	{}

	free_list(size_type size_alloc, const allocator_type& allocator)
	CPP_NOEXCEPT_OPERATOR2(allocator_type(allocator))
	: m_node(0)
	, m_size_alloc(size_alloc)
	, m_allocator(allocator)
	{}

	template<typename CPP_EXTEND_PACK Args>
	free_list(size_type size_alloc, FALCON_RVALUE(Args)CPP_EXTEND_PACK args)
	CPP_NOEXCEPT_OPERATOR2(allocator_type(FALCON_FORWARD(Args, args)CPP_EXTEND_PACK))
	: m_node(0)
	, m_size_alloc(size_alloc)
	, m_allocator(FALCON_FORWARD(Args, args)CPP_EXTEND_PACK)
	{}

#if __cplusplus > 201100L
	free_list(size_type size_alloc, allocator_type&& allocator)
	CPP_NOEXCEPT_OPERATOR2(allocator_type(std::forward<allocator_type>(allocator)))
	: m_node(0)
	, m_size_alloc(size_alloc)
	, m_allocator(std::forward<allocator_type>(allocator))
	{}

	free_list(free_list&& other)
	CPP_NOEXCEPT_OPERATOR2(std::forward<allocator_type>(other.m_allocator))
	: m_node(other.m_node)
	, m_size_alloc(other.m_size_alloc)
	, m_allocator(std::forward<allocator_type>(other.m_allocator))
	{ other.m_node = 0; }

	free_list& operator=(free_list&& other)
	CPP_NOEXCEPT_OPERATOR2(other.m_allocator = std::forward<allocator_type>(other.m_allocator))
	{
		clear();
		m_node = other.m_node;
		m_size_alloc = other.m_size_alloc;
		m_allocator = std::forward<allocator_type>(other.m_allocator);
		other.m_node = 0;
	}

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
		if ( ! m_node) {
			return reinterpret_cast<pointer>(m_allocator.allocate(_S_heap + m_size_alloc * sizeof(T)) + _S_heap);
		}
		pointer ret = reinterpret_cast<pointer>(m_node->data);
		m_node = m_node->next;
		return ret;
	}

	void free(pointer p)
	{
		Node * tmp = m_node;
		m_node = reinterpret_cast<Node*>(byte_cast(p) - _S_heap);
		m_node->next = tmp;
	}

	void clear() CPP_NOEXCEPT
	{
		while (m_node) {
			Node * node = m_node->next;
			m_allocator.deallocate(byte_cast(m_node), _S_heap + m_size_alloc * sizeof(T));
			m_node = node;
		}
	}

	size_type node_size() const
	{ return m_size_alloc; }

	void move_list_to(free_list& other)
	{
		if (other.m_size_alloc < m_size_alloc) {
			throw std::underflow_error("free_list::move_list_to");
		}

		if (m_node) {
			Node * node = m_node;
			while (node->next) {
				node = node->next;
			}
			node->next = other.m_node;
		}
		else {
			m_node = other.m_node;
		}

		other.m_node = 0;
	}

private:
	Node * m_node;
	size_type m_size_alloc;
	allocator_type m_allocator;
};


template<typename T, typename AllocBase>
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
