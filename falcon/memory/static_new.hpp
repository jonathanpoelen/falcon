#ifndef _FALCON_MEMORY_STATIC_NEW_HPP
#define _FALCON_MEMORY_STATIC_NEW_HPP

#include <utility>
#include <falcon/memory/memory_stack.hpp>
#include <falcon/arg/arg.hpp>

namespace falcon {

template<typename _T>
struct __static_new_traits
{
	typedef typename std::remove_extent<_T>::type __type;
	static constexpr bool easy_constructible =
		std::has_trivial_default_constructor<__type>::value
		&& std::has_trivial_copy_constructor<__type>::value
		&& std::has_trivial_copy_assign<__type>::value;
	static constexpr bool easy_destructible =
		std::has_trivial_destructor<__type>::value;
};

template <typename _T,
	bool = false,
	bool = __static_new_traits<_T>::easy_constructible,
	bool = __static_new_traits<_T>::easy_destructible>
class __static_new_base
: __memory_stack<_T>
{
public:
	typedef _T type;
	typedef typename __memory_stack<_T>::memory_type memory_type;

private:
	type* _ptr;

public:
	__static_new_base()
	: _ptr(0)
	{}

	__static_new_base(const __static_new_base& other)
	: _ptr(other._ptr ? _ptr = new (data()) _T(other.get()) : 0)
	{}

	__static_new_base& operator=(const __static_new_base& other)
	{
		if (_ptr)
		{
			if (other._ptr)
				get() = other.get();
			else
			{
				__memory_stack<_T>::destroy();
				_ptr = 0;
			}
		}
		else if (other._ptr)
			_ptr = new (data()) _T(other.get());
		return *this;
	}

	~__static_new_base()
	{
		if (_ptr)
			__memory_stack<_T>::destroy();
	}

	template<typename... _Args>
	void construct(_Args&&... args)
	{
		if (_ptr)
			_ptr->~_T();
		_ptr = new (data()) _T(std::forward<_Args>(args)...);
	}

	void destroy()
	{
		if (_ptr)
		{
			__memory_stack<_T>::destroy();
			_ptr = 0;
		}
	}

	using __memory_stack<_T>::get;
	using __memory_stack<_T>::data;
	using __memory_stack<_T>::address;

	bool initialized() const
	{ return _ptr; }
};

template <typename _T, bool>
struct __static_new_value
{
	_T _value;
	void construct() {}
	void destroy() {}
	bool initialized() const { return false; };
};

template <typename _T>
struct __static_new_value<_T, true>
{
	_T _value;
	bool _ini = false;
	void construct() { _ini = true; }
	void destroy() { _ini = false; }
	bool initialized() const { return _ini; };
};

template <typename _T, bool AddInitialized>
class __static_new_base<_T, AddInitialized, true, true>
{
public:
	typedef _T type;
	typedef _T memory_type;

private:
	__static_new_value<_T, AddInitialized> _value;

public:
	type& get()
	{ return _value._value; }

	const type& get() const
	{ return _value._value; }

	memory_type& data()
	{ return _value._value; }

	const memory_type& data() const
	{ return _value._value; }

	type* address()
	{ return std::addressof(_value._value); }

	const type* address() const
	{ return std::addressof(_value._value); }

	template<typename... _Args>
	void construct(_Args&&... args)
	{
		_value.construct();
		_value._value = {std::forward<_Args>(args)...};
	}

	void construct(_T&& value)
	{
		_value.construct();
		_value._value = std::forward<_T>(value);
	}

	void destroy()
	{
		_value.destroy();
	}

	bool initialized() const
	{ return _value.initialized(); }
};


template <typename _T, std::size_t _N, bool AddInitialized>
class __static_new_base<_T[_N], AddInitialized, false, false>
: __memory_stack<_T[_N]>
{
public:
	typedef _T type[_N];
	typedef typename __memory_stack<_T[_N]>::memory_type memory_type;

private:
	type* _ptr;

public:
	__static_new_base()
	: _ptr(0)
	{}

	__static_new_base(const __static_new_base& other)
	: _ptr(0)
	{
		if (other._ptr)
			construct(other.get());
	}

	__static_new_base& operator=(const __static_new_base& other)
	{
		if (_ptr)
		{
			if (other._ptr)
			{
				for (std::size_t i = 0; i != _N; ++i)
					this->get()[i] = other.get()[i];
			}
			else
				destroy();
		}
		else if (other._ptr)
			construct(other.get());
		return *this;
	}

	~__static_new_base()
	{ __destroy(); }

private:
	void __destroy()
	{
		if (_ptr)
			__memory_stack<_T[_N]>::destroy();
	}

public:
	template<typename... _Args>
	void construct(_Args&&... args)
	{
		__destroy();
		__memory_stack<_T[_N]>::construct(std::forward<_Args>(args)...);
		_ptr = address();
	}

	void construct(const emplace_t&)
	{ construct(); }

	template<typename... _Args>
	void construct(const emplace_t&, _Args&&... args)
	{
		__destroy();
		__memory_stack<_T[_N]>::construct(emplace, std::forward<_Args>(args)...);
		_ptr = address();
	}

	void destroy()
	{
		__destroy();
		_ptr = 0;
	}

	using __memory_stack<_T[_N]>::get;
	using __memory_stack<_T[_N]>::data;
	using __memory_stack<_T[_N]>::address;

	bool initialized() const
	{ return _ptr; }
};

template <typename _T, std::size_t _N, bool AddInitialized>
class __static_new_base<_T[_N], AddInitialized, false, true>
: __memory_stack<_T[_N]>
{
public:
	typedef _T type[_N];
	typedef typename __memory_stack<_T[_N]>::memory_type memory_type;

private:
	type* _ptr;

public:
	__static_new_base()
	: _ptr(0)
	{}

	__static_new_base(const __static_new_base& other)
	: _ptr(0)
	{
		if (other._ptr)
			construct(other.get());
	}

	__static_new_base& operator=(const __static_new_base& other)
	{
		if (_ptr)
		{
			if (other._ptr)
			{
				for (std::size_t i = 0; i != _N; ++i)
					this->get()[i] = other.get()[i];
			}
			else
				destroy();
		}
		else if (other._ptr)
			construct(other.get());
		return *this;
	}

	template<typename... _Args>
	void construct(_Args&&... args)
	{
		__memory_stack<_T[_N]>::construct(std::forward<_Args>(args)...);
		_ptr = address();
	}

	void construct(const emplace_t&)
	{ construct(); }

	template<typename... _Args>
	void construct(const emplace_t&, _Args&&... args)
	{
		__memory_stack<_T[_N]>::construct(emplace, std::forward<_Args>(args)...);
		_ptr = address();
	}

	void destroy()
	{ _ptr = 0; }

	using __memory_stack<_T[_N]>::get;
	using __memory_stack<_T[_N]>::data;
	using __memory_stack<_T[_N]>::address;

	bool initialized() const
	{ return _ptr; }
};

template <typename _T, std::size_t _N, bool AddInitialized>
class __static_new_base<_T[_N], AddInitialized, true, true>
{
public:
	typedef _T type[_N];
	typedef _T memory_type;

private:
	__static_new_value<_T[_N], AddInitialized> _value;

public:
	type& get()
	{ return _value._value; }

	const type& get() const
	{ return _value._value; }

	memory_type& data()
	{ return _value._value; }

	const memory_type& data() const
	{ return _value._value; }

	type* address()
	{ return std::addressof(_value._value); }

	const type* address() const
	{ return std::addressof(_value._value); }

	template<typename... _Args>
	void construct(_Args&&... args)
	{
		_value.construct();
		for (unsigned int i = 0; i != _N; ++i)
			_value._value[i] = {std::forward<_Args>(args)...};
	}

	void construct(_T&& value)
	{
		_value.construct();
		for (unsigned int i = 0; i != _N; ++i)
			_value._value[i] = std::forward<_T>(value);
	}

private:
	template<typename _U, typename... _Args>
	void __construct(std::size_t n, _U&& a, _Args&&... args)
	{
		_value._value[n] = std::forward<_U>(a);
		__construct<n+1>(std::forward<_Args>(args)...);
	}

	void __construct(std::size_t i)
	{
		for (; i != _N; ++i)
			_value._value[i] = _T();
	}

public:
	template<typename... _Args>
	void construct(const emplace_t&, _Args&&... args)
	{
		_value.construct();
		__construct(0, std::forward<_Args>(args)...);
	}

	void destroy()
	{ _value.destroy(); }

	bool initialized() const
	{ return _value.initialized(); }
};


/**
 * \brief Reserve memory in the stack. If \c static_new::construct was used, \c static_new::destroy will call automatically.
 */
template <typename _T>
struct static_new
: private __static_new_base<_T>
{
	typedef _T type;
	typedef typename __static_new_base<_T>::memory_type memory_type;

public:
	using __static_new_base<_T>::get;
	using __static_new_base<_T>::data;
	using __static_new_base<_T>::address;
	using __static_new_base<_T>::destroy;
	using __static_new_base<_T>::construct;

	operator _T& ()
	{ return get(); }

	operator const _T& () const
	{ return get(); }

	_T* operator->()
	{ return address(); }

	const _T* operator->() const
	{ return address(); }
};


/**
 * \brief such as @ref static_new but knows if the variable was constructed.
 */
template <typename _T>
struct static_new2
: private __static_new_base<_T, true>
{
	typedef _T type;
	typedef typename __static_new_base<_T, true>::memory_type memory_type;

public:
	using __static_new_base<_T, true>::get;
	using __static_new_base<_T, true>::data;
	using __static_new_base<_T, true>::address;
	using __static_new_base<_T, true>::destroy;
	using __static_new_base<_T, true>::construct;
	using __static_new_base<_T, true>::initialized;

	operator _T& ()
	{ return get(); }

	operator const _T& () const
	{ return get(); }

	_T* operator->()
	{ return address(); }

	const _T* operator->() const
	{ return address(); }
};

}

#endif