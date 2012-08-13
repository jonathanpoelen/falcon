#ifndef _FALCON_TYPE_TRAITS_ADD_N_POINTER_HPP
#define _FALCON_TYPE_TRAITS_ADD_N_POINTER_HPP

namespace falcon {

template<typename _T, std::size_t _N>
struct add_n_pointer
{
	typedef typename add_n_pointer<_T*, _N-1>::type type;
};

template<typename _T>
struct add_n_pointer<_T, 0>
{
	typedef _T type;
};

}

#endif
