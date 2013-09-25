#ifndef FALCON_LOGICAL_BETWEEN_MINMAX_HPP
#define FALCON_LOGICAL_BETWEEN_MINMAX_HPP

namespace falcon {

/// Return @p v between @p min and @p max
template<typename T>
T between_minmax(const T & min, const T & v, const  T & max)
{
	return v < min ? min : (v > max ? max : v);
}

}

#endif
