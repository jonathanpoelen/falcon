#ifndef _FALCON_DETAIL_ADDRESSOF_HPP
#define _FALCON_DETAIL_ADDRESSOF_HPP

#ifdef __GXX_EXPERIMENTAL_CXX0X__
# include <type_traits>
#endif

namespace falcon {
namespace detail {

#ifdef __GXX_EXPERIMENTAL_CXX0X__
using std::addressof;
#else
template <typename _T>
inline _T* addressof(_T& v) {
	return &v;
}
#endif

}
}

#endif