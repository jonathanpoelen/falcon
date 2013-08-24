#ifndef FALCON_TYPE_TRAITS_ADD_N_POINTER_HPP
#define FALCON_TYPE_TRAITS_ADD_N_POINTER_HPP

#include <cstddef>

namespace falcon {

template<typename T, std::size_t N>
struct add_n_pointer
{
	typedef typename add_n_pointer<T*, N-1>::type type;
};

template<typename T>
struct add_n_pointer<T, 0>
{
	typedef T type;
};

}

#endif
