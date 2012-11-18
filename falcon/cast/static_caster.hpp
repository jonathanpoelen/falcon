#ifndef _FALCON_CAST_STATIC_CASTER_HPP
#define _FALCON_CAST_STATIC_CASTER_HPP

namespace falcon {

/// Wrapper for static_cast
template <typename _Cast>
struct static_caster
{
	template<typename _T>
	_Cast operator()(_T& d) const
	{ return static_cast<_Cast>(d); }

	template<typename _T>
	_Cast operator()(const _T& d) const
	{ return static_cast<_Cast>(d); }
};

}

#endif