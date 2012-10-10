#ifndef FALCON_UTILITY_TO_CONST_HPP
#define FALCON_UTILITY_TO_CONST_HPP

namespace falcon {
template<typename _T>
inline const _T& to_const(const _T& v)
{
	return v;
}
}

#endif
