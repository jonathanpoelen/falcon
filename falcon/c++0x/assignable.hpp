#ifndef FALCON_CPP0X_VISIBILITY_HPP
#define FALCON_CPP0X_VISIBILITY_HPP

#include <falcon/c++0x/warning.hpp>

#include <falcon/c++/assignable.hpp>

#define CPP0X_DEFAULT CPP_DEFAULT
#define CPP0X_DELETE  CPP_DELETE
#define CPP0X_FINAL   CPP_FINAL

#define CPP0X_DELETE_COPY_CONSTUCTIBLE(class_name)\
	CPP_DELETE_COPY_CONSTUCTIBLE(class_name)

#define CPP0X_DELETE_ASSIGNABLE(class_name)\
	CPP_DELETE_ASSIGNABLE(class_name)

#define CPP0X_DELETE_SGI_ASSIGNABLE(class_name)\
	CPP_DELETE_SGI_ASSIGNABLE(class_name)


#define CPP0X_DEFAULT_COPY_CONSTUCTIBLE(class_name)\
	__CPP_COPY_CONSTRUCTOR(class_name) CPP_DEFAULT

#define CPP0X_DEFAULT_ASSIGNABLE(class_name)\
	__CPP_ASSIGNABLE(class_name) CPP_DEFAULT

#define CPP0X_DEFAULT_SGI_ASSIGNABLE(class_name)\
	CPP0X_DEFAULT_COPY_CONSTUCTIBLE(class_name);\
	CPP0X_DEFAULT_ASSIGNABLE(class_name)

#endif