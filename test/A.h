#ifndef _FALCON_TEST_A_H
#define _FALCON_TEST_A_H

#include <falcon/unused_variable.hpp>
#include <boost/current_function.hpp>
#include <iostream>
using falcon::unused_variable;
using falcon::unused_variables;

struct A{
	int i;
	#ifdef __GXX_EXPERIMENTAL_CXX0X__
	A(A&&a):i(a.i) {std::cout << "A&&" << std::endl; }
	#endif
	A(const A&a):i(a.i) { std::cout << "const A&" << std::endl; }
	A(int ii=0):i(ii) { std::cout << "A(" << ii << ')' << std::endl; }

	~A() { std::cout << "~A" << std::endl; }

	A& operator=(const A&a) {i=a.i; std::cout << BOOST_CURRENT_FUNCTION << std::endl; return *this;}
	A& operator+=(int _i) {i+=_i; std::cout << BOOST_CURRENT_FUNCTION << std::endl; return *this; }
	A& operator+=(const A&a) {i+=a.i; std::cout << BOOST_CURRENT_FUNCTION << std::endl; return *this; }
	A operator+(int _i)const { std::cout << BOOST_CURRENT_FUNCTION << std::endl; return A(i+_i);}
	A operator+(const A&a)const { std::cout << BOOST_CURRENT_FUNCTION << std::endl; return A(i+a.i);}

	operator int() const {std::cout << BOOST_CURRENT_FUNCTION << std::endl; return i;}

	A* address() { return this; }
	const A* address() const { return this; }
	bool operator==(const A&a) const
	{
		return i==a.i;
	}
};

inline int operator+(int i, const A& a)
{ return a.i+i; }
inline int operator*(const A& a)
{ return a.i; }
// inline int operator&(const A& a)
// { unused_variable(a); return 0; }

inline A& operator<<(A& a, int i)
{ std::cout << i << std::endl; return a; }

inline bool operator==(const A& a, const A& b)
{ return a.i == b.i; }
inline bool operator<(const A& a, const A& b)
{ return a.i < b.i; }

#endif
