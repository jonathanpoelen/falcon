#ifndef FALCON_CONFIG_HPP
#define FALCON_CONFIG_HPP

#if defined(IN_KDEVELOP_PARSER) && !defined(IN_IDE_PARSER)
# define IN_IDE_PARSER
#endif

#if defined(IN_IDE_PARSER)
# define __cplusplus 201103L
# define __VA_ARGS__ 0
# define FALCON_IF_IN_IDE_PARSER(x) x
# define FALCON_IF_NOT_IN_IDE_PARSER(x)
#else
# define FALCON_IF_IN_IDE_PARSER(x)
# define FALCON_IF_NOT_IN_IDE_PARSER(x) x
#endif

#endif
