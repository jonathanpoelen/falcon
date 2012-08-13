#ifndef _FALCON_CAST_CONST_CASTER_HPP
#define _FALCON_CAST_CONST_CASTER_HPP

namespace falcon {

	/// Wrapper for const_cast
	template <typename _Cast>
	struct const_caster
	{
		template<typename _T>
		_Cast operator()(_T& d)
		{ return const_cast<_Cast>(d); }

		template<typename _T>
		_Cast operator()(const _T& d)
		{ return const_cast<_Cast>(d); }
	};

}

#endif