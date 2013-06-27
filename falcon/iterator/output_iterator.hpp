#ifndef FALCON_ITERATOR_OUTPUT_ITERATOR_HPP
#define FALCON_ITERATOR_OUTPUT_ITERATOR_HPP

#include <iterator>
#include <boost/typeof/typeof.hpp>
#include <falcon/utility/move.hpp>
#include <falcon/c++/extend_parameter.hpp>

namespace falcon {
namespace iterator {

template<typename _Iterator>
class output_iterator_base
: public std::iterator<std::output_iterator_tag, void, void, void, void>
{
	_Iterator& downcast()
	{ return static_cast<_Iterator&>(*this); }

public:
	output_iterator_base()
	{}

	/// Simply returns *this.
	_Iterator& operator*()
	{ return downcast(); }

	/// Simply returns *this.  (This %iterator does not @a move.)
	_Iterator& operator++()
	{ return downcast(); }

	/// Simply returns *this.  (This %iterator does not @a move.)
	_Iterator& operator++(int)
	{ return downcast(); }
};

template<typename>
struct __argument_obj;

template<typename _Result, typename _Functor, typename _FirstArg
	CPP_OTHER_TYPENAME_EXTEND_PARAMETER(_Args)>
struct __argument_obj<_Result(_Functor::*)(_FirstArg
	CPP_USE_OTHER_OPTIONAL_EXTEND_PARAMETER(_Args))>
{ typedef _FirstArg type; };

template<typename _Result, typename _Functor, typename _FirstArg
	CPP_OTHER_TYPENAME_EXTEND_PARAMETER(_Args)>
struct __argument_obj<_Result(_Functor::*)(_FirstArg
	CPP_USE_OTHER_OPTIONAL_EXTEND_PARAMETER(_Args)) const>
{ typedef _FirstArg type; };

template<typename _Functor>
struct __argument_type
: __argument_obj<BOOST_TYPEOF(&_Functor::operator())>
{};

template<typename _Return, typename _FirstArg>
struct __argument_type<_Return(*)(_FirstArg)>
{ typedef _FirstArg type; };

template<typename _Functor, typename _T = typename __argument_type<_Functor>::type>
struct output_iterator
: output_iterator_base<output_iterator<_Functor, _T> >
{
	_Functor m_functor;

public:
	output_iterator()
	: m_functor()
	{}

	output_iterator(_Functor func)
	: m_functor(func)
	{}

	template<typename _U>
	output_iterator(const _U& func)
	: m_functor(func)
	{}

	output_iterator& operator=(_T& x)
	{
		m_functor(x);
		return *this;
	}

	output_iterator& operator=(const _T& x)
	{
		m_functor(x);
		return *this;
	}
};

template<typename _Functor>
output_iterator<_Functor> make_output_iterator(_Functor func)
{ return output_iterator<_Functor>(FALCON_MOVE(func)); }

}}

#endif