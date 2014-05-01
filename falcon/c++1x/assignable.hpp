#ifndef FALCON_CPP1X_VISIBILITY_HPP
#define FALCON_CPP1X_VISIBILITY_HPP

#include <falcon/c++1x/warning.hpp>

#include <falcon/c++/assignable.hpp>


#define CPP1X_DELETE_COPY_CONSTUCTIBLE(class_name)\
	CPP_DELETE_COPY_CONSTUCTIBLE(class_name)

#define CPP1X_DELETE_ASSIGNABLE(class_name)\
	CPP_DELETE_ASSIGNABLE(class_name)

#define CPP1X_DELETE_SGI_ASSIGNABLE(class_name)\
	CPP_DELETE_SGI_ASSIGNABLE(class_name)


#define CPP1X_DEFAULT_COPY_CONSTUCTIBLE(class_name)\
  class_name(class_name const &) = default

#define CPP1X_DEFAULT_ASSIGNABLE(class_name)\
  class_name& operator=(class_name const &) = default

#define CPP1X_DEFAULT_SGI_ASSIGNABLE(class_name)\
	CPP1X_DEFAULT_COPY_CONSTUCTIBLE(class_name);\
	CPP1X_DEFAULT_ASSIGNABLE(class_name)

#endif
