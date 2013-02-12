#ifndef FALCON_ITERATOR_ZONE_ITERATOR_HPP
#define FALCON_ITERATOR_ZONE_ITERATOR_HPP

#include <falcon/iterator/iterator_handler.hpp>

namespace falcon {
namespace iterator {

template <typename _Iterator, typename _Tp = use_default,
	typename _Category = use_default, typename _Reference = use_default,
	typename _Distance = use_default, typename _Pointer = use_default
>
class zone_iterator;

namespace detail
{
	template <typename _Iterator, typename _Tp, typename _Category,
		typename _Reference, typename _Distance, typename _Pointer>
	struct zone_base
	{
		typedef typename iterator_handler_types<
			zone_iterator<_Iterator, _Tp, _Category, _Reference, _Distance, _Pointer>,
			_Iterator,
			_Category,
			_Tp,
			_Distance,
			_Pointer,
			_Reference
		>::base base;
	};
}

template <typename _Iterator, typename _Tp, typename _Category,
	typename _Reference, typename _Distance, typename _Pointer>
class zone_iterator
: public detail::zone_base<_Iterator, _Tp, _Category, _Reference, _Distance, _Pointer>::base
{
	friend iterator_core_access;

	typedef typename detail::zone_base<_Iterator, _Tp, _Category, _Reference, _Distance, _Pointer>::base __base;

public:
	typedef typename __base::iterator_type iterator_type;
	typedef typename __base::difference_type difference_type;

private:
	iterator_type m_end;
	difference_type m_n;
	difference_type m_step;

public:
	explicit zone_iterator(iterator_type x)
	: __base(x)
	, m_end()
	, m_n()
	, m_step()
	{}

	zone_iterator(iterator_type x,
								difference_type __width, difference_type __sub_width)
	: __base(x)
	, m_end(x + __width - __sub_width)
	, m_n(__sub_width - 1)
	, m_step(__width - __sub_width + 1)
	{}

	zone_iterator(iterator_type x, iterator_type end,
								difference_type __width, difference_type __sub_width)
	: __base(x)
	, m_end(end)
	, m_n(__sub_width - 1)
	, m_step(__width - __sub_width + 1)
	{}

	zone_iterator(const zone_iterator& other)
	: __base(other)
	, m_end(other.m_end)
	, m_n(other.m_n)
	, m_step(other.m_step)
	{}

	using __base::operator=;
#ifdef __GXX_EXPERIMENTAL_CXX0X__
	zone_iterator& operator=(const zone_iterator&) = default;
#else
	zone_iterator& operator=(const zone_iterator& other)
	{
		this->base_reference() = other.base_reference();
		m_end = other.m_end;
		m_n = other.m_n;
		m_step = other.m_step;
		return *this;
	}
#endif

	difference_type real_width() const
	{ return m_step + m_n; }

	difference_type width() const
	{ return m_n + 1; }

protected:
	void increment()
	{
		if (this->base_reference() == m_end)
		{
			this->base_reference() = m_end + m_step;
			m_end = this->base_reference() + m_n;
		}
		else
			++this->base_reference();
	}

	void decrement()
	{
		if (this->base_reference() == m_end - m_n)
		{
			m_end -= m_step;
			this->base_reference() = m_end;
		}
		else
			--this->base_reference();
	}

	void advance(difference_type n)
	{
		if (n < 0)
			_recoil(-n);
		else
			_advance(n);
	}

	void recoil(difference_type n)
	{
		if (n < 0)
			_advance(-n);
		else
			_recoil(n);
	}

	difference_type difference(const zone_iterator& other) const
	{
		difference_type d = this->base_reference() - other.base_reference();
		if (other.m_end != m_end)
			d -= d / (m_n + m_step) * (m_step-1);
		return d;
	}

private:
	void _advance(difference_type n)
	{
		difference_type d = m_end - this->base_reference();
		if (n > d)
		{
			n -= d + 1;
			difference_type t = n / (m_n + 1) * (m_step + m_n) + m_step;
			this->base_reference() = m_end + (t + n % (m_n + 1));
			m_end += t + m_n;
		}
		else
			this->base_reference() += n;
	}

	void _recoil(difference_type n)
	{
		difference_type d = this->base_reference() - (m_end - m_n);
		if (n > d)
		{
			n -= d + 1;
			difference_type t = n / (m_n + 1) * (m_step + m_n) + m_step + m_n;
			this->base_reference() = m_end - (t + n % (m_n + 1));
			m_end -= t;
		}
		else
			this->base_reference() -= n;
	}
};

template <typename _Iterator>
zone_iterator<_Iterator>
make_zone_iterator(_Iterator x,
									 typename zone_iterator<_Iterator>::difference_type width,
									 typename zone_iterator<_Iterator>::difference_type sub_width)
{ return zone_iterator<_Iterator>(x, width, sub_width); }

template <typename _Iterator>
zone_iterator<_Iterator>
make_zone_iterator(_Iterator x, _Iterator end,
									 typename zone_iterator<_Iterator>::difference_type width,
									 typename zone_iterator<_Iterator>::difference_type sub_width)
{ return zone_iterator<_Iterator>(x, end, width, sub_width); }

}}

#endif