#include <iostream>
/*
#include <falcon/property/readonly.hpp>

class A
{
	int n = 3;
public:
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
	std::cout << a.num() << ' ';
	std::cout << a.num2 << ' ';
	std::cout << a.ref_num() << ' ';
	std::cout << a.ref_num2 << '\n';
	a.f();
	std::cout << a.num() << ' ';
	std::cout << a.num2 << ' ';
	std::cout << a.ref_num() << ' ';
	std::cout << a.ref_num2 << ' ';
}*/

#include <falcon/property.hpp>

using namespace falcon::property;

class A
{
	int n = 3;
public:
// 	class_property<properties::attribute, int, falcon::use_default, void> num = n;
// 	readonly_property<properties::attribute, int> num = n;
	read_attr<int> num = n;
	get_attr<int> num2 = n;

#define READ_ATTR(name, value) read_attr<decltype(value)> name = value
	READ_ATTR(num3, n);

	void f()
	{ ++n; }
};

int main()
{
	A a;
	std::cout << a.num() << ' ';
	std::cout << a.num << ' ';
	std::cout << a.num2() << ' ';
	a.f();
	std::cout << a.num.get() << ' ';
	std::cout << a.num << ' ';
	std::cout << a.num2() << ' ';
}
