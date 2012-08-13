#ifndef _FALCON_DETAIL_TYPEOF_HPP
#define _FALCON_DETAIL_TYPEOF_HPP

#ifndef __GXX_EXPERIMENTAL_CXX0X__
# include <boost/typeof/typeof.hpp>
# define __FALCON_TYPEOF(Expr) BOOST_TYPEOF(Expr)
# define __FALCON_TYPEOF_WRAP_EXPR(Expr) BOOST_TYPEOF(Expr)
#else
#include <type_traits>
//NOTE __FALCON_TYPEOF((Temp<5,int>::value)) = decltype((Temp<5,int>::value)) = reference -> (decltype((int)) = int&)
// # define __FALCON_TYPEOF(Expr) decltype(Expr)
# define __FALCON_TYPEOF(Expr) typename std::conditional<std::is_same<decltype((Expr)), decltype(Expr)>::value, decltype(Expr), typename std::remove_reference<decltype(Expr)>::type>::type
# define __FALCON_TYPEOF_WRAP_EXPR(Expr) decltype Expr
#endif

#define __FALCON_TYPEOF_INIT(Expr) __FALCON_TYPEOF(Expr) NameVar = Expr
#define __FALCON_TYPEOF_INIT_WRAP_EXPR(NameVar, Expr) __FALCON_TYPEOF_WRAP_EXPR(Expr) NameVar = Expr

#endif