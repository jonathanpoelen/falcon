#ifndef FALCON_ITERATOR_MINIMAL_ITERATOR_CATEGORY_HPP
#define FALCON_ITERATOR_MINIMAL_ITERATOR_CATEGORY_HPP

#include <iterator>

namespace falcon {
namespace iterator {

namespace _aux {
  template<class Category>
  struct rank_category
  { static const int rank = 0; };

  template<>
  struct rank_category<std::output_iterator_tag>
  { static const int rank = 1; };

  template<>
  struct rank_category<std::forward_iterator_tag>
  { static const int rank = 2; };

  template<>
  struct rank_category<std::bidirectional_iterator_tag>
  { static const int rank = 3; };

  template<>
  struct rank_category<std::random_access_iterator_tag>
  { static const int rank = 4; };

  template<int _Rank>
  struct rank_to_category
  { typedef std::input_iterator_tag type; };

  template<>
  struct rank_to_category<1>
  { typedef std::output_iterator_tag type; };

  template<>
  struct rank_to_category<2>
  { typedef std::forward_iterator_tag type; };

  template<>
  struct rank_to_category<3>
  { typedef std::bidirectional_iterator_tag type; };

  template<>
  struct rank_to_category<4>
  { typedef std::random_access_iterator_tag type; };
}

template<class Category, class MinimalCategory>
struct minimal_iterator_category
{
  typedef typename _aux::rank_to_category<(
		( _aux::rank_category<Category>::rank
		< _aux::rank_category<MinimalCategory>::rank)
		? _aux::rank_category<Category>::rank
		: _aux::rank_category<MinimalCategory>::rank)
	>::type type;
};

template<class Iterator, class MinimalCategory>
struct minimal_iterator_category_for
{
  typedef typename minimal_iterator_category<
    typename std::iterator_traits<Iterator>::iterator_category
  , MinimalCategory
  >::type type;
};

}
}

#endif
