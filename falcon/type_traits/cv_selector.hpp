#ifndef _FALCON_TYPE_TRAITS_CV_SELECTOR_HPP
#define _FALCON_TYPE_TRAITS_CV_SELECTOR_HPP

#include <falcon/c++/boost_or_std.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(is_const)
#include FALCON_BOOST_OR_STD_TRAITS(is_volatile)

namespace falcon {

template<typename _Unqualified, bool _IsConst, bool _IsVol>
struct cv_selector
{
	typedef _Unqualified type;
};

template<typename _Unqualified>
struct cv_selector<_Unqualified, false, true>
{
	typedef volatile _Unqualified type;
};

template<typename _Unqualified>
struct cv_selector<_Unqualified, true, false>
{
	typedef const _Unqualified type;
};

template<typename _Unqualified>
struct cv_selector<_Unqualified, true, true>
{
	typedef const volatile _Unqualified type;
};

template<typename _Qualified, typename _Unqualified,
	bool _IsConst = FALCON_BOOST_OR_STD_NAMESPACE::is_const<_Qualified>::value,
	bool _IsVol = FALCON_BOOST_OR_STD_NAMESPACE::is_volatile<_Qualified>::value>
struct match_cv_qualifiers
{
	typedef typename cv_selector<_Unqualified, _IsConst, _IsVol>::type type;
};

}

#endif
