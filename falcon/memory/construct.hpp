#ifndef _FALCON_MEMORY_CONSTRUCT_HPP
#define _FALCON_MEMORY_CONSTRUCT_HPP

#if __cplusplus >= 201103L
# include <utility>
# include <falcon/utility/detail/construct_category.hpp>
#endif
#include <type_traits>
#include <new>
#include <falcon/c++/constexpr.hpp>

//construct, default_new, nothrow_default_new, allocate, nothrow_allocate
//construct_wrapper, default_new_wrapper, nothrow_default_new_wrapper, allocate_wrapper, nothrow_allocate_wrapper

namespace falcon {

template<bool>
struct __construct
{
	template<typename _T, typename _U>
	inline static void __cons(_T* p, const _U& value)
	{ ::new(p) _T(value); }
};

template<>
struct __construct<true>
{
	template<typename _T, typename _U>
	inline static void __cons(_T* p, const _U& value)
	{ *p = value; }
};

/**
 * Constructs an object in existing memory by invoking an allocated
 * object's constructor with an initializer.
 */
template<typename _T>
inline void construct(_T* p)
{ ::new(p) _T(); }

template<typename _T, typename _U>
inline void construct(_T* p, const _U& value)
{
	__construct<
#if __cplusplus >= 201103L
		std::has_trivial_default_constructor<_T>::value
#else
		false
#endif
	>::__cons(p, value);
}

#if __cplusplus >= 201103L
template<typename _T, typename... _Args>
inline void __construct2(const falcon::detail::normal_construct_tag&,
						 typename std::remove_extent<_T>::type* p,
						 _Args&&... args)
{ ::new(p) _T{std::forward<_Args>(args)...}; }

template<typename _T, typename... _Args>
inline void __construct2(const falcon::detail::initilizer_list_construct_tag&,
						 typename std::remove_extent<_T>::type* p,
						 _Args&&... args)
{ ::new(p) _T{{std::forward<_Args>(args)...}}; }

template<typename _T, typename... _Args>
inline void construct(_T* p, _Args&&... args)
{
	typedef typename falcon::detail::construct_category<_T>::type __construct_category;
	__construct2<_T>(__construct_category(),
					 p, std::forward<_Args>(args)...);
}

template<typename _T, typename... _Args>
inline typename std::remove_extent<_T>::type*
__default_new(const falcon::detail::normal_construct_tag&,
			  _Args&&... args)
{ return ::new _T{std::forward<_Args>(args)...}; }

template<typename _T, typename... _Args>
inline typename std::remove_extent<_T>::type*
__default_new(const falcon::detail::initilizer_list_construct_tag&,
			  _Args&&... args)
{ return ::new _T{{std::forward<_Args>(args)...}}; }

template<typename _T, typename... _Args>
inline typename std::remove_extent<_T>::type* default_new(_Args&&... args)
{
	typedef typename falcon::detail::construct_category<_T>::type __construct_category;
	return __default_new<_T>(__construct_category(),
							 std::forward<_Args>(args)...);
}


template<typename _T, typename... _Args>
inline typename std::remove_extent<_T>::type*
__nothrow_default_new(const falcon::detail::normal_construct_tag&,
					  _Args&&... args)
{ return ::new (std::nothrow) _T{std::forward<_Args>(args)...}; }

template<typename _T, typename... _Args>
inline typename std::remove_extent<_T>::type*
__nothrow_default_new(const falcon::detail::initilizer_list_construct_tag&,
					  _Args&&... args)
{ return ::new (std::nothrow) _T{{std::forward<_Args>(args)...}}; }

template<typename _T, typename... _Args>
inline typename std::remove_extent<_T>::type*
nothrow_default_new(_Args&&... args)
{
	typedef typename falcon::detail::construct_category<_T>::type __construct_category;
	return __nothrow_default_new<_T>(__construct_category(),
									 std::forward<_Args>(args)...);
}
#else

template<typename _T>
inline _T* default_new()
{ return ::new _T(); }
template<typename _T, typename _U>
inline _T* default_new(const _U& value)
{ return ::new _T(value); }

template<typename _T>
inline _T* nothrow_default_new()
{ return ::new (std::nothrow) _T(); }
template<typename _T, typename _U>
inline _T* nothrow_default_new(const _U& value)
{ return ::new (std::nothrow) _T(value); }
#endif

template<typename _T>
inline _T* allocate()
{ return static_cast<_T*>(::operator new(sizeof(_T))); }

template<typename _T>
inline _T* nothrow_allocate()
{ return static_cast<_T*>(::operator new(sizeof(_T), std::nothrow)); }

template<typename _T>
inline _T* allocate(std::size_t n)
{
	if (n > (std::size_t(-1) / sizeof(_T)))
		std::bad_alloc();
	return static_cast<_T*>(::operator new(sizeof(_T) * n));
}

template<typename _T>
inline _T* nothrow_allocate(std::size_t n)
{
	if (n > (std::size_t(-1) / sizeof(_T)))
		std::bad_alloc();
	return static_cast<_T*>(::operator new(sizeof(_T) * n, std::nothrow));
}


///wrapper of constructor (new (ptr) _Tp())
template<typename _Tp>
struct construct_wrapper
{
	CPP_CONSTEXPR construct_wrapper()
	{}

	template<typename _Up>
	CPP_CONSTEXPR construct_wrapper(const construct_wrapper<_Up>&)
	{}

	void operator()(_Tp* ptr) const
	{
		construct<>(ptr);
	}

	template<typename _U>
	void operator()(_Tp* ptr, const _U& v) const
	{
		construct<>(ptr, v);
	}

#if __cplusplus >= 201103L
	template<typename... _Args>
	void operator()(_Tp* ptr, _Args&&... args) const
	{
		construct<>(ptr, std::forward<_Args>(args)...);
	}
#endif
};

///wrapper of new keyword
template<typename _Tp>
struct default_new_wrapper
{
	CPP_CONSTEXPR default_new_wrapper()
	{}

	template<typename _Up>
	CPP_CONSTEXPR default_new_wrapper(const default_new_wrapper<_Up>&)
	{}

	_Tp* operator()() const
	{
		return default_new<_Tp>();
	}

	template<typename _U>
	_Tp* operator()(const _U& v) const
	{
		return default_new<_Tp>(v);
	}

#if __cplusplus >= 201103L
	template<typename... _Args>
	_Tp* operator()(_Args&&... args) const
	{
		return default_new<_Tp>(std::forward<_Args>(args)...);
	}
#endif

	_Tp* operator()(const std::nothrow_t& nothrow) const
	{
		return nothrow_default_new<_Tp>();
	}

	_Tp* operator()(const std::nothrow_t& nothrow, const _Tp& v) const
	{
		return nothrow_default_new<_Tp>(v);
	}

#if __cplusplus >= 201103L
	template<typename... _Args>
	_Tp* operator()(const std::nothrow_t& nothrow, _Args&&... args) const
	{
		return nothrow_default_new<_Tp>(std::forward<_Args>(args)...);
	}
#endif
};

template<typename _Tp>
struct nothrow_default_new_wrapper
{
	CPP_CONSTEXPR nothrow_default_new_wrapper()
	{}

	template<typename _Up>
	CPP_CONSTEXPR nothrow_default_new_wrapper(const nothrow_default_new_wrapper<_Up>&)
	{}

	_Tp* operator()() const
	{
		return nothrow_default_new<_Tp>();
	}

	_Tp* operator()(const _Tp& v) const
	{
		return nothrow_default_new<_Tp>(v);
	}

#if __cplusplus >= 201103L
	template<typename... _Args>
	_Tp* operator()(_Args&&... args) const
	{
		return nothrow_default_new<_Tp>(std::forward<_Args>(args)...);
	}
#endif
};

///wrapper of operator new
template<typename _Tp>
struct allocate_wrapper
{
	CPP_CONSTEXPR allocate_wrapper()
	{}

	template<typename _Up>
	CPP_CONSTEXPR allocate_wrapper(const allocate_wrapper<_Up>&)
	{}

	_Tp* operator()(_Tp*& ptr) const
	{
		return ptr = (*this)();
	}

	_Tp* operator()(_Tp*& ptr, std::size_t n) const
	{
		return ptr = (*this)(n);
	}

	_Tp* operator()(_Tp*& ptr, const std::nothrow_t& nothrow) const
	{
		return ptr = (*this)(nothrow);
	}

	_Tp* operator()(_Tp*& ptr, std::size_t n, const std::nothrow_t& nothrow) const
	{
		return ptr = (*this)(n, nothrow);
	}

	_Tp* operator()(std::size_t n) const
	{
		return allocate<_Tp>(n);
	}

	_Tp* operator()() const
	{
		return allocate<_Tp>();
	}

	_Tp* operator()(std::size_t n, const std::nothrow_t& nothrow) const
	{
		return nothrow_allocate<_Tp>(n);
	}

	_Tp* operator()(const std::nothrow_t& nothrow) const
	{
		return nothrow_allocate<_Tp>();
	}
};

template<typename _Tp>
struct nothrow_allocate_wrapper
{
	CPP_CONSTEXPR nothrow_allocate_wrapper()
	{}

	template<typename _Up>
	CPP_CONSTEXPR nothrow_allocate_wrapper(const nothrow_allocate_wrapper<_Up>&)
	{}

	_Tp* operator()(_Tp*& ptr) const
	{
		return ptr = (*this)();
	}

	_Tp* operator()(_Tp*& ptr, std::size_t n) const
	{
		return ptr = (*this)(n);
	}

	_Tp* operator()(std::size_t n) const
	{
		return nothrow_allocate<_Tp>(n);
	}

	_Tp* operator()() const
	{
		return nothrow_allocate<_Tp>();
	}
};

}

#endif