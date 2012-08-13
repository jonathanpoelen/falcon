#ifndef _FALCON_CAST_REFERENCE_CASTER_HPP
#define _FALCON_CAST_REFERENCE_CASTER_HPP

#include <falcon/cast/reference_cast.hpp>

namespace falcon {

	///Wrapper for reference_cast
	template <typename _Cast>
	struct reference_caster
	{
		template<typename _T>
		_Cast& operator()(_T& a)
		{ return reference_cast<_Cast&>(a); }

		template<typename _T>
		const _Cast& operator()(const _T& a)
		{ return reference_cast<const _Cast&>(a); }
	};

}

#endif