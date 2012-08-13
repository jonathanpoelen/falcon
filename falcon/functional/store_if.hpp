#ifndef _FALCON_FUNCTIONAL_STORE_IF_HPP
#define _FALCON_FUNCTIONAL_STORE_IF_HPP

namespace falcon {

template <typename _T, typename _Functor, typename _Access = void>
struct store_if
{
	typedef _T* pointer_type;
	typedef const _T* const_pointer_type;

private:
	_Functor _functor;
	_Access _access;
	pointer_type _marchandise;

public:
	store_if(_Functor functor, _Access access, pointer_type p = 0)
	: _functor(functor)
	, _access(access)
	, _marchandise(p)
	{}

	store_if(_Functor functor, pointer_type p = 0)
	: _functor(functor)
	, _access()
	, _marchandise(p)
	{}

	store_if(pointer_type p = 0)
	: _functor()
	, _access()
	, _marchandise(p)
	{}

	template<typename _U>
	bool operator()(_U& value)
	{
		if (_functor(value))
		{
			_marchandise = _access(value);
			return true;
		}
		return false;
	}

	pointer_type get()
	{
		return _marchandise;
	}
	const_pointer_type get() const
	{
		return _marchandise;
	}

	void set(pointer_type p)
	{
		_marchandise = p;
	}

	void clear()
	{
		_marchandise = 0;
	}
};

template <typename _T, typename _Functor, typename _Access = void>
struct store_if_not
{
	typedef _T* pointer_type;
	typedef const _T* const_pointer_type;

private:
	_Functor _functor;
	_Access _access;
	pointer_type _marchandise;

public:
	store_if_not(_Functor functor, _Access access, pointer_type p = 0)
	: _functor(functor)
	, _access(access)
	, _marchandise(p)
	{}

	store_if_not(_Functor functor, pointer_type p = 0)
	: _functor(functor)
	, _access()
	, _marchandise(p)
	{}

	store_if_not(pointer_type p = 0)
	: _functor()
	, _access()
	, _marchandise(p)
	{}

	template<typename _U>
	bool operator()(_U& value)
	{
		if (!_functor(value))
		{
			_marchandise = _access(value);
			return false;
		}
		return true;
	}

	pointer_type get()
	{
		return _marchandise;
	}
	const_pointer_type get() const
	{
		return _marchandise;
	}

	void set(pointer_type p)
	{
		_marchandise = p;
	}

	void clear()
	{
		_marchandise = 0;
	}
};

template <typename _T, typename _Functor>
struct store_if<_T, _Functor, void>
{
	typedef _T* pointer_type;
	typedef const _T* const_pointer_type;

private:
	_Functor _functor;
	pointer_type _marchandise;

public:
	store_if(_Functor functor, pointer_type p = 0)
	: _functor(functor)
	, _marchandise(p)
	{}

	store_if(pointer_type p = 0)
	: _functor()
	, _marchandise(p)
	{}

	template<typename _U>
	bool operator()(_U& value)
	{
		if (_functor(value))
		{
			_marchandise = &value;
			return true;
		}
		return false;
	}

	pointer_type get()
	{
		return _marchandise;
	}
	const_pointer_type get() const
	{
		return _marchandise;
	}

	void set(pointer_type p)
	{
		_marchandise = p;
	}

	void clear()
	{
		_marchandise = 0;
	}
};

template <typename _T, typename _Functor>
struct store_if_not<_T, _Functor, void>
{
	typedef _T* pointer_type;
	typedef const _T* const_pointer_type;

private:
	_Functor _functor;
	pointer_type _marchandise;

public:
	store_if_not(_Functor functor, pointer_type p = 0)
	: _functor(functor)
	, _marchandise(p)
	{}

	store_if_not(pointer_type p = 0)
	: _functor()
	, _marchandise(p)
	{}

	template<typename _U>
	bool operator()(_U& value)
	{
		if (!_functor(value))
		{
			_marchandise = &value;
			return false;
		}
		return true;
	}

	pointer_type get()
	{
		return _marchandise;
	}
	const_pointer_type get() const
	{
		return _marchandise;
	}

	void set(pointer_type p)
	{
		_marchandise = p;
	}

	void clear()
	{
		_marchandise = 0;
	}
};

}

#endif
