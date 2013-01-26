#ifndef _FALCON_JAVA_ITERATOR_STEPPING_ITERATOR_HPP
#define _FALCON_JAVA_ITERATOR_STEPPING_ITERATOR_HPP

#include <falcon/java_iterator/java_iterator.hpp>
#include <falcon/java_iterator/is_java_iterator.hpp>

namespace falcon {
namespace java_iterator {

template <typename _Iterator,
	typename _Tp = use_default,
	typename _Reference = use_default>
class stepping_iterator;

namespace detail {
	template <typename _Iterator, typename _Tp, typename _Reference,
		bool _IsJavaIterator = is_java_iterator<_Iterator>::value>
	struct stepping_base
	{
		typedef java_iterator<
			_Iterator,
			use_default,
			_Tp,
			_Reference,
			stepping_iterator<_Iterator, _Tp, _Reference>
		> base;
	};

	template <typename _Iterator, typename _Tp, typename _Reference>
	struct stepping_base<_Iterator, _Tp, _Reference, true>
	{
		typedef typename java_iterator_handler_types<
			stepping_iterator<_Iterator, _Tp, _Reference>,
			_Iterator,
			use_default,
			_Tp,
			_Reference
		>::base base;
	};
}

template <typename _Iterator, typename _Tp, typename _Reference>
class stepping_iterator
: public detail::stepping_base<_Iterator, _Tp, _Reference>::base
{
	friend class java_iterator_core_access;

	typedef typename detail::stepping_base<_Iterator, _Tp, _Reference>::base __base;

public:
	typedef typename __base::iterator_type iterator_type;

private:
	unsigned int _step;

public:
	stepping_iterator(iterator_type x, unsigned int p)
	: __base(x)
	, _step(p)
	{}

	stepping_iterator(iterator_type first, iterator_type last, unsigned int p)
	: __base(first, last)
	, _step(p)
	{}

	template<typename _Container>
	stepping_iterator(_Container& cont, unsigned int p)
	: __base(cont)
	, _step(p)
	{}

	using __base::operator=;

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	stepping_iterator(const stepping_iterator&) = default;
#else
	stepping_iterator(const stepping_iterator& other)
	: __base(other.base_reference())
	, _step(other._step)
	{}
#endif

	void step(unsigned int p)
	{ _step = p; }

	unsigned int step() const
	{ return _step; }

private:
	template<typename _I, typename _C, typename _T, typename _R, typename _P>
	void advance_base(true_type, const java_iterator<_I, _C, _T, _R, _P>&)
	{ advance_base(false_type()); }

	template<typename _Self>
	void advance_base(true_type, const _Self&)
	{
		unsigned int n = _step;
		while (n-- && this->valid())
			__base::advance();
	}

	void advance_base(false_type)
	{
		typedef typename iterator_type::iterator_category tag;
		advance_iterator(tag());
	}

	void advance_iterator(std::random_access_iterator_tag)
	{
		if (_step > this->size())
			this->begin(this->end());
		else
			this->begin(this->begin() + _step);
	}

	template<typename _Tag>
	void advance_iterator(_Tag)
	{ advance_base(true_type(),0); }

protected:
	void advance()
	{
		typedef typename is_java_iterator<_Iterator>::type is_java_iterator;
		advance_base(is_java_iterator());
	}

	void recoil()
	{ std::advance<>(this->base_reference(), -_step); }
};


template <typename _Iterator>
stepping_iterator<_Iterator>
make_stepping_iterator(_Iterator first, _Iterator last, unsigned int p)
{ return stepping_iterator<_Iterator>(first, last, p); }

template <typename _Container>
stepping_iterator<typename _Container::iterator>
make_stepping_iterator(_Container& cont, unsigned int p)
{ return stepping_iterator<typename _Container::iterator>(cont, p); }

}
}

#endif