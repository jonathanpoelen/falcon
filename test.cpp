#include <iostream>
// #include <falcon/functional/short_circuit.hpp>
// #include <falcon/algorithm.hpp>
// #include <falcon/iostream/iostream.hpp>
// #include <falcon/functional/call_inserted_param.hpp>
// #include <falcon/functional/placeholder_for_argument.hpp>
// #include <falcon/functional/caller.hpp>

// #include <falcon/memory/construct.hpp>
// #include <array>
// #include <utility>
// #include <functional>
// #include <tuple>
//
// struct A
// {
// 	int n;
//
// // public:
// 	A(int __n)
// 	: n(__n)
// 	{}
//
// 	int f(){return n;}
// };

// #include <falcon/functional/operators.hpp>
//
// struct A
// {
// 	template<typename _T, typename... _Args>
// 	int operator()(const _T& a, _Args&&... args) const
// 	{
// 		std::cout << sizeof...(args) << ':' << a << '\n';
// 		return 0;
// 	}
// };

// #include <falcon/memory/static_new.hpp>
// #include <falcon/accessor.hpp>
// #include <test/A.h>

// static constexpr int f(){return 0;}

#include <falcon/functional/compose.hpp>
#include <falcon/functional/placeholder_for_argument.hpp>
#include <falcon/functional/operators.hpp>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>

int main()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	// perform 4 trials, each succeeds 1 in 2 times
	std::binomial_distribution<> d(4, 0.5);

// 	falcon::placeholder_for_argument<0, std::binomial_distribution<>&, std::mt19937&> r(gen, d);

	std::map<int, int> hist;
	falcon::placeholder_for_argument<0, falcon::late_index, std::map<int, int>&> a(hist);

	///TODO error if references
	///TODO error if false is not passing
	falcon::unary_compose<decltype((a)), std::binomial_distribution<>&, false> a2(a, d);
	falcon::unary_compose<falcon::late_increment, decltype(a2), false> a3(falcon::late_increment(), a2);

	falcon::placeholder_for_argument<0, decltype((a3)), std::mt19937&> f(gen, a3);

	for(int n=0; n<10000; ++n)
		f();
	for(auto p : hist)
		std::cout << p.first << ' ' << std::string(p.second/100, '*') << '\n';
// 	const int i = 6;
// 	auto f = falcon::compose<>(A(), A(), A(), A());
// 	std::cout << "f: " << f(i) << '\n';
// 	std::cout << "i: " << i << '\n';

// 	const auto f = falcon::make_ostream_functor(std::cout);
// 	f(5, ' ', 55);

// 	const auto t = std::make_tuple<>(5, ' ', 55);
// 	falcon::tuple_apply<const falcon::basic_ostream_functor<char>&>
// 	(falcon::parameter_index<0,1,2>(), f, t);


// 	falcon::static_new<A[2]> snew;
// 	snew.construct(falcon::emplace);
//
// 	std::cout << snew.get()[0] << '\n';
// 	std::cout << snew.get()[1] << '\n';

// 	snew.destroy();

	return 0;
}
