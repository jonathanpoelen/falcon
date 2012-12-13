#ifndef FALCON_ITERATOR_OUTPUT_ITERATOR_HPP
#define FALCON_ITERATOR_OUTPUT_ITERATOR_HPP

#include <iterator>

namespace falcon {
namespace iterator {

typedef std::iterator<std::output_iterator_tag, void, void, void, void> output_iterator_base;

template<typename _Iterator, typename _T>
struct output_iterator
: output_iterator_base
{
	typedef _Iterator iterator_type;

private:
	iterator_type _M_current;

public:
	output_iterator()
	: _M_current()
	{}

	output_iterator(iterator_type x)
	: _M_current(x)
	{}

	output_iterator(const output_iterator& other)
	: _M_current(other._M_current)
	{}

	template<typename _U>
	output_iterator(const _U& x)
	: _M_current(x)
	{}

	template<typename _U>
	output_iterator(_U& x)
	: _M_current(x)
	{}

	output_iterator(const _T& x)
	{
		*_M_current = x;
		return *this;
	}

	/// Simply returns *this.
	output_iterator& operator*()
	{ return *this; }

	/// Simply returns *this.  (This %iterator does not @a move.)
	output_iterator& operator++()
	{ return *this; }

	/// Simply returns *this.  (This %iterator does not @a move.)
	output_iterator& operator++(int)
	{ return *this; }
};

}}

#endif