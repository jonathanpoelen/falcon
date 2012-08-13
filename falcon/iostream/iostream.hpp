#ifndef _FALCON_IOSTREAM_IOSTREAM_HPP
#define _FALCON_IOSTREAM_IOSTREAM_HPP

#include <iostream>
#include <falcon/iostream/put_and_get.hpp>

namespace falcon {

/**
*/
//@{
template<typename... _Args>
std::istream& scan(_Args&... args)
{
	return get<>(std::cin, args...);
}

template<typename... _Args>
std::ostream& print(const _Args&... args)
{
	return put<>(std::cout, args...);
}

template<typename... _Args>
std::ostream& print_err(const _Args&... args)
{
	return put<>(std::cerr, args...);
}

template<typename... _Args>
std::ostream& print_log(const _Args&... args)
{
	return put<>(std::clog, args...);
}

template<typename... _Args>
std::ostream& println(const _Args&... args)
{
	return print<>(args...) << '\n';
}

template<typename... _Args>
std::ostream& println_err(const _Args&... args)
{
	return print_err<>(args...) << '\n';
}

template<typename... _Args>
std::ostream& println_log(const _Args&... args)
{
	return print_log<>(args...) << '\n';
}

template<typename... _Args>
std::wistream& wscan(_Args&... args)
{
	return get<>(std::wcin, args...);
}

template<typename... _Args>
std::wostream& wprint(const _Args&... args)
{
	return put<>(std::wcout, args...);
}

template<typename... _Args>
std::wostream& wprint_err(const _Args&... args)
{
	return put<>(std::wcerr, args...);
}

template<typename... _Args>
std::wostream& wprint_log(const _Args&... args)
{
	return put<>(std::wclog, args...);
}

template<typename... _Args>
std::wostream& wprintln(const _Args&... args)
{
	return wprint<>(args...) << '\n';
}

template<typename... _Args>
std::wostream& wprintln_err(const _Args&... args)
{
	return wprint_err<>(args...) << '\n';
}

template<typename... _Args>
std::wostream& wprintln_log(const _Args&... args)
{
	return wprint_log<>(args...) << '\n';
}

inline basic_ostream_functor<char> cout_functor()
{ return basic_ostream_functor<char>(std::cout); }

inline basic_ostream_functor<wchar_t> wcout_functor()
{ return basic_ostream_functor<wchar_t>(std::wcout); }

inline basic_ostream_functor<char> cerr_functor()
{ return basic_ostream_functor<char>(std::cerr); }

inline basic_ostream_functor<wchar_t> wcerr_functor()
{ return basic_ostream_functor<wchar_t>(std::wcerr); }

inline basic_ostream_functor<char> clog_functor()
{ return basic_ostream_functor<char>(std::clog); }

inline basic_ostream_functor<wchar_t> wclog_functor()
{ return basic_ostream_functor<wchar_t>(std::wclog); }

inline basic_istream_functor<char> cin_functor()
{ return basic_istream_functor<char>(std::cin); }

inline basic_istream_functor<wchar_t> wcin_functor()
{ return basic_istream_functor<wchar_t>(std::wcin); }

//@}

}

#endif
