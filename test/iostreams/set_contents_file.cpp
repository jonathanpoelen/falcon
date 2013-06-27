#include <test/test.hpp>
#define FALCON_NO_BOOST_FILESYSTEM
#include <falcon/iostreams/set_contents_file.hpp>
#include <falcon/iostreams/get_contents_file.hpp>
#include "set_contents_file.hpp"

void set_contents_file_test()
{
  std::streamsize ssize = falcon::set_contents_file<>("/tmp/l", "plop");
  CHECK_EQUAL_VALUE(4, ssize);
  std::ios_base::iostate err;
  std::string str = falcon::get_contents_file("/tmp/l", &err);
  CHECK_EQUAL_VALUE("plop", str);
  CHECK_EQUAL_VALUE(std::ios_base::goodbit, err);
}

FALCON_TEST_TO_MAIN(set_contents_file_test)
