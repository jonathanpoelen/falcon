#ifndef FALCON_IOSTREAMULTIBUF_HPP
#define FALCON_IOSTREAMULTIBUF_HPP

#include <ios>
#include <streambuf>
#include <vector>

namespace falcon {

template<typename CharT, typename Traits>
class basic_streambuf_generator
{
public:
  typedef std::basic_streambuf<CharT, Traits> streambuf_type;
  typedef streambuf_type* value_type;

  std::vector<streambuf_type *> vector;
  std::size_t position;

public:
#if __cplusplus >= 201103L
  basic_streambuf_generator() = default;
  basic_streambuf_generator(const basic_streambuf_generator&) = default;
  basic_streambuf_generator(basic_streambuf_generator&&) = default;

  basic_streambuf_generator(std::initializer_list<streambuf_type*> l)
  : vector(l)
  , position(0)
  {}
#else
  basic_streambuf_generator()
  : vector()
  , position(0)
  {}

  basic_streambuf_generator(const basic_streambuf_generator& other)
  : vector(other.vector)
  , position(0)
  {}
#endif

  template<typename InputIterator>
  basic_streambuf_generator(InputIterator first, InputIterator last)
  : vector(first, last)
  , position(0)
  {}

  streambuf_type * operator()()
  {
    if (position < vector.size()) {
      return vector[position++];
    }
    return 0;
  }

  void push(streambuf_type * buf)
  { vector.push_back(buf); }

  template<typename InputIterator>
  void push(InputIterator first, InputIterator last)
  { vector.insert(vector.end(), first, last); }
};


template<typename CharT, typename Traits = std::char_traits<CharT>,
  typename Generator = basic_streambuf_generator<CharT, Traits> >
class basic_multibuf
: public std::basic_streambuf<CharT, Traits>
{
  typedef std::basic_streambuf<CharT, Traits> streambuf_type;

public:
  typedef typename streambuf_type::char_type char_type;
  typedef typename streambuf_type::traits_type traits_type;
  typedef typename streambuf_type::int_type int_type;
  typedef typename streambuf_type::pos_type pos_type;
  typedef typename streambuf_type::off_type off_type;
  typedef Generator streambuf_generator;

public:
  basic_multibuf()
  : streambuf_type()
  , m_gen()
  , m_sb(0)
  , m_set_loc(0)
  {}

  basic_multibuf(const streambuf_generator& sbs)
  : streambuf_type()
  , m_gen(sbs)
  , m_sb(m_gen())
  , m_set_loc(0)
  {}

#if __cplusplus >= 201103L
  basic_multibuf(streambuf_generator&& sbs)
  : streambuf_type()
  , m_gen(std::forward<streambuf_generator>(sbs))
  , m_sb(m_gen())
  , m_set_loc(0)
  {}

#endif

  virtual ~basic_multibuf()
  {}

  streambuf_generator& generator_streambuf()
  { return m_gen; }

  const streambuf_generator& generator_streambuf() const
  { return m_gen; }

  void generator_streambuf(const streambuf_generator& gen)
  { m_gen = gen; }

#if __cplusplus >= 201103L
void generator_streambuf(streambuf_generator&& gen)
  { m_gen = std::move(gen); }
#endif

  streambuf_type * rdbuf() const
  { return m_sb; }

  streambuf_type * rdbuf(streambuf_type * sb)
  {
    streambuf_type * ret = m_sb;
    m_sb = sb;
    return m_sb;
  }

protected:
  virtual void
  imbue(const std::locale& loc)
  {
    m_set_loc = true;
    streambuf_type::imbue(loc);
    if (m_sb)
      m_sb->pubimbue(loc);
  }

  virtual basic_multibuf*
  setbuf(char_type* s, std::streamsize n)
  {
    if (m_sb)
      m_sb->pubsetbuf(s, n);
    return this;
  }

  virtual pos_type
  seekoff(off_type off, std::ios_base::seekdir way,
          std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out)
  { return m_sb ? m_sb->pubseekoff(off, way, mode) : pos_type(off_type(-1)); }

  virtual pos_type
  seekpos(pos_type pos,
          std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out)
  { return m_sb ? m_sb->pubseekpos(pos, mode) : pos_type(off_type(-1)); }

  virtual int
  sync()
  { return m_sb ? m_sb->pubsync() : -1; }

  virtual std::streamsize
  showmanyc()
  { return m_sb ? m_sb->in_avail() : -1; }

  virtual std::streamsize
  xsgetn(char_type* s, std::streamsize n)
  {
    std::streamsize ret = 0;
    while (m_sb && n) {
      std::streamsize tmp = m_sb->sgetn(s, n);
      ret += tmp;
      if (tmp != n)
        next_stream();
      s += tmp;
      n -= tmp;
    }
    this->setg(0,0,0);
    return ret;
  }

  virtual int_type
  underflow()
  {
      int_type ret = traits_type::eof();
      while (m_sb && traits_type::eq_int_type(ret = m_sb->sbumpc(), traits_type::eof()))
        next_stream();
      ic = traits_type::to_char_type(ret);
      this->setg(&ic, &ic, &ic + 1);
      return ret;
  }

  virtual int_type
  pbackfail(int_type c = traits_type::eof())
  {
      return m_sb
      ? m_sb->sputbackc(traits_type::to_char_type(c))
      : traits_type::eof();
  }

  virtual std::streamsize
  xsputn(const char_type* s, std::streamsize n)
  {
    std::streamsize ret = 0;
    while (m_sb && n) {
      std::streamsize tmp = m_sb->sputn(s, n);
      ret += tmp;
      if (tmp != n)
        next_stream();
      s += tmp;
      n -= tmp;
    }
    this->setp(0,0);
    return ret;
  }

  virtual int_type
  overflow(int_type c = traits_type::eof())
  {
    int_type ret = traits_type::eof();
    while (m_sb && traits_type::eq_int_type(ret = m_sb->sputc(traits_type::to_char_type(c)), traits_type::eof()))
      next_stream();
    oc = traits_type::to_char_type(ret);
    this->setp(&oc, &oc + 1);
    return ret;
  }

  bool next_stream()
  {
    m_sb = m_gen();
    if (m_set_loc && m_sb)
      m_sb->pubimbue(streambuf_type::getloc());
    return m_sb;
  }


private:
  streambuf_generator m_gen;
  streambuf_type* m_sb;
  bool m_set_loc;
  char_type ic;
  char_type oc;
};

typedef basic_multibuf<char> multistreambuf;
typedef basic_multibuf<wchar_t> wmultistreambuf;

}

#endif
