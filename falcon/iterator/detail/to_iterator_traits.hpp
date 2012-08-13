#ifndef _FALCON_ITERATOR_DETAIL_ITERATOR_TRAITS_HPP
#define _FALCON_ITERATOR_DETAIL_ITERATOR_TRAITS_HPP

#include <iterator>
#include <falcon/helper/has_iterator_category.hpp>
#include <falcon/helper/has_pointer.hpp>
#include <falcon/helper/has_reference.hpp>
#include <falcon/helper/has_value_type.hpp>
#include <falcon/sfinae/choose_has_type.hpp>
#include <falcon/type_traits/difference.hpp>

namespace falcon {
namespace iterator {
namespace detail {

template <typename _Iterator>
class to_iterator_category
{
	FALCON_CREATE_CHOOSE_TYPE(choose, typename _Iterator::iterator_category, void);
public:
	typedef typename choose<
		::falcon::helper::has_iterator_category<_Iterator>::value
	>::type type;
};

template <typename _Iterator>
class to_iterator_value
{
	FALCON_CREATE_CHOOSE_TYPE(choose, typename _Iterator::value_type, void);
public:
	typedef typename choose<
		::falcon::helper::has_value_type<_Iterator>::value
	>::type type;
};

template <typename _Iterator>
class to_iterator_pointer
{
	FALCON_CREATE_CHOOSE_TYPE(choose, typename _Iterator::pointer, void);
public:
	typedef typename choose<
		::falcon::helper::has_pointer<_Iterator>::value
	>::type type;
};

template <typename _Iterator>
class to_iterator_reference
{
	FALCON_CREATE_CHOOSE_TYPE(choose, typename _Iterator::reference, void);
public:
	typedef typename choose<
		::falcon::helper::has_reference<_Iterator>::value
	>::type type;
};

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
	typedef typename std::iterator_traits<_T*>::iterator_value type;
};

template <typename _T>
struct to_iterator_difference<_T*>
{
	typedef typename std::iterator_traits<_T*>::iterator_difference type;
};

template <typename _T>
struct to_iterator_pointer<_T*>
{
	typedef typename std::iterator_traits<_T*>::iterator_pointer type;
};

template <typename _T>
struct to_iterator_reference<_T*>
{
	typedef typename std::iterator_traits<_T*>::iterator_reference type;
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
