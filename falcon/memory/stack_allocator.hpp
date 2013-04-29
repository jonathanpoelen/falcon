#ifndef FALCON_MEMORY_STACK_ALLOCATOR_HPP
#define FALCON_MEMORY_STACK_ALLOCATOR_HPP

#include <cassert>
#include <cstring>
#include <memory>

#include <falcon/c++/boost_or_std.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(aligned_storage)

#include <falcon/bit/size.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/initialize.hpp>
#include <falcon/type_traits/eval_if.hpp>

namespace falcon {

struct stack_allocator_flag {
	enum enum_t {
		always_one      = 1 << 0,
		lifo_allocation = 1 << 1,
		normal_storage  = 1 << 2,
		minimal_storage = 1 << 3,
		speed_deduction = 1 << 4,
	};
};

template<typename _T, std::size_t _N, stack_allocator_flag::enum_t _Flag>
class __stack_allocator_bool_array
: public std::allocator<_T>
{
	typedef std::allocator<_T> __allocator_base;
	typedef typename FALCON_BOOST_OR_STD_NAMESPACE::aligned_storage<
		sizeof(_T),
		FALCON_BOOST_OR_STD_NAMESPACE::alignment_of<_T>::value
	>::type __memory_type;

	__memory_type m_memory[_N];
	bool m_allocate[_N];
	bool * m_first_free;

public:
	typedef typename __allocator_base::pointer pointer;
	typedef typename __allocator_base::size_type size_type;


#if __cplusplus >= 201103L
	__stack_allocator_bool_array()
	: m_allocate CPP_INITIALIZE(0)
	, m_first_free(m_allocate)
	{}
#else
	__stack_allocator_bool_array()
	: m_first_free(m_allocate)
	{ std::memset(m_allocate, 0, _N); }
#endif


	pointer allocate(size_type n, const void * = 0)
	{
		if (_Flag & stack_allocator_flag::always_one)
			assert(n == 1);
		else if (n == 0)
			return 0;

		if (&m_allocate[_N] == m_first_free)
			throw std::bad_alloc();

		while (*m_first_free) {
			++m_first_free;
			if (m_first_free != &m_allocate[_N])
				throw std::bad_alloc();
		}

		if (_Flag & stack_allocator_flag::always_one || n == 1) {
			*m_first_free = true;
			++m_first_free;
			return reinterpret_cast<pointer>(&m_memory[m_first_free - n - &m_allocate[0]]);

		}
		else {
			if (n > &m_allocate[_N] - m_first_free)
				throw std::bad_alloc();

			size_type nn = 0;
			bool * ppos = m_first_free;
			while (++nn != n) {
				if (*++ppos) {
					while (*++ppos) {
						if (ppos == &m_allocate[_N])
							throw std::bad_alloc();
					}
					nn = 0;
				}
			}
			if (m_first_free + n == ppos+1)
				m_first_free += n;
			std::memset(ppos+1-n, ~0u, n);
			return reinterpret_cast<pointer>(&m_memory[ppos+1 - (&m_allocate[0] + n)]);
		}
	}

	void deallocate(pointer p, size_type n)
	{
		assert(reinterpret_cast<pointer>(&m_memory[0]) <= p
				&& p < reinterpret_cast<pointer>(&m_memory[_N]));
		if (_Flag & stack_allocator_flag::always_one)
			assert(n == 1);
		bool * pb = m_allocate + (p - reinterpret_cast<pointer>(&m_memory[0]));

		if (_Flag & stack_allocator_flag::always_one)
			*pb = false;
		else
			std::memset(pb, 0, n);

		if (pb < m_first_free)
			m_first_free = pb;
	}
};

template<typename _T, std::size_t _N, stack_allocator_flag::enum_t _Flag>
class __stack_allocator_normal_lifo
: public std::allocator<_T>
{
	typedef std::allocator<_T> __allocator_base;
	typedef typename FALCON_BOOST_OR_STD_NAMESPACE::aligned_storage<
		sizeof(_T),
		FALCON_BOOST_OR_STD_NAMESPACE::alignment_of<_T>::value
	>::type __memory_type;

	__memory_type m_memory[_N];
	__memory_type * m_pos;

public:
	typedef typename __allocator_base::pointer pointer;
	typedef typename __allocator_base::size_type size_type;


	__stack_allocator_normal_lifo()
	: m_pos(m_memory)
	{}

	pointer allocate(size_type n, const void * = 0)
	{
		if (_Flag & stack_allocator_flag::always_one)
			assert(n == 1);
		else if (n == 0)
			return 0;

		if (_Flag & stack_allocator_flag::always_one ? m_pos == &m_memory[_N] : m_pos + n >= &m_memory[_N])
			throw std::bad_alloc();

		m_pos += n;
		return m_pos-n;
	}

	void deallocate(pointer p, size_type n)
	{
		(void)p;
		assert(reinterpret_cast<pointer>(&m_memory[0]) <= p
				&& p < reinterpret_cast<pointer>(&m_memory[_N]));
		if (_Flag & stack_allocator_flag::always_one) {
			assert(n == 1);
			--m_pos;
		}
		else {
			m_pos -= n;
		}
	}
};

template<typename _T, std::size_t _N, stack_allocator_flag::enum_t _Flag>
class __stack_allocator_speed_always_one
: public std::allocator<_T>
{
	typedef std::allocator<_T> __allocator_base;
	typedef typename FALCON_BOOST_OR_STD_NAMESPACE::aligned_storage<
		sizeof(_T),
		FALCON_BOOST_OR_STD_NAMESPACE::alignment_of<_T>::value
	>::type __memory_type;

	__memory_type m_memory[_N];
	__memory_type * m_free[_N];
	__memory_type ** m_last_free;

public:
	typedef typename __allocator_base::pointer pointer;
	typedef typename __allocator_base::size_type size_type;


public:
	__stack_allocator_speed_always_one()
	: m_last_free(&m_free[0])
	{
		for (__memory_type * p = m_memory, * e = &m_memory[_N]; p != e; ++p) {
			*m_last_free = p;
			++m_last_free;
		}
	}

	pointer allocate(size_type n, const void * = 0)
	{
		(void)n;
		assert(n == 1);

		if (m_last_free == &m_free[0])
			throw std::bad_alloc();

		--m_last_free;
		return reinterpret_cast<pointer>(*m_last_free);
	}

	void deallocate(pointer p, size_type n)
	{
		(void)n;
		assert(reinterpret_cast<pointer>(&m_memory[0]) <= p
				&& p < reinterpret_cast<pointer>(&m_memory[_N]));
		assert(n == 1);

		*m_last_free = reinterpret_cast<__memory_type*>(p);
		++m_last_free;
	}
};

template<typename _T, std::size_t _N, stack_allocator_flag::enum_t _Flag>
class __stack_allocator_minimal_storage
: public std::allocator<_T>
{
	typedef std::allocator<_T> __allocator_base;
	typedef typename FALCON_BOOST_OR_STD_NAMESPACE::aligned_storage<
		sizeof(_T),
		FALCON_BOOST_OR_STD_NAMESPACE::alignment_of<_T>::value
	>::type memory_type;

	typedef unsigned long bits_t;

	static const unsigned _S_word_bit = bit::size<bits_t>::value;

	memory_type m_memory[_N];
	bits_t m_is_allocate[_N / (_S_word_bit + 1) + 1];
	memory_type * m_first_memory;
	bits_t * m_first_free;
	bits_t m_first_free_offset;

public:
	typedef typename __allocator_base::pointer pointer;
	typedef typename __allocator_base::size_type size_type;


	__stack_allocator_minimal_storage()
	: m_is_allocate CPP_INITIALIZE(0)
	, m_first_memory(&m_memory[0])
	, m_first_free(&m_is_allocate[0])
	, m_first_free_offset(0)
	{}

private:
	CPP_CONSTEXPR const bits_t * __end() const
	{ return &m_is_allocate[_N / _S_word_bit]; }

	bool __is_end() const
	{ return m_first_free == __end() && m_first_free_offset == (_N % _S_word_bit); }

	static void _S_next(bits_t *& m, bits_t& offset)
	{
		if (++offset == _S_word_bit) {
			offset = 0;
			++m;
		}
	}

public:
	pointer allocate(size_type n, const void * hint = 0)
	{
		(void)hint;///TODO from hint to end and from first to hint
		if (_Flag & stack_allocator_flag::always_one)
			assert(n == 1);
		else if (n == 0)
			return 0;

		if (__is_end())
			throw std::bad_alloc();

		if (!(_Flag & stack_allocator_flag::lifo_allocation)) {
			while ((*m_first_free & (1ul << m_first_free_offset))) {
				_S_next(m_first_free, m_first_free_offset);
				if (__is_end())
					throw std::bad_alloc();
			};
		}

		if ((_Flag & stack_allocator_flag::always_one) || n == 1)
		{
			memory_type * ret = m_first_memory;
			++m_first_memory;
			*m_first_free |= 1ul << m_first_free_offset;
			return reinterpret_cast<pointer>(ret);
		}

		if (m_first_memory + n >= &m_memory[_N])
			throw std::bad_alloc();

		unsigned long * first_free = m_first_free;
		unsigned long free_offset = m_first_free_offset;
		unsigned long * kfirst_free = first_free;
		unsigned long kfree_offset = free_offset;
		size_type nn = n;

		for (;;) {
			do {
				_S_next(first_free, free_offset);
				--nn;
			} while (nn && !(first_free == __end() && free_offset == (_N % _S_word_bit - 1)) && !(*first_free & (1 << free_offset)));

			if (!nn)
				break;

			if (_Flag & stack_allocator_flag::lifo_allocation) {
				throw std::bad_alloc();
				break;
			}

			do {
				if (first_free == __end() && free_offset == (_N % _S_word_bit - 1))
					throw std::bad_alloc();
				_S_next(first_free, free_offset);
			} while (*first_free & (1 << free_offset));
			nn = n;
			kfirst_free = first_free;
			kfree_offset = free_offset;
		}

		if ((_Flag & stack_allocator_flag::lifo_allocation) || kfirst_free != m_first_free) {
			if (_Flag & stack_allocator_flag::lifo_allocation) {
				_S_next(first_free, free_offset);
			}
			m_first_free = first_free;
			m_first_free_offset =  free_offset;
		}
		memory_type * ret = &m_memory[kfirst_free - &m_is_allocate[0]];
		do {
			*kfirst_free |= 1 << kfree_offset;
			if (++kfree_offset == _S_word_bit) {
				kfree_offset = 0;
				++kfirst_free;
			}
		} while (--n);
		return reinterpret_cast<pointer>(ret);
	}

	void deallocate(pointer p, size_type n)
	{
		assert(reinterpret_cast<pointer>(&m_memory[0]) <= p
				&& p < reinterpret_cast<pointer>(&m_memory[_N]));
		if (_Flag & stack_allocator_flag::always_one)
			assert(n == 1);
		std::size_t d = p - reinterpret_cast<pointer>(&m_memory[0]);
		unsigned long * first_free = &m_is_allocate[0] + d / _S_word_bit;
		unsigned long first_free_offset = d % _S_word_bit;

		if ((_Flag & stack_allocator_flag::lifo_allocation) || p <= reinterpret_cast<pointer>(m_first_memory)){
			m_first_memory = reinterpret_cast<memory_type*>(p);
			m_first_free = first_free;
			m_first_free_offset = first_free_offset;
		}

		while ((_Flag & stack_allocator_flag::always_one) || n--) {
			*first_free &= ~(1ul << first_free_offset);
			_S_next(first_free, first_free_offset);
			if (_Flag & stack_allocator_flag::always_one)
				break;
		}
	}
};

template<typename _T, std::size_t _N, stack_allocator_flag::enum_t _Flag>
struct __stack_allocator_base
{
#define FALCON_SELECT_STACK_ALLOCATOR(name)\
	struct __select_stack_allocator_##name\
	{ typedef __stack_allocator_##name<_T, _N, _Flag> type; }

	FALCON_SELECT_STACK_ALLOCATOR(minimal_storage);
	FALCON_SELECT_STACK_ALLOCATOR(normal_lifo);
	FALCON_SELECT_STACK_ALLOCATOR(speed_always_one);
	FALCON_SELECT_STACK_ALLOCATOR(bool_array);

#undef FALCON_SELECT_STACK_ALLOCATOR

	typedef typename if_<
		_Flag & stack_allocator_flag::minimal_storage,
		__select_stack_allocator_minimal_storage,
		typename if_<
			_Flag == (stack_allocator_flag::speed_deduction | stack_allocator_flag::always_one),
			__select_stack_allocator_speed_always_one,
			typename if_<
				_Flag & stack_allocator_flag::lifo_allocation,
				__select_stack_allocator_normal_lifo,
				__select_stack_allocator_bool_array
			>::type
		>::type
	>::type::type __type;
};

template<typename _T, std::size_t _N,
	stack_allocator_flag::enum_t _Flag = stack_allocator_flag::normal_storage>
class stack_allocator
: public __stack_allocator_base<_T, _N, _Flag>::__type
{
	typedef typename __stack_allocator_base<_T, _N, _Flag>::__type __allocator_base;

public:
	typedef typename __allocator_base::pointer pointer;
	typedef typename __allocator_base::size_type size_type;
	typedef typename __allocator_base::const_pointer const_pointer;

	template<typename _U, std::size_t _N2 = _N,
		stack_allocator_flag::enum_t _Flag2 = _Flag>
	struct rebind
	{ typedef stack_allocator<_U, _N2, _Flag2> other; };

	stack_allocator()
	: __allocator_base()
	{}

	stack_allocator(const stack_allocator&)
	: __allocator_base()
	{}

	size_type max_size() const
	{ return _N; }
};

}

#endif