#ifndef FALCON_ITERATOR_ITERATOR_ITERATOR_HPP
#define FALCON_ITERATOR_ITERATOR_ITERATOR_HPP

#include <vector>
#include <utility>
#include <falcon/iterator/iterator_handler.hpp>
#include <falcon/iterator/minimal_iterator_category.hpp>

namespace falcon {
namespace iterator {

template <typename _Iterator,
	typename _Tp = use_default, typename _Category = use_default,
	typename _Reference = use_default, typename _Distance = use_default,
	typename _Pointer = use_default
>
class iterator_iterator;

namespace detail {

	template <typename _Iterator, typename _Tp,
		typename _Category, typename _Reference, typename _Distance, typename _Pointer>
	struct iterators_base
	{
		typedef iterator_handler_types<void, _Iterator, void,
			_Tp,
			_Distance,
			_Pointer,
			_Reference
		> __handler_types;
		typedef typename iterator_handler_types<
			iterator_iterator<_Iterator,
				_Tp, _Category, _Reference, _Distance, _Pointer>,
			std::vector<std::pair<_Iterator, _Iterator> >,
			typename minimal_iterator_category<
				_Category,
				std::forward_iterator_tag
			>::type,
			typename __handler_types::value_type,
			typename __handler_types::difference_type,
			typename __handler_types::pointer,
			typename __handler_types::reference
		>::base base;
	};

}

template <typename _Iterator,
	typename _Tp,
	typename _Category,
	typename _Reference,
	typename _Distance,
	typename _Pointer
>
class iterator_iterator
: public detail::iterators_base<_Iterator, _Tp, _Category, _Reference, _Distance, _Pointer>::base
{
	friend class iterator_core_access;

	typedef typename detail::iterators_base<_Iterator, _Tp, _Category, _Reference, _Distance, _Pointer>::base __base;

private:
	std::size_t _pos;

public:
	typedef typename __base::iterator_type iterator_type;
	typedef typename __base::difference_type difference_type;
	typedef typename __base::reference reference;

	typedef std::pair<_Iterator, _Iterator> pair_iterator;

public:
	explicit iterator_iterator()
	: __base()
	, _pos(0)
	{}

	explicit iterator_iterator(_Iterator __last)
	: __base()
	, _pos(0)
	{ this->base_reference().push_back(pair_iterator(__last, _Iterator())); }

	explicit iterator_iterator(const std::vector<pair_iterator>& __iterators)
	: __base(__iterators, 1)
	, _pos(0)
	{}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	explicit iterator_iterator(std::initializer_list<pair_iterator> __iterators)
	: __base(std::piecewise_construct, __iterators)
	, _pos(0)
	{}

	explicit iterator_iterator(std::vector<pair_iterator>&& __iterators)
	: __base(std::move(__iterators), 1)
	, _pos(0)
	{}
#endif

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	iterator_iterator& operator=(const std::vector<pair_iterator>& __v)
	{
		this->base_reference() == __v;
		_pos = 0;
	}

	iterator_iterator& operator=(std::vector<pair_iterator>&& __v)
	{
		this->base_reference() == std::move(__v);
		_pos = 0;
	}

	iterator_iterator& operator=(const iterator_iterator&) = default;
#else
	iterator_iterator& operator=(const iterator_iterator& other)
	{
		this->base_reference().assign(&other.base_reference()[oter._pos],
																	&other.base_reference()[oter._M_count()]);
		_pos = 0;
		return *this;
	}
#endif

	bool valid() const
	{ return _pos < _M_count() && _M_first() != _M_second(); }

	const iterator_type& base() const
	{ return this->base_reference(); }

protected:
	pair_iterator& _M_current()
	{ return this->base_reference()[_pos]; }

	const pair_iterator& _M_current() const
	{ return this->base_reference()[_pos]; }

	_Iterator& _M_first()
	{ return this->base_reference()[_pos].first; }

	const _Iterator& _M_first() const
	{ return this->base_reference()[_pos].first; }

	_Iterator& _M_second()
	{ return this->base_reference()[_pos].second; }

	const _Iterator& _M_second() const
	{ return this->base_reference()[_pos].second; }

	std::size_t _M_count() const
	{ return this->base_reference().size(); }

protected:
	reference dereference() const
	{ return *_M_first(); }

	reference dereference()
	{ return *_M_first(); }

	bool equal(const iterator_iterator& x) const
	{ return _M_first() == x._M_first(); }

	bool less(const iterator_iterator& x) const
	{ return _M_first() < x._M_first(); }

	void increment()
	{
		++_M_first();
		while (_M_first() == _M_second() && _pos+1 < _M_count())
			++_pos;
	}

	void advance(difference_type n)
	{
		difference_type d = _M_second() - _M_first();
		for (;;){
			if (d > n){
				if (_pos+1 < _M_count()){
					++_pos;
					n -= d;
					d = _M_second() - _M_first();
					continue;
				}
				break;
			}
			_M_first() += n;
			break;
		}
	}

	iterator_iterator next(difference_type n) const
	{
		const pair_iterator * p = &_M_current();
		const pair_iterator * last = &this->base_reference()[_M_count()];
		difference_type d = p->second - p->first;
		std::size_t pos = _pos;
		while (d > n && ++p != last)
		{
			n -= d;
			d = p->second - p->first;
		}
		iterator_iterator ret(p, last);
		if (p != last)
			ret._M_first() += n;
		return ret;
	}
};

}
}

#endif