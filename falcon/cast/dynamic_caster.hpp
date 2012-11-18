#ifndef _FALCON_CAST_DYNAMIC_CASTER_HPP
#define _FALCON_CAST_DYNAMIC_CASTER_HPP

namespace falcon {

/// Wrapper for dynamic_cast
template <typename _Cast>
struct dynamic_caster
{
	template<typename _T>
	_Cast operator()(_T& d) const
	{ return dynamic_cast<_Cast>(d); }

	template<typename _T>
	_Cast operator()(const _T& d) const
	{ return dynamic_cast<_Cast>(d); }
};

}

#endif