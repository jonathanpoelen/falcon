#ifndef FALCON_MEMORY_DEEP_PTR_HPP
#define FALCON_MEMORY_DEEP_PTR_HPP

#include <falcon/memory/default_new.hpp>

#include <type_traits>
#include <memory>

namespace falcon {

template <class T, class Dp = std::default_delete<T>, class Cp = default_new<T>>
struct deep_ptr
{
public:
  using pointer = typename std::unique_ptr<T, Dp>::pointer;
  using element_type = T;
  using deleter_type = Dp;
  using copier_type = Cp;

private:
  struct Copier
  {
    Copier() noexcept = default;
    Copier(Copier const &) noexcept = default;

    Copier(typename std::conditional<std::is_reference<Cp>::value,
      Cp, const Cp&>::type c) noexcept
    : copier_(c)
    { }

    Copier(typename std::remove_reference<Cp>::type&& c) noexcept
    : copier_(std::move(c))
    { static_assert(!std::is_reference<Cp>::value,
      "rvalue copier bound to reference"); }

    template<class U, class Ep, class Fp, class = typename std::enable_if<
    (std::is_convertible<typename deep_ptr<U, Ep, Fp>::pointer, pointer>::value
      && !std::is_array<U>::value
      && std::conditional<std::is_reference<Cp>::value,
      std::is_same<Fp, Cp>,
      std::is_convertible<Fp, Cp>
      >::type::value)>::type>
    Copier(deep_ptr<U, Ep, Fp>&& u) noexcept
    : copier_(std::forward<Fp>(u.get_copier()))
    { }

    pointer operator()(pointer const & p) noexcept(noexcept(std::declval<Cp>()(*p)))
    { return copier_(*p); }

    Cp copier_;
  };

public:
  constexpr deep_ptr(std::nullptr_t) noexcept : deep_ptr() { }

  deep_ptr(deep_ptr const & other)
  : copier_(other.copier_)
  , ptr_{other ? copier_(other.get()) : nullptr} {}

  constexpr deep_ptr() noexcept
  : copier_()
  { static_assert(!std::is_pointer<copier_type>::value,
    "constructed with null function pointer copier"); }

  explicit
  deep_ptr(pointer p) noexcept
  : ptr_(p)
  { static_assert(!std::is_pointer<copier_type>::value,
    "constructed with null function pointer copier"); }

  deep_ptr(pointer p, Cp && c) noexcept
  : copier_(std::forward<Cp>(c))
  , ptr_(p)
  { }

  deep_ptr(pointer p, Dp && d) noexcept
  : ptr_(p, std::forward<Dp>(d))
  { }

  deep_ptr(pointer p, Dp && d, Cp && c) noexcept
  : copier_(std::forward<Cp>(c))
  , ptr_(p, std::forward<Dp>(d))
  { }

  deep_ptr(pointer p, Cp && c, Dp && d) noexcept
  : copier_(std::forward<Cp>(c))
  , ptr_(p, std::forward<Dp>(d))
  { }

  deep_ptr(deep_ptr&& other) noexcept
  : copier_(std::move(other))
  , ptr_(std::move(other.ptr_))
  { }

  template<class U, class _Dp, class _Cp>
  deep_ptr(deep_ptr<U, _Dp, _Cp>&& other) noexcept
  : copier_(std::forward<std::unique_ptr<U, _Dp>>(other))
  , ptr_(std::forward<_Cp>(other.ptr_))
  { }

  template<class U, class _Dp>
  deep_ptr(std::unique_ptr<U, _Dp> p) noexcept
  : ptr_(std::move(p))
  { }

  template<class U, class _Dp>
  deep_ptr(std::unique_ptr<U, _Dp> p, Cp && c) noexcept
  : copier_(std::forward<Cp>(c))
  , ptr_(std::move(p))
  { }

  deep_ptr& operator=(deep_ptr&& other) noexcept = default;

  template<class U, class _Dp, class _Cp>
  typename std::enable_if<
    (std::is_convertible<typename deep_ptr<U, _Dp, _Cp>::pointer, pointer>::value
    && !std::is_array<U>::value),
    deep_ptr&>::type
  operator=(deep_ptr<U, _Dp, _Cp>&& other) noexcept
  {
    ptr_ = std::forward<std::unique_ptr<T, Dp>>(other.ptr_);
    get_copier() = std::forward<_Cp>(other.get_copier());
    return *this;
  }

  deep_ptr& operator=(std::nullptr_t) noexcept
  {
    ptr_ = nullptr;
    return *this;
  }

  deep_ptr& operator=(deep_ptr const & other) noexcept(noexcept(std::declval<Cp>()(other.get())))
  {
    if (&other != this && other) {
      get_deleter() = other.get_deleter();
      get_copier() = other.get_copier();
      ptr_.reset(copier_(other.get()));
    }
    return *this;
  }

  pointer release()  noexcept { return ptr_.release(); }

  void swap(deep_ptr& other) noexcept
  {
    using std::swap;
    swap(copier_.copier_, other.copier_.copier_);
    ptr_.swap(other.ptr_);
  }

  void reset(pointer ptr = pointer()) noexcept { ptr_.reset(ptr); }
  void reset(std::nullptr_t) noexcept { ptr_.reset(nullptr); }
  template<class U> void reset(U p) noexcept { ptr_.reset(p); }

  pointer get() const noexcept { return ptr_.get(); }

  typename std::add_lvalue_reference<element_type>::type
  operator*() const { return *ptr_; }

  pointer operator->() const noexcept { return ptr_.get(); }
  explicit operator bool() const noexcept { return bool(ptr_); }

  deleter_type& get_deleter() noexcept { return ptr_.get_deleter(); }
  const deleter_type& get_deleter() const noexcept { return ptr_.get_deleter(); }

  copier_type& get_copier() noexcept { return copier_.copier_; }
  const copier_type& get_copier() const noexcept { return copier_.copier_; }

  T& operator[](size_t i) const { return ptr_[i]; }

private:
  Copier copier_;
  std::unique_ptr<T, Dp> ptr_;
};

template<class T, class Deleter, class Copier>
void swap(deep_ptr<T, Deleter, Copier> & lhs, deep_ptr<T, Deleter, Copier> & rhs) noexcept
{ lhs.swap(rhs); }


template<class T1, class D1, class C1, class T2, class D2, class C2>
bool operator==(const deep_ptr<T1, D1, C1>& x, const deep_ptr<T2, D2, C2>& y) noexcept
{ return x.get() == y.get(); }

template<class T1, class D1, class C1, class T2, class D2, class C2>
bool operator!=(const deep_ptr<T1, D1, C1>& x, const deep_ptr<T2, D2, C2>& y) noexcept
{ return x.get() != y.get(); }

template<class T1, class D1, class C1, class T2, class D2, class C2>
bool operator<(const deep_ptr<T1, D1, C1>& x, const deep_ptr<T2, D2, C2>& y) noexcept
{
  typedef typename std::common_type<
    typename deep_ptr<T1, D1, C1>::pointer
  , typename deep_ptr<T2, D2, C2>::pointer
  >::type CT;
  return std::less<CT>()(x.get(), y.get());
}

template<class T1, class D1, class C1, class T2, class D2, class C2>
bool operator<=(const deep_ptr<T1, D1, C1>& x, const deep_ptr<T2, D2, C2>& y) noexcept
{ return !(y < x); }

template<class T1, class D1, class C1, class T2, class D2, class C2>
bool operator>(const deep_ptr<T1, D1, C1>& x, const deep_ptr<T2, D2, C2>& y) noexcept
{ return y < x; }

template<class T1, class D1, class C1, class T2, class D2, class C2>
bool operator>=(const deep_ptr<T1, D1, C1>& x, const deep_ptr<T2, D2, C2>& y) noexcept
{ return !(x < y); }

template <class T, class D, class C>
bool operator==(const deep_ptr<T, D, C>& x, std::nullptr_t) noexcept
{ return !x; }

template <class T, class D, class C>
bool operator==(std::nullptr_t, const deep_ptr<T, D, C>& x) noexcept
{ return !x; }

template <class T, class D, class C>
bool operator!=(const deep_ptr<T, D, C>& x, std::nullptr_t) noexcept
{ return static_cast<bool>(x); }

template <class T, class D, class C>
bool operator!=(std::nullptr_t, const deep_ptr<T, D, C>& x) noexcept
{ return static_cast<bool>(x); }

template <class T, class D, class C>
bool operator<(const deep_ptr<T, D, C>& x, std::nullptr_t) noexcept
{ return std::less<typename deep_ptr<T, D, C>::pointer>()(x.get(), nullptr); }

template <class T, class D, class C>
bool operator<(std::nullptr_t, const deep_ptr<T, D, C>& y)
{ return std::less<typename deep_ptr<T, D, C>::pointer>()(nullptr, y.get()); }

template <class T, class D, class C>
bool operator<=(const deep_ptr<T, D, C>& x, std::nullptr_t) noexcept
{ return nullptr < x; }

template <class T, class D, class C>
bool operator<=(std::nullptr_t, const deep_ptr<T, D, C>& y) noexcept
{ return y < nullptr; }

template <class T, class D, class C>
bool operator>(const deep_ptr<T, D, C>& x, std::nullptr_t) noexcept
{ return !(nullptr < x); }

template <class T, class D, class C>
bool operator>(std::nullptr_t, const deep_ptr<T, D, C>& y) noexcept
{ return !(y < nullptr); }

template <class T, class D, class C>
bool operator>=(const deep_ptr<T, D, C>& x, std::nullptr_t) noexcept
{ return !(x < nullptr); }

template <class T, class D, class C>
bool operator>=(std::nullptr_t, const deep_ptr<T, D, C>& y) noexcept
{ return !(nullptr < y); }

template<class T, class... Ts>
deep_ptr<T> make_deep(Ts&&... args)
{ return deep_ptr<T>(std::forward<Ts>(args)...); }

}

namespace std {

template<class T, class Dp, class Cp>
struct hash< ::falcon::deep_ptr<T, Dp, Cp>>
: public hash<typename ::falcon::deep_ptr<T, Dp, Cp>::pointer>
{
  typename hash<typename ::falcon::deep_ptr<T, Dp, Cp>::pointer>::result_type
  operator()(const ::falcon::deep_ptr<T, Dp, Cp>& p) const noexcept
  { return std::hash<typename ::falcon::deep_ptr<T, Dp, Cp>::pointer>()(p.get()); }
};

}

#endif
