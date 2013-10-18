#ifndef FALCON_TYPE_TRAITS_ENABLE_IF_TYPE_HPP
#define FALCON_TYPE_TRAITS_ENABLE_IF_TYPE_HPP

namespace falcon {

template<class T, class R = void>
struct enable_if_type
{
  typedef R type;
};

}

#endif

