#ifndef _FALCON_MEMORY_MEMORY_STACK_HPP
#define _FALCON_MEMORY_MEMORY_STACK_HPP

#include <utility>
#include <falcon/c++/constexpr.hpp>
#include <boost/aligned_storage.hpp>

namespace falcon {

template<typename _T, std::size_t _N>
struct __memory_stack_type
{
	typedef _T type[_N];
	typedef typename __memory_stack_type<_T, -1u>::memory_type memory_type[_N];
};

template<typename _T>
struct __memory_stack_type<_T, std::size_t(-1u)>
{
	typedef _T type;
	typedef typename boost::aligned_storage<
		sizeof(_T),
		boost::alignment_of<_T>::value
	>::type memory_type;
};

template<typename _T, std::size_t _N = std::size_t(-1u)>
class __memory_stack_base
{
public:
	typedef typename __memory_stack_type<_T, _N>::type type;
	typedef typename __memory_stack_type<_T, _N>::memory_type memory_type;
	typedef _T * pointer;
	typedef const _T * const_pointer;

private:
	memory_type m_data;

public:
	__memory_stack_base()
	{}

	const memory_type& data() const
	{
		return m_data;
	}

	type& get()
	{
		return reinterpret_cast<type&>(m_data);
	}

	const type& get() const
	{
		return reinterpret_cast<const type&>(m_data);
	}

	memory_type& data()
	{
		return m_data;
	}

	pointer address()
	{
		return reinterpret_cast<_T*>(&m_data);
	}

	const_pointer address() const
	{
		return reinterpret_cast<const _T*>(&m_data);
	}

	CPP_CONSTEXPR std::size_t size() const
	{
		return sizeof(memory_type);
	}
};

template <typename _T,
bool = std::is_trivial<typename std::remove_extent<_T>::type>::value>
class __memory_stack
: public __memory_stack_base<_T>
{
public:
	typedef typename __memory_stack_base<_T>::type type;
	typedef typename __memory_stack_base<_T>::memory_type memory_type;

public:
	__memory_stack()
	: __memory_stack_base<_T>()
	{}

	template<typename... _Args>
	void construct(_Args&&... args)
	{
		new (this->address()) _T(std::forward<_Args>(args)...);
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
	typedef typename __memory_stack_base<_T>::type type;
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

#if __cplusplus > 201100L
constexpr struct emplace_t {} emplace;
#else
struct emplace_t {};
const emplace_t emplace;
#endif

template <typename _T, std::size_t _N>
class __memory_stack<_T[_N], false>
: public __memory_stack_base<_T, _N>
{
public:
	typedef typename __memory_stack_base<_T, _N>::type type;
	typedef typename __memory_stack_base<_T, _N>::memory_type memory_type;

public:
	__memory_stack()
	: __memory_stack_base<_T, _N>()
	{}

public:
	template<typename... _Args>
	void construct(_Args&&... args)
	{
		std::size_t i = 0;
		try
		{
			_T * p = this->address();
			for (; i != _N; ++i, ++p)
				new (p) _T(std::forward<_Args>(args)...);
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
		_T * p = this->address();
		while (i)
			p[--i].~_T();
	}

private:
	template<typename _U, typename... _Args>
	void __construct(std::size_t& n, _T * p, _U&& a, _Args&&... args)
	{
		new (p) _T(std::forward<_U>(a));
		__construct(++n, p+1, std::forward<_U>(args)...);
	}

	void __construct(std::size_t& n, _T * p)
	{
		for (; n != _N; ++n, ++p)
			new (p) _T();
	}

public:
	template<typename... _Args>
	void construct(const emplace_t&, _Args&&... args)
	{
		std::size_t i = 0;
		try
		{
			__construct(i, this->address(), std::forward<_Args>(args)...);
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
: public __memory_stack_base<_T, _N>
{
public:
	typedef typename __memory_stack_base<_T, _N>::type type;
	typedef typename __memory_stack_base<_T, _N>::memory_type memory_type;

public:
	__memory_stack()
	: __memory_stack_base<_T, _N>()
	{}

	template<typename... _Args>
	void construct(_Args&&... args)
	{
		_T* p = this->address();
		for (std::size_t i = 0; i != _N; ++i, ++p)
			new (p) _T{std::forward<_Args>(args)...};
	}

	template<typename _U>
	void construct(const _U& value)
	{
		for (std::size_t i = 0; i != _N; ++i)
			this->get()[i] = value;
	}

private:
	template<typename _U, typename... _Args>
	void __construct(std::size_t n, _T* p, _U&& a, _Args&&... args)
	{
		new (p) _T(std::forward<_U>(a));
		__construct(n+1, p+1, std::forward<_U>(args)...);
	}

	void __construct(std::size_t n, _T* p = 0)
	{
		for (; n != _N; ++n, ++p)
			new (p) _T();
	}

public:
	template<typename... _Args>
	void construct(const emplace_t&, _Args&&... args)
	{
		__construct(0, this->address(), std::forward<_Args>(args)...);
	}

	void destroy()
	{}
};

/**
 * \brief Reserve memory in the stack.
 * \attention The internal object is not automatically destroy.
 */
template<typename _T>
class memory_stack
: __memory_stack<_T>
{
public:
	typedef typename __memory_stack<_T>::type type;
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