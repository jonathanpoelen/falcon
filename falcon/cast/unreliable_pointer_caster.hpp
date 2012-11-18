#ifndef _FALCON_CAST_UNRELIABLE_POINTER_CASTER_HPP
#define _FALCON_CAST_UNRELIABLE_POINTER_CASTER_HPP

#include <falcon/cast/unreliable_pointer_cast.hpp>

namespace falcon {

///Wrapper for unreliable_pointer_cast
template <typename _Cast>
struct unreliable_pointer_caster
{
	_Cast* operator()(void *p) const
	{ return unreliable_pointer_cast<_Cast>(p); }

	const _Cast* operator()(const void *p) const
	{ return unreliable_pointer_cast<const _Cast>(p); }
};

}

#endif