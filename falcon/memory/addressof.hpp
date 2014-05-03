#ifndef FALCON_MEMORY_ADDRESSOF_HPP
#define FALCON_MEMORY_ADDRESSOF_HPP

#if __cplusplus >= 201103L
# include <memory>
namespace falcon { using std::addressof; }
#else
# include <boost/utility/addressof.hpp>
namespace falcon { using boost::addressof; }
#endif

#endif
