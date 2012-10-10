#ifndef _FALCON_ACCESSOR_AT_ACCESSOR_HPP
#define _FALCON_ACCESSOR_AT_ACCESSOR_HPP

#include <falcon/c++/constexpr.hpp>

namespace falcon {

	template <typename _Class, typename _Posiion, typename _T = typename _Class::value_type>
	struct at_accessor
	{
		typedef _T value_type;

		value_type& operator()(_Class& cont, const _Posiion& pos) const
		{
			return cont.at(pos);
		}

		CPP_USE_CONSTEXPR value_type& operator()(const _Class& cont,
												 const _Posiion& pos) const
		{
			return cont.at();
		}
	};

}

#endif