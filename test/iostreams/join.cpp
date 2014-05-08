#include <test/test.hpp>
#include <array>
#include <falcon/c++1x/syntax.hpp>
#include <falcon/iostreams/join.hpp>
#include "join.hpp"

template<typename _T>
void dispath_join_test(_T& arr)
{
  using falcon::iostreams::join;
  using falcon::begin;
  using falcon::end;

  std::stringstream ss;
  std::string s;

  join(ss, arr) << std::endl;
  s += "18,19,0,1\n";

  ss.width(4);
  join(ss, arr, ':') << std::endl;
  s += "  18:  19:   0:   1\n";
  ss.width(4);
  ss.flags(std::ios::left);
  ss << join(arr, ':') << std::endl;
  s += "18  :19  :0   :1   \n";

  join(ss, arr, "::", 1) << std::endl;
  s += "18:19:0:1\n";
  ss << join(arr, "::", 1) << std::endl;
  s += "18:19:0:1\n";

  join(ss, arr, ":") << std::endl;
  s += "18:19:0:1\n";
  ss << join(arr, ":") << std::endl;
  s += "18:19:0:1\n";

  join(ss, begin(arr), end(arr), ':') << std::endl;
  s += "18:19:0:1\n";
  ss << join(begin(arr), end(arr), ':') << std::endl;
  s += "18:19:0:1\n";

  join(ss, begin(arr), end(arr), "::", 1) << std::endl;
  s += "18:19:0:1\n";
  ss << join(begin(arr), end(arr), "::", 1) << std::endl;
  s += "18:19:0:1\n";

  join(ss, begin(arr), end(arr), ":") << std::endl;
  s += "18:19:0:1\n";
  ss << join(begin(arr), end(arr), ":") << std::endl;
  s += "18:19:0:1\n";

  CHECK_EQUAL_VALUE(s, ss.str());
}

void join_test()
{
  {
    typedef std::array<int, 4> container_type;
    container_type arr{{18,19,0,1}};
    dispath_join_test<container_type>(arr);
  }
  {
    typedef int container_type[4];
    container_type arr{18,19,0,1};
    dispath_join_test<container_type>(arr);
  }
}
FALCON_TEST_TO_MAIN(join_test)
