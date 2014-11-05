#include <vector>
#include <test/test.hpp>
#include <test/check_sequence.hpp>
#include <falcon/iterator/indirect_iterator.hpp>
#include <falcon/functional/operators.hpp>
#include "indirect_iterator.hpp"

void indirect_iterator_test()
{
	typedef std::vector<int*> container_type;
	typedef typename container_type::iterator iterator;

	{
		int a = 0, b = 1, c = 2, d = 3, e = 4;
		container_type cont = {&a,&b,&c,&d,&e};

		falcon::iterator::indirect_iterator<iterator> it(cont.begin());
		falcon::iterator::indirect_iterator<iterator> end(cont.end());

		{
			int ab [] = {0,1,2,3,4};
			CHECK_SEQUENCE_M2(ab, it, end, ++*it);
		}
		it = cont.begin();
		{
			int ab [] = {1,2,3,4,5};
			CHECK_SEQUENCE2(ab, it, end);
		}
	}

	{
		int a = 0, b = 1, c = 2, d = 3, e = 4;
		container_type cont = {&a,&b,&c,&d,&e};

		typedef falcon::iterator::indirect_iterator<iterator, falcon::dereference<int*>> pointer_iterator;
		pointer_iterator it(cont.begin());
		pointer_iterator end(cont.end());

		{
			int ab [] = {0,1,2,3,4};
			CHECK_SEQUENCE_M2(ab, it, end, ++*it);
		}
		it = cont.begin();
		{
			int ab [] = {1,2,3,4,5};
			CHECK_SEQUENCE2(ab, it, end);
		}
	}
}
FALCON_TEST_TO_MAIN(indirect_iterator_test)
