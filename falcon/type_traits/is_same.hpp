#ifndef FALCON_TYPE_TRAITS_IS_SAME_HPP
#define FALCON_TYPE_TRAITS_IS_SAME_HPP

#if __cplusplus >= 201103L
# include <type_traits>
namespace falcon { using std::is_same; }
#else
# include <boost/type_traits/is_same.hpp>
namespace falcon { using boost::is_same; }
#endif

#endif
