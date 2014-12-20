#ifndef FALCON_IOSTREAM_IOSTREAM_HPP
#define FALCON_IOSTREAM_IOSTREAM_HPP

#include <iostream>
#include <falcon/iostreams/sput.hpp>
#include <falcon/iostreams/sget.hpp>

namespace falcon {
namespace iostreams {

//@{
template<class... Args>
std::istream& scan(Args&... args)
{ return sget(std::cin, args...); }

template<class... Args>
std::ostream& print(const Args&... args)
{ return sput(std::cout, args...); }

template<class... Args>
std::ostream& print_err(const Args&... args)
{ return sput(std::cerr, args...); }

template<class... Args>
std::ostream& print_log(const Args&... args)
{ return sput(std::clog, args...); }

template<class... Args>
std::ostream& println(const Args&... args)
{ return print(args...) << '\n'; }

template<class... Args>
std::ostream& println_err(const Args&... args)
{ return print_err(args...) << '\n'; }

template<class... Args>
std::ostream& println_log(const Args&... args)
{ return print_log(args...) << '\n'; }

template<class... Args>
std::wistream& wscan(Args&... args)
{ return sget(std::wcin, args...); }

template<class... Args>
std::wostream& wprint(const Args&... args)
{ return sput(std::wcout, args...); }

template<class... Args>
std::wostream& wprint_err(const Args&... args)
{ return sput(std::wcerr, args...); }

template<class... Args>
std::wostream& wprint_log(const Args&... args)
{ return sput(std::wclog, args...); }

template<class... Args>
std::wostream& wprintln(const Args&... args)
{ return wprint(args...) << '\n'; }

template<class... Args>
std::wostream& wprintln_err(const Args&... args)
{ return wprint_err(args...) << '\n'; }

template<class... Args>
std::wostream& wprintln_log(const Args&... args)
{ return wprint_log(args...) << '\n'; }
//@}

}
}

#endif
