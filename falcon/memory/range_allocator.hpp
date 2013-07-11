#ifndef FALCON_MEMORY_RANGE_ALLOCATOR_HPP
#define FALCON_MEMORY_RANGE_ALLOCATOR_HPP

#include <falcon/bit/left.hpp>
#include <falcon/bit/byte_cast.hpp>
#include <falcon/c++/noexcept.hpp>
#include <falcon/memory/allocator_rebind.hpp>
#include <falcon/memory/allocator_swap.hpp>

#include <memory>
#include <stdexcept>

namespace falcon {

template <typename T, typename AllocBase = std::allocator<T> >
class range_minimal_heap_allocator
: public allocator_rebind<AllocBase, T>::type
{
  typedef typename allocator_rebind<AllocBase, T>::type __allocator_base;

public:
  typedef typename __allocator_base::pointer pointer;
  typedef typename __allocator_base::size_type size_type;

#if __cplusplus > 201100L
  using propagate_on_container_copy_assignment = std::false_type;
  using propagate_on_container_move_assignment = std::true_type;
  using propagate_on_container_swap = std::true_type;
#endif

  template<typename U, typename AllocBase2 = AllocBase>
  struct rebind
  { typedef range_minimal_heap_allocator<U, AllocBase2> other; };

public:
  range_minimal_heap_allocator(T * first, T * last) CPP_NOEXCEPT
  : __allocator_base()
  , m_start(reinterpret_cast<Obj*>(first))
  , m_finish(reinterpret_cast<Obj*>(last))
  , m_current(m_start)
  {
    m_start->byte_and_use = byte_cast(last) - byte_cast(first);
    m_start->prev = 0;
  }

#if __cplusplus > 201100L
  range_minimal_heap_allocator(const range_minimal_heap_allocator&) = delete;
  range_minimal_heap_allocator(range_minimal_heap_allocator&&) noexcept = default;
  range_minimal_heap_allocator& operator=(const range_minimal_heap_allocator&) = delete;
  range_minimal_heap_allocator& operator=(range_minimal_heap_allocator&&) noexcept = default;
#else
private:
  range_minimal_heap_allocator(const range_minimal_heap_allocator&);
  range_minimal_heap_allocator& operator=(const range_minimal_heap_allocator&);
public:
#endif

  ~range_minimal_heap_allocator() CPP_NOEXCEPT
  {}

  pointer allocate(size_type n, const void * = 0)
  {
    Obj * ret = m_current->find(n, m_finish);
    if (!ret) {
      ret = m_start->find(n, m_current);
      if (!ret) {
        throw std::bad_alloc();
      }
    }
    m_current = ret->from(ret->byte_and_use);
    ret->use(n);
    return ret->data;
  }

  void deallocate(pointer p, size_type n)
  {
    (void)n;
    Obj * obj = Obj_cast(byte_cast(p) - Obj::_S_heap_size);
    obj->free(m_finish);
  }

  bool expand_alloc(pointer * p, std::size_t n)
  {
    if (p + n < m_finish) {
      Obj * obj = reinterpret_cast<Obj*>(byte_cast(p) - Obj::_S_heap_size);
      if ((obj->byte_and_use | ~1) >= n) {
        return true;
      }
      Obj * nx = obj->next();
      if (nx->prev == obj && ! nx->is_used() && nx->byte_and_use <= n) {
        Obj * nx2 = nx->next();
        if (nx2 < m_finish)
          nx->next()->prev = obj;
        obj->byte_and_use = (obj->byte_and_use & ~Obj::_S_mask_use) + nx->byte_and_use;
        obj->use(n);
        return true;
      }
    }
    return false;
  }

  void swap(range_minimal_heap_allocator& other) CPP_NOEXCEPT
  {
    using std::swap;
    swap(m_start, other.m_start);
    swap(m_finish, other.m_finish);
    swap(m_current, other.m_current);
    allocator_swap<__allocator_base>(*this, other);
  }

private:
  class Obj;

  inline Obj * Obj_cast(unsigned char * p)
  { return reinterpret_cast<Obj*>(p); }

  struct Obj
  {
    static const std::size_t _S_self_align = sizeof(std::size_t) > sizeof(Obj*) ? sizeof(std::size_t) : sizeof(Obj*);
    static const std::size_t _S_T_byte = sizeof(T);
    static const std::size_t _S_heap_size = sizeof(Obj) - sizeof(T);
    static const std::size_t _S_mask_use = bit::left<std::size_t>::value;

    std::size_t byte_and_use;
    Obj * prev;
    T data[1];

    static std::size_t aligned_size(std::size_t n)
    {
      std::size_t __byte = n * _S_T_byte + _S_heap_size;
      return __byte + (_S_self_align - (__byte + _S_self_align) % _S_self_align);
    }

    Obj * from(std::size_t n)
    { return Obj_cast(byte_cast(this) + n); }

    Obj * next()
    { return from(byte_and_use & ~_S_mask_use); }

    Obj * find(std::size_t n, Obj * last)
    {
      Obj * ret = this;
      std::size_t byte = n * _S_T_byte + _S_heap_size;
      while (ret < last && (ret->is_used() || ret->byte_and_use < byte)) {
          ret = ret->from(ret->byte_and_use);
      }
      return ret;
    }

    void use(std::size_t n)
    {
      Obj * nx = from(byte_and_use);
      if (false == nx->is_used() && _S_heap_size + _S_T_byte * n != byte_and_use) {
        Obj * obj = from(aligned_size(n));
        std::size_t byte = byte_cast(obj) - byte_cast(this);
        nx->byte_and_use += byte_and_use - byte;
        byte_and_use = byte;
        //nx and obj may have overlapping memory
        byte = nx->byte_and_use;
        obj->prev = this;
        obj->byte_and_use = byte;
      }
      byte_and_use |= _S_mask_use;
    }

    void free(Obj * last)
    {
      byte_and_use &= ~_S_mask_use;
      if (prev && ! prev->is_used()) {
        prev->byte_and_use += byte_and_use;
        Obj * nx = from(byte_and_use);
        if (nx < last) {
          nx->prev = prev;
        }
      }
    }

    bool is_used() const
    { return byte_and_use & _S_mask_use; }
  };

  Obj * m_start;
  Obj * m_finish;
  Obj * m_current;

public:
  static const std::size_t heap_size = 0;
  static const std::size_t heap_element_size = Obj::_S_heap_size;
};


template<typename T, typename AllocBase = std::allocator<T> >
class range_fixed_allocator
: public allocator_rebind<AllocBase, T>::type
{
  typedef typename allocator_rebind<AllocBase, T>::type __allocator_base;

public:
  typedef typename __allocator_base::pointer pointer;
  typedef typename __allocator_base::size_type size_type;

#if __cplusplus > 201100L
  using propagate_on_container_copy_assignment = std::false_type;
  using propagate_on_container_move_assignment = std::true_type;
  using propagate_on_container_swap = std::true_type;
#endif

  template<typename U, typename AllocBase2 = AllocBase>
  struct rebind
  { typedef range_fixed_allocator<U, AllocBase2> other; };

public:
  range_fixed_allocator(void * first, void * last, std::size_t n = 1)
  : __allocator_base()
  , m_finish(last)
  , m_free(reinterpret_cast<Obj*>(byte_cast(first) + Obj::_S_heap_size))
  , m_size(n)
  {
    if (!n) {
      throw std::domain_error("range_fixed_allocator invalid size 0");
    }

    m_free->next = reinterpret_cast<Obj*>(byte_cast(first) + Obj::_S_heap_size);
    Obj * objfirst = m_free->next;
    for (; objfirst < reinterpret_cast<Obj*>(last); objfirst += n) {
      objfirst->next = objfirst+n;
    }
    objfirst->next = reinterpret_cast<Obj*>(last);
  }

#if __cplusplus > 201100L
  range_fixed_allocator(const range_fixed_allocator&) = delete;
  range_fixed_allocator(range_fixed_allocator&&) noexcept = default;
  range_fixed_allocator& operator=(const range_fixed_allocator&) = delete;
  range_fixed_allocator& operator=(range_fixed_allocator&&) noexcept = default;
#else
private:
  range_fixed_allocator(const range_fixed_allocator&);
  range_fixed_allocator& operator=(const range_fixed_allocator&);
public:
#endif

  ~range_fixed_allocator() CPP_NOEXCEPT
  {}

  pointer allocate(size_type, const void * = 0)
  {
    Obj * ret = m_free->next;
    if (ret == m_finish) {
      throw std::bad_alloc();
    }
    m_free->next = m_free->next->next;
    return ret->data;
  }

  void deallocate(pointer p, size_type)
  {
    Obj * obj = reinterpret_cast<Obj*>(byte_cast(p) - Obj::_S_heap_size);
    obj->next = m_free->next;
    m_free->next = obj;
  }

  size_type max_size() const CPP_NOEXCEPT
  { return m_size; }

  void swap(range_fixed_allocator& other) CPP_NOEXCEPT
  {
    using std::swap;
    swap(m_free, other.m_free);
    swap(m_finish, other.m_finish);
    swap(m_size, other.m_size);
    allocator_swap<__allocator_base>(*this, other);
  }

private:
  struct Obj
  {
    static const std::size_t _S_self_align = sizeof(Obj*);
    static const std::size_t _S_heap_size = sizeof(Obj*);
    static const std::size_t _S_align_size = sizeof(Obj);

    Obj * next;
    T data[1];
  };

  void * m_finish;
  Obj * m_free;
  std::size_t m_size;

public:
  static const std::size_t heap_size = Obj::_S_heap_size;
  static const std::size_t heap_element_size = Obj::_S_heap_size;
};


template <typename T, typename AllocBase = std::allocator<T> >
class range_allocator
: public allocator_rebind<AllocBase, T>::type
{
  typedef typename allocator_rebind<AllocBase, T>::type __allocator_base;

public:
  typedef typename __allocator_base::pointer pointer;
  typedef typename __allocator_base::size_type size_type;

#if __cplusplus > 201100L
  using propagate_on_container_copy_assignment = std::false_type;
  using propagate_on_container_move_assignment = std::true_type;
  using propagate_on_container_swap = std::true_type;
#endif

  template<typename U, typename AllocBase2 = AllocBase>
  struct rebind
  { typedef range_allocator<U, AllocBase2> other; };

public:
  range_allocator(void * first, void * last)
  : __allocator_base()
  , m_finish(last)
  , m_used(reinterpret_cast<Obj*>(first))
  , m_free(reinterpret_cast<Obj*>(byte_cast(first) + Obj::_S_heap_size))
  {
    if (byte_distance(first, last) < 3 * Obj::_S_heap_size) {
      throw std::domain_error("range_fixed_allocator invalid size 0");
    }

    m_used->byte_and_use = Obj::_S_mask_use;
    m_used->prev = 0;
    m_used->next = 0;

    m_free->byte_and_use = Obj::_S_mask_use;
    m_free->prev = 0;
    m_free->next = reinterpret_cast<Obj*>(byte_cast(first) + 2 * Obj::_S_heap_size);

    m_free->next->byte_and_use = byte_cast(last) - byte_cast(first) - 2 * Obj::_S_heap_size;
    m_free->next->prev = m_free;
    m_free->next->next = 0;
  }

#if __cplusplus > 201100L
  range_allocator(const range_allocator&) = delete;
  range_allocator(range_allocator&&) noexcept = default;
  range_allocator& operator=(const range_allocator&) = delete;
  range_allocator& operator=(range_allocator&&) noexcept = default;
#else
private:
  range_allocator(const range_allocator&);
  range_allocator& operator=(const range_allocator&);
public:
#endif

  ~range_allocator() CPP_NOEXCEPT
  {}

  pointer allocate(size_type n, const void * = 0)
  {
    Obj * ret = m_free->next;
    std::size_t byte = Obj::aligned_size(n);
    while (ret && ret->byte_and_use < byte) {
      ret = ret->next;
    }

    if (!ret) {
      throw std::bad_alloc();
    }

    if (byte + sizeof(Obj) <= ret->byte_and_use) {
      ret->split_and_detach(byte);
    }
    else {
      ret->detach();
    }

    m_used->insert_next(ret);
    ret->byte_and_use |= Obj::_S_mask_use;

    return ret->data;
  }

  void deallocate(pointer p, size_type n)
  {
    (void)n;
    Obj * obj = reinterpret_cast<Obj*>(byte_cast(p) - Obj::_S_heap_size);
    Obj * tmp = obj;
    obj->byte_and_use &= ~Obj::_S_mask_use;
    obj->detach();

    if (obj->prev && obj->prev->next == obj && obj->prev->is_used()) {
      obj->prev->byte_and_use += obj->byte_and_use;
      obj = obj->prev;
    }

    Obj * nx = reinterpret_cast<Obj*>(byte_cast(obj) + obj->byte_and_use);
    if (nx < m_finish && ! nx->is_used()) {
      obj->next = nx->next;
      obj->prev = nx->prev;
      if (nx->next)
        nx->next->prev = obj;
      if (nx->prev)
        nx->prev->next = obj;
      obj->byte_and_use += nx->byte_and_use;
      obj = 0;
    }

    if (tmp == obj) {
        m_free->next->insert_next(obj);
    }
  }

  size_type max_size() const CPP_NOEXCEPT
  {
    size_type max = 0;
    Obj * obj = m_free->next;
    while (obj) {
      if (obj->byte_and_use > max) {
        max = obj->byte_and_use;
      }
      obj = obj->next;
    }
    return max;
  }

  bool expand_alloc(pointer * p, std::size_t n)
  {
    Obj * obj = reinterpret_cast<Obj*>(byte_cast(p) - Obj::_S_heap_size);
    std::size_t byte_use = obj->byte();
    Obj * nx = reinterpret_cast<Obj*>(byte_cast(obj) + byte_use);
    if (nx < m_finish && ! nx->is_used()) {
      std::size_t byte = Obj::aligned_size(n);
      byte_use += nx->byte_and_use;
      if (byte_use >= byte) {
        if (byte + sizeof(Obj) <= byte_use) {
          Obj * prev = nx->prev;
          Obj * next = nx->next;
          obj->byte_and_use = byte | Obj::_S_mask_use;
          nx = reinterpret_cast<Obj*>(byte_cast(nx) + nx->byte_and_use);
          nx->byte_and_use = byte_use - byte;
          nx->prev = prev;
          nx->next = next;
          if (prev)
            prev->next = nx;
          if (next)
            next->prev = nx;
        }
        else {
          obj->byte_and_use += nx->byte_and_use;
          nx->detach();
        }
        return true;
      }
    }
    return false;
  }

  void swap(range_allocator& other) CPP_NOEXCEPT
  {
    using std::swap;
    swap(m_finish, other.m_finish);
    swap(m_used, other.m_used);
    swap(m_free, other.m_free);
    allocator_swap<__allocator_base>(*this, other);
  }

private:
  struct Obj
  {
    static const std::size_t _S_self_align = sizeof(std::size_t) > sizeof(Obj*) ? sizeof(std::size_t) : sizeof(Obj*);
    static const std::size_t _S_T_byte = sizeof(T);
    static const std::size_t _S_heap_size = _S_self_align*3;
    static const std::size_t _S_mask_use = bit::left<std::size_t>::value;

    std::size_t byte_and_use;
    Obj * prev;
    Obj * next;
    T data[1];

    static std::size_t aligned_size(std::size_t n)
    {
      std::size_t __byte = n * _S_T_byte + _S_heap_size;
      return __byte + (_S_self_align - (__byte + _S_self_align) % _S_self_align);
    }

    std::size_t byte() const
    { return byte_and_use & ~_S_mask_use; }

    void insert_next(Obj* nx) {
        nx->next = next;
        nx->prev = this;
        if (next) {
            next->prev = nx;
        }
        next = nx;
    }

    void split_and_detach(std::size_t __byte)
    {
      Obj * nx = reinterpret_cast<Obj*>(byte_cast(this) + __byte);
      nx->byte_and_use = byte_and_use - __byte;
      byte_and_use = __byte;
      if (next) {
        next->prev = nx;
      }
      if (prev) {
        prev->next = nx;
      }
      nx->next = next;
      nx->prev = prev;
    }

    bool is_used() const
    { return byte_and_use & _S_mask_use; }

    void detach()
    {
      if (prev) {
        prev->next = next;
      }
      if (next) {
        next->prev = prev;
      }
    }
  };

  void * m_finish;
  Obj * m_used;
  Obj * m_free;

public:
  static const std::size_t heap_size = Obj::_S_heap_size * 2;
  static const std::size_t heap_element_size = Obj::_S_heap_size;
};


template<typename T, typename AllocBase>
bool operator==(const range_minimal_heap_allocator<T, AllocBase>& a,
                const range_minimal_heap_allocator<T, AllocBase>& b)
{ return &a == &b; }

template<typename T, typename AllocBase>
bool operator!=(const range_minimal_heap_allocator<T, AllocBase>& a,
                const range_minimal_heap_allocator<T, AllocBase>& b)
{ return &a != &b; }

template<typename T, typename AllocBase>
bool operator==(const range_fixed_allocator<T, AllocBase>& a,
                const range_fixed_allocator<T, AllocBase>& b)
{ return &a == &b; }

template<typename T, typename AllocBase>
bool operator!=(const range_fixed_allocator<T, AllocBase>& a,
                const range_fixed_allocator<T, AllocBase>& b)
{ return &a != &b; }

template<typename T, typename AllocBase>
bool operator==(const range_allocator<T, AllocBase>& a,
                const range_allocator<T, AllocBase>& b)
{ return &a == &b; }

template<typename T, typename AllocBase>
bool operator!=(const range_allocator<T, AllocBase>& a,
                const range_allocator<T, AllocBase>& b)
{ return &a != &b; }

template<typename T, typename AllocBase>
void swap(range_minimal_heap_allocator<T, AllocBase>& a,
          range_minimal_heap_allocator<T, AllocBase>& b)
{ a.swap(b); }

template<typename T, typename AllocBase>
void swap(range_fixed_allocator<T, AllocBase>& a,
          range_fixed_allocator<T, AllocBase>& b)
{ a.swap(b); }

template<typename T, typename AllocBase>
void swap(range_allocator<T, AllocBase>& a,
          range_allocator<T, AllocBase>& b)
{ a.swap(b); }
}

#endif
