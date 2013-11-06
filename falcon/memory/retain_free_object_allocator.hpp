#ifndef FALCON_MEMORY_RETAIN_FREE_OBJECT_ALLOCATOR_HPP
#define FALCON_MEMORY_RETAIN_FREE_OBJECT_ALLOCATOR_HPP

#include <falcon/algorithm/dichotomic_algorithm.hpp>
#include <falcon/memory/allocator_rebind.hpp>
#include <falcon/type_traits/if.hpp>
#include <falcon/bit/byte_cast.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(aligned_storage)

#include <memory>
#include <vector>

namespace falcon {

struct retain_free_object_allocator_policies {
  typedef int policy;
  static const policy normal_storage   = 1 << 0;
  static const policy always_same_size = 1 << 2;
  static const policy speed_deduction  = 1 << 4;
};

template<typename T, typename AllocBase
  , retain_free_object_allocator_policies::policy Policy
  , bool always_same_size
    = (Policy & retain_free_object_allocator_policies::always_same_size)>
struct __retain_free_object_allocator_traits {
  typedef typename allocator_rebind<AllocBase, T>::type allocator_base;
  typedef typename allocator_base::size_type size_type;
  typedef typename allocator_base::pointer pointer;
  typedef std::vector<size_type*> container_t;

  static const bool _S_align = FALCON_BOOST_OR_STD_NAMESPACE::alignment_of<T>::value;
  static const bool _S_heap = (_S_align > sizeof(size_type)) ? _S_align : sizeof(size_type);

  static pointer allocate(container_t& cont, size_type n)
  {
    if (Policy & retain_free_object_allocator_policies::speed_deduction) {
      struct EUpper {
        bool operator()(size_type * a, size_type * b) {
          return *a >= *b;
        }
      };
      typedef typename container_t::iterator iterator;
      iterator it = dichotomic_lower_bound(cont.begin(), cont.end(), &n, EUpper());
      if (it != cont.end()) {
        pointer ret = ptr(*it);
        cont.erase(it);
        return ret;
      }
    }
    else {
      for (std::size_t pos = 0, max = cont.size(); pos < max; ++pos) {
        if (*cont[pos] >= n) {
          pointer ret = ptr(cont[pos]);
          cont[pos] = cont.back();
          cont.pop_back();
          return ret;
        }
      }
    }
    size_type * p = reinterpret_cast<size_type*>(::operator new(_S_heap + n*sizeof(T)));
    *p = n;
    return ptr(p);
  }

  static void deallocate(container_t& cont, pointer p, size_type)
  {
    if (Policy & retain_free_object_allocator_policies::speed_deduction) {
      struct Upper {
        bool operator()(size_type * a, size_type * b) {
          return *a > *b;
        }
      };
      size_type * pf = reinterpret_cast<size_type*>(byte_cast(p) - _S_heap);
      cont.insert(dichotomic_lower_bound(cont.begin(), cont.end(), pf, Upper()), pf);
    }
    else {
      cont.push_back(reinterpret_cast<size_type*>(byte_cast(p) - _S_heap));
    }
  }

  static pointer ptr(void * p)
  { return reinterpret_cast<pointer>(byte_cast(p) + _S_heap); }
};

template<typename T, typename AllocBase, retain_free_object_allocator_policies::policy Policy>
struct __retain_free_object_allocator_traits<T, AllocBase, Policy, true> {
  typedef typename allocator_rebind<AllocBase, T>::type allocator_base;
  typedef typename allocator_base::size_type size_type;
  typedef typename allocator_base::pointer pointer;
  typedef std::vector<pointer> container_t;

  static pointer allocate(container_t& cont, size_type)
  {
    if (cont.empty()) {
      return static_cast<pointer>(::operator new(sizeof(T)));
    }
    pointer ret = cont.back();
    cont.pop_back();
    return ret;
  }

  static void deallocate(container_t& cont, pointer p, size_type)
  { cont.push_back(p); }
};

template<typename T
  , retain_free_object_allocator_policies::policy Policy
    = retain_free_object_allocator_policies::normal_storage,
  typename AllocBase = std::allocator<T> >
class retain_free_object_allocator
#if defined(IN_IDE_PARSER)
: public std::allocator<T>
#else
: public __retain_free_object_allocator_traits<T, AllocBase, Policy>::allocator_base
#endif
{
  typedef __retain_free_object_allocator_traits<T, AllocBase, Policy> __traits;
  typedef typename __traits::container_t __container_type;
  typedef typename __traits::allocator_base __allocator_base;

public:
  typedef typename __allocator_base::pointer pointer;
  typedef typename __allocator_base::size_type size_type;

#if __cplusplus <= 201103L
  using propagate_on_container_copy_assignment = std::false_type;
  using propagate_on_container_move_assignment = std::true_type;
  using propagate_on_container_swap = std::true_type;
#endif

  template<typename U,
      retain_free_object_allocator_policies::policy Policy2 = Policy,
      typename AllocBase2 = AllocBase>
  struct rebind
  { typedef retain_free_object_allocator<U, Policy2, AllocBase2> other; };

  retain_free_object_allocator()
  : __allocator_base()
  , m_ptrs()
  {}

  retain_free_object_allocator(const retain_free_object_allocator& other)
  : __allocator_base(other)
  , m_ptrs()
  {}

#if __cplusplus <= 201103L
  retain_free_object_allocator(retain_free_object_allocator&& other)
  : __allocator_base(std::forward<__allocator_base>(other))
  , m_ptrs(std::forward<std::vector<pointer>>(other.m_ptrs))
  {}
#endif

  template<typename U, retain_free_object_allocator_policies::policy Policy2, typename AllocBase2>
  retain_free_object_allocator(const retain_free_object_allocator<U, Policy2, AllocBase2>& other)
  : __allocator_base(other)
  {}

  ~retain_free_object_allocator()
  { remove_ptr(); }

  retain_free_object_allocator& operator=(const retain_free_object_allocator& other)
  {
    __allocator_base::operator=(other);
    return *this;
  }

#if __cplusplus <= 201103L
  retain_free_object_allocator& operator=(retain_free_object_allocator&& other)
  {
    __allocator_base::operator=(std::forward<__allocator_base>(other));
    other.m_ptrs = std::forward<std::vector<pointer>>(other.m_ptrs);
    return *this;
  }
#endif

  pointer allocate(size_type n, const void * = 0)
  { return __traits::allocate(m_ptrs, n); }

  void deallocate(pointer p, size_type n)
  { __traits::deallocate(m_ptrs, p, n); }

  void clear()
  {
    remove_ptr();
    m_ptrs.clear();
  }

private:
  __container_type m_ptrs;

  void remove_ptr()
  {
    typedef typename __container_type::iterator iterator;
    for (iterator first = m_ptrs.begin(), last = m_ptrs.end(); first != last; ++first) {
      ::operator delete(*first);
    }
  }
};

}

#endif
