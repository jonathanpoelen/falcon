// #include <test/A.h>
// #include <type_traits>
// #include <vector>
// #include <iostream>
// #include <falcon/memory/grouping_new.hpp>

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

// #include <falcon/functional/dynamic_callback.hpp>

#include <falcon/parameter/parameter_index.hpp>
#include <falcon/c++1x/unpack.hpp>
#include <falcon/arg/arg.hpp>
#include <falcon/functional/call.hpp>
#include <falcon/parameter/keep_parameter_index.hpp>

#include <initializer_list>
#include <iostream>
#include <typeinfo>

using falcon::parameter_index;
using falcon::build_parameter_index;
using falcon::build_parameter_index_t;
using falcon::build_range_parameter_index;
using falcon::build_range_parameter_index_t;
using falcon::call;
using namespace falcon;



template<std::size_t... Indexes, typename Function, typename... Args>
void __call(parameter_index<Indexes...>, Function func, Args&&... args)
{
  func(arg<Indexes>(std::forward<Args>(args)...)...);
}

template<std::size_t NumberArg, typename Function, typename... Args,
  std::size_t... Indexes, std::size_t Index>
void __call_partial_param_loop(parameter_index<Indexes...>, parameter_index<Index>,
                               Function func, Args&&... args)
// -> decltype(call(build_range_parameter_index_t<Index*NumberArg, sizeof...(Args)>(),
//                  func, std::forward<Args>(args)...))
{
//   CPP1X_UNPACK(__call(
//     build_range_parameter_index_t<Indexes*NumberArg, Indexes*NumberArg + NumberArg>,
//     func,
//     std::forward<Args>(args)...
//   ));
  /*return*/ call(build_range_parameter_index_t<Index*NumberArg, sizeof...(Args)>(),
              func, std::forward<Args>(args)...);
}

template<std::size_t NumberArg, typename Function, typename... Args,
  typename Indexes = build_parameter_index_t<
    (sizeof...(Args) / NumberArg + ((sizeof...(Args) % NumberArg) ? 1 : 0))
  >
>
void call_partial_param_loop(Function func, Args&&... args)
// -> decltype(__call_partial_param_loop<NumberArg>(
//   build_parameter_index_t<sizeof...(Args) / NumberArg + ((sizeof...(Args) % NumberArg) ? 1 : 0)>(),
//   func,
//   std::forward<Args>(args)...
// ))
{
  /*return*/ __call_partial_param_loop<NumberArg>(
    Indexes(),
//     keep_parameter_index<last_parameter_index_tag<>>
    func,
    std::forward<Args>(args)...
  );
}

void f1(int /*n*/)
{}

int main()
{
  call_partial_param_loop<1>(f1, 1,3,4);


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

