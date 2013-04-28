#ifndef _FALCON_ACCESSOR_GET_ACCESSOR_HPP
#define _FALCON_ACCESSOR_GET_ACCESSOR_HPP

#include <falcon/c++/constexpr.hpp>

namespace falcon {

template <typename _Class, typename _T = typename _Class::type&>
struct get_accessor
{
	typedef _T result_type;
	typedef _Class argument_type;

	result_type operator()(_Class& cont) const
	{
		return cont.get();
	}

	CPP_CONSTEXPR_OR_CONST result_type operator()(const _Class& cont) const
	{
		return cont.get();
	}
};

}

#endif