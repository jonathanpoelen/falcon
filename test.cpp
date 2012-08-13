#include <iostream>
// #include <falcon/functional/short_circuit.hpp>
// #include <falcon/algorithm.hpp>
// #include <falcon/iostream/iostream.hpp>
// #include <falcon/functional/call_inserted_param.hpp>
// #include <falcon/functional/placeholder_functor.hpp>
// #include <falcon/functional/caller.hpp>
// #include <falcon/utility/to_cref.hpp>
//
// struct Out
// {
// 	template<typename... _Args>
// 	void operator()(const _Args&... args)
// 	{
// 		falcon::print(args...) << '\n';
// 	}
// 	template<typename... _Args>
// 	void operator()(const _Args&... args) const
// 	{
// 		falcon::print(args...) << " const\n";
// 	}
// };

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

// #include <falcon/functional/compose.hpp>
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

#include <falcon/memory/static_new.hpp>
#include <falcon/accessor.hpp>
#include <test/A.h>

static constexpr int f(){return 0;}

int main()
{
// 	const int i = 6;
// 	auto f = falcon::compose<>(A(), A(), A(), A());
// 	std::cout << "f: " << f(i) << '\n';
// 	std::cout << "i: " << i << '\n';

// 	const auto f = falcon::make_ostream_functor(std::cout);
// 	f(5, ' ', 55);

// 	const auto t = std::make_tuple<>(5, ' ', 55);
// 	falcon::tuple_call<const falcon::basic_ostream_functor<char>&>
// 	(falcon::parameter_index<0,1,2>(), f, t);


	falcon::static_new<A[2]> snew;
	snew.construct(falcon::emplace);

	std::cout << snew.get()[0] << '\n';
	std::cout << snew.get()[1] << '\n';

// 	snew.destroy();

// 	{
// 		falcon::caller<Out, char, falcon::placeholder_functor<1,Out,char>> f('<');
// 		f(0,0);
// 	}
// 	{
// 		int a[] = {0, 1, 2, 3, 4, 2, 5, 6, 7, 8, 9, 10};
// 		typedef falcon::placeholder_functor<3, std::greater<int>, int> functor_type;
// 		functor_type func(3);
// 		std::cout
// 		<< *falcon::find_if(a, falcon::short_circuit<functor_type&>(4, func)) << '\n'
// 		<< *falcon::find_if(a, std::ref(func)) << '\n';
// 	}

	return 0;
}
