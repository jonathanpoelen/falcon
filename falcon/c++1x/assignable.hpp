#ifndef FALCON_CPP1X_VISIBILITY_HPP
#define FALCON_CPP1X_VISIBILITY_HPP

#include <falcon/c++1x/warning.hpp>

#include <falcon/c++/assignable.hpp>

#define CPP1X_DEFAULT __CPP_DEFAULT
#define CPP1X_DELETE  __CPP_DELETE
#define CPP1X_FINAL   __CPP_FINAL

#define CPP1X_DELETE_COPY_CONSTUCTIBLE(class_name)\
	CPP_DELETE_COPY_CONSTUCTIBLE(class_name)

#define CPP1X_DELETE_ASSIGNABLE(class_name)\
	CPP_DELETE_ASSIGNABLE(class_name)

#define CPP1X_DELETE_SGI_ASSIGNABLE(class_name)\
	CPP_DELETE_SGI_ASSIGNABLE(class_name)


#define CPP1X_DEFAULT_COPY_CONSTUCTIBLE(class_name)\
	__CPP_COPY_CONSTRUCTOR(class_name) = default

#define CPP1X_DEFAULT_ASSIGNABLE(class_name)\
	__CPP_ASSIGNABLE(class_name) = default

#define CPP1X_DEFAULT_SGI_ASSIGNABLE(class_name)\
	CPP1X_DEFAULT_COPY_CONSTUCTIBLE(class_name);\
	CPP1X_DEFAULT_ASSIGNABLE(class_name)

#endif