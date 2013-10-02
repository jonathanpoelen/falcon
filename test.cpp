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

#include <falcon/tuple/optimal_tuple.hpp>
#include <falcon/tuple/ostream.hpp>
#include <iostream>

using namespace falcon::tuple::ostream;
int main()
{
  using normal_tuple = std::tuple<int, long, int>;
  using optimal_tuple = falcon::optimal_tuple<normal_tuple>;
  std::cout
  << (sizeof(normal_tuple)) << "\n"
  << (sizeof(optimal_tuple)) << "\n";
  normal_tuple t1(1,2,3);
  optimal_tuple t2 = t1;
  falcon::put_tuple(std::cout, t2) << "\n";
  optimal_tuple t3(1,2,3);
  falcon::put_tuple(std::cout, t3) << "\n";
  std::cout << t2;



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
//   std::get<1>(t) = const_cast<char*>("plop");
//   std::cout
//   << (std::get<0>(t)) << "\n"
//   << (std::get<1>(t)) << "\n"
//   << (std::get<2>(t)) << "\n"
//   ;
//
//   auto t2 = falcon::grouping_allocate<char, int>(falcon::allocate_wrapper<char>(),
//                                                  size_t(12), size_t(32));
//   std::get<0>(t2) = const_cast<char*>("plop");
//   std::cout
//   << (std::get<0>(t2)) << "\n"
//   << (std::get<1>(t2)) << "\n"
//   ;

//   falcon::grouping_new<int, char>(2, 4);
//   falcon::grouping_new(falcon::new_element<int>{2}, falcon::new_element<char>{4});
}

