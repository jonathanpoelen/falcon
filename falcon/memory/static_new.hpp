#ifndef FALCON_MEMORY_STATICNEW_HPP
#define FALCON_MEMORY_STATICNEW_HPP

#include <utility>
#include <falcon/memory/memory_stack.hpp>
#include <falcon/functional/arg.hpp>

namespace falcon {

namespace aux_ {

template<class T>
struct static_new_traits
{
  typedef typename std::remove_extent<T>::type remove_extent;
  static constexpr bool easily_constructible =
    std::has_trivial_default_constructor<remove_extent>::value
    && std::has_trivial_copy_constructor<remove_extent>::value
    && std::has_trivial_copy_assign<remove_extent>::value;
  static constexpr bool easily_destructible =
    std::is_trivially_destructible<remove_extent>::value;
};

template<class T,
  bool = false,
  bool = static_new_traits<T>::easily_constructible,
  bool = static_new_traits<T>::easily_destructible>
struct static_new_base
: memory_stack<T>
{
  typedef T type;
  typedef typename memory_stack<T>::memory_type memory_type;


  static_new_base(const static_new_base& other)
  : ptr_(other.ptr_ ? ptr_ = new (this->data()) T(other.get()) : nullptr)
  {}

  static_new_base& operator=(const static_new_base& other)
  {
    if (ptr_)
    {
      if (other.ptr_)
        this->get() = other.get();
      else
      {
        memory_stack<T>::destroy();
        ptr_ = nullptr;
      }
    }
    else if (other.ptr_)
      ptr_ = new (this->data()) T(other.get());
    return *this;
  }

  ~static_new_base()
  {
    if (ptr_)
      memory_stack<T>::destroy();
  }

  template<class... Args>
  void construct(Args&&... args)
  {
    destroy();
    ptr_ = new (this->data()) T(std::forward<Args>(args)...);
  }

  void destroy()
  {
    if (ptr_)
    {
      memory_stack<T>::destroy();
      ptr_ = 0;
    }
  }

  bool initialized() const
  { return ptr_; }


private:
  type* ptr_ = nullptr;
};

template<class T, bool>
struct static_new_value
: memory_stack<T>
{
  void set_initilize(bool) {}
  bool initialized() const { return false; };
  struct guard_initialise {
    guard_initialise(const static_new_value&)
    {}
    void setinit()
    {}
  };
  guard_initialise guard()
  { return {}; }
};

template<class T>
struct static_new_value<T, true>
: memory_stack<T>
{
  bool _ini = false;
  void set_initilize(bool b) { _ini = b; }
  bool initialized() const { return _ini; };
  struct guard_initialise {
    static_new_value& obj;
    bool _is_ini = false;
    void setinit()
    { _is_ini = true; }
    ~guard_initialise()
    { obj._ini = _is_ini; }
  };
  guard_initialise guard()
  { return {*this, false}; }
};

template<class T, bool AddInitialized>
class static_new_base<T, AddInitialized, true, true>
: public memory_stack<T>
{
public:
  typedef T type;
  typedef T memory_type;
  typedef T * pointer;
  typedef const T * const_pointer;

private:
  static_new_value<T, AddInitialized> value_;

public:
  template<class... Args>
  void construct(Args&&... args)
  {
    auto guard = value_.guard();
    memory_stack<T>::construct(std::forward<Args>(args)...);
    guard.setinit();
  }

  bool initialized() const
  { return value_.initialized(); }
};


template<class T, std::size_t N, bool AddInitialized>
class static_new_base<T[N], AddInitialized, false, false>
: public memory_stack<T[N]>
{
public:
  typedef T type[N];
  typedef typename memory_stack<T[N]>::memory_type memory_type;

private:
  T * ptr_;

public:
  static_new_base()
  : ptr_(0)
  {}

  static_new_base(const static_new_base& other)
  : ptr_(0)
  {
    if (other.ptr_)
      construct(other.get());
  }

  static_new_base& operator=(const static_new_base& other)
  {
    if (ptr_)
    {
      if (other.ptr_)
      {
        for (std::size_t i = 0; i != N; ++i)
          this->get()[i] = other.get()[i];
      }
      else
        destroy();
    }
    else if (other.ptr_)
      construct(other.get());
    return *this;
  }

  ~static_new_base()
  { priv_destroy(); }

private:
  void priv_destroy()
  {
    if (ptr_)
      memory_stack<T[N]>::destroy();
  }

public:
  template<class... Args>
  void construct(Args&&... args)
  {
    priv_destroy();
    memory_stack<T[N]>::construct(std::forward<Args>(args)...);
    ptr_ = &this->get()[0];
  }

  void construct(const emplace_t&)
  { construct(); }

  template<class... Args>
  void construct(const emplace_t&, Args&&... args)
  {
    priv_destroy();
    memory_stack<T[N]>::construct(emplace, std::forward<Args>(args)...);
    ptr_ = &this->get()[0];
  }

  void destroy()
  {
    priv_destroy();
    ptr_ = 0;
  }

  bool initialized() const
  { return ptr_; }
};

template<class T, std::size_t N, bool AddInitialized>
class static_new_base<T[N], AddInitialized, false, true>
: public memory_stack<T[N]>
{
public:
  typedef T type[N];
  typedef typename memory_stack<T[N]>::memory_type memory_type;

private:
  T* ptr_;

public:
  static_new_base()
  : ptr_(0)
  {}

  static_new_base(const static_new_base& other)
  : ptr_(0)
  {
    if (other.ptr_)
      construct(other.get());
  }

  static_new_base& operator=(const static_new_base& other)
  {
    if (ptr_)
    {
      if (other.ptr_)
      {
        for (std::size_t i = 0; i != N; ++i)
          this->get()[i] = other.get()[i];
      }
      else
        destroy();
    }
    else if (other.ptr_)
      construct(other.get());
    return *this;
  }

  template<class... Args>
  void construct(Args&&... args)
  {
    memory_stack<T[N]>::construct(std::forward<Args>(args)...);
    ptr_ = this->address();
  }

  void construct(const emplace_t&)
  { construct(); }

  template<class... Args>
  void construct(const emplace_t&, Args&&... args)
  {
    memory_stack<T[N]>::construct(emplace, std::forward<Args>(args)...);
    ptr_ = this->address();
  }

  void destroy()
  { ptr_ = 0; }

  bool initialized() const
  { return ptr_; }
};

template<class T, std::size_t N, bool AddInitialized>
class static_new_base<T[N], AddInitialized, true, true>
{
public:
  typedef T type[N];
  typedef T memory_type;
  typedef T* pointer;
  typedef const T* const_pointer;


  type& get()
  { return value_.value_; }

  const type& get() const
  { return value_.value_; }

  memory_type& data()
  { return value_.value_; }

  const memory_type& data() const
  { return value_.value_; }

  pointer address()
  { return std::addressof(value_.value_); }

  const_pointer address() const
  { return std::addressof(value_.value_); }

  template<class... Args>
  void construct(Args&&... args)
  {
    value_.construct();
    for (unsigned int i = 0; i != N; ++i)
      value_.value_[i] = {std::forward<Args>(args)...};
  }

  void construct(T&& value)
  {
    value_.construct();
    for (unsigned int i = 0; i != N; ++i)
      value_.value_[i] = std::forward<T>(value);
  }

private:
  template<class U, typename... Args>
  void priv_construct(std::size_t n, U&& a, Args&&... args)
  {
    value_.value_[n] = std::forward<U>(a);
    priv_construct<n+1>(std::forward<Args>(args)...);
  }

  void priv_construct(std::size_t i)
  {
    for (; i != N; ++i)
      value_.value_[i] = T();
  }

public:
  template<class... Args>
  void construct(const emplace_t&, Args&&... args)
  {
    value_.construct();
    priv_construct(0, std::forward<Args>(args)...);
  }

  void destroy()
  { value_.destroy(); }

  bool initialized() const
  { return value_.initialized(); }

private:
  static_new_value<T[N], AddInitialized> value_;
};

template<class T, bool B>
struct basic_static_new
: private static_new_base<T, B>
{
  typedef T type;
  typedef typename static_new_base<T, B>::memory_type memory_type;
  typedef typename static_new_base<T, B>::pointer pointer;
  typedef typename static_new_base<T, B>::const_pointer const_pointer;

public:
  using static_new_base<T, B>::get;
  using static_new_base<T, B>::data;
  using static_new_base<T, B>::address;
  using static_new_base<T, B>::destroy;
  using static_new_base<T, B>::construct;

  operator T& ()
  { return this->get(); }

  operator const T& () const
  { return this->get(); }

  pointer operator->()
  { return this->address(); }

  const_pointer operator->() const
  { return this->address(); }
};

}

/**
 * \brief Reserve memory in the stack. If \c static_new::construct was used, \c static_new::destroy will call automatically.
 */
template<class T>
using static_new = aux_::basic_static_new<T, false>;


/**
 * \brief such as @ref static_new but knows if the variable was constructed.
 */
template<class T>
using static_new2 = aux_::basic_static_new<T, true>;

}

#endif
