#ifndef FALCON_TYPE_TRAITS_IDENTITY_HPP
#define FALCON_TYPE_TRAITS_IDENTITY_HPP

namespace falcon {

template<typename T>
struct identity
{
	typedef T type;
};

}

#endif
