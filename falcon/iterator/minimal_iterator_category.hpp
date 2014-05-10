#ifndef FALCON_ITERATOR_MINIMAL_ITERATOR_CATEGORY_HPP
#define FALCON_ITERATOR_MINIMAL_ITERATOR_CATEGORY_HPP

#include <iterator>

namespace falcon {
namespace iterator {

template<typename _Category>
struct __rank_category
{ static const int __rank = 0; };

template<>
struct __rank_category<std::output_iterator_tag>
{ static const int __rank = 1; };

template<>
struct __rank_category<std::forward_iterator_tag>
{ static const int __rank = 2; };

template<>
struct __rank_category<std::bidirectional_iterator_tag>
{ static const int __rank = 3; };

template<>
struct __rank_category<std::random_access_iterator_tag>
{ static const int __rank = 4; };

template<int _Rank>
struct __rank_to_category
{ typedef std::input_iterator_tag __type; };

template<>
struct __rank_to_category<1>
{ typedef std::output_iterator_tag __type; };

template<>
struct __rank_to_category<2>
{ typedef std::forward_iterator_tag __type; };

template<>
struct __rank_to_category<3>
{ typedef std::bidirectional_iterator_tag __type; };

template<>
struct __rank_to_category<4>
{ typedef std::random_access_iterator_tag __type; };

template<typename _Category, typename _MinimalCategory>
struct minimal_iterator_category
{
	typedef typename __rank_to_category<(
		(__rank_category<_Category>::__rank
		< __rank_category<_MinimalCategory>::__rank)
		? __rank_category<_Category>::__rank
		: __rank_category<_MinimalCategory>::__rank)
	>::__type type;
};

template<typename Iterator, typename _MinimalCategory>
struct minimal_iterator_category_for
{
  typedef typename minimal_iterator_category<
    typename std::iterator_traits<Iterator>::iterator_category
  , _MinimalCategory
  >::type type;
};

}
}

#endif
