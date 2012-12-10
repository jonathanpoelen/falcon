#ifndef ITERATOR_ITERATOR_HANDLER_HPP
#define ITERATOR_ITERATOR_HANDLER_HPP

#include <iterator>
#ifdef __GXX_EXPERIMENTAL_CXX0X__
# include <utility>
#endif
#include <falcon/type_traits/is_same.hpp>
#include <falcon/type_traits/use.hpp>
#include <falcon/type_traits/use_if.hpp>

namespace falcon {
namespace iterator {

class iterator_core_access;

template<typename _Iterator, typename _IteratorBase,
	typename _Category,
	typename _Tp,
	typename _Distance,
	typename _Pointer,
	typename _Reference
>
class iterator_handler
: public std::iterator<_Category, _Tp, _Distance, _Pointer, _Reference>
{
	friend class iterator_core_access;

	typedef std::iterator<_Category, _Tp, _Distance, _Pointer, _Reference> __base;
public:
	_IteratorBase _M_current;

public:
	typedef _IteratorBase iterator_type;
	typedef typename __base::iterator_category iterator_category;
	typedef typename __base::value_type value_type;
	typedef typename __base::difference_type difference_type;
	typedef typename __base::pointer pointer;
	typedef typename __base::reference reference;


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

	iterator_handler(const iterator_handler& other)
	: _M_current(other._M_current)
	{}

	template<typename I2, typename IBase2, typename C2,
		typename T2, typename D2, typename P2, typename R2>
	iterator_handler(const iterator_handler<I2, IBase2, C2, T2, D2, P2, R2>& other)
	: _M_current(other._M_current)
	{}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	explicit iterator_handler(iterator_type&& __x)
	: _M_current(std::forward<iterator_type>(__x))
	{}

	template<typename _U, class _Enable = typename
	std::enable_if<!std::is_reference<iterator_type>::value && std::is_convertible<_U, iterator_type>::value>::type>
	explicit iterator_handler(_U&& __x)
	: _M_current(std::forward<_U>(__x))
	{}
#endif

	iterator_handler& operator=(iterator_type __x)
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

private:
	iterator_type& base_reference()
	{ return _M_current; }

	const iterator_type& base_reference() const
	{ return _M_current; }

	_Iterator& downcast()
	{ return static_cast<_Iterator&>(*this); }

	const _Iterator& downcast() const
	{ return static_cast<const _Iterator&>(*this); }

	reference dereference() const
	{ return *_M_current; }

	reference dereference()
	{ return *_M_current; }

	void increment(true_type)
	{}

	void increment(false_type)
	{ ++_M_current; }

	void increment()
	{
		increment(integral_constant<bool,
							is_same<std::input_iterator_tag, iterator_category>::value>());
	}

	void decrement()
	{ --_M_current; }

	bool equal(const iterator_handler& x) const
	{ return _M_current == x._M_current; }

	bool less(const iterator_handler& x) const
	{ return _M_current < x._M_current; }

	difference_type difference(const iterator_handler& x) const
	{ return x._M_current - _M_current; }

	void advance(difference_type n)
	{ _M_current += n; }

	_Iterator advance(difference_type n) const
	{ return _Iterator(downcast()) += n; }

	void recoil(difference_type n)
	{ _M_current += n; }

	_Iterator recoil(difference_type n) const
	{ return _Iterator(downcast()) -= n; }
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
		use_type<__iterator_traits>,
		_Tp
	>::type value_type;
	typedef typename default_or_type<
		use_difference_type<__iterator_traits>,
		_Distance
	>::type difference_type;
	typedef typename eval_if_c<
		is_default<_Pointer>,
		if_c<
			is_default<_Tp>,
			typename __iterator_traits::value_type,
			value_type*
		>,
		default_or_type<
			use_pointer<__iterator_traits>,
			_Pointer
		>
	>::type pointer;
	typedef typename eval_if_c<
		is_default<_Reference>,
		if_c<
			is_default<_Tp>,
			typename __iterator_traits::reference,
			value_type&
		>,
		default_or_type<
			use_reference<__iterator_traits>,
			_Reference
		>
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

#define FALCON_ITERATOR_HANDLER_TEMPLATE_HEAD()\
	template<typename _I, typename _IBase, \
		typename _C, typename _V, typename _D, typename _P, typename _R>

#define FALCON_ITERATOR_HANDLER_TEMPLATE2_HEAD()\
	template<typename _I, typename _IBase, \
		typename _C, typename _V, typename _D, typename _P, typename _R,\
		typename _I2, typename _IBase2, \
		typename _C2, typename _V2, typename _D2, typename _P2, typename _R2>

#define FALCON_ITERATOR_HANDLER_TYPE()\
	iterator_handler<_I, _IBase, _C, _V, _D, _P, _R>

#define FALCON_ITERATOR_HANDLER2_TYPE()\
	iterator_handler<_I2, _IBase2, _C2, _V2, _D2, _P2, _R2>

class iterator_core_access
{
public:
#define FALCON_ITERATOR_CORE_ACCESS_OP(result_type, qualifier, member)\
	FALCON_ITERATOR_HANDLER_TEMPLATE_HEAD()\
	static result_type member(qualifier FALCON_ITERATOR_HANDLER_TYPE()& a)\
	{ return derived(a).member(); }

	FALCON_ITERATOR_CORE_ACCESS_OP(typename _I::reference, const, dereference)
	FALCON_ITERATOR_CORE_ACCESS_OP(typename _I::reference, , dereference)
	FALCON_ITERATOR_CORE_ACCESS_OP(void, , increment)
	FALCON_ITERATOR_CORE_ACCESS_OP(void, , decrement)

#undef FALCON_ITERATOR_CORE_ACCESS_OP

#define FALCON_ITERATOR_CORE_ACCESS_OP2(result_type, member)\
	FALCON_ITERATOR_HANDLER_TEMPLATE2_HEAD()\
	static result_type member(const FALCON_ITERATOR_HANDLER_TYPE()& a,\
														const FALCON_ITERATOR_HANDLER2_TYPE()& b)\
	{ return derived(a).member(derived(b)); }

FALCON_ITERATOR_CORE_ACCESS_OP2(bool, equal)
FALCON_ITERATOR_CORE_ACCESS_OP2(bool, less)
FALCON_ITERATOR_CORE_ACCESS_OP2(typename _I::difference_type, difference)

#undef FALCON_ITERATOR_CORE_ACCESS_OP2

#define FALCON_ITERATOR_CORE_ACCESS_MOVE_OP(result_type, qualifier, member, ret)\
	FALCON_ITERATOR_HANDLER_TEMPLATE_HEAD()\
	static result_type member(qualifier FALCON_ITERATOR_HANDLER_TYPE()& a,\
														typename _I::difference_type n)\
	{ ret derived(a).member(n); }

FALCON_ITERATOR_CORE_ACCESS_MOVE_OP(_I, const, advance, return)
FALCON_ITERATOR_CORE_ACCESS_MOVE_OP(_I, const, recoil, return)
FALCON_ITERATOR_CORE_ACCESS_MOVE_OP(void, , advance, )
FALCON_ITERATOR_CORE_ACCESS_MOVE_OP(void, , recoil, )

#undef FALCON_ITERATOR_CORE_ACCESS_MOVE_OP

#define FALCON_ITERATOR_CORE_ACCESS_HEAD(prefix, result_type, qualifier, name)\
	FALCON_ITERATOR_HANDLER_TEMPLATE_HEAD()\
	prefix result_type name(qualifier FALCON_ITERATOR_HANDLER_TYPE()& a)

	FALCON_ITERATOR_CORE_ACCESS_HEAD(static, _I&, , derived)
	{ return a.downcast(); }

	FALCON_ITERATOR_CORE_ACCESS_HEAD(static, const _I&, const, derived)
	{ return a.downcast(); }
};


FALCON_ITERATOR_CORE_ACCESS_HEAD(, typename _I::reference, const, operator*)
{ return iterator_core_access::dereference(a); }

FALCON_ITERATOR_CORE_ACCESS_HEAD(, typename _I::reference, , operator*)
{ return iterator_core_access::dereference(a); }

FALCON_ITERATOR_CORE_ACCESS_HEAD(, _I&, , operator++)
{
	iterator_core_access::increment(a);
	return iterator_core_access::derived(a);
}

FALCON_ITERATOR_CORE_ACCESS_HEAD(, _I&, , operator--)
{
	iterator_core_access::decrement(a);
	return iterator_core_access::derived(a);
}

#undef FALCON_ITERATOR_CORE_ACCESS_HEAD

FALCON_ITERATOR_HANDLER_TEMPLATE_HEAD()
_I operator++(FALCON_ITERATOR_HANDLER_TYPE()& a, int)
{
	_I ret(a);
	iterator_core_access::increment(a);
	return ret;
}

FALCON_ITERATOR_HANDLER_TEMPLATE_HEAD()
_I operator--(FALCON_ITERATOR_HANDLER_TYPE()& a, int)
{
	_I ret(a);
	iterator_core_access::decrement(a);
	return ret;
}

#define FALCON_ITERATOR_HANDLER_OP2(result_type, op, member)\
	FALCON_ITERATOR_HANDLER_TEMPLATE2_HEAD()\
	result_type operator op(const FALCON_ITERATOR_HANDLER_TYPE()& a,\
													const FALCON_ITERATOR_HANDLER2_TYPE()& b)\
	{ return iterator_core_access::member(a,b); }

FALCON_ITERATOR_HANDLER_OP2(bool, ==, equal)
FALCON_ITERATOR_HANDLER_OP2(bool, <, less)
FALCON_ITERATOR_HANDLER_OP2(typename _I::difference_type, -, difference)

#undef FALCON_ITERATOR_HANDLER_OP2

#define FALCON_ITERATOR_HANDLER_BINARY_OP(op, cmp)\
	FALCON_ITERATOR_HANDLER_TEMPLATE2_HEAD()\
	bool operator op(const FALCON_ITERATOR_HANDLER_TYPE()& a,\
									const FALCON_ITERATOR_HANDLER2_TYPE()& b)\
	{ return cmp; }

FALCON_ITERATOR_HANDLER_BINARY_OP(!=, !(a==b))
FALCON_ITERATOR_HANDLER_BINARY_OP(<=, !(b<a))
FALCON_ITERATOR_HANDLER_BINARY_OP(>,    b<a)
FALCON_ITERATOR_HANDLER_BINARY_OP(>=, !(a<b))

#undef FALCON_ITERATOR_HANDLER_BINARY_OP

#define FALCON_ITERATOR_HANDLER_MOVE_OP(result_type, qualifier, op, member, ret)\
	FALCON_ITERATOR_HANDLER_TEMPLATE_HEAD()\
	result_type operator op(qualifier FALCON_ITERATOR_HANDLER_TYPE()& a,\
													typename _I::difference_type n)\
	{ \
		ret iterator_core_access::member(a,n); \
		return iterator_core_access::derived(a);\
	}

FALCON_ITERATOR_HANDLER_MOVE_OP(_I, const, +, advance, return)
FALCON_ITERATOR_HANDLER_MOVE_OP(_I, const, -, recoil, return)
FALCON_ITERATOR_HANDLER_MOVE_OP(_I&, , +, advance, )
FALCON_ITERATOR_HANDLER_MOVE_OP(_I&, , -, recoil, )

#undef FALCON_ITERATOR_HANDLER_MOVE_OP

#undef FALCON_ITERATOR_HANDLER_TYPE
#undef FALCON_ITERATOR_HANDLER2_TYPE
#undef FALCON_ITERATOR_HANDLER_TEMPLATE_HEAD
#undef FALCON_ITERATOR_HANDLER_TEMPLATE2_HEAD

}}

#endif