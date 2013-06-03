#ifndef FALCON_MEMORY_POD_ALLOCATOR_HPP
#define FALCON_MEMORY_POD_ALLOCATOR_HPP

#include <falcon/parameter/parameter_index.hpp>
#include <falcon/c++/noexcept.hpp>

#include <memory>

namespace falcon {

template<typename T, typename AllocBase = std::allocator<T> >
class pod_allocator
: public std::allocator_traits<AllocBase>::template rebind_alloc<T>::other
{
	typedef typename std::allocator_traits<AllocBase>::template rebind_alloc<T>::other __allocator_base;

public:
	typedef typename __allocator_base::pointer pointer;
	typedef typename __allocator_base::size_type size_type;
	typedef typename __allocator_base::const_pointer const_pointer;
	typedef typename __allocator_base::const_reference const_reference;

	template<typename U, typename NewAllocBase = AllocBase>
	struct rebind
	{ typedef pod_allocator<U, NewAllocBase> other; };

	pod_allocator() noexcept(noexcept(__allocator_base())) = default;

	pod_allocator(const pod_allocator& other) noexcept(noexcept(__allocator_base(other))) = default;

	template<typename U>
	pod_allocator(const pod_allocator<U>& other) noexcept(noexcept(__allocator_base(other)))
	{}

	~pod_allocator() noexcept(noexcept(__allocator_base().~__allocator_base()))
	{}

	template<typename Up, typename... _Args>
	void construct(Up* p, _Args&&... __args) CPP_NOEXCEPT
	{ ::new(p) Up{std::forward<_Args>(__args)...}; }

	template<std::size_t _Index>
	static int get(T val)
	{ return val[_Index]; }

	template<typename Up, std::size_t... _Indexes>
	void dispatch_construct(std::true_type,
													falcon::parameter_index<_Indexes...>,
													Up* p, T val) CPP_NOEXCEPT
	{ ::new(p) Up{get<_Indexes>(val)...}; }

	template<typename Up, std::size_t... _Indexes>
	void dispatch_construct(std::false_type,
													falcon::parameter_index<_Indexes...>,
													Up* p, T val) CPP_NOEXCEPT
	{ ::new(p) Up(val); }

	template<typename Up>
	void construct(Up* p, T val) CPP_NOEXCEPT
	{ dispatch_construct(typename std::is_array<T>::type(), falcon::build_parameter_index<2>::type(), p, val); }

	template<typename Up>
	void destroy(Up*) CPP_NOEXCEPT
	{ }
};

}

#endif
