#include <test/test.hpp>
#include <falcon/iostreams/membuf.hpp>
#include "membuf.hpp"

#include <string>

void membuf_test()
{
  char s[] = "10 22 abc";
  falcon::iostreams::membuf mem(s, sizeof(s)-1);

  CHECK_EQUAL(mem.size(), 9);
  CHECK_EQUAL(mem.in_avail(), 9);

  std::iostream io(&mem);

  int i, ii;
  std::string str;
  io >> i >> ii >> str;
  io.clear();
  io << str << ' ' << ii << ' ' << i;

  CHECK_EQUAL(mem.size(), 9);
  CHECK_EQUAL(mem.in_avail(), 0);

  auto eq = [](const char * s, std::ptrdiff_t n, const char * s2) {
    for (std::ptrdiff_t i = 0; i < n; ++i) {
      if (*s++ != *s2++) {
        return false;
      }
    }
    return true;
  };

  CHECK(eq(s, mem.size(), "abc 22 10"));

  CHECK_EQUAL(mem.pubseekpos(0), 0);
  CHECK_EQUAL(mem.size(), 9);
  CHECK_EQUAL(mem.in_avail(), 9);

  char sbuf[sizeof(s)];
  CHECK_EQUAL(std::streamsize(sizeof(s)-1), mem.sgetn(sbuf, sizeof(s)));
  CHECK(eq(s, mem.size(), "abc 22 10"));
  CHECK_EQUAL(std::streamsize(sizeof(s)-1), mem.sputn("abcdefghijklmnop", 15));
  CHECK(eq(s, mem.size(), "abcdefghijklmnop"));
}

FALCON_TEST_TO_MAIN(membuf_test)
