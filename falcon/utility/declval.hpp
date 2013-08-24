#ifndef FALCON_UTILITY_DECLVAL_HPP
#define FALCON_UTILITY_DECLVAL_HPP

#if __cplusplus >= 201103L
# include <utility>
#endif

namespace falcon {
#if __cplusplus >= 201103L
using std::declval;
#else
template<typename T>
T declval();
#endif
}

#endif
