#include <iostream>
// #include <falcon/memory/stack_allocator.hpp>
// #include <test/A.h>
#include <falcon/string/basic_cstring.hpp>

int main(/*int argc, char **argv*/)
{
	constexpr falcon::const_cstring s1("s");
	constexpr const char ss[]{""};
	constexpr falcon::const_cstring s2(ss);
// 	typedef falcon::stack_allocator<A, 10> allocator_type;
// 	allocator_type alloc;
// 	allocator_type::pointer p;
// 	p = alloc.allocate(1);
// 	alloc.construct(p, 34);
// 	alloc.destroy(p);
// 	alloc.deallocate(p, 1);
// 	std::flush<>(std::cout);
// 	p = alloc.allocate(4);
// 	alloc.construct(p, 534);
// 	alloc.construct(p+1, 34);
// 	alloc.construct(p+2, 44);
// 	alloc.construct(p+3, 234);
// 	alloc.destroy(p);
// 	alloc.destroy(p+1);
// 	alloc.destroy(p+2);
// 	alloc.destroy(p+3);
// 	alloc.deallocate(p, 4);
//
// 	alloc.allocate(1);
// 	std::cout << "--\n";
// 	alloc.allocate(1);
// 	std::cout << "--\n";
// 	alloc.allocate(1);
// 	std::cout << "--\n";
// 	alloc.allocate(1);
// 	std::cout << "--\n";
// 	alloc.allocate(1);
// 	std::cout << "--\n";
//
// 	alloc.allocate(1);
// 	std::cout << "--\n";
// 	alloc.allocate(1);
// 	std::cout << "--\n";
// 	alloc.allocate(1);
// 	std::cout << "--\n";
// 	alloc.allocate(1);
// 	std::cout << "--\n";
// 	alloc.allocate(1);
// 	std::cout << "--\n";
}
