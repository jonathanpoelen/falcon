#ifndef ITERATOR_DETAIL_HANDLER_ITERATOR_HPP
#define ITERATOR_DETAIL_HANDLER_ITERATOR_HPP

#include <iterator>
#ifdef __GXX_EXPERIMENTAL_CXX0X__
# include <utility>
#endif
#include <falcon/type_traits/use_default.hpp>
#include <falcon/type_traits/use_type.hpp>
#include <falcon/type_traits/is_same.hpp>

namespace falcon {
namespace iterator {
namespace detail {

template<
	typename _Iterator,
	typename _IteratorBase,
	typename _Traits,
	typename _Base = std::iterator_traits<_IteratorBase>
>
class handler_iterator
: public _Base
{
public:
	_IteratorBase _M_current;

public:
	typedef _IteratorBase iterator_type;
	typedef typename _Base::difference_type difference_type;
	typedef typename _Base::pointer pointer;
	typedef typename _Base::reference reference;


public:
	handler_iterator()
	: _M_current()
	{}

	explicit handler_iterator(iterator_type __x)
	: _M_current(__x)
	{}

	explicit handler_iterator(const iterator_type& __x, int)
	: _M_current(__x)
	{}

	handler_iterator(const handler_iterator& other)
	: _M_current(other._M_current)
	{}

	template<typename _Iterator2, typename _Base2, typename _Traits2>
	handler_iterator(const handler_iterator<_Iterator2, _Base2, _Traits2>& other)
	: _M_current(other.base())
	{}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	explicit handler_iterator(iterator_type&& __x)
	: _M_current(std::forward<iterator_type>(__x))
	{}

	template<typename _U, class _Enable = typename
	std::enable_if<!std::is_reference<iterator_type>::value && std::is_convertible<_U, iterator_type>::value>::type>
	explicit handler_iterator(_U&& __x)
	: _M_current(std::forward<_U>(__x))
	{}
#endif

	handler_iterator& operator=(iterator_type __x)
	{
		_M_current = __x;
		return *this;
	}

	iterator_type base() const
	{ return _M_current; }

	reference operator*()
	{ return _Traits::dereference(downcast()); }

	reference operator*() const
	{ return _Traits::dereference(downcast()); }

	pointer operator->()
	{ return &(operator*()); }

	pointer operator->() const
	{ return &(operator*()); }

	_Iterator& operator++()
	{
		_Traits::next(downcast());
		return downcast();
	}

	_Iterator operator++(int)
	{
		_Iterator tmp = downcast();
		operator++();
		return tmp;
	}

	_Iterator& operator--()
	{
		_Traits::prev(downcast());
		return downcast();
	}

	_Iterator operator--(int)
	{
		_Iterator tmp = downcast();
		operator--();
		return tmp;
	}

	_Iterator& downcast()
	{ return static_cast<_Iterator&>(*this); }

	const _Iterator& downcast() const
	{ return static_cast<const _Iterator&>(*this); }

	reference operator[](difference_type n)
	{ return *(*this += n); }
};


template <typename _Iterator, typename _IteratorBase, typename _Traits, typename _Base>
bool operator==(const handler_iterator<_Iterator, _IteratorBase, _Traits, _Base>& a,
				const handler_iterator<_Iterator, _IteratorBase, _Traits, _Base>& b)
{ return _Traits::eq(a.downcast(), b.downcast()); }

template <typename _Iterator, typename _IteratorBase, typename _Traits, typename _Base>
bool operator<(const handler_iterator<_Iterator, _IteratorBase, _Traits, _Base>& a,
			   const handler_iterator<_Iterator, _IteratorBase, _Traits, _Base>& b)
{ return _Traits::lt(a.downcast(), b.downcast()); }

template <typename _Iterator, typename _IteratorBase, typename _Traits, typename _Base>
bool operator!=(const handler_iterator<_Iterator, _IteratorBase, _Traits, _Base>& a,
				const handler_iterator<_Iterator, _IteratorBase, _Traits, _Base>& b)
{ return !(a==b); }

template <typename _Iterator, typename _IteratorBase, typename _Traits, typename _Base>
bool operator<=(const handler_iterator<_Iterator, _IteratorBase, _Traits, _Base>& a,
				const handler_iterator<_Iterator, _IteratorBase, _Traits, _Base>& b)
{ return !(b<a); }

template <typename _Iterator, typename _IteratorBase, typename _Traits, typename _Base>
bool operator>(const handler_iterator<_Iterator, _IteratorBase, _Traits, _Base>& a,
			   const handler_iterator<_Iterator, _IteratorBase, _Traits, _Base>& b)
{ return (b<a); }

template <typename _Iterator, typename _IteratorBase, typename _Traits, typename _Base>
bool operator>=(const handler_iterator<_Iterator, _IteratorBase, _Traits, _Base>& a,
				const handler_iterator<_Iterator, _IteratorBase, _Traits, _Base>& b)
{ return !(a<b); }


template <typename _Iterator, typename _IteratorBase, typename _Traits, typename _Base>
_Iterator&
operator+=(handler_iterator<_Iterator, _IteratorBase, _Traits, _Base>& a, int n)
{
	_Traits::next(a.downcast(), n);
	return a.downcast();
}

template <typename _Iterator, typename _IteratorBase, typename _Traits, typename _Base>
_Iterator&
operator-=(handler_iterator<_Iterator, _IteratorBase, _Traits, _Base>& a, int n)
{
	_Traits::prev(a.downcast(), n);
	return a.downcast();
}

template <typename _Iterator, typename _IteratorBase, typename _Traits, typename _Base>
_Iterator
operator+(const handler_iterator<_Iterator, _IteratorBase, _Traits, _Base>& a, int n)
{ return _Traits::next(a.downcast(), n, 1); }

template <typename _Iterator, typename _IteratorBase, typename _Traits, typename _Base>
_Iterator
operator-(const handler_iterator<_Iterator, _IteratorBase, _Traits, _Base>& a, int n)
{ return _Traits::prev(a.downcast(), n, 1); }

template <typename _Iterator, typename _IteratorBase, typename _Traits, typename _Base>
typename _Traits::difference_type
operator-(const handler_iterator<_Iterator, _IteratorBase, _Traits, _Base>& a,
		  const handler_iterator<_Iterator, _IteratorBase, _Traits, _Base>& b)
{ return _Traits::diff(a.downcast(), b.downcast()); }


template<typename _Iterator, typename _Tag = typename std::iterator_traits<_Iterator>::iterator_category>
class handler_iterator_traits;

template<typename _Iterator>
struct handler_iterator_traits<_Iterator, std::output_iterator_tag>
{
	typedef typename std::iterator_traits<_Iterator> __traits;

public:
	typedef typename __traits::iterator_category iterator_category;
	typedef void value_type;
	typedef void difference_type;
	typedef void pointer;
	typedef void reference;

	static void next(const _Iterator&)
	{}
};

template<typename _Iterator>
struct handler_iterator_traits<_Iterator, std::input_iterator_tag>
{
	typedef typename std::iterator_traits<_Iterator> __traits;

public:
	typedef typename __traits::iterator_category iterator_category;
	typedef typename __traits::value_type value_type;
	typedef typename __traits::difference_type difference_type;
	typedef typename __traits::pointer pointer;
	typedef typename __traits::reference reference;

	static reference dereference(const _Iterator& it)
	{ return *it._M_current; }
};

template<typename _Iterator>
struct handler_iterator_traits<_Iterator, std::forward_iterator_tag>
: handler_iterator_traits<_Iterator, std::input_iterator_tag>
{
	static void next(_Iterator& it)
	{ ++it._M_current; }

	static bool eq(const _Iterator& a, const _Iterator& b)
	{ return a._M_current == b._M_current; }

	static bool lt(const _Iterator& a, const _Iterator& b)
	{ return a._M_current < b._M_current; }

	static typename std::iterator_traits<_Iterator>::difference_type
	diff(const _Iterator& a, const _Iterator& b)
	{ return a._M_current - b._M_current; }
};

template<typename _Iterator>
struct handler_iterator_traits<_Iterator, std::bidirectional_iterator_tag>
: handler_iterator_traits<_Iterator, std::forward_iterator_tag>
{
	static void prev(_Iterator& it)
	{ --it._M_current; }
};

template<typename _Iterator>
struct handler_iterator_traits<_Iterator, std::random_access_iterator_tag>
: handler_iterator_traits<_Iterator, std::bidirectional_iterator_tag>
{
	static void next(_Iterator& it)
	{ ++it._M_current; }

	static void next(_Iterator& it, int n)
	{ it._M_current += n; }

	static _Iterator next(const _Iterator& it, int n, int)
	{ return _Iterator(it._M_current + n); }

	static void prev(_Iterator& it)
	{ --it._M_current; }

	static void prev(_Iterator& it, int n)
	{ it._M_current -= n; }

	static _Iterator prev(const _Iterator& it, int n, int)
	{ return _Iterator(it._M_current - n); }
};


#ifdef __GXX_EXPERIMENTAL_CXX0X__
template<typename _Iterator, typename _Base, typename _Traits>
handler_iterator<_Iterator, _Base, _Traits> __to_handler_iterator(const handler_iterator<_Iterator, _Base, _Traits>&);

template<typename _T>
struct to_handler_iterator
{
	typedef decltype(__to_handler_iterator(std::declval<const _T&>())) type;
};
#endif

}}}

#endif