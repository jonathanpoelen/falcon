#ifndef FALCON_IOSTREAM_COPY_HPP
#define FALCON_IOSTREAM_COPY_HPP

#include <ios>

namespace falcon {
namespace iostreams {

template<
  class CharT
, class Traits>
void
copy(
  std::basic_istream<CharT, Traits> & is
, std::basic_ios<CharT, Traits> & os)
{ is >> os.rdbuf(); }

template<
  class CharT
, class Traits>
void
copy(
  std::basic_istream<CharT, Traits> & is
, std::basic_streambuf<CharT, Traits> * dbuf)
{ is >> dbuf; }

template<
  class CharT
, class Traits>
std::streamsize
copy(
  std::basic_streambuf<CharT, Traits> & sbout
, std::basic_streambuf<CharT, Traits> & sbin
, bool & ineof)
{
  typedef typename std::basic_streambuf<CharT, Traits>::int_type int_type;
  ineof = true;
  std::streamsize n = 0;
  int_type c = sbin->sgetc();
  while (!Traits::eq_int_type(c, Traits::eof())) {
    c = sbout->sputc(Traits::to_char_type(c));
    if (Traits::eq_int_type(c, Traits::eof())) {
      ineof = false;
      break;
    }
    ++n;
    c = sbin->snextc();
  }
  return n;
}

template<
  class CharT
, class Traits>
std::streamsize
copy(
  std::basic_streambuf<CharT, Traits> & sbout
, std::basic_streambuf<CharT, Traits> & sbin)
{
  bool ineof;
  return copy(sbout, sbin, ineof);
}

namespace aux_ {
  template<
    class CharT
  , class Traits>
  std::ios_base::iostate
  copy_streambuf(
    std::basic_streambuf<CharT, Traits> & sbin
  , std::basic_streambuf<CharT, Traits> & sbout)
  {
    std::ios_base::iostate ret = std::ios_base::goodbit;
    bool ineof;
    if (!copy(sbout, sbin, ineof)) {
      ret = std::ios_base::failbit;
      if (ineof) {
        ret |= std::ios_base::eofbit;
      }
    }
    else if (ineof) {
      ret = std::ios_base::eofbit;
    }
    return ret;
  }
}

template<
  class CharT
, class Traits>
std::ios_base::iostate
copy_streambuf(
  std::basic_streambuf<CharT, Traits> * sbin
, std::basic_streambuf<CharT, Traits> * sbout)
{
  return (sbout && sbin)
  ? aux_::copy_streambuf(*sbin, *sbout)
  : std::ios_base::failbit;
}

}
}

#endif
