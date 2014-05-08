#include <test/test.hpp>
#define FALCON_NO_BOOST_FILESYSTEM
#include <falcon/iostreams/set_file_contents.hpp>
#include <falcon/iostreams/get_file_contents.hpp>
#include "set_file_contents.hpp"

void set_file_contents_test()
{
  std::streamsize ssize = falcon::iostreams::set_file_contents("/tmp/l", "plop");
  CHECK_EQUAL_VALUE(4, ssize);
  int err;
  std::string str = falcon::iostreams::get_file_contents("/tmp/l", &err);
  CHECK_EQUAL_VALUE("plop", str);
  CHECK_EQUAL_VALUE(true, err);
}

FALCON_TEST_TO_MAIN(set_file_contents_test)
