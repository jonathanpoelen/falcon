#include <array>
#include <falcon/coordinates/coord.hpp>
#include <falcon/coordinates/index.hpp>
#include "test/test.hpp"
#include "coordinates.hpp"

void coordinates_test()
{
	int w = 12, h = 8;
	int x1 = 2, y1 = 4, z1 = 8;
	int x2 = 0, y2 = 7, z2 = 1;

	using namespace falcon::coordinates;

	int i1 = index(w,h, x1,y1,z1);
	int i2 = index(w,h, x2,y2,z2);

	CHECK_EQUAL_VALUE(818, i1);
	CHECK_EQUAL_VALUE(180, i2);

	CHECK_EQUAL_VALUE(x1, coord_x<>(w, i1));
	CHECK_EQUAL_VALUE(y1, coord_y<>(w,h, i1));
	CHECK_EQUAL_VALUE(z1, coord_z<>(w,h, i1));

	CHECK_EQUAL_VALUE(x2, coord_x<>(w, i2));
	CHECK_EQUAL_VALUE(y2, coord_y<>(w,h, i2));
	CHECK_EQUAL_VALUE(z2, coord_z<>(w,h, i2));

	std::array<int, 3> acoord{{x1,y1,z1}};
	std::array<int, 2> asize{{w,h}};
	CHECK_EQUAL_VALUE(818, index2(acoord.begin(), acoord.end(), asize.begin()));

	std::array<int, 3> acoord2;
	coord2(asize.begin(), asize.end(), acoord2.begin(), 818);
	CHECK_EQUAL_VALUE(x1, acoord2[0]);
	CHECK_EQUAL_VALUE(y1, acoord2[1]);
	CHECK_EQUAL_VALUE(z1, acoord2[2]);
}

FALCON_TEST_TO_MAIN(coordinates_test)
