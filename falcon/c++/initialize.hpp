#ifndef FALCON_CPP_INITIALIZE_HPP
#define FALCON_CPP_INITIALIZE_HPP

#if __cplusplus > 201100L
# define CPP_INITIALIZE(values...) {values}
#else
# define CPP_INITIALIZE(values...) (values)
#endif

#endif