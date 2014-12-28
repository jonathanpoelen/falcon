#ifndef FALCON_CPP1X_ASSIGNABLE_HPP
#define FALCON_CPP1X_ASSIGNABLE_HPP

#include <falcon/c++1x/warning.hpp>

#include <falcon/c++/assignable.hpp>


#define CPP1X_DELETE_COPY_CONSTRUCTOR(class_name)\
	CPP_DELETE_COPY_CONSTRUCTOR(class_name)

#define CPP1X_DELETE_COPY_ASSIGNABLE(class_name)\
	CPP_DELETE_COPY_ASSIGNABLE(class_name)

#define CPP1X_DELETE_SGI_ASSIGNABLE(class_name)\
	CPP_DELETE_SGI_ASSIGNABLE(class_name)


#define CPP1X_DEFAULT_CONSTRUCTOR(class_name)\
  class_name() = default

#define CPP1X_DEFAULT_COPY_CONSTRUCTOR(class_name)\
  class_name(class_name const &) = default

#define CPP1X_DEFAULT_MOVE_CONSTRUCTOR(class_name)\
  class_name(class_name &&) = default

#define CPP1X_DEFAULT_COPY_ASSIGNABLE(class_name)\
  class_name& operator=(class_name const &) = default

#define CPP1X_DEFAULT_MOVE_ASSIGNABLE(class_name)\
  class_name& operator=(class_name &&) = default

#define CPP1X_DEFAULT_SGI_CONSTRUCTOR(class_name)\
  CPP1X_DEFAULT_CONSTRUCTOR(class_name);\
  CPP1X_DEFAULT_COPY_CONSTRUCTOR(class_name);\
  CPP1X_DEFAULT_MOVE_CONSTRUCTOR(class_name)

#define CPP1X_DEFAULT_SGI_ASSIGNABLE(class_name)\
  CPP1X_DEFAULT_COPY_ASSIGNABLE(class_name);\
  CPP1X_DEFAULT_MOVE_ASSIGNABLE(class_name)

#endif
