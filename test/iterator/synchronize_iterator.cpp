#include <sstream>
#include <algorithm>
#include <test/test.hpp>
#include <falcon/iterator/synchronize_iterator.hpp>
#include <falcon/tuple/tuple_applier.hpp>
#include "synchronize_iterator.hpp"

void synchronize_iterator_test()
{
	char s[] = {'p','l','o','p','\0'};
	char s2[] = {'a','b','c','d','\0'};
	{
		typedef char * iterator;
		typedef iterator iterator2;
		falcon::iterator::synchronize_iterator<iterator, iterator2> first(&s[0], &s2[0]);
		falcon::iterator::synchronize_iterator<iterator, iterator2> last(&s[4], &s2[4]);
		int i = 0;
		for (; first != last; ++first){
			++*first;
			++i;
		}
		CHECK(i == 4);
		CHECK(s[0] == 'q' && s[1] == 'm' && s[2] == 'p' && s[3] == 'q');
		CHECK(s2[0] == 'b' && s2[1] == 'c' && s2[2] == 'd' && s2[3] == 'e');
	}
	{
		typedef char * iterator;
		typedef iterator iterator2;
		typedef falcon::iterator::synchronize_iterator<iterator, iterator2, falcon::first_parameter_index_tag<>> synchronize_iterator;
		synchronize_iterator first(&s[0], &s2[0]);
		synchronize_iterator last(&s[2], &s2[1]);
		int i = 0;
		for (; first != last; ++first){
			++*first;
			++i;
		}
		CHECK(i == 2);
		CHECK(s[0] == 'r' && s[1] == 'n' && s[2] == 'p' && s[3] == 'q');
		CHECK(s2[0] == 'c' && s2[1] == 'd' && s2[2] == 'd' && s2[3] == 'e');
	}

	{
		int a[]{0,1,2,3,4,5,6,7,8,9};
		int a2[]{1,2,3,4,5,6,7,8,9,10};
		std::ostringstream ss;

		std::for_each<>(falcon::iterator::make_synchronize_iterator<>(&a[0], &a2[0]),
										falcon::iterator::make_synchronize_iterator<>(&a[10], &a2[10]),
										falcon::make_tuple_applier([&ss](int i,int i2){
											ss << i << '-' << i2 << '\n';
										}));
		CHECK_EQUAL_VALUE(ss.str(), "0-1\n1-2\n2-3\n3-4\n4-5\n5-6\n6-7\n7-8\n8-9\n9-10\n");
	}
}

FALCON_TEST_TO_MAIN(synchronize_iterator_test)
