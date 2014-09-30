#ifndef FALCON_CPP_CONDITIONAL_CPP_HPP
#define FALCON_CPP_CONDITIONAL_CPP_HPP

#if __cplusplus == 201103L
// enable if c++11 only
# define CPP_IF_CPP11(x) x
// enable if not c++011 or later
# define CPP_IF_NOT_CPP11(x)
# define CPP_IF_ELSE_CPP11(yes, no) yes
#else
// enable if c++11 only
# define CPP_IF_CPP11(x)
// enable if not c++11 or later
# define CPP_IF_NOT_CPP11(x) x
# define CPP_IF_ELSE_CPP11(yes, no) no
#endif

#if __cplusplus >= 201103L
// enable if c++11 or later
# define CPP_IF_CPP1X(x) x
// enable if not c++11 or later
# define CPP_IF_NOT_CPP1X(x)
# define CPP_IF_ELSE_CPP1X(yes, no) yes
#else
// enable if c++11 or later
# define CPP_IF_CPP1X(x)
// enable if not c++11 or later
# define CPP_IF_NOT_CPP1X(x) x
# define CPP_IF_ELSE_CPP1X(yes, no) no
#endif

#if __cplusplus > 201103L
// enable if c++14 or later
# define CPP_IF_CPP1Y(x) x
// enable if not c++14 or later
# define CPP_IF_NOT_CPP1Y(x)
# define CPP_IF_ELSE_CPP1Y(yes, no) yes
#else
// enable if c++14 or later
# define CPP_IF_CPP1Y(x)
// enable if not c++14 or later
# define CPP_IF_NOT_CPP1Y(x) x
# define CPP_IF_ELSE_CPP1Y(yes, no) no
#endif

#endif
