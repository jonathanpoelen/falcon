#ifndef FALCON_UTILITY_MUTABLE_POINTER_HPP
#define FALCON_UTILITY_MUTABLE_POINTER_HPP

namespace falcon {

template<typename T>
class mutable_pointer
{
public:
  mutable_pointer(T * x = 0) noexcept
  : ptr(x)
  {}

  mutable_pointer(const mutable_pointer&) noexcept = default;

  operator T* () const
  { return ptr; }

  mutable_pointer operator=(T & x) const
  {
    ptr = &x;
    return *this;
  }

private:
  mutable T * ptr;
};

}

#endif
