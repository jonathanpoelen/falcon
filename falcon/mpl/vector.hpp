#ifndef FALCON_MPL_VECTOR_HPP
#define FALCON_MPL_VECTOR_HPP

#include <falcon/mpl/seq.hpp>

#include <iterator>

namespace falcon {
namespace mpl {

template<typename... Args>
struct vector
{
  typedef vector type;
};

template<typename T>
struct size
{
  static const size_t size = T::size;
};

template<typename Sequence, typename T>
struct push_back
{};

template <typename... Args>
struct iterator_category<vector<Args...>>
{ typedef std::random_access_iterator_tag iterator_tag; };

}
}

#endif

