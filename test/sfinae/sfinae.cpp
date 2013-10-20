#include <test/test.hpp>
#include <falcon/sfinae.hpp>
#include "sfinae.hpp"

namespace n_test_sfinae {
  struct test1  {};
  struct test2  { void xxx(); };
  struct test3  { void xxx() const; };
  struct test4  { int xxx; };
  struct test5  { static int xxx(); };
  struct test6  { typedef int xxx; };
  struct test7  { struct xxx {}; };
  struct test8  { typedef void (*xxx)(); };
  struct test9  { typedef void (xxx)(); };
  struct test10  { template< class T > struct xxx {}; };
  struct test11  { template< class T > void xxx(T); };
  struct test12  { int xxx(int); };
  typedef int test13;
  typedef int test14[2];

  FALCON_HAS_TYPE_TRAIT_DEF(xxx);
  FALCON_HAS_TEMPLATE_TYPE_TRAIT_DEF(xxx);
  FALCON_HAS_ATTRIBUTE_TRAIT_DEF(xxx);
  FALCON_HAS_FUNCTION_TRAIT_DEF(xxx);
  FALCON_HAS_MEMBER_FUNCTION_TRAIT_DEF(xxx);
  FALCON_HAS_STATIC_FUNCTION_TRAIT_DEF(xxx);
  FALCON_HAS_MEMBER_TRAIT_DEF(xxx);
  FALCON_HAS_SIGNATURE_TRAIT_DEF(xxx);
  FALCON_HAS_MEMBER_IS_CALLABLE_TRAIT_DEF(xxx);
  FALCON_HAS_MEMBER_IS_CALLABLE_AND_CONVERTIBLE_TRAIT_DEF(xxx);
//   FALCON_FUNCTION_IS_CALLABLE_TRAIT_DEF(xxx);
//   FALCON_FUNCTION_IS_CALLABLE_AND_CONVERTIBLE_TRAIT_DEF(xxx);
}

void sfinae_test()
{
  using namespace n_test_sfinae;

  STATIC_CHECK_VALUE(false, has_xxx<test1>);
  STATIC_CHECK_VALUE(false, has_xxx<test2>);
  STATIC_CHECK_VALUE(false, has_xxx<test3>);
  STATIC_CHECK_VALUE(false, has_xxx<test4>);
  STATIC_CHECK_VALUE(false, has_xxx<test5>);
  STATIC_CHECK_VALUE(true , has_xxx<test6>);
  STATIC_CHECK_VALUE(true , has_xxx<test7>);
  STATIC_CHECK_VALUE(true , has_xxx<test8>);
  STATIC_CHECK_VALUE(true , has_xxx<test9>);
  STATIC_CHECK_VALUE(false, has_xxx<test10>);
  STATIC_CHECK_VALUE(false, has_xxx<test11>);
  STATIC_CHECK_VALUE(false, has_xxx<test12>);
  STATIC_CHECK_VALUE(false, has_xxx<test13>);
  STATIC_CHECK_VALUE(false, has_xxx<test14>);

  STATIC_CHECK_VALUE(false, has_template_xxx<test1>);
  STATIC_CHECK_VALUE(false, has_template_xxx<test2>);
  STATIC_CHECK_VALUE(false, has_template_xxx<test3>);
  STATIC_CHECK_VALUE(false, has_template_xxx<test4>);
  STATIC_CHECK_VALUE(false, has_template_xxx<test5>);
  STATIC_CHECK_VALUE(false, has_template_xxx<test6>);
  STATIC_CHECK_VALUE(false, has_template_xxx<test7>);
  STATIC_CHECK_VALUE(false, has_template_xxx<test8>);
  STATIC_CHECK_VALUE(false, has_template_xxx<test9>);
  STATIC_CHECK_VALUE(true , has_template_xxx<test10>);
  STATIC_CHECK_VALUE(false, has_template_xxx<test11>);
  STATIC_CHECK_VALUE(false, has_template_xxx<test12>);
  STATIC_CHECK_VALUE(false, has_template_xxx<test13>);
  STATIC_CHECK_VALUE(false, has_template_xxx<test14>);

  STATIC_CHECK_VALUE(false, has_xxx_attribute<test1>);
  STATIC_CHECK_VALUE(false, has_xxx_attribute<test2>);
  STATIC_CHECK_VALUE(false, has_xxx_attribute<test3>);
  STATIC_CHECK_VALUE(true , has_xxx_attribute<test4>);
  STATIC_CHECK_VALUE(false, has_xxx_attribute<test5>);
  STATIC_CHECK_VALUE(false, has_xxx_attribute<test6>);
  STATIC_CHECK_VALUE(false, has_xxx_attribute<test7>);
  STATIC_CHECK_VALUE(false, has_xxx_attribute<test8>);
  STATIC_CHECK_VALUE(false, has_xxx_attribute<test9>);
  STATIC_CHECK_VALUE(false, has_xxx_attribute<test10>);
  STATIC_CHECK_VALUE(false, has_xxx_attribute<test11>);
  STATIC_CHECK_VALUE(false, has_xxx_attribute<test12>);
  STATIC_CHECK_VALUE(false, has_xxx_attribute<test13>);
  STATIC_CHECK_VALUE(false, has_xxx_attribute<test14>);

  STATIC_CHECK_VALUE(false, has_xxx_function<test1>);
  STATIC_CHECK_VALUE(true , has_xxx_function<test2>);
  STATIC_CHECK_VALUE(true , has_xxx_function<test3>);
  STATIC_CHECK_VALUE(false, has_xxx_function<test4>);
  STATIC_CHECK_VALUE(true , has_xxx_function<test5>);
  STATIC_CHECK_VALUE(false, has_xxx_function<test6>);
  STATIC_CHECK_VALUE(false, has_xxx_function<test7>);
  STATIC_CHECK_VALUE(false, has_xxx_function<test8>);
  STATIC_CHECK_VALUE(false, has_xxx_function<test9>);
  STATIC_CHECK_VALUE(false, has_xxx_function<test10>);
  STATIC_CHECK_VALUE(false, has_xxx_function<test11>);
  STATIC_CHECK_VALUE(true , has_xxx_function<test12>);
  STATIC_CHECK_VALUE(false, has_xxx_function<test13>);
  STATIC_CHECK_VALUE(false, has_xxx_function<test14>);

  STATIC_CHECK_VALUE(false, has_xxx_member_function<test1>);
  STATIC_CHECK_VALUE(true , has_xxx_member_function<test2>);
  STATIC_CHECK_VALUE(true , has_xxx_member_function<test3>);
  STATIC_CHECK_VALUE(false, has_xxx_member_function<test4>);
  STATIC_CHECK_VALUE(false, has_xxx_member_function<test5>);
  STATIC_CHECK_VALUE(false, has_xxx_member_function<test6>);
  STATIC_CHECK_VALUE(false, has_xxx_member_function<test7>);
  STATIC_CHECK_VALUE(false, has_xxx_member_function<test8>);
  STATIC_CHECK_VALUE(false, has_xxx_member_function<test9>);
  STATIC_CHECK_VALUE(false, has_xxx_member_function<test10>);
  STATIC_CHECK_VALUE(false, has_xxx_member_function<test11>);
  STATIC_CHECK_VALUE(true , has_xxx_member_function<test12>);
  STATIC_CHECK_VALUE(false, has_xxx_member_function<test13>);
  STATIC_CHECK_VALUE(false, has_xxx_member_function<test14>);

  STATIC_CHECK_VALUE(false, has_xxx_static_function<test1>);
  STATIC_CHECK_VALUE(false, has_xxx_static_function<test2>);
  STATIC_CHECK_VALUE(false, has_xxx_static_function<test3>);
  STATIC_CHECK_VALUE(false, has_xxx_static_function<test4>);
  STATIC_CHECK_VALUE(true , has_xxx_static_function<test5>);
  STATIC_CHECK_VALUE(false, has_xxx_static_function<test6>);
  STATIC_CHECK_VALUE(false, has_xxx_static_function<test7>);
  STATIC_CHECK_VALUE(false, has_xxx_static_function<test8>);
  STATIC_CHECK_VALUE(false, has_xxx_static_function<test9>);
  STATIC_CHECK_VALUE(false, has_xxx_static_function<test10>);
  STATIC_CHECK_VALUE(false, has_xxx_static_function<test11>);
  STATIC_CHECK_VALUE(false, has_xxx_static_function<test12>);
  STATIC_CHECK_VALUE(false, has_xxx_static_function<test13>);
  STATIC_CHECK_VALUE(false, has_xxx_static_function<test14>);

  STATIC_CHECK_VALUE(false, has_xxx_member<test1>);
  STATIC_CHECK_VALUE(true , has_xxx_member<test2>);
  STATIC_CHECK_VALUE(true , has_xxx_member<test3>);
  STATIC_CHECK_VALUE(true , has_xxx_member<test4>);
  STATIC_CHECK_VALUE(true , has_xxx_member<test5>);
  STATIC_CHECK_VALUE(true , has_xxx_member<test6>);
  STATIC_CHECK_VALUE(true , has_xxx_member<test7>);
  STATIC_CHECK_VALUE(true , has_xxx_member<test8>);
  STATIC_CHECK_VALUE(true , has_xxx_member<test9>);
  STATIC_CHECK_VALUE(true , has_xxx_member<test10>);
  STATIC_CHECK_VALUE(true , has_xxx_member<test11>);
  STATIC_CHECK_VALUE(true , has_xxx_member<test12>);
  STATIC_CHECK_VALUE(false, has_xxx_member<test13>);
  STATIC_CHECK_VALUE(false, has_xxx_member<test14>);

  STATIC_CHECK_VALUE(false, has_xxx_signature<test1, void(test1::*)(int)>);
  STATIC_CHECK_VALUE(true , has_xxx_signature<test2, void(test2::*)()>);
  STATIC_CHECK_VALUE(true , has_xxx_signature<test3, void(test3::*)()const>);
  STATIC_CHECK_VALUE(true , has_xxx_signature<test4, int(test4::*)>);
  STATIC_CHECK_VALUE(true , has_xxx_signature<test5, int(*)()>);
  STATIC_CHECK_VALUE(false, has_xxx_signature<test6, void(*)(int)>);
  STATIC_CHECK_VALUE(false, has_xxx_signature<test7, test7::xxx>);
  STATIC_CHECK_VALUE(false, has_xxx_signature<test8, void(*)(int)>);
  STATIC_CHECK_VALUE(false, has_xxx_signature<test9, void(*)(int)>);
  STATIC_CHECK_VALUE(false, has_xxx_signature<test10, test10::xxx<int>>);
  STATIC_CHECK_VALUE(true , has_xxx_signature<test11, void(test11::*)(int)>);
  STATIC_CHECK_VALUE(true , has_xxx_signature<test12, int(test12::*)(int)>);

  STATIC_CHECK_VALUE(false, xxx_member_is_callable<test1>);
  STATIC_CHECK_VALUE(true , xxx_member_is_callable<test2>);
  STATIC_CHECK_VALUE(true , xxx_member_is_callable<test3>);
  STATIC_CHECK_VALUE(false, xxx_member_is_callable<test4>);
  STATIC_CHECK_VALUE(true , xxx_member_is_callable<test5>);
  STATIC_CHECK_VALUE(false, xxx_member_is_callable<test6>);
  STATIC_CHECK_VALUE(false, xxx_member_is_callable<test7>);
  STATIC_CHECK_VALUE(false, xxx_member_is_callable<test8>);
  STATIC_CHECK_VALUE(false, xxx_member_is_callable<test9>);
  STATIC_CHECK_VALUE(false, xxx_member_is_callable<test10>);
  STATIC_CHECK_VALUE(true , xxx_member_is_callable<test11, int>);
  STATIC_CHECK_VALUE(true , xxx_member_is_callable<test12, int>);
  STATIC_CHECK_VALUE(false, xxx_member_is_callable<test13>);
  STATIC_CHECK_VALUE(false, xxx_member_is_callable<test14>);

  STATIC_CHECK_VALUE(false, xxx_member_is_callable_and_convertible<test1, void>);
  STATIC_CHECK_VALUE(true , xxx_member_is_callable_and_convertible<test2, void>);
  STATIC_CHECK_VALUE(true, xxx_member_is_callable_and_convertible<test3, void>);
  STATIC_CHECK_VALUE(false, xxx_member_is_callable_and_convertible<test4, int>);
  STATIC_CHECK_VALUE(true , xxx_member_is_callable_and_convertible<test5, int>);
  STATIC_CHECK_VALUE(false, xxx_member_is_callable_and_convertible<test6, int>);
  STATIC_CHECK_VALUE(false, xxx_member_is_callable_and_convertible<test7, test7::xxx>);
  STATIC_CHECK_VALUE(false, xxx_member_is_callable_and_convertible<test8, int(*)()>);
  STATIC_CHECK_VALUE(false, xxx_member_is_callable_and_convertible<test9, int>);
  STATIC_CHECK_VALUE(false, xxx_member_is_callable_and_convertible<test10, void>);
  STATIC_CHECK_VALUE(true , xxx_member_is_callable_and_convertible<test11,void, int>);
  STATIC_CHECK_VALUE(true , xxx_member_is_callable_and_convertible<test12, int, int>);
  STATIC_CHECK_VALUE(false, xxx_member_is_callable_and_convertible<test13, void>);
  STATIC_CHECK_VALUE(false, xxx_member_is_callable_and_convertible<test14, void>);
}

FALCON_TEST_TO_MAIN(sfinae_test)
