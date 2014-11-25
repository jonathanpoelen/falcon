#ifndef FALCON_FN_HASH_HPP
#define FALCON_FN_HASH_HPP

#include <falcon/type_traits/static_const.hpp>
#include <falcon/c++1x/syntax.hpp>

#include <functional>

namespace falcon {
namespace fn {


/// \brief call std::hash< T>(x)
struct hash_fn {
  constexpr hash_fn() noexcept {}

  template<class T>
  constexpr CPP1X_DELEGATE_FUNCTION_FORCE_NOEXCEPT(
    operator()(T const & x) const
  , std::hash<T>()(x))
};


FALCON_GLOBAL_OBJECT(hash, hash_fn);

}
}

#endif
