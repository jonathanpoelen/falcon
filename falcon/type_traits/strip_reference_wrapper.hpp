#ifndef FALCON_TYPE_TRAITS_STRIP_REFERENCE_WRAPPER_HPP
#define FALCON_TYPE_TRAITS_STRIP_REFERENCE_WRAPPER_HPP

namespace std { template<class> class reference_wrapper; }
namespace boost { template<class> class reference_wrapper; }

namespace falcon {

// Helper which adds a reference to a type when given a reference_wrapper
template<class T>
struct strip_reference_wrapper
{
  typedef T type;
};

#if __cplusplus >= 201103L
template<class T>
struct strip_reference_wrapper<std::reference_wrapper<T> >
{
  typedef T& type;
};

template<class T>
struct strip_reference_wrapper<const std::reference_wrapper<T> >
{
  typedef T& type;
};
#endif

template<class T>
struct strip_reference_wrapper<boost::reference_wrapper<T> >
{
  typedef T& type;
};

template<class T>
struct strip_reference_wrapper<const boost::reference_wrapper<T> >
{
  typedef T& type;
};

}

#endif
