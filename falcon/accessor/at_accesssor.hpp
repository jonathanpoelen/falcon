#ifndef _FALCON_ACCESSOR_AT_ACCESSOR_HPP
#define _FALCON_ACCESSOR_AT_ACCESSOR_HPP

#include <falcon/c++/constexpr.hpp>

namespace falcon {

template <typename _Class, typename _Position, typename _T = typename _Class::value_type&>
struct at_accessor
{
	typedef _T result_type;

	result_type operator()(_Class& cont, const _Position& pos) const
	{
		return cont.at(pos);
	}

	CPP_USE_CONSTEXPR result_type operator()(const _Class& cont,
												const _Position& pos) const
	{
		return cont.at();
	}
};

}

#endif