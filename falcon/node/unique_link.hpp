#ifndef _FALCON_NODE_UNIQUE_LINK_HPP
#define _FALCON_NODE_UNIQUE_LINK_HPP

#include <falcon/c++/constexpr.hpp>

namespace falcon { namespace node {

template<typename _Next>
struct unique_link
{
	typedef unique_link<_Next> self_type;
	typedef _Next next_type;
	typedef next_type value_type;

	next_type next;

	CPP_CONSTEXPR unique_link(const next_type& __next)
	: next(__next)
	{}

	bool is_superposed(const self_type& other) const
	{ return is_superposed<_Next>(other); }

	template<typename __Next>
	bool is_superposed(const unique_link<_Next>& other) const
	{
		return other.next == next;
	}

	void set(const next_type& __next)
	{
		next = __next;
	}

	void set(const self_type& other)
	{
		next = other.next;
	}
};

template<typename _Next, typename _Right>
bool operator==(const unique_link<_Next>& a, const unique_link<_Next>& b)
{ return a.is_superposed(b); }

template<typename _Next, typename _Right>
bool operator!=(const unique_link<_Next>& a, const unique_link<_Next>& b)
{ return !(a == b); }


template<typename _Next>
class restrict_unique_link
{
	typedef unique_link<_Next> link_type;
public:
	typedef restrict_unique_link<_Next> self_type;
	typedef typename link_type::next_type next_type;
	typedef typename link_type::value_type value_type;

protected:
	unique_link<_Next> _unique_link;

public:
	CPP_CONSTEXPR restrict_unique_link()
	: _unique_link()
	{}

	CPP_CONSTEXPR restrict_unique_link(const link_type& unique_link)
	: _unique_link(unique_link)
	{}

	CPP_CONSTEXPR restrict_unique_link(const next_type& __next)
	: _unique_link(__next)
	{}

	CPP_CONSTEXPR restrict_unique_link(const self_type& other)
	: _unique_link(other._unique_link)
	{}

	self_type& operator=(const self_type& other)
	{
		_unique_link = other._unique_link;
		return *this;
	}

	self_type& operator=(const link_type& other)
	{
		_unique_link.set(other);
		return *this;
	}

	const next_type& next() const
	{ return _unique_link.next; }

	bool is_superposed(const self_type& other) const
	{ return _unique_link.is_superposed(other._unique_link); }

	bool is_superposed(const link_type& other) const
	{ return _unique_link.is_superposed(other); }

	template<typename __Next>
	bool is_superposed(const restrict_unique_link<_Next>& other) const
	{ return _unique_link.is_superposed(other._unique_link); }

	template<typename __Next>
	bool is_superposed(const unique_link<_Next>& other) const
	{ return _unique_link.is_superposed(other); }
};

template<typename _Next, typename _Right>
bool operator==(const restrict_unique_link<_Next>& a, const restrict_unique_link<_Next>& b)
{ return a.is_superposed(b); }

template<typename _Next, typename _Right>
bool operator!=(const restrict_unique_link<_Next>& a, const restrict_unique_link<_Next>& b)
{ return !(a == b); }

} }

#endif
