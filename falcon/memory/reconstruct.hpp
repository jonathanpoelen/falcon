#ifndef _FALCON_MEMORY_RECONSTRUCT_HPP
#define _FALCON_MEMORY_RECONSTRUCT_HPP

#include <falcon/memory/construct.hpp>
#include <falcon/memory/destroy.hpp>

//reconstruct, renew, emplace_new, nothrow_renew, nothrow_emplace_new
//reconstruct_wrapper, renew_wrapper, emplace_new_wrapper, nothrow_renew_wrapper, nothrow_emplace_new_wrapper

namespace falcon {

#ifdef __GXX_EXPERIMENTAL_CXX0X__
template<typename _T, typename... _Args>
inline void reconstruct(_T* p, _Args&&... args)
{
	destroy(p);
	construct(p, std::forward<_Args>(args)...);
}
#else
template<typename _T>
inline void reconstruct(_T* p)
{
	destroy(p);
	construct(p);
}
template<typename _T, typename _U>
inline void reconstruct(_T* p, const _U& value)
{
	destroy(p);
	construct(p, value);
}
#endif

#ifdef __GXX_EXPERIMENTAL_CXX0X__
template<typename _T, typename... _Args>
inline _T* renew(_T* p, _Args&&... args)
{
	default_delete(p);
	return p = default_new<_T>(std::forward<_Args>(args)...);
}

template<typename _T, typename... _Args>
inline _T* nothrow_renew(_T* p, _Args&&... args)
{
	default_delete(p);
	return p = nothrow_default_new<_T>(std::forward<_Args>(args)...);
}
#else
template<typename _T>
inline _T* renew(_T* p)
{
	default_delete(p);
	return p = default_new<_T>();
}
template<typename _T, typename _U>
inline _T* renew(_T* p, const _U& value)
{
	default_delete(p);
	return p = default_new<_T>(value);
}

template<typename _T>
inline _T* nothrow_renew(_T* p)
{
	default_delete(p);
	return p = nothrow_default_new<_T>();
}
template<typename _T, typename _U>
inline _T* nothrow_renew(_T* p, const _U& value)
{
	default_delete(p);
	return p = nothrow_default_new<_T>(value);
}
#endif

#ifdef __GXX_EXPERIMENTAL_CXX0X__
template<typename _T, typename... _Args>
inline void emplace_new(_T*& p, _Args&&... args)
{
	if (p)
		reconstruct<>(p, std::forward<_Args>(args)...);
	else
		p = default_new<_T>(std::forward<_Args>(args)...);
}

template<typename _T, typename... _Args>
inline void nothrow_emplace_new(_T*& p, _Args&&... args)
{
	if (p)
		reconstruct<>(p, std::forward<_Args>(args)...);
	else
		p = nothrow_default_new<_T>(std::forward<_Args>(args)...);
}
#else
template<typename _T>
inline void emplace_new(_T*& p)
{
	if (p)
		reconstruct<>(p);
	else
		p = default_new<_T>();
}
template<typename _T, typename _U>
inline void emplace_new(_T*& p, const _U& value)
{
	if (p)
		reconstruct<>(p, value);
	else
		p = default_new<_T>(value);
}

template<typename _T>
inline void nothrow_emplace_new(_T*& p)
{
	if (p)
		reconstruct<>(p);
	else
		p = nothrow_default_new<_T>();
}
template<typename _T, typename _U>
inline void nothrow_emplace_new(_T*& p, const _U& value)
{
	if (p)
		reconstruct<>(p, value);
	else
		p = nothrow_default_new<_T>(value);
}
#endif


///wrapper of destructor then constructor
template<typename _Tp>
struct reconstruct_wrapper
{
	CPP_CONSTEXPR reconstruct_wrapper()
	{}

	template<typename _Up>
	CPP_CONSTEXPR reconstruct_wrapper(const reconstruct_wrapper<_Up>&)
	{}

	void operator()(_Tp* ptr) const
	{
		reconstruct<>(ptr);
	}

	void operator()(_Tp* ptr, const _Tp& v) const
	{
		reconstruct<>(ptr, v);
	}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	template<typename... _Args>
	void operator()(_Tp* ptr, _Args&&... args) const
	{
		reconstruct<>(ptr, std::forward<_Args>(args)...);
	}
#endif
};


///wrapper of new then delete
template<typename _Tp>
struct renew_wrapper
{
	CPP_CONSTEXPR renew_wrapper()
	{}

	template<typename _Up>
	CPP_CONSTEXPR renew_wrapper(const renew_wrapper<_Up>&)
	{}

	_Tp* operator()(_Tp*& ptr) const
	{
		return renew<>(ptr);
	}

	_Tp* operator()(_Tp*& ptr, const _Tp& v) const
	{
		return renew<>(ptr, v);
	}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	template<typename... _Args>
	_Tp* operator()(_Tp*& ptr, _Args&&... args) const
	{
		return renew<>(ptr, std::forward<_Args>(args)...);
	}
#endif

	_Tp* operator()(_Tp*& ptr, const std::nothrow_t& nothrow) const
	{
		return nothrow_renew<>(ptr);
	}

	_Tp* operator()(_Tp*& ptr, const std::nothrow_t& nothrow, const _Tp& v) const
	{
		return nothrow_renew<>(ptr, v);
	}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	template<typename... _Args>
	_Tp* operator()(_Tp*& ptr, const std::nothrow_t& nothrow, _Args&&... args) const
	{
		return nothrow_renew<>(ptr, std::forward<_Args>(args)...);
	}
#endif
};

template<typename _Tp>
struct nothrow_renew_wrapper
{
	CPP_CONSTEXPR nothrow_renew_wrapper()
	{}

	template<typename _Up>
	CPP_CONSTEXPR nothrow_renew_wrapper(const nothrow_renew_wrapper<_Up>&)
	{}

	_Tp* operator()(_Tp*& ptr) const
	{
		return nothrow_renew<>(ptr);
	}

	_Tp* operator()(_Tp*& ptr, const _Tp& v) const
	{
		return nothrow_renew<>(ptr, v);
	}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	template<typename... _Args>
	_Tp* operator()(_Tp*& ptr, _Args&&... args) const
	{
		return nothrow_renew<>(ptr, std::forward<_Args>(args)...);
	}
#endif
};

///if ptr is null, use new keyword, else reconstruct_wrapper
template<typename _Tp>
struct emplace_new_wrapper
{
	CPP_CONSTEXPR emplace_new_wrapper()
	{}

	template<typename _Up>
	CPP_CONSTEXPR emplace_new_wrapper(const emplace_new_wrapper<_Up>&)
	{}

	void operator()(_Tp*& ptr) const
	{
		emplace_new<>(ptr);
	}

	void operator()(_Tp*& ptr, const _Tp& v) const
	{
		emplace_new<>(ptr, v);
	}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	template<typename... _Args>
	void operator()(_Tp*& ptr, _Args&&... args) const
	{
		emplace_new<>(ptr, std::forward<_Args>(args)...);
	}
#endif

	void operator()(_Tp*& ptr, const std::nothrow_t& nothrow) const
	{
		nothrow_emplace_new<>(ptr);
	}

	void operator()(_Tp*& ptr, const std::nothrow_t& nothrow, const _Tp& v) const
	{
		nothrow_emplace_new<>(ptr, v);
	}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	template<typename... _Args>
	void operator()(_Tp*& ptr, const std::nothrow_t& nothrow, _Args&&... args) const
	{
		nothrow_emplace_new<>(ptr, std::forward<_Args>(args)...);
	}
#endif
};

template<typename _Tp>
struct nothrow_emplace_new_wrapper
{
	CPP_CONSTEXPR nothrow_emplace_new_wrapper()
	{}

	template<typename _Up>
	CPP_CONSTEXPR nothrow_emplace_new_wrapper(const nothrow_emplace_new_wrapper<_Up>&)
	{}

	void operator()(_Tp*& ptr) const
	{
		nothrow_emplace_new<>(ptr);
	}

	void operator()(_Tp*& ptr, const _Tp& v) const
	{
		nothrow_emplace_new<>(ptr, v);
	}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	template<typename... _Args>
	void operator()(_Tp*& ptr, _Args&&... args) const
	{
		nothrow_emplace_new<>(ptr, std::forward<_Args>(args)...);
	}
#endif
};

}

#endif