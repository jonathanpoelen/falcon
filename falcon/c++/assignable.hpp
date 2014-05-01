#ifndef FALCON_CPP_VISIBILITY_HPP
#define FALCON_CPP_VISIBILITY_HPP

#include <falcon/config.hpp>

#if __cplusplus >= 201103L

#define CPP_DELETE_COPY_CONSTUCTIBLE(class_name) \
  class_name(const class_name&) = delete
#define CPP_DELETE_ASSIGNABLE(class_name) \
  class_name& operator=(const class_name&) = delete

#else

#define CPP_DELETE_COPY_CONSTUCTIBLE(class_name) \
  private: class_name(const class_name&);
#define CPP_DELETE_ASSIGNABLE(class_name) \
  private: class_name& operator=(const class_name&);

#endif

#define CPP_DELETE_SGI_ASSIGNABLE(class_name)\
	CPP_DELETE_COPY_CONSTUCTIBLE(class_name);\
	CPP_DELETE_ASSIGNABLE(class_name)

#endif
