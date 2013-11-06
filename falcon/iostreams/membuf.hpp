#ifndef FALCON_IOSTREAMS_MEMBUF_HPP
#define FALCON_IOSTREAMS_MEMBUF_HPP

#include <streambuf>
#include <limits>

namespace falcon {

template<typename CharT, typename Traits = std::char_traits<CharT> >
class basic_membuf
: public std::basic_streambuf<CharT, Traits>
{
  typedef std::basic_streambuf<CharT, Traits> __streambuf_base;

public:
  typedef typename __streambuf_base::traits_type traits_type;
  typedef typename __streambuf_base::char_type char_type;
  typedef typename __streambuf_base::int_type int_type;
  typedef typename __streambuf_base::pos_type pos_type;
  typedef typename __streambuf_base::off_type off_type;

public:
  explicit
  basic_membuf(std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
  : __streambuf_base(), m_mode(__mode)
  { }

  basic_membuf(CharT * memory, std::size_t len,
               std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
  : __streambuf_base(), m_mode(__mode)
  { mem(memory, len); }

#if __cplusplus >= 201103L
  basic_membuf(const basic_membuf& other)
  : __streambuf_base(other)
  {}

  basic_membuf & operator=(const basic_membuf& other)
  {
    __streambuf_base::operator=(other);
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
    std::streamsize __ret = -1;
    if (m_mode & std::ios_base::in)
    {
      _update_egptr();
      __ret = this->egptr() - this->gptr();
    }
    return __ret;
  }

  virtual pos_type seekoff(off_type __off, std::ios_base::seekdir __way,
                           std::ios_base::openmode __mode)
  {
    pos_type __ret =  pos_type(off_type(-1));
    bool __testin = (std::ios_base::in & m_mode & __mode) != 0;
    bool __testout = (std::ios_base::out & m_mode & __mode) != 0;
    const bool __testboth = __testin && __testout && __way != std::ios_base::cur;
    __testin &= !(__mode & std::ios_base::out);
    __testout &= !(__mode & std::ios_base::in);

    const char_type* __beg = __testin ? this->eback() : this->pbase();
    if ((__beg || !__off) && (__testin || __testout || __testboth))
    {
      _update_egptr();

      off_type __newoffi = __off;
      off_type __newoffo = __newoffi;
      if (__way == std::ios_base::cur)
      {
        __newoffi += this->gptr() - __beg;
        __newoffo += this->pptr() - __beg;
      }
      else if (__way == std::ios_base::end) {
        __newoffo = __newoffi += this->egptr() - __beg;
      }


      if ((__testin || __testboth)
        && __newoffi >= 0
        && this->egptr() - __beg >= __newoffi)
      {
        std::cout << "__newoffi: " << __newoffi << std::endl;
        this->setg(this->eback(), this->eback() + __newoffi, this->egptr());
        __ret = pos_type(__newoffi);
      }
      if ((__testout || __testboth)
        && __newoffo >= 0
        && this->egptr() - __beg >= __newoffo)
      {
        std::cout << "__newoffo: " << __newoffo << std::endl;
        _pbump(__newoffo);
        __ret = pos_type(__newoffo);
      }
    }
    return __ret;
  }

  virtual pos_type seekpos(pos_type __sp, std::ios_base::openmode __mode)
  {
    pos_type __ret =  pos_type(off_type(-1));
    const bool __testin = (std::ios_base::in & m_mode & __mode) != 0;
    const bool __testout = (std::ios_base::out & m_mode & __mode) != 0;

    const char_type* __beg = __testin ? this->eback() : this->pbase();
    if ((__beg || !off_type(__sp)) && (__testin || __testout))
    {
      _update_egptr();

      const off_type __pos(__sp);
      const bool __testpos = (0 <= __pos && __pos <= this->egptr() - __beg);
      if (__testpos)
      {
        if (__testin) {
          this->setg(this->eback(), this->eback() + __pos, this->egptr());
        }
        if (__testout) {
          _pbump(__pos);
        }
        __ret = __sp;
      }
    }
    return __ret;
  }

  virtual int_type pbackfail(int_type __c)
  {
    int_type __ret = traits_type::eof();
    if (this->eback() < this->gptr())
    {
      // Try to put back __c into input sequence in one of three ways.
      // Order these tests done in is unspecified by the standard.
      const bool __testeof = traits_type::eq_int_type(__c, __ret);
      if (!__testeof)
      {
        const bool __testeq = traits_type::eq(traits_type::
        to_char_type(__c),
        this->gptr()[-1]);
        const bool __testout = m_mode & std::ios_base::out;
        if (__testeq || __testout)
        {
          this->gbump(-1);
          if (!__testeq)
          *this->gptr() = traits_type::to_char_type(__c);
          __ret = __c;
        }
      }
      else
      {
        this->gbump(-1);
        __ret = traits_type::not_eof(__c);
      }
    }
    return __ret;
  }

private:
  void _assign(CharT * beg, CharT * end)
  {
    this->setp(beg, end);
    this->setg(beg, beg, end);
  }

  void _update_egptr()
  {
    const bool __testin = m_mode & std::ios_base::in;
    if (this->pptr() && this->pptr() > this->egptr())
    {
      if (__testin) {
        this->setg(this->eback(), this->gptr(), this->pptr());
      }
      else {
        this->setg(this->pptr(), this->pptr(), this->pptr());
      }
    }
  }

  void _pbump(off_type __off)
  {
    this->setp(this->pbase(), this->epptr());

    while (__off > std::numeric_limits<int>::max())
    {
      this->pbump(std::numeric_limits<int>::max());
      __off -= std::numeric_limits<int>::max();
    }
    this->pbump(static_cast<int>(__off));
  }

  std::ios_base::openmode m_mode;
};

typedef basic_membuf<char> membuf;
typedef basic_membuf<wchar_t> wmembuf;

}

#endif
