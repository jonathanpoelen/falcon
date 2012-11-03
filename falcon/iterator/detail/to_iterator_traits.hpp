#ifndef _FALCON_ITERATOR_DETAIL_ITERATOR_TRAITS_HPP
#define _FALCON_ITERATOR_DETAIL_ITERATOR_TRAITS_HPP

#include <iterator>
#include <falcon/type_traits/difference.hpp>
#include <falcon/type_traits/use_if.hpp>

namespace falcon {
namespace iterator {
namespace detail {

template <typename _Iterator>
struct to_iterator_category
: use_if<use_iterator_category<_Iterator>, void>
{};

template <typename _Iterator>
struct to_iterator_value
: use_if<use_value_type<_Iterator>, void>
{};

template <typename _Iterator>
struct to_iterator_pointer
: use_if<use_pointer<_Iterator>, void>
{};

template <typename _Iterator>
struct to_iterator_reference
: use_if<use_reference<_Iterator>, void>
{};

template <typename _Iterator>
struct to_iterator_difference
{
	typedef typename ::falcon::difference<_Iterator>::type type;
};

template <typename _T>
struct to_iterator_category<_T*>
{
	typedef typename std::iterator_traits<_T*>::iterator_category type;
};

template <typename _T>
struct to_iterator_value<_T*>
{
	typedef typename std::iterator_traits<_T*>::value_type type;
};

template <typename _T>
struct to_iterator_difference<_T*>
{
	typedef typename std::iterator_traits<_T*>::difference_type type;
};

template <typename _T>
struct to_iterator_pointer<_T*>
{
	typedef typename std::iterator_traits<_T*>::pointer type;
};

template <typename _T>
struct to_iterator_reference<_T*>
{
	typedef typename std::iterator_traits<_T*>::reference type;
};

template <typename _Iterator>
struct to_iterator_traits
{
	typedef std::iterator<
		typename to_iterator_category<_Iterator>::type,
		typename to_iterator_value<_Iterator>::type,
		typename to_iterator_difference<_Iterator>::type,
		typename to_iterator_pointer<_Iterator>::type,
		typename to_iterator_reference<_Iterator>::type
	> type;
};

template <typename _T>
struct to_iterator_traits<_T*>
{
	typedef typename std::iterator_traits<_T*> type;
};

}
}
}

#endif
