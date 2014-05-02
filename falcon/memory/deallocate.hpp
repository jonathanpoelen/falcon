#ifndef FALCON_MEMORY_DEALLOCATE_HPP
#define FALCON_MEMORY_DEALLOCATE_HPP

#include <falcon/c++/boost_or_std.hpp>

#include FALCON_BOOST_OR_STD_TRAITS(remove_extent)
#include <new>

namespace falcon {

template<typename T>
struct deallocate
{
  void operator()(T* p, std::size_t = 1) const
  { ::operator delete(p); }
};

template<typename T>
struct deallocate<T[]>
{
  void operator()(T* p, std::size_t = 1) const
  { ::operator delete[](p); }
};


template<typename T>
struct deallocate_then_zero
{
  void operator()(typename FALCON_BOOST_OR_STD_NAMESPACE::remove_extent<T>::type * & p,
                  std::size_t = 1) const
  {
    deallocate<T>()(p);
    p = 0;
  }
};


template<typename ForwardIterator>
void deallocater(ForwardIterator first, ForwardIterator last)
{
  typedef typename FALCON_BOOST_OR_STD_NAMESPACE::remove_pointer<
    typename std::iterator_traits<ForwardIterator>::value_type
  >::type pointer;
  deallocate<pointer> dealloc;
  for (; first != last; ++first) {
    dealloc(*first);
  }
}

template<typename ForwardIterator>
void deallocater_then_zero(ForwardIterator first, ForwardIterator last)
{
  typedef typename FALCON_BOOST_OR_STD_NAMESPACE::remove_pointer<
    typename std::iterator_traits<ForwardIterator>::value_type
  >::type pointer;
  deallocate_then_zero<pointer> dealloc;
  for (; first != last; ++first) {
    dealloc(*first);
    *first = 0;
  }
}

}

#endif
