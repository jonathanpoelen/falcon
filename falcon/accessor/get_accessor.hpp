#ifndef _FALCON_ACCESSOR_GET_ACCESSOR_HPP
#define _FALCON_ACCESSOR_GET_ACCESSOR_HPP

#include <falcon/c++/constexpr.hpp>

namespace falcon {

template <typename _Class, typename _T = typename _Class::value_type>
struct get_accessor
{
	typedef _T value_type;

	value_type& operator()(_Class& cont) const
	{
		return cont.get();
	}

	CPP_USE_CONSTEXPR value_type& operator()(const _Class& cont) const
	{
		return cont.get();
	}
};

}

#endif