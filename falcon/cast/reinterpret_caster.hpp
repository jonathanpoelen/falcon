#ifndef _FALCON_CAST_REINTERPRET_CASTER_HPP
#define _FALCON_CAST_REINTERPRET_CASTER_HPP

namespace falcon {

/// Wrapper for reinterpret_cast
template <typename _Cast>
struct reinterpret_caster
{
	template<typename _T>
	_Cast operator()(_T& d) const
	{ return reinterpret_cast<_Cast>(d); }

	template<typename _T>
	_Cast operator()(const _T& d) const
	{ return reinterpret_cast<_Cast>(d); }
};

}

#endif