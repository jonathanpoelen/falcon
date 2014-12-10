#include <vector>
#include <test/test.hpp>
#include <falcon/iterator/is_iterable.hpp>
#include <falcon/container/range_access.hpp>
#include "is_iterable.hpp"

void is_iterable_test()
{
	using falcon::is_iterable;
	using falcon::is_reversible_iterable;

	STATIC_CHECK_VALUE(false, is_iterable<int>);
	STATIC_CHECK_VALUE(true, is_iterable<int[5]>);
	STATIC_CHECK_VALUE(false, is_reversible_iterable<int>);
	STATIC_CHECK_VALUE(true, is_reversible_iterable<int[5]>);

	typedef std::vector<int> container;
	typedef typename container::iterator iterator;
	typedef std::vector<container> w_container;
	typedef typename w_container::iterator w_iterator;

	CHECK_TYPE(iterator, falcon::range_access_iterator<container>);
	CHECK_TYPE(w_iterator, falcon::range_access_iterator<w_container>);

	STATIC_CHECK_VALUE(true, is_iterable<container>);
	STATIC_CHECK_VALUE(true, is_reversible_iterable<container>);

	STATIC_CHECK_VALUE(true, is_iterable<w_container>);
	STATIC_CHECK_VALUE(true, is_reversible_iterable<w_container>);

	STATIC_CHECK_VALUE(false, is_iterable<iterator>);
	STATIC_CHECK_VALUE(false, is_reversible_iterable<w_iterator>);
}
FALCON_TEST_TO_MAIN(is_iterable_test)
