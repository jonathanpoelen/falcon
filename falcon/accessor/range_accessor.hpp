#ifndef _FALCON_ACCESSOR_RANGE_ACCESSOR_HPP
#define _FALCON_ACCESSOR_RANGE_ACCESSOR_HPP

#include <falcon/c++/constexpr.hpp>

namespace falcon {

template <typename _RangeAccessTraits>
struct begin_accessor
{
	typedef _RangeAccessTraits traits_type;
	typedef typename traits_type::container_type container_type;
	typedef typename traits_type::iterator iterator;

	CPP_CONSTEXPR iterator operator()(container_type& cont) const
	{
		return traits_type::begin(cont);
	}
};

template <typename _RangeAccessTraits>
struct end_accessor
{
	typedef _RangeAccessTraits traits_type;
	typedef typename traits_type::container_type container_type;
	typedef typename traits_type::iterator iterator;

	CPP_CONSTEXPR iterator operator()(container_type& cont) const
	{
		return traits_type::end(cont);
	}
};

}

#endif