#ifndef FALCON_INFINITE_HPP
#define FALCON_INFINITE_HPP

#include <cstddef>
#include <falcon/c++/constexpr.hpp>
#include <falcon/preprocessor/incremental.hpp>
#include <falcon/preprocessor/comparison.hpp>
#include <falcon/preprocessor/getter.hpp>

namespace falcon {

template <typename _T>
struct infinite_base
{
	typedef _T value_type;

protected:
	value_type _it, _first, _last;

	typedef infinite_base<_T> self_type;

public:
	CPP_CONSTEXPR infinite_base(const value_type& first, const value_type& last)
	: _it(first)
	, _first(first)
	, _last(last)
	{}

	CPP_CONSTEXPR infinite_base(const value_type& first, const value_type& it, const value_type& last)
	: _it(it)
	, _first(first)
	, _last(last)
	{}

	CPP_CONSTEXPR infinite_base(const self_type& other)
	: _it(other._it)
	, _first(other._first)
	, _last(other._last)
	{}

	self_type& operator=(const self_type& other)
	{
		_it = other._it;
		_first = other._first;
		_last = other._last;
		return *this;
	}

	self_type& operator=(const value_type& it)
	{
		_it = it;
		return *this;
	}

	bool empty() const
	{ return _first == _last; }

	const value_type& begin() const
	{ return _first; }

	const value_type& end() const
	{ return _last; }

	const value_type& current() const
	{ return _it; }

	const value_type& rcurrent() const
	{ return _it; }

	value_type& rcurrent()
	{ return _it; }

	void begin(const value_type& first)
	{ _first = first; }

	void end(const value_type& last)
	{ _last = last; }

	void current(const value_type& it)
	{ _it = it; }

	bool operator==(const self_type& other) const
	{ return _it == other._it; }

	bool operator<(const self_type& other) const
	{ return _it < other._it; }

	FALCON_MEMBER_COMPARISON_OTHER_OPERATOR(self_type)

protected:
	void next()
	{
		if (++_it == _last)
			_it = _first;
	}

	void prev()
	{
		if (_it == _first)
			_it = _last;
		--_it;
	}

private:
	template<typename _U>
	inline void _move_n(_U& n, const _T& d)
	{
		d = _last - _first;
		while (d <= n)
			n -= d;
	}

	template<typename _U>
	inline void _plus(const _U& n)
	{
		_T d = _last - _it;
		if (d <= n)
		{
			_U cn = n - d;
			_move_n(cn, d);
			_it = cn;
		}
		else
			_it += n;
	}

	template<typename _U>
	inline void _minus(_U& n)
	{
		_T d = _it - _first;
		if (d <= n)
		{
			n -= d;
			_move_n(n, d);
			_it = _last - n;
		}
		else
			_it -= n;
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
class infinite : public infinite_base<_T>
{
	typedef infinite_base<_T> base_type;
	typedef infinite<_T> self_type;

public:
	typedef typename base_type::value_type value_type;

public:
	CPP_CONSTEXPR infinite(const value_type& first, const value_type& last)
	: base_type(first, last)
	{}

	CPP_CONSTEXPR infinite(const value_type& first, const value_type& it, const value_type& last)
	: base_type(first, it, last)
	{}

	CPP_CONSTEXPR infinite(const self_type& other)
	: base_type(other)
	{}

	FALCON_MEMBER_GETTER(value_type, operator->, base_type::_it)

	FALCON_CAST_GETTER(value_type, base_type::_it)

	using infinite_base<_T>::operator=;

	FALCON_MEMBER_INCREMENT(self_type, base_type::next())
	FALCON_MEMBER_DECREMENT(self_type, base_type::prev())

#if 0
	using base_type::next;
	using base_type::prev;

	self_type& operator+=(const _T& n)
	{ base_type::plus(n); }

	self_type& operator-=(const _T& n)
	{ base_type::minus(n); }
#endif
};

}

#endif