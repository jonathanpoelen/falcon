#ifndef _FALCON_ITERATOR_INFINITE_ITERATOR_HPP
#define _FALCON_ITERATOR_INFINITE_ITERATOR_HPP

#include <falcon/infinite.hpp>
#include <falcon/container/range_access.hpp>
#include <falcon/iterator/iterator_handler.hpp>

namespace falcon {
namespace iterator {

template <typename _Iterator,
	typename _Category = typename std::iterator_traits<_Iterator>::iterator_category
> class infinite_iterator;

namespace detail {

	template <typename _Iterator, typename _Category>
	struct infinite_base
	{
		typedef typename iterator_handler_types<
			infinite_iterator<_Iterator, _Category>,
			_Iterator,
			_Category
		>::base base;
	};

}

template <typename _Iterator, typename _Category>
struct infinite_iterator
: detail::infinite_base<_Iterator, _Category>::base
{
	friend class iterator_core_access;

	typedef typename detail::infinite_base<_Iterator, _Category>::base __base;

public:
	typedef typename __base::iterator_type iterator_type;
	typedef typename __base::difference_type difference_type;
	typedef typename __base::iterator_category iterator_category;

private:
	iterator_type _first;
	iterator_type _last;

public:
	infinite_iterator()
	: __base()
	, _first()
	, _last()
	{}

	infinite_iterator(iterator_type begin, iterator_type it)
	: __base(it)
	, _first(begin)
	, _last()
	{}

	infinite_iterator(iterator_type begin, iterator_type it, iterator_type end)
	: __base(it)
	, _first(begin)
	, _last(end)
	{}

	template <typename _Container>
	explicit infinite_iterator(_Container& container)
	: __base(falcon::begin(container))
	, _first(this->base_reference())
	, _last(falcon::end(container))
	{}

	template <typename _Container>
	infinite_iterator(_Container& container, iterator_type it)
	: __base(falcon::begin(container))
	, _first(it)
	, _last(falcon::end(container))
	{}

	infinite_iterator(const infinite_iterator& other)
	: __base(other)
	, _first(other._first)
	, _last(other._last)
	{}

	using __base::operator=;

private:
	void increment()
	{
		if (++this->base_reference() == _last)
			this->base_reference() = _first;
	}

	void decrement()
	{
		if (this->base_reference() == _first)
			this->base_reference() = _last;
		--this->base_reference();
	}

	void advance(difference_type n, std::random_access_iterator_tag)
	{ infinite<_Iterator&>(_first, this->base_reference(), _last) += n; }

	void difference(infinite_iterator);

	void advance(difference_type n)
	{ advance(n, iterator_category()); }

	void recoil(difference_type n, std::random_access_iterator_tag)
	{ infinite<_Iterator&>(_first, this->base_reference(), _last) -= n; }

	void recoil(difference_type n)
	{ recoil(n, iterator_category()); }

	bool equal(const infinite_iterator&) const
	{ return false; }

	bool less(const infinite_iterator&) const
	{ return true; }
};

template <typename _Container>
infinite_iterator<typename range_access_iterator<_Container>::type>
make_infinite_iterator(_Container& c)
{ return infinite_iterator<typename range_access_iterator<_Container>::type>(c); }

template <typename _Container, typename _Iterator>
infinite_iterator<_Iterator> make_infinite_iterator(_Container& c, _Iterator it)
{ return infinite_iterator<_Iterator>(c, it); }

template <typename _Iterator>
infinite_iterator<_Iterator> make_infinite_iterator(_Iterator begin, _Iterator it)
{ return infinite_iterator<_Iterator>(begin, it); }

template <typename _Iterator>
infinite_iterator<_Iterator> make_infinite_iterator(_Iterator begin, _Iterator it, _Iterator end)
{ return infinite_iterator<_Iterator>(begin, it, end); }

}}

#endif