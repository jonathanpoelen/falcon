#include <functional>
#include <falcon/functional/short_circuit.hpp>
#include <falcon/functional/placeholder_for_argument.hpp>
#include <falcon/algorithm/algorithm.hpp>
#include <test/test.hpp>
#include "short_circuit.hpp"

void short_circuit_test()
{
	int a[] = {0, 1, 2, 3, 4, 2, 5, 6, 7, 8, 9, 10};
	typedef falcon::placeholder_for_argument<3, std::greater<int>, int> functor_type;
	functor_type func(3);
	CHECK_EQUAL_VALUE(8, *falcon::find_if(a, falcon::short_circuit<functor_type&>(4, func)));
}
FALCON_TEST_TO_MAIN(short_circuit_test)
