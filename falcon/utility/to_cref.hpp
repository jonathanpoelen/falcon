#ifndef _FALCON_UTILITY_TO_CREF_HPP
#define _FALCON_UTILITY_TO_CREF_HPP

namespace falcon {
template<typename _T>
inline const _T& to_cref(const _T& v)
{
	return v;
}
}

#endif
