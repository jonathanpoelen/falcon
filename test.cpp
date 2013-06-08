#include <iostream>

// #include <memory>
#include <vector>
// #include <array>
#include "test/A.h"
#include <falcon/memory/generic_allocator.hpp>
#include <falcon/utility/maker.hpp>

using namespace std;

// struct P {int x, y; ~P(){cout << "~" << x << " " << y << "\n"; }};
struct PP {int x; ~PP(){cout << "~" << x << "\n"; }};
using P = PP[2];

int main(/*int argc, char **argv*/)
{
	std::cout.sync_with_stdio(false);

	typedef std::vector<P, falcon::generic_allocator<P>> container_t;
	container_t vec/*({P{2,3}})*/;
	vec.reserve(4);
	vec.emplace_back<>(PP{4},PP{2});

	P a{2,7};
	vec.push_back(a);
	vec.push_back(P{3,1});
	vec.emplace_back<>(P{9,8});
	for (auto& value: vec)
	{
		cout << value[0].x << ", " << value[1].x << '\n';
	}
}

