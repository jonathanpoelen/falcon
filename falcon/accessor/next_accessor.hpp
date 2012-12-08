#ifndef _FALCON_ACCESSOR_NEXT_ACCESSOR_HPP
#define _FALCON_ACCESSOR_NEXT_ACCESSOR_HPP

#include <falcon/c++/constexpr.hpp>

namespace falcon {

template <typename _Class, typename _T = typename _Class::value_type&>
struct next_accessor
{
	typedef _T result_type;
	typedef _Class argument_type;

	result_type operator()(_Class& cont) const
	{
		return cont.next();
	}

	CPP_CONSTEXPR result_type operator()(const _Class& cont) const
	{
		return cont.next();
	}
};

}

#endif