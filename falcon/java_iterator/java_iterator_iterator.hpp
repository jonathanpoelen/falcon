#ifndef _FALCON_JAVA_ITERATOR_JAVA_ITERATOR_ITERATOR_HPP
#define _FALCON_JAVA_ITERATOR_JAVA_ITERATOR_ITERATOR_HPP

#include <type_traits>
#include <falcon/c++/cast.hpp>
#include <falcon/preprocessor/incremental.hpp>
#include <falcon/preprocessor/comparison.hpp>
#include <falcon/preprocessor/getter.hpp>
#include <falcon/java_iterator/detail/iterator_traits.hpp>
#include <falcon/type_traits/is_java_iterator.hpp>
#include <falcon/container/range_access.hpp>

namespace falcon {

namespace java_iterator {

template <typename _Iterator, typename _AccessIterator, bool _IsJavaIterator = is_java_iterator<_Iterator>::value>
class java_iterator_iterator
{
	typedef java_iterator_iterator<_Iterator, _AccessIterator, _IsJavaIterator> self_type;

public:
	typedef _Iterator iterator;
	typedef typename _AccessIterator::result_type iterator_wrapper;

private:
	typedef typename detail::to_iterator_traits<iterator_wrapper>::type iterator_traits;

public:
	typedef typename iterator_traits::value_type value_type;
	typedef typename iterator_traits::pointer pointer;
	typedef typename iterator_traits::reference reference;
	typedef typename iterator_traits::difference_type difference_type;
	typedef typename iterator_traits::iterator_category iterator_category;

private:
	iterator _it;
	iterator _end;
	iterator_wrapper _it_wrap;
	iterator_wrapper _end_wrap;
	_AccessIterator _begin_access;
	_AccessIterator _end_access;

public:
	java_iterator_iterator(const _AccessIterator& access)
	: _it()
	, _end()
	, _it_wrap()
	, _end_wrap()
	, _begin_access(access)
	, _end_access(access)
	{}

	java_iterator_iterator(const _AccessIterator& begin_access, const _AccessIterator& end_access)
	: _it()
	, _end()
	, _it_wrap()
	, _end_wrap()
	, _begin_access(begin_access)
	, _end_access(end_access)
	{}

	java_iterator_iterator(const iterator& it, const iterator& __end, const _AccessIterator& access)
	: _it(it)
	, _end(__end)
	, _it_wrap(access(*it))
	, _end_wrap(access(*it))
	, _begin_access(access)
	, _end_access(access)
	{}

	java_iterator_iterator(const iterator& it, const iterator& __end, const _AccessIterator& begin_access, const _AccessIterator& end_access)
	: _it(it)
	, _end(__end)
	, _it_wrap(begin_access(*it))
	, _end_wrap(end_access(*it))
	, _begin_access(begin_access)
	, _end_access(end_access)
	{}

	template <typename _Container>
	java_iterator_iterator(_Container& container, const _AccessIterator& access)
	: _it(falcon::begin(container))
	, _end(falcon::end(container))
	, _it_wrap(access(*_it))
	, _end_wrap(access(*_it))
	, _begin_access(access)
	, _end_access(access)
	{}

	template <typename _Container>
	java_iterator_iterator(_Container& container, const _AccessIterator& begin_access, const _AccessIterator& end_access)
	: _it(falcon::begin(container))
	, _end(falcon::end(container))
	, _it_wrap(begin_access(*_it))
	, _end_wrap(end_access(*_it))
	, _begin_access(begin_access)
	, _end_access(end_access)
	{}

	java_iterator_iterator(const self_type& other)
	: _it(other._it)
	, _end(other._end)
	, _it_wrap(other._it_wrap)
	, _end_wrap(other._end_wrap)
	, _begin_access(other._begin_access)
	, _end_access(other._end_access)
	{}

	self_type& operator=(const self_type& other)
	{
		_it = other._it;
		_end = other._end;
		_it_wrap = other._it_wrap;
		_end_wrap = other._end_wrap;
		_begin_access = other._begin_access;
		_end_access = other._end_access;
		return *this;
	}

	self_type& operator=(const iterator& it)
	{ begin(it); return *this; }

	void begin(const iterator& it)
	{
		_it = it;
		_it_wrap = _begin_access(*it);
		_end_wrap = _end_access(*it);
	}

	void end(const iterator& __end)
	{ _end = __end; }

	FALCON_MEMBER_GETTER(reference, operator*, *_it_wrap)
	FALCON_MEMBER_GETTER(pointer, operator->, _it_wrap.operator->())

	reference next()
	{
		reference r = *_it;
		++*this;
		return r;
	}

	self_type & operator ++ ()
	{
		if (++_it_wrap == _end_wrap && ++_it != _end)
		{
			_it_wrap = _begin_access(*_it);
			_end_wrap = _end_access(*_it);
		}
		return *this;
	}

	self_type operator ++ (int)
	{
		self_type tmp(*this);
		operator ++ ();
		return tmp;
	}

	const iterator& current() const
	{ return _it_wrap; }

	iterator& current()
	{ return _it_wrap; }

	bool valid() const
	{ return _it != _end; }

	CPP_EXPLICIT_BOOL_CAST(valid())
};

template <typename _JavaIterator, typename _AccessIterator>
class java_iterator_iterator<_JavaIterator, _AccessIterator, true>
{
	typedef java_iterator_iterator<_JavaIterator, _AccessIterator, true> self_type;

public:
	typedef _JavaIterator java_iterator;
	typedef typename _AccessIterator::result_type iterator_wrapper;

private:
	typedef typename detail::to_iterator_traits<iterator_wrapper>::type iterator_traits;

public:
	typedef typename iterator_traits::value_type value_type;
	typedef typename iterator_traits::pointer pointer;
	typedef typename iterator_traits::reference reference;
	typedef typename iterator_traits::difference_type difference_type;
	typedef typename iterator_traits::iterator_category iterator_category;

private:
	java_iterator _java_it;
	iterator_wrapper _it_wrap;
	iterator_wrapper _end_wrap;
	_AccessIterator _begin_access;
	_AccessIterator _end_access;

public:
	java_iterator_iterator(const _AccessIterator& access)
	: _java_it()
	, _it_wrap()
	, _end_wrap()
	, _begin_access(access)
	, _end_access(access)
	{}

	java_iterator_iterator(const _AccessIterator& begin_access, const _AccessIterator& end_access)
	: _java_it()
	, _it_wrap()
	, _end_wrap()
	, _begin_access(begin_access)
	, _end_access(end_access)
	{}

	java_iterator_iterator(const java_iterator& java_it, const _AccessIterator& access)
	: _java_it(java_it)
	, _it_wrap(access(*_java_it))
	, _end_wrap(access(*_java_it))
	, _begin_access(access)
	, _end_access(access)
	{}

	java_iterator_iterator(const java_iterator& java_it, const _AccessIterator& begin_access, const _AccessIterator& end_access)
	: _java_it(java_it)
	, _it_wrap(begin_access(*_java_it))
	, _end_wrap(end_access(*_java_it))
	, _begin_access(begin_access)
	, _end_access(end_access)
	{}

	template <typename _Container>
	java_iterator_iterator(_Container& container, const _AccessIterator& access)
	: _java_it(container)
	, _it_wrap(access(*_java_it))
	, _end_wrap(access(*_java_it))
	, _begin_access(access)
	, _end_access(access)
	{}

	template <typename _Container>
	java_iterator_iterator(_Container& container, const _AccessIterator& begin_access, const _AccessIterator& end_access)
	: _java_it(container)
	, _it_wrap(begin_access(*_java_it))
	, _end_wrap(end_access(*_java_it))
	, _begin_access(begin_access)
	, _end_access(end_access)
	{}

	java_iterator_iterator(const self_type& other)
	: _java_it(other._java_it)
	, _it_wrap(other._it_wrap)
	, _end_wrap(other._end_wrap)
	, _begin_access(other._begin_access)
	, _end_access(other._end_access)
	{}

	self_type& operator=(const self_type& other)
	{
		_java_it = other._java_it;
		_it_wrap = other._it_wrap;
		_end_wrap = other._end_wrap;
		_begin_access = other._begin_access;
		_end_access = other._end_access;
		return *this;
	}

	self_type& operator=(const java_iterator& it)
	{ iterator(it); return *this; }

	void iterator(const java_iterator& it)
	{
		_java_it = it;
		_it_wrap = _begin_access(*it);
		_end_wrap = _end_access(*it);
	}

	FALCON_MEMBER_GETTER(reference, operator*, *_java_it)
	FALCON_MEMBER_GETTER(pointer, operator->, _java_it.operator->())

	reference next()
	{
		reference r = *_it_wrap;
		++*this;
		return r;
	}

	self_type & operator ++ ()
	{
		if (++_it_wrap == _end_wrap && _java_it.valid())
		{
			_java_it.next();
			_it_wrap = _begin_access(*_java_it);
			_end_wrap = _end_access(*_java_it);
		}
		return *this;
	}

	self_type operator ++ (int)
	{
		self_type tmp(*this);
		operator ++ ();
		return tmp;
	}

	const java_iterator& current() const
	{ return _it_wrap; }

	java_iterator& current()
	{ return _it_wrap; }

	bool valid() const
	{ return _java_it.valid(); }

	CPP_EXPLICIT_BOOL_CAST(valid())
};

namespace detail {

	template <typename _Iterator, typename _AccessIterator>
	struct to_iterator_traits<java_iterator_iterator<_Iterator, _AccessIterator, true>, true>
	{
		typedef typename to_iterator_traits<typename _Iterator::java_iterator>::type type;
	};

}

template <typename _Iterator, typename _AccessIterator>
java_iterator_iterator<_Iterator, _AccessIterator, false> make_java_iterator_iterator(const _Iterator& it, const _Iterator& end, const _AccessIterator& access)
{ return java_iterator_iterator<_Iterator, _AccessIterator, false>(it, end, access); }

template <typename _Iterator, typename _AccessIterator>
java_iterator_iterator<_Iterator, _AccessIterator, false> make_java_iterator_iterator(const _Iterator& it, const _Iterator& end, const _AccessIterator& begin_access, const _AccessIterator& end_access)
{ return java_iterator_iterator<_Iterator, _AccessIterator, false>(it, end, begin_access, end_access); }

template <typename _Container, typename _AccessIterator>
typename std::enable_if<!is_java_iterator<_Container>::value, java_iterator_iterator<typename _Container::iterator, _AccessIterator, false> >::type make_java_iterator_iterator(_Container& container, const _AccessIterator& access)
{ return java_iterator_iterator<typename _Container::iterator, _AccessIterator, false>(container, access); }

template <typename _Container, typename _AccessIterator>
typename std::enable_if<!is_java_iterator<_Container>::value, java_iterator_iterator<typename _Container::iterator, _AccessIterator, false> >::type make_java_iterator_iterator(_Container& container, const _AccessIterator& begin_access, const _AccessIterator& end_access)
{ return java_iterator_iterator<typename _Container::iterator, _AccessIterator, false>(container, begin_access, end_access); }

template <typename _Iterator, typename _AccessIterator>
typename std::enable_if<is_java_iterator<_Iterator>::value, java_iterator_iterator<_Iterator, _AccessIterator, true> >::type make_java_iterator_iterator(const _Iterator& java_it, const _AccessIterator& access)
{ return java_iterator_iterator<_Iterator, _AccessIterator, true>(java_it, access); }

template <typename _Iterator, typename _AccessIterator>
typename std::enable_if<is_java_iterator<_Iterator>::value, java_iterator_iterator<_Iterator, _AccessIterator, true> >::type make_java_iterator_iterator(const _Iterator& java_it, const _AccessIterator& begin_access, const _AccessIterator& end_access)
{ return java_iterator_iterator<_Iterator, _AccessIterator, true>(java_it, begin_access, end_access); }

}

template <typename _Iterator, typename _AccessIterator, bool _IsJavaIterator>
struct is_java_iterator<java_iterator::java_iterator_iterator<_Iterator, _AccessIterator, _IsJavaIterator> >
: true_type
{};

}

#endif