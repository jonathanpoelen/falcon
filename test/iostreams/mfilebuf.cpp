#include <test/test.hpp>
#include <falcon/iostreams/mfilebuf.hpp>
#include "mfilebuf.hpp"
#include <sstream>

void mfilebuf_test()
{
  std::ostringstream oss1;
  {
    falcon::iostreams::mfilebuf files({
      {__FILE__, std::ios::in},
      {__FILE__, std::ios::in},
    });

    oss1 << &files;
  }

  std::ostringstream oss2;
  {
    std::filebuf file;
    file.open(__FILE__, std::ios::in);
    oss2 << &file;
  }

  std::string contents1 = oss1.str();
  std::string contents2 = oss2.str();
  contents2 += contents2;
  CHECK_EQUAL(contents1, contents2);
}

FALCON_TEST_TO_MAIN(mfilebuf_test)
