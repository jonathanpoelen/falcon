#ifndef FALCON_MEMORY_RECONSTRUCT_HPP
#define FALCON_MEMORY_RECONSTRUCT_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/memory/destroy.hpp>
#include <falcon/memory/construct.hpp>
#include <falcon/memory/default_new.hpp>
#include <falcon/memory/default_delete.hpp>

//reconstruct, renew, emplace_new, nothrow_renew, nothrow_emplace_new

namespace falcon {

CPP_GLOBAL_CONSTEXPR struct reconstruct_t {
  CPP_CONSTEXPR reconstruct_t() {}
#if __cplusplus >= 201103L
  template<class T, class... Args>
  void operator()(T* p, Args&&... args) const
  noexcept(noexcept(construct(p, std::forward<Args>(args)...)))
  {
    destroy(p);
    construct(p, std::forward<Args>(args)...);
  }
#else
  template<class T>
  void operator()(T* p) const
  {
    destroy(p);
    construct(p);
  }
  template<class T, class U>
  void operator()(T* p, const U& value) const
  {
    destroy(p);
    construct(p, value);
  }
#endif
} reconstruct;


CPP_GLOBAL_CONSTEXPR struct nothrow_renew_t {
  CPP_CONSTEXPR nothrow_renew_t() {}
#if __cplusplus >= 201103L
  template<class T, class... Args>
  T* operator()(T* p, Args&&... args) const noexcept
  {
    default_delete<T>()(p);
    return nothrow_default_new<T>()()(std::forward<Args>(args)...);
  }
#else
  template<class T>
  T* operator()(T* p) const throw()
  {
    default_delete<T>()(p);
    return nothrow_default_new<T>()();
  }

  template<class T, class U>
  T* operator()(T* p, const U& value) const throw()
  {
    default_delete<T>()(p);
    return nothrow_default_new<T>()(value);
  }
#endif
} nothrow_renew;


CPP_GLOBAL_CONSTEXPR struct renew_t {
  CPP_CONSTEXPR renew_t() {}
#if __cplusplus >= 201103L
  template<class T, class... Args>
  T* operator()(T* p, Args&&... args) const
  {
    default_delete<T>()(p);
    return default_new<T>()(std::forward<Args>(args)...);
  }

  template<class T, class... Args>
  T* operator()(std::nothrow_t, T* p, Args&&... args) const noexcept
  {
    default_delete<T>()(p);
    return nothrow_default_new<T>()(std::forward<Args>(args)...);
  }
#else
  template<class T>
  T* operator()(T* p) const
  {
    default_delete<T>()(p);
    return default_new<T>()();
  }

  template<class T, class U>
  T* operator()(T* p, const U& value) const
  {
    default_delete<T>()(p);
    return default_new<T>()(value);
  }

  template<class T>
  T* operator()(std::nothrow_t, T* p) const
  {
    default_delete<T>()(p);
    return nothrow_default_new<T>()();
  }

  template<class T, class U>
  T* operator()(std::nothrow_t, T* p, const U& value) const
  {
    default_delete<T>()(p);
    return nothrow_default_new<T>()(value);
  }
#endif
} renew;


CPP_GLOBAL_CONSTEXPR struct nothrow_emplace_new_t {
  CPP_CONSTEXPR nothrow_emplace_new_t() {}
#if __cplusplus >= 201103L
  template<class T, class... Args>
  T* operator()(T* p, Args&&... args) const noexcept
  {
    return p
      ? reconstruct(p, std::forward<Args>(args)...), p
      : nothrow_default_new<T>()(std::forward<Args>(args)...);
  }
#else
  template<class T>
  T* operator()(T* p) const throw()
  { return p ? reconstruct(p), p : nothrow_default_new<T>()(); }

  template<class T, class U>
  T* operator()(T* p, const U& value) const throw()
  { return p ? reconstruct(p, value), p : nothrow_default_new<T>()(value); }
#endif
} nothrow_emplace_new;


CPP_GLOBAL_CONSTEXPR struct emplace_new_t {
  CPP_CONSTEXPR emplace_new_t() {}
#if __cplusplus >= 201103L
  template<class T, class... Args>
  T* operator()(T* p, Args&&... args) const
  {
    return p
      ? reconstruct(p, std::forward<Args>(args)...), p
      : default_new<T>()(std::forward<Args>(args)...);
  }

  template<class T, class... Args>
  T* operator()(std::nothrow_t, T* p, Args&&... args) const noexcept
  {
    return p
      ? reconstruct(p, std::forward<Args>(args)...), p
      : nothrow_default_new<T>()(std::forward<Args>(args)...);
  }
#else
  template<class T>
  T* operator()(T* p) const
  { return p ? reconstruct(p), p : default_new<T>()(); }

  template<class T, class U>
  T* operator()(T* p, const U& value) const
  { return p ? reconstruct(p, value), p : default_new<T>()(value); }

  template<class T>
  T* operator()(std::nothrow_t, T* p) const throw()
  { return p ? reconstruct(p), p : nothrow_default_new<T>()(); }

  template<class T, class U>
  T* operator()(std::nothrow_t, T* p, const U& value) const throw()
  { return p ? reconstruct(p, value), p : nothrow_default_new<T>()(value); }
#endif
} emplace_new;

}

#endif
