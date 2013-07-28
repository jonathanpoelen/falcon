#ifndef _FALCON_TEST_A_H
#define _FALCON_TEST_A_H

#include <boost/current_function.hpp>
#include <iostream>

struct A{
  int i;
#if __cplusplus >= 201103L
  A(A&&a):i(a.i) {std::cout << "A(" << i << ")&&" << std::endl; }
#endif
  A(const A&a):i(a.i) { std::cout << "const A(" << i << ")&" << std::endl; }
  A(int ii=0):i(ii) { std::cout << "A(" << ii << ')' << std::endl; }

  ~A() { std::cout << "~A(" << i << ')' << std::endl; }

  A& operator=(const A&a) {i=a.i; std::cout << "A& A::operator=(A(" << a.i << "))" << std::endl; return *this;}
  A& operator=(int ii) {i=ii; std::cout << "A& A::operator=(" << ii << ')' << std::endl; return *this;}
  A& operator+=(int ii) {i+=ii; std::cout << "A& A::operator+=(" << ii << ')' << std::endl; return *this; }
  A& operator+=(const A&a) {i+=a.i; std::cout << "A& A::operator+=(A(" << a.i << "))" << std::endl; return *this; }
  A operator+(int ii)const { std::cout << "A& A::operator+(" << ii << ')' << std::endl; return A(i+ii);}
  A operator+(const A&a)const { std::cout << "A& A::operator+(A(" << a.i << "))" << std::endl; return A(i+a.i);}

  operator int() const {std::cout << BOOST_CURRENT_FUNCTION << std::endl; return i;}

  A* address() { return this; }
  const A* address() const { return this; }
};

inline int operator+(int i, const A& a)
{ return a.i+i; }
inline int operator*(const A& a)
{ return a.i; }

inline A& operator<<(A& a, int i)
{ std::cout << i << std::endl; return a; }

inline bool operator==(const A& a, const A& b)
{ return a.i == b.i; }
inline bool operator<(const A& a, const A& b)
{ return a.i < b.i; }

#endif
