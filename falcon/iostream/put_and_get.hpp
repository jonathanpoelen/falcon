#ifndef _FALCON_IOSTREAM_PUT_AND_GET_HPP
#define _FALCON_IOSTREAM_PUT_AND_GET_HPP

#include <iosfwd>
#include <falcon/functional/call_partial_param_loop.hpp>
#include <falcon/functional/placeholder_for_argument.hpp>
#include <falcon/functional/operators.hpp>

namespace falcon {

/**
 *
 */
//@{
template<typename _CharT, typename _Traits, typename... _Args>
std::basic_ostream<_CharT, _Traits>& put(std::basic_ostream<_CharT, _Traits>& os, const _Args&... args)
{
	return call_partial_param_loop<1>(
		placeholder_for_argument<
			0,
			left_shift<
				std::basic_ostream<_CharT, _Traits>&,
				late_parameter_t
			>,
			std::basic_ostream<_CharT, _Traits>&
		>(os),
		args...
	);
}

template<typename _CharT, typename _Traits, typename... _Args>
std::basic_istream<_CharT, _Traits>& get(std::basic_istream<_CharT, _Traits>& is, _Args&... args)
{
	return call_partial_param_loop<1>(
		placeholder_for_argument<
			0,
			right_shift<
				std::basic_istream<_CharT, _Traits>&,
				late_parameter_t
			>,
			std::basic_istream<_CharT, _Traits>&
		>(is),
		args...
	);
}
//@}

template<typename _CharT, typename _Traits = std::char_traits<_CharT>>
class basic_ostream_functor
{
	typedef std::basic_ostream<_CharT, _Traits> __ostream_type;

	__ostream_type& _os;

public:
	basic_ostream_functor(__ostream_type& os)
	: _os(os)
	{}

	basic_ostream_functor(const basic_ostream_functor& other)
	: _os(other._os)
	{}

	template<typename... _Args>
	__ostream_type& operator()(const _Args&... args) const
	{
		return put<>(_os, args...);
	}

	__ostream_type& base()
	{ return _os; }
};

typedef basic_ostream_functor<char> ostream_functor;
typedef basic_ostream_functor<wchar_t> wostream_functor;

template<typename _CharT, typename _Traits>
basic_ostream_functor<_CharT, _Traits> make_ostream_functor(std::basic_ostream<_CharT, _Traits>& os)
{ return basic_ostream_functor<_CharT, _Traits>(os); }

template<typename _CharT, typename _Traits = std::char_traits<_CharT>>
struct basic_istream_functor
{
	typedef std::basic_istream<_CharT, _Traits> __istream_type;

	__istream_type& _is;

public:
	basic_istream_functor(__istream_type& is)
	: _is(is)
	{}

	basic_istream_functor(const basic_istream_functor& other)
	: _is(other._is)
	{}

	template<typename... _Args>
	__istream_type& operator()(_Args&... args) const
	{
		return get<>(_is, args...);
	}

	__istream_type& base()
	{ return _is; }
};

typedef basic_istream_functor<char> istream_functor;
typedef basic_istream_functor<wchar_t> wistream_functor;

template<typename _CharT, typename _Traits>
basic_istream_functor<_CharT, _Traits> make_istream_functor(std::basic_istream<_CharT, _Traits>& is)
{ return basic_istream_functor<_CharT, _Traits>(is); }

}

#endif