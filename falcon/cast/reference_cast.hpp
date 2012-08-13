#ifndef _FALCON_CAST_REFERENCE_CAST_HPP
#define _FALCON_CAST_REFERENCE_CAST_HPP

namespace falcon {

	template <typename _Target, typename _Source>
	_Target& reference_cast(_Source& a) {
		return const_cast<_Target&>(a);
	}

}

#endif