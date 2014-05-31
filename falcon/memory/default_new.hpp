#ifndef FALCON_MEMORY_DEFAULT_NEW_HPP
#define FALCON_MEMORY_DEFAULT_NEW_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/boost_or_std.hpp>

#if __cplusplus >= 201103L
# include <falcon/memory/construct_category.hpp>
# include <utility>
#else
# include <boost/type_traits/remove_extent.hpp>
#endif

# include <new>

namespace falcon {

template<class T>
struct nothrow_default_new
{
  typedef typename FALCON_BOOST_OR_STD_NAMESPACE::remove_extent<T>::type * pointer;

  pointer operator()() const CPP_NOEXCEPT
  { return new(std::nothrow) T(); }

#if __cplusplus >= 201103L
  template<class... Args>
  pointer operator()(Args&&... args) const noexcept
  { return _default_new(construct_category_t<T>(), std::forward<Args>(args)...); }

private:
  template<class... Args>
  T* _default_new(normal_ctor_tag, Args&&... args) const noexcept
  { return new(std::nothrow) T(std::forward<Args>(args)...); }

  template<class... Args>
  pointer _default_new(dispatch_index_tag, Args&&... args) const noexcept
  { return new(std::nothrow) T{std::forward<Args>(args)...}; }

  template<class... Args>
  T* _default_new(brace_init_tag, Args&&... args) const noexcept
  { return new(std::nothrow) T{std::forward<Args>(args)...}; }

  T* _default_new(brace_init_tag, T&& val) const noexcept
  { return new(std::nothrow) T(std::forward<T>(val)); }

  T* _default_new(brace_init_tag, const T& val) const noexcept
  { return new(std::nothrow) T(val); }

  template<class... Args>
  T* _default_new(double_brace_init_tag, Args&&... args) const noexcept
  { return new(std::nothrow) T{{std::forward<Args>(args)...}}; }
#else
  template<class U>
  T* operator()(const U& value) const throw()
  { return ::new (std::nothrow) T(value); }
#endif
};


template<class T>
struct default_new
{
  typedef typename FALCON_BOOST_OR_STD_NAMESPACE::remove_extent<T>::type * pointer;

  pointer operator()() const CPP_NOEXCEPT_OPERATOR2(T())
  { return new T(); }

  pointer operator()(std::nothrow_t) const CPP_NOEXCEPT
  { return nothrow_default_new<T>()(); }

#if __cplusplus >= 201103L
  template<class... Args>
  pointer operator()(Args&&... args) const
  CPP_NOEXCEPT_OPERATOR2(std::declval<default_new>()._default_new(
    construct_category_t<T>(), std::forward<Args>(args)...))
  { return _default_new(construct_category_t<T>(), std::forward<Args>(args)...); }

  template<class... Args>
  pointer operator()(std::nothrow_t, Args&&... args) const CPP_NOEXCEPT
  { return nothrow_default_new<T>()(std::forward<Args>(args)...); }

private:
  template<class... Args>
  T* _default_new(normal_ctor_tag, Args&&... args) const
  CPP_NOEXCEPT_OPERATOR2(new T(std::forward<Args>(args)...))
  { return new T(std::forward<Args>(args)...); }

  template<class... Args>
  pointer _default_new(dispatch_index_tag, Args&&... args) const
  CPP_NOEXCEPT_OPERATOR2(new T{std::forward<Args>(args)...})
  { return new T{std::forward<Args>(args)...}; }

  template<class... Args>
  T* _default_new(brace_init_tag, Args&&... args) const
  CPP_NOEXCEPT_OPERATOR2(new T{std::forward<Args>(args)...})
  { return new T{std::forward<Args>(args)...}; }

  T* _default_new(brace_init_tag, T&& val) const
  CPP_NOEXCEPT_OPERATOR2(new T(std::forward<T>(val)))
  { return new T(std::forward<T>(val)); }

  T* _default_new(brace_init_tag, const T& val) const
  CPP_NOEXCEPT_OPERATOR2(T(val))
  { return new T(val); }

  template<class... Args>
  T* _default_new(double_brace_init_tag, Args&&... args) const
  CPP_NOEXCEPT_OPERATOR2(new T{{std::forward<Args>(args)...}})
  { return new T{{std::forward<Args>(args)...}}; }
#else
  template<class U>
  T* operator()(const U& value) const
  { return ::new T(value); }
#endif
};


CPP_GLOBAL_CONSTEXPR struct nothrow_new_ptr_t {
  template<class T>
  void operator()(T * p) const
  { nothrow_default_new<T>()(p); }
} nothrow_new_ptr;

CPP_GLOBAL_CONSTEXPR struct nothrow_new_array_t {
  template<class T>
  void operator()(T * p) const
  { nothrow_default_new<T[]>()(p); }
} nothrow_new_array;

CPP_GLOBAL_CONSTEXPR struct new_ptr_t {
  template<class T>
  void operator()(T * p) const
  { default_new<T>()(p); }
} new_ptr;

CPP_GLOBAL_CONSTEXPR struct new_array_t {
  template<class T>
  void operator()(T * p) const
  { default_new<T[]>()(p); }
} new_array;

}

#endif
