#include <test/test.hpp>
#include <falcon/memory/range_allocator.hpp>
#include "range_allocator.hpp"
#include "test/A.h"

#include <boost/io/ios_state.hpp>

void range_allocator_test()
{
	std::cout.sync_with_stdio(false);
	std::stringbuf sbuf;
	boost::io::ios_rdbuf_saver rdbuf_saver(std::cout, &sbuf);

	constexpr size_t len = 500;
	falcon::byte_t memory[len];
	falcon::range_allocator<A> allocator(memory, &memory[0]+len);
	A * p = allocator.allocate(2);
	allocator.construct<>(p, 2);
	allocator.construct<>(p+1, 4);
	A * p2 = allocator.allocate(3);
	allocator.construct<>(p2, 12);
	allocator.construct<>(p2+1, 14);
	allocator.construct<>(p2+2, 15);
	allocator.destroy<>(p+1);
	allocator.destroy<>(p);
	allocator.deallocate(p,2);
	p = allocator.allocate(2);
	allocator.construct<>(p, 2);
	allocator.construct<>(p+1, 4);
	allocator.destroy<>(p2+2);
	allocator.destroy<>(p2+1);
	allocator.destroy(p2);
	allocator.deallocate(p2,3);
	allocator.destroy<>(p+1);
	allocator.destroy<>(p);
	allocator.deallocate(p,2);

	CHECK_EQUAL_VALUE(sbuf.str(),
	"A(2)\n"
	"A(4)\n"
	"A(12)\n"
	"A(14)\n"
	"A(15)\n"
	"~A(4)\n"
	"~A(2)\n"
	"A(2)\n"
	"A(4)\n"
	"~A(15)\n"
	"~A(14)\n"
	"~A(12)\n"
	"~A(4)\n"
	"~A(2)\n"
	);
}

FALCON_TEST_TO_MAIN(range_allocator_test)
