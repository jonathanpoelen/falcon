#ifndef FALCON_MEMORY_ALLOCATOR_SWAP_HPP
#define FALCON_MEMORY_ALLOCATOR_SWAP_HPP

#if __cplusplus <= 201103L

#include <memory>

namespace falcon {

namespace _aux {
  template<class Allocator>
  void allocator_swap_impl(Allocator&, Allocator&, std::false_type)
  {}

  template<class Allocator>
  void allocator_swap_impl(Allocator& a, Allocator& b, std::true_type)
  {
    using std::swap;
    swap(a, b);
  }
}

template<class Allocator>
void allocator_swap(Allocator& a, Allocator& b)
{
  ::falcon::_aux::allocator_swap_impl(
    a, b, typename std::allocator_traits<Allocator>::propagate_on_container_swap()
  );
}

}

#else

#include <falcon/sfinae/has_type.hpp>

namespace falcon {

namespace _aux {
  FALCON_CLASS_HAS_TYPE(propagate_on_container_swap);

  template<class Allocator,
    bool = has_propagate_on_container_swap<Allocator>::value>
  struct allocator_swap_impl
  {
    static void swap(Allocator&, Allocator&)
    {}
  };

  template<class Allocator>
  struct allocator_swap_impl<Allocator, true>
  {
    static void swap_impl(Allocator& a, Allocator& b, std::true_type)
    {
      using std::swap;
      swap(a, b);
    }
    static void swap_impl(Allocator&, Allocator&, std::false_type)
    {}
    static void swap(Allocator& a, Allocator& b)
    {
      typedef typename Allocator::propagate_on_container_swap propagate;
      swap_impl(a, b, propagate());
    }
  };
}

template<class Allocator>
void allocator_swap(Allocator& a, Allocator& b)
{ ::falcon::_aux::allocator_swap_impl<Allocator>::swap(a, b); }

}

#endif

#endif
