#ifndef _FALCON_DETAIL_DEP_NSPACE_HPP
#define _FALCON_DETAIL_DEP_NSPACE_HPP

#ifdef __GXX_EXPERIMENTAL_CXX0X__
# define _FALCON_NAME_DEP_NSPACE ::std
#else
# define _FALCON_NAME_DEP_NSPACE ::boost
#endif

#define _FALCON_DEP_NSPACE(_FunctionOrClass) _FALCON_NAME_DEP_NSPACE::_FunctionOrClass

#endif