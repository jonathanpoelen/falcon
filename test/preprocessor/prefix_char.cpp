#include <falcon/preprocessor/prefix_char.hpp>
#include "to_main.hpp"
#include "prefix_char.hpp"

void prefix_char_test()
{
	const FALCON_PP_PREFIX_TYPE() * s1 = "";
	const FALCON_PP_PREFIX_TYPE(L) * s2 = L"";
	const FALCON_PP_PREFIX_TYPE(u) * s3 = u"";
	const FALCON_PP_PREFIX_TYPE(U) * s4 = U"";
	const FALCON_PP_PREFIX_TYPE(u8) * s5 = u8"";

	(void)(s5 == s1);

	const char * t1 = FALCON_PP_PREFIX_CAT(char, "");
	const wchar_t  *t2 = FALCON_PP_PREFIX_CAT(wchar_t, "");
	const char16_t * t3 = FALCON_PP_PREFIX_CAT(char16_t, "");
	const char32_t * t4 = FALCON_PP_PREFIX_CAT(char32_t, "");

	(void)(s1 == t1);
	(void)(s2 == t2);
	(void)(s3 == t3);
	(void)(s4 == t4);
}
FALCON_TEST_TO_MAIN(prefix_char_test)
