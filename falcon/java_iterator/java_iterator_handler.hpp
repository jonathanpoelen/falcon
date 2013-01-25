#ifndef FALCON_JAVA_ITERATOR_JAVA_ITERATOR_HANDLER_HPP
#define FALCON_JAVA_ITERATOR_JAVA_ITERATOR_HANDLER_HPP

#include <iterator>
#ifdef __GXX_EXPERIMENTAL_CXX0X__
# include <utility>
#endif
#include <falcon/type_traits/use.hpp>
#include <falcon/type_traits/use_if.hpp>
#include <falcon/java_iterator/java_iterator_category.hpp>

namespace falcon {
namespace java_iterator {

template<typename _Iterator, typename _IteratorBase, typename _Category,
	typename _Tp, typename _Reference>
class java_iterator_handler;

class java_iterator_core_access
{
public:
#define FALCON_ITERATOR_CORE_ACCESS_HEAD(result_type, name, qualifier)\
	template<typename _I, typename _IBase, typename _C, typename _T, typename _R>\
	static result_type name(qualifier java_iterator_handler<_I, _IBase, _C, _T, _R>& a)

	FALCON_ITERATOR_CORE_ACCESS_HEAD(_I&, derived, )
	{ return a.downcast(); }

	FALCON_ITERATOR_CORE_ACCESS_HEAD(const _I&, derived, const)
	{ return a.downcast(); }

	FALCON_ITERATOR_CORE_ACCESS_HEAD(_IBase&, base_reference, )
	{ return a.downcast().base_reference(); }

	FALCON_ITERATOR_CORE_ACCESS_HEAD(const _IBase&, base_reference, const)
	{ return a.downcast().base_reference(); }

	FALCON_ITERATOR_CORE_ACCESS_HEAD(bool, valid, const)
	{ return a.downcast().do_valid(); }

	FALCON_ITERATOR_CORE_ACCESS_HEAD(const _R, current, const)
	{ return a.downcast().do_current(); }

	FALCON_ITERATOR_CORE_ACCESS_HEAD(_R, current, )
	{ return a.downcast().do_current(); }

	FALCON_ITERATOR_CORE_ACCESS_HEAD(void, advance, )
	{ return a.downcast().advance(); }

	FALCON_ITERATOR_CORE_ACCESS_HEAD(void, recoil, )
	{ return a.downcast().recoil(); }

	FALCON_ITERATOR_CORE_ACCESS_HEAD(_R, next, )
	{
		_R r = current(a);
		advance(a);
		return r;
	}

	FALCON_ITERATOR_CORE_ACCESS_HEAD(_R, prev, )
	{
		_R r = current(a);
		recoil(a);
		return r;
	}

#undef FALCON_ITERATOR_CORE_ACCESS_HEAD
};

template<typename _Iterator, typename _IteratorBase, typename _Category,
	typename _Tp, typename _Reference>
class java_iterator_handler
{
	friend class java_iterator_core_access;

public:
	typedef _Category java_iterator_category;
	typedef _IteratorBase iterator_type;
	typedef _Tp value_type;
	typedef _Reference reference;

private:
	_IteratorBase _M_current;

public:
	java_iterator_handler()
	: _M_current()
	{}

	explicit java_iterator_handler(iterator_type __x)
	: _M_current(__x)
	{}

	explicit java_iterator_handler(const iterator_type& __x, int)
	: _M_current(__x)
	{}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	explicit java_iterator_handler(iterator_type&& __x, int)
	: _M_current(std::move(__x))
	{}

	template<typename... _Args>
	explicit java_iterator_handler(const std::piecewise_construct_t&, _Args&&... __args)
	: _M_current(std::forward<_Args>(__args)...)
	{}
#endif

	java_iterator_handler(const java_iterator_handler& other)
	: _M_current(other._M_current)
	{}

	template<typename I2, typename IBase2, typename _C2, typename T2, typename R2>
	java_iterator_handler(const java_iterator_handler<I2, IBase2, _C2, T2, R2>& other)
	: _M_current(java_iterator_core_access::base_reference(other._M_current))
	{}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	template<typename _U, class _Enable = typename
	std::enable_if<!std::is_reference<iterator_type>::value && std::is_convertible<_U, iterator_type>::value>::type>
	explicit java_iterator_handler(_U&& __x)
	: _M_current(std::forward<_U>(__x))
	{}
#endif

	java_iterator_handler& operator=(const iterator_type& __x)
	{
		_M_current = __x;
		return *this;
	}

	iterator_type base() const
	{ return _M_current; }

	const reference current() const
	{ return java_iterator_core_access::current(*this); }

	reference current()
	{ return java_iterator_core_access::current(*this); }

	bool valid() const
	{ return java_iterator_core_access::valid(*this); }

	reference next()
	{ return java_iterator_core_access::next(*this); }

	reference prev()
	{ return java_iterator_core_access::prev(*this); }

protected:
	bool do_valid() const
	{ return _M_current.valid(); }

	reference do_current()
	{ return *_M_current; }

	const reference do_current() const
	{ return *_M_current; }

	void advance()
	{ ++_M_current; }

	void recoil()
	{ --_M_current; }

protected:
	iterator_type& base_reference()
	{ return _M_current; }

	const iterator_type& base_reference() const
	{ return _M_current; }

	_Iterator& downcast()
	{ return static_cast<_Iterator&>(*this); }

	const _Iterator& downcast() const
	{ return static_cast<const _Iterator&>(*this); }
};

template<typename _Iterator, typename _IteratorBase,
	typename _Category = use_default,
	typename _Tp = use_default,
	typename _Reference = use_default
>
struct java_iterator_handler_types
{
	typedef typename if_c<
		is_java_iterator_category<_IteratorBase>,
		_IteratorBase,
		std::iterator_traits<_IteratorBase>
	>::type __iterator_traits;

	typedef typename default_or_type<
		use_iterator_category<__iterator_traits>,
		_Category
	>::type iterator_category;
	typedef typename default_or_type<
		use_value_type<__iterator_traits>,
		_Tp
	>::type value_type;
	typedef typename eval_if_c<
		is_default<_Reference>,
		eval_if_c<
			is_default<_Tp>,
			use_reference<__iterator_traits>,
			use<value_type&>
		>,
		use<_Reference>
	>::type reference;

	typedef java_iterator_handler<
		_Iterator,
		_IteratorBase,
		iterator_category,
		value_type,
		reference
	> base;
};

}
}

#endif