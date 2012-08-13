#ifndef _FALCON_ACCESSOR_REFERENCE_ACCESSOR_HPP
#define _FALCON_ACCESSOR_REFERENCE_ACCESSOR_HPP

#include <falcon/c++/constexpr.hpp>

namespace falcon {

template <typename _T>
struct reference_accessor
{
	typedef _T value_type;
	typedef _T& reference;
	typedef const _T& const_reference;

	reference operator()(reference v) const
	{ return v; }

	CPP_CONSTEXPR const_reference operator()(const_reference v) const
	{ return v; }
};

}

#endif