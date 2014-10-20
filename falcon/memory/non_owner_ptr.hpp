#ifndef FALCON_MEMORY_NON_OWNER_PTR_HPP
#define FALCON_MEMORY_NON_OWNER_PTR_HPP

#include <memory>
#include <falcon/unused_variable.hpp>

namespace falcon {

template <class T>
using non_owner_ptr = std::unique_ptr<T, unused_variable_t>;

}

#endif
