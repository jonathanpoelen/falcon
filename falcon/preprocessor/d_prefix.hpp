#ifndef _FALCON_PREPROCESSOR_D_PREFIX_HPP
#define _FALCON_PREPROCESSOR_D_PREFIX_HPP

#define FALCON_PP_D_PREFIX_char
#define FALCON_PP_D_PREFIX_wchar_t L

#if __cplusplus > 201100L
# define FALCON_PP_D_PREFIX_char16_t u
# define FALCON_PP_D_PREFIX_char32_t U
#endif

#endif
