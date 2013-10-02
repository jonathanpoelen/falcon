#ifndef FALCON_MEMORY_CONSTRUCT_HPP
#define FALCON_MEMORY_CONSTRUCT_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/tuple/array_compatibility.hpp>
#include <type_traits>
#include <new>

#if __cplusplus >= 201103L
# include <falcon/parameter/parameter_index.hpp>
# include <falcon/memory/construct_category.hpp>
# include <falcon/tuple/detail/tuplefwd.hpp>
# include <utility>
#endif

//construct, default_new, nothrow_default_new, allocate, nothrow_allocate
//construct_wrapper, default_new_wrapper, nothrow_default_new_wrapper, allocate_wrapper, nothrow_allocate_wrapper

namespace falcon {

/**
 * Constructs an object in existing memory by invoking an allocated
 * object's constructor with an initializer.
 */
template<typename T>
void construct(T* p)
{ ::new(p) T(); }

template<typename T>
T* default_new()
{ return ::new T(); }

template<typename T>
T* nothrow_default_new()
{ return ::new (std::nothrow) T(); }

#if __cplusplus >= 201103L
template<typename T, typename... Args>
void __construct2(const normal_ctor_tag&, T* p, Args&&... args)
{ ::new(p) T(std::forward<Args>(args)...); }

template<typename T, typename... Args>
void __construct2(const brace_init_tag&, T* p, Args&&... args)
{ ::new(p) T{std::forward<Args>(args)...}; }

template<typename T>
void __construct2(const brace_init_tag&, T* p, T&& val)
{ ::new(p) T(std::forward<T>(val)); }

template<typename T>
void __construct2(const brace_init_tag&, T* p, const T& val)
{ ::new(p) T(val); }

template<typename T, typename... Args>
void __construct2(const double_brace_init_tag&, T* p, Args&&... args)
{ ::new(p) T{{std::forward<Args>(args)...}}; }

template<typename T, std::size_t... Indexes>
void __dispatch_construct2(T* p, T&& val, falcon::parameter_index<Indexes...>)
{ ::new(p) T{get<Indexes>(std::forward<T>(val))...}; }

template<typename T>
void __construct2(const dispatch_index_tag&, T* p, T&& val)
{
	__dispatch_construct2<T>(
		p, std::forward<T>(val),
		typename falcon::build_parameter_index<std::tuple_size<T>::value>::type()
	);
}

template<typename T, std::size_t... Indexes>
void __dispatch_construct2(T* p, const T& val, falcon::parameter_index<Indexes...>)
{ ::new(p) T{get<Indexes>(val)...}; }

template<typename T>
void __construct2(const dispatch_index_tag&, T* p, const T& val)
{
	__dispatch_construct2<T>(
		p, val,
		typename falcon::build_parameter_index<std::tuple_size<T>::value>::type()
	);
}

template<typename T, typename... Args>
void __construct2(const dispatch_index_tag&, T* p, Args&&... args)
{
	::new(p) T{std::forward<Args>(args)...};
}

template<typename T, typename... Args>
void construct(T* p, Args&&... args)
{
	typedef typename construct_category<T>::type __construct_category;
	__construct2<T>(__construct_category(), p, std::forward<Args>(args)...);
}


template<typename T, typename... Args>
T* default_new(Args&&... args)
{
	T* ret = static_cast<T*>(::operator new(sizeof(T)));
	struct Free {
		T* ptr;
		~Free() { ::operator delete(ptr); }
	} autofree{ret};
	construct(ret, std::forward<Args>(args)...);
	autofree.ptr = nullptr;
	return ret;
}


template<typename T, typename... Args>
T*
nothrow_default_new(Args&&... args)
{
	T* ret = static_cast<T*>(::operator new(sizeof(T), std::nothrow));
	if (ret) {
		struct Free {
			T* ptr;
			~Free() { ::operator delete(ptr, std::nothrow); }
		} autofree{ret};
		construct(ret, std::forward<Args>(args)...);
		autofree.ptr = nullptr;
	}
	return ret;
}

#else
template<typename T, typename U>
void construct(T* p, const U& value)
{ ::new(p) T(value); }

template<typename T, typename U>
T* default_new(const U& value)
{ return ::new T(value); }

template<typename T, typename U>
T* nothrow_default_new(const U& value)
{ return ::new (std::nothrow) T(value); }
#endif

template<typename T>
T* allocate()
{ return static_cast<T*>(::operator new(sizeof(T))); }

template<typename T>
T* nothrow_allocate()
{ return static_cast<T*>(::operator new(sizeof(T), std::nothrow)); }

template<typename T>
T* allocate(std::size_t n)
{
	if (n > (std::size_t(-1) / sizeof(T)))
		std::bad_alloc();
	return static_cast<T*>(::operator new(sizeof(T) * n));
}

template<typename T>
T* nothrow_allocate(std::size_t n)
{
	if (n > (std::size_t(-1) / sizeof(T)))
		std::bad_alloc();
	return static_cast<T*>(::operator new(sizeof(T) * n, std::nothrow));
}


///wrapper of constructor (new (ptr) Tp())
template<typename Tp>
struct construct_wrapper
{
	CPP_CONSTEXPR construct_wrapper()
	{}

	template<typename Up>
	CPP_CONSTEXPR construct_wrapper(const construct_wrapper<Up>&)
	{}

	void operator()(Tp* ptr) const
	{
		construct<>(ptr);
	}

#if __cplusplus >= 201103L
	template<typename... Args>
	void operator()(Tp* ptr, Args&&... args) const
	{
		construct<>(ptr, std::forward<Args>(args)...);
	}
#else
	template<typename U>
	void operator()(Tp* ptr, const U& v) const
	{
		construct<>(ptr, v);
	}
#endif
};

///wrapper of new keyword
template<typename Tp>
struct default_new_wrapper
{
	CPP_CONSTEXPR default_new_wrapper()
	{}

	template<typename Up>
	CPP_CONSTEXPR default_new_wrapper(const default_new_wrapper<Up>&)
	{}

	Tp* operator()() const
	{
		return default_new<Tp>();
	}

#if __cplusplus >= 201103L
	template<typename... Args>
	Tp* operator()(Args&&... args) const
	{
		return default_new<Tp>(std::forward<Args>(args)...);
	}
#else
	template<typename U>
	Tp* operator()(const U& v) const
	{
		return default_new<Tp>(v);
	}
#endif

	Tp* operator()(const std::nothrow_t& nothrow) const
	{
		return nothrow_default_new<Tp>();
	}

#if __cplusplus >= 201103L
	template<typename... Args>
	Tp* operator()(const std::nothrow_t& nothrow, Args&&... args) const
	{
		return nothrow_default_new<Tp>(std::forward<Args>(args)...);
	}
#else
	Tp* operator()(const std::nothrow_t& nothrow, const Tp& v) const
	{
		return nothrow_default_new<Tp>(v);
	}
#endif
};

template<typename Tp>
struct nothrow_default_new_wrapper
{
	CPP_CONSTEXPR nothrow_default_new_wrapper()
	{}

	template<typename Up>
	CPP_CONSTEXPR nothrow_default_new_wrapper(const nothrow_default_new_wrapper<Up>&)
	{}

	Tp* operator()() const
	{
		return nothrow_default_new<Tp>();
	}

#if __cplusplus >= 201103L
	template<typename... Args>
	Tp* operator()(Args&&... args) const
	{
		return nothrow_default_new<Tp>(std::forward<Args>(args)...);
	}
#else
	Tp* operator()(const Tp& v) const
	{
		return nothrow_default_new<Tp>(v);
	}
#endif
};

///wrapper of operator new
template<typename Tp>
struct allocate_wrapper
{
	CPP_CONSTEXPR allocate_wrapper()
	{}

	template<typename Up>
	CPP_CONSTEXPR allocate_wrapper(const allocate_wrapper<Up>&)
	{}

	Tp* operator()(Tp*& ptr) const
	{
		return ptr = (*this)();
	}

	Tp* operator()(Tp*& ptr, std::size_t n) const
	{
		return ptr = (*this)(n);
	}

	Tp* operator()(Tp*& ptr, const std::nothrow_t& nothrow) const
	{
		return ptr = (*this)(nothrow);
	}

	Tp* operator()(Tp*& ptr, std::size_t n, const std::nothrow_t& nothrow) const
	{
		return ptr = (*this)(n, nothrow);
	}

	Tp* operator()(std::size_t n) const
	{
		return allocate<Tp>(n);
	}

	Tp* operator()() const
	{
		return allocate<Tp>();
	}

	Tp* operator()(std::size_t n, const std::nothrow_t& nothrow) const
	{
		return nothrow_allocate<Tp>(n);
	}

	Tp* operator()(const std::nothrow_t& nothrow) const
	{
		return nothrow_allocate<Tp>();
	}
};

template<typename Tp>
struct nothrow_allocate_wrapper
{
	CPP_CONSTEXPR nothrow_allocate_wrapper()
	{}

	template<typename Up>
	CPP_CONSTEXPR nothrow_allocate_wrapper(const nothrow_allocate_wrapper<Up>&)
	{}

	Tp* operator()(Tp*& ptr) const
	{
		return ptr = (*this)();
	}

	Tp* operator()(Tp*& ptr, std::size_t n) const
	{
		return ptr = (*this)(n);
	}

	Tp* operator()(std::size_t n) const
	{
		return nothrow_allocate<Tp>(n);
	}

	Tp* operator()() const
	{
		return nothrow_allocate<Tp>();
	}
};

}

#endif
