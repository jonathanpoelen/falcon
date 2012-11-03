#ifndef _FALCON_ACCESSOR_SIZE_ACCESSOR_HPP
#define _FALCON_ACCESSOR_SIZE_ACCESSOR_HPP

#include <cstddef>
#include <falcon/c++/constexpr.hpp>

namespace falcon {

template <typename _T>
struct size_accessor
{
	typedef std::size_t result_type;

	CPP_CONSTEXPR result_type operator()(const _T& x) const
	{ return x.size(); }
};

}

#endif