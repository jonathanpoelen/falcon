#ifndef FALCON_MEMORY_STACK_ALLOCATOR_HPP
#define FALCON_MEMORY_STACK_ALLOCATOR_HPP

#include <falcon/bit/size.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/type_traits/if.hpp>
#include <falcon/memory/allocator_rebind.hpp>

#include <falcon/c++/boost_or_std.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(aligned_storage)

#include <cassert>
#include <cstring>
#include <memory>

namespace falcon {

struct stack_allocator_policies {
  typedef int policy;
  static const policy normal_storage  = 1 << 0;
  static const policy lifo_allocation = 1 << 1;
  static const policy always_one      = 1 << 2;
  static const policy minimal_storage = 1 << 3;
  static const policy speed_deduction = 1 << 4;
};

namespace aux_ {

template<class T, std::size_t N, stack_allocator_policies::policy Policy, class AllocBase>
class stack_allocator_bool_array
: public allocator_rebind<AllocBase, T>::type
{
  typedef typename allocator_rebind<AllocBase, T>::type allocator_base_;
  typedef typename FALCON_BOOST_OR_STD_NAMESPACE::aligned_storage<
    sizeof(T),
    FALCON_BOOST_OR_STD_NAMESPACE::alignment_of<T>::value
  >::type memory_type;

  memory_type m_memory[N];
  bool m_allocate[N];
  bool * m_first_free;

public:
  typedef typename allocator_base_::pointer pointer;
  typedef typename allocator_base_::size_type size_type;


#if __cplusplus >= 201103L
  stack_allocator_bool_array()
  : allocator_base_()
  , m_allocate{0}
  , m_first_free(m_allocate)
  {}
#else
  stack_allocator_bool_array()
  : allocator_base_()
  , m_first_free(m_allocate)
  { std::memset(m_allocate, 0, sizeof(m_allocate); }
#endif

  pointer allocate(size_type n, const void * = 0)
  {
    if (Policy & stack_allocator_policies::always_one)
      assert(n == 1);
    else if (n == 0)
      return 0;

    if (&m_allocate[N] == m_first_free)
      throw std::bad_alloc();

    while (*m_first_free) {
      ++m_first_free;
      if (m_first_free != &m_allocate[N])
        throw std::bad_alloc();
    }

    if (Policy & stack_allocator_policies::always_one || n == 1) {
      *m_first_free = true;
      ++m_first_free;
      return reinterpret_cast<pointer>(&m_memory[m_first_free - n - &m_allocate[0]]);
    }
    else {
      if (n > std::size_t(&m_allocate[N] - m_first_free))
        throw std::bad_alloc();

      size_type nn = 0;
      bool * ppos = m_first_free;
      while (++nn != n) {
        if (*++ppos) {
          while (*++ppos) {
            if (ppos == &m_allocate[N])
              throw std::bad_alloc();
          }
          nn = 0;
        }
      }
      if (m_first_free + n == ppos+1)
        m_first_free += n;
      std::memset(ppos+1-n, 0xff, n);
      return reinterpret_cast<pointer>(&m_memory[ppos+1 - (&m_allocate[0] + n)]);
    }
  }

  void deallocate(pointer p, size_type n)
  {
    assert(reinterpret_cast<pointer>(&m_memory[0]) <= p
           && p < reinterpret_cast<pointer>(&m_memory[N]));
    if (Policy & stack_allocator_policies::always_one)
      assert(n == 1);
    bool * pb = m_allocate + (p - reinterpret_cast<pointer>(&m_memory[0]));

    if (Policy & stack_allocator_policies::always_one)
      *pb = false;
    else
      std::memset(pb, 0, n);

    if (pb < m_first_free)
      m_first_free = pb;
  }
};

template<class T, std::size_t N, stack_allocator_policies::policy Policy,
  class AllocBase>
class stack_allocator_normal_lifo
: public allocator_rebind<AllocBase, T>::type
{
  typedef typename allocator_rebind<AllocBase, T>::type allocator_base_;
  typedef typename FALCON_BOOST_OR_STD_NAMESPACE::aligned_storage<
    sizeof(T),
    FALCON_BOOST_OR_STD_NAMESPACE::alignment_of<T>::value
  >::type memory_type;

  memory_type m_memory[N];
  memory_type * m_pos;

public:
  typedef typename allocator_base_::pointer pointer;
  typedef typename allocator_base_::size_type size_type;


  stack_allocator_normal_lifo()
  : allocator_base_()
  , m_pos(m_memory)
  {}

  pointer allocate(size_type n, const void * = 0)
  {
    if (Policy & stack_allocator_policies::always_one)
      assert(n == 1);
    else if (n == 0)
      return 0;

    if (Policy & stack_allocator_policies::always_one ? m_pos == &m_memory[N] : m_pos + n > &m_memory[N])
      throw std::bad_alloc();

    if (Policy & stack_allocator_policies::always_one) {
      return reinterpret_cast<pointer>(m_pos++);
    }
    m_pos += n;
    return reinterpret_cast<pointer>(m_pos-n);
  }

  void deallocate(pointer p, size_type n)
  {
    (void)p;
    assert(reinterpret_cast<pointer>(&m_memory[0]) <= p
           && p < reinterpret_cast<pointer>(&m_memory[N]));
    if (Policy & stack_allocator_policies::always_one) {
      assert(n == 1);
      --m_pos;
    }
    else {
      m_pos -= n;
    }
  }
};

template<class T, std::size_t N, stack_allocator_policies::policy Policy,
  class AllocBase>
class stack_allocator_speed_always_one
: public allocator_rebind<AllocBase, T>::type
{
  typedef typename allocator_rebind<AllocBase, T>::type allocator_base_;
  typedef typename FALCON_BOOST_OR_STD_NAMESPACE::aligned_storage<
    sizeof(T),
    FALCON_BOOST_OR_STD_NAMESPACE::alignment_of<T>::value
  >::type memory_type;

  memory_type m_memory[N];
  memory_type * m_free[N];
  memory_type ** m_last_free;

public:
  typedef typename allocator_base_::pointer pointer;
  typedef typename allocator_base_::size_type size_type;


public:
  stack_allocator_speed_always_one()
  : allocator_base_()
  , m_last_free(&m_free[0])
  {
    for (memory_type * p = m_memory, * e = &m_memory[N]; p != e; ++p) {
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
           && p < reinterpret_cast<pointer>(&m_memory[N]));
    assert(n == 1);

    *m_last_free = reinterpret_cast<memory_type*>(p);
    ++m_last_free;
  }
};

template<class T, std::size_t N, stack_allocator_policies::policy Policy,
  class AllocBase>
class stack_allocator_minimal_storage
: public allocator_rebind<AllocBase, T>::type
{
  typedef typename allocator_rebind<AllocBase, T>::type allocator_base_;
  typedef typename FALCON_BOOST_OR_STD_NAMESPACE::aligned_storage<
    sizeof(T),
    FALCON_BOOST_OR_STD_NAMESPACE::alignment_of<T>::value
  >::type memory_type;

  typedef unsigned long bits_t;

  static const unsigned s_word_bit = bit::size<bits_t>::value;

  memory_type m_memory[N];
  bits_t m_is_allocate[N / (s_word_bit + 1) + 1];
  memory_type * m_first_memory;
  bits_t * m_first_free;
  bits_t m_first_free_offset;

public:
  typedef typename allocator_base_::pointer pointer;
  typedef typename allocator_base_::size_type size_type;

  stack_allocator_minimal_storage()
  : allocator_base_()
#if __cplusplus >= 201103L
  , m_is_allocate{0}
#endif
  , m_first_memory(&m_memory[0])
  , m_first_free(&m_is_allocate[0])
  , m_first_free_offset(0)
  {
#if __cplusplus < 201103L
		std::memset(m_is_allocate, 0, sizeof(m_is_allocate);
#endif
  }

private:
  CPP_CONSTEXPR const bits_t * end_() const
  { return &m_is_allocate[N / s_word_bit]; }

  bool is_end_() const
  { return m_first_free == end_() && m_first_free_offset == (N % s_word_bit); }

  static void s_next(bits_t *& m, bits_t& offset)
  {
    if (++offset == s_word_bit) {
      offset = 0;
      ++m;
    }
  }

public:
  pointer allocate(size_type n, const void * = 0)
  {
    if (Policy & stack_allocator_policies::always_one)
      assert(n == 1);
    else if (n == 0)
      return 0;

    if (is_end_())
      throw std::bad_alloc();

    while ((*m_first_free & (1ul << m_first_free_offset))) {
      s_next(m_first_free, m_first_free_offset);
      if (is_end_())
        throw std::bad_alloc();
    };

    if ((Policy & stack_allocator_policies::always_one) || n == 1)
    {
      memory_type * ret = m_first_memory;
      ++m_first_memory;
      *m_first_free |= 1ul << m_first_free_offset;
      return reinterpret_cast<pointer>(ret);
    }

    if (m_first_memory + n >= &m_memory[N])
        throw std::bad_alloc();

    unsigned long * first_free = m_first_free;
    unsigned long free_offset = m_first_free_offset;
    unsigned long * kfirst_free = first_free;
    unsigned long kfree_offset = free_offset;
    size_type nn = n;

    for (;;) {
      do {
        s_next(first_free, free_offset);
        --nn;
      } while (nn && !(first_free == end_() && free_offset == (N % s_word_bit - 1)) && !(*first_free & (1 << free_offset)));

      if (!nn)
        break;

      do {
        if (first_free == end_() && free_offset == (N % s_word_bit - 1))
          throw std::bad_alloc();
        s_next(first_free, free_offset);
      } while (*first_free & (1 << free_offset));
      nn = n;
      kfirst_free = first_free;
      kfree_offset = free_offset;
    }

    if (kfirst_free != m_first_free) {
      m_first_free = first_free;
      m_first_free_offset =  free_offset;
    }
    memory_type * ret = &m_memory[kfirst_free - &m_is_allocate[0]];
    do {
      *kfirst_free |= 1 << kfree_offset;
      if (++kfree_offset == s_word_bit) {
        kfree_offset = 0;
        ++kfirst_free;
      }
    } while (--n);
    return reinterpret_cast<pointer>(ret);
  }

  void deallocate(pointer p, size_type n)
  {
    assert(reinterpret_cast<pointer>(&m_memory[0]) <= p
           && p < reinterpret_cast<pointer>(&m_memory[N]));
    if (Policy & stack_allocator_policies::always_one)
      assert(n == 1);
    std::size_t d = std::size_t(p - reinterpret_cast<pointer>(&m_memory[0]));
    unsigned long * first_free = &m_is_allocate[0] + d / s_word_bit;
    unsigned long first_free_offset = d % s_word_bit;

    if (p <= reinterpret_cast<pointer>(m_first_memory)){
      m_first_memory = reinterpret_cast<memory_type*>(p);
      m_first_free = first_free;
      m_first_free_offset = first_free_offset;
    }

    while ((Policy & stack_allocator_policies::always_one) || n--) {
      *first_free &= ~(1ul << first_free_offset);
      s_next(first_free, first_free_offset);
      if (Policy & stack_allocator_policies::always_one)
        break;
    }
  }
};

template<class T, std::size_t N, stack_allocator_policies::policy Policy,
  class AllocBase>
class stack_allocator_base
{
#define FALCON_SELECT_STACK_ALLOCATOR(name)\
  struct select_stack_allocator_##name\
  { typedef stack_allocator_##name<T, N, Policy, AllocBase> type; }

  FALCON_SELECT_STACK_ALLOCATOR(minimal_storage);
  FALCON_SELECT_STACK_ALLOCATOR(normal_lifo);
  FALCON_SELECT_STACK_ALLOCATOR(speed_always_one);
  FALCON_SELECT_STACK_ALLOCATOR(bool_array);
#undef FALCON_SELECT_STACK_ALLOCATOR

public:
  typedef typename if_<
    !!(Policy & stack_allocator_policies::lifo_allocation),
    select_stack_allocator_normal_lifo,
    typename if_<
      !!(Policy & stack_allocator_policies::minimal_storage),
      select_stack_allocator_minimal_storage,
      typename if_<
        Policy == (
          stack_allocator_policies::speed_deduction
        | stack_allocator_policies::always_one),
        select_stack_allocator_speed_always_one,
        select_stack_allocator_bool_array
      >::type
    >::type
  >::type::type type;
};

}

template<class T, std::size_t N,
  stack_allocator_policies::policy Policy = stack_allocator_policies::normal_storage,
  class AllocBase = std::allocator<T> >
class stack_allocator
#if defined(IN_IDE_PARSER)
: public std::allocator<T>
#else
: public aux_::stack_allocator_base<T, N, Policy, AllocBase>::type
#endif
{
  typedef typename aux_::stack_allocator_base<T, N, Policy, AllocBase>::type allocator_base_;

public:
  typedef typename allocator_base_::pointer pointer;
  typedef typename allocator_base_::size_type size_type;
  typedef typename allocator_base_::const_pointer const_pointer;

#if __cplusplus >= 201103L
  using propagate_on_container_copy_assignment = std::false_type;
  using propagate_on_container_move_assignment = std::false_type;
  using propagate_on_container_swap = std::false_type;
#endif

  template<class U, std::size_t N2 = N,
    stack_allocator_policies::policy Policy2 = Policy,
    class AllocBase2 = AllocBase>
  struct rebind
  { typedef stack_allocator<U, N2, Policy2, AllocBase2> other; };

  stack_allocator()
  : allocator_base_()
  {}

  stack_allocator(const stack_allocator&)
  : allocator_base_()
  {}

  template<class T2, std::size_t N2, stack_allocator_policies::policy Policy2,
      class AllocBase2>
  stack_allocator(const stack_allocator<T2, N2, Policy2, AllocBase2>&)
  : allocator_base_()
  {}

  stack_allocator& operator=(const stack_allocator&)
  { return *this; }

  size_type max_size() const
  { return N; }
};

template<class T, std::size_t N, stack_allocator_policies::policy Policy, class AllocBase>
bool operator==(const falcon::stack_allocator<T, N, Policy, AllocBase>& a,
                const falcon::stack_allocator<T, N, Policy, AllocBase>& b)
{ return &a == &b; }

template<class T, std::size_t N, stack_allocator_policies::policy Policy, class AllocBase>
bool operator!=(const falcon::stack_allocator<T, N, Policy, AllocBase>& a,
                const falcon::stack_allocator<T, N, Policy, AllocBase>& b)
{ return &a != &b; }

}

#endif
