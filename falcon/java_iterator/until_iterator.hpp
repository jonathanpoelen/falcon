#ifndef _FALCON_JAVA_ITERATOR_UNTIL_ITERATOR_HPP
#define _FALCON_JAVA_ITERATOR_UNTIL_ITERATOR_HPP

#include <falcon/java_iterator/java_iterator_handler.hpp>

namespace falcon {
namespace java_iterator {

template <typename _Iterator,
	typename _Tp = use_default,
	typename _Reference = use_default>
class until_iterator;

namespace detail {
	template <typename _Iterator, typename _Tp, typename _Reference>
	struct until_base
	{
		typedef typename java_iterator_handler_types<
			until_iterator<_Iterator, _Tp, _Reference>,
			_Iterator,
			use_default,
			_Tp,
			_Reference
		>::base base;
	};
}

template <typename _Iterator, typename _Tp, typename _Reference>
struct until_iterator
: public detail::until_base<_Iterator, _Tp, _Reference>::base
{
	friend class java_iterator_core_access;

	typedef typename detail::until_base<_Iterator, _Tp, _Reference>::base __base;

public:
	typedef typename __base::iterator_type iterator_type;
	typedef typename __base::value_type value_type;

private:
	value_type _stop;

public:
	until_iterator(iterator_type begin, const value_type& __stop)
	: __base(begin)
	, _stop(__stop)
	{}

	until_iterator(iterator_type begin)
	: __base(begin)
	, _stop()
	{}

	template <typename _Container>
	until_iterator(_Container& container, const value_type& __stop)
	: __base(container)
	, _stop(__stop)
	{}

	using __base::operator=;

	const value_type& stop() const
	{ return _stop; }

	void stop(const value_type& value)
	{ _stop = value; }

protected:
	bool do_valid() const
	{ return this->current() != _stop; }
};

template <typename _Iterator, typename _Value>
inline until_iterator<_Iterator>
make_until_iterator(_Iterator begin, const _Value& stop)
{ return until_iterator<_Iterator>(begin, stop); }

}

}

#endif