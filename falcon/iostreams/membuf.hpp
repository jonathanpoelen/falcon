#ifndef FALCON_IOSTREAMS_MEMBUF_HPP
#define FALCON_IOSTREAMS_MEMBUF_HPP

#include <streambuf>
#include <limits>

namespace falcon {
namespace iostreams {

template<typename CharT, typename Traits = std::char_traits<CharT> >
class basic_membuf
: public std::basic_streambuf<CharT, Traits>
{
  typedef std::basic_streambuf<CharT, Traits> streambuf_base;

public:
  typedef typename streambuf_base::traits_type traits_type;
  typedef typename streambuf_base::char_type char_type;
  typedef typename streambuf_base::int_type int_type;
  typedef typename streambuf_base::pos_type pos_type;
  typedef typename streambuf_base::off_type off_type;

public:
  explicit
  basic_membuf(std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out)
  : streambuf_base(), m_mode(mode)
  { }

  basic_membuf(CharT * memory, std::size_t len,
               std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out)
  : streambuf_base(), m_mode(mode)
  { mem(memory, len); }

#if cplusplus >= 201103L
  basic_membuf(const basic_membuf& other)
  : streambuf_base(other)
  {}

  basic_membuf & operator=(const basic_membuf& other)
  {
    streambuf_base::operator=(other);
    return *this;
  }
#endif

  void mem(char_type* s, std::streamsize n)
  { _assign(s, s+n); }

  std::size_t size()
  { return this->egptr() - this->eback(); }

protected:
  virtual basic_membuf* setbuf(char_type* s, std::streamsize n)
  {
    _assign(s, s+n);
    return this;
  }

  virtual std::streamsize showmanyc()
  {
    std::streamsize ret = -1;
    if (m_mode & std::ios_base::in)
    {
      _update_egptr();
      ret = this->egptr() - this->gptr();
    }
    return ret;
  }

  virtual pos_type seekoff(off_type off, std::ios_base::seekdir way,
                           std::ios_base::openmode mode)
  {
    pos_type ret =  pos_type(off_type(-1));
    bool testin = (std::ios_base::in & m_mode & mode) != 0;
    bool testout = (std::ios_base::out & m_mode & mode) != 0;
    const bool testboth = testin && testout && way != std::ios_base::cur;
    testin &= !(mode & std::ios_base::out);
    testout &= !(mode & std::ios_base::in);

    const char_type* beg = testin ? this->eback() : this->pbase();
    if ((beg || !off) && (testin || testout || testboth))
    {
      _update_egptr();

      off_type newoffi = off;
      off_type newoffo = newoffi;
      if (way == std::ios_base::cur)
      {
        newoffi += this->gptr() - beg;
        newoffo += this->pptr() - beg;
      }
      else if (way == std::ios_base::end) {
        newoffo = newoffi += this->egptr() - beg;
      }

      if ((testin || testboth)
        && newoffi >= 0
        && this->egptr() - beg >= newoffi)
      {
        this->setg(this->eback(), this->eback() + newoffi, this->egptr());
        ret = pos_type(newoffi);
      }
      if ((testout || testboth)
        && newoffo >= 0
        && this->egptr() - beg >= newoffo)
      {
        _pbump(newoffo);
        ret = pos_type(newoffo);
      }
    }
    return ret;
  }

  virtual pos_type seekpos(pos_type sp, std::ios_base::openmode mode)
  {
    pos_type ret =  pos_type(off_type(-1));
    const bool testin = (std::ios_base::in & m_mode & mode) != 0;
    const bool testout = (std::ios_base::out & m_mode & mode) != 0;

    const char_type* beg = testin ? this->eback() : this->pbase();
    if ((beg || !off_type(sp)) && (testin || testout))
    {
      _update_egptr();

      const off_type pos(sp);
      const bool testpos = (0 <= pos && pos <= this->egptr() - beg);
      if (testpos)
      {
        if (testin) {
          this->setg(this->eback(), this->eback() + pos, this->egptr());
        }
        if (testout) {
          _pbump(pos);
        }
        ret = sp;
      }
    }
    return ret;
  }

  virtual int_type pbackfail(int_type c)
  {
    int_type ret = traits_type::eof();
    if (this->eback() < this->gptr())
    {
      // Try to put back c into input sequence in one of three ways.
      // Order these tests done in is unspecified by the standard.
      const bool testeof = traits_type::eq_int_type(c, ret);
      if (!testeof)
      {
        const bool testeq = traits_type::eq(traits_type::
        to_char_type(c),
        this->gptr()[-1]);
        const bool testout = m_mode & std::ios_base::out;
        if (testeq || testout)
        {
          this->gbump(-1);
          if (!testeq)
          *this->gptr() = traits_type::to_char_type(c);
          ret = c;
        }
      }
      else
      {
        this->gbump(-1);
        ret = traits_type::not_eof(c);
      }
    }
    return ret;
  }

private:
  void _assign(CharT * beg, CharT * end)
  {
    this->setp(beg, end);
    this->setg(beg, beg, end);
  }

  void _update_egptr()
  {
    const bool testin = m_mode & std::ios_base::in;
    if (this->pptr() && this->pptr() > this->egptr())
    {
      if (testin) {
        this->setg(this->eback(), this->gptr(), this->pptr());
      }
      else {
        this->setg(this->pptr(), this->pptr(), this->pptr());
      }
    }
  }

  void _pbump(off_type off)
  {
    this->setp(this->pbase(), this->epptr());

    while (off > std::numeric_limits<int>::max())
    {
      this->pbump(std::numeric_limits<int>::max());
      off -= std::numeric_limits<int>::max();
    }
    this->pbump(static_cast<int>(off));
  }

  std::ios_base::openmode m_mode;
};

typedef basic_membuf<char> membuf;
typedef basic_membuf<wchar_t> wmembuf;

}
}

#endif
