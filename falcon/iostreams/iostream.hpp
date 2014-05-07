#ifndef FALCON_IOSTREAM_IOSTREAM_HPP
#define FALCON_IOSTREAM_IOSTREAM_HPP

#include <iostream>
#include <falcon/iostreams/put.hpp>
#include <falcon/iostreams/get.hpp>

namespace falcon {
namespace iostreams {

//@{
template<class... Args>
std::istream& scan(Args&... args)
{
  return get(std::cin, args...);
}

template<class... Args>
std::ostream& print(const Args&... args)
{
  return put(std::cout, args...);
}

template<class... Args>
std::ostream& print_err(const Args&... args)
{
  return put(std::cerr, args...);
}

template<class... Args>
std::ostream& print_log(const Args&... args)
{
  return put(std::clog, args...);
}

template<class... Args>
std::ostream& println(const Args&... args)
{
  return print(args...) << '\n';
}

template<class... Args>
std::ostream& println_err(const Args&... args)
{
  return print_err(args...) << '\n';
}

template<class... Args>
std::ostream& println_log(const Args&... args)
{
  return print_log(args...) << '\n';
}

template<class... Args>
std::wistream& wscan(Args&... args)
{
  return get(std::wcin, args...);
}

template<class... Args>
std::wostream& wprint(const Args&... args)
{
  return put(std::wcout, args...);
}

template<class... Args>
std::wostream& wprint_err(const Args&... args)
{
  return put(std::wcerr, args...);
}

template<class... Args>
std::wostream& wprint_log(const Args&... args)
{
  return put(std::wclog, args...);
}

template<class... Args>
std::wostream& wprintln(const Args&... args)
{
  return wprint(args...) << '\n';
}

template<class... Args>
std::wostream& wprintln_err(const Args&... args)
{
  return wprint_err(args...) << '\n';
}

template<class... Args>
std::wostream& wprintln_log(const Args&... args)
{
  return wprint_log(args...) << '\n';
}

inline basic_ostream_function<char> cout_function() noexcept
{ return basic_ostream_function<char>(std::cout); }

inline basic_ostream_function<wchar_t> wcout_function() noexcept
{ return basic_ostream_function<wchar_t>(std::wcout); }

inline basic_ostream_function<char> cerr_function() noexcept
{ return basic_ostream_function<char>(std::cerr); }

inline basic_ostream_function<wchar_t> wcerr_function() noexcept
{ return basic_ostream_function<wchar_t>(std::wcerr); }

inline basic_ostream_function<char> clog_function() noexcept
{ return basic_ostream_function<char>(std::clog); }

inline basic_ostream_function<wchar_t> wclog_function() noexcept
{ return basic_ostream_function<wchar_t>(std::wclog); }

inline basic_istream_function<char> cin_function() noexcept
{ return basic_istream_function<char>(std::cin); }

inline basic_istream_function<wchar_t> wcin_function() noexcept
{ return basic_istream_function<wchar_t>(std::wcin); }

//@}

}
}

#endif
