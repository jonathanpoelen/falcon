#include <iostream>
#include <falcon/iostream/iostream.hpp>
// #include <falcon/utility/synchronizer.hpp>
#include <falcon/functional/arguments_wrapper.hpp>


int main()
{
	//synchronizer_tuple<std::array<int, 8>&> s;
	//synchronizer<build_pack<int, 8>> s;
	//build_class<synchronizer, build_pack<int, 8>::type>::type s;
	//bind_class<synchronizer, build_pack<int, 8>> s;
	//bind_class<synchronizer, use<paramter_pack<int, int>>> s;
// 	int i = 2, i2 = 4;
// 	falcon::synchronizer<int&> synchronizer(i, i2);
// 	++synchronizer;
// 	std::cout << i << ' ' << i2 << '\n';

	int a = 0, b = 2;
	falcon::arguments_wrapper<int&, int> arguments(a, b);
	arguments([](int &x, int& y){ x += ++y; });
	falcon::println<>(a, ' ', b);
	falcon::println<>(std::get<0>(arguments), ' ', std::get<1>(arguments));
}
