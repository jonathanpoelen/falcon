#ifndef FALCON_MEMORY_ALLOCATE_HPP
#define FALCON_MEMORY_ALLOCATE_HPP

#include <falcon/c++/noexcept.hpp>

#include <new>

namespace falcon {

template<class T>
struct nothrow_allocate
{
  typedef T* pointer;

  T* operator()() const CPP_NOEXCEPT
  { return static_cast<T*>(::operator new(sizeof(T), std::nothrow)); }

  T* operator()(std::size_t n) const CPP_NOEXCEPT
  {
    if (n > (std::size_t(-1u) / sizeof(T))) {
      std::bad_alloc();
    }
    return static_cast<T*>(::operator new(sizeof(T) * n, std::nothrow));
  }
};


template<class T>
struct allocate
{
  typedef T* pointer;

  T* operator()() const
  { return static_cast<T*>(::operator new(sizeof(T))); }

  T* operator()(std::nothrow_t) const CPP_NOEXCEPT
  { return nothrow_allocate<T>()(); }

  T* operator()(std::size_t n) const
  {
    if (n > (std::size_t(-1u) / sizeof(T))) {
      std::bad_alloc();
    }
    return static_cast<T*>(::operator new(sizeof(T) * n));
  }

  T* operator()(std::size_t n, std::nothrow_t) const CPP_NOEXCEPT
  { return nothrow_allocate<T>()(n); }
};

}

#endif
