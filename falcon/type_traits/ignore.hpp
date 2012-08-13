#ifndef _FALCON_TYPE_TRAITS_IGNORE_HPP
#define _FALCON_TYPE_TRAITS_IGNORE_HPP

namespace falcon {

#ifdef __GXX_EXPERIMENTAL_CXX0X__
struct ignore_t
	{};

constexpr ignore_t ignore {};
#else
struct ignore_t
{
	ignore_t()
	{}
};
const ignore_t ignore;
#endif

}

#endif
