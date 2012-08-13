#ifndef _FALCON_TYPE_TRAITS_IS_SAME_HPP
#define _FALCON_TYPE_TRAITS_IS_SAME_HPP

#ifdef __GXX_EXPERIMENTAL_CXX0X__
# include <type_traits>
namespace falcon {
	using std::is_same;
}
#else
# include <falcon/type_traits/integral_constant.hpp>
namespace falcon {
	template<typename, typename>
	struct is_same
	: public false_type
	{};

	template<typename _Tp>
	struct is_same<_Tp, _Tp>
	: public true_type
	{};
}
#endif

#endif