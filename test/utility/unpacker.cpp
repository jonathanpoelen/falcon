#include <test/test.hpp>
#include <falcon/utility/unpacker.hpp>
#include "unpacker.hpp"
#include <string>
#include <array>

void unpacker_test()
{
  {
    int a=0;
    auto t = std::make_tuple(1, 3);
    falcon::unpacker(a, std::ignore) = t;
    CHECK_EQUAL_VALUE(a, 1);
  }
  {
    std::string s;
    auto t = std::make_tuple(std::string("plop"));
    falcon::unpacker(s) = std::move(t);
    CHECK_EQUAL_VALUE(s, "plop");
    CHECK_EQUAL_VALUE(std::get<0>(t), "");
  }
  {
    std::string a, b;
    std::string arr[]{"a", "b"};
    falcon::unpacker(a, b) = arr;
    CHECK_EQUAL_VALUE(a, "a");
    CHECK_EQUAL_VALUE(b, "b");
    CHECK_EQUAL_VALUE(arr[0], "a");
    CHECK_EQUAL_VALUE(arr[1], "b");
  }
  {
    std::string a, b;
    std::string arr[]{"a", "b"};
    falcon::unpacker(a, b) = std::move(arr);
    CHECK_EQUAL_VALUE(a, "a");
    CHECK_EQUAL_VALUE(b, "b");
    CHECK_EQUAL_VALUE(arr[0], "");
    CHECK_EQUAL_VALUE(arr[1], "");
  }
}

FALCON_TEST_TO_MAIN(unpacker_test)
