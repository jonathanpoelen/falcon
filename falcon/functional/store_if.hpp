#ifndef _FALCON_FUNCTIONAL_STORE_IF_HPP
#define _FALCON_FUNCTIONAL_STORE_IF_HPP

#include <falcon/cast/static_caster.hpp>

namespace falcon {

struct __store_if_accessor
{
	template <typename _T>
	_T* operator()(_T& x) const
	{ return &x; }

	template <typename _T>
	const _T* operator()(const _T& x) const
	{ return &x; }
};

template <
	typename _T,
	typename _Functor = static_caster<bool>,
	typename _Access = __store_if_accessor,
	bool _IsNot = false
>
struct __store_if
{
	typedef _T value_type;
	typedef _T* pointer_type;
	typedef const _T* const_pointer_type;
	typedef _Functor functor_type;
	typedef _Access accessor_type;

private:
	_Functor _functor;
	_Access _access;
	pointer_type _marchandise;

public:
	__store_if(_Functor functor, _Access access, pointer_type p = 0)
	: _functor(functor)
	, _access(access)
	, _marchandise(p)
	{}

	__store_if(_Functor functor, pointer_type p = 0)
	: _functor(functor)
	, _access()
	, _marchandise(p)
	{}

	__store_if(pointer_type p = 0)
	: _functor()
	, _access()
	, _marchandise(p)
	{}

	template<typename _U>
	bool operator()(_U& value)
	{
		if (_IsNot ? !_functor(value) : _functor(value))
		{
			_marchandise = _access(value);
			return true;
		}
		return false;
	}

	template<typename _U>
	bool operator()(_U& value) const
	{
		if (_IsNot ? !_functor(value) : _functor(value))
		{
			_marchandise = _access(value);
			return true;
		}
		return false;
	}

	pointer_type get()
	{ return _marchandise; }

	const_pointer_type get() const
	{ return _marchandise; }

	void set(pointer_type p)
	{ _marchandise = p; }

	void clear()
	{ _marchandise = 0; }
};

#ifdef __GXX_EXPERIMENTAL_CXX0X__
template <
	typename _T,
	typename _Functor = static_caster<bool>,
	typename _Access = __store_if_accessor
>
using store_if = __store_if<_T, _Functor, _Access>;

template <
	typename _T,
	typename _Functor = static_caster<bool>,
	typename _Access = __store_if_accessor
>
using store_if_not = __store_if<_T, _Functor, _Access, true>;
#else
template <
	typename _T,
	typename _Functor = static_caster<bool>,
	typename _Access = __store_if_accessor
>
struct store_if
: __store_if<_T, _Functor, _Access>
{
private:
	typedef __store_if<_T, _Functor, _Access> __base;

public:
	store_if(_Functor functor, _Access access, pointer_type p = 0)
	: __base(functor, access, p)
	{}

	store_if(_Functor functor, pointer_type p = 0)
	: __base(functor, p)
	{}

	store_if(pointer_type p = 0)
	: __base(p)
	{}
};

template <
	typename _T,
	typename _Functor = static_caster<bool>,
	typename _Access = __store_if_accessor
>
struct store_if_not
: __store_if<_T, _Functor, _Access, true>
{
private:
	typedef __store_if<_T, _Functor, _Access, true> __base;

public:
	store_if_not(_Functor functor, _Access access, pointer_type p = 0)
	: __base(functor, access, p)
	{}

	store_if_not(_Functor functor, pointer_type p = 0)
	: __base(functor, p)
	{}

	store_if_not(pointer_type p = 0)
	: __base(p)
	{}
};
#endif

}

#endif
