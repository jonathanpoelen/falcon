#ifndef _FALCON_ITERATOR_NEXTER_ITERATOR_HPP
#define _FALCON_ITERATOR_NEXTER_ITERATOR_HPP

#include <falcon/iterator/iterator_handler.hpp>
#include <falcon/iterator/minimal_iterator_category.hpp>

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
			typename minimal_iterator_category<
				iterator_category,
				std::forward_iterator_tag
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
#ifdef __GXX_EXPERIMENTAL_CXX0X__
	nexter_iterator& operator=(const nexter_iterator&) = default;
#else
	nexter_iterator& operator=(const nexter_iterator& other)
	{
		this->base_reference() = other.base_reference();
		_nexter = other._nexter;
		return *this;
	}
#endif

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