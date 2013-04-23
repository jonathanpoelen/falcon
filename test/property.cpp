#include <test/test.hpp>
#include <falcon/property.hpp>
#include "property.hpp"

void property_test()
{
	using namespace falcon::property;

	class A
	{
		int n = 3;
	public:
		//class_property<properties::attribute, int, falcon::use_default, void> num = n;
		//readonly_property<properties::attribute, int> num = n;
		attr_read<int> num = n;
		attr_get<int> num2 = n;

#define READ_ATTR(name, value) attr_read<decltype(value)> name = value
		READ_ATTR(num3, n);
#undef READ_ATTR

		void f()
		{ ++n; }

		attr_set<int> set_num = n;
	};

	A a;
	CHECK(3 == a.num());
	CHECK(3 == a.num);
	CHECK(3 == a.num2());
	CHECK(3 == a.num3);
	a.f();
	CHECK(4 == a.num());
	CHECK(4 == a.num);
	CHECK(4 == a.num2());
	a.set_num(9);
	CHECK(9 == a.num3);
}

FALCON_GROUP_TEST_TO_MAIN(property_test)
