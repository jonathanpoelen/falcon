#include <iostream>
// #include <memory>
// #include <vector>
// #include <array>
#include "test/A.h"
#include <falcon/memory/free_list_allocator.hpp>

using namespace std;

int main(/*int argc, char **argv*/)
{
	falcon::free_list_allocator<A> alloc(1);
	A * p = alloc.allocate(1);
	alloc.construct<>(p, 1);
	alloc.destroy<>(p);
	alloc.deallocate(p, 1);
}

