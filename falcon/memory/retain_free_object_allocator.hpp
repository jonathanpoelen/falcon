#ifndef FALCON_MEMORY_RETAIN_FREE_OBJECT_ALLOCATOR_HPP
#define FALCON_MEMORY_RETAIN_FREE_OBJECT_ALLOCATOR_HPP

#include <falcon/memory/allocator_rebind.hpp>
#include <falcon/memory/deallocate.hpp>
#include <falcon/type_traits/if.hpp>
#include <falcon/bit/byte_cast.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(aligned_storage)

#include <memory>
#include <vector>
#include <algorithm>

namespace falcon {

struct retain_free_object_allocator_policies {
  typedef int policy;
  static const policy normal_storage   = 1 << 0;
  static const policy always_same_size = 1 << 2;
  static const policy speed_deduction  = 1 << 4;
};

namespace aux_ {
  template<class T, typename AllocBase
  , retain_free_object_allocator_policies::policy Policy
  , bool always_same_size
    = Policy & retain_free_object_allocator_policies::always_same_size>
  struct retain_free_object_allocator_traits
  {
    typedef typename allocator_rebind<AllocBase, T>::type allocator_base;
    typedef typename allocator_base::size_type size_type;
    typedef typename allocator_base::pointer pointer;
    typedef std::vector<size_type*> container_t;

    static const bool s_align = FALCON_BOOST_OR_STD_NAMESPACE::alignment_of<T>::value;
    static const bool s_heap = (s_align > sizeof(size_type)) ? s_align : sizeof(size_type);

    static pointer allocate(container_t& cont, size_type n)
    {
      if (Policy & retain_free_object_allocator_policies::speed_deduction) {
        struct EUpper {
          bool operator()(size_type * a, size_type * b) {
            return *a >= *b;
          }
        };
        typedef typename container_t::iterator iterator;
        iterator it = std::lower_bound(cont.begin(), cont.end(), &n, EUpper());
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
      size_type * p = reinterpret_cast<size_type*>(::operator new(s_heap + n*sizeof(T)));
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
        size_type * pf = reinterpret_cast<size_type*>(byte_cast(p) - s_heap);
        cont.insert(std::lower_bound(cont.begin(), cont.end(), pf, Upper()), pf);
      }
      else {
        cont.push_back(reinterpret_cast<size_type*>(byte_cast(p) - s_heap));
      }
    }

    static pointer ptr(void * p)
    { return reinterpret_cast<pointer>(byte_cast(p) + s_heap); }
  };

  template<class T, typename AllocBase
  , retain_free_object_allocator_policies::policy Policy>
  struct retain_free_object_allocator_traits<T, AllocBase, Policy, true>
  {
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
}

template<class T
, retain_free_object_allocator_policies::policy Policy
  = retain_free_object_allocator_policies::normal_storage
, typename AllocBase = std::allocator<T> >
class retain_free_object_allocator
#if defined(IN_IDE_PARSER)
: public std::allocator<T>
#else
: public aux_::retain_free_object_allocator_traits<T, AllocBase, Policy>::allocator_base
#endif
{
  typedef aux_::retain_free_object_allocator_traits<T, AllocBase, Policy> traits_;
  typedef typename traits_::container_t container_type_;
  typedef typename traits_::allocator_base allocator_base_;

public:
  typedef typename allocator_base_::pointer pointer;
  typedef typename allocator_base_::size_type size_type;

#if __cplusplus >= 201103L
  using propagate_on_container_copy_assignment = std::false_type;
  using propagate_on_container_move_assignment = std::true_type;
  using propagate_on_container_swap = std::true_type;
#endif

  template<class U
  , retain_free_object_allocator_policies::policy Policy2 = Policy
  , class AllocBase2 = AllocBase>
  struct rebind
  { typedef retain_free_object_allocator<U, Policy2, AllocBase2> other; };

  retain_free_object_allocator()
  : allocator_base_()
  , ptrs_()
  {}

  retain_free_object_allocator(const retain_free_object_allocator& other)
  : allocator_base_(other)
  , ptrs_()
  {}

#if __cplusplus >= 201103L
  retain_free_object_allocator(retain_free_object_allocator&& other)
  : allocator_base_(std::forward<allocator_base_>(other))
  , ptrs_(std::forward<std::vector<pointer>>(other.ptrs_))
  {}
#endif

  template<class U, retain_free_object_allocator_policies::policy Policy2, class AllocBase2>
  retain_free_object_allocator(const retain_free_object_allocator<U, Policy2, AllocBase2>& other)
  : allocator_base_(other)
  {}

  retain_free_object_allocator& operator=(const retain_free_object_allocator& other)
  {
    allocator_base_::operator=(other);
    return *this;
  }

#if __cplusplus >= 201103L
  retain_free_object_allocator& operator=(retain_free_object_allocator&& other)
  {
    allocator_base_::operator=(std::forward<allocator_base_>(other));
    other.ptrs_ = std::forward<std::vector<pointer>>(other.ptrs_);
    return *this;
  }
#endif

  pointer allocate(size_type n, const void * = 0)
  { return traits_::allocate(ptrs_, n); }

  void deallocate(pointer p, size_type n)
  { traits_::deallocate(ptrs_, p, n); }

  void clear()
  {
    deallocater(ptrs_.begin(), ptrs_.end());
    ptrs_.clear();
  }

private:
  container_type_ ptrs_;
};

}

#endif
