// #include <test/A.h>
// #include <type_traits>
// #include <vector>
// #include <iostream>
// #include <falcon/memory/grouping_new.hpp>
//
// #include <falcon/mpl/seq.hpp>
// #include <falcon/mpl/integral.hpp>
// // #include <falcon/mpl/pair.hpp>
//
// using namespace falcon::mpl;
// using namespace falcon::mpl::placeholders;
//
// template< typename N1, typename N2 >
// struct int_plus
// : int_<( N1::value + N2::value )>
// {};
//

#include <falcon/container/unordered_vector.hpp>
#include <iostream>

int main()
{
  falcon::unordered_vector<int> v{{1,2,3,4}};
//   v.container().insert(v.begin(), 3);
  v.insert(5);
  for (auto x: v) {
    std::cout << (x) << "\n";
  }
  v.remove(2);
  for (auto x: v) {
    std::cout << (x) << "\n";
  }
  return v==v;

//   using sequence = seq<_1,_2,_3>;
//   using first = begin<sequence>::type;
//   using last = end<sequence>::type;
//   using t1 = deref<first>::type;
//   using first2 = next<first>::type;
//   using t2 = deref<first2>::type;
//   return t1::value + t2::value + deref<prior<last>::type>::type::value;



//   typedef apply_impl< int_plus<_1,_2>, int_<2>, int_<3>, int_<2> >::type r1;
//   return r1::value;
//   typedef apply_impl< if_<arg<4>,_2,_3>, _1, _2, _3, int_<0> >::type r1;
//   typedef apply_or_type_impl_t< if_<_1, _2, _3>, int_<0>, int_<30>, int_<4> > r1;
//   typedef apply< pair<if_<int_plus<_1,_1>, _2, pair<_3,_4>>, _2>, int_<0>, int_<20>, int_<30>, int_<40> >::type r1;
//   typedef apply< pair< if_< int_plus< _1, _1 >, _2, pair< _3, _4 > >, _2 >, int_< 0 >, int_< 20 >, int_< 30 >, int_< 40 > >::type r1;
//   return r1::first::first::value;


//   auto t = falcon::optimal_grouping_allocate<char, int>(falcon::allocate_wrapper<char>(),
//                                                         size_t(12), size_t(32));
//   get<1>(t) = const_cast<char*>("plop");
//   std::cout
//   << (get<0>(t)) << "\n"
//   << (get<1>(t)) << "\n"
//   << (get<2>(t)) << "\n"
//   ;
//
//   auto t2 = falcon::grouping_allocate<char, int>(falcon::allocate_wrapper<char>(),
//                                                  size_t(12), size_t(32));
//   get<0>(t2) = const_cast<char*>("plop");
//   std::cout
//   << (get<0>(t2)) << "\n"
//   << (get<1>(t2)) << "\n"
//   ;

//   falcon::grouping_new<int, char>(2, 4);
//   falcon::grouping_new(falcon::new_element<int>{2}, falcon::new_element<char>{4});
}

