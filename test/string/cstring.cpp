#include <test/test.hpp>
#include <falcon/string/cstring.hpp>
#include "cstring.hpp"

void basic_cstring_test()
{
  {
    constexpr falcon::const_cstring cstr("plop");
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
  {
    char s[10] = {'p','l','o','p','\0'};
    falcon::cstring cstr = falcon::cstring_array(s, 4);
    CHECK_EQUAL_VALUE(cstr.size(), 4u);
    CHECK(cstr.capacity() == sizeof(s));
    CHECK(cstr == "plop");
    cstr.push_back('e');
    CHECK_EQUAL_VALUE(cstr.size(), 5u);
    CHECK(cstr == "plope");
    cstr.insert(0, 2, 'r');
    CHECK_EQUAL_VALUE(cstr.size(), 7u);
    CHECK(cstr >= "rrplope");
    cstr.replace(1, 4, "abc");
    CHECK_EQUAL_VALUE(cstr.size(), 6u);
    CHECK("rabcpe" == cstr);
    cstr.append("fe");
    CHECK_EQUAL_VALUE(cstr.size(), 8u);
    CHECK("rabcpefe" == cstr);
    try {
      cstr.append("yy");
      CHECK(false);
    } catch (std::length_error &)
    {}
    cstr.erase(3, 4);
    CHECK_EQUAL_VALUE(cstr.size(), 4u);
    CHECK("rabe" == cstr);
  }
}

FALCON_TEST_TO_MAIN(basic_cstring_test)
