#include <vector>
#include <test/test.hpp>
#include <test/check_sequence.hpp>
#include <falcon/iterator/recursive_iterator.hpp>
#include "recursive_iterator.hpp"

void recursive_iterator_test()
{
	{
		typedef std::vector<int> subcontainer;
		typedef std::vector<std::vector<int>> container;
		typedef subcontainer::iterator subiterator;
		typedef container::iterator iterator;

		container v({
			{0,1,2,3},
			{4,5,6,7}
		});

		auto first = falcon::iterator::recursive_iterator<>(v);
		auto last = std::end(v[1]);

		{
			int a[] = {0,1,2,3,4,5,6,7};
			CHECK_SEQUENCE2(a, first, last);
		}

		typedef decltype(first) recursive_iterator;
		CHECK_NOTYPENAME_TYPE(
			recursive_iterator,
			falcon::iterator::basic_recursive_iterator<
				falcon::parameter_pack<
					iterator,
					subiterator
				>
			>
		);

		recursive_iterator random(true, std::begin(v[1])+2);
		first = falcon::iterator::recursive_iterator<>(v);
		std::advance<>(first, 6);
		CHECK(first == random);
	}

	{
		typedef std::pair<int*, int*> pair2;
		typedef int(*r2_t)[2][2];
		typedef int(*r1_t)[2];
		typedef std::pair<r1_t, r1_t> pair3;
		typedef std::pair<r2_t, r2_t> pair4;
		typedef std::tuple<bool, pair4, pair3, pair2> tuple;
		typedef falcon::iterator::basic_recursive_iterator<falcon::parameter_pack<r2_t, r1_t, int*>> recursive_iterator;
		int array[3][2][2] = {
			{{0,1},{2,3}},
			{{4,5},{6,7}},
			{{8,9},{10,11}}
		};
		auto first1 = std::begin(array);
		auto last1 = std::end(array);
		auto last2 = std::end(*(last1-1));
		recursive_iterator lastrec(true, std::begin(*(last2-1)));
		auto rec = falcon::iterator::recursive_iterator<>(array);
		CHECK_NOTYPENAME_TYPE(decltype(rec), recursive_iterator);
		recursive_iterator tmp = rec;
		(void)tmp;
		recursive_iterator rec2(tuple(
			true,
			pair4(first1, last1),
			pair3(last2-1, last2),
			pair2(std::begin(*(std::begin(*first1)+2))+2, nullptr)
		));

		{
			int a[] = {0,1,2,3,4,5,6,7,8,9};
			int n = 10;
			CHECK_SEQUENCE_M2(a, rec, lastrec, CHECK(!!(n--) == (rec != *(last2-1))));
		}
		CHECK_EQUAL_VALUE(10, *rec);
		CHECK(rec == *(last2-1));
		CHECK(rec == lastrec);
		CHECK(rec.valid());
		CHECK_EQUAL_VALUE(11, *++rec);
		CHECK(rec != *(last2-1));
		CHECK(rec != lastrec);
		CHECK(rec.valid());
		++rec;
		CHECK(!rec.valid());
	}

	{
		typedef std::vector<int> v1_t;
		typedef std::vector<v1_t> v2_t;
		typedef std::vector<v2_t> v3_t;

		v3_t cont{{{7}}};

		auto rec = falcon::iterator::recursive_iterator<>(cont);
		decltype(rec) last;
		CHECK_EQUAL_VALUE(7, *rec);
		CHECK(rec != last);
		CHECK(rec.valid());
		++rec;
		CHECK(rec == last);
		CHECK(!rec.valid());

		rec + 2l;
	}
}

FALCON_TEST_TO_MAIN(recursive_iterator_test)
