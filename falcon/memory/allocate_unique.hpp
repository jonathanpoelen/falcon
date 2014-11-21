#ifndef FALCON_MEMORY_ALLOCATE_UNIQUE_HPP
#define FALCON_MEMORY_ALLOCATE_UNIQUE_HPP

#include <memory>
#include <falcon/noncopyable.hpp>
#include <falcon/memory/allocator_rebind.hpp>

namespace falcon {

template<class T, class Alloc>
struct allocator_delete : private noncopyable_but_movable
{
  using allocator_type = allocator_rebind_t<Alloc, T>;

  using pointer = typename allocator_type::pointer;

  template<class Alloc2>
  explicit allocator_delete(const Alloc2 & alloc)
  : alloc(alloc)
  {}

  explicit allocator_delete(const allocator_type & alloc)
  : alloc(alloc)
  {}

  void operator()(T * p) noexcept
  {
    alloc.destroy(p);
    alloc.deallocate(p, 1);
  }

private:
  allocator_type alloc;
};

namespace aux_ {
  template<class T, class Alloc>
  struct allocate_unique
  {
    typedef allocator_delete<T, allocator_rebind_t<Alloc, T> > deleter;
    typedef std::unique_ptr<T, deleter> single_object;
  };

  template<class T, class Alloc>
  struct allocate_unique<T[], Alloc>
  { struct invalid_type { }; };


  template<class T, std::size_t Bound, class Alloc>
  struct allocate_unique<T[Bound], Alloc>
  { struct invalid_type { }; };
}

/**
 * \brief Constructs an object of type T with a allocator and wraps it in a std::unique_ptr.
 */
template<class T, class Alloc, class... Args>
typename aux_::allocate_unique<T, Alloc>::single_object
allocate_unique(const Alloc& alloc, Args&&... args)
{
  using Allocator = allocator_rebind_t<Alloc, T>;
  using Deleter = allocator_delete<T, Allocator>;
  using Pointer = typename Allocator::pointer;

  struct PtrAllocated
  {
    PtrAllocated(Allocator & allocator)
    : alloc(allocator)
    , ptr(alloc.allocate(1))
    {}

    Pointer release()
    {
      // std::exchange (c++14)
      Pointer ret = std::move(ptr);
      ptr = nullptr;
      return ret;
    }

    void construct(Args&&... args)
    {
      alloc.construct(ptr, std::forward<Args>(args)...);
    }

    ~PtrAllocated()
    {
      if (ptr) {
        alloc.deallocate(ptr, 1);
      }
    }

  private:
    Allocator & alloc;
    Pointer ptr;
  };

  std::unique_ptr<T, Deleter> ret(nullptr, Deleter(alloc));
  PtrAllocated ptr(reinterpret_cast<Allocator&>(ret.get_deleter()));
  ptr.construct(std::forward<Args>(args)...);
  ret.reset(ptr.release());
  return ret;
}

template<class T, class Alloc, class... Args>
typename aux_::allocate_unique<T, Alloc>::invalid_type
allocate_unique(const Alloc&, Args&&...) = delete;

}

#endif
