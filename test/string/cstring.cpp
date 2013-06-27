#include <test/test.hpp>
#include <falcon/string/basic_cstring.hpp>
#include "cstring.hpp"

void basic_cstring_test()
{
  {
    falcon::const_cstring cstr = "plop";
    CHECK(cstr == "plop");
    CHECK(cstr <= "plop");
    CHECK(cstr >= "plop");
    CHECK("plop" <= cstr);
    CHECK("plop" >= cstr);
  }
  {
    char s[] = {'p','l','o','p','\0'};
    falcon::cstring cstr(s);
    CHECK(cstr == "plop");
    CHECK(cstr <= "plop");
    CHECK(cstr >= "plop");
    CHECK("plop" <= cstr);
    CHECK("plop" >= cstr);
  }
  {
    falcon::const_cstring cstr = "abcd";
    CHECK(cstr != "bcd");
    CHECK("bcd" != cstr);
    CHECK(cstr < "bcd");
    CHECK("bcd" > cstr);
  }

  {
    char s[] = "abcd";
    falcon::cstring cstr(s);
    falcon::const_cstring cstr2("abc");
    CHECK(cstr != cstr2);
    CHECK(cstr2 != cstr);
    CHECK(!(cstr < cstr2));
    CHECK(!(cstr2 > cstr));
    CHECK(!(cstr == cstr2));
    CHECK(!(cstr <= cstr2));
    CHECK(cstr >= cstr2);
    CHECK(cstr2 <= cstr);
    CHECK(!(cstr2 >= cstr));
  }
}

FALCON_TEST_TO_MAIN(basic_cstring_test)
