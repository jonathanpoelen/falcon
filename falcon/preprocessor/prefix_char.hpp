#ifndef FALCON_PREPROCESSOR_PREFIX_CHAR_HPP
#define FALCON_PREPROCESSOR_PREFIX_CHAR_HPP

#include <boost/preprocessor/cat.hpp>

#define FALCON_PP_PREFIX_CHAR_char()
#define FALCON_PP_PREFIX_CHAR_wchar_t() L
#if __cplusplus >= 201103L
#define FALCON_PP_PREFIX_CHAR_char16_t() u
#define FALCON_PP_PREFIX_CHAR_char32_t() U
#endif

#define FALCON_PP_PREFIX_CHAR(type) BOOST_PP_CAT(FALCON_PP_PREFIX_CHAR_, type)()

#define FALCON_PP_PREFIX_TYPE_() char
#define FALCON_PP_PREFIX_TYPE_L() wchar_t
#if __cplusplus >= 201103L
#define FALCON_PP_PREFIX_TYPE_u8() char
#define FALCON_PP_PREFIX_TYPE_u() char16_t
#define FALCON_PP_PREFIX_TYPE_U() char32_t
#endif

#define FALCON_PP_PREFIX_TYPE(prefix) BOOST_PP_CAT(FALCON_PP_PREFIX_TYPE_, prefix)()

#define FALCON_PP_PREFIX_CAT(type, str) BOOST_PP_CAT(FALCON_PP_PREFIX_CHAR(type), str)

#endif
