#ifndef ITERATOR_ITERATOR_HANDLER_HPP
#define ITERATOR_ITERATOR_HANDLER_HPP

#include <iterator>
#ifdef __GXX_EXPERIMENTAL_CXX0X__
# include <utility>
#else
# include <boost/type_traits/add_pointer.hpp>
#endif
#include <falcon/c++/boost_or_std.hpp>
#include <falcon/type_traits/is_same.hpp>
#include <falcon/type_traits/use.hpp>
#include <falcon/type_traits/use_if.hpp>

namespace falcon {
namespace iterator {

template<typename _Iterator, typename _IteratorBase,
	typename _Category,
	typename _Tp,
	typename _Distance,
	typename _Pointer,
	typename _Reference
>
class iterator_handler;

class iterator_core_access
{
public:
#define FALCON_ITERATOR_HANDLER_TEMPLATE_HEAD()\
	template<typename _I, typename _IBase, \
		typename _C, typename _V, typename _D, typename _P, typename _R>

#define FALCON_ITERATOR_HANDLER_TYPE()\
	iterator_handler<_I, _IBase, _C, _V, _D, _P, _R>

#define FALCON_ITERATOR_CORE_ACCESS_HEAD(prefix, result_type, name, qualifier)\
	FALCON_ITERATOR_HANDLER_TEMPLATE_HEAD()\
	prefix result_type name(qualifier FALCON_ITERATOR_HANDLER_TYPE()& a)

	FALCON_ITERATOR_CORE_ACCESS_HEAD(static, _I&, derived, )
	{ return a.downcast(); }

	FALCON_ITERATOR_CORE_ACCESS_HEAD(static, const _I&, derived, const)
	{ return a.downcast(); }

#define FALCON_ITERATOR_CORE_ACCESS(result_type, member, qualifier)\
	FALCON_ITERATOR_CORE_ACCESS_HEAD(static, result_type, member, qualifier)\
	{ return derived(a).member(); }

	FALCON_ITERATOR_CORE_ACCESS(const _IBase&, base_reference, )
	FALCON_ITERATOR_CORE_ACCESS(_IBase&, base_reference, const)

	FALCON_ITERATOR_CORE_ACCESS(typename _I::reference, dereference, )
	FALCON_ITERATOR_CORE_ACCESS(typename _I::reference, dereference, const)

	FALCON_ITERATOR_CORE_ACCESS(void, increment, )
	FALCON_ITERATOR_CORE_ACCESS(void, decrement, )

#undef FALCON_ITERATOR_CORE_ACCESS

	FALCON_ITERATOR_CORE_ACCESS_HEAD(friend, typename _I::reference, operator*, )
	{ return dereference(a); }

	FALCON_ITERATOR_CORE_ACCESS_HEAD(friend, typename _I::reference, operator*, const)
	{ return dereference(a); }

	FALCON_ITERATOR_CORE_ACCESS_HEAD(friend, _I&, operator++, )
	{
		increment(a);
		return derived(a);
	}

	FALCON_ITERATOR_CORE_ACCESS_HEAD(friend, _I&, operator--, )
	{
		decrement(a);
		return derived(a);
	}

#undef FALCON_ITERATOR_CORE_ACCESS_HEAD

	FALCON_ITERATOR_HANDLER_TEMPLATE_HEAD()
	friend _I operator++(FALCON_ITERATOR_HANDLER_TYPE()& a, int)
	{
		_I ret(derived(a));
		increment(a);
		return ret;
	}

	FALCON_ITERATOR_HANDLER_TEMPLATE_HEAD()
	friend _I operator--(FALCON_ITERATOR_HANDLER_TYPE()& a, int)
	{
		_I ret(derived(a));
		decrement(a);
		return ret;
	}

#define FALCON_ITERATOR_CORE_ACCESS_2CONST_HEAD(prefix, result_type, name)\
	template<typename _I, typename _IBase, typename _I2, typename _IBase2,\
		typename _C, typename _V, typename _D, typename _P, typename _R>\
	prefix result_type name(const FALCON_ITERATOR_HANDLER_TYPE()& a,\
													const iterator_handler<_I2, _IBase2, \
																								 _C, _V, _D, _P, _R>& b)

#define FALCON_ITERATOR_CORE_ACCESS_COMPARISON(result_type, op, member)\
	FALCON_ITERATOR_CORE_ACCESS_2CONST_HEAD(static, result_type, member)\
	{ return derived(a).member(derived(b)); }\
	FALCON_ITERATOR_CORE_ACCESS_2CONST_HEAD(friend, result_type, operator op)\
	{ return member(a, b); }

	FALCON_ITERATOR_CORE_ACCESS_COMPARISON(bool, ==, equal)
	FALCON_ITERATOR_CORE_ACCESS_COMPARISON(bool, <, less)
	FALCON_ITERATOR_CORE_ACCESS_COMPARISON(typename _I::difference_type, -, difference)

#undef FALCON_ITERATOR_CORE_ACCESS_COMPARISON

#define FALCON_ITERATOR_CORE_ACCESS_COMPARISON(op, core)\
	FALCON_ITERATOR_CORE_ACCESS_2CONST_HEAD(friend, bool, operator op)\
	{ return core; }

	FALCON_ITERATOR_CORE_ACCESS_COMPARISON(!=, !(a==b))
	FALCON_ITERATOR_CORE_ACCESS_COMPARISON(<=, !(b<a))
	FALCON_ITERATOR_CORE_ACCESS_COMPARISON(>,    b<a)
	FALCON_ITERATOR_CORE_ACCESS_COMPARISON(>=, !(a<b))

#undef FALCON_ITERATOR_CORE_ACCESS_COMPARISON

#define FALCON_ITERATOR_CORE_ACCESS_MOVE(op, member, member2)\
	FALCON_ITERATOR_HANDLER_TEMPLATE_HEAD()\
	static void member(FALCON_ITERATOR_HANDLER_TYPE()& a,\
														typename _I::difference_type n)\
	{ derived(a).member(n); }\
	FALCON_ITERATOR_HANDLER_TEMPLATE_HEAD()\
	static _I member2(const FALCON_ITERATOR_HANDLER_TYPE()& a,\
									 typename _I::difference_type n)\
	{ return derived(a).member2(n); }\
	FALCON_ITERATOR_HANDLER_TEMPLATE_HEAD()\
	friend _I& operator op##=(FALCON_ITERATOR_HANDLER_TYPE()& a,\
														typename _I::difference_type n)\
	{\
		member(a, n);\
		return derived(a);\
	}\
	FALCON_ITERATOR_HANDLER_TEMPLATE_HEAD()\
	friend _I operator op(const FALCON_ITERATOR_HANDLER_TYPE()& a,\
											 typename _I::difference_type n)\
	{ return member2(a, n); }

	FALCON_ITERATOR_CORE_ACCESS_MOVE(+, advance, next)
	FALCON_ITERATOR_CORE_ACCESS_MOVE(-, recoil, prev)

#undef FALCON_ITERATOR_CORE_ACCESS_MOVE

#undef FALCON_ITERATOR_HANDLER_TYPE
#undef FALCON_ITERATOR_HANDLER_TEMPLATE_HEAD
};

template<typename _Iterator, typename _IteratorBase,
	typename _Category,
	typename _Tp,
	typename _Distance,
	typename _Pointer,
	typename _Reference
>
class iterator_handler
: public std::iterator<_Category, _Tp, _Distance, _Pointer, _Reference>
, public iterator_core_access
{
	friend class iterator_core_access;

	typedef std::iterator<_Category, _Tp, _Distance, _Pointer, _Reference> __base;


public:
	typedef _IteratorBase iterator_type;
	typedef typename __base::iterator_category iterator_category;
	typedef typename __base::value_type value_type;
	typedef typename __base::difference_type difference_type;
	typedef typename __base::pointer pointer;
	typedef typename __base::reference reference;


private:
	_IteratorBase _M_current;


public:
	iterator_handler()
	: _M_current()
	{}

	explicit iterator_handler(iterator_type __x)
	: _M_current(__x)
	{}

	explicit iterator_handler(const iterator_type& __x, int)
	: _M_current(__x)
	{}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	explicit iterator_handler(iterator_type&& __x, int)
	: _M_current(std::move(__x))
	{}

	template<typename... _Args>
	explicit iterator_handler(const std::piecewise_construct_t&, _Args&&... __args)
	: _M_current(std::forward<_Args>(__args)...)
	{}
#endif

	iterator_handler(const iterator_handler& other)
	: _M_current(other._M_current)
	{}

	template<typename I2, typename IBase2, typename C2,
		typename T2, typename D2, typename P2, typename R2>
	iterator_handler(const iterator_handler<I2, IBase2, C2, T2, D2, P2, R2>& other)
	: _M_current(iterator_core_access::base_reference(other._M_current))
	{}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	template<typename _U, class _Enable = typename
	std::enable_if<!std::is_reference<iterator_type>::value && std::is_convertible<_U, iterator_type>::value>::type>
	explicit iterator_handler(_U&& __x)
	: _M_current(std::forward<_U>(__x))
	{}

	iterator_handler& operator=(const iterator_handler&) = default;
	iterator_handler& operator=(iterator_handler&&) = default;
	iterator_handler& operator=(_Iterator&& other)
	{ return operator=(static_cast<iterator_handler&&>(other)); };
#else
	iterator_handler& operator=(const iterator_type& other) = default
	{
		_M_current = other._M_current;
		return *this;
	}
#endif

	iterator_handler& operator=(const iterator_type& __x)
	{
		_M_current = __x;
		return *this;
	}

	iterator_type base() const
	{ return _M_current; }

	pointer operator->()
	{ return &**this; }

	pointer operator->() const
	{ return &**this; }

	reference operator[](difference_type n)
	{ return *(*this + n); }

	reference operator[](difference_type n) const
	{ return *(*this + n); }

protected:
	iterator_type& base_reference()
	{ return _M_current; }

	const iterator_type& base_reference() const
	{ return _M_current; }

private:
	typedef integral_constant<bool, is_same<std::input_iterator_tag, iterator_category>::value> __is_input_tag;

	void dereference(true_type) const;

	reference dereference(false_type) const
	{ return *_M_current; }

	reference dereference(false_type)
	{ return *_M_current; }

	void increment(true_type)
	{}

	void increment(false_type)
	{ ++_M_current; }

	void decrement(true_type)
	{}

	void decrement(false_type)
	{ --_M_current; }

protected:
	_Iterator& downcast()
	{ return static_cast<_Iterator&>(*this); }

	const _Iterator& downcast() const
	{ return static_cast<const _Iterator&>(*this); }

	reference dereference() const
	{ return dereference(__is_input_tag()); }

	reference dereference()
	{ return dereference(__is_input_tag()); }

	void increment()
	{ increment(__is_input_tag()); }

	void decrement()
	{ decrement(__is_input_tag()); }

	bool equal(const iterator_handler& x) const
	{ return _M_current == x._M_current; }

	bool less(const iterator_handler& x) const
	{ return _M_current < x._M_current; }

	difference_type difference(const iterator_handler& x,
														 std::forward_iterator_tag) const
	{ return _M_current - x._M_current; }

	difference_type difference(const iterator_handler& x) const
	{ return difference(x, iterator_category()); }

	void advance(difference_type n)
	{ _M_current += n; }

	_Iterator next(difference_type n) const
	{
		_Iterator ret(downcast());
		ret += n;
		return ret;
	}

	void recoil(difference_type n)
	{ _M_current -= n; }

	_Iterator prev(difference_type n) const
	{
		_Iterator ret(downcast());
		ret -= n;
		return ret;
	}
};

template<typename _Iterator, typename _IteratorBase,
	typename _Category = use_default,
	typename _Tp = use_default,
	typename _Distance = use_default,
	typename _Pointer = use_default,
	typename _Reference = use_default
>
struct iterator_handler_types
{
	typedef std::iterator_traits<_IteratorBase> __iterator_traits;

	typedef typename default_or_type<
		use_iterator_category<__iterator_traits>,
		_Category
	>::type iterator_category;
	typedef typename default_or_type<
		use_value_type<__iterator_traits>,
		_Tp
	>::type value_type;
	typedef typename default_or_type<
		use_difference_type<__iterator_traits>,
		_Distance
	>::type difference_type;
	typedef typename eval_if_c<
		is_default<_Pointer>,
		eval_if_c<
			is_default<_Tp>,
			use_pointer<__iterator_traits>,
			FALCON_BOOST_OR_STD_NAMESPACE::add_pointer<value_type>
		>,
		use<_Pointer>
	>::type pointer;
	typedef typename eval_if_c<
		is_default<_Reference>,
		eval_if_c<
			is_default<_Tp>,
			use_reference<__iterator_traits>,
			use<value_type&>
		>,
		use<_Reference>
	>::type reference;

	typedef iterator_handler<
		_Iterator,
		_IteratorBase,
		iterator_category,
		value_type,
		difference_type,
		pointer,
		reference
	> base;
};

}}

#endif