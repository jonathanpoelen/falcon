#include <falcon/coordinates/array_coord.hpp>
#include <falcon/coordinates/array_index.hpp>
#include "test/test.hpp"
#include "array_coordinates.hpp"

void array_coordinates_test()
{
	int w = 12, h = 8, z = 2;
	int x1 = 2, y1 = 4, z1 = 8;
	int x2 = 0, y2 = 7, z2 = 1;

	using namespace falcon::coordinates;

	{
		typedef std::array<int,1> array;
		typedef std::array<int,0> tuple;
		tuple tsize;
		array t1{{x1}};
		array t2{{x2}};
		int ti1 = array_index(tsize, t1);
		int ti2 = array_index(tsize, t2);

		CHECK_EQUAL_VALUE(2, ti1);
		CHECK_EQUAL_VALUE(0, ti2);

		CHECK_EQUAL_VALUE(2, array_coord(tsize, ti1)[0]);
		CHECK_EQUAL_VALUE(0, array_coord(tsize, ti2)[0]);
	}
	{
		typedef std::array<int,2> array;
		typedef array tuple;
		tuple tsize{{w,h}};
		array t1 {{x1,y1}};
		tuple t2{{x2,y2}};
		int ti1 = array_index(tsize, t1);
		int ti2 = array_index(tsize, t2);

		CHECK_EQUAL_VALUE(50, ti1);
		CHECK_EQUAL_VALUE(84, ti2);

		auto r1 = array_coord(tsize, ti1);
		auto r2 = array_coord(tsize, ti2);
		CHECK_EQUAL_VALUE(2, r1[0]);
		CHECK_EQUAL_VALUE(4, r1[1]);
		CHECK_EQUAL_VALUE(0, r2[0]);
		CHECK_EQUAL_VALUE(7, r2[1]);
	}
	{
		typedef std::array<int,3> array;
		typedef array tuple;
		tuple tsize{{w,h,z}};
		array t1{{x1,y1,z1}};
		tuple t2{{x2,y2,z2}};
		int ti1 = array_index(tsize, t1);
		int ti2 = array_index(tsize, t2);

		CHECK_EQUAL_VALUE(818, ti1);
		CHECK_EQUAL_VALUE(180, ti2);

		auto r1 = array_coord(tsize, ti1);
		auto r2 = array_coord(tsize, ti2);
		CHECK_EQUAL_VALUE(2, r1[0]);
		CHECK_EQUAL_VALUE(4, r1[1]);
		CHECK_EQUAL_VALUE(8, r1[2]);
		CHECK_EQUAL_VALUE(0, r2[0]);
		CHECK_EQUAL_VALUE(7, r2[1]);
		CHECK_EQUAL_VALUE(1, r2[2]);
	}
}

FALCON_TEST_TO_MAIN(array_coordinates_test)
