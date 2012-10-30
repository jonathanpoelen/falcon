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
	CPP_CONSTEXPR infinite_base(const value_type& first, const value_type& last)
	: _current(first)
	, _first(first)
	, _last(last)
	{}

	CPP_CONSTEXPR infinite_base(const value_type& first, const value_type& x, const value_type& last)
	: _current(x)
	, _first(first)
	, _last(last)
	{}

	void current(const value_type& x)
	{ _current = x; }

	const value_type& begin() const
	{ return _first; }

	const value_type& end() const
	{ return _last; }

	void begin(const value_type& first)
	{ _first = first; }

	void end(const value_type& last)
	{ _last = last; }

protected:
	const value_type& current() const
	{ return _current; }

	const value_type& rcurrent() const
	{ return _current; }

	value_type& rcurrent()
	{ return _current; }

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

private:
	inline void _move_n(_T& n, const _T& d)
	{
		d = _last - _first;
		while (d <= n)
			n -= d;
	}

	inline void _plus(const _T& n)
	{
		_T d = _last - _current;
		if (d <= n)
		{
			_T cn = static_cast<_T>(n - d);
			_move_n(cn, d);
			_current = cn;
		}
		else
			_current += n;
	}

	inline void _minus(_T& n)
	{
		_T d = _current - _first;
		if (d <= n)
		{
			n -= d;
			_move_n(n, d);
			_current = static_cast<_T>(_last - n);
		}
		else
			_current -= n;
	}

protected:
	void plus(const _T& n)
	{ _plus(n); }

	void minus(const _T& n)
	{
		_T cn = -n;
		_minus(cn);
	}

	void next(std::size_t n)
	{
		if (n)
			_plus(n);
	}

	void prev(std::size_t n)
	{
		if (!n)
			return;
		_minus(n);
	}
};


template <typename _T>
struct infinite : public infinite_base<_T>
{
private:
	typedef infinite_base<_T> base_type;
	typedef infinite<_T> self_type;

public:
	typedef typename base_type::value_type value_type;

public:
	CPP_CONSTEXPR infinite(const value_type& first, const value_type& last)
	: base_type(first, last)
	{}

	CPP_CONSTEXPR infinite(const value_type& first, const value_type& x, const value_type& last)
	: base_type(first, x, last)
	{}

	FALCON_MEMBER_GETTER(value_type, operator->, base_type::_current)

	operator const value_type &() const
	{ return current(); }

	using base_type::current;
	using base_type::rcurrent;
	using base_type::next;
	using base_type::prev;

	FALCON_MEMBER_INCREMENT(infinite<_T>, next())
	FALCON_MEMBER_DECREMENT(infinite<_T>, prev())
};

}

#endif