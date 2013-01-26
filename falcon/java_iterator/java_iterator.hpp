#ifndef FALCON_JAVA_ITERATOR_JAVA_ITERATOR_HPP
#define FALCON_JAVA_ITERATOR_JAVA_ITERATOR_HPP

#include <falcon/java_iterator/java_iterator_handler.hpp>
#include <falcon/container/range_access.hpp>

namespace falcon {
namespace java_iterator {

template <typename _Iterator,
	typename _Category = use_default,
	typename _Tp = use_default,
	typename _Reference = use_default,
	typename _Parent = use_default>
class java_iterator;

namespace detail {
	template <typename _Iterator, typename _Category,
		typename _Tp, typename _Reference, typename _Parent>
	struct java_base
	{
		typedef typename java_iterator_handler_types<
			typename default_or_type<
				use<java_iterator<_Iterator, _Category, _Tp, _Reference, _Parent> >,
				_Parent
			>::type,
			_Iterator,
			_Category,
			_Tp,
			_Reference
		>::base base;
	};
}

template <typename _Iterator, typename _Category,
	typename _Tp, typename _Reference, typename _Parent>
struct java_iterator
: detail::java_base<_Iterator, _Category, _Tp, _Reference, _Parent>::base
{
	friend class java_iterator_core_access;

	typedef typename detail::java_base<_Iterator, _Category, _Tp, _Reference, _Parent>::base __base;

public:
	typedef _Iterator iterator_type;

private:
	iterator_type _end;

public:
	java_iterator()
	: __base()
	, _end()
	{}

	explicit java_iterator(iterator_type first)
	: __base(first)
	, _end()
	{}

	java_iterator(iterator_type first, iterator_type last)
	: __base(first)
	, _end(last)
	{}

	template<typename _Container>
	java_iterator(_Container& cont)
	: __base(falcon::begin<>(cont))
	, _end(falcon::end<>(cont))
	{}

	java_iterator(const java_iterator& other)
	: __base(other)
	, _end(other._end)
	{}

	void begin(const iterator_type& x)
	{ __base::operator=(x); }

	void end(const iterator_type& x)
	{ _end = x; }

	const iterator_type& begin() const
	{ return this->base_reference(); }

	const iterator_type& end() const
	{ return _end; }

	typename iterator_type::difference_type size() const
	{ return _end - this->base_reference(); }

protected:
	bool do_valid() const
	{ return this->base_reference() != _end; }
};


template <typename _Iterator>
java_iterator<_Iterator>
make_java_iterator(_Iterator first, _Iterator last)
{ return java_iterator<_Iterator>(first, last); }

template <typename _Container>
java_iterator<typename _Container::iterator>
make_java_iterator(_Container& cont)
{ return java_iterator<typename _Container::iterator>(cont); }

}
}

#endif