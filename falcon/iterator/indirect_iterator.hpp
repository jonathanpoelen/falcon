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
class indirect_iterator;

namespace detail
{
	template <typename _Iterator, typename _Proxy>
	struct indirect_iterator_base
	: std::iterator_traits<_Iterator>
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

template<typename _Iterator, typename _Proxy>
struct __indirect_iterator_traits
: detail::handler_iterator_traits<indirect_iterator<_Iterator, _Proxy> >
{
	typedef indirect_iterator<_Iterator, _Proxy> __indirect_iterator;
	typedef detail::handler_iterator_traits<__indirect_iterator> __base;

	static typename __base::reference dereference(const __indirect_iterator& it)
	{ return it.proxy()(*it._M_current); }

	static typename __base::reference dereference(__indirect_iterator& it)
	{ return it.proxy()(*it._M_current); }

	using __base::next;
	static __indirect_iterator next(const __indirect_iterator& it, int n, int)
	{ return __indirect_iterator(it._M_current + n, it.proxy()); }

	using __base::prev;
	static __indirect_iterator prev(const __indirect_iterator& it, int n, int)
	{ return __indirect_iterator(it._M_current - n, it.proxy()); }
};

template <typename _Iterator>
struct __proxy_indirect_iterator
{
	typedef typename std::iterator_traits<_Iterator>::value_type __value_type;
#ifdef __GXX_EXPERIMENTAL_CXX0X__
	typedef decltype(**std::declval<_Iterator&>()) __result_type;
#else
	typedef typename boost::remove_pointer<__value_type>::type& __result_type;
#endif

	__result_type operator()(__value_type& x) const
	{ return *x; }
};

template <typename _Iterator, typename _Proxy = __proxy_indirect_iterator<_Iterator> >
class indirect_iterator
: public detail::handler_iterator<
	indirect_iterator<_Iterator, _Proxy>,
	_Iterator,
	__indirect_iterator_traits<_Iterator, _Proxy>,
	detail::indirect_iterator_base<_Iterator, _Proxy>
>
{
	typedef detail::handler_iterator<
		indirect_iterator<_Iterator, _Proxy>,
		_Iterator,
		__indirect_iterator_traits<_Iterator, _Proxy>,
		detail::indirect_iterator_base<_Iterator, _Proxy>
	> __base;

	_Proxy _proxy;

public:
	typedef typename __base::iterator_type iterator_type;
	typedef _Proxy proxy_type;

public:
	indirect_iterator()
	: __base()
	, _proxy()
	{}

	explicit indirect_iterator(iterator_type __x)
	: __base(__x)
	, _proxy()
	{}

	explicit indirect_iterator(iterator_type __x, proxy_type __proxy)
	: __base(__x)
	, _proxy(__proxy)
	{}

	indirect_iterator(const indirect_iterator& __x)
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
indirect_iterator<_Iterator, _Proxy>
make_indirect_iterator(_Iterator x, _Proxy proxy)
{ return indirect_iterator<_Iterator, _Proxy>(x, proxy); }

template <typename _Iterator>
indirect_iterator<_Iterator>
make_indirect_iterator(_Iterator x)
{ return indirect_iterator<_Iterator>(x); }

}}

#endif