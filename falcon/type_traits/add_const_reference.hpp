#ifndef _FALCON_TYPE_TRAITS_ADD_CONST_REFERENCE_HPP
#define _FALCON_TYPE_TRAITS_ADD_CONST_REFERENCE_HPP

namespace falcon {

/**
 * \brief add const and reference if _T is not reference
 */
template<typename _T>
struct add_const_reference
{
	typedef const _T& type;
};

template<typename _T>
struct add_const_reference<_T&>
{
	typedef _T& type;
};

}

#endif