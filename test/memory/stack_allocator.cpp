#include <test/test.hpp>
#include <falcon/memory/stack_allocator.hpp>
#include "stack_allocator.hpp"
#include "A.h"

#include <boost/io/ios_state.hpp>

#if !defined(IN_IDE_PARSER)
template<falcon::stack_allocator_flag::flags _Flag>
#endif
void stack_allocator_test_impl()
{
	typedef falcon::stack_allocator<A, 10, _Flag> allocator_type;
	allocator_type alloc;
	typename allocator_type::pointer p;
	p = alloc.allocate(1);
	alloc.construct(p, 34);
	alloc.destroy(p);
	alloc.deallocate(p, 1);
	std::flush<>(std::cout);
	if (!(_Flag & falcon::stack_allocator_flag::always_one)) {
		p = alloc.allocate(4);
		alloc.construct(p, 534);
		alloc.construct(p+1, 34);
		alloc.construct(p+2, 44);
		alloc.construct(p+3, 234);
		alloc.destroy(p);
		alloc.destroy(p+1);
		alloc.destroy(p+2);
		alloc.destroy(p+3);
		alloc.deallocate(p, 4);
	}

	alloc.allocate(1);
	std::cout << "--" << std::endl;
	alloc.allocate(1);
	std::cout << "--" << std::endl;
	alloc.allocate(1);
	std::cout << "--" << std::endl;
	alloc.allocate(1);
	std::cout << "--" << std::endl;
	alloc.allocate(1);
	std::cout << "--" << std::endl;

	alloc.allocate(1);
	std::cout << "--" << std::endl;
	alloc.allocate(1);
	std::cout << "--" << std::endl;
	alloc.allocate(1);
	std::cout << "--" << std::endl;
	alloc.allocate(1);
	std::cout << "--" << std::endl;
	alloc.allocate(1);
	std::cout << "--" << std::endl;

	bool b = false;
	try {
		alloc.allocate(1);
	} catch (std::bad_alloc& e) {
		b = true;
	}

	if (!b) {
		std::cout << "not throw" << std::endl;
	}
}

void stack_allocator_test()
{
	std::cout.sync_with_stdio(false);
	std::stringbuf sbuf;
	boost::io::ios_rdbuf_saver rdbuf_saver(std::cout, &sbuf);

	typedef falcon::stack_allocator_flag flag_t;

	stack_allocator_test_impl<flag_t::normal_storage>();
	std::cout << "1" << std::endl;
	stack_allocator_test_impl<flag_t::minimal_storage>();
	std::cout << "2" << std::endl;
	stack_allocator_test_impl<flag_t::always_one>();
	std::cout << "3" << std::endl;
	stack_allocator_test_impl<flag_t::lifo_allocation>();
	std::cout << "4" << std::endl;
	stack_allocator_test_impl<flag_t::minimal_storage|flag_t::lifo_allocation>();
	std::cout << "5" << std::endl;
	stack_allocator_test_impl<flag_t::lifo_allocation|flag_t::always_one>();
	std::cout << "6" << std::endl;
	stack_allocator_test_impl<flag_t::minimal_storage|flag_t::always_one>();
	std::cout << "7" << std::endl;
	stack_allocator_test_impl<flag_t::speed_deduction|flag_t::always_one>();
	std::cout << "8" << std::endl;
	stack_allocator_test_impl<flag_t::minimal_storage|flag_t::always_one|flag_t::lifo_allocation>();
	std::cout << "9" << std::endl;
	CHECK_EQUAL_VALUE(sbuf.str(),
	"A(34)\n"
	"~A(34)\n"
	"A(534)\n"
	"A(34)\n"
	"A(44)\n"
	"A(234)\n"
	"~A(534)\n"
	"~A(34)\n"
	"~A(44)\n"
	"~A(234)\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"1\n"
	"A(34)\n"
	"~A(34)\n"
	"A(534)\n"
	"A(34)\n"
	"A(44)\n"
	"A(234)\n"
	"~A(534)\n"
	"~A(34)\n"
	"~A(44)\n"
	"~A(234)\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"2\n"
	"A(34)\n"
	"~A(34)\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"3\n"
	"A(34)\n"
	"~A(34)\n"
	"A(534)\n"
	"A(34)\n"
	"A(44)\n"
	"A(234)\n"
	"~A(534)\n"
	"~A(34)\n"
	"~A(44)\n"
	"~A(234)\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"4\n"
	"A(34)\n"
	"~A(34)\n"
	"A(534)\n"
	"A(34)\n"
	"A(44)\n"
	"A(234)\n"
	"~A(534)\n"
	"~A(34)\n"
	"~A(44)\n"
	"~A(234)\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"5\n"
	"A(34)\n"
	"~A(34)\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"6\n"
	"A(34)\n"
	"~A(34)\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"7\n"
	"A(34)\n"
	"~A(34)\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"8\n"
	"A(34)\n"
	"~A(34)\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"--\n"
	"9\n");
}

FALCON_TEST_TO_MAIN(stack_allocator_test)
