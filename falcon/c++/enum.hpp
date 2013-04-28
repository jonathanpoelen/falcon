#ifndef FALCON_CPP_ENUM_HPP
#define FALCON_CPP_ENUM_HPP

#include <falcon/config.hpp>

#if __cplusplus < 201103L

# define CPP_SCOPED_ENUM_START(name) struct name { enum enum_t
# define CPP_SCOPED_ENUM_START2(name, type) CPP_SCOPED_ENUM_START(name)
# define CPP_SCOPED_ENUM_END };
# define CPP_SCOPED_ENUM(name) name::enum_t
# define CPP_ENUM_TYPE(type)

#else

# define CPP_SCOPED_ENUM_START(name) enum class name
# define CPP_SCOPED_ENUM_START2(name, type) enum class name : type
# define CPP_SCOPED_ENUM_END
# define CPP_SCOPED_ENUM(name) name
# define CPP_ENUM_TYPE(type) :type

#endif

#endif