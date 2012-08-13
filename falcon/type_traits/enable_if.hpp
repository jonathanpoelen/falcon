#ifndef _FALCON_TYPE_TRAITS_ENABLE_IF_HPP
#define _FALCON_TYPE_TRAITS_ENABLE_IF_HPP

#ifdef __GXX_EXPERIMENTAL_CXX0X__
# include <type_traits>
namespace falcon {
	using std::enable_if;
}
#else
# include <falcon/type_traits/integral_constant.hpp>
namespace falcon {
	// Define a nested type if some predicate holds.
	template<bool, typename _Tp = void>
	struct enable_if
	{};

	// Partial specialization for true.
	template<typename _Tp>
	struct enable_if<true, _Tp>
	{ typedef _Tp type; };
}
#endif

#endif