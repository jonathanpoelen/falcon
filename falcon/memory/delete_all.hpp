#ifndef FALCON_MEMORY_DELETE_ALL_HPP
#define FALCON_MEMORY_DELETE_ALL_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/container/range_access.hpp>
#include <falcon/memory/default_delete.hpp>

namespace falcon
{

CPP_GLOBAL_CONSTEXPR struct delete_all_t
{
  template<class ForwardIterator>
  void operator()(ForwardIterator first, ForwardIterator last) const
  { default_deleter(first, last); }

  template<class Container>
  void operator()(Container& container) const
  { default_deleter(begin(container), end(container)); }
} delete_all;

}

#endif
