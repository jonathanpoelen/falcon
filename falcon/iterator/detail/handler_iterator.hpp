#ifndef ITERATOR_DETAIL_HANDLER_ITERATOR_HPP
#define ITERATOR_DETAIL_HANDLER_ITERATOR_HPP

#include <iterator>
#ifdef __GXX_EXPERIMENTAL_CXX0X__
# include <utility>
#endif

namespace falcon {
namespace iterator {
namespace detail {

template<typename _Iterator, typename _Base, typename _Traits>
class handler_iterator
: public std::iterator<
	typename _Traits::iterator_category,
	typename _Traits::value_type,
	typename _Traits::difference_type,
	typename _Traits::pointer,
	typename _Traits::reference
>
{
public:
	_Base _M_current;

public:
	typedef _Base iterator_type;
	typedef typename _Traits::difference_type difference_type;
	typedef typename _Traits::pointer pointer;
	typedef typename _Traits::reference reference;


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

	pointer operator->()
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
		return *this;
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
};


template <typename _Iterator, typename _Base, typename _Traits>
bool operator==(const handler_iterator<_Iterator, _Base, _Traits>& a,
				const handler_iterator<_Iterator, _Base, _Traits>& b)
{ return _Traits::eq(a.downcast(), b.downcast()); }

template <typename _Iterator, typename _Base, typename _Traits>
bool operator<(const handler_iterator<_Iterator, _Base, _Traits>& a,
			   const handler_iterator<_Iterator, _Base, _Traits>& b)
{ return _Traits::lt(a.downcast(), b.downcast()); }

template <typename _Iterator, typename _Base, typename _Traits>
bool operator!=(const handler_iterator<_Iterator, _Base, _Traits>& a,
				const handler_iterator<_Iterator, _Base, _Traits>& b)
{ return !(a==b); }

template <typename _Iterator, typename _Base, typename _Traits>
bool operator<=(const handler_iterator<_Iterator, _Base, _Traits>& a,
				const handler_iterator<_Iterator, _Base, _Traits>& b)
{ return !(b<a); }

template <typename _Iterator, typename _Base, typename _Traits>
bool operator>(const handler_iterator<_Iterator, _Base, _Traits>& a,
				const handler_iterator<_Iterator, _Base, _Traits>& b)
{ return (b<a); }

template <typename _Iterator, typename _Base, typename _Traits>
bool operator>=(const handler_iterator<_Iterator, _Base, _Traits>& a,
				const handler_iterator<_Iterator, _Base, _Traits>& b)
{ return !(a<b); }


template <typename _Iterator, typename _Base, typename _Traits>
_Iterator&
operator+=(handler_iterator<_Iterator, _Base, _Traits>& a, int n)
{
	_Traits::next(a.downcast(), n);
	return a.downcast();
}

template <typename _Iterator, typename _Base, typename _Traits>
_Iterator&
operator-=(handler_iterator<_Iterator, _Base, _Traits>& a, int n)
{
	_Traits::prev(a.downcast(), n);
	return a.downcast();
}

template <typename _Iterator, typename _Base, typename _Traits>
_Iterator
operator+(const handler_iterator<_Iterator, _Base, _Traits>& a, int n)
{ return _Traits::next(a.downcast(), n, 1); }

template <typename _Iterator, typename _Base, typename _Traits>
_Iterator
operator-(const handler_iterator<_Iterator, _Base, _Traits>& a, int n)
{ return _Traits::prev(a.downcast(), n, 1); }

template <typename _Iterator, typename _Base, typename _Traits>
typename _Traits::difference_type
operator-(const handler_iterator<_Iterator, _Base, _Traits>& a,
		  const handler_iterator<_Iterator, _Base, _Traits>& b)
{ return _Traits::diff(a.downcast(), b.downcast()); }


template<typename _Iterator, typename _Base, typename _Tag = typename std::iterator_traits<_Iterator>::iterator_category>
class handler_iterator_trait;

template<typename _Iterator, typename _Base>
class handler_iterator_trait<_Iterator, _Base, std::input_iterator_tag>
{
	typedef typename std::iterator_traits<_Iterator> __traits;

public:
	typedef typename __traits::iterator_category iterator_category;
	typedef typename __traits::value_type value_type;
	typedef typename __traits::difference_type difference_type;
	typedef typename __traits::pointer pointer;
	typedef typename __traits::reference reference;

	static reference dereference(_Iterator& it)
	{ return *it._M_current; }
};

template<typename _Iterator, typename _Base>
struct handler_iterator_trait<_Iterator, _Base, std::output_iterator_tag>
: handler_iterator_trait<_Iterator, _Base, std::input_iterator_tag>
{};

template<typename _Iterator, typename _Base>
struct handler_iterator_trait<_Iterator, _Base, std::forward_iterator_tag>
: handler_iterator_trait<_Iterator, _Base, std::input_iterator_tag>
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

template<typename _Iterator, typename _Base>
struct handler_iterator_trait<_Iterator, _Base, std::bidirectional_iterator_tag>
: handler_iterator_trait<_Iterator, _Base, std::forward_iterator_tag>
{
	static void prev(_Iterator& it)
	{ --it._M_current; }
};

template<typename _Iterator, typename _Base>
struct handler_iterator_trait<_Iterator, _Base, std::random_access_iterator_tag>
: handler_iterator_trait<_Iterator, _Base, std::bidirectional_iterator_tag>
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