#ifndef _FALCON_ITERATOR_PROXY_ITERATOR_HPP
#define _FALCON_ITERATOR_PROXY_ITERATOR_HPP

#include <utility>
#include <falcon/c++0x/keywords.hpp>
// #include <falcon/preprocessor/incremental.hpp>
#include <falcon/preprocessor/comparison.hpp>
#include <falcon/preprocessor/getter.hpp>
#include <falcon/iterator/detail/to_iterator_traits.hpp>

namespace falcon {

namespace iterator {

template <typename _Iterator, typename _Proxy, typename _T = typename std::result_of<_Proxy(decltype(*std::declval<_Iterator&>()))>::type, bool = std::is_reference<_T>::value>
class proxy_iterator
{
	typedef proxy_iterator<_Iterator, _Proxy, _T, true> self_type;
	typedef typename detail::to_iterator_traits<_Iterator>::type iterator_traits;

public:
	typedef _Proxy proxy_type;
	typedef _Iterator iterator;
	typedef typename std::remove_reference<_T>::type value_type;
	typedef _T reference;
	typedef const value_type& const_reference;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef typename iterator_traits::difference_type difference_type;
	typedef typename iterator_traits::iterator_category iterator_category;

private:
	iterator _it;
	proxy_type _proxy;

public:
	proxy_iterator()
	: _it()
	, _proxy()
	{}

	proxy_iterator(const iterator& it)
	: _it(it)
	, _proxy()
	{}

	proxy_iterator(const iterator& it, const proxy_type& proxy)
	: _it(it)
	, _proxy(proxy)
	{}

	/*proxy_iterator(const proxy_type& proxy, const iterator& it)
	: _it(it)
	, _proxy(proxy)
	{}*/

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	template<typename... _Args>
	proxy_iterator(const std::piecewise_construct_t&, const iterator& it, _Args&&... args)
	: _it(it)
	, _proxy(std::forward<_Args>(args)...)
	{}
#endif

	proxy_iterator(const self_type& other)
	: _it(other._it)
	, _proxy(other._proxy)
	{}

	self_type& operator=(const self_type& oher)
	{
		_it = oher._it;
		_proxy = oher._proxy;
		return *this;
	}

	self_type& operator=(const iterator& it)
	{
		_it = it;
		return *this;
	}

	self_type& operator=(const proxy_type& proxy)
	{
		_proxy = proxy;
		return *this;
	}

	FALCON_MEMBER_GETTER(iterator, base, _it)

	/*const proxy_type& proxy() const
	{ return _proxy; }
	proxy_type& proxy()
	{ return _proxy; }

	void proxy(const proxy_type& proxy)
	{ _proxy = proxy; }*/

	reference operator*()
	{ return _proxy(*_it); }
	const_reference operator*() const
	{ return _proxy(*_it); }

	pointer operator->()
	{ return &_proxy(*_it); }
	const_pointer operator->() const
	{ return &_proxy(*_it); }
};

template <typename _Iterator, typename _Proxy, typename _T>
class proxy_iterator<_Iterator, _Proxy, _T, false>
{
	typedef proxy_iterator<_Iterator, _Proxy, _T, false> self_type;
	typedef typename detail::to_iterator_traits<_Iterator>::type iterator_traits;

public:
	typedef _Proxy proxy_type;
	typedef _Iterator iterator;
	typedef _T value_type;
	typedef _T reference;
	typedef _T pointer;
	typedef typename iterator_traits::difference_type difference_type;
	typedef typename iterator_traits::iterator_category iterator_category;

private:
	iterator _it;
	proxy_type _proxy;

public:
	proxy_iterator()
	: _it()
	, _proxy()
	{}

	proxy_iterator(const iterator& it)
	: _it(it)
	, _proxy()
	{}

	proxy_iterator(const iterator& it, const proxy_type& proxy)
	: _it(it)
	, _proxy(proxy)
	{}

	proxy_iterator(const proxy_type& proxy, const iterator& it)
	: _it(it)
	, _proxy(proxy)
	{}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	template<typename... _Args>
	proxy_iterator(const iterator& it, _Args&&... args)
	: _it(it)
	, _proxy(std::forward<_Args>(args)...)
	{}
#endif

	proxy_iterator(const self_type& other)
	: _it(other._it)
	, _proxy(other._proxy)
	{}

	self_type& operator=(const self_type& oher)
	{
		_it = oher._it;
		_proxy = oher._proxy;
		return *this;
	}

	self_type& operator=(const iterator& it)
	{
		_it = it;
		return *this;
	}

	self_type& operator=(const proxy_type& proxy)
	{
		_proxy = proxy;
		return *this;
	}

	FALCON_MEMBER_GETTER(iterator, base, _it)

	/*const proxy_type& proxy() const
	{ return _proxy; }
	proxy_type& proxy()
	{ return _proxy; }

	void proxy(const proxy_type& proxy)
	{ _proxy = proxy; }*/

	reference operator*()
	{ return _proxy(*_it); }
	reference operator*() const
	{ return _proxy(*_it); }

	pointer operator->()
	{ return _proxy(*_it); }
	pointer operator->() const
	{ return _proxy(*_it); }
};

template <typename _Iterator, typename _Proxy, typename _T, bool _IsRef>
proxy_iterator<_Iterator, _Proxy, _T, _IsRef>& operator++(proxy_iterator<_Iterator, _Proxy, _T, _IsRef>& it)
{
	++it.base();
	return it;
}

template <typename _Iterator, typename _Proxy, typename _T, bool _IsRef>
proxy_iterator<_Iterator, _Proxy, _T, _IsRef> operator++(const proxy_iterator<_Iterator, _Proxy, _T, _IsRef>& it, int)
{
	proxy_iterator<_Iterator, _Proxy, _T, _IsRef> ret(it);
	++ret;
	return ret;
}

template <typename _Iterator, typename _Proxy, typename _T, bool _IsRef>
proxy_iterator<_Iterator, _Proxy, _T, _IsRef>& operator--(proxy_iterator<_Iterator, _Proxy, _T, _IsRef>& it)
{
	--it.base();
	return it;
}

template <typename _Iterator, typename _Proxy, typename _T, bool _IsRef>
proxy_iterator<_Iterator, _Proxy, _T, _IsRef> operator--(const proxy_iterator<_Iterator, _Proxy, _T, _IsRef>& it, int)
{
	proxy_iterator<_Iterator, _Proxy, _T, _IsRef> ret(it);
	--ret;
	return ret;
}

template <typename _Iterator, typename _Proxy, typename _T, bool _IsRef>
bool operator == (const proxy_iterator<_Iterator, _Proxy, _T, _IsRef> & a, const proxy_iterator<_Iterator, _Proxy, _T, _IsRef> & b)
{ return a.base() == b.base(); }

template <typename _Iterator, typename _Proxy, typename _T, bool _IsRef>
bool operator < (const proxy_iterator<_Iterator, _Proxy, _T, _IsRef> & a, const proxy_iterator<_Iterator, _Proxy, _T, _IsRef> & b)
{ return a.base() < b.base(); }

template <typename _Iterator, typename _Proxy, typename _T, bool _IsRef>
bool operator <= (const proxy_iterator<_Iterator, _Proxy, _T, _IsRef> & a, const proxy_iterator<_Iterator, _Proxy, _T, _IsRef> & b)
{ return a.base() <= b.base(); }

template <typename _Iterator, typename _Proxy, typename _T, bool _IsRef>
bool operator > (const proxy_iterator<_Iterator, _Proxy, _T, _IsRef> & a, const proxy_iterator<_Iterator, _Proxy, _T, _IsRef> & b)
{ return a.base() > b.base(); }

template <typename _Iterator, typename _Proxy, typename _T, bool _IsRef>
bool operator >= (const proxy_iterator<_Iterator, _Proxy, _T, _IsRef> & a, const proxy_iterator<_Iterator, _Proxy, _T, _IsRef> & b)
{ return a.base() >= b.base(); }

template <typename _Iterator, typename _Proxy, typename _T, bool _IsRef>
bool operator != (const proxy_iterator<_Iterator, _Proxy, _T, _IsRef> & a, const proxy_iterator<_Iterator, _Proxy, _T, _IsRef> & b)
{ return a.base() != b.base(); }


template <typename _Iterator, typename _Proxy, typename _T, bool _IsRef>
bool operator == (const proxy_iterator<_Iterator, _Proxy, _T, _IsRef> & a, const typename proxy_iterator<_Iterator, _Proxy, _T, _IsRef>::iterator & b)
{ return a.base() == b; }

template <typename _Iterator, typename _Proxy, typename _T, bool _IsRef>
bool operator < (const proxy_iterator<_Iterator, _Proxy, _T, _IsRef> & a, const typename proxy_iterator<_Iterator, _Proxy, _T, _IsRef>::iterator& b)
{ return a.base() < b; }

template <typename _Iterator, typename _Proxy, typename _T, bool _IsRef>
bool operator <= (const proxy_iterator<_Iterator, _Proxy, _T, _IsRef> & a, const typename proxy_iterator<_Iterator, _Proxy, _T, _IsRef>::iterator & b)
{ return a.base() <= b; }

template <typename _Iterator, typename _Proxy, typename _T, bool _IsRef>
bool operator > (const proxy_iterator<_Iterator, _Proxy, _T, _IsRef> & a, const typename proxy_iterator<_Iterator, _Proxy, _T, _IsRef>::iterator& b)
{ return a.base() > b; }

template <typename _Iterator, typename _Proxy, typename _T, bool _IsRef>
bool operator >= (const proxy_iterator<_Iterator, _Proxy, _T, _IsRef> & a, const typename proxy_iterator<_Iterator, _Proxy, _T, _IsRef>::iterator & b)
{ return a.base() >= b; }

template <typename _Iterator, typename _Proxy, typename _T, bool _IsRef>
bool operator != (const proxy_iterator<_Iterator, _Proxy, _T, _IsRef> & a, const typename proxy_iterator<_Iterator, _Proxy, _T, _IsRef>::iterator & b)
{ return a.base() != b; }


template <typename _Iterator, typename _Proxy, typename _T, bool _IsRef>
proxy_iterator<_Iterator, _Proxy, _T, _IsRef>& operator+=(proxy_iterator<_Iterator, _Proxy, _T, _IsRef>& it, std::size_t n)
{
	it.base() += n;
	return it;
}

template <typename _Iterator, typename _Proxy, typename _T, bool _IsRef>
proxy_iterator<_Iterator, _Proxy, _T, _IsRef>& operator-=(const proxy_iterator<_Iterator, _Proxy, _T, _IsRef>& it, std::size_t n)
{
	it.base() -= n;
	return it;
}


template <typename _Iterator, typename _Proxy, typename _T, bool _IsRef>
typename proxy_iterator<_Iterator, _Proxy, _T, _IsRef>::difference_type operator-(const proxy_iterator<_Iterator, _Proxy, _T, _IsRef>& a, const proxy_iterator<_Iterator, _Proxy, _T, _IsRef>& b)
{ return a.base() - b.base(); }


template <typename _Iterator, typename _Proxy, typename _T, bool _IsRef>
proxy_iterator<_Iterator, _Proxy, _T, _IsRef> operator-(const proxy_iterator<_Iterator, _Proxy, _T, _IsRef>& a, std::size_t n)
{ return a.base() - n; }

template <typename _Iterator, typename _Proxy, typename _T, bool _IsRef>
proxy_iterator<_Iterator, _Proxy, _T, _IsRef> operator+(const proxy_iterator<_Iterator, _Proxy, _T, _IsRef>& a, const proxy_iterator<_Iterator, _Proxy, _T, _IsRef>& b)
{ return a.base() + b.base(); }

template <typename _Iterator, typename _Proxy, typename _T, bool _IsRef>
proxy_iterator<_Iterator, _Proxy, _T, _IsRef> operator+(const proxy_iterator<_Iterator, _Proxy, _T, _IsRef>& a, std::size_t n)
{ return a.base() + n; }


template <typename _Iterator, typename _Proxy, typename _T = typename std::remove_reference<typename std::result_of<_Proxy(_Iterator&)>::type>::type, bool _IsRef = std::is_reference<_T>::value>
proxy_iterator<_Iterator, _Proxy, _T, _IsRef> make_proxy_iterator(const _Iterator& begin, const _Proxy& proxy) {
	return proxy_iterator<_Iterator, _Proxy, _T, _IsRef>(begin, proxy);
}

}

}

#endif