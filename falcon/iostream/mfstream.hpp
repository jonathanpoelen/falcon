#ifndef FALCON_IOSTREAM_MFSTREAM_HPP
#define FALCON_IOSTREAM_MFSTREAM_HPP

#include <fstream>
#include <vector>
#include <string>

namespace falcon {

class filename_generator
{
public:
  typedef std::string value_type;

  std::vector<std::string> vector;
  std::size_t position;

public:
#if __cplusplus >= 201103L
  filename_generator() = default;
  filename_generator(const filename_generator&) = default;
  filename_generator(filename_generator&&) = default;

  filename_generator(std::initializer_list<value_type> l)
  : vector(l)
  , position(0)
  {}
#else
  filename_generator()
  : vector()
  , position(0)
  {}

  filename_generator(const filename_generator& other)
  : vector(other.vector)
  , position(0)
  {}
#endif

  template<typename InputIterator>
  filename_generator(InputIterator first, InputIterator last)
  : vector(first, last)
  , position(0)
  {}

  const char * operator()()
  {
    if (position < vector.size()) {
      return vector[position++].c_str();
    }
    return 0;
  }

  void push(const std::string& filename)
  { vector.push_back(filename); }

  void push(const char* filename)
  { vector.push_back(filename); }

#if __cplusplus >= 201103L
  void push(std::string&& filename)
  { vector.emplace_back<>(std::move(filename)); }
#endif

  template<typename InputIterator>
  void push(InputIterator first, InputIterator last)
  { vector.insert(vector.end(), first, last); }
};

template<typename CharT, typename Traits = std::char_traits<CharT>,
  typename Generator = filename_generator>
class basic_mfilebuf;

template<typename CharT, typename Traits = std::char_traits<CharT>,
  typename Generator = filename_generator>
class basic_mifstream;

template<typename CharT, typename Traits = std::char_traits<CharT>,
  typename Generator = filename_generator>
class basic_mofstream;

template<typename CharT, typename Traits = std::char_traits<CharT>,
  typename Generator = filename_generator>
class basic_mfstream;


template<typename CharT, typename Traits, typename Generator>
class basic_mfilebuf
: public std::basic_filebuf<CharT, Traits>
{
  typedef std::basic_filebuf<CharT, Traits> __filebuf_type;

public:
  typedef CharT char_type;
  typedef Traits traits_type;
  typedef typename __filebuf_type::int_type int_type;
  typedef typename __filebuf_type::pos_type pos_type;
  typedef typename __filebuf_type::off_type off_type;
  typedef Generator filename_generator;

public:
  basic_mfilebuf()
  : __filebuf_type()
  , m_gen()
  {}

  basic_mfilebuf(std::ios_base::openmode __mode)
  : __filebuf_type()
  , m_gen()
  { this->_M_mode = __mode; }

  basic_mfilebuf(const filename_generator& gen)
  : __filebuf_type()
  , m_gen(gen)
  { }

  basic_mfilebuf(const filename_generator& gen, std::ios_base::openmode __mode)
  : __filebuf_type()
  , m_gen(gen)
  { this->_M_mode = __mode; }

#if __cplusplus >= 201103L
  basic_mfilebuf(filename_generator&& gen)
  : __filebuf_type()
  , m_gen(std::forward<filename_generator>(gen))
  { }

  basic_mfilebuf(filename_generator&& gen, std::ios_base::openmode __mode)
  : __filebuf_type()
  , m_gen(std::forward<filename_generator>(gen))
  { this->_M_mode = __mode; }
#endif

  virtual
  ~basic_mfilebuf()
  {}

  bool mode(std::ios_base::openmode __mode)
  {
    if (this->is_open())
      return false;
    this->_M_mode = __mode;
    return true;
  }

  std::ios_base::openmode mode() const
  { return this->_M_mode; }

  filename_generator& generator_filename()
  { return m_gen; }

  const filename_generator& generator_filename() const
  { return m_gen; }

  void generator_filename(const filename_generator& gen)
  { m_gen = gen; }

#if __cplusplus >= 201103L
  void generator_filename(filename_generator&& gen)
  { m_gen = std::move(gen); }
#endif

  bool opennext(std::ios_base::openmode __mode)
  {
    const char * filename = m_gen();
    return filename && newopen(filename, __mode);
  }

  bool opennext()
  { return opennext(this->_M_mode); }

  virtual bool
  newopen(const char* s, std::ios_base::openmode __mode)
  { return this->open(s, __mode); }

protected:
  bool _M_opennext()
  {
    if (!this->is_open())
      return false;
    std::ios_base::openmode __mode = this->_M_mode;
    this->close();
    return opennext(__mode);
  }

  virtual int_type
  underflow()
  {
    int_type ret = traits_type::eof();
    if (this->_M_mode & std::ios_base::in)
    {
      ret = __filebuf_type::underflow();
      while (traits_type::eq_int_type(ret, traits_type::eof()) && _M_opennext())
      {
        if (this->gptr() < this->egptr())
          ret = traits_type::to_int_type(*this->gptr());
        else
          ret = __filebuf_type::underflow();
      }
    }
    return ret;
  }

  virtual int_type
  overflow(int_type __c = traits_type::eof())
  {
    int_type ret = traits_type::eof();
    if (this->_M_mode & std::ios_base::out)
    {
      ret = __filebuf_type::overflow(__c);
      while (traits_type::eq_int_type(ret, traits_type::eof()) && _M_opennext())
      {
          if (this->pptr() < this->epptr())
          {
           *this->pptr() = traits_type::to_char_type(__c);
            this->pbump(1);
            ret = traits_type::not_eof(__c);
          }
          else
            ret = __filebuf_type::overflow(__c);
        }
    }
      return ret;
  }


private:
  filename_generator m_gen;
};


template<typename CharT, typename Traits, typename Generator>
class basic_mifstream
: public std::basic_istream<CharT, Traits>
{
public:
  typedef CharT char_type;
  typedef Traits traits_type;
  typedef typename traits_type::int_type int_type;
  typedef typename traits_type::pos_type pos_type;
  typedef typename traits_type::off_type off_type;

private:
  typedef basic_mfilebuf<char_type, traits_type, Generator> __mfilebuf_type;
  typedef std::basic_istream<char_type, traits_type> __istream_type;
  typedef typename __mfilebuf_type::filename_generator filename_generator;

public:
  // Constructors/Destructors:
  /**
   *  @brief  Default constructor.
   *
   *  Initializes @c sb using its default constructor, and passes
   *  @c &sb to the base class initializer.  Does not open any files
   *  (you haven't given it a filename to open).
   */
  basic_mifstream()
  : __istream_type()
  , m_mfilebuf()
  { this->init(&m_mfilebuf); }

  /**
   *  @brief  Create an input file stream.
   *  @param  s  Null terminated string specifying the filename.
   *  @param  mode  Open file in specified mode (see std::ios_base).
   *
   *  @c std::ios_base::in is automatically included in @a mode.
   *
   *  Tip:  When using std::string to hold the filename, you must use
   *  .c_str() before passing it to this constructor.
   */
  explicit
  basic_mifstream(const char* s, std::ios_base::openmode __mode = std::ios_base::in)
  : __istream_type()
  , m_mfilebuf()
  {
    this->init(&m_mfilebuf);
    this->open(s, __mode);
  }

#if __cplusplus >= 201103L
  /**
   *  @brief  Create an input file stream.
   *  @param  s  std::string specifying the filename.
   *  @param  mode  Open file in specified mode (see std::ios_base).
   *
   *  @c std::ios_base::in is automatically included in @a mode.
   */
  explicit
  basic_mifstream(const std::string& s,
                  std::ios_base::openmode __mode = std::ios_base::in)
  : __istream_type()
  , m_mfilebuf()
  {
    this->init(&m_mfilebuf);
    this->open(s, __mode);
  }
#endif

  /**
   *  @brief  Create an input file stream.
   *  @param  files  Null terminated strings specifying generator_filename.
   *  @param  mode  Open file in specified mode (see std::ios_base).
   *
   *  @c std::ios_base::in is automatically included in @a mode.
   */
  explicit
  basic_mifstream(const filename_generator& gen,
                  std::ios_base::openmode __mode = std::ios_base::in)
  : __istream_type()
  , m_mfilebuf(gen)
  {
    this->init(&m_mfilebuf);
    m_mfilebuf.opennext(__mode | std::ios_base::in);
  }

#if __cplusplus >= 201103L
  /**
   *  @brief  Create an input file stream.
   *  @param  files  Null terminated strings specifying generator_filename.
   *  @param  mode  Open file in specified mode (see std::ios_base).
   *
   *  @c std::ios_base::in is automatically included in @a mode.
   */
  explicit
  basic_mifstream(filename_generator&& gen,
                  std::ios_base::openmode __mode = std::ios_base::in)
  : __istream_type()
  , m_mfilebuf(std::move(gen))
  {
    this->init(&m_mfilebuf);
    m_mfilebuf.opennext(__mode | std::ios_base::in);
  }
#endif

  /**
   *  @brief  Create an input file stream.
   *  @param  first  An input iterator on null terminated strings specifying generator_filename.
   *  @param  last  An input iterator on null terminated strings specifying generator_filename.
   *  @param  mode  Open file in specified mode (see std::ios_base).
   *
   *  @c std::ios_base::in is automatically included in @a mode.
   */
  template<typename _InputIterator>
  basic_mifstream(_InputIterator first, _InputIterator last,
                  std::ios_base::openmode __mode = std::ios_base::in)
  : __istream_type()
  , m_mfilebuf(filename_generator(first, last))
  {
    this->init(&m_mfilebuf);
    m_mfilebuf.opennext(__mode | std::ios_base::in);
  }

  /**
   *  @brief  The destructor does nothing.
   *
   *  The file is closed by the filebuf object, not the formatting
   *  stream.
   */
  ~basic_mifstream()
  { }

  // Members:
  /**
   *  @brief  Accessing the underlying buffer.
   *  @return  The current basic_filebuf buffer.
   *
   *  This hides both signatures of std::basic_ios::rdbuf().
   */
  __mfilebuf_type*
  rdbuf() const
  { return const_cast<__mfilebuf_type*>(&m_mfilebuf); }

  filename_generator& generator_filename()
  { return m_mfilebuf.generator_filename(); }

  const filename_generator& generator_filename() const
  { return m_mfilebuf.generator_filename(); }

  void generator_filename(const filename_generator& gen)
  { m_mfilebuf.generator_filename(gen); }

#if __cplusplus >= 201103L
  void generator_filename(filename_generator&& gen)
  { m_mfilebuf.generator_filename(std::move(gen)); }
#endif

  /**
   *  @brief  Wrapper to test for an open file.
   *  @return  @c rdbuf()->is_open()
   */
  bool
  is_open()
  { return m_mfilebuf.is_open(); }

  bool
  is_open() const
  { return m_mfilebuf.is_open(); }

  /**
   *  @brief  Opens an external file.
   *  @param  s  The name of the file.
   *  @param  mode  The open mode flags.
   *
   *  Calls @c std::basic_filebuf::open(s,mode|in).  If that function
   *  fails, @c failbit is set in the stream's error state.
   *
   *  Tip:  When using std::string to hold the filename, you must use
   *  .c_str() before passing it to this constructor.
   */
  void
  open(const char* s, std::ios_base::openmode __mode = std::ios_base::in)
  {
    if (!m_mfilebuf.open(s, __mode | std::ios_base::in))
      this->setstate(std::ios_base::failbit);
    else
      this->clear();
  }

#if __cplusplus >= 201103L
  /**
   *  @brief  Opens an external file.
   *  @param  s  The name of the file.
   *  @param  mode  The open mode flags.
   *
   *  Calls @c std::basic_filebuf::open(s,mode|in).  If that function
   *  fails, @c failbit is set in the stream's error state.
   */
  void
  open(const std::string& s, std::ios_base::openmode __mode = std::ios_base::in)
  {
    if (!m_mfilebuf.open(s, __mode | std::ios_base::in))
      this->setstate(std::ios_base::failbit);
    else
      this->clear();
  }
#endif

  /**
   *  @brief  Opens an external file.
   *  @param  mode  The open mode flags.
   *
   *  Calls @c std::basic_filebuf::open(s,mode|in).  If that function
   *  fails, @c failbit is set in the stream's error state.
   */
  void
  open_next(std::ios_base::openmode __mode = std::ios_base::in)
  {
    if (!m_mfilebuf.opennext(__mode | std::ios_base::in))
      this->setstate(std::ios_base::failbit);
    else
      this->clear();
  }

  /**
   *  @brief  Close the file.
   *
   *  Calls @c std::basic_filebuf::close().  If that function
   *  fails, @c failbit is set in the stream's error state.
   */
  void
  close()
  {
    if (!m_mfilebuf.close())
      this->setstate(std::ios_base::failbit);
  }

private:
  __mfilebuf_type m_mfilebuf;
};


template<typename CharT, typename Traits, typename Generator>
class basic_mofstream
: public std::basic_ostream<CharT,Traits>
{
public:
  // Types:
  typedef CharT char_type;
  typedef Traits traits_type;
  typedef typename traits_type::int_type int_type;
  typedef typename traits_type::pos_type pos_type;
  typedef typename traits_type::off_type off_type;

private:
  typedef basic_mfilebuf<char_type, traits_type, Generator> __mfilebuf_type;
  typedef std::basic_ostream<char_type, traits_type> __ostream_type;
  typedef typename __mfilebuf_type::filename_generator filename_generator;

public:
  // Constructors:
  /**
   *  @brief  Default constructor.
   *
   *  Initializes @c sb using its default constructor, and passes
   *  @c &sb to the base class initializer.  Does not open any files
   *  (you haven't given it a filename to open).
   */
  basic_mofstream()
  : __ostream_type()
  , m_mfilebuf()
  { this->init(&m_mfilebuf); }

  /**
   *  @brief  Create an output file stream.
   *  @param  s  Null terminated string specifying the filename.
   *  @param  mode  Open file in specified mode (see std::ios_base).
   *
   *  @c std::ios_base::out|ios_base::trunc is automatically included in
   *  @a mode.
   *
   *  Tip:  When using std::string to hold the filename, you must use
   *  .c_str() before passing it to this constructor.
   */
  explicit
  basic_mofstream(const char* s,
                  std::ios_base::openmode __mode = std::ios_base::out | std::ios_base::trunc)
  : __ostream_type()
  , m_mfilebuf()
  {
    this->init(&m_mfilebuf);
    this->open(s, __mode);
  }

#if __cplusplus >= 201103L
  /**
   *  @brief  Create an output file stream.
   *  @param  s  std::string specifying the filename.
   *  @param  mode  Open file in specified mode (see std::ios_base).
   *
   *  @c std::ios_base::out|ios_base::trunc is automatically included in
   *  @a mode.
   */
  explicit
  basic_mofstream(const std::string& s,
                  std::ios_base::openmode __mode = std::ios_base::out | std::ios_base::trunc)
  : __ostream_type()
  , m_mfilebuf()
  {
    this->init(&m_mfilebuf);
    this->open(s, __mode);
  }
#endif

  /**
   *  @brief  Create an output file stream.
   *  @param  files  Null terminated strings specifying generator_filename.
   *  @param  mode  Open file in specified mode (see std::ios_base).
   *
   *  @c std::ios_base::out|ios_base::trunc is automatically included in
   *  @a mode.
   */
  explicit
  basic_mofstream(const filename_generator& gen,
                  std::ios_base::openmode __mode = std::ios_base::out | std::ios_base::trunc)
  : __ostream_type()
  , m_mfilebuf(gen)
  {
    this->init(&m_mfilebuf);
    m_mfilebuf.opennext(__mode | std::ios_base::out);
  }

#if __cplusplus >= 201103L
  /**
   *  @brief  Create an output file stream.
   *  @param  files  Null terminated strings specifying generator_filename.
   *  @param  mode  Open file in specified mode (see std::ios_base).
   *
   *  @c std::ios_base::out|ios_base::trunc is automatically included in
   *  @a mode.
   */
  explicit
  basic_mofstream(filename_generator&& gen,
                  std::ios_base::openmode __mode = std::ios_base::out | std::ios_base::trunc)
  : __ostream_type()
  , m_mfilebuf(std::move(gen))
  {
      this->init(&m_mfilebuf);
      m_mfilebuf.opennext(__mode | std::ios_base::out);
  }
  #endif

  /**
   *  @brief  Create an output file stream.
   *  @param  first  An output iterator on null terminated strings specifying generator_filename.
   *  @param  last  An output iterator on null terminated strings specifying generator_filename.
   *  @param  mode  Open file in specified mode (see std::ios_base).
   *
   *  @c std::ios_base::out|ios_base::trunc is automatically included in @a mode.
   */
  template<typename _InputIterator>
  basic_mofstream(_InputIterator first, _InputIterator last,
                  std::ios_base::openmode __mode = std::ios_base::out | std::ios_base::trunc)
  : __ostream_type()
  , m_mfilebuf(filename_generator(first, last))
  {
    this->init(&m_mfilebuf);
    m_mfilebuf.opennext(__mode | std::ios_base::out);
  }

  /**
   *  @brief  The destructor does nothing.
   *
   *  The file is closed by the filebuf object, not the formatting
   *  stream.
   */
  ~basic_mofstream()
  { }

  // Members:
  /**
   *  @brief  Accessing the underlying buffer.
   *  @return  The current basic_filebuf buffer.
   *
   *  This hides both signatures of std::basic_ios::rdbuf().
   */
  __mfilebuf_type*
  rdbuf() const
  { return const_cast<__mfilebuf_type*>(&m_mfilebuf); }

  filename_generator& generator_filename()
  { return m_mfilebuf.generator_filename(); }

  const filename_generator& generator_filename() const
  { return m_mfilebuf.generator_filename(); }

  void generator_filename(const filename_generator& gen)
  { m_mfilebuf.generator_filename(gen); }

#if __cplusplus >= 201103L
  void generator_filename(filename_generator&& gen)
  { m_mfilebuf.generator_filename(std::move(gen)); }
#endif

  /**
   *  @brief  Wrapper to test for an open file.
   *  @return  @c rdbuf()->is_open()
   */
  bool
  is_open()
  { return m_mfilebuf.is_open(); }

  // _GLIBCXX_RESOLVE_LIB_DEFECTS
  // 365. Lack of const-qualification in clause 27
  bool
  is_open() const
  { return m_mfilebuf.is_open(); }

  /**
   *  @brief  Opens an external file.
   *  @param  s  The name of the file.
   *  @param  mode  The open mode flags.
   *
   *  Calls @c std::basic_filebuf::open(s,mode|out|trunc).  If that
   *  function fails, @c failbit is set in the stream's error state.
   *
   *  Tip:  When using std::string to hold the filename, you must use
   *  .c_str() before passing it to this constructor.
   */
  void
  open(const char* s,
       std::ios_base::openmode __mode = std::ios_base::out | std::ios_base::trunc)
  {
    if (!m_mfilebuf.open(s, __mode | std::ios_base::out))
      this->setstate(std::ios_base::failbit);
    else
      this->clear();
  }

#if __cplusplus >= 201103L
  /**
   *  @brief  Opens an external file.
   *  @param  s  The name of the file.
   *  @param  mode  The open mode flags.
   *
   *  Calls @c std::basic_filebuf::open(s,mode|out|trunc).  If that
   *  function fails, @c failbit is set in the stream's error state.
   */
  void
  open(const std::string& s,
       std::ios_base::openmode __mode = std::ios_base::out | std::ios_base::trunc)
  {
    if (!m_mfilebuf.open(s, __mode | std::ios_base::out))
      this->setstate(std::ios_base::failbit);
    else
      this->clear();
  }
#endif

  /**
   *  @brief  Opens an external file.
   *  @param  mode  The open mode flags.
   *
   *  Calls @c std::basic_filebuf::open(s,mode|in).  If that function
   *  fails, @c failbit is set in the stream's error state.
   */
  void
  open_next(std::ios_base::openmode __mode = std::ios_base::out | std::ios_base::trunc)
  {
    if (!m_mfilebuf.opennext(__mode | std::ios_base::out))
      this->setstate(std::ios_base::failbit);
    else
      this->clear();
  }

  /**
   *  @brief  Close the file.
   *
   *  Calls @c std::basic_filebuf::close().  If that function
   *  fails, @c failbit is set in the stream's error state.
   */
  void
  close()
  {
      if (!m_mfilebuf.close())
          this->setstate(std::ios_base::failbit);
  }


private:
  __mfilebuf_type m_mfilebuf;
};


// [27.8.1.11] Template class basic_mfstream
/**
*  @brief  Controlling input and output for files.
*  @ingroup io
*
*  This class supports reading from and writing to named files, using
*  the inherited functions from std::basic_iostream.  To control the
*  associated sequence, an instance of std::basic_filebuf is used, which
*  this page refers to as @c sb.
*/
template<typename CharT, typename Traits, typename Generator>
class basic_mfstream
: public std::basic_iostream<CharT, Traits>
{
public:
  typedef CharT char_type;
  typedef Traits traits_type;
  typedef typename traits_type::int_type int_type;
  typedef typename traits_type::pos_type pos_type;
  typedef typename traits_type::off_type off_type;

private:
  typedef basic_mfilebuf<char_type, traits_type, Generator> __mfilebuf_type;
  typedef std::basic_ios<char_type, traits_type> __ios_type;
  typedef std::basic_iostream<char_type, traits_type> __iostream_type;
  typedef typename __mfilebuf_type::filename_generator filename_generator;

public:
  // Constructors/destructor:
  /**
   *  @brief  Default constructor.
   *
   *  Initializes @c sb using its default constructor, and passes
   *  @c &sb to the base class initializer.  Does not open any files
   *  (you haven't given it a filename to open).
   */
  basic_mfstream()
  : __iostream_type()
  , m_mfilebuf()
  { this->init(&m_mfilebuf); }

  /**
   *  @brief  Create an input/output file stream.
   *  @param  s  Null terminated string specifying the filename.
   *  @param  mode  Open file in specified mode (see std::ios_base).
   *
   *  Tip:  When using std::string to hold the filename, you must use
   *  .c_str() before passing it to this constructor.
   */
  explicit
  basic_mfstream(const char* s,
                 std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
  : __iostream_type(0)
  , m_mfilebuf()
  {
    this->init(&m_mfilebuf);
    this->open(s, __mode);
  }

#if __cplusplus >= 201103L
  /**
   *  @brief  Create an input/output file stream.
   *  @param  s  Null terminated string specifying the filename.
   *  @param  mode  Open file in specified mode (see std::ios_base).
   */
  explicit
  basic_mfstream(const std::string& s,
                 std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
  : __iostream_type(0)
  , m_mfilebuf()
  {
    this->init(&m_mfilebuf);
    this->open(s, __mode);
  }
#endif

  /**
   *  @brief  Create an input/output file stream.
   *  @param  files  Null terminated strings specifying generator_filename.
   *  @param  mode  Open file in specified mode (see std::ios_base).
   */
  explicit
  basic_mfstream(const filename_generator& gen,
                 std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
  : __iostream_type()
  , m_mfilebuf(gen)
  {
    this->init(&m_mfilebuf);
    m_mfilebuf.opennext(__mode);
  }

#if __cplusplus >= 201103L
  /**
   *  @brief  Create an input/output file stream.
   *  @param  files  Null terminated strings specifying generator_filename.
   *  @param  mode  Open file in specified mode (see std::ios_base).
   */
  explicit
  basic_mfstream(filename_generator&& gen,
                 std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
  : __iostream_type()
  , m_mfilebuf(std::move(gen))
  {
      this->init(&m_mfilebuf);
      m_mfilebuf.opennext(__mode);
  }
#endif

  /**
   *  @brief  Create an input/output file stream.
   *  @param  first  An input/output iterator on null terminated strings specifying generator_filename.
   *  @param  last  An input/output iterator on null terminated strings specifying generator_filename.
   *  @param  mode  Open file in specified mode (see std::ios_base).
   */
  template<typename _InputIterator>
  basic_mfstream(_InputIterator first, _InputIterator last,
                 std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
  : __iostream_type()
  , m_mfilebuf(filename_generator(first, last))
  {
      this->init(&m_mfilebuf);
      m_mfilebuf.opennext(__mode);
  }

  /**
   *  @brief  The destructor does nothing.
   *
   *  The file is closed by the filebuf object, not the formatting
   *  stream.
   */
  ~basic_mfstream()
  { }

  // Members:
  /**
   *  @brief  Accessing the underlying buffer.
   *  @return  The current basic_filebuf buffer.
   *
   *  This hides both signatures of std::basic_ios::rdbuf().
   */
  __mfilebuf_type*
  rdbuf() const
  { return const_cast<__mfilebuf_type*>(&m_mfilebuf); }

  filename_generator& generator_filename()
  { return m_mfilebuf.generator_filename(); }

  const filename_generator& generator_filename() const
  { return m_mfilebuf.generator_filename(); }

  void generator_filename(const filename_generator& gen)
  { m_mfilebuf.generator_filename(gen); }

#if __cplusplus >= 201103L
  void generator_filename(filename_generator&& gen)
  { m_mfilebuf.generator_filename(std::move(gen)); }
#endif

  /**
   *  @brief  Wrapper to test for an open file.
   *  @return  @c rdbuf()->is_open()
   */
  bool
  is_open()
  { return m_mfilebuf.is_open(); }

  // _GLIBCXX_RESOLVE_LIB_DEFECTS
  // 365. Lack of const-qualification in clause 27
  bool
  is_open() const
  { return m_mfilebuf.is_open(); }

  /**
   *  @brief  Opens an external file.
   *  @param  s  The name of the file.
   *  @param  mode  The open mode flags.
   *
   *  Calls @c std::basic_filebuf::open(s,mode).  If that
   *  function fails, @c failbit is set in the stream's error state.
   *
   *  Tip:  When using std::string to hold the filename, you must use
   *  .c_str() before passing it to this constructor.
   */
  void
  open(const char* s,
       std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
  {
    if (!m_mfilebuf.open(s, __mode))
      this->setstate(std::ios_base::failbit);
    else
      this->clear();
  }

#if __cplusplus >= 201103L
  /**
   *  @brief  Opens an external file.
   *  @param  s  The name of the file.
   *  @param  mode  The open mode flags.
   *
   *  Calls @c std::basic_filebuf::open(s,mode).  If that
   *  function fails, @c failbit is set in the stream's error state.
   */
  void
  open(const std::string& s,
       std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
  {
    if (!m_mfilebuf.open(s, __mode))
      this->setstate(std::ios_base::failbit);
    else
      this->clear();
  }
#endif

  /**
   *  @brief  Opens an external file.
   *  @param  mode  The open mode flags.
   *
   *  Calls @c std::basic_filebuf::open(s,mode|in).  If that function
   *  fails, @c failbit is set in the stream's error state.
   */
  void
  open_next(std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
  {
    if (!m_mfilebuf.opennext(__mode))
      this->setstate(std::ios_base::failbit);
    else
      this->clear();
  }

  /**
   *  @brief  Close the file.
   *
   *  Calls @c std::basic_filebuf::close().  If that function
   *  fails, @c failbit is set in the stream's error state.
   */
  void
  close()
  {
      if (!m_mfilebuf.close())
          this->setstate(std::ios_base::failbit);
  }

private:
  __mfilebuf_type m_mfilebuf;
};

typedef basic_mfilebuf<char> mfilebuf;
typedef basic_mfilebuf<wchar_t> wmfilebuf;

typedef basic_mfstream<char> mfstream;
typedef basic_mifstream<char> mifstream;
typedef basic_mofstream<char> mofstream;

typedef basic_mfstream<wchar_t> wmfstream;
typedef basic_mifstream<wchar_t> wmifstream;
typedef basic_mofstream<wchar_t> wmofstream;

}

#endif
