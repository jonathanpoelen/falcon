#ifndef FALCON_CPP_VISIBILITY_HPP
#define FALCON_CPP_VISIBILITY_HPP

#include <falcon/config.hpp>

#if __cplusplus >= 201103L

# define __CPP_DEFAULT = default
# define __CPP_DELETE = delete
# define __CPP_FINAL final

# define __CPP_DELETE_VISIBILITY

#else

# define __CPP_DEFAULT
# define __CPP_DELETE
# define __CPP_FINAL

# define __CPP_DELETE_VISIBILITY private:

#endif


#define __CPP_COPY_CONSTRUCTOR(class_name) class_name(const class_name&)
#define __CPP_ASSIGNABLE(class_name) class_name& operator=(const class_name&)

#define CPP_DELETE_COPY_CONSTUCTIBLE(class_name)\
	__CPP_DELETE_VISIBILITY __CPP_COPY_CONSTRUCTOR(class_name) __CPP_DELETE;

#define CPP_DELETE_ASSIGNABLE(class_name)\
		__CPP_DELETE_VISIBILITY __CPP_ASSIGNABLE(class_name) __CPP_DELETE;

#define CPP_DELETE_SGI_ASSIGNABLE(class_name)\
	CPP_DELETE_COPY_CONSTUCTIBLE(class_name)\
	CPP_DELETE_ASSIGNABLE(class_name)

#endif