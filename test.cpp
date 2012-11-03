#include <iostream>

#include <falcon/accessor/readonly.hpp>

struct A
{
	int n = 3;
	falcon::readonly<int, A> num = n;
	falcon::readonly_variable<int, A> num2 = n;
	falcon::readonly<int&, A> ref_num = n;
	falcon::readonly_variable<int&, A> ref_num2 = n;

	void f()
	{ ++n; }
};

int main()
{
	A a;
	std::cout << a.num() << std::endl;
	std::cout << a.num2 << std::endl;
	std::cout << a.ref_num() << std::endl;
	std::cout << a.ref_num2 << std::endl;
	a.f();
	std::cout << a.num() << std::endl;
	std::cout << a.num2 << std::endl;
	std::cout << a.ref_num() << std::endl;
	std::cout << a.ref_num2 << std::endl;
}
