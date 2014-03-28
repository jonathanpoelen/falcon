#ifndef _FALCON_DETAIL_ADDRESSOF_HPP
#define _FALCON_DETAIL_ADDRESSOF_HPP

#if __cplusplus >= 201103L
# include <memory>
#endif

namespace falcon {
namespace detail {

#if __cplusplus >= 201103L
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
