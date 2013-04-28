#ifndef FALCON_CPP_INITIALIZE_HPP
#define FALCON_CPP_INITIALIZE_HPP

#include <falcon/config.hpp>

#if defined(IN_IDE_PARSER)
# define CPP_INITIALIZE(args...) (args)
#elif __cplusplus < 201103L
# define CPP_INITIALIZE(...) (__VA_ARGS__)
#else
# define CPP_INITIALIZE(...) {__VA_ARGS__}
#endif

#endif