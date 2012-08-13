#ifndef _FALCON_TYPE_TRAITS_IDENTITY_HPP
#define _FALCON_TYPE_TRAITS_IDENTITY_HPP

namespace falcon {

template<typename _T>
struct identity
{
	typedef _T type;
};

}

#endif
