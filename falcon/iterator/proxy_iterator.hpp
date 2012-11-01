#ifndef FALCON_ITERATOR_PROXY_ITERATOR_HPP
#define FALCON_ITERATOR_PROXY_ITERATOR_HPP

#ifdef __GXX_EXPERIMENTAL_CXX0X__
# include <type_traits>
#else
# include <boost/type_traits/remove_reference.hpp>
#endif
#include <falcon/iterator/detail/handler_iterator.hpp>

namespace falcon {
namespace iterator {
	template <typename _Iterator, typename _Proxy>
	class proxy_iterator;
}}

namespace std
{
	template <typename _Iterator, typename _Proxy>
	struct iterator_traits< ::falcon::iterator::proxy_iterator<_Iterator, _Proxy> >
	: iterator_traits<_Iterator>
	{
#ifdef __GXX_EXPERIMENTAL_CXX0X__
		typedef typename std::result_of<
			const _Proxy&(decltype(*std::declval<_Iterator&>()))
		>::type reference;
		typedef typename std::remove_reference<reference>::type value_type;
#else
		typedef typename _Proxy::result_type reference;
		typedef typename boost::remove_reference<reference>::type value_type;
#endif
		typedef value_type* pointer;
	};
}

namespace falcon {
namespace iterator {

template<typename _Iterator, typename _Proxy>
struct __proxy_iterator_traits
: detail::handler_iterator_trait<proxy_iterator<_Iterator, _Proxy>, _Iterator>
{
	typedef proxy_iterator<_Iterator, _Proxy> __proxy_iterator;
	typedef detail::handler_iterator_trait<__proxy_iterator, _Iterator> __base;

	static typename __base::reference dereference(const __proxy_iterator& it)
	{ return it.proxy()(*it._M_current); }

	static typename __base::reference dereference(__proxy_iterator& it)
	{ return it.proxy()(*it._M_current); }

	using __base::next;
	static __proxy_iterator next(const __proxy_iterator& it, int n, int)
	{ return __proxy_iterator(it._M_current + n, it.proxy()); }

	using __base::prev;
	static __proxy_iterator prev(const __proxy_iterator& it, int n, int)
	{ return __proxy_iterator(it._M_current - n, it.proxy()); }
};


template <typename _Iterator, typename _Proxy>
class proxy_iterator
: public detail::handler_iterator<
	proxy_iterator<_Iterator, _Proxy>,
	_Iterator,
	__proxy_iterator_traits<_Iterator, _Proxy>
>
{
	typedef detail::handler_iterator<
		proxy_iterator<_Iterator, _Proxy>,
		_Iterator,
		__proxy_iterator_traits<_Iterator, _Proxy>
	> __base;

	_Proxy _proxy;

public:
	typedef typename __base::iterator_type iterator_type;
	typedef _Proxy proxy_type;

public:
	proxy_iterator()
	: __base()
	, _proxy()
	{}

	explicit proxy_iterator(iterator_type __x)
	: __base(__x)
	, _proxy()
	{}

	explicit proxy_iterator(iterator_type __x, const proxy_type& __proxy)
	: __base(__x)
	, _proxy(__proxy)
	{}

	proxy_iterator(const proxy_iterator& __x)
	: __base(__x._M_current)
	, _proxy(__x._proxy)
	{}

	using __base::operator=;

	const _Proxy& proxy() const
	{ return _proxy; }

	_Proxy& proxy()
	{ return _proxy; }
};

template <typename _Iterator, typename _Proxy>
proxy_iterator<_Iterator, _Proxy>
make_proxy_iterator(_Iterator x, const _Proxy& proxy)
{ return proxy_iterator<_Iterator, _Proxy>(x, proxy); }

}}

#endif