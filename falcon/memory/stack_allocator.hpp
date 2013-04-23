#ifndef FALCON_MEMORY_STACK_ALLOCATOR_HPP
#define FALCON_MEMORY_STACK_ALLOCATOR_HPP

#include <memory>
#include <falcon/preprocessor/not_ide_parser.hpp>
#include <falcon/bit/first.hpp>
#include <falcon/bit/size.hpp>
#include <falcon/memory/memory_stack.hpp>
#include <falcon/iterator/bit_iterator.hpp>
#include <falcon/c++/initialize.hpp>

namespace falcon {

///TODO 3 implementatin: tableau de bool, tableau de ull et mask, 2 tab: valeur utiliser ou non. Le refaire avec en fixant une taille de 1 élement allouer.

// struct always_one {}; --> int
//always_one + (minimal_storage(minimal_memory?) | normal_storage | speed_deduction | lifo_allocation) | big_allocation. lifo_allocation à ça propre implementation. Si seconde partie non donner alors _N < sizeof(unsigned long ) ? minimal_memory : (_N <= 1024 ? normal_storage : speed_deduction)
//si _N < sizeof(unsigned long ) et minimal_memory alors implementation spéciale.
//si big_allocation et minimal_memory alors implementation spéciale.

///minimal_storage
template<typename _T, std::size_t _N/*, typename Flag = void*/>
class stack_allocator
: public std::allocator<_T>
{
	typedef std::allocator<_T> __allocator_base;
	typedef typename boost::aligned_storage<
		sizeof(_T),
		boost::alignment_of<_T>::value
	>::type memory_type;
	typedef iterator::bit_iterator<unsigned long*> __bit_iterator;

	static const unsigned _S_word_bit = bit::size<unsigned long>::value;

	memory_type m_memory[_N];
	unsigned long m_is_allocate[_N / (_S_word_bit + 1) + 1];
	memory_type * m_first_memory;
	unsigned long * m_first_free;
	unsigned long m_first_free_offset;

public:
	typedef typename __allocator_base::pointer pointer;
	typedef typename __allocator_base::size_type size_type;
	typedef typename __allocator_base::const_pointer const_pointer;

	template<typename _U>
	struct rebind
	{ typedef stack_allocator<_U, _N> other; };

	stack_allocator() throw()
	: m_is_allocate CPP_INITIALIZE(0)
	, m_first_memory(&m_memory[0])
	, m_first_free(&m_is_allocate[0])
	, m_first_free_offset(0)
	{}

private:
	stack_allocator(const stack_allocator& __a) throw();
// 	: std::allocator<_T>(__a)
// 	, m_current_memory(&m_memory)
// 	{}
//
// 	template<typename _Tp1>
// 	stack_allocator(const stack_allocator<_Tp1>&) throw()
// 	: m_current_memory(&m_memory)
// 	{}

private:
	CPP_CONSTEXPR const unsigned long * __end() const
	{ return &m_is_allocate[_N / _S_word_bit]; }

	bool __is_end() const
	{ return m_first_free == __end() && m_first_free_offset == (_N % _S_word_bit); }

	void __next()
	{
		if (++m_first_free_offset == _S_word_bit) {
			m_first_free_offset = 0;
			++m_first_free;
		}
	}

	void __init_pos_free()
	{
		do {
			__next();
		} while (!__is_end() && (*m_first_free & (1ul << m_first_free_offset)));
	}

public:
	~stack_allocator() throw()
	{}

	pointer allocate(size_type n, const void * hint = 0)
	{
		(void)hint;///TODO
		if (n == 0)
			return 0;
		if (__is_end())
			throw std::bad_alloc();
		if (n == 1)
		{
			memory_type * ret = m_first_memory;
			++m_first_memory;
			*m_first_free |= 1ul << m_first_free_offset;
			__init_pos_free();
			return reinterpret_cast<pointer>(ret);
		}

		if (m_first_memory + n > &m_memory[0] + _N)
			throw std::bad_alloc();

		unsigned long * first_free = m_first_free;
		unsigned long first_free_mask = 1 << m_first_free_offset;
		size_type nn = n;

		for (;;) {
			do {
				if (!(first_free_mask <<= 1)) {
					first_free_mask = 1;
					++first_free;
				}
				--nn;
			} while (nn && !(first_free == __end() && first_free_mask == (1 << (_N % _S_word_bit - 1))) && !(*first_free & first_free_mask));

			if (!nn)
				break;

			do {
				if (first_free == __end() && first_free_mask == (1 << (_N % _S_word_bit - 1)))
					throw std::bad_alloc();
				if (!(first_free_mask <<= 1)) {
					first_free_mask = 1;
					++first_free;
				}
			} while (*first_free & first_free_mask);
			nn = n;
		}

		memory_type * ret = m_first_memory;
		do {
			*m_first_free |= 1 << m_first_free_offset;
			__next();
		} while (--n);
		__init_pos_free();
		return reinterpret_cast<pointer>(ret);
	}

	void deallocate(pointer p, size_type n)
	{
		std::size_t d = p - reinterpret_cast<pointer>(&m_memory[0]);
		unsigned long * first_free = &m_is_allocate[0] + d / _S_word_bit;
		unsigned long first_free_offset = d % _S_word_bit;

		if (p <= reinterpret_cast<pointer>(m_first_memory)){
			m_first_memory = reinterpret_cast<memory_type*>(p);
			m_first_free = first_free;
			m_first_free_offset = first_free_offset;
		}

		while (n--) {
			*first_free &= ~(1ul << first_free_offset);
			if (++first_free_offset == _S_word_bit) {
				first_free_offset = 0;
				++first_free;
			}
		}
	}

	size_type max_size() const
	{ return _N; }
};

}

#endif

#if 0
#ifndef FALCON_MEMORY_STACK_ALLOCATOR_HPP
#define FALCON_MEMORY_STACK_ALLOCATOR_HPP

#include <memory>
#include <falcon/bit/first.hpp>
#include <falcon/memory/memory_stack.hpp>
#include <falcon/iterator/bit_iterator.hpp>

namespace falcon {

///TODO 3 implementatin: tableau de bool, tableau de ull et mask, 2 tab: valeur utiliser ou non. Le refaire avec en fixant une taille de 1 élement allouer.

template<typename _T, std::size_t _N>
class stack_allocator
: public std::allocator<_T>
{
	typedef std::allocator<_T> __allocator_base;
	typedef typename boost::aligned_storage<
		sizeof(_T),
		boost::alignment_of<_T>::value
	>::type memory_type;
	typedef iterator::bit_iterator<unsigned long*> __bit_iterator;

	static const unsigned _S_word_bit = bit::size<unsigned long>::value;

	unsigned long m_is_allocate[_N / (_S_word_bit + 1) + 1];
	memory_type m_memory[_N];
	memory_type * m_first_free;
	memory_type * m_last_free;
	__bit_iterator m_first_is_allocate; ///TODO gerer a la main

public:
	typedef typename __allocator_base::pointer pointer;
	typedef typename __allocator_base::size_type size_type;
	typedef typename __allocator_base::const_pointer const_pointer;

	template<typename _U>
	struct rebind
	{ typedef stack_allocator<_U, _N> other; };

	stack_allocator() throw()
	: m_first_free(&m_memory[0])
	, m_last_free(&m_memory[_N])
	, m_first_is_allocate(&m_is_allocate[0], 1)
	{}

private:
	stack_allocator(const stack_allocator& __a) throw();
// 	: std::allocator<_T>(__a)
// 	, m_current_memory(&m_memory)
// 	{}
//
// 	template<typename _Tp1>
// 	stack_allocator(const stack_allocator<_Tp1>&) throw()
// 	: m_current_memory(&m_memory)
// 	{}
public:

	~stack_allocator() throw()
	{}

private:
	static unsigned long& ul(__bit_iterator& bi)
	{
		return *iterator::iterator_core_access::base_reference(bi);
	}

	static unsigned long& inc(__bit_iterator& bi)
	{
		return *++iterator::iterator_core_access::base_reference(bi);
	}

public:

	pointer allocate(size_type n, const void * hint = 0)
	{
		(void)hint;///TODO
		if (n == 0)
			return 0;
		if (n == 1)
		{
			if (m_first_free == m_last_free)
				throw std::bad_alloc();
			memory_type * ret = m_first_free;
			*m_first_is_allocate = 1;
			while (++m_first_free != m_last_free && *++m_first_is_allocate)
				;
			return reinterpret_cast<pointer>(ret);
		}
		__bit_iterator bfirst = m_first_is_allocate;
		memory_type * p = m_first_free;
		for (; p + n < m_last_free; ++p, ++bfirst)
		{
			memory_type * brp = p+1;
			__bit_iterator bbp = bfirst+1;
			while (brp != p + n && !*bbp) {
				++brp;
				++bbp;
			}
			if (brp == p + n)
			{
				m_first_free += n;
				unsigned long nf = bfirst.offset();
				if (nf < n) {
					ul(bfirst) |= ~((~0ul << nf) >> nf);
					n -= nf;
					for (; n >= _S_word_bit; n -= _S_word_bit) {
						inc(bfirst) = ~0ul;
					}
					if (n) {
						inc(bfirst) = ~((~0ul << n) >> n);
					}
				} else {
					inc(bfirst) = ~((~0ul << n) >> n);
				}
				return reinterpret_cast<pointer>(p);
			}
		}
		throw std::bad_alloc();
		return 0;
	}

	void deallocate(pointer p, size_type n)
	{
		if (p < reinterpret_cast<pointer>(m_first_free))
			m_first_free = reinterpret_cast<memory_type*>(p);
		std::size_t d = p - reinterpret_cast<pointer>(&m_memory[0]);
		unsigned long * first = &m_is_allocate[0] + d / _S_word_bit;
		if (d % _S_word_bit){
			if (d % _S_word_bit + n < _S_word_bit) {
				*first &= (~0ul >> (_S_word_bit - n));
				return ;
			} else {
				n += d % _S_word_bit;
			}
		}
		for (; n >= _S_word_bit; n -= _S_word_bit) {
			*first++ = 0ul;
		}
		*first |= (~0ul >> (_S_word_bit - n));
	}

	size_type max_size() const
	{ return _N; }
};

}

#endif
#endif