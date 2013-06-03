#ifndef FALCON_MEMORY_PTR_ALLOCATOR_HPP
#define FALCON_MEMORY_PTR_ALLOCATOR_HPP

#include <falcon/c++/noexcept.hpp>

#include <memory>
#include <utility>

namespace falcon {

template<typename Alloc>
class ptr_allocator
{
public:
	typedef Alloc allocator_type;
	typedef typename Alloc::value_type value_type;
	typedef typename Alloc::pointer pointer;
	typedef typename Alloc::const_pointer const_pointer;
	typedef typename Alloc::reference reference;
	typedef typename Alloc::const_reference const_reference;
	typedef typename Alloc::size_type size_type;
	typedef typename Alloc::difference_type difference_type;

#if __cplusplus > 201100L
	using propagate_on_container_copy_assignment = std::true_type;
	using propagate_on_container_move_assignment = std::true_type;
	using propagate_on_container_swap = std::true_type;
#endif

	template<typename U>
	struct rebind
	{ typedef ptr_allocator<U> other; };

public:
	ptr_allocator() CPP_NOEXCEPT
	: m_alloc(0)
	{}

	ptr_allocator(Alloc& alloc) CPP_NOEXCEPT
	: m_alloc(&alloc)
	{}

	ptr_allocator(const ptr_allocator& other) CPP_NOEXCEPT
	: m_alloc(other->m_alloc)
	{}

	template<class U>
	ptr_allocator(const ptr_allocator<U>& other) CPP_NOEXCEPT
	: m_alloc(other->m_alloc)
	{}

	ptr_allocator& operator=(Alloc& alloc) CPP_NOEXCEPT
	{ m_alloc = &alloc; }

	ptr_allocator& operator=(const ptr_allocator& other) CPP_NOEXCEPT
	{ m_alloc = other.m_alloc; }

#if __cplusplus > 201100L
	ptr_allocator(ptr_allocator&& other) CPP_NOEXCEPT
	: m_alloc(other.m_alloc)
	{
		other.m_alloc = nullptr;
	}

	ptr_allocator& operator==(ptr_allocator&& other) CPP_NOEXCEPT
	{
		m_alloc = other.m_alloc;
		other.m_alloc = nullptr;
	}
#endif

	~allocator() CPP_NOEXCEPT
	{}

	pointer address(reference x) const
	{ return m_alloc->address(x); }

	const_pointer address(const_reference x) const
	{ return m_alloc->address(x); }

	pointer allocate(size_type n, std::allocator<void>::const_pointer hint = 0)
	{ return m_alloc->allocate(n, hint); }

	void deallocate(pointer p, size_type n)
	{ m_alloc->deallocate(p, n); }

	size_type max_size() const  CPP_NOEXCEPT_OPERATOR2(m_alloc->max_size())
	{ return m_alloc->max_size(); }

#if __cplusplus > 201100L
	template<class U, class... Args>
	void construct(U* p, Args&&... args)
	{ m_alloc->construct(p, std::forward<Args>(args)...); }

	template<class U>
	void destroy(U* p)
	{ m_alloc->destroy(p); }
#else
	void construct(pointer p, const_reference val)
	{ m_alloc->construct(p, val); }

	void destroy(pointer p)
	{ m_alloc->destroy(p); }
#endif

	template<typename U>
	bool operator==(const ptr_allocator<U>& rhs) const
	{ return m_alloc == rhs.m_alloc; }

	template<typename U>
	bool operator!=(const ptr_allocator<U>& rhs) const
	{ return m_alloc == rhs.m_alloc; }

	void swap(ptr_allocator& other)
	{ std::swap(m_alloc, other.m_alloc); }

	void set(Alloc& other)
	{ m_alloc = &other; }

	Alloc& get() const
	{ return *m_alloc; }

	bool valid() const
	{ return !!m_alloc; }

private:
	Alloc * m_alloc;
};

}

namespace std {
	template<typename Alloc>
	void swap(falcon::ptr_allocator<Alloc>& a, falcon::ptr_allocator<Alloc>& b)
	{ a.swap(b); }
}

#endif
