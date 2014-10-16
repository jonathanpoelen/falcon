#ifndef FALCON_MEMORY_ALLOCATE_HPP
#define FALCON_MEMORY_ALLOCATE_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>

#include <new>

namespace falcon {

template<class T>
struct default_nothrow_allocate
{
  typedef T* pointer;

  CPP_CONSTEXPR default_nothrow_allocate() {}

  T* operator()() const CPP_NOEXCEPT
  { return static_cast<T*>(::operator new(sizeof(T), std::nothrow)); }

  T* operator()(std::size_t n) const CPP_NOEXCEPT
  { return static_cast<T*>(::operator new(sizeof(T) * n, std::nothrow)); }
};

template<class T>
struct default_nothrow_allocate<T[]>
{
  typedef T* pointer;

  CPP_CONSTEXPR default_nothrow_allocate() {}

  T* operator()() const CPP_NOEXCEPT
  { return static_cast<T*>(::operator new[](sizeof(T), std::nothrow)); }

  T* operator()(std::size_t n) const CPP_NOEXCEPT
  { return static_cast<T*>(::operator new[](sizeof(T) * n, std::nothrow)); }
};


template<class T>
struct default_allocate
{
  typedef T* pointer;

  CPP_CONSTEXPR default_allocate() {}

  T* operator()() const
  { return static_cast<T*>(::operator new(sizeof(T))); }

  T* operator()(std::nothrow_t) const CPP_NOEXCEPT
  { return default_nothrow_allocate<T>()(); }

  T* operator()(std::size_t n) const
  { return static_cast<T*>(::operator new(sizeof(T) * n)); }

  T* operator()(std::size_t n, std::nothrow_t) const CPP_NOEXCEPT
  { return default_nothrow_allocate<T>()(n); }
};

template<class T>
struct default_allocate<T[]>
{
  typedef T* pointer;

  CPP_CONSTEXPR default_allocate() {}

  T* operator()() const
  { return static_cast<T*>(::operator new[](sizeof(T))); }

  T* operator()(std::nothrow_t) const CPP_NOEXCEPT
  { return default_nothrow_allocate<T[]>()(); }

  T* operator()(std::size_t n) const
  { return static_cast<T*>(::operator new[](sizeof(T) * n)); }

  T* operator()(std::size_t n, std::nothrow_t) const CPP_NOEXCEPT
  { return default_nothrow_allocate<T[]>()(n); }
};


template<class T>
typename default_nothrow_allocate<T>::pointer
nothrow_allocate(std::size_t n) CPP_NOEXCEPT
{ return default_nothrow_allocate<T>()(n); }

template<class T>
typename default_nothrow_allocate<T>::pointer
nothrow_allocate() CPP_NOEXCEPT
{ return default_nothrow_allocate<T>()(); }


template<class T>
typename default_allocate<T>::pointer
allocate()
{ return default_allocate<T>()(); }

template<class T>
typename default_nothrow_allocate<T>::pointer
allocate(std::nothrow_t) CPP_NOEXCEPT
{ return default_nothrow_allocate<T>()(); }

template<class T>
typename default_allocate<T>::pointer
allocate(std::size_t n)
{ return default_allocate<T>()(n); }

template<class T>
typename default_nothrow_allocate<T>::pointer
allocate(std::size_t n, std::nothrow_t) CPP_NOEXCEPT
{ return default_nothrow_allocate<T>()(n); }

}

#endif
