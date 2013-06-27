#ifndef FALCON_UTILITY_MOVE_HPP
#define FALCON_UTILITY_MOVE_HPP

#if __cplusplus >= 201103L
# include <utility>
# define FALCON_MOVE(value) std::move(value)
# define FALCON_FORWARD(type, value) std::forward<type>(value)
#else
# define FALCON_MOVE(value) value
# define FALCON_FORWARD(type, value) value
#endif

#endif
