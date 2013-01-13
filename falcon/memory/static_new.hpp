#ifndef _FALCON_MEMORY_STATIC_NEW_HPP
#define _FALCON_MEMORY_STATIC_NEW_HPP

#include <utility>
#include <falcon/memory/memory_stack.hpp>

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

template <typename _T, bool = __static_new_traits<_T>::easy_constructible,
bool = __static_new_traits<_T>::easy_destructible>
class __static_new_base
{
public:
	typedef _T value_type;

private:
	__memory_stack<_T> _memory;
	value_type* _ptr;

public:
	__static_new_base()
	: _ptr(0)
	{}

	__static_new_base(const __static_new_base& other)
	: _ptr(other._ptr ? _ptr = new (_memory.data()) _T(other.get()) : 0)
	{}

	__static_new_base& operator=(const __static_new_base& other)
	{
		if (_ptr)
		{
			if (other._ptr)
				get() = other.get();
			else
			{
				_memory.destroy();
				_ptr = 0;
			}
		}
		else if (other._ptr)
			_ptr = new (_memory.data()) _T(other.get());
		return *this;
	}

	~__static_new_base()
	{
		if (_ptr)
			_memory.destroy();
	}

	value_type& get()
	{
		return _memory.get();
	}

	const value_type& get() const
	{
		return _memory.get();
	}

	template<typename... _Args>
	void construct(_Args&&... args)
	{
		if (_ptr)
			_ptr->~_T();
		_ptr = new (_memory.data()) _T(std::forward<_Args>(args)...);
	}

	void destroy()
	{
		if (_ptr)
		{
			_memory.destroy();
			_ptr = 0;
		}
	}
};

template <typename _T>
class __static_new_base<_T, true, true>
{
public:
	typedef _T value_type;

private:
	value_type _value;

public:
	value_type& get()
	{
		return _value;
	}

	const value_type& get() const
	{
		return _value;
	}

	template<typename... _Args>
	void construct(_Args&&... args)
	{
		_value = {std::forward<_Args>(args)...};
	}

	void construct(_T&& value)
	{
		_value = std::forward<_T>(value);
	}

	void destroy()
	{}
};

/**
 * \brief Reserve memory in the stack. If \c static_new::construct was used, \c static_new::destroy will call automatically.
 */
template <typename _T>
struct static_new
: private __static_new_base<_T>
{
	typedef __static_new_base<_T> __base;

public:
	typedef _T value_type;

public:
	template<typename... _Args>
	void construct(_Args&&... args)
	{
		__base::construct(std::forward<_Args>(args)...);
	}

	void destroy()
	{
		__base::destroy();
	}

	value_type& get()
	{
		return __base::get();
	}

	const value_type& get() const
	{
		return __base::get();
	}
};


template <typename _T, std::size_t _N>
class __static_new_base<_T[_N], false, false>
{
public:
	typedef _T value_type[_N];

private:
	__memory_stack<_T[_N]> _memory;
	value_type* _ptr;

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
	{
		__destroy();
	}

	value_type& get()
	{
		return _memory.get();
	}

	const value_type& get() const
	{
		return _memory.get();
	}

private:
	void __destroy()
	{
		if (_ptr)
			_memory.destroy();
	}

public:
	template<typename... _Args>
	void construct(_Args&&... args)
	{
		__destroy();
		_memory.construct(std::forward<_Args>(args)...);
		_ptr = _memory.address();
	}

	void construct(const emplace_t&)
	{
		construct();
	}

	template<typename... _Args>
	void construct(const emplace_t&, _Args&&... args)
	{
		__destroy();
		_memory.construct(emplace, std::forward<_Args>(args)...);
		_ptr = _memory.address();
	}

	void destroy()
	{
		__destroy();
		_ptr = 0;
	}
};

template <typename _T, std::size_t _N>
class __static_new_base<_T[_N], false, true>
{
public:
	typedef _T value_type[_N];

private:
	__memory_stack<_T[_N]> _memory;
	value_type* _ptr;

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

	value_type& get()
	{
		return _memory.get();
	}

	const value_type& get() const
	{
		return _memory.get();
	}

	template<typename... _Args>
	void construct(_Args&&... args)
	{
		_memory.construct(std::forward<_Args>(args)...);
		_ptr = _memory.address();
	}

	void construct(const emplace_t&)
	{
		construct();
	}

	template<typename... _Args>
	void construct(const emplace_t&, _Args&&... args)
	{
		_memory.construct(emplace, std::forward<_Args>(args)...);
		_ptr = _memory.address();
	}

	void destroy()
	{
		_ptr = 0;
	}
};

template <typename _T, std::size_t _N>
class __static_new_base<_T[_N], true, true>
{
public:
	typedef _T value_type[_N];

private:
	value_type _value;

public:
	value_type& get()
	{
		return _value;
	}

	const value_type& get() const
	{
		return _value;
	}

	template<typename... _Args>
	void construct(_Args&&... args)
	{
		for (unsigned int i = 0; i != _N; ++i)
			_value[i] = {std::forward<_Args>(args)...};
	}

	void construct(_T&& value)
	{
		for (unsigned int i = 0; i != _N; ++i)
			_value[i] = std::forward<_T>(value);
	}

private:
	template<typename _U, typename... _Args>
	void __construct(std::size_t n, _U&& a, _Args&&... args)
	{
		_value[n] = std::forward<_U>(a);
		__construct<n+1>(std::forward<_Args>(args)...);
	}

	void __construct(std::size_t i)
	{
		for (; i != _N; ++i)
			_value[i] = _T();
	}

public:
	template<typename... _Args>
	void construct(const emplace_t&, _Args&&... args)
	{
		__construct(0, std::forward<_Args>(args)...);
	}

	void destroy()
	{}
};


template<typename _T, std::size_t _N>
struct static_new<_T[_N]>
: private __static_new_base<_T[_N]>
{
private:
	typedef __static_new_base<_T[_N]> __base;

public:
	typedef _T value_type[_N];

public:
	template<typename... _Args>
	void construct(_Args&&... args)
	{
		__base::construct(std::forward<_Args>(args)...);
	}

	template<typename... _Args>
	void construct(const emplace_t& __emplace, _Args&&... args)
	{
		__base::construct(__emplace, std::forward<_Args>(args)...);
	}

	void destroy()
	{
		__base::destroy();
	}

	value_type& get()
	{
		return __base::get();
	}

	const value_type& get() const
	{
		return __base::get();
	}
};

}

#endif