#ifndef _FALCON_MEMORY_DESTROY_HPP
#define _FALCON_MEMORY_DESTROY_HPP

#if __cplusplus >= 201103L
# include <type_traits>
#endif
#include <iterator>
#include <falcon/c++/constexpr.hpp>
#include <falcon/detail/addressof.hpp>

//destroy, default_delete, default_delete_then_zero, deallocate, deallocate_then_zero
//destroy_wrapper, default_delete_wrapper, default_delete_then_zero_wrapper, deallocate_wrapper, deallocate_then_zero_wrapper

namespace falcon {

/**
 * Destroy the object pointed to by a pointer type.
 */
template<typename _Tp>
inline void destroy(_Tp* p)
{ p->~_Tp(); }

template<bool>
struct __destroy_aux
{
	template<typename _ForwardIterator>
	static void __destroy(_ForwardIterator __first, _ForwardIterator __last)
	{
		for (; __first != __last; ++__first)
			destroy(falcon::detail::addressof(*__first));
	}
};

template<>
struct __destroy_aux<true>
{
	template<typename _ForwardIterator>
	inline static void __destroy(_ForwardIterator, _ForwardIterator)
	{}
};

/**
 * Destroy a range of objects. If the value_type of the object has
 * a trivial destructor, the compiler should optimize all of this
 * away, otherwise the objects' destructors must be invoked.
 */
template<typename _ForwardIterator>
inline void destroy(_ForwardIterator __first, _ForwardIterator __last)
{
	__destroy_aux<
#if __cplusplus >= 201103L
		std::is_trivially_destructible<typename std::iterator_traits<_ForwardIterator>::value_type>::value
#else
		false
#endif
	>::__destroy(__first, __last);
}

template<typename _ForwardIterator, typename _Allocator>
void destroy(_ForwardIterator __first, _ForwardIterator __last, _Allocator& __alloc)
{
	for (; __first != __last; ++__first)
		__alloc.destroy(*__first);
}


template<typename _Tp>
struct __default_delete
{
	inline static void __delete(_Tp* p)
	{
		::delete p;
	}
};

template<typename _Tp>
struct __default_delete<_Tp[]>
{
	inline static void __delete(_Tp* p)
	{
		::delete[] p;
	}
};

template<typename _T>
inline void default_delete(_T* p)
{ __default_delete<_T>::__delete(p); }

template<typename _T>
inline void default_delete_then_zero(_T*& p)
{
	default_delete<_T>(p);
	p = 0;
}

template<typename _ForwardIterator>
inline void default_delete(_ForwardIterator __first, _ForwardIterator __last)
{
	for (; __first != __last; ++__first)
		default_delete(*__first);
}

template<typename _ForwardIterator>
inline void default_delete_then_zero(_ForwardIterator __first, _ForwardIterator __last)
{
	for (; __first != __last; ++__first)
		default_delete_then_zero(*__first);
}

template<typename _Tp>
struct __deallocate
{
	inline static void __dealloc(_Tp* p)
	{
		::operator delete(p);
	}
};

template<typename _Tp>
struct __deallocate<_Tp[]>
{
	inline static void __dealloc(_Tp* p)
	{
		::operator delete[](p);
	}
};

template<typename _T>
inline void deallocate(_T* p, std::size_t = 1)
{ __deallocate<_T>::__dealloc(p); }

template<typename _T>
inline void deallocate_then_zero(_T*& p, std::size_t = 1)
{
	deallocate<_T>(p);
	p = 0;
}

template<typename _ForwardIterator>
inline void deallocate(_ForwardIterator __first, _ForwardIterator __last)
{
	for (; __first != __last; ++__first)
		deallocate(*__first);
}

template<typename _ForwardIterator>
inline void deallocate_then_zero(_ForwardIterator __first, _ForwardIterator __last)
{
	for (; __first != __last; ++__first)
		deallocate_then_zero(*__first);
}


///wrapper of delete keyword
template<typename _Tp>
struct default_delete_wrapper
{
	CPP_CONSTEXPR default_delete_wrapper()
	{}

	template<typename _Up>
	CPP_CONSTEXPR default_delete_wrapper(const default_delete_wrapper<_Up>&)
	{}

	void operator()(_Tp* ptr) const
	{
		default_delete<>(ptr);
	}
};

///wrapper of delete keyword and set 0 in ptr
template<typename _Tp>
struct default_delete_then_zero_wrapper
{
	CPP_CONSTEXPR default_delete_then_zero_wrapper()
	{}

	template<typename _Up>
	CPP_CONSTEXPR default_delete_then_zero_wrapper(const default_delete_then_zero_wrapper<_Up>&)
	{}

	void operator()(_Tp*& ptr) const
	{
		default_delete_then_zero<_Tp>(ptr);
	}
};

///wrapper of destructor (ptr->~_Tp())
template<typename _Tp>
struct destroy_wrapper
{
	CPP_CONSTEXPR destroy_wrapper()
	{}

	template<typename _Up>
	CPP_CONSTEXPR destroy_wrapper(const destroy_wrapper<_Up>&)
	{}

	template<typename _ForwardIterator>
	void operator()(_ForwardIterator __first, _ForwardIterator __last) const
	{
		destroy<>(__first, __last);
	}

	template<typename _ForwardIterator, typename _Allocator>
	void operator()(_ForwardIterator __first, _ForwardIterator __last, _Allocator& __alloc) const
	{
		destroy<>(__first, __last, __alloc);
	}

	void operator()(_Tp* p) const
	{
		destroy<_Tp>(p);
	}
};

///wrapper of operator delete
template<typename _Tp>
struct deallocate_wrapper
{
	CPP_CONSTEXPR deallocate_wrapper()
	{}

	template<typename _Up>
	CPP_CONSTEXPR deallocate_wrapper(const deallocate_wrapper<_Up>&)
	{}

	void operator()(_Tp* ptr, std::size_t = 1) const
	{
		deallocate(ptr);
	}
};


///wrapper of operator delete and set 0 in ptr
template<typename _Tp>
struct deallocate_then_zero_wrapper
{
	CPP_CONSTEXPR deallocate_then_zero_wrapper()
	{}

	template<typename _Up>
	CPP_CONSTEXPR deallocate_then_zero_wrapper(const deallocate_then_zero_wrapper<_Up>&)
	{}

	void operator()(_Tp*& ptr, std::size_t = 1) const
	{
		deallocate_then_zero<>(ptr);
	}
};

}

#endif