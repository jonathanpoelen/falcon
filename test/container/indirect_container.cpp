#include <test/test.hpp>
#include <falcon/container/indirect_container.hpp>
#include <falcon/container/reference_vector.hpp>
#include "indirect_container.hpp"

void indirect_container_test()
{
	struct A
	{
		int i;
		A& operator=(int n)
		{
			i = n;
			return *this;
		}
	};

	A i{0};
	falcon::container::vector<A&> v({i});
	i = 5;
	A i2{3};
	v.push_back(i2);
	i2 = 40;
	std::vector<A*> vv{{&i2}};
	//falcon::indirect_container(v).begin() = v.begin()->get()
	//falcon::indirect_container(vv).begin() = *vv.begin()
	CHECK(50 == v[0].i + falcon::indirect_container(v).begin()->i + falcon::indirect_container(vv).begin()->i);
}

FALCON_TEST_TO_MAIN(indirect_container_test)
