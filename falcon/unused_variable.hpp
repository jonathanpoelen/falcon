#ifndef FALCON_UNUSED_VARIABLE_HPP
#define FALCON_UNUSED_VARIABLE_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/preprocessor/not_ide_parser.hpp>

namespace falcon {
#ifdef __GXX_EXPERIMENTAL_CXX0X__
template<typename... _Args>
//void unused_variables(const _Args&...) = kdevelop parser error -_-
constexpr inline void unused_variables(const _Args&... FALCON_PP_NOT_IDE_PARSER())
{}
#else
inline void unused_variables(...)
{}
#endif

template<typename _T>
CPP_CONSTEXPR inline void unused_variable(const _T&)
{}

}

#define FALCON_UNUSED(args...) ::falcon::unused_variables(args)

#ifdef __GXX_EXPERIMENTAL_CXX0X__
# define FALCON_UNUSED_PACK(pack) (void)sizeof...(pack)
#endif

#endif
