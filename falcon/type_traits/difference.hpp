#ifndef _FALCON_TYPE_TRAITS_DIFFERENCE_HPP
#define _FALCON_TYPE_TRAITS_DIFFERENCE_HPP

#ifdef __GXX_EXPERIMENTAL_CXX0X__
# include <type_traits>
namespace falcon {
template <typename _T>
struct difference
{
	typedef decltype(std::declval<_T>() - std::declval<_T>()) type;
};
}
#else
# include <cstddef>
# include <boost/type_traits/remove_cv.hpp
# include <falcon/helper/has_difference_type.hpp
# include <falcon/sfinae/choose_has_type.hpp>

namespace falcon {

template <typename _T>
class difference
{
	FALCON_CLASS_CHOOSE_TYPE(_T, typename _T::difference_type, typename boost::remove_cv<_T>::type);

public:
	typedef FALCON_CALL_CHOOSE_HAS_TYPE(_T, difference_type) type;
};

template <typename _T>
struct difference<_T*>
{
	typedef std::ptrdiff_t type;
};

}

#endif
#endif
