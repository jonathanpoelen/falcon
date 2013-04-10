#ifndef _FALCON_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
#define _FALCON_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP

#if __cplusplus > 201100L
# include <type_traits>
namespace falcon {
using std::integral_constant;
using std::true_type;
using std::false_type;
}
#else
namespace falcon {

template<typename _Tp, _Tp __v>
struct integral_constant
{
	static const _Tp                      value = __v;
	typedef _Tp                           value_type;
	typedef integral_constant<_Tp, __v>   type;
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

}
#endif

#endif
