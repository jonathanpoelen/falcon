#ifndef FALCON_IOSTREAM_MFSTREAM_HPP
#define FALCON_IOSTREAM_MFSTREAM_HPP

#include <fstream>
#include <vector>
#include <string>

namespace falcon {

template<typename _CharT, typename _Traits = std::char_traits<_CharT> >
class basic_mfilebuf;

template<typename _CharT, typename _Traits = std::char_traits<_CharT> >
class basic_mifstream;

template<typename _CharT, typename _Traits = std::char_traits<_CharT> >
class basic_mofstream;

template<typename _CharT, typename _Traits = std::char_traits<_CharT> >
class basic_mfstream;


template<typename _CharT, typename _Traits>
class basic_mfilebuf
: public std::basic_filebuf<_CharT, _Traits>
{
	typedef std::basic_filebuf<_CharT, _Traits> __filebuf_type;

public:
	typedef _CharT char_type;
	typedef _Traits traits_type;
	typedef typename __filebuf_type::int_type int_type;
	typedef typename __filebuf_type::pos_type pos_type;
	typedef typename __filebuf_type::off_type off_type;
	typedef std::vector<std::string> filenames_type;

protected:
	filenames_type _M_filenames;
	std::size_t _M_posname;

public:
	basic_mfilebuf()
	: __filebuf_type()
	, _M_filenames()
	, _M_posname(0)
	{}

	basic_mfilebuf(std::ios_base::openmode __mode)
	: __filebuf_type()
	, _M_filenames()
	, _M_posname(0)
	{ this->_M_mode = __mode; }

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

	filenames_type& filenames()
	{ return _M_filenames; }

	const filenames_type& filenames() const
	{ return _M_filenames; }

	void filenames(const filenames_type& __filenames)
	{ _M_filenames = __filenames; }

#if __cplusplus > 201100L
	void filenames(filenames_type&& __filenames)
	{ _M_filenames = std::move(__filenames); }

	void filenames(std::initializer_list<std::string> __filenames)
	{ _M_filenames = __filenames; }

	void filenames(std::initializer_list<const char *> __filenames)
	{ _M_filenames.assign(__filenames.begin(), __filenames.end()); }
#endif

	template <typename _InputIterator>
	void filenames(_InputIterator __first, _InputIterator __last)
	{ _M_filenames.assign(__first, __last); }

	std::size_t posname() const
	{ return _M_posname; }

	void posname(std::size_t __n)
	{ _M_posname = __n; }

	void erase_is_open()
	{
		if (_M_posname)
		{
			std::string * __first = &_M_filenames[0];
			std::string * __pos = &_M_filenames[_M_posname];
			std::string * __last = &_M_filenames[_M_filenames.size()];
			for ( ; __pos != __last; ++__first, __pos)
				*__first = *__pos;
			_M_filenames.resize(_M_filenames.size() - _M_posname);
			_M_posname = 0;
		}
	}

#if __cplusplus > 201100L
	void shrink_to_fit()
	{
		erase_is_open();
		_M_filenames.shrink_to_fit();
	}
#endif

	bool opennext(std::ios_base::openmode __mode)
	{
		if (_M_posname < _M_filenames.size()
			&& newopen(_M_filenames[_M_posname].c_str(), __mode))
		{
			++_M_posname;
			return true;
		}
		return false;
	}

	bool opennext()
	{ return opennext(this->_M_mode); }

protected:
	bool _M_opennext()
	{
		if (!this->is_open())
			return false;
		std::ios_base::openmode __mode = this->_M_mode;
		this->close();
		return opennext(__mode);
	}

	virtual bool
	newopen(const char* __s, std::ios_base::openmode __mode)
	{ return this->open(__s, __mode); }

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
};

template<typename _CharT, typename _Traits>
class basic_mifstream
: public std::basic_istream<_CharT, _Traits>
{
public:
	// Types:
	typedef _CharT char_type;
	typedef _Traits traits_type;
	typedef typename traits_type::int_type int_type;
	typedef typename traits_type::pos_type pos_type;
	typedef typename traits_type::off_type off_type;

private:
	typedef basic_mfilebuf<char_type, traits_type> __mfilebuf_type;
	typedef std::basic_istream<char_type, traits_type> __istream_type;
	typedef typename __mfilebuf_type::filenames_type __filenames_type;

private:
	__mfilebuf_type _M_mfilebuf;

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
	, _M_mfilebuf()
	{ this->init(&_M_mfilebuf); }

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
	basic_mifstream(const char* __s, std::ios_base::openmode __mode = std::ios_base::in)
	: __istream_type()
	, _M_mfilebuf()
	{
		this->init(&_M_mfilebuf);
		this->open(__s, __mode);
	}

#if __cplusplus > 201100L
	/**
	 *  @brief  Create an input file stream.
	 *  @param  s  std::string specifying the filename.
	 *  @param  mode  Open file in specified mode (see std::ios_base).
	 *
	 *  @c std::ios_base::in is automatically included in @a mode.
	 */
	explicit
	basic_mifstream(const std::string& __s,
									std::ios_base::openmode __mode = std::ios_base::in)
	: __istream_type()
	, _M_mfilebuf()
	{
		this->init(&_M_mfilebuf);
		this->open(__s, __mode);
	}
#endif

	/**
	 *  @brief  Create an input file stream.
	 *  @param  files  Null terminated strings specifying filenames.
	 *  @param  mode  Open file in specified mode (see std::ios_base).
	 *
	 *  @c std::ios_base::in is automatically included in @a mode.
	 */
	explicit
	basic_mifstream(const __filenames_type& __files,
									std::ios_base::openmode __mode = std::ios_base::in)
	: __istream_type()
	, _M_mfilebuf()
	{
		this->init(&_M_mfilebuf);
		open(__files, __mode);
	}

#if __cplusplus > 201100L
	/**
	 *  @brief  Create an input file stream.
	 *  @param  files  Null terminated strings specifying filenames.
	 *  @param  mode  Open file in specified mode (see std::ios_base).
	 *
	 *  @c std::ios_base::in is automatically included in @a mode.
	 */
	explicit
	basic_mifstream(__filenames_type&& __files,
									std::ios_base::openmode __mode = std::ios_base::in)
	: __istream_type()
	, _M_mfilebuf()
	{
		this->init(&_M_mfilebuf);
		open(std::move(__files), __mode);
	}

	/**
	 *  @brief  Create an input file stream.
	 *  @param  files  Null terminated strings specifying filenames.
	 *  @param  mode  Open file in specified mode (see std::ios_base).
	 *
	 *  @c std::ios_base::in is automatically included in @a mode.
	 */
	explicit
	basic_mifstream(std::initializer_list<std::string> __files,
									std::ios_base::openmode __mode = std::ios_base::in)
	: __istream_type()
	, _M_mfilebuf()
	{
		this->init(&_M_mfilebuf);
		open(__files.begin(), __files.end(), __mode);
	}
#endif

	/**
	 *  @brief  Create an input file stream.
	 *  @param  first  An input iterator on null terminated strings specifying filenames.
	 *  @param  last  An input iterator on null terminated strings specifying filenames.
	 *  @param  mode  Open file in specified mode (see std::ios_base).
	 *
	 *  @c std::ios_base::in is automatically included in @a mode.
	 */
	template<typename _InputIterator>
	basic_mifstream(_InputIterator __first, _InputIterator __last,
									std::ios_base::openmode __mode = std::ios_base::in)
	: __istream_type()
	, _M_mfilebuf()
	{
		this->init(&_M_mfilebuf);
		open(__first, __last, __mode);
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
	{ return const_cast<__mfilebuf_type*>(&_M_mfilebuf); }

	void push_filename(const std::string& __s)
	{ filenames().push_back(__s); }

	std::size_t count() const
	{ return filenames().size() - _M_mfilebuf.posname(); }

	__filenames_type& filenames()
	{ return _M_mfilebuf.filenames(); }

	const __filenames_type& filenames() const
	{ return _M_mfilebuf.filenames(); }

	void filenames(const __filenames_type& __filenames)
	{ _M_mfilebuf.filenames(__filenames); }

#if __cplusplus > 201100L
	void filenames(__filenames_type&& __filenames)
	{ _M_mfilebuf.filenames(std::move(__filenames)); }

	void filenames(std::initializer_list<std::string> __filenames)
	{ _M_mfilebuf.filenames(__filenames); }

	void filenames(std::initializer_list<const char *> __filenames)
	{ _M_mfilebuf.filenames(__filenames); }
#endif

	template <typename _InputIterator>
	void filenames(_InputIterator __first, _InputIterator __last)
	{ _M_mfilebuf.filenames(__first, __last); }

	/**
	 *  @brief  Wrapper to test for an open file.
	 *  @return  @c rdbuf()->is_open()
	 */
	bool
	is_open()
	{ return _M_mfilebuf.is_open(); }

	bool
	is_open() const
	{ return _M_mfilebuf.is_open(); }

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
	open(const char* __s, std::ios_base::openmode __mode = std::ios_base::in)
	{
		if (!_M_mfilebuf.open(__s, __mode | std::ios_base::in))
			this->setstate(std::ios_base::failbit);
		else
			this->clear();
	}

#if __cplusplus > 201100L
	/**
	 *  @brief  Opens an external file.
	 *  @param  s  The name of the file.
	 *  @param  mode  The open mode flags.
	 *
	 *  Calls @c std::basic_filebuf::open(s,mode|in).  If that function
	 *  fails, @c failbit is set in the stream's error state.
	 */
	void
	open(const std::string& __s, std::ios_base::openmode __mode = std::ios_base::in)
	{
		if (!_M_mfilebuf.open(__s, __mode | std::ios_base::in))
			this->setstate(std::ios_base::failbit);
		else
			this->clear();
	}
#endif

	/**
	 *  @brief  Opens an external file.
	 *  @param  files  Null terminated strings specifying filenames.
	 *  @param  mode  The open mode flags.
	 *
	 *  Calls @c std::basic_filebuf::open(@p files.begin()->c_str(), mode|in).
	 *  If that function fails, @c failbit is set in the stream's error state.
	 */
	void
	open(const __filenames_type& __files,
			 std::ios_base::openmode __mode = std::ios_base::in)
	{
		if (!__files.empty())
		{
			filenames().assign(__files.begin() + 1, __files.end());
			this->open(__files.begin()->c_str(), __mode | std::ios_base::in);
		}
		else
			this->setstate(std::ios_base::failbit);
	}

#if __cplusplus > 201100L
	/**
	 *  @brief  Opens an external file.
	 *  @param  files  Null terminated strings specifying filenames.
	 *  @param  mode  The open mode flags.
	 *
	 *  Calls @c std::basic_filebuf::open(@p files.begin()->c_str(), mode|in).
	 *  If that function fails, @c failbit is set in the stream's error state.
	 */
	void
	open(__filenames_type&& __files,
			 std::ios_base::openmode __mode = std::ios_base::in)
	{
		if (!__files.empty())
		{
			filenames() = std::move(__files);
			_M_mfilebuf.posname(1);
			this->open(filenames().begin()->c_str(), __mode | std::ios_base::in);
		}
		else
			this->setstate(std::ios_base::failbit);
	}

	/**
	 *  @brief  Opens an external file.
	 *  @param  files  Null terminated strings specifying filenames.
	 *  @param  mode  The open mode flags.
	 *
	 *  Calls @c std::basic_filebuf::open(@p files.begin()->c_str(), mode|in).
	 *  If that function fails, @c failbit is set in the stream's error state.
	 */
	void
	open(std::initializer_list<std::string> __files,
			 std::ios_base::openmode __mode = std::ios_base::in)
	{
		if (__files.size())
		{
			filenames().assign(__files.begin() + 1, __files.end());
			this->open(__files.begin()->c_str(), __mode | std::ios_base::in);
		}
		else
			this->setstate(std::ios_base::failbit);
	}
#endif

	/**
	 *  @brief  Opens an external file.
	 *  @param  first  An input iterator on null terminated strings specifying filenames.
	 *  @param  last  An input iterator on null terminated strings specifying filenames.
	 *  @param  mode  The open mode flags.
	 *
	 *  Calls @c std::basic_filebuf::open(@p first->c_str(), mode|in).
	 *  If that function fails, @c failbit is set in the stream's error state.
	 */
	template<typename _InputIterator>
	void
	open(_InputIterator __first, _InputIterator __last,
			 std::ios_base::openmode __mode = std::ios_base::in)
	{
		if (__first != __last)
		{
			this->open(__first->c_str(), __mode | std::ios_base::in);
			filenames().assign(++__first, __last);
		}
		else
			this->setstate(std::ios_base::failbit);
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
		if (!_M_mfilebuf.close())
			this->setstate(std::ios_base::failbit);
	}
};


template<typename _CharT, typename _Traits>
class basic_mofstream
: public std::basic_ostream<_CharT,_Traits>
{
public:
	// Types:
	typedef _CharT char_type;
	typedef _Traits traits_type;
	typedef typename traits_type::int_type int_type;
	typedef typename traits_type::pos_type pos_type;
	typedef typename traits_type::off_type off_type;

private:
	typedef basic_mfilebuf<char_type, traits_type> __mfilebuf_type;
	typedef std::basic_ostream<char_type, traits_type> __ostream_type;
	typedef typename __mfilebuf_type::filenames_type __filenames_type;

private:
	__mfilebuf_type _M_mfilebuf;

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
	, _M_mfilebuf()
	{ this->init(&_M_mfilebuf); }

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
	basic_mofstream(const char* __s,
									std::ios_base::openmode __mode = std::ios_base::out | std::ios_base::trunc)
	: __ostream_type()
	, _M_mfilebuf()
	{
		this->init(&_M_mfilebuf);
		this->open(__s, __mode);
	}

#if __cplusplus > 201100L
	/**
	 *  @brief  Create an output file stream.
	 *  @param  s  std::string specifying the filename.
	 *  @param  mode  Open file in specified mode (see std::ios_base).
	 *
	 *  @c std::ios_base::out|ios_base::trunc is automatically included in
	 *  @a mode.
	 */
	explicit
	basic_mofstream(const std::string& __s,
									std::ios_base::openmode __mode = std::ios_base::out | std::ios_base::trunc)
	: __ostream_type()
	, _M_mfilebuf()
	{
		this->init(&_M_mfilebuf);
		this->open(__s, __mode);
	}
#endif

	/**
	 *  @brief  Create an input file stream.
	 *  @param  files  Null terminated strings specifying filenames.
	 *  @param  mode  Open file in specified mode (see std::ios_base).
	 *
	 *  @c std::ios_base::out|ios_base::trunc is automatically included in
	 *  @a mode.
	 */
	explicit
	basic_mofstream(const __filenames_type& __files,
									std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
	: __ostream_type()
	, _M_mfilebuf()
	{
		this->init(&_M_mfilebuf);
		open(__files, __mode);
	}

#if __cplusplus > 201100L
	/**
	 *  @brief  Create an input file stream.
	 *  @param  files  Null terminated strings specifying filenames.
	 *  @param  mode  Open file in specified mode (see std::ios_base).
	 *
	 *  @c std::ios_base::out|ios_base::trunc is automatically included in
	 *  @a mode.
	 */
	explicit
	basic_mofstream(__filenames_type&& __files,
									std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
	: __ostream_type()
	, _M_mfilebuf()
	{
		this->init(&_M_mfilebuf);
		open(std::move(__files), __mode);
	}

	/**
	 *  @brief  Create an input file stream.
	 *  @param  files  Null terminated strings specifying filenames.
	 *  @param  mode  Open file in specified mode (see std::ios_base).
	 *
	 *  @c std::ios_base::out|ios_base::trunc is automatically included in
	 *  @a mode.
	 */
	explicit
	basic_mofstream(std::initializer_list<std::string> __files,
									std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
	: __ostream_type()
	, _M_mfilebuf()
	{
		this->init(&_M_mfilebuf);
		open(__files.begin(), __files.end(), __mode);
	}
#endif

	/**
	 *  @brief  Create an input file stream.
	 *  @param  first  An input iterator on null terminated strings specifying filenames.
	 *  @param  last  An input iterator on null terminated strings specifying filenames.
	 *  @param  mode  Open file in specified mode (see std::ios_base).
	 *
	 *  @c std::ios_base::out|ios_base::trunc is automatically included in
	 *  @a mode.
	 */
	template<typename _InputIterator>
	basic_mofstream(_InputIterator __first, _InputIterator __last,
									std::ios_base::openmode __mode = std::ios_base::out | std::ios_base::trunc)
	: __ostream_type()
	, _M_mfilebuf()
	{
		this->init(&_M_mfilebuf);
		open(__first, __last, __mode);
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
	{ return const_cast<__mfilebuf_type*>(&_M_mfilebuf); }

	void push_filename(const std::string& __s)
	{ filenames().push_back(__s); }

	std::size_t count() const
	{ return filenames().size() - _M_mfilebuf.posname(); }

	__filenames_type& filenames()
	{ return _M_mfilebuf.filenames(); }

	const __filenames_type& filenames() const
	{ return _M_mfilebuf.filenames(); }

	void filenames(const __filenames_type& __filenames)
	{ _M_mfilebuf.filenames(__filenames); }

#if __cplusplus > 201100L
	void filenames(__filenames_type&& __filenames)
	{ _M_mfilebuf.filenames(std::move(__filenames)); }

	void filenames(std::initializer_list<std::string> __filenames)
	{ _M_mfilebuf.filenames(__filenames); }

	void filenames(std::initializer_list<const char *> __filenames)
	{ _M_mfilebuf.filenames(__filenames); }
#endif

	template <typename _InputIterator>
	void filenames(_InputIterator __first, _InputIterator __last)
	{ _M_mfilebuf.filenames(__first, __last); }

	/**
	 *  @brief  Wrapper to test for an open file.
	 *  @return  @c rdbuf()->is_open()
	 */
	bool
	is_open()
	{ return _M_mfilebuf.is_open(); }

	// _GLIBCXX_RESOLVE_LIB_DEFECTS
	// 365. Lack of const-qualification in clause 27
	bool
	is_open() const
	{ return _M_mfilebuf.is_open(); }

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
	open(const char* __s,
			 std::ios_base::openmode __mode = std::ios_base::out | std::ios_base::trunc)
	{
		if (!_M_mfilebuf.open(__s, __mode | std::ios_base::out))
			this->setstate(std::ios_base::failbit);
		else
			this->clear();
	}

#if __cplusplus > 201100L
	/**
	 *  @brief  Opens an external file.
	 *  @param  s  The name of the file.
	 *  @param  mode  The open mode flags.
	 *
	 *  Calls @c std::basic_filebuf::open(s,mode|out|trunc).  If that
	 *  function fails, @c failbit is set in the stream's error state.
	 */
	void
	open(const std::string& __s,
			 std::ios_base::openmode __mode = std::ios_base::out | std::ios_base::trunc)
	{
		if (!_M_mfilebuf.open(__s, __mode | std::ios_base::out))
			this->setstate(std::ios_base::failbit);
		else
			this->clear();
	}
#endif

	/**
	 *  @brief  Opens an external file.
	 *  @param  files  Null terminated strings specifying filenames.
	 *  @param  mode  The open mode flags.
	 *
	 *  Calls @c std::basic_filebuf::open(@p files.begin()->c_str(), mode|out|trunc).
	 *  If that function fails, @c failbit is set in the stream's error state.
	 */
	void
	open(const __filenames_type& __files,
			 std::ios_base::openmode __mode = std::ios_base::out | std::ios_base::trunc)
	{
		if (!__files.empty())
		{
			filenames().assign(__files.begin() + 1, __files.end());
			this->open(__files.begin()->c_str(), __mode | std::ios_base::out);
		}
		else
			this->setstate(std::ios_base::failbit);
	}

#if __cplusplus > 201100L
	/**
	 *  @brief  Opens an external file.
	 *  @param  files  Null terminated strings specifying filenames.
	 *  @param  mode  The open mode flags.
	 *
	 *  Calls @c std::basic_filebuf::open(@p files.begin()->c_str(), mode|out|trunc).
	 *  If that function fails, @c failbit is set in the stream's error state.
	 */
	void
	open(__filenames_type&& __files,
			 std::ios_base::openmode __mode = std::ios_base::out | std::ios_base::trunc)
	{
		if (!__files.empty())
		{
			filenames() = std::move(__files);
			_M_mfilebuf.posname(1);
			this->open(filenames().begin()->c_str(), __mode | std::ios_base::out);
		}
		else
			this->setstate(std::ios_base::failbit);
	}

	/**
	 *  @brief  Opens an external file.
	 *  @param  files  Null terminated strings specifying filenames.
	 *  @param  mode  The open mode flags.
	 *
	 *  Calls @c std::basic_filebuf::open(@p files.begin()->c_str(), mode|out|trunc).
	 *  If that function fails, @c failbit is set in the stream's error state.
	 */
	void
	open(std::initializer_list<std::string> __files,
			 std::ios_base::openmode __mode = std::ios_base::out | std::ios_base::trunc)
	{
		if (__files.size())
		{
			filenames().assign(__files.begin() + 1, __files.end());
			this->open(__files.begin()->c_str(), __mode | std::ios_base::out);
		}
		else
			this->setstate(std::ios_base::failbit);
	}
#endif

	/**
	 *  @brief  Opens an external file.
	 *  @param  first  An input iterator on null terminated strings specifying filenames.
	 *  @param  last  An input iterator on null terminated strings specifying filenames.
	 *  @param  mode  The open mode flags.
	 *
	 *  Calls @c std::basic_filebuf::open(@p first->c_str(), mode|out|trunc).
	 *  If that function fails, @c failbit is set in the stream's error state.
	 */
	template<typename _InputIterator>
	void
	open(_InputIterator __first, _InputIterator __last,
			 std::ios_base::openmode __mode = std::ios_base::out | std::ios_base::trunc)
	{
		if (__first != __last)
		{
			this->open(__first->c_str(), __mode | std::ios_base::out);
			filenames().assign(++__first, __last);
		}
		else
			this->setstate(std::ios_base::failbit);
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
		if (!_M_mfilebuf.close())
			this->setstate(std::ios_base::failbit);
	}
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
template<typename _CharT, typename _Traits>
class basic_mfstream
: public std::basic_iostream<_CharT, _Traits>
{
public:
	// Types:
	typedef _CharT char_type;
	typedef _Traits traits_type;
	typedef typename traits_type::int_type int_type;
	typedef typename traits_type::pos_type pos_type;
	typedef typename traits_type::off_type off_type;

private:
	typedef basic_mfilebuf<char_type, traits_type> __mfilebuf_type;
	typedef std::basic_ios<char_type, traits_type> __ios_type;
	typedef std::basic_iostream<char_type, traits_type> __iostream_type;
	typedef typename __mfilebuf_type::filenames_type __filenames_type;

private:
	__mfilebuf_type _M_mfilebuf;

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
	, _M_mfilebuf()
	{ this->init(&_M_mfilebuf); }

	/**
	 *  @brief  Create an input/output file stream.
	 *  @param  s  Null terminated string specifying the filename.
	 *  @param  mode  Open file in specified mode (see std::ios_base).
	 *
	 *  Tip:  When using std::string to hold the filename, you must use
	 *  .c_str() before passing it to this constructor.
	 */
	explicit
	basic_mfstream(const char* __s,
								 std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
	: __iostream_type(0)
	, _M_mfilebuf()
	{
		this->init(&_M_mfilebuf);
		this->open(__s, __mode);
	}

#if __cplusplus > 201100L
	/**
	 *  @brief  Create an input/output file stream.
	 *  @param  s  Null terminated string specifying the filename.
	 *  @param  mode  Open file in specified mode (see std::ios_base).
	 */
	explicit
	basic_mfstream(const std::string& __s,
								 std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
	: __iostream_type(0)
	, _M_mfilebuf()
	{
		this->init(&_M_mfilebuf);
		this->open(__s, __mode);
	}
#endif

	/**
	 *  @brief  Create an input file stream.
	 *  @param  files  Null terminated strings specifying filenames.
	 *  @param  mode  Open file in specified mode (see std::ios_base).
	 */
	explicit
	basic_mfstream(const __filenames_type& __files,
								 std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
	: __iostream_type()
	, _M_mfilebuf()
	{
		this->init(&_M_mfilebuf);
		open(__files, __mode);
	}

#if __cplusplus > 201100L
	/**
	 *  @brief  Create an input file stream.
	 *  @param  files  Null terminated strings specifying filenames.
	 *  @param  mode  Open file in specified mode (see std::ios_base).
	 */
	explicit
	basic_mfstream(__filenames_type&& __files,
								 std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
	: __iostream_type()
	, _M_mfilebuf()
	{
		this->init(&_M_mfilebuf);
		open(std::move(__files), __mode);
	}

	/**
	 *  @brief  Create an input file stream.
	 *  @param  files  Null terminated strings specifying filenames.
	 *  @param  mode  Open file in specified mode (see std::ios_base).
	 */
	explicit
	basic_mfstream(std::initializer_list<std::string> __files,
								 std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
	: __iostream_type()
	, _M_mfilebuf()
	{
		this->init(&_M_mfilebuf);
		open(__files.begin(), __files.end(), __mode);
	}
#endif

	/**
	 *  @brief  Create an input file stream.
	 *  @param  first  An input iterator on null terminated strings specifying filenames.
	 *  @param  last  An input iterator on null terminated strings specifying filenames.
	 *  @param  mode  Open file in specified mode (see std::ios_base).
	 */
	template<typename _InputIterator>
	basic_mfstream(_InputIterator __first, _InputIterator __last,
								 std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
	: __iostream_type()
	, _M_mfilebuf()
	{
		this->init(&_M_mfilebuf);
		open(__first, __last, __mode);
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
	{ return const_cast<__mfilebuf_type*>(&_M_mfilebuf); }

	void push_filename(const std::string& __s)
	{ filenames().push_back(__s); }

	std::size_t count() const
	{ return filenames().size() - _M_mfilebuf.posname(); }

	__filenames_type& filenames()
	{ return _M_mfilebuf.filenames(); }

	const __filenames_type& filenames() const
	{ return _M_mfilebuf.filenames(); }

	void filenames(const __filenames_type& __filenames)
	{ _M_mfilebuf.filenames(__filenames); }

#if __cplusplus > 201100L
	void filenames(__filenames_type&& __filenames)
	{ _M_mfilebuf.filenames(std::move(__filenames)); }

	void filenames(std::initializer_list<std::string> __filenames)
	{ _M_mfilebuf.filenames(__filenames); }

	void filenames(std::initializer_list<const char *> __filenames)
	{ _M_mfilebuf.filenames(__filenames); }
#endif

	template <typename _InputIterator>
	void filenames(_InputIterator __first, _InputIterator __last)
	{ _M_mfilebuf.filenames(__first, __last); }

	/**
	 *  @brief  Wrapper to test for an open file.
	 *  @return  @c rdbuf()->is_open()
	 */
	bool
	is_open()
	{ return _M_mfilebuf.is_open(); }

	// _GLIBCXX_RESOLVE_LIB_DEFECTS
	// 365. Lack of const-qualification in clause 27
	bool
	is_open() const
	{ return _M_mfilebuf.is_open(); }

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
	open(const char* __s,
			 std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
	{
		if (!_M_mfilebuf.open(__s, __mode))
			this->setstate(std::ios_base::failbit);
		else
			this->clear();
	}

#if __cplusplus > 201100L
	/**
	 *  @brief  Opens an external file.
	 *  @param  s  The name of the file.
	 *  @param  mode  The open mode flags.
	 *
	 *  Calls @c std::basic_filebuf::open(s,mode).  If that
	 *  function fails, @c failbit is set in the stream's error state.
	 */
	void
	open(const std::string& __s,
			 std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
	{
		if (!_M_mfilebuf.open(__s, __mode))
			this->setstate(std::ios_base::failbit);
		else
			this->clear();
	}
#endif

	/**
	 *  @brief  Opens an external file.
	 *  @param  files  Null terminated strings specifying filenames.
	 *  @param  mode  The open mode flags.
	 *
	 *  Calls @c std::basic_filebuf::open(@p files.begin()->c_str(), mode).
	 *  If that function fails, @c failbit is set in the stream's error state.
	 */
	void
	open(const __filenames_type& __files,
			 std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
	{
		if (!__files.empty())
		{
			filenames().assign(__files.begin() + 1, __files.end());
			this->open(__files.begin()->c_str(), __mode);
		}
		else
			this->setstate(std::ios_base::failbit);
	}

#if __cplusplus > 201100L
	/**
	 *  @brief  Opens an external file.
	 *  @param  files  Null terminated strings specifying filenames.
	 *  @param  mode  The open mode flags.
	 *
	 *  Calls @c std::basic_filebuf::open(@p files.begin()->c_str(), mode).
	 *  If that function fails, @c failbit is set in the stream's error state.
	 */
	void
	open(__filenames_type&& __files,
			 std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
	{
		if (!__files.empty())
		{
			filenames() = std::move(__files);
			_M_mfilebuf.posname(1);
			this->open(filenames().begin()->c_str(), __mode);
		}
		else
			this->setstate(std::ios_base::failbit);
	}

	/**
	 *  @brief  Opens an external file.
	 *  @param  files  Null terminated strings specifying filenames.
	 *  @param  mode  The open mode flags.
	 *
	 *  Calls @c std::basic_filebuf::open(@p files.begin()->c_str(), mode).
	 *  If that function fails, @c failbit is set in the stream's error state.
	 */
	void
	open(std::initializer_list<std::string> __files,
			 std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
	{
		if (__files.size())
		{
			filenames().assign(__files.begin() + 1, __files.end());
			this->open(__files.begin()->c_str(), __mode);
		}
		else
			this->setstate(std::ios_base::failbit);
	}
#endif

	/**
	 *  @brief  Opens an external file.
	 *  @param  first  An input iterator on null terminated strings specifying filenames.
	 *  @param  last  An input iterator on null terminated strings specifying filenames.
	 *  @param  mode  The open mode flags.
	 *
	 *  Calls @c std::basic_filebuf::open(@p first->c_str(), mode).
	 *  If that function fails, @c failbit is set in the stream's error state.
	 */
	template<typename _InputIterator>
	void
	open(_InputIterator __first, _InputIterator __last,
			 std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
	{
		if (__first != __last)
		{
			this->open(__first->c_str(), __mode);
			filenames().assign(++__first, __last);
		}
		else
			this->setstate(std::ios_base::failbit);
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
		if (!_M_mfilebuf.close())
			this->setstate(std::ios_base::failbit);
	}
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