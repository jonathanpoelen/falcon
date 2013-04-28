#ifndef _FALCON_PREPROCESSOR_MOVE_HPP
#define _FALCON_PREPROCESSOR_MOVE_HPP

#if __cplusplus >= 201103L
# include <utility>
# define FALCON_MOVE(value) std::move(value)
# define FALCON_FORWARD(type, value) std::forward<type>(value)
# define FALCON_RVALUE(type) type&&
#else
# define FALCON_MOVE(value) value
# define FALCON_FORWARD(type, value) value
# define FALCON_RVALUE(type) const type&
#endif

#endif