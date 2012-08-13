#ifndef _FALCON_ITERATOR_NEXTER_ITERATOR_HPP
#define _FALCON_ITERATOR_NEXTER_ITERATOR_HPP

#include <falcon/preprocessor/incremental.hpp>
#include <falcon/preprocessor/comparison.hpp>
#include <falcon/preprocessor/getter.hpp>
#include <falcon/iterator/detail/to_iterator_traits.hpp>
#include <falcon/c++/constexpr.hpp>

namespace falcon {

namespace iterator {

template <typename _Iterator, typename _Nexter>
class nexter_iterator
{
	typedef nexter_iterator<_Iterator, _Nexter> self_type;
	typedef typename detail::to_iterator_traits<_Iterator>::type iterator_traits;

public:
	typedef _Nexter nexter_type;
	typedef _Iterator iterator_base;
	typedef typename iterator_traits::value_type value_type;
	//typedef typename iterator_traits::pointer pointer;
	typedef iterator_base pointer;
	typedef typename iterator_traits::reference reference;
	typedef typename iterator_traits::difference_type difference_type;
	typedef typename iterator_traits::iterator_category iterator_category;

private:
	iterator_base _it;
	nexter_type _nexter;

public:
	CPP_CONSTEXPR nexter_iterator(const nexter_type& nexter)
	: _it()
	, _nexter(nexter)
	{}

	CPP_CONSTEXPR nexter_iterator(const iterator_base& it)
	: _it(it)
	, _nexter()
	{}

	CPP_CONSTEXPR nexter_iterator(const iterator_base& it, const nexter_type& nexter)
	: _it(it)
	, _nexter(nexter)
	{}

// 	CPP_CONSTEXPR nexter_iterator(const nexter_type& nexter, const iterator_base& it)
// 	: _it(it)
// 	, _nexter(nexter)
// 	{}

	CPP_CONSTEXPR nexter_iterator(const self_type& other)
	: _it(other._it)
	, _nexter(other._nexter)
	{}

	self_type& operator=(const self_type& oher)
	{
		_it = oher._it;
		_nexter = oher._nexter;
		return *this;
	}

	self_type& operator=(const iterator_base& it)
	{
		_it = it;
		return *this;
	}

	self_type& operator=(const nexter_type& nexter)
	{
		_nexter = nexter;
		return *this;
	}

	//FALCON_MEMBER_GETTER(iterator, get, _it)
	FALCON_MEMBER_GETTER(reference, operator*, *_it)
	FALCON_MEMBER_GETTER_POINTER(value_type, operator->, *_it)

	/*const nexter_type& nexter() const
	{ return _nexter; }
	nexter_type& nexter()
	{ return _nexter; }

	void nexter(const nexter_type& nexter)
	{ _nexter = nexter; }*/

	FALCON_MEMBER_INCREMENT(self_type, /*_it = */_nexter(_it))

	FALCON_MEMBER_COMPARISON_ALL_OPERATOR(iterator_base, _it)
	FALCON_MEMBER_COMPARISON2_ALL_OPERATOR(self_type, _it, other._it)

	iterator_base& base()
	{ return _it; }
	CPP_CONSTEXPR const iterator_base& base() const
	{ return _it; }

};

template <typename _Iterator, typename _Nexter>
CPP_CONSTEXPR typename nexter_iterator<_Iterator, _Nexter>::difference_type operator-(const nexter_iterator<_Iterator, _Nexter>& a, const nexter_iterator<_Iterator, _Nexter>& b)
{ return a.base() - b.base(); }

template <typename _Iterator, typename _Nexter>
CPP_CONSTEXPR nexter_iterator<_Iterator, _Nexter> make_nexter_iterator(const _Iterator& begin, const _Nexter& nexter) {
	return nexter_iterator<_Iterator, _Nexter>(begin, nexter);
}

}

}

#endif