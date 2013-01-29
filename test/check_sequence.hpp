#ifndef FALCON_TEST_CHECK_SEQUENCE_HPP
#define FALCON_TEST_CHECK_SEQUENCE_HPP

#include "check.hpp"
#include <boost/typeof/typeof.hpp>
#include <falcon/container/range_access.hpp>

#define __CHECK_SEQUENCE_M(first, last, first2, last2, op, m)\
do {\
	int n_ = 0;\
	for ( ; first != last && first2 != last2; ++first, op first2){\
		if (*first != *first2)\
			std::cerr << "bad sequence test at " << n_ << std::endl;\
		CHECK_EQUAL_VALUE(*first, *first2);\
		m;\
		++n_;\
	}\
	if (first != last || first2 != last2)\
		std::cerr << "bad sequence test at " << n_ << std::endl;\
	CHECK(first == last);\
	CHECK(first2 == last2);\
} while(0)


#define CHECK_SEQUENCE_M(first, last, first2, last2, m)\
	__CHECK_SEQUENCE_M(first, last, first2, last2, ++, m)

#define CHECK_SEQUENCE_M2(cont, first, last, m)\
do {\
	BOOST_AUTO(Xfirst_##cont, falcon::begin(cont));\
	BOOST_AUTO(Xlast_##cont, falcon::end(cont));\
	CHECK_SEQUENCE_M(Xfirst_##cont, Xlast_##cont, first, last, m);\
} while(0)

#define CHECK_SEQUENCE_M3(cont, cont2, m)\
do {\
	BOOST_AUTO(Xfirst_##cont2, falcon::begin(cont2));\
	BOOST_AUTO(Xlast_##cont2, falcon::end(cont2));\
	CHECK_SEQUENCE_M2(cont, Xfirst_##cont2, Xlast_##cont2, m);\
} while(0)

#define CHECK_SEQUENCE(first, last, first2, last2)\
	CHECK_SEQUENCE_M(first, last, first2, last2, )

#define CHECK_SEQUENCE2(cont, first, last)\
do {\
	BOOST_AUTO(Xfirst_##cont, falcon::begin(cont));\
	BOOST_AUTO(Xlast_##cont, falcon::end(cont));\
	CHECK_SEQUENCE(Xfirst_##cont, Xlast_##cont, first, last);\
} while(0)

#define CHECK_SECHECK_SEQUENCE_MQUENCE3(cont, cont2)\
do {\
	BOOST_AUTO(Xfirst_##cont2, falcon::begin(cont2));\
	BOOST_AUTO(Xlast_##cont2, falcon::end(cont2));\
	CHECK_SEQUENCE2(cont, Xfirst_##cont2, Xlast_##cont2);\
} while(0)


#define CHECK_REVERSE_SEQUENCE_M(first, last, first2, last2, m)\
	__CHECK_SEQUENCE_M(first, last, first2, last2, --, m)

#define CHECK_REVERSE_SEQUENCE_M2(cont, first, last, m)\
do {\
	BOOST_AUTO(Xfirst_##cont, falcon::begin(cont));\
	BOOST_AUTO(Xlast_##cont, falcon::end(cont));\
	CHECK_REVERSE_SEQUENCE_M(Xfirst_##cont, Xlast_##cont, first, last, m);\
} while(0)

#define CHECK_REVERSE_SEQUENCE_M3(cont, cont2, m)\
do {\
	BOOST_AUTO(Xfirst_##cont2, falcon::begin(cont2));\
	BOOST_AUTO(Xlast_##cont2, falcon::end(cont2));\
	CHECK_REVERSE_SEQUENCE_M2(cont, Xfirst_##cont2, Xlast_##cont2, m);\
} while(0)

#define CHECK_REVERSE_SEQUENCE(first, last, first2, last2)\
	CHECK_REVERSE_SEQUENCE_M(first, last, first2, last2, )

#define CHECK_REVERSE_SEQUENCE2(cont, first, last)\
do {\
	BOOST_AUTO(Xfirst_##cont, falcon::begin(cont));\
	BOOST_AUTO(Xlast_##cont, falcon::end(cont));\
	CHECK_REVERSE_SEQUENCE(Xfirst_##cont, Xlast_##cont, first, last);\
} while(0)

#define CHECK_REVERSE_SEQUENCE3(cont, cont2)\
do {\
	BOOST_AUTO(Xfirst_##cont2, falcon::begin(cont2));\
	BOOST_AUTO(Xlast_##cont2, falcon::end(cont2));\
	CHECK_REVERSE_SEQUENCE2(cont, Xfirst_##cont2, Xlast_##cont2);\
} while(0)


#endif