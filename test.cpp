// #include <test/A.h>
// #include <type_traits>
// #include <vector>
#include <iostream>
#include <falcon/memory/grouping_new.hpp>


int main()
{
  auto t = falcon::optimal_grouping_allocate<char, int>(size_t(12), size_t(32));
  std::cout
  << (std::get<0>(t)) << "\n"
  << (std::get<1>(t)) << "\n"
  << (std::get<2>(t)) << "\n"
  ;

//   falcon::grouping_new<int, char>(2, 4);
//   falcon::grouping_new(falcon::new_element<int>{2}, falcon::new_element<char>{4});
}

