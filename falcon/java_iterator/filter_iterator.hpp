#ifndef _FALCON_JAVA_ITERATOR_FILTER_ITERATOR_HPP
#define _FALCON_JAVA_ITERATOR_FILTER_ITERATOR_HPP

#include <falcon/java_iterator/java_iterator.hpp>
#include <falcon/java_iterator/is_java_iterator.hpp>

namespace falcon {
namespace java_iterator {

template <typename _Iterator, typename _Predicate,
	typename _Tp = use_default,
	typename _Reference = use_default>
class filter_iterator;

namespace detail {
	template <typename _Iterator, typename _Predicate, typename _Tp, typename _Reference,
		bool _IsJavaIterator = is_java_iterator<_Iterator>::value>
	struct filter_base
	{
		typedef java_iterator<
			_Iterator,
			use_default,
			_Tp,
			_Reference,
			filter_iterator<_Iterator, _Predicate, _Tp, _Reference>
		> base;
	};

	template <typename _Iterator, typename _Predicate, typename _Tp, typename _Reference>
	struct filter_base<_Iterator, _Predicate, _Tp, _Reference, true>
	{
		typedef typename java_iterator_handler_types<
			filter_iterator<_Iterator, _Predicate, _Tp, _Reference>,
			_Iterator,
			use_default,
			_Tp,
			_Reference
		>::base base;
	};
}

template <typename _Iterator, typename _Predicate, typename _Tp, typename _Reference>
class filter_iterator
: public detail::filter_base<_Iterator, _Predicate, _Tp, _Reference>::base
{
	friend class java_iterator_core_access;

	typedef typename detail::filter_base<_Iterator, _Predicate, _Tp, _Reference>::base __base;

public:
	typedef _Predicate predicate_type;
	typedef typename __base::iterator_type iterator_type;

private:
	predicate_type _predicate;

public:
	filter_iterator(iterator_type x, predicate_type p)
	: __base(x)
	, _predicate(p)
	{ satisfy_predicate(); }

	explicit filter_iterator(iterator_type x)
	: __base(x)
	, _predicate()
	{ satisfy_predicate(); }

	filter_iterator(iterator_type first, iterator_type last, predicate_type p)
	: __base(first, last)
	, _predicate(p)
	{ satisfy_predicate(); }

	filter_iterator(iterator_type first, iterator_type last)
	: __base(first, last)
	, _predicate()
	{ satisfy_predicate(); }

	template<typename _Container>
	filter_iterator(_Container& cont, _Predicate p)
	: __base(cont)
	, _predicate(p)
	{ satisfy_predicate(); }

	template<typename _Container>
	explicit filter_iterator(_Container& cont)
	: __base(cont)
	, _predicate()
	{ satisfy_predicate(); }

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	filter_iterator(const filter_iterator&) = default;
#else
	filter_iterator(const filter_iterator& other)
	: __base(other.base_reference())
	, _predicate(other._predicate)
	{}
#endif

	filter_iterator& operator=(const iterator_type& x)
	{
		__base::operator=(x);
		satisfy_predicate();
		return *this;
	}

	void satisfy_predicate()
	{
		while (__base::do_valid() && _predicate(this->current()))
			__base::advance();
	}

	void predicate(const predicate_type& p)
	{ _predicate = p; }

	const predicate_type& predicate() const
	{ return _predicate; }

protected:
	void advance()
	{
		__base::advance();
		satisfy_predicate();
	}

	void recoil()
	{
		do {
			__base::recoil();
		} while(_predicate(this->current()));
	}
};


template <typename _Iterator, typename _Predicate>
inline filter_iterator<_Iterator, _Predicate>
make_filter_iterator(_Iterator first, _Iterator last, _Predicate p)
{ return filter_iterator<_Iterator, _Predicate>(first, last, p); }

template <typename _Container, typename _Predicate>
inline filter_iterator<typename _Container::iterator, _Predicate>
make_filter_iterator(_Container& cont, _Predicate p)
{ return filter_iterator<typename _Container::iterator, _Predicate>(cont, p); }

}
}

#endif