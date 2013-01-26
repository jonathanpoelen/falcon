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
#ifdef __GXX_EXPERIMENTAL_CXX0X__
	infinite_iterator& operator=(const infinite_iterator&) = default;
#else
	infinite_iterator& operator=(const infinite_iterator& other)
	{
		this->base_reference() = other.base_reference();
		_first = other._first;
		_last = other._last;
		return *this;
	}
#endif

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

	void difference(infinite_iterator);

	void advance(difference_type n)
	{
		if (n < 0)
			recoil(-n);
		difference_type diff = _last - this->base_reference();
		if (diff < n)
			this->base_reference() = _first + (n - diff) % (_last - _first);
		else
			this->base_reference() += n;
	}

	void recoil(difference_type n)
	{
		if (n < 0)
			advance(-n);
		difference_type diff = this->base_reference() - _first;
		if (diff < n)
			this->base_reference() = _last - (n - diff) % (_last - _first);
		else
			this->base_reference() -= n;
	}

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