#ifndef FALCON_CPP_VISIBILITY_HPP
#define FALCON_CPP_VISIBILITY_HPP

#if __cplusplus > 201100L

# define CPP_DEFAULT = default
# define CPP_DELETE = delete
# define CPP_FINAL final

# define __CPP_DELETE_VISIBILITY

#else

# define CPP_DEFAULT
# define CPP_DELETE
# define CPP_FINAL

# define __CPP_DELETE_VISIBILITY private:

#endif


#define __CPP_COPY_CONSTRUCTOR(class_name) class_name(const class_name&)
#define __CPP_ASSIGNABLE(class_name) class_name& operator=(const class_name&)

#define CPP_DELETE_COPY_CONSTUCTIBLE(class_name)\
	__CPP_DELETE_VISIBILITY __CPP_COPY_CONSTRUCTOR(class_name) CPP_DELETE;

#define CPP_DELETE_ASSIGNABLE(class_name)\
	__CPP_DELETE_VISIBILITY __CPP_ASSIGNABLE(class_name) CPP_DELETE;

#define CPP_DELETE_SGI_ASSIGNABLE(class_name)\
	CPP_DELETE_COPY_CONSTUCTIBLE(class_name)\
	CPP_DELETE_ASSIGNABLE(class_name)

#endif