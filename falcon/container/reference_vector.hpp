#ifndef FALCON_CONTAINER_REFERENCE_VECTOR_HPP
#define FALCON_CONTAINER_REFERENCE_VECTOR_HPP

#include <falcon/memory/mutation_allocator.hpp>

#include <type_traits>
#include <functional>
#include <vector>

namespace falcon {

template<class T, class Allocator = std::allocator<T>>
using reference_vector = std::vector<
  std::reference_wrapper<T>,
  mutation_allocator<std::reference_wrapper<T>, Allocator>
>;

namespace aux_ {
  template<class T, class Allocator>
  struct vector
  { typedef std::vector<T, Allocator> type; };

  template<class T, class Allocator>
  struct vector<T&, Allocator>
  { typedef reference_vector<T, Allocator> type; };
}

namespace container {
	/// Alias for falcon::reference_vector< @a T > if @a T is a reference otherwise std::vector< @a T >
	template<class T,
    class Allocator = std::allocator<typename std::remove_reference<T>::type>>
	using vector = typename ::falcon::aux_::vector<T, Allocator>::type;
}

}

#endif
