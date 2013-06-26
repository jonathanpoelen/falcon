#include <iostream>
// #include <memory>
// #include <vector>
// #include <array>
// #include <falcon/container/container_wrapper.hpp>

#include <falcon/iostream/mfstream.hpp>

// using namespace std;

int main(/*int argc, char **argv*/)
{
  falcon::mfstream mfs(falcon::mfstream::filename_generator{"/tmp/l.html","/tmp/l.sh"});
  std::cout << mfs.rdbuf();
}

