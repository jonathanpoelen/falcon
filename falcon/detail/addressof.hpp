#ifndef FALCON_DETAIL_ADDRESSOF_HPP
#define FALCON_DETAIL_ADDRESSOF_HPP

#if __cplusplus >= 201103L
# include <memory>
#endif

namespace falcon {
namespace detail {

#if __cplusplus >= 201103L
using std::addressof;
#else
template <typename T>
inline T* addressof(T& v) throw() {
	return &v;
}
#endif

}
}

#endif
