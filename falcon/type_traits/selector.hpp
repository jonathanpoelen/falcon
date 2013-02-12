#ifndef _FALCON_TYPE_TRAITS_SELECTOR_HPP
#define _FALCON_TYPE_TRAITS_SELECTOR_HPP

#include <falcon/type_traits/cv_selector.hpp>
#include <falcon/type_traits/reference_selector.hpp>

namespace falcon {

template<typename _Qualified, typename _Unqualified,
	bool _IsConst = FALCON_BOOST_OR_STD_NAMESPACE::is_const<_Qualified>::value,
	bool _IsVol = FALCON_BOOST_OR_STD_NAMESPACE::is_volatile<_Qualified>::value,
	reference_type::enum_t _Ref = reference_qualified<_Qualified>::value>
struct match_selector
{
	typedef typename cv_selector<
		typename reference_selector<_Unqualified, _Ref>::type,
		_IsConst, _IsVol
	>::type type;
};

}

#endif
