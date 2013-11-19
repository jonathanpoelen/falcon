// #include <test/A.h>
#include <type_traits>
// #include <vector>
// #include <iostream>
// #include <falcon/memory/grouping_new.hpp>
//
// #include <falcon/mpl/seq.hpp>
#include <falcon/mpl/integral.hpp>
// #include <falcon/mpl/pair.hpp>

using namespace falcon::mpl;

template< typename N1, typename N2 >
struct int_plus
: int_<( N1::value + N2::value )>
{};

// template<
//   typename T
// , T... args
// >
// using seq_c = seq<integral_c<T, args>...>;
//
// template< typename N1, typename N2 >
// struct less_impl
// { using type = integral_c<bool, (N1::value < N2::value)>; };
//
// template< typename N1, typename N2 >
// struct less
// : mpl_apply_def
// { using type = typename less_impl<typename N1::type, typename N2::type>::type; };

#include <falcon/mpl/vector.hpp>
#include <falcon/mpl/set.hpp>
#include <falcon/mpl/apply.hpp>
#include <falcon/mpl/quote.hpp>
#include <falcon/mpl/placeholders.hpp>
#include <falcon/mpl/tpl.hpp>
#include <falcon/mpl/at.hpp>
#include <type_traits>
#include <iostream>
using namespace falcon::mpl;
using namespace falcon::mpl::placeholders;

int main()
{
  typedef apply< int_plus<_1,_2>, int_<2>, int_<3> >::type r1;
  typedef apply< quote<int_plus>, int_<2>, int_<3> >::type r2;
  typedef apply< tpl<int_plus, 0>, int_<2>, int_<3> >::type r3;
  typedef apply< tpl<int_plus, 1>, int_<2>, int_<3>, int_<3> >::type r4;

  std::cout
    << (r1::value) << "\n"
    << (r2::value) << "\n"
    << (r3::value) << "\n"
    << (r4::value) << "\n"
  ;

  using c1 = set<int_<2>, int_<3>, int_<12>>;
  return at<c1, int_<12>>::type::value;


//   using vec = vector<int, float>;
//   std::cout << (std::is_same<front<vec>::type, int>::value) << "\n";
//   std::cout << (std::is_same<back<vec>::type, float>::value) << "\n";
//
//   using vec2 = insert<vec, begin<vec>::type, long>::type;
//   std::cout << (size<vec2>::value) << "\n";
//   std::cout << (std::is_same<front<vec2>::type, long>::value) << "\n";
//
//   return int(size<vec2>::value);




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
//   return r1::value;

//   typedef seq<long,float,short,double,float,long,long double> types;
//   typedef fold<
//       types
//     , int_<0>
//     , if_< std::is_floating_point<_2>,next<_1>,_1 >
//   >::type number_of_floats;
//   return number_of_floats::value;

//   typedef seq_c<int, 5,-1,0,7,2,0,-5,4> numbers;
//   typedef iter_fold<
//       numbers
//     , begin<numbers>::type
//     , if_< less< deref<_1>, deref<_2> >,_2,_1 >
//   >::type max_element_iter;
//   return max_element_iter::type::value;


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

