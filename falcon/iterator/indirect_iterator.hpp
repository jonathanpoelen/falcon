#ifndef _FALCON_ITERATOR_INDIRECT_ITERATOR_HPP
#define _FALCON_ITERATOR_INDIRECT_ITERATOR_HPP

#ifndef __GXX_EXPERIMENTAL_CXX0X__
# include <boost/type_traits/remove_pointer.hpp>
#endif
#include <falcon/iterator/proxy_iterator.hpp>

namespace falcon {
namespace iterator {

template <typename _T, typename _IndirectT>
struct __proxy_indirect_iterator
{
	typedef _IndirectT result_type;

	result_type operator()(_T& x) const
	{ return *x; }
};

#ifdef __GXX_EXPERIMENTAL_CXX0X__

template <
	typename _Iterator,
	typename _IndirectT = decltype(**std::declval<_Iterator&>())
>
using indirect_iterator = proxy_iterator<
	_Iterator,
	__proxy_indirect_iterator<
		typename std::iterator_traits<_Iterator>::value_type,
		_IndirectT
	>
>;

#else

template <
	typename _Iterator,
	typename _IndirectT = typename boost::remove_pointer<
		typename std::iterator_traits<_Iterator>::value_type
	>::type&
>
class indirect_iterator
: public proxy_iterator<
	_Iterator,
	__proxy_indirect_iterator<
		typename std::iterator_traits<_Iterator>::value_type,
		_IndirectT
	>
>
{
	typedef proxy_iterator<
		_Iterator,
		__proxy_indirect_iterator<
			typename std::iterator_traits<_Iterator>::value_type,
			_IndirectT
		>
	> __base;

public:
	explicit indirect_iterator(const _Iterator& __x)
	: __base(__x)
	{}

	indirect_iterator(const indirect_iterator& other)
	: __base(other)
	{}

	using __base::operator=;
};

#endif


template <typename _Iterator>
indirect_iterator<_Iterator> make_indirect_iterator(_Iterator x)
{ return indirect_iterator<_Iterator>(x); }

}}

#endif