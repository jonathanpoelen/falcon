#ifndef FALCON_MEMORY_PTR_ALLOCATOR_HPP
#define FALCON_MEMORY_PTR_ALLOCATOR_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/memory/allocator_swap.hpp>

#if __cplusplus < 201103L
# include <boost/container/allocator_traits.hpp>
#endif
#include <memory>
#include <utility>

namespace falcon {

template<typename Alloc>
class ptr_allocator
{
  typedef FALCON_BOOST_OR_STD_NAMESPACE::allocator_traits<Alloc> allocator_traits;

public:
	typedef Alloc allocator_type;
  typedef typename allocator_traits::value_type value_type;
  typedef typename allocator_traits::pointer pointer;
  typedef typename allocator_traits::const_pointer const_pointer;
  typedef value_type & reference;
  typedef const value_type & const_reference;
  typedef typename allocator_traits::size_type size_type;
  typedef typename allocator_traits::difference_type difference_type;

#if __cplusplus <= 201103L
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

#if __cplusplus <= 201103L
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

  pointer allocate(size_type n)
  { return allocator_traits::allocate(m_alloc, n); }

	pointer allocate(size_type n, typename allocator_traits::const_void_pointer hint)
  { return allocator_traits::allocate(m_alloc, n, hint); }

	void deallocate(pointer p, size_type n)
  { allocator_traits::deallocate(m_alloc, p, n); }

	size_type max_size() const
  { return allocator_traits::max_size(m_alloc); }

#if __cplusplus <= 201103L
	template<class U, class... Args>
	void construct(U* p, Args&&... args)
  { allocator_traits::construct(m_alloc, p, std::forward<Args>(args)...); }

	template<class U>
	void destroy(U* p)
  { allocator_traits::destroy(m_alloc, p); }
#else
	void construct(pointer p, const_reference val)
  { allocator_traits::construct(m_alloc, p, val); }

	void destroy(pointer p)
  { allocator_traits::destroy(m_alloc, p); }
#endif

	template<typename U>
	bool operator==(const ptr_allocator<U>& rhs) const
	{ return m_alloc == rhs.m_alloc || *m_alloc == *rhs.m_alloc; }

	template<typename U>
	bool operator!=(const ptr_allocator<U>& rhs) const
	{ return !operator==(rhs); }

	void swap(ptr_allocator& other)
  {
    using std::swap;
    swap(m_alloc, other.m_alloc);
		allocator_swap<__allocator_base>(*this, other);
	}

	void set(Alloc& other)
	{ m_alloc = &other; }

	Alloc& get() const
	{ return *m_alloc; }

	bool valid() const
	{ return !!m_alloc; }

private:
	Alloc * m_alloc;
};

template<typename Alloc>
void swap(ptr_allocator<Alloc>& a, ptr_allocator<Alloc>& b)
{ a.swap(b); }

}

#endif
