#ifndef FALCON_MEMORY_STACK_ALLOCATOR_HPP
#define FALCON_MEMORY_STACK_ALLOCATOR_HPP

#include <memory>
#include <cstring>
#include <falcon/bit/size.hpp>
#include <falcon/c++/initialize.hpp>

namespace falcon {

enum stack_allocator_flag {
	always_one,
	lifo_allocation,
	normal_storage,
	minimal_storage,
};

template<typename _T, std::size_t _N, std::size_t _Flag = 0>
class __stack_allocator_bool_array
: public std::allocator<_T>
{
	typedef std::allocator<_T> __allocator_base;
	typedef typename boost::aligned_storage<
		sizeof(_T),
		boost::alignment_of<_T>::value
	>::type __memory_type;

	__memory_type m_memory[_N];
	bool m_allocate[_N];
	bool * m_first_free;

public:
	typedef typename __allocator_base::pointer pointer;
	typedef typename __allocator_base::size_type size_type;
	typedef typename __allocator_base::const_pointer const_pointer;

	template<typename _U>
	struct rebind
	{ typedef __stack_allocator_bool_array<_U, _N, _Flag> other; };

#if __cplusplus >= 201103L
	typedef std::true_type propagate_on_container_move_assignment;

	__stack_allocator_bool_array()
	: m_allocate CPP_INITIALIZE(0)
	, m_first_free(m_allocate)
	{}

	__stack_allocator_bool_array(const __stack_allocator_bool_array&)
	: m_allocate CPP_INITIALIZE(0)
	, m_first_free(m_allocate)
	{}
#else
	__stack_allocator_bool_array()
	: m_first_free(m_allocate)
	{ std::memset(m_allocate, 0, _N); }

	__stack_allocator_bool_array(const __stack_allocator_bool_array&)
	: m_first_free(m_allocate)
	{ std::memset(m_allocate, 0, _N); }
#endif


	pointer allocate(size_type n, const void * = 0)
	{
		if (!(_Flag & always_one) && n == 0)
			return 0;

		if (&m_allocate[_N] == m_first_free)
			throw std::bad_alloc();

		while (*m_first_free) {
			++m_first_free;
			if (m_first_free != &m_allocate[_N])
				throw std::bad_alloc();
		}

		if (_Flag & always_one || n == 1) {
			++m_first_free;
		}
		else {
			if (n > &m_allocate[_N] - m_first_free)
				throw std::bad_alloc();

			size_type nn = 0;
			bool * ppos = m_first_free + 1;
			while (++nn != n) {
				if (*ppos) {
					while (*++ppos) {
						if (ppos != &m_allocate[_N])
							throw std::bad_alloc();
					}
					nn = 0;
				}
			}
			m_first_free = ppos;
			std::memset(ppos-n, ppos, ~0u);
		}

		return m_first_free;
	}

	void deallocate(pointer p, size_type n)
	{
		bool * pb = m_allocate + (p - &m_memory[0]);

		if (_Flag & always_one)
			*pb = false;
		else
			std::memset(pb, pb + n, 0);

		if (pb < m_first_free)
			m_first_free = pb;
	}
};

template<typename _T, std::size_t _N, std::size_t _Flag = 0>
class __stack_allocator_normal_lifo
: public std::allocator<_T>
{
	typedef std::allocator<_T> __allocator_base;
	typedef typename boost::aligned_storage<
		sizeof(_T),
		boost::alignment_of<_T>::value
	>::type __memory_type;

	__memory_type m_memory[_N];
	__memory_type * m_pos;

public:
	typedef typename __allocator_base::pointer pointer;
	typedef typename __allocator_base::size_type size_type;
	typedef typename __allocator_base::const_pointer const_pointer;

	template<typename _U>
	struct rebind
	{ typedef __stack_allocator_normal_lifo<_U, _N, _Flag> other; };

#if __cplusplus >= 201103L
	typedef std::true_type propagate_on_container_move_assignment;
#endif

	__stack_allocator_normal_lifo()
	: m_pos(m_memory)
	{}

	__stack_allocator_normal_lifo(const __stack_allocator_normal_lifo&)
	: m_pos(m_memory)
	{}

	pointer allocate(size_type n, const void * = 0)
	{
		if (!(_Flag & always_one) && n == 0)
			return 0;

		if (_Flag & always_one ? m_pos == &m_memory[_N] : m_pos + n >= &m_memory[_N])
			throw std::bad_alloc();

		m_pos += n;
		return m_pos-n;
	}

	void deallocate(pointer , size_type n)
	{
		m_pos -= n;
	}
};

///TODO 3 implementatin: tableau de bool, tableau de ull et mask, 2 tab: valeur utiliser ou non. Le refaire avec en fixant une taille de 1 élement allouer.

// struct always_one {}; --> int
//always_one + (minimal_storage(minimal_memory?) | normal_storage | speed_deduction | lifo_allocation) | big_allocation. lifo_allocation à ça propre implementation. Si seconde partie non donner alors _N < sizeof(unsigned long ) ? minimal_memory : (_N <= 1024 ? normal_storage : speed_deduction)
//si _N < sizeof(unsigned long ) et minimal_memory alors implementation spéciale.
//si big_allocation et minimal_memory alors implementation spéciale.

///minimal_storage
template<typename _T, std::size_t _N, std::size_t _Flag = 0>
class stack_allocator
: public std::allocator<_T>
{
	typedef std::allocator<_T> __allocator_base;
	typedef typename boost::aligned_storage<
		sizeof(_T),
		boost::alignment_of<_T>::value
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
	typedef typename __allocator_base::const_pointer const_pointer;

	template<typename _U>
	struct rebind
	{ typedef stack_allocator<_U, _N, _Flag> other; };

#if __cplusplus >= 201103L
	typedef std::true_type propagate_on_container_move_assignment;
#endif

	stack_allocator()
	: m_is_allocate CPP_INITIALIZE(0)
	, m_first_memory(&m_memory[0])
	, m_first_free(&m_is_allocate[0])
	, m_first_free_offset(0)
	{}

private:
	stack_allocator(const stack_allocator& __a)/**/;
// 	: std::allocator<_T>(__a)
// 	, m_current_memory(&m_memory)
// 	{}
//
// 	template<typename _Tp1>
// 	stack_allocator(const stack_allocator<_Tp1>&)
// 	: m_current_memory(&m_memory)
// 	{}

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
	~stack_allocator()
	{}

	pointer allocate(size_type n, const void * hint = 0)
	{
		(void)hint;///TODO from hint to end and from first to hint
		if (!(_Flag & always_one) && n == 0)
			return 0;

		if (__is_end())
			throw std::bad_alloc();

		if (!(_Flag & lifo_allocation)) {
			while ((*m_first_free & (1ul << m_first_free_offset))) {
				_S_next(m_first_free, m_first_free_offset);
				if (__is_end())
					throw std::bad_alloc();
			};
		}

		if ((_Flag & always_one) || n == 1)
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

			if (_Flag & lifo_allocation) {
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

		if ((_Flag & lifo_allocation) || kfirst_free != m_first_free) {
			if (_Flag & lifo_allocation) {
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
		std::size_t d = p - reinterpret_cast<pointer>(&m_memory[0]);
		unsigned long * first_free = &m_is_allocate[0] + d / _S_word_bit;
		unsigned long first_free_offset = d % _S_word_bit;

		if ((_Flag & lifo_allocation) || p <= reinterpret_cast<pointer>(m_first_memory)){
			m_first_memory = reinterpret_cast<memory_type*>(p);
			m_first_free = first_free;
			m_first_free_offset = first_free_offset;
		}

		while ((_Flag & always_one) || n--) {
			*first_free &= ~(1ul << first_free_offset);
			_S_next(first_free, first_free_offset);
			if (_Flag & always_one)
				break;
		}
	}

	size_type max_size() const
	{ return _N; }
};

}

#endif