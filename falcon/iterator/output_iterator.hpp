#ifndef FALCON_ITERATOR_OUTPUT_ITERATOR_HPP
#define FALCON_ITERATOR_OUTPUT_ITERATOR_HPP

#include <iterator>

namespace falcon {
namespace iterator {

template<typename _Self>
struct output_iterator_base
: std::iterator<std::output_iterator_tag, void, void, void, void>
{
	/// Simply returns *this.
	_Self& operator*()
	{ return downcast(); }

	/// Simply returns *this.  (This %iterator does not @a move.)
	_Self& operator++()
	{ return downcast(); }

	/// Simply returns *this.  (This %iterator does not @a move.)
	_Self operator++(int)
	{ return _Self(downcast()); }

private:
	_Self& downcast()
	{ static_cast<_Self&>(*this); }
}
}}

#endif