#ifndef _FALCON_ITERATOR_RECURSIVE_ITERATOR_HPP
#define _FALCON_ITERATOR_RECURSIVE_ITERATOR_HPP

#include <falcon/container/range_access_traits.hpp>
#include <falcon/iterator/iterator_handler.hpp>
#include <falcon/parameter/pack_element.hpp>
#include <falcon/parameter/manip.hpp>
#include <falcon/tuple/parameter_pack.hpp>
#include <falcon/parameter/parameter_index.hpp>
#include <falcon/arg/arg_range.hpp>
#include <falcon/type_traits/if.hpp>
#include <falcon/type_traits/use.hpp>
#include <falcon/arg/arg.hpp>

namespace falcon {
namespace iterator {

template <typename... _Iterators>
class recursive_iterator;

template<typename _Iterator, typename _AccessTrait = range_access_traits<typename std::iterator_traits<_Iterator>::value_type>>
struct recursive_iterator_access_adapter
{
	typedef _Iterator iterator;
	typedef std::pair<_Iterator, _Iterator> type;
	typedef _AccessTrait access_traits;
};

template<typename _Iterator>
struct iterator_to_recursive_iterator_access_adapter
{ typedef recursive_iterator_access_adapter<_Iterator> type; };

template<typename _Iterator, typename _AccessTrait>
struct iterator_to_recursive_iterator_access_adapter
<recursive_iterator_access_adapter<_Iterator, _AccessTrait>>
{ typedef recursive_iterator_access_adapter<_Iterator, _AccessTrait> type; };

namespace detail {

	template <typename... _Iterators>
	struct recursive_iterator_base
	{
		typedef typename parameter::pack_modifier<
			iterator_to_recursive_iterator_access_adapter,
			typename parameter::pack_element<
				parameter_pack<_Iterators...>,
				typename build_parameter_index<sizeof...(_Iterators) - 1>::type
			>::type
		>::type __parameter_adapter;

		typedef typename arg_element<
			sizeof...(_Iterators) - 1,
			_Iterators...
		>::type __last_iterator;
		typedef typename std::pair<__last_iterator, __last_iterator> __last_type;

		typedef typename parameter_pack_to_tuple<
			typename parameter::pack_add_right<
				typename parameter::pack_use_type<__parameter_adapter>::type,
				__last_type
			>::type
		>::type __tuple;

		typedef typename std::iterator_traits<__last_iterator> __traits;

		typedef typename iterator_handler_types<
			recursive_iterator<_Iterators...>,
			__tuple,
			std::forward_iterator_tag,
			typename __traits::value_type,
			typename __traits::difference_type,
			typename __traits::pointer,
			typename __traits::reference
		>::base base;
	};

}

template<typename _Tuple, typename _ParameterAdapter, std::size_t _Idx>
struct __recursive_iterator_move
{
	typedef typename parameter_element<_Idx-1, _ParameterAdapter>::type::access_traits __access;
	static void __inc(_Tuple& t)
	{
		if (++std::get<_Idx>(t).first == std::get<_Idx>(t).second)
		{
			__recursive_iterator_move<_Tuple, _ParameterAdapter, _Idx - 1>::__inc(t);
			std::get<_Idx>(t).first = __access::begin(*std::get<_Idx-1>(t).first);
			std::get<_Idx>(t).second = __access::end(*std::get<_Idx-1>(t).second);
		}
	}
};

template<typename _Tuple, typename _ParameterAdapter>
struct __recursive_iterator_move<_Tuple, _ParameterAdapter, 0>
{
	static void __inc(_Tuple& t)
	{ ++std::get<0>(t).first; }
};


template <typename... _Iterator>
class recursive_iterator
: public detail::recursive_iterator_base<_Iterator...>::base
{
	friend class iterator_core_access;

	typedef detail::recursive_iterator_base<_Iterator...> __detail;
	typedef typename __detail::__last_type __last_type;
	typedef typename __detail::__last_iterator __last_iterator;
	typedef typename __detail::__parameter_adapter __parameter_adapter;

	typedef typename __detail::base __base;

public:
	typedef typename __base::iterator_type iterator_type;
	typedef typename __base::difference_type difference_type;
	typedef typename __base::reference reference;

public:
	recursive_iterator()
	: __base()
	{}

	explicit recursive_iterator(iterator_type __x)
	: __base(__x)
	{}

	recursive_iterator(const recursive_iterator& __x)
	: __base(__x)
	{}

	using __base::operator=;

private:
	static const std::size_t __last_idx = sizeof...(_Iterator) - 1;

	const __last_type& get_last() const
	{ return std::get<__last_idx>(this->base_reference()); }

	const __last_iterator& get_last_iterator() const
	{ return get_last().first; }

	reference dereference() const
	{ return *get_last_iterator(); }

	void increment()
	{
		__recursive_iterator_move<iterator_type, __parameter_adapter, __last_idx>
		::__inc(this->base_reference());
	}

	bool equal(const recursive_iterator& x) const
	{ return get_last_iterator() == x.get_last_iterator(); }

	bool less(const recursive_iterator& x) const
	{ return get_last_iterator() < x.get_last_iterator(); }
};




}
}


#if 0

#include <iterator>
#include <falcon/c++0x/syntax.hpp>
#include <falcon/type_traits/dimension.hpp>
#include <falcon/parameter/parameter_pack.hpp>
#include <falcon/iterator/subrange_access_iterator.hpp>
#include <falcon/iterator/detail/to_iterator_traits.hpp>

///TODO mettre les tags (iterator_tag) et les type de iterator_traits

namespace falcon {
namespace iterator {

template<bool _Protect, std::size_t _N, std::size_t _Dimension, typename... _Iterators>
struct __recursive_iterator;

template<bool _Protect, std::size_t _N, std::size_t _Dimension, typename _Iterator, typename... _Iterators>
class __recursive_iterator<_Protect, _N, _Dimension, _Iterator, _Iterators...>
{
	typedef __recursive_iterator<_Protect, _N, _Dimension, _Iterator, _Iterators...> self_type;
	typedef __recursive_iterator<_Protect, _N-1, _Dimension, _Iterators...> parent_recursive_iterator;
	typedef typename detail::to_iterator_traits<_Iterator>::type iterator_traits;

public:
	typedef _Iterator iterator;
	typedef typename parent_recursive_iterator::compare_iterator_type compare_iterator_type;
	typedef typename iterator_traits::value_type value_type;
	typedef typename iterator_traits::reference reference;
	typedef const reference const_reference;
	typedef typename iterator_traits::pointer pointer;
	typedef const value_type* const_pointer;
	typedef std::size_t size_type;
	typedef void difference_type;
	typedef void iterator_category;

private:
	parent_recursive_iterator _parent;
	_Iterator _first;
	_Iterator _last;

public:
	template<typename _IteratorParent>
	__recursive_iterator(_IteratorParent first, _IteratorParent last)
	: _parent(first, last)
	, _first(_parent.begin())
	, _last(_parent.end())
	{}

	template<typename _Container>
	__recursive_iterator(_Container& container)
	: _parent(falcon::begin(container), falcon::end(container))
	, _first(_parent.begin())
	, _last(_parent.end())
	{}

	__recursive_iterator(const self_type& other)
	: _parent(other._parent)
	, _first(other._first)
	, _last(other._last)
	{}

	self_type& operator=(const self_type& other)
	{
		_parent = other._parent;
		_first = other._first;
		_last = other._last;
		return *this;
	}

	self_type& operator++()
	{
		if (++_first == _last)
		{
			++_parent;
			_first = _parent.begin();
			_last = _parent.end();
		}
		return *this;
	}

	self_type& operator--()
	{
		if (_first == _last)
		{
			--_parent;
			_first = _parent.end();
			_last = _parent.begin();
			--_first;
		}
		else
			--_first;
		return *this;
	}

	self_type& operator+=(size_type n)
	{
		size_type distance = _first - _last;
		while (n > distance)
		{
			n -= distance;
			++_parent;
			_first = _parent.begin();
			_last = _parent.end();
			distance = _first - _last;
		}
		_first += distance;
		return *this;
	}

	reference operator*()
	{ return *_first; }
	reference operator->()
	{ return *_first; }

	const_reference operator*() const
	{ return *_first; }
	const_reference operator->() const
	{ return *_first; }

	bool operator==(const compare_iterator_type& it) const
	{ return _parent == it; }

	bool operator!=(const compare_iterator_type& it) const
	{ return _parent != it; }

	typedef typename parent_recursive_iterator::iterator child_iterator;

	child_iterator begin() const
	{ return _Protect && _first == _last ? child_iterator() : falcon::begin(*_first); }

	child_iterator end() const
	{ return _Protect && _first == _last ? child_iterator() : end(*_first); }

	void begin(const _Iterator& first)
	{ _first = first; }

	template<typename _IteratorParent>
	void begin(const _IteratorParent& first)
	{ _parent.begin(first); }

	child_iterator end()
	{ return _Protect && _first == _last ? child_iterator() : falcon::end(*_first); }

	void end(const _Iterator& last)
	{ _last = last; }

	template<typename _IteratorParent>
	void end(const _IteratorParent& last)
	{ _parent.end(last); }
};

template<bool _Protect, std::size_t _Dimension, typename _Iterator>
class __recursive_iterator<_Protect, 1, _Dimension, _Iterator>
{
	typedef __recursive_iterator<_Protect, 1, _Dimension, _Iterator> self_type;
	typedef typename detail::to_iterator_traits<_Iterator>::type iterator_traits;

public:
	typedef typename subrange_access_iterator<_Iterator>::type iterator;
	typedef _Iterator compare_iterator_type;
	typedef typename iterator_traits::value_type value_type;
	typedef typename iterator_traits::reference reference;
	typedef const reference const_reference;
	typedef typename iterator_traits::pointer pointer;
	typedef const value_type* const_pointer;
	typedef std::size_t size_type;
	typedef void difference_type;
	typedef void iterator_category;

private:
	_Iterator _first;
	_Iterator _last;

public:
	template<typename _IteratorParent>
	__recursive_iterator(_IteratorParent first, _IteratorParent last)
	: _first(first)
	, _last(last)
	{}

	template<typename _Container>
	__recursive_iterator(_Container& container)
	: _first(falcon::begin(container))
	, _last(falcon::end(container))
	{}

	__recursive_iterator(const self_type& other)
	: _first(other._first)
	, _last(other._last)
	{}

	self_type& operator=(const self_type& other)
	{
		_first = other._first;
		_last = other._last;
		return *this;
	}

	self_type& operator++()
	{
		++_first;
		return *this;
	}

	self_type& operator--()
	{
		--_first;
		return *this;
	}

	self_type& operator+=(size_type n)
	{
		_first += n;
		return *this;
	}

	reference operator*()
	{ return *_first; }
	reference operator->()
	{ return *_first; }

	const_reference operator*() const
	{ return *_first; }
	const_reference operator->() const
	{ return *_first; }

	bool operator==(const compare_iterator_type& it) const
	{ return _first == it; }

	bool operator!=(const compare_iterator_type& it) const
	{ return !(*this == it); }

	iterator begin() const
	{ return _Protect && _first == _last ? iterator() : falcon::begin(*_first); }

	iterator end() const
	{ return _Protect && _first == _last ? iterator() : falcon::end(*_first); }

	void begin(const _Iterator& first)
	{ _first = first; }

	void end(const _Iterator& last)
	{ _last = last; }
};

template<bool _Protect, std::size_t _Dimension, typename _Iterator>
class __recursive_iterator_info
{
	template<std::size_t _N, typename _Pack>
	struct __recursive_iterator_info_impl;

	template<std::size_t _N, typename _T, typename... _Elements>
	struct __recursive_iterator_info_impl<_N, parameter_pack<_T, _Elements...> >
	{
		typedef typename __recursive_iterator_info_impl<_N-1, parameter_pack<typename subrange_access_iterator<_T>::type, _T, _Elements...> >::type type;
	};

	template<typename _T, typename... _Elements>
	struct __recursive_iterator_info_impl<0, parameter_pack<_T, _Elements...> >
	{
		typedef __recursive_iterator<_Protect, _Dimension, _Dimension, _T, _Elements...> type;
	};

public:
	typedef typename __recursive_iterator_info_impl<_Dimension-1, parameter_pack<_Iterator> >::type type;
};

/**
 * \brief create begin recursive iterator. End iterator is end first iterator. Use safe_recursive_iterator if iterator can be empty.
 * @{
 */
template<std::size_t _Dimension, typename _Container>
typename __recursive_iterator_info<false, _Dimension, typename range_access_iterator<_Container>::type>::type
recursive_iterator(_Container& container)
{
	return typename __recursive_iterator_info<false, _Dimension, typename range_access_iterator<_Container>::type>::type(container);
}

template<typename _Container>
typename __recursive_iterator_info<false, dimension<_Container>::value, typename range_access_iterator<_Container>::type>::type
recursive_iterator(_Container& container)
{
	return typename __recursive_iterator_info<false, dimension<_Container>::value, typename range_access_iterator<_Container>::type>::type(container);
}

template<std::size_t _Dimension, typename _Container>
typename __recursive_iterator_info<true, _Dimension, typename range_access_iterator<_Container>::type>::type
safe_recursive_iterator(_Container& container)
{
	return typename __recursive_iterator_info<true, _Dimension, typename range_access_iterator<_Container>::type>::type(container);
}

template<typename _Container>
typename __recursive_iterator_info<true, dimension<_Container>::value, typename range_access_iterator<_Container>::type>::type
safe_recursive_iterator(_Container& container)
{
	return typename __recursive_iterator_info<true, dimension<_Container>::value, typename range_access_iterator<_Container>::type>::type(container);
}

template<std::size_t _Dimension, typename _Iterator>
typename __recursive_iterator_info<false, _Dimension, _Iterator>::type
recursive_iterator(_Iterator first, _Iterator last)
{
	return typename __recursive_iterator_info<false, _Dimension, _Iterator>::type(first, last);
}

template<typename _Iterator>
typename __recursive_iterator_info<false, dimension<_Iterator>::value, _Iterator>::type
recursive_iterator(_Iterator first, _Iterator last)
{
	return typename __recursive_iterator_info<false, dimension<_Iterator>::value, _Iterator>::type(first, last);
}

template<std::size_t _Dimension, typename _Iterator>
typename __recursive_iterator_info<true, _Dimension, _Iterator>::type
safe_recursive_iterator(_Iterator first, _Iterator last)
{
	return typename __recursive_iterator_info<true, _Dimension, _Iterator>::type(first, last);
}

template<typename _Iterator>
typename __recursive_iterator_info<true, dimension<_Iterator>::value, _Iterator>::type
safe_recursive_iterator(_Iterator first, _Iterator last)
{
	return typename __recursive_iterator_info<true, dimension<_Iterator>::value, _Iterator>::type(first, last);
}
//@}

}
}

#endif

#endif