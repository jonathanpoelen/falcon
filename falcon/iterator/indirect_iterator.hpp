#ifndef FALCON_ITERATOR_PROXY_ITERATOR_HPP
#define FALCON_ITERATOR_PROXY_ITERATOR_HPP

#ifdef __GXX_EXPERIMENTAL_CXX0X__
# include <type_traits>
#else
# include <boost/type_traits/remove_pointer.hpp>
#endif
#include <falcon/iterator/iterator_handler.hpp>

namespace falcon {
namespace iterator {

template <typename _Iterator>
struct __proxy_indirect_iterator
{
	typedef typename std::iterator_traits<_Iterator>::value_type argument_type;
#ifdef __GXX_EXPERIMENTAL_CXX0X__
	typedef decltype(**std::declval<_Iterator&>()) result_type;
#else
	typedef typename boost::remove_pointer<argument_type>::type& result_type;
#endif

	result_type operator()(argument_type& x) const
	{ return *x; }
};

template <typename _Iterator, typename _Proxy = use_default,
	typename _Tp = use_default, typename _Category = use_default,
	typename _Reference = use_default, typename _Distance = use_default,
	typename _Pointer = use_default
>
class indirect_iterator;

namespace detail {

	template <typename _Iterator, typename _Proxy, typename _Tp,
		typename _Category, typename _Reference, typename _Distance, typename _Pointer>
	struct indirect_base
	{
		typedef typename default_or_type<
			use<__proxy_indirect_iterator<_Iterator> >,
			_Proxy
		>::type __proxy;

#ifdef __GXX_EXPERIMENTAL_CXX0X__
		struct __result_type{
			typedef typename std::result_of<
				__proxy(decltype(*std::declval<_Iterator&>()))
			>::type type;
		};
		typedef typename default_or_type<__result_type, _Reference>::type reference;
		typedef typename default_or_type<std::remove_reference<reference>, _Tp>::type value_type;
#else
		typedef typename default_or_type<use_result_type<__proxy>, _Tp>::type value_type;
		typedef typename default_or_type<use<value_type&>, _Reference>::type reference;
#endif

		typedef typename iterator_handler_types<
			indirect_iterator<_Iterator, _Proxy,
				_Tp, _Category, _Reference, _Distance, _Pointer>,
			_Iterator,
			_Category,
			value_type,
			_Distance,
			_Pointer,
			reference
		>::base base;
	};

}

template <typename _Iterator, typename _Proxy,
	typename _Tp,
	typename _Category,
	typename _Reference,
	typename _Distance,
	typename _Pointer
>
class indirect_iterator
: public detail::indirect_base<_Iterator, _Proxy, _Tp, _Category, _Reference, _Distance, _Pointer>::base
{
	friend class iterator_core_access;

	typedef detail::indirect_base<_Iterator, _Proxy, _Tp, _Category, _Reference, _Distance, _Pointer> __detail;
	typedef typename __detail::base __base;

public:
	typedef typename __base::iterator_type iterator_type;
	typedef typename __base::difference_type difference_type;
	typedef typename __base::reference reference;

	typedef typename __detail::__proxy  proxy_type;

private:
	proxy_type _proxy;

public:
	indirect_iterator()
	: __base()
	, _proxy()
	{}

	explicit indirect_iterator(iterator_type __x)
	: __base(__x)
	, _proxy()
	{}

	indirect_iterator(iterator_type __x, proxy_type __proxy)
	: __base(__x)
	, _proxy(__proxy)
	{}

	indirect_iterator(const indirect_iterator& __x)
	: __base(__x)
	, _proxy(__x._proxy)
	{}

	using __base::operator=;
#ifdef __GXX_EXPERIMENTAL_CXX0X__
	indirect_iterator& operator=(const indirect_iterator&) = default;
#else
	indirect_iterator& operator=(const indirect_iterator& other)
	{
		this->base_reference() = other.base_reference();
		_proxy = other._proxy;
		return *this;
	}
#endif

	const _Proxy& proxy() const
	{ return _proxy; }

	_Proxy& proxy()
	{ return _proxy; }

private:
	reference dereference() const
	{ return _proxy(*(this->base_reference())); }

	reference dereference()
	{ return _proxy(*(this->base_reference())); }
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