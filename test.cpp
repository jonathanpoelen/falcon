#include <iostream>
#include <typeinfo>
#include <falcon/iostream/iostream.hpp>
#include <falcon/utility/synchronizer.hpp>
#include <falcon/tuple/ostream.hpp>

template <typename, typename>
struct A
{};

int main()
{
	//synchronizer_tuple<std::array<int, 8>&> s;
	//synchronizer<build_pack<int, 8>> s;
	//build_class<synchronizer, build_pack<int, 8>::type>::type s;
	//bind_class<synchronizer, build_pack<int, 8>> s;
	//bind_class<synchronizer, use<paramter_pack<int, int>>> s;
// 	int i = 2, i2 = 4;
// 	falcon::tuple_synchronizer<int&, int&> synchronizer(i, i2);
// 	(void)synchronizer;
	const char * s = "plop";
// 	std::cout << std::is_same<std::tuple<int,int>>::value;
// 	typedef falcon::tuple_synchronizer<const char*,const char*> tuple_synchronizer;
// 	std::cout << typeid(tuple_synchronizer::__delegate<falcon::late_index>::__tuple).name();
// 	std::cout << typeid(falcon::left_accumulator_template<A, int>::wrapper<char>).name();
	/*std::cout << */falcon::make_tuple_synchronizer<>(s, s+1)[0];
// 	++synchronizer;
// 	std::cout << i << ' ' << i2 << '\n';
}
