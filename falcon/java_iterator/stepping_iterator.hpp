#ifndef _FALCON_JAVA_ITERATOR_STEPPING_ITERATOR_HPP
#define _FALCON_JAVA_ITERATOR_STEPPING_ITERATOR_HPP

#include <falcon/c++/cast.hpp>
#include <falcon/java_iterator/partial_java_iterator.hpp>
#include <falcon/type_traits/is_java_iterator.hpp>
#include <falcon/container/range_access.hpp>

namespace falcon {

namespace java_iterator {

	namespace detail {
		template<typename _Iterator, typename _Tag = typename _Iterator::iterator_category>
		struct stepping_iterator
		{
			static void next(_Iterator& it, _Iterator& end, int n)
			{
				while (n-- && it != end)
					--it;
			}

			static void prev(_Iterator& it, int n)
			{ std::advance<>(it, -n); }
		};

		template<typename _Iterator>
		struct stepping_iterator<_Iterator, std::random_access_iterator_tag>
		{
			static void next(_Iterator& it, _Iterator& end, int n)
			{
				it += n;
				if (it > end)
					it = end;
			}

			static void prev(_Iterator& it, int n)
			{ it -= n; }
		};
	}

template <typename _Iterator>
class stepping_iterator
: public partial_java_iterator<_Iterator>
{
	typedef stepping_iterator<_Iterator> self_type;
	typedef partial_java_iterator<_Iterator> base_type;

public:
	typedef _Iterator iterator;
	typedef typename base_type::value_type value_type;
	typedef typename base_type::pointer pointer;
	typedef typename base_type::reference reference;

private:
	iterator _end;
	int _step;

public:
	stepping_iterator(int step, const iterator& begin, const iterator& __end)
	: base_type(begin)
	, _end(__end)
	, _step(step)
	{}

	stepping_iterator(int step, const iterator& begin)
	: base_type(begin)
	, _end()
	, _step(step)
	{}

	template <typename _Container>
	stepping_iterator(int step, _Container& container)
	: base_type(falcon::begin(container))
	, _end(falcon::end(container))
	, _step(step)
	{}

	stepping_iterator(const self_type& other)
	: base_type(other._it)
	, _end(other._end)
	{}

	self_type& operator=(const self_type& other)
	{
		base_type::current(other._it);
		_end = other._end;
		return *this;
	}

	self_type& operator=(const iterator& it)
	{
		base_type::operator=(it);
		return *this;
	}

	const iterator& end() const
	{ return _end; }

	void end(const iterator& __end)
	{ _end = __end; }

	bool valid() const
	{ return base_type::_it != _end; }

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

	FALCON_MEMBER_INCREMENT(self_type, detail::stepping_iterator<_Iterator>::next(base_type::_it, _end, _step))
	FALCON_MEMBER_DECREMENT(self_type, detail::stepping_iterator<_Iterator>::prev(base_type::_it, _step))

	CPP_EXPLICIT_BOOL_CAST(valid())
};

template <typename _Container, typename _Iterator = typename _Container::iterator>
stepping_iterator<_Iterator> make_stepping_iterator(int step, _Container& c) {
	return stepping_iterator<_Iterator>(step, c);
}

template <typename _Iterator>
stepping_iterator<_Iterator> make_stepping_iterator(int step, const _Iterator& begin, const _Iterator& end) {
	return stepping_iterator<_Iterator>(step, begin, end);
}

}

template <typename _Iterator>
struct is_java_iterator<java_iterator::stepping_iterator<_Iterator> >
: true_type
{};

}

#endif