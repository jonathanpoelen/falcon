// #include <test/A.h>
// #include <type_traits>
// #include <vector>
// #include <iostream>
// #include <falcon/memory/grouping_new.hpp>
//
// #include <falcon/mpl/seq.hpp>
// #include <falcon/mpl/integral.hpp>
// #include <falcon/mpl/pair.hpp>

// using namespace falcon::mpl;
//
// template< typename N1, typename N2 >
// struct int_plus
// : int_<( N1::value + N2::value )>
// {};

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

// #include <falcon/mpl/vector.hpp>
// #include <falcon/mpl/list.hpp>
// #include <falcon/mpl/map.hpp>
// #include <falcon/mpl/set.hpp>
// #include <falcon/mpl/range_c.hpp>
// #include <falcon/mpl/apply.hpp>
// #include <falcon/mpl/quote.hpp>
// #include <falcon/mpl/placeholders.hpp>
// #include <falcon/mpl/tpl.hpp>
// #include <falcon/mpl/at.hpp>
// #include <type_traits>
// #include <iostream>

// #include <falcon/mpl/vector_c.hpp>
// #include <falcon/mpl/for_each.hpp>
// #include <falcon/mpl/placeholders.hpp>
// #include <falcon/mpl/back_inserter.hpp>
// #include <falcon/mpl/size.hpp>
// #include <falcon/mpl/copy_if.hpp>
// #include <falcon/mpl/less.hpp>

// #include <type_traits>

// using namespace falcon::mpl;
// using namespace falcon::mpl::placeholders;

// struct value_printer
// {
//   template< typename U > void operator()(U x)
//   {
//     std::cout << x << 'n';
//   }
// };

#include <falcon/iostreams/showspace.hpp>
#include <falcon/iostreams/pad.hpp>
#include <falcon/iostreams/quoted.hpp>
#include <falcon/iostreams/iofmts.hpp>
#include <falcon/io/hexu.hpp>
#include <iostream>
#include <iomanip>


struct S {
  int i = 1;
  operator int () const { return i; }
};
std::ostream &operator <<(std::ostream &os, S const&) { return os << "ok"; }

namespace iofmts {
  using namespace falcon::iostreams::iofmts;
}

int main()
{
  using falcon::iostreams::showspace;
  using falcon::iostreams::pad;
  using falcon::iostreams::padl;
  using falcon::iostreams::padr;
  using falcon::iostreams::quoted;

  const void * p = 0; p = static_cast<const char*>(p)+3232;
  std::cout
//     << std::left << std::setw(6) << showspace(S()) << "]\n"
    << std::left << std::setw(6) << std::setiosflags(std::ios::boolalpha) <<  showspace(false) << "]\n"
    << std::left << std::setw(6) << showspace(p) << "]\n"
    << std::left << std::setw(6) << showspace(S()) << "]\n"
    << std::left << std::setw(6) << showspace(2) << "]\n"
    << std::left << std::setw(6) << showspace(2, '#') << "]\n"
    << std::left << std::setw(6) << showspace(showspace(2, '#')) << "]\n"
    << padl(5, '#') << 0 << "]\n"
    << padr(5, '#') << 0 << "]\n"
    << pad(std::ios::left, 5, '#') << 0 << "]\n"
    << pad(5, '#') << 0 << "]\n"
    << iofmts::setfill(5, '#') << 0 << "]\n"
    << std::right << std::setw(12) << quoted("plo\"p\"") << "]\n"
    << iofmts::right(iofmts::setw(quoted("plo\"p\""), 12)) << "]\n"
  ;

  std::string s("plo\"p\"");
  /*std::cout <<
   falcon::iostreams::is_fmt_manipulator<
     decltype(iofmts::right(s))//::template fmt_lock<void>
    >::value*/;
  std::cout
    << quoted(iofmts::right(s)) << "]\n"
    << quoted(iofmts::setfill(iofmts::setw(s, 10), '%')) << "]\n"
  ;
//   std::cout << quoted(iofmts::right(iofmts::setw(s, 12))) << "]\n";

//     << std::left << std::setw(6) << 1 << "]\n"
//     << std::left << std::setw(6) << showspace('a') << "]\n"
//     << std::left << std::setw(6) << showspace(-12) << "]\n"
//     << std::left << std::setw(6) << showspace(12.2) << "]\n"
//     << std::left << std::setw(6) << showspace(-12.2) << "]\n"
//     << std::left << std::setw(6) << showspace( 12u) << "]\n"
//     << std::left << std::setw(6) << showspace("") << "]\n"
//     << std::left << std::setw(10) << p << "]\n"
  ;


//   falcon::retain_free_object_allocator<int> allocator;
//   allocator.deallocate(allocator.allocate(2), 2);

//   int data[10];
//   falcon::lifo_allocator<int> l(std::begin(data), std::end(data));
//   l.deallocate(l.allocate(2), 2);

//   auto t2 = falcon::grouping_allocate<char, int>(falcon::allocate<char>(),
//                                                  size_t(12), size_t(32));
// //   get<0>(t2) = const_cast<char*>("plop");
//   std::cout
//   << ptrt(get<0>(t2)) << "\n"
//   << ptrt(get<1>(t2)) << "\n"
//   ;

//   falcon::grouping_new<int, char>(2, 4);
//   falcon::grouping_new(falcon::new_element<int>{2}, falcon::new_element<char>{4});



//   typedef vector_c<int,0,9> numbers;
//   for_each< numbers >( value_printer() );

//   result() = 0;


//   typedef apply< int_plus<_1,_2>, int_<2>, int_<3> >::type r1;
//   typedef apply< quote<int_plus>, int_<2>, int_<3> >::type r2;
//   typedef apply< tpl<int_plus, 0>, int_<2>, int_<3> >::type r3;
//   typedef apply< tpl<int_plus, 1>, int_<2>, int_<3>, int_<3> >::type r4;
//
//   std::cout
//     << (r1::value) << "\n"
//     << (r2::value) << "\n"
//     << (r3::value) << "\n"
//     << (r4::value) << "\n"
//   ;
//
//   using c1 = set<int_<2>, int_<3>, int_<12>>;
//   return at<c1, int_<12>>::type::value;


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

}

