#ifndef FALCON_CPP_CONDITIONAL_CPP_HPP
#define FALCON_CPP_CONDITIONAL_CPP_HPP

#if __cplusplus == 201103L
// enable if c++11 only
# define CPP_IF_CPP11(x) x
// enable if not c++011 or later
# define CPP_IF_NOT_CPP11(x)
#else
// enable if c++11 only
# define CPP_IF_CPP11(x)
// enable if not c++11 or later
# define CPP_IF_NOT_CPP11(x) x
#endif

#if __cplusplus >= 201103L
// enable if c++11 or later
# define CPP_IF_CPP1X(x) x
// enable if not c++11 or later
# define CPP_IF_NOT_CPP1X(x)
#else
// enable if c++11 or later
# define CPP_IF_CPP1X(x)
// enable if not c++11 or later
# define CPP_IF_NOT_CPP1X(x) x
#endif

#if __cplusplus > 201103L
// enable if c++14 or later
# define CPP_IF_CPP1Y(x) x
// enable if not c++14 or later
# define CPP_IF_NOT_CPP1Y(x)
#else
// enable if c++14 or later
# define CPP_IF_CPP1Y(x)
// enable if not c++14 or later
# define CPP_IF_NOT_CPP1Y(x) x
#endif

#endif
