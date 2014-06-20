#ifndef FALCON_MEMORY_ALIGN_HPP
#define FALCON_MEMORY_ALIGN_HPP

#if __cplusplus >= 201103L && !defined(__GNUC__)
# include <memory>
#else
# include <cstddef>
#endif

namespace falcon {

#if __cplusplus < 201103L || defined(__GNUC__)
inline void* align(size_t alignment, size_t size, void*& ptr, size_t& space)
{
  void* r = nullptr;
  if (size <= space)
  {
    char* p1 = static_cast<char*>(ptr);
    char* p2 = reinterpret_cast<char*>(
      reinterpret_cast<size_t>(p1 + (alignment - 1)) & -alignment
    );
    size_t d = static_cast<size_t>(p2 - p1);
    if (d <= space - size)
    {
      r = p2;
      ptr = r;
      space -= d;
    }
  }
  return r;
}
#else
using std::align;
#endif

}

#endif
