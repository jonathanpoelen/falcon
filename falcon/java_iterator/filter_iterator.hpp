#ifndef _FALCON_JAVA_ITERATOR_FILTER_ITERATOR_HPP
#define _FALCON_JAVA_ITERATOR_FILTER_ITERATOR_HPP


#include <falcon/c++/cast.hpp>
#include <falcon/java_iterator/partial_java_iterator.hpp>
#include <falcon/type_traits/is_java_iterator.hpp>
#include <falcon/container/range_access.hpp>

namespace falcon {
namespace java_iterator {

template <typename _Predicate, typename _Iterator>
class filter_iterator
: partial_java_iterator<_Iterator>
{
	typedef filter_iterator<_Predicate, _Iterator> self_type;
	typedef partial_java_iterator<_Iterator> base_type;

public:
	typedef _Iterator iterator;
	typedef _Predicate predicate;
	typedef typename base_type::value_type value_type;
	typedef typename base_type::pointer pointer;
	typedef typename base_type::reference reference;

private:
	iterator _end;
	predicate _predicate;

public:
	filter_iterator(_Predicate p, const _Iterator& first, const _Iterator& last)
	: base_type(first)
	, _end(last)
	, _predicate(p)
	{
		satisfy_predicate();
	}

	template<typename _Container>
	filter_iterator(_Predicate p, _Container& cont)
	: base_type(falcon::begin<>(cont))
	, _end(falcon::end<>(cont))
	, _predicate(p)
	{
		satisfy_predicate();
	}

	filter_iterator(_Predicate p, const _Iterator& first)
	: base_type(first)
	, _end()
	, _predicate(p)
	{
		satisfy_predicate();
	}

	filter_iterator(const _Iterator& first, const _Iterator& last)
	: base_type(first)
	, _end(last)
	, _predicate()
	{
		satisfy_predicate();
	}

	filter_iterator(const _Iterator& first)
	: base_type(first)
	, _end()
	, _predicate()
	{
		satisfy_predicate();
	}

	filter_iterator(const filter_iterator& other)
	: base_type(other._it)
	, _end(other._end)
	, _predicate(other._predicate)
	{}

	self_type& operator=(const iterator& it)
	{
		base_type::operator=(it);
		satisfy_predicate();
		return *this;
	}

	bool valid() const
	{ return base_type::_it != _end; }

	void satisfy_predicate()
	{
		while (base_type::_it != _end && !_predicate(*base_type::_it))
			++base_type::_it;
	}

	reference next()
	{
		reference r = *base_type::_it;
		++*this;
		return r;
	}
	reference prev()
	{
		reference r = *base_type::_it;
		--*this;
		return r;
	}

	FALCON_MEMBER_INCREMENT(self_type,
							++base_type::_it; satisfy_predicate())
	FALCON_MEMBER_DECREMENT(self_type,
							while(!_predicate(*--(base_type::_it))))

	CPP_EXPLICIT_BOOL_CAST(valid())
};

template <typename _Predicate, typename _Container, typename _Iterator = typename _Container::iterator>
filter_iterator<_Predicate, _Iterator> make_filter_iterator(_Predicate p, _Container& c) {
	return filter_iterator<_Predicate, _Iterator>(p, c);
}

template <typename _Predicate, typename _Iterator>
filter_iterator<_Predicate, _Iterator> make_filter_iterator(_Predicate p, const _Iterator& it, const _Iterator& last) {
	return filter_iterator<_Predicate, _Iterator>(p, it, last);
}

template <typename _Predicate, typename _Iterator>
filter_iterator<_Predicate, _Iterator> make_filter_iterator(_Predicate p, const _Iterator& it) {
	return filter_iterator<_Predicate, _Iterator>(p, it);
}

}

template <typename _Predicate, typename _Iterator>
struct is_java_iterator<java_iterator::filter_iterator<_Predicate, _Iterator> >
: true_type
{};

}

#endif