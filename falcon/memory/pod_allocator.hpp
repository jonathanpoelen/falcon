#ifndef FALCON_MEMORY_POD_ALLOCATOR_HPP
#define FALCON_MEMORY_POD_ALLOCATOR_HPP

#include <falcon/parameter/parameter_index.hpp>

#include <memory>

namespace falcon {

template<typename _T>
class pod_allocator
: public std::allocator<_T>
{
	typedef std::allocator<_T> __allocator_base;

public:
	typedef typename __allocator_base::pointer pointer;
	typedef typename __allocator_base::size_type size_type;
	typedef typename __allocator_base::const_pointer const_pointer;
	typedef typename __allocator_base::const_reference const_reference;

	template<typename _U>
	struct rebind
	{ typedef pod_allocator<_U> other; };

	pod_allocator() throw() = default;
	pod_allocator(const pod_allocator&) throw() = default;
	template<typename _U>
	pod_allocator(const pod_allocator<_U>&) throw()
	{}

	template<typename _Up, typename... _Args>
	void construct(_Up* p, _Args&&... __args)
	{ ::new(p) _Up{std::forward<_Args>(__args)...}; }

	template<std::size_t _Index>
	static int get(_T val)
	{ return val[_Index]; }

	template<typename _Up, std::size_t... _Indexes>
	void dispatch_construct(std::true_type,
													falcon::parameter_index<_Indexes...>,
													_Up* p, _T val)
	{ ::new(p) _Up{get<_Indexes>(val)...}; }

	template<typename _Up, std::size_t... _Indexes>
	void dispatch_construct(std::false_type,
													falcon::parameter_index<_Indexes...>,
													_Up* p, _T val)
	{ ::new(p) _Up(val); }

	template<typename _Up>
	void construct(_Up* p, _T val)
	{ dispatch_construct(typename std::is_array<_T>::type(), falcon::build_parameter_index<2>::type(), p, val); }

	template<typename _Up>
	void destroy(_Up*)
	{ }
};

}

#endif