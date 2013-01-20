#include <test/test.hpp>
#include <falcon/iterator/synchronize_iterator.hpp>
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
}

FALCON_TEST_TO_MAIN(synchronize_iterator_test)
