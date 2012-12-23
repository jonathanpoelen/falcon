#ifndef FALCON_INFINITE_HPP
#define FALCON_INFINITE_HPP

#include <cstddef>
#include <falcon/c++/constexpr.hpp>
#include <falcon/preprocessor/incremental.hpp>
#include <falcon/preprocessor/getter.hpp>

namespace falcon {

template <typename _T>
struct infinite_base
{
	typedef _T value_type;

protected:
	value_type _current, _first, _last;


public:
	CPP_CONSTEXPR infinite_base(const value_type& x, const value_type& last)
	: _current(x)
	, _first()
	, _last(last)
	{}

	CPP_CONSTEXPR infinite_base(const value_type& first, const value_type& x, const value_type& last)
	: _current(x)
	, _first(first)
	, _last(last)
	{}

	void set(const value_type& x)
	{ _current = x; }

	const value_type& get() const
	{ return _current; }

	const value_type& begin() const
	{ return _first; }

	const value_type& end() const
	{ return _last; }

	void begin(const value_type& first)
	{ _first = first; }

	void end(const value_type& last)
	{ _last = last; }

	void next()
	{
		if (++_current == _last)
			_current = _first;
	}

	void prev()
	{
		if (_current == _first)
			_current = _last;
		--_current;
	}

protected:
	const value_type& get_by_reference() const
	{ return _current; }

	value_type& get_by_reference()
	{ return _current; }

private:
	template<typename _Distance>
	void _next(_Distance n)
	{
		_Distance d = _last - _current;
		if (n < d)
			_current += n;
		else
			_current = _first + (n - d) % (_last - _first);
	}

	template<typename _Distance>
	void _prev(_Distance n)
	{
		_Distance d = _current - _first;
		if (n <= d)
			_current -= n;
		else
			_current = _last - (n - d) % (_last - _first);
	}

protected:
	template<typename _Distance>
	void add(_Distance n)
	{
		if (n < 0)
			_prev(-n);
		if (n > 0)
			_next(n);
	}

	template<typename _Distance>
	void minus(_Distance n)
	{
		if (n < 0)
			_next(n);
		if (n > 0)
			_prev(-n);
	}

	void next(std::size_t n)
	{ _next(n); }

	void prev(std::size_t n)
	{ _prev(n); }
};


template <typename _T>
struct infinite : public infinite_base<_T>
{
private:
	typedef infinite_base<_T> base_type;

public:
	typedef typename base_type::value_type value_type;

public:
	CPP_CONSTEXPR infinite(const value_type& x, const value_type& last)
	: base_type(x, last)
	{}

	CPP_CONSTEXPR infinite(const value_type& first, const value_type& x, const value_type& last)
	: base_type(first, x, last)
	{}

	FALCON_MEMBER_GETTER(value_type, operator->, get())

	operator const value_type &() const
	{ return get(); }

	using base_type::get;
	using base_type::get_by_reference;
	using base_type::next;
	using base_type::prev;

	FALCON_MEMBER_INCREMENT(infinite, next())
	FALCON_MEMBER_DECREMENT(infinite, prev())

	infinite& operator+=(const _T& n)
	{
		this->add(n);
		return *this;
	}

	infinite& operator-=(const _T& n)
	{
		this->minus(n);
		return *this;
	}

	infinite& operator+=(std::size_t n)
	{
		next(n);
		return *this;
	}

	infinite& operator-=(std::size_t n)
	{
		prev(n);
		return *this;
	}
};

}

#endif