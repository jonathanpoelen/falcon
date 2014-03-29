#ifndef FALCON_UTILITY_NOEXCEPT_CLASS_HPP
#define FALCON_UTILITY_NOEXCEPT_CLASS_HPP

#include <utility>

namespace falcon {

template<typename T>
class noexcept_class
{
public:
  typedef T type;


public:
  noexcept_class() noexcept
  : v()
  {}

  noexcept_class(T&& value) noexcept
  : v(std::forward<T>(value))
  {}

  noexcept_class(noexcept_class&& other) noexcept
  : v(std::forward<T>(other.v))
  {}

  noexcept_class(const noexcept_class& other) noexcept
  : v(other.v)
  {}

  operator T& () noexcept
  { return v; }

  operator const T& () const noexcept
  { return v; }

  operator T* () noexcept
  { return &v; }

  operator const T* () const noexcept
  { return &v; }

  T& get() noexcept
  { return v; }

  const T& get() const noexcept
  { return v; }

private:
  T v;
};

}

#endif
