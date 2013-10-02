#include <test/test.hpp>
#include <falcon/tuple/to_tuple_pointer.hpp>
#include <falcon/tuple/tuple_modifier.hpp>
#include <falcon/tuple/tuple_assign.hpp>
#include <falcon/functional/operators.hpp>
#include "to_tuple_pointer.hpp"

void to_tuple_pointer_test()
{
	typedef std::tuple<int, int> tuple_type;
	typedef typename falcon::tuple_modifier<std::add_pointer, tuple_type>::type tuple_pointer_type;
	tuple_type t(1,2);
	auto t2 = falcon::to_tuple_pointer<>(t);
	tuple_pointer_type t3;
	falcon::tuple_assign<>(t3, t, falcon::late_address());

	CHECK_NOTYPENAME_TYPE(tuple_pointer_type, decltype(t2));
	CHECK_NOTYPENAME_TYPE(tuple_pointer_type, std::tuple<int*, int*>);

    using std::get;
    
	CHECK_EQUAL_VALUE(1, *get<0>(t2));
	CHECK_EQUAL_VALUE(2, *get<1>(t2));
	CHECK_EQUAL_VALUE(1, *get<0>(t3));
	CHECK_EQUAL_VALUE(2, *get<1>(t3));
}
FALCON_TEST_TO_MAIN(to_tuple_pointer_test)
