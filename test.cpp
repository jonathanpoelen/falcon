#include <iostream>

// #include <memory>
// #include <vector>
// #include <array>
#include "test/A.h"
#include <falcon/memory/free_list_allocator.hpp>
// #include <falcon/utility/maker.hpp>

using namespace std;

// struct P {int x, y; ~P(){cout << "~" << x << " " << y << "\n"; }};
// struct PP {int x; ~PP(){cout << "~" << x << "\n"; }};
// using P = PP[2];

int main(/*int argc, char **argv*/)
{
	falcon::free_list_allocator<A> alloc;
	A * p = alloc.allocate(1);
	alloc.construct<>(p, 1);
	alloc.destroy<>(p);
	alloc.deallocate(p, 1);
}

