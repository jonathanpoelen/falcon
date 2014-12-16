#ifndef FALCON_IOSTREAM_SET_FILE_CONTENTS_HPP
#define FALCON_IOSTREAM_SET_FILE_CONTENTS_HPP

#include <falcon/iostreams/copy.hpp>

#include <fstream> //basic_filebuf

namespace falcon {
namespace iostreams {

/**
 * \brief Write \a s in the file \a name
 *
 * \return -1 if file cannot be open. Otherwise the number of characters to write.
 */
template<class CharT>
std::streamsize
set_file_contents(const char * name, const CharT * s, std::size_t size)
{
  if (size) {
    std::basic_filebuf<CharT> sbout;
    CharT c;
    sbout.pubsetbuf(&c, 1);
    if (sbout.open(name, std::ios_base::out)) {
      return sbout.sputn(s, std::streamsize(size));
    }
    return std::streamsize(-1);
  }
  return 0;
}


/**
 * \brief Write \a sbin in the file \a name
 * \attention \a sbin must be non-null
 *
 * \return -1 if file cannot be open. Otherwise the number of characters to write.
 */
template<class CharT, class Traits>
std::streamsize
set_file_contents(const char * name, std::basic_streambuf<CharT, Traits> * sbin)
{
  std::basic_filebuf<CharT, Traits> sbout;
  CharT buf[4096];
  sbout.pubsetbuf(buf, 4096);
  if (sbout.open(name, std::ios_base::out)) {
    return copy(sbout, *sbin);
  }
  return std::streamsize(-1);
}


template<class CharT>
std::streamsize
set_file_contents(const char * name, const CharT * s)
{ return set_file_contents(name, s, std::char_traits<CharT>::length(s)); }

template<class CharT, class String>
std::streamsize
set_file_contents(const char * name, String const & s, std::size_t size)
{ return set_file_contents(name, s.data(), size); }

template<class CharT, class String>
std::streamsize
set_file_contents(const char * name, String const & s)
{ return set_file_contents(name, s.data(), s.size()); }

template<class CharT, class Traits>
std::streamsize
set_file_contents(const char * name, std::basic_istream<CharT, Traits>& is)
{ return set_file_contents(name, is.rdbuf()); }


template<class CharT>
std::streamsize
set_file_contents(const std::string & name, const CharT * s, std::size_t size)
{ return set_file_contents(name.c_str(), s, size); }

template<class CharT>
std::streamsize
set_file_contents(const std::string & name, const CharT * s)
{ return set_file_contents(name.c_str(), s); }

template<class CharT, class String>
std::streamsize
set_file_contents(const std::string & name, String& s, std::size_t size)
{ return set_file_contents(name.c_str(), s, size); }

template<class CharT, class String>
std::streamsize
set_file_contents(const std::string & name, String& s)
{ return set_file_contents(name.c_str(), s); }

template<class CharT, class Traits>
std::streamsize
set_file_contents(
  const std::string & name
, std::basic_streambuf<CharT, Traits> * sbin)
{ return set_file_contents(name.c_str(), sbin); }

template<class CharT, class Traits>
std::streamsize
set_file_contents(
  const std::string & name
, std::basic_istream<CharT, Traits>& is)
{ return set_file_contents(name.c_str(), is.rdbuf()); }

}
}

#endif
