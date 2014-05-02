#ifndef FALCON_CONTAINER_REFERENCE_VECTOR_HPP
#define FALCON_CONTAINER_REFERENCE_VECTOR_HPP

#include <vector>
#include <functional>
#include <falcon/type_traits/use.hpp>
#include <falcon/memory/mutation_allocator.hpp>

namespace falcon {

template<class T, class Allocator = std::allocator<T>>
struct built_reference_vector
{
	typedef std::vector<
		std::reference_wrapper<T>,
		mutation_allocator<
			std::reference_wrapper<T>,
			Allocator
		>
	> type;
};

template<class T, class Allocator = std::allocator<T>>
using reference_vector = typename built_reference_vector<T, Allocator>::type;

namespace _aux {
  template<class T, class Allocator>
  struct vector
  { typedef std::vector<T, Allocator> type; };

  template<class T, class Allocator>
  struct vector<T&, Allocator>
  { typedef reference_vector<T, Allocator> type; };
}

namespace container {
	/// Alias for falcon::reference_vector<T> if T is a reference otherwise std::vector<T>
	template<typename T,
		typename Allocator = std::allocator<typename std::remove_reference<T>::type>>
	using vector = typename ::falcon::_aux::vector<T, Allocator>::type;
}

}

#endif
