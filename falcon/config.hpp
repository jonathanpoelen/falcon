#ifndef FALCON_CONFIG_HPP
#define FALCON_CONFIG_HPP

#if defined(IN_KDEVELOP_PARSER) && !defined(IN_IDE_PARSER)
# define IN_IDE_PARSER
#endif

#if defined(IN_IDE_PARSER)
# define __cplusplus 201103L
# define __VA_ARGS__ 0
#endif

#endif
