#ifndef FALCON_CONTAINER_REFERENCE_VECTOR_HPP
#define FALCON_CONTAINER_REFERENCE_VECTOR_HPP

#include <vector>
#include <functional>
#include <falcon/type_traits/use.hpp>
#include <falcon/memory/reference_allocator.hpp>

namespace falcon {

template<typename _T, typename _Allocator = std::allocator<_T>>
struct built_reference_vector
{
	typedef std::vector<
		std::reference_wrapper<_T>,
		reference_allocator<
			std::reference_wrapper<_T>,
			typename _Allocator::template rebind<
				std::reference_wrapper<_T>
			>::other
		>
	> type;
};

template<typename _T, typename _Allocator = std::allocator<_T>>
using reference_vector = typename built_reference_vector<_T, _Allocator>::type;

namespace container {
	template<typename _T, typename _Allocator>
	struct __vector
	{ typedef std::vector<_T, _Allocator> __type; };

	template<typename _T, typename _Allocator>
	struct __vector<_T&, _Allocator>
	{ typedef reference_vector<_T, _Allocator> __type; };

	/// Alias for falcon::reference_vector<T> if T is a reference otherwise std::vector<T>
	template<typename T,
		typename Allocator = std::allocator<typename std::remove_reference<T>::type>>
	using vector = typename __vector<T, Allocator>::__type;
}

}

#endif