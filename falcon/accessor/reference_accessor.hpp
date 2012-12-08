#ifndef _FALCON_ACCESSOR_REFERENCE_ACCESSOR_HPP
#define _FALCON_ACCESSOR_REFERENCE_ACCESSOR_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/type_traits/add_const_if_reference.hpp>

namespace falcon {

template <typename _T>
struct reference_accessor
{
	typedef _T value_type;
	typedef _T& reference;
	typedef reference argument_type;
	typedef reference result_type;
	typedef typename add_const_if_reference<reference>::type const_reference;

	result_type operator()(reference v) const
	{ return v; }

	CPP_CONSTEXPR const_reference operator()(const_reference v) const
	{ return v; }
};

template <typename _T>
struct reference_accessor<const _T>
{
	typedef _T value_type;
	typedef const _T& reference;
	typedef reference argument_type;
	typedef reference result_type;
	typedef reference const_reference;

	result_type operator()(const_reference v) const
	{ return v; }
};

}

#endif