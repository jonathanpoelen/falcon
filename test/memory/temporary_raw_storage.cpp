#include <test/test.hpp>
#include <falcon/memory/temporary_raw_storage.hpp>
#include "temporary_raw_storage.hpp"
#include <sstream>

template<class T>
struct allocator_raw_storage
: std::allocator<T>
{
  template<class U>
  struct rebind { typedef allocator_raw_storage<U> other; };

  allocator_raw_storage(std::ostream & os)
  : os(os)
  {}

  template<class U>
  allocator_raw_storage(allocator_raw_storage<U> const & other)
  : os(other.os)
  {}

  T* allocate(size_t n, void * p = 0)
  {
    T * ret = std::allocator<T>::allocate(n, p);
    os << static_cast<void*>(ret) << '\n';
    return ret;
  }

  void deallocate(T * p, size_t n)
  {
    os << static_cast<void*>(p) << '\n';
    std::allocator<T>::deallocate(p, n);
  }

private:
  std::ostream & os;
};

void temporary_raw_storage_test()
{
  using std::get;

  std::ostringstream oss;
  std::ostringstream oss2;

  {
    auto trs = falcon::make_temporary_raw_storage<char, int>(allocator_raw_storage<char>(oss), 12, 32);
    auto t = trs.get_tuple();
    CHECK_EQUAL(
      reinterpret_cast<void*>(get<0>(t) - sizeof(int) * 32),
      reinterpret_cast<void*>(get<1>(t))
    );
    oss2 << static_cast<void*>(get<1>(t)) << '\n' << static_cast<void*>(get<1>(t)) << '\n';
  }

  CHECK_EQUAL(oss.str(), oss2.str());
}

FALCON_TEST_TO_MAIN(temporary_raw_storage_test)
