#ifndef _FALCON_ITERATOR_MULTIPLE_ITERATOR_HPP
#define _FALCON_ITERATOR_MULTIPLE_ITERATOR_HPP

#include <falcon/c++0x/syntax.hpp>
#include <falcon/tuple/operators.hpp>
#include <falcon/preprocessor/incremental.hpp>
#include <falcon/preprocessor/getter.hpp>

namespace falcon {

namespace iterator {

///TODO value_type, pointer, etc sont templater à la maniere de std::get (membre static)

template<typename... _Iterators>
struct multiple_iterator : public std::tuple<_Iterators CPP0X_EXTEND_PACK>
{
	typedef multiple_iterator<_Iterators CPP0X_EXTEND_PACK> self_type;

private:
	typedef std::tuple<_Iterators CPP0X_EXTEND_PACK> base_type;

public:
	typedef base_type tuple_type;

public:
	multiple_iterator()
	: base_type()
	{}

	multiple_iterator(const _Iterators CPP0X_EXTEND_PACK iterators)
	: base_type(iterators CPP0X_EXTEND_PACK)
	{}

	template <typename... _Args>
	multiple_iterator(const _Args CPP0X_EXTEND_PACK iterators)
	: base_type(iterators CPP0X_EXTEND_PACK)
	{}

	multiple_iterator(const base_type& other)
	: base_type(other)
	{}

	template <typename... _Args>
	multiple_iterator(const std::tuple<_Args CPP0X_EXTEND_PACK>& other)
	: base_type(other)
	{}

	self_type& operator=(const base_type& other)
	{
		base_type::operator=(other);
		return *this;
	}

	template <typename... _Args>
	self_type& operator=(const std::tuple<_Args CPP0X_EXTEND_PACK>& other)
	{
		base_type::operator=(other);
		return *this;
	}

	self_type& operator+=(std::size_t n)
	{
		tuple::operators::plus_equal<>(_M_base(), n);
		return *this;
	}

	self_type& operator-=(std::size_t n)
	{
		tuple::operators::minus_equal<>(_M_base(), n);
		return *this;
	}

#define __FALCON_MULTIPLE_ITERATOR_COMPARISON(name, op)\
	bool operator op(const self_type& other) const\
	{ return tuple::operators::each_##name<>(_M_base(), other._M_base()); }

	__FALCON_MULTIPLE_ITERATOR_COMPARISON(equal, ==)
	__FALCON_MULTIPLE_ITERATOR_COMPARISON(not_equal, !=)
	__FALCON_MULTIPLE_ITERATOR_COMPARISON(less, <)
	__FALCON_MULTIPLE_ITERATOR_COMPARISON(greater, >)
	__FALCON_MULTIPLE_ITERATOR_COMPARISON(less_equal, <=)
	__FALCON_MULTIPLE_ITERATOR_COMPARISON(greater_equal, >=)

#undef __FALCON_MULTIPLE_ITERATOR_COMPARISON

	FALCON_MEMBER_INCREMENT(self_type, tuple::operators::increment<>(_M_base()))
	FALCON_MEMBER_DECREMENT(self_type, tuple::operators::decrement<>(_M_base()))

public:
	FALCON_MEMBER_GETTER(tuple_type, _M_base, *this)

};

template <typename... _Iterators>
multiple_iterator<_Iterators CPP0X_EXTEND_PACK> make_multiple_iterator(const _Iterators CPP0X_EXTEND_PACK iterators)
{ return multiple_iterator<_Iterators CPP0X_EXTEND_PACK>(iterators CPP0X_EXTEND_PACK); }

template <typename... _Iterators>
multiple_iterator<_Iterators CPP0X_EXTEND_PACK> make_multiple_iterator(const std::tuple<_Iterators CPP0X_EXTEND_PACK> tuple_iterators)
{ return multiple_iterator<_Iterators CPP0X_EXTEND_PACK>(tuple_iterators); }

}

}

namespace std {
	template<size_t idx, typename... _Iterators>
	typename tuple_element<idx, typename falcon::iterator::multiple_iterator<_Iterators CPP0X_EXTEND_PACK>::tuple_type>::type& get(falcon::iterator::multiple_iterator<_Iterators CPP0X_EXTEND_PACK>& m)
	{ return get<idx>(m._M_base()); }

	template<size_t idx, typename... _Iterators>
	typename tuple_element<idx, const typename falcon::iterator::multiple_iterator<_Iterators CPP0X_EXTEND_PACK>::tuple_type>::type& get(const falcon::iterator::multiple_iterator<_Iterators CPP0X_EXTEND_PACK>& m)
	{ return get<idx>(m._M_base()); }

}

#endif