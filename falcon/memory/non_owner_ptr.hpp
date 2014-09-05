#ifndef FALCON_MEMORY_NON_OWNER_PTR_HPP
#define FALCON_MEMORY_NON_OWNER_PTR_HPP

#include <memory>

namespace falcon {

template <class T>
struct non_owner_ptr
{
  using pointer = T*;
  using element_type = T;

  constexpr non_owner_ptr(std::nullptr_t) noexcept : non_owner_ptr() { }
  constexpr non_owner_ptr(non_owner_ptr const & other) = default;
  constexpr non_owner_ptr() noexcept : ptr_(0) { }

  explicit non_owner_ptr(pointer p) noexcept : ptr_(p) { }

  non_owner_ptr(non_owner_ptr&& other) noexcept : ptr_(other.release()) { }

  template<class U>
  non_owner_ptr(non_owner_ptr<U>&& other) noexcept
  : ptr_(other.release())
  { }

  template<class U>
  non_owner_ptr& operator=(non_owner_ptr<U>&& other) noexcept
  {
    ptr_ = other.release();
    return *this;
  }

  non_owner_ptr& operator=(std::nullptr_t) noexcept
  {
    ptr_ = nullptr;
    return *this;
  }

  non_owner_ptr& operator=(non_owner_ptr const & other) = default;

  pointer release() noexcept
  {
    pointer ret = ptr_;
    ptr_ = nullptr;
    return ret;
  }

  void swap(non_owner_ptr& other) noexcept
  {
    using std::swap;
    swap(ptr_, other.ptr_);
  }

  void reset(pointer p = pointer()) noexcept { ptr_= p; }

  void reset(std::nullptr_t) noexcept { ptr_ = nullptr; }

  pointer get() const noexcept { return ptr_; }

  typename std::add_lvalue_reference<element_type>::type
  operator*() const { return *ptr_; }

  pointer operator->() const noexcept { return get(); }
  explicit operator bool() const noexcept { return bool(ptr_); }

  T& operator[](size_t i) const noexcept { return ptr_[i]; }

private:
  pointer ptr_;
};

template<class T>
void swap(non_owner_ptr<T> & lhs, non_owner_ptr<T> & rhs) noexcept
{ lhs.swap(rhs); }


template<class T1, class T2>
bool operator==(const non_owner_ptr<T1>& x, const non_owner_ptr<T2>& y) noexcept
{ return x.get() == y.get(); }

template<class T1, class T2>
bool operator!=(const non_owner_ptr<T1>& x, const non_owner_ptr<T2>& y) noexcept
{ return x.get() != y.get(); }

template<class T1, class T2>
bool operator<(const non_owner_ptr<T1>& x, const non_owner_ptr<T2>& y) noexcept
{
  typedef typename std::common_type<
    typename non_owner_ptr<T1>::pointer
  , typename non_owner_ptr<T2>::pointer
  >::type CT;
  return std::less<CT>()(x.get(), y.get());
}

template<class T1, class T2>
bool operator<=(const non_owner_ptr<T1>& x, const non_owner_ptr<T2>& y) noexcept
{ return !(y < x); }

template<class T1, class T2>
bool operator>(const non_owner_ptr<T1>& x, const non_owner_ptr<T2>& y) noexcept
{ return y < x; }

template<class T1, class T2>
bool operator>=(const non_owner_ptr<T1>& x, const non_owner_ptr<T2>& y) noexcept
{ return !(x < y); }

template <class T>
bool operator==(const non_owner_ptr<T>& x, std::nullptr_t) noexcept
{ return !x; }

template <class T>
bool operator==(std::nullptr_t, const non_owner_ptr<T>& x) noexcept
{ return !x; }

template <class T>
bool operator!=(const non_owner_ptr<T>& x, std::nullptr_t) noexcept
{ return static_cast<bool>(x); }

template <class T>
bool operator!=(std::nullptr_t, const non_owner_ptr<T>& x) noexcept
{ return static_cast<bool>(x); }

template <class T>
bool operator<(const non_owner_ptr<T>& x, std::nullptr_t) noexcept
{ return std::less<typename non_owner_ptr<T>::pointer>()(x.get(), nullptr); }

template <class T>
bool operator<(std::nullptr_t, const non_owner_ptr<T>& y) noexcept
{ return std::less<typename non_owner_ptr<T>::pointer>()(nullptr, y.get()); }

template <class T>
bool operator<=(const non_owner_ptr<T>& x, std::nullptr_t) noexcept
{ return nullptr < x; }

template <class T>
bool operator<=(std::nullptr_t, const non_owner_ptr<T>& y) noexcept
{ return y < nullptr; }

template <class T>
bool operator>(const non_owner_ptr<T>& x, std::nullptr_t) noexcept
{ return !(nullptr < x); }

template <class T>
bool operator>(std::nullptr_t, const non_owner_ptr<T>& y) noexcept
{ return !(y < nullptr); }

template <class T>
bool operator>=(const non_owner_ptr<T>& x, std::nullptr_t) noexcept
{ return !(x < nullptr); }

template <class T>
bool operator>=(std::nullptr_t, const non_owner_ptr<T>& y) noexcept
{ return !(nullptr < y); }

}

namespace std {

template<class T>
struct hash< ::falcon::non_owner_ptr<T>>
: public hash<typename ::falcon::non_owner_ptr<T>::pointer>
{
  typename hash<typename ::falcon::non_owner_ptr<T>::pointer>::result_type
  operator()(const ::falcon::non_owner_ptr<T>& p) const noexcept
  { return std::hash<typename ::falcon::non_owner_ptr<T>::pointer>()(p.get()); }
};

}

#endif
