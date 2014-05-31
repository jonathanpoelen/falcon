#ifndef FALCON_MEMORY_CONSTRUCT_HPP
#define FALCON_MEMORY_CONSTRUCT_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/memory/addressof.hpp>

#if __cplusplus >= 201103L
# include <falcon/utility/unpack.hpp>
# include <falcon/parameter/parameter_index.hpp>
# include <falcon/memory/construct_category.hpp>
# include <falcon/tuple/array_compatibility.hpp>
# include <type_traits>
# include <utility>
#endif

namespace falcon {

/**
 * Constructs an object in existing memory by invoking an allocated
 * object's constructor with an initializer.
 */
CPP_GLOBAL_CONSTEXPR struct construct_t {
  template<class T>
  void operator()(T* p) const
  { new(p) T(); }

  template<class T>
  void operator()(T & p) const
  { operator()(addressof(p)); }

#if __cplusplus >= 201103L
  template<class T, class... Args>
  void operator()(T* p, Args&&... args) const
  { _construct<T>(construct_category_t<T>(), p, std::forward<Args>(args)...); }

  template<class T, class... Args>
  void operator()(T & p, Args&&... args) const
  { operator()(addressof(p), std::forward<Args>(args)...); }

private:
  template<class T, class... Args>
  void _construct(normal_ctor_tag, T* p, Args&&... args) const
  { new(p) T(std::forward<Args>(args)...); }

  template<class T, class... Args>
  void _construct(brace_init_tag, T* p, Args&&... args) const
  { new(p) T{std::forward<Args>(args)...}; }

  template<class T>
  void _construct(brace_init_tag, T* p, T&& val) const
  { new(p) T(std::forward<T>(val)); }

  template<class T>
  void _construct(brace_init_tag, T* p, const T& val) const
  { new(p) T(val); }

  template<class T, class... Args>
  void _construct(double_brace_init_tag, T* p, Args&&... args) const
  { new(p) T{{std::forward<Args>(args)...}}; }

  template<class T, std::size_t... Indexes>
  void _dispatch_construct(
    std::false_type, T* p, T&& val, falcon::parameter_index<Indexes...>) const
  { new(p) T{get<Indexes>(std::forward<T>(val))...}; }

  template<class T, std::size_t... Indexes>
  void _dispatch_construct(
    std::true_type, T* p, T&& val, falcon::parameter_index<Indexes...>) const
  {
    auto ref = &(*p)[0];
    FALCON_UNPACK(operator()(ref++, get<Indexes>(std::forward<T>(val))));
  }

  template<class T>
  void _construct(dispatch_index_tag, T* p, T&& val) const
  {
    typedef typename std::remove_extent<T>::type value_type;
    _dispatch_construct<T>(
      std::is_array<value_type>(), p, std::forward<T>(val),
      typename falcon::build_parameter_index<std::tuple_size<T>::value>::type()
    );
  }

  template<class T, std::size_t... Indexes>
  void _dispatch_construct(
    std::false_type, T* p, const T& val, falcon::parameter_index<Indexes...>) const
  { new(p) T{get<Indexes>(val)...}; }

  template<class T, std::size_t... Indexes>
  void _dispatch_construct(
    std::true_type, T* p, const T& val, falcon::parameter_index<Indexes...>) const
  {
    auto ref = &(*p)[0];
    FALCON_UNPACK(operator()(ref++, get<Indexes>(val)));
  }

  template<class T>
  void _construct(dispatch_index_tag, T* p, const T& val) const
  {
    typedef typename std::remove_extent<T>::type value_type;
    _dispatch_construct<T>(
      std::is_array<value_type>(),
      p, val,
      typename falcon::build_parameter_index<std::tuple_size<T>::value>::type()
    );
  }

  template<class T>
  void _construct(dispatch_index_tag, T* p, T& val) const
  {
    typedef typename std::remove_extent<T>::type value_type;
    _dispatch_construct<T>(
      std::is_array<value_type>(),
      p, val,
      typename falcon::build_parameter_index<std::tuple_size<T>::value>::type()
    );
  }

  template<class T, class... Args>
  void _dispatch_construct_array_elems(std::false_type, T* p, Args&&... args) const
  { new(p) T{std::forward<Args>(args)...}; }

  template<class T, class... Args>
  void _dispatch_construct_array_elems(std::true_type, T* p, Args&&... args) const
  {
    typedef typename std::remove_all_extents<T>::type type;
    typedef std::integral_constant<std::size_t, sizeof(T)/sizeof(type)> integral;
    new(p) type[integral::value]{std::forward<Args>(args)...};
  }

  template<class T, class U, class... Args>
  void _dispatch_construct_array_elems(
    std::true_type, T* p, std::initializer_list<U> ilist, Args&&... other) const
  {
    static_assert(
      std::rank<T>::value < sizeof...(other)+1, "too many initializers for ‘T");
    auto ref = &p[0];
    operator()(ref, ilist)
    FALCON_UNPACK(operator()(++ref, other));
  }

  template<class T, class... Args>
  void _construct(dispatch_index_tag, T* p, Args&&... args) const
  {
    typedef typename std::remove_extent<T>::type value_type;
    _dispatch_construct_array_elems(
      std::is_array<value_type>(), p, std::forward<Args>(args)...);
  }
#else
  template<class T, class U>
  void operator()(T* p, const U& value) const
  { new(p) T(value); }

  template<class T, class U>
  void operator()(T & p, const U& value) const
  { operator()(addressof(p), value); }
#endif
} construct;

}

#endif
