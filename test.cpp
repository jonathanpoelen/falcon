#include <iostream>
// #include <memory>
#include <vector>
// #include <array>
#include <falcon/container/container_wrapper.hpp>

using namespace std;

int main(/*int argc, char **argv*/)
{
  std::vector<int> v;
  falcon::container_wrapper<std::vector<int>> cw(v);
  falcon::seq(v);
  falcon::seq(cw);
  falcon::cseq(v);
  falcon::rseq(v);
  falcon::crseq(v);
  return int(cw.end()-cw.begin());
}

