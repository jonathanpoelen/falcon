#ifndef FALCON_MEMORY_DEEP_PTR_HPP
#define FALCON_MEMORY_DEEP_PTR_HPP

#include <falcon/memory/default_new.hpp>

#include <type_traits>
#include <memory>

namespace falcon {

template <class T, class Dp = std::default_delete<T>, class Cp = default_new<T>>
struct deep_ptr
{
  using pointer = typename std::unique_ptr<T, Dp>::pointer;
  using element_type = T;
  using deleter_type = Dp;
  using copier_type = Cp;

private:
  template<class U, class Ep, class Fp>
  struct IsEnable
  : std::integral_constant<
    bool,
    (std::is_convertible<typename deep_ptr<U, Ep, Fp>::pointer, pointer>::value
    && !std::is_array<U>::value
    && std::conditional<std::is_reference<Cp>::value,
      std::is_same<Fp, Cp>,
      std::is_convertible<Fp, Cp>
    >::type::value)
  > {};

  template<class U, class Ep, class Fp, bool b = true>
  struct EnableIf
  : std::enable_if<b == IsEnable<U, Ep, Fp>::value>
  {};

  using unique_ptr = std::unique_ptr<T, Dp>;

public:
  constexpr deep_ptr() noexcept
  { static_assert(!std::is_pointer<copier_type>::value,
    "constructed with null function pointer copier"); }

  explicit deep_ptr(pointer p)
  :t(unique_ptr(p), copier_type())
  { static_assert(!std::is_pointer<copier_type>::value,
    "constructed with null function pointer copier"); }

  deep_ptr(deep_ptr const & other)
  : t(unique_ptr{other
    ? other.get_copier()(*other.get())
    : pointer(), other.get_deleter()}, other.get_copier())
  {}

  deep_ptr(deep_ptr && other)
  : t(std::move(std::get<0>(other.t)), std::forward<copier_type>(other.get_copier()))
  {}

  template<class U, class Dp2, class Cp2, class = typename EnableIf<T, Dp2, Cp2>::type>
  deep_ptr(const deep_ptr<U, Dp2, Cp2> & other)
  : t(unique_ptr{other
    ? other.get_copier()(*other.get())
    : pointer(), other.get_deleter()}, other.get_copier())
  {}

  template<class U, class Dp2, class Cp2, class = typename EnableIf<U, Dp2, Cp2>::type>
  deep_ptr(deep_ptr<U, Dp2, Cp2> && other)
  : t(std::move(std::get<0>(other.t)), std::forward<copier_type>(other.get_copier()))
  {}

private:
  template<class Cp2>
  deep_ptr(pointer p, Cp2 && c, std::true_type)
  : t(unique_ptr(p), std::forward<Cp2>(c))
  {}

  template<class Dp2>
  deep_ptr(pointer p, Dp2 && d, std::false_type)
  : t({unique_ptr(p), std::forward<Dp2>(d)}, copier_type())
  { static_assert(!std::is_pointer<copier_type>::value,
    "constructed with null function pointer copier"); }

  template<class Dp2, class Cp2>
  deep_ptr(pointer p, Dp2 && d, Cp2 && c, std::true_type)
  : t({p, std::forward<Dp2>(d)}, std::forward<Cp2>(c))
  {}

  template<class Cp2, class Dp2>
  deep_ptr(pointer p, Cp2 && c, Dp2 && d, std::false_type)
  : t({p, std::forward<Dp2>(d)}, std::forward<Cp2>(c))
  {}

public:
  template<class Cp2>
  deep_ptr(pointer p, Cp2 && c)
  : deep_ptr(p, std::forward<Cp2>(c), IsEnable<T, Dp, Cp2>())
  {}

  template<class Dp2, class Cp2, class = typename EnableIf<T, Dp, Cp2>::type>
  deep_ptr(pointer p, Dp2 && d, Cp2 && c)
  : deep_ptr(p, std::forward<Dp2>(d), std::forward<Cp2>(c), IsEnable<T, Dp, Cp2>())
  {}

  template<class U, class Dp2>
  deep_ptr(std::unique_ptr<U, Dp2> p)
  : t(std::move(p), copier_type())
  { static_assert(!std::is_pointer<copier_type>::value,
    "constructed with null function pointer copier"); }

  template<class U, class Dp2, class Cp2, class = typename EnableIf<T, Dp, Cp2>::type>
  deep_ptr(std::unique_ptr<U, Dp2> p, Cp2 && c)
  : t(std::move(p), std::forward<Cp2>(c))
  {}

  deep_ptr& operator=(deep_ptr&& other)
  {
    std::get<0>(t) = std::move(std::get<0>(other.t));
    std::get<1>(t) = std::forward<copier_type>(other.get_copier());
    return *this;
  }

  template<class U, class Dp2, class Cp2>
  typename std::enable_if<
    (std::is_convertible<typename deep_ptr<U, Dp2, Cp2>::pointer, pointer>::value
    && !std::is_array<U>::value),
    deep_ptr&
  >::type
  operator=(deep_ptr<U, Dp2, Cp2>&& other)
  {
    std::get<0>(t) = std::move(std::get<0>(other.t));
    std::get<1>(t) = std::forward<copier_type>(other.get_copier());
    return *this;
  }

  deep_ptr& operator=(std::nullptr_t)
  {
    reset(nullptr);
    return *this;
  }

  deep_ptr& operator=(deep_ptr const & other)
  {
    if (&other != this) {
      get_deleter() = other.get_deleter();
      get_copier() = other.get_copier();
      if (other) {
        reset(nullptr);
      }
      else {
        reset(other.get_copier()(*other.get()));
      }
    }
    return *this;
  }

  pointer release() { return std::get<0>(t).release(); }

  void swap(deep_ptr& other) { std::swap(t, other.t); }

  void reset(pointer ptr = pointer()) { std::get<0>(t).reset(ptr); }
  void reset(std::nullptr_t) { std::get<0>(t).reset(nullptr); }
  template<class U> void reset(U p) { std::get<0>(t).reset(p); }

  pointer get() const { return std::get<0>(t).get(); }

  typename std::add_lvalue_reference<element_type>::type
  operator*() const { return *std::get<0>(t); }

  pointer operator->() const { return std::get<0>(t).get(); }
  explicit operator bool() const { return bool(std::get<0>(t)); }

  deleter_type& get_deleter() noexcept { return std::get<0>(t).get_deleter(); }
  const deleter_type& get_deleter() const noexcept { return std::get<0>(t).get_deleter(); }

  copier_type& get_copier() noexcept { return std::get<1>(t); }
  const copier_type& get_copier() const noexcept { return std::get<1>(t); }

  T& operator[](size_t i) const { return std::get<0>(t)[i]; }

private:
  std::tuple<std::unique_ptr<T, Dp>, copier_type> t;
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
bool operator<=(const deep_ptr<T1, D1, C1>& x, const deep_ptr<T2, D2, C2>& y)
{ return !(y < x); }

template<class T1, class D1, class C1, class T2, class D2, class C2>
bool operator>(const deep_ptr<T1, D1, C1>& x, const deep_ptr<T2, D2, C2>& y)
{ return y < x; }

template<class T1, class D1, class C1, class T2, class D2, class C2>
bool operator>=(const deep_ptr<T1, D1, C1>& x, const deep_ptr<T2, D2, C2>& y)
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
bool operator<(const deep_ptr<T, D, C>& x, std::nullptr_t)
{ return std::less<typename deep_ptr<T, D, C>::pointer>()(x.get(), nullptr); }

template <class T, class D, class C>
bool operator<(std::nullptr_t, const deep_ptr<T, D, C>& y)
{ return std::less<typename deep_ptr<T, D, C>::pointer>()(nullptr, y.get()); }

template <class T, class D, class C>
bool operator<=(const deep_ptr<T, D, C>& x, std::nullptr_t)
{ return nullptr < x; }

template <class T, class D, class C>
bool operator<=(std::nullptr_t, const deep_ptr<T, D, C>& y)
{ return y < nullptr; }

template <class T, class D, class C>
bool operator>(const deep_ptr<T, D, C>& x, std::nullptr_t)
{ return !(nullptr < x); }

template <class T, class D, class C>
bool operator>(std::nullptr_t, const deep_ptr<T, D, C>& y)
{ return !(y < nullptr); }

template <class T, class D, class C>
bool operator>=(const deep_ptr<T, D, C>& x, std::nullptr_t)
{ return !(x < nullptr); }

template <class T, class D, class C>
bool operator>=(std::nullptr_t, const deep_ptr<T, D, C>& y)
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
  typedef ::falcon::deep_ptr<T, Dp, Cp> argument_type;

  typename hash<typename argument_type::pointer>::result_type
  operator()(const argument_type& p) const noexcept
  { return std::hash<typename argument_type::pointer>()(p.get()); }
};

}

#endif
