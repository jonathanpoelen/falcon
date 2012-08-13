#ifndef _FALCON_LOGICAL_BETWEEN_MINMAX_HPP
#define _FALCON_LOGICAL_BETWEEN_MINMAX_HPP

namespace falcon {

/// Return @p v between @p min and @p max
template<typename _T>
_T between_minmax(const _T& min, const _T& v, const  _T& max)
{
	return v < min ? min : (v > max ? max : v);
}

}

#endif
