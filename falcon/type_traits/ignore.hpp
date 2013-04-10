#ifndef _FALCON_TYPE_TRAITS_IGNORE_HPP
#define _FALCON_TYPE_TRAITS_IGNORE_HPP

namespace falcon {

struct ignore_t
{};

#if __cplusplus > 201100L
constexpr ignore_t ignore;
#else
const ignore_t ignore;
#endif

}

#endif
