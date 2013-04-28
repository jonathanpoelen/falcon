#ifndef FALCON_IOSTREAMULTIBUF_HPP
#define FALCON_IOSTREAMULTIBUF_HPP

#include <streambuf>
#include <vector>
#include <falcon/algorithm/find_first_not_of.hpp>
#include <falcon/container/ptr_container.hpp>

namespace falcon {

template<typename _CharT, typename _Traits = std::char_traits<_CharT> >
class basic_multibuf
: public std::basic_streambuf<_CharT, _Traits>
{
	typedef std::basic_streambuf<_CharT, _Traits>    __streambuf_type;

public:
	typedef typename __streambuf_type::char_type char_type;
	typedef typename __streambuf_type::traits_type traits_type;
	typedef typename __streambuf_type::int_type int_type;
	typedef typename __streambuf_type::pos_type pos_type;
	typedef typename __streambuf_type::off_type off_type;

private:
	typedef std::vector<__streambuf_type*> __multistreambuf_type;
	typedef typename __multistreambuf_type::iterator __iterator;

	__multistreambuf_type _sbs;
	__streambuf_type* _sb;
	std::size_t _pos;

	bool _next()
	{
		_sb = 0;
		while (_pos < _sbs.size())
		{
			_sb = _sbs[_pos++];
			if (_sb)
				break;
		}
		return _sb;
	}

	struct __pubstreambuf
	: __streambuf_type
	{
		using __streambuf_type::eback;
		using __streambuf_type::gptr;
		using __streambuf_type::egptr;
		using __streambuf_type::gbump;
		using __streambuf_type::pbase;
		using __streambuf_type::pptr;
		using __streambuf_type::epptr;
		using __streambuf_type::pbump;
		using __streambuf_type::setg;
		using __streambuf_type::setp;
	};

	void _force_setg()
	{
		__pubstreambuf* __psb = static_cast<__pubstreambuf*>(_sb);
		this->setg(__psb->eback(), __psb->gptr(), __psb->egptr());
		__psb->gbump(int(__psb->egptr() - __psb->gptr()));
	}

	void _setg()
	{
		if (_sb)
			_force_setg();
		else
			this->setg(0, 0, 0);
	}

	void _setp()
	{
		if (_sb){
			__pubstreambuf* __psb = static_cast<__pubstreambuf*>(_sb);
			this->setp(__psb->pbase(), __psb->epptr());
			this->pbump(int(__psb->pptr() - __psb->pbase()));
			__psb->pbump(int(__psb->epptr() - __psb->pptr()));
		}
		else
			this->setp(0, 0);
	}

	void _rset(__streambuf_type * sb)
	{
		if (sb)
		{
			__pubstreambuf* __psb = static_cast<__pubstreambuf*>(sb);
			__psb->setg(this->eback(), this->gptr(), this->egptr());
			__psb->setp(this->pbase(), this->epptr());
			__psb->pbump(int(this->pptr() - this->pbase()));
		}
	}

	void _init_when_sequence()
	{
		if (_sb)
			resetptr();
		else
			_next();
	}

public:
	basic_multibuf()
	: __streambuf_type()
	, _sbs()
	, _sb()
	, _pos(0)
	{}

	basic_multibuf(const __multistreambuf_type& __sbs)
	: __streambuf_type()
	, _sbs(__sbs)
	, _sb(__sbs.empty() ? 0 : __sbs[0])
	, _pos(__sbs.empty() ? 0 : 1)
	{ _init_when_sequence(); }

#if __cplusplus >= 201103L
	basic_multibuf(__multistreambuf_type&& __sbs)
	: __streambuf_type()
	, _sbs(std::move(__sbs))
	, _sb(_sbs.empty() ? 0 : _sbs[0])
	, _pos(_sbs.empty() ? 0 : 1)
	{ _init_when_sequence(); }

	basic_multibuf(std::initializer_list<__streambuf_type> l)
	: __streambuf_type()
	, _sbs(l)
	, _sb(_sbs.empty() ? 0 : _sbs[0])
	, _pos(_sbs.empty() ? 0 : 1)
	{ _init_when_sequence(); }
#endif

	template<typename _InputIterator>
	basic_multibuf(_InputIterator first, _InputIterator last)
	: __streambuf_type()
	, _sbs(find_first_not_of(first, last, 0), last)
	, _sb(_sbs.empty() ? 0 : _sbs[0])
	, _pos(_sbs.empty() ? 0 : 1)
	{ _init_when_sequence(); }

	virtual ~basic_multibuf()
	{ _rset(_sb); }

	void resetptr()
	{
		_setg();
		_setp();
	}

	void push_back(__streambuf_type* sb)
	{
		if (sb)
		{
			_sbs.push_back(sb);
			if (!_sb)
			{
				_sb = sb;
				_pos = 1;
				resetptr();
			}
		}
	}

	std::size_t size() const
	{ return _sbs.size() - _pos; }

private:
	void _assign_to_fit(__streambuf_type ** first, __streambuf_type ** last,
											__streambuf_type ** cp)
	{
		for (; first != last; ++first)
		{
			if (*first)
			{
				*cp = *first;
				++cp;
			}
		}
		_sbs.resize(&_sbs[0] - cp);
	}

public:
	void assign_to_fit()
	{
		__streambuf_type ** first = &_sbs[_pos];
		__streambuf_type ** last = &_sbs[_sbs.size()];
		if (_pos)
		{
			_assign_to_fit(first, last, &_sbs[0]);
			_pos = 0;
		}
		else
		{
			for (; first != last; ++first)
			{
				if (!*first)
				{
					_assign_to_fit(first + 1, last, first);
					break;
				}
			}
		}
	}

#if __cplusplus >= 201103L
	void shrink_to_fit()
	{
		assign_to_fit();
		_sbs.shrink_to_fit();
	}
#endif

	typedef ptr_container<const __streambuf_type* const> const_rdbufs_type;

	const_rdbufs_type rdbufs() const
	{ return const_rdbufs_type(&_sbs[0], _sbs.size()); }

	void rdbufs(const __multistreambuf_type& sbs)
	{
		__streambuf_type * oldsb = _sb;
		_sbs = sbs;

		if (sbs.empty())
		{
			_sb = 0;
			_pos = 0;
		}
		else
		{
			_sb = sbs[0];
			_pos = 1;
		}

		if (sbs[0] != oldsb)
		{
			_rset(oldsb);
			resetptr();
		}
		if (sbs.empty() && oldsb)
			resetptr();
	}

	void clear()
	{
		_rset(_sb);
		_sbs.clear();
		_pos = 0;
		_sb = 0;
	}

	const __streambuf_type * rdbuf() const
	{ return _sb; }

	__streambuf_type * pop_front()
	{
		__streambuf_type * ret = _sb;
		_rset(_sb);
		_next();
		return ret;
	}

	__streambuf_type * pop_back()
	{ return (_sbs.size() == _pos) ? pop_front() : _sbs.pop_back(); }

protected:
	virtual void
	imbue(const std::locale& __loc)
	{
		for (__iterator first = _sbs.begin(), last = _sbs.end(); first != last; ++first)
			(*first)->pubimbue(__loc);
	}

	virtual __streambuf_type*
	setbuf(char_type* s, std::streamsize n)
	{
		_sb->pubsetbuf(s, n);
		resetptr();
		return this;
	}

	virtual pos_type
	seekoff(off_type __off, std::ios_base::seekdir __way,
					std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
	{ return _sb->pubseekoff(__off, __way, __mode); } ///TODO

	virtual pos_type
	seekpos(pos_type __pos,
					std::ios_base::openmode __mode = std::ios_base::in | std::ios_base::out)
	{ return _sb->pubseekpos(__pos, __mode); } ///TODO

	virtual int
	sync()
	{
		for (__iterator first = _sbs.begin(), last = _sbs.end(); first != last; ++first)
		{
			if (-1 == (*first)->pubsync())
				return -1;
		}
		return 0;
	}

	virtual std::streamsize
	showmanyc()
	{
		std::streamsize ret = 0;
		for (__iterator first = _sbs.begin(), last = _sbs.end(); first != last; ++first)
		{
			std::streamsize tmp = (*first)->in_avail();
			if (-1 == tmp)
				return -1;
			ret += tmp;
		}
		return ret;
	}

	virtual std::streamsize
	xsgetn(char_type* __s, std::streamsize __n)
	{
		std::streamsize ret = 0;
		if (_sb)
		{
			do {
				std::streamsize tmp = _sb->sgetn(__s, __n);
				ret += tmp;
				if (tmp == __n || !_next())
					break;
				__s += tmp;
				__n -= tmp;
			} while (_sb);
			_setg();
		}
		return ret;
	}

	virtual int_type
	underflow()
	{
		int_type ret = traits_type::eof();
		if (_sb)
		{
			for (;;)
			{
				ret = _sb->sgetc();
				if (!traits_type::eq_int_type(ret, traits_type::eof()))
				{
					_setg();
					break;
				}
				if (!_next())
					break;
			}
		}
		return ret;
	}

	virtual int_type
	pbackfail(int_type __c = traits_type::eof())
	{
		return _sb
		? _sb->sputbackc(traits_type::to_char_type(__c))
		: traits_type::eof();
	}

	virtual std::streamsize
	xsputn(const char_type* __s, std::streamsize __n)
	{
		std::streamsize ret = 0;
		if (_sb)
		{
			do {
				std::streamsize tmp = _sb->sputn(__s, __n);
				ret += tmp;
				if (tmp == __n || !_next())
					break;
				__s += tmp;
				__n -= tmp;
			} while (_sb);
			_setp();
		}
		return ret;
	}

	virtual int_type
	overflow(int_type __c = traits_type::eof())
	{
		int_type ret = traits_type::eof();
		if (_sb)
		{
			for (;;)
			{
				ret = _sb->sputc(traits_type::to_char_type(__c));
				if (!traits_type::eq_int_type(ret, traits_type::eof()))
				{
					_setp();
					break;
				}
				if (!_next())
					break;
			}
		}
		return ret;
	}
};

typedef basic_multibuf<char> multistreambuf;
typedef basic_multibuf<wchar_t> wmultistreambuf;

}

#endif