#ifndef FALCON_MEMORY_ALIGNED_BUFFER_HPP
#define FALCON_MEMORY_ALIGNED_BUFFER_HPP

#include <falcon/c++/noexcept.hpp>

#if __cplusplus >= 201103L
# include <type_traits>
#else
# include <boost/type_traits/aligned_storage.hpp>
# include <boost/type_traits/alignment_of.hpp>
#endif

namespace falcon {

template<typename T>
struct aligned_buffer
{
  typedef T value_type;
  typedef T* pointer;
  typedef const T* const_pointer;

private:
#if __cplusplus >= 201103L
  std::aligned_storage<sizeof(T), std::alignment_of<T>::value>
#else
  boost::aligned_storage<sizeof(T), boost::alignment_of<T>::value>
#endif
  storage_;

public:
  void*
  addr() CPP_NOEXCEPT
  { return static_cast<void*>(&storage_); }

  const void*
  addr() const CPP_NOEXCEPT
  { return static_cast<const void*>(&storage_); }

  T*
  ptr() CPP_NOEXCEPT
  { return static_cast<T*>(addr()); }

  const T*
  ptr() const CPP_NOEXCEPT
  { return static_cast<const T*>(addr()); }
};

}

#endif
