#ifndef _FALCON_ITERATOR_NEXTER_ITERATOR_HPP
#define _FALCON_ITERATOR_NEXTER_ITERATOR_HPP

#include <falcon/type_traits/is_same.hpp>
#include <falcon/iterator/iterator_handler.hpp>

namespace falcon {
namespace iterator {

template <typename _Iterator, typename _Nexter>
class nexter_iterator;

namespace detail
{
	template <typename _Iterator, typename _Nexter>
	struct nexter_base
	{
		typedef typename std::iterator_traits<_Iterator>::iterator_category iterator_category;

		typedef typename iterator_handler_types<
			nexter_iterator<_Iterator, _Nexter>,
			_Iterator,
			typename if_<
				(is_same<iterator_category, std::bidirectional_iterator_tag>::value
				|| is_same<iterator_category, std::random_access_iterator_tag>::value),
				std::forward_iterator_tag,
				iterator_category
			>::type
		>::base base;
	};
}

template <typename _Iterator, typename _Nexter>
class nexter_iterator
: public detail::nexter_base<_Iterator, _Nexter>::base
{
	friend iterator_core_access;

	typedef typename detail::nexter_base<_Iterator, _Nexter>::base __base;

public:
	typedef _Nexter nexter_type;
	typedef typename __base::iterator_type iterator_type;
	typedef typename __base::difference_type difference_type;

private:
	nexter_type _nexter;

public:
	explicit nexter_iterator(nexter_type fn)
	: __base()
	, _nexter(fn)
	{}

	explicit nexter_iterator(const iterator_type& x)
	: __base(x)
	, _nexter()
	{}

	nexter_iterator(const iterator_type& x, nexter_type fn)
	: __base(x)
	, _nexter(fn)
	{}

	nexter_iterator(const nexter_iterator& other)
	: __base(other)
	, _nexter(other._nexter)
	{}

	using __base::operator=;

	const nexter_type& nexter() const
	{ return _nexter; }
	nexter_type& nexter()
	{ return _nexter; }

private:
	void increment()
	{ _nexter(this->base_reference()); }

	void advance(difference_type n)
	{ _nexter(this->base_reference(), n); }
};

template <typename _Iterator, typename _Nexter>
nexter_iterator<_Iterator, _Nexter> make_nexter_iterator(_Iterator x, const _Nexter& fn)
{ return nexter_iterator<_Iterator, _Nexter>(x, fn); }

}}

#endif