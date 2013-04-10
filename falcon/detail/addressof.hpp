#ifndef _FALCON_DETAIL_ADDRESSOF_HPP
#define _FALCON_DETAIL_ADDRESSOF_HPP

#if __cplusplus > 201100L
# include <type_traits>
#endif

namespace falcon {
namespace detail {

#if __cplusplus > 201100L
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