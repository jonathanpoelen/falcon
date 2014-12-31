#ifndef FALCON_UTILITY_EXCHANGE_HPP
#define FALCON_UTILITY_EXCHANGE_HPP

#include <utility>

namespace falcon {

#if __cplusplus > 201103L
using std::exchange;
#else
/// Assign @p new_val to @p obj and return its previous value.
template <class T, class U = T>
T exchange(T & obj, U && new_val)
{
  T old_val = std::move(obj);
  obj = std::forward<U>(new_val);
  return old_val;
}
#endif

}

#endif
