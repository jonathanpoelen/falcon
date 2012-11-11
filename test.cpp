#include <iostream>
#include <falcon/utility/synchronizer.hpp>


int main()
{
	//synchronizer_tuple<std::array<int, 8>&> s;
	//synchronizer<build_pack<int, 8>> s;
	//build_class<synchronizer, build_pack<int, 8>::type>::type s;
	//bind_class<synchronizer, build_pack<int, 8>> s;
	//bind_class<synchronizer, use<paramter_pack<int, int>>> s;
	int i = 2, i2 = 4;
	falcon::synchronizer<int&> synchronizer(i, i2);
	++synchronizer;
	std::cout << i << ' ' << i2 << '\n';
}
