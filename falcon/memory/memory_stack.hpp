#ifndef _FALCON_MEMORY_MEMORY_STACK_HPP
#define _FALCON_MEMORY_MEMORY_STACK_HPP

#include <utility>

namespace falcon {

template<typename _T>
class __memory_stack_base
{
public:
	typedef _T value_type;
	typedef unsigned char memory_type[sizeof(_T)];

private:
	union _Union{
		memory_type _memory;
		_T _v;

		_Union()
		{}
		~_Union()
		{}
	} _data;

public:
	__memory_stack_base()
	{}

	value_type& get()
	{
		return _data._v;
	}

	const value_type& get() const
	{
		return _data._v;
	}

	const memory_type& data() const
	{
		return _data._memory;
	}

	memory_type& data()
	{
		return _data._memory;
	}

	value_type* address()
	{
		return reinterpret_cast<value_type*>(&_data._memory);
	}

	const value_type* address() const
	{
		return reinterpret_cast<const value_type*>(&_data._memory);
	}

	constexpr std::size_t size() const
	{
		return sizeof(value_type);
	}
};

template <typename _T,
bool = std::is_trivial<typename std::remove_extent<_T>::type>::value>
class __memory_stack
: public __memory_stack_base<_T>
{
public:
	typedef typename __memory_stack_base<_T>::value_type value_type;
	typedef typename __memory_stack_base<_T>::memory_type memory_type;

public:
	__memory_stack()
	: __memory_stack_base<_T>()
	{}

	template<typename... _Args>
	void construct(_Args&&... args)
	{
		new (this->data()) _T(std::forward<_Args>(args)...);
	}

	void destroy()
	{
		this->get().~_T();
	}
};

template <typename _T>
class __memory_stack<_T, true>
: public __memory_stack_base<_T>
{
public:
	typedef typename __memory_stack_base<_T>::value_type value_type;
	typedef typename __memory_stack_base<_T>::memory_type memory_type;

public:
	__memory_stack()
	: __memory_stack_base<_T>()
	{}

	template<typename... _Args>
	void construct(_Args&&... args)
	{
		this->get() = {std::forward<_Args>(args)...};
	}

	template<typename _U>
	void construct(const _U& value)
	{
		this->get() = value;
	}

	void destroy()
	{}
};

constexpr struct emplace_t {} emplace;

template <typename _T, std::size_t _N>
class __memory_stack<_T[_N], false>
: public __memory_stack_base<_T[_N]>
{
public:
	typedef typename __memory_stack_base<_T>::value_type value_type;
	typedef typename __memory_stack_base<_T>::memory_type memory_type;

public:
	__memory_stack()
	: __memory_stack_base<_T[_N]>()
	{}

	unsigned char * __pdata(std::size_t n)
	{
		return &this->data()[sizeof(_T) * n];
	}

public:
	template<typename... _Args>
	void construct(_Args&&... args)
	{
		std::size_t i = 0;
		try
		{
			for (; i != _N; ++i)
				new (__pdata(i)) _T(std::forward<_Args>(args)...);
		}
		catch (...)
		{
			__destroy_n(i);
			throw;
		}
	}

	void construct(const emplace_t&)
	{
		construct();
	}

	void __destroy_n(std::size_t i)
	{
		while (i)
			this->get()[--i].~_T();
	}

private:
	template<typename _U, typename... _Args>
	void __construct(std::size_t& n, _U&& a, _Args&&... args)
	{
		new (__pdata(n)) _T(std::forward<_U>(a));
		__construct(++n, std::forward<_U>(args)...);
	}

	void __construct(std::size_t& n)
	{
		for (; n != _N; ++n)
			new (__pdata(n)) _T();
	}

public:
	template<typename... _Args>
	void construct(const emplace_t&, _Args&&... args)
	{
		std::size_t i = 0;
		try
		{
			__construct(i, std::forward<_Args>(args)...);
		}
		catch (...)
		{
			__destroy_n(i);
			throw;
		}
	}

	void destroy()
	{
		__destroy_n(_N);
	}
};

template <typename _T, std::size_t _N>
class __memory_stack<_T[_N], true>
: public __memory_stack_base<_T[_N]>
{
public:
	typedef typename __memory_stack_base<_T>::value_type value_type;
	typedef typename __memory_stack_base<_T>::memory_type memory_type;

public:
	__memory_stack()
	: __memory_stack_base<_T[_N]>()
	{}

	unsigned char * __pdata(std::size_t n)
	{
		return &this->data()[sizeof(_T) * n];
	}

	template<typename... _Args>
	void construct(_Args&&... args)
	{
		for (std::size_t i = 0; i != _N; ++i)
			new (__pdata(i)) _T{std::forward<_Args>(args)...};
	}

	template<typename _U>
	void construct(const _U& value)
	{
		for (std::size_t i = 0; i != _N; ++i)
			this->get()[i] = value;
	}

private:
	template<typename _U, typename... _Args>
	void __construct(std::size_t n, _U&& a, _Args&&... args)
	{
		new (__pdata(n)) _T(std::forward<_U>(a));
		__construct(n+1, std::forward<_U>(args)...);
	}

	void __construct(std::size_t n)
	{
		for (; n != _N; ++n)
			new (__pdata(n)) _T();
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

/**
 * \brief Reserve memory in the stack.
 * \attention The inner object is not automatically destroy.
 */
template<typename _T>
class memory_stack
: __memory_stack<_T>
{
public:
	typedef typename __memory_stack<_T>::value_type value_type;
	typedef typename __memory_stack<_T>::memory_type memory_type;

public:
	memory_stack()
	: __memory_stack<_T>()
	{}

	using __memory_stack<_T>::get;
	using __memory_stack<_T>::data;
	using __memory_stack<_T>::address;
	using __memory_stack<_T>::construct;
	using __memory_stack<_T>::destroy;
};

}

#endif