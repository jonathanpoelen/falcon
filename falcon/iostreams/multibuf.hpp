#ifndef FALCON_IOSTREAMULTIBUF_HPP
#define FALCON_IOSTREAMULTIBUF_HPP

#include <falcon/c++1x/assignable.hpp>
#include <falcon/utility/exchange.hpp>
#include <falcon/iostreams/intrusive_data_streambuf.hpp>

#include <streambuf>
#include <vector>
#include <ios>

namespace falcon {
namespace iostreams {

template<class CharT, class Traits = std::char_traits<CharT>>
struct basic_streambuf_generator
{
  typedef std::basic_streambuf<CharT, Traits> streambuf_type;

  CPP1X_DEFAULT_SGI_CONSTRUCTOR(basic_streambuf_generator);

  basic_streambuf_generator(std::initializer_list<streambuf_type *> l)
  : bufs(l)
  {}

  basic_streambuf_generator(std::vector<streambuf_type *> buffers) noexcept
  : bufs(std::move(buffers))
  {}

  template<class InputIterator>
  basic_streambuf_generator(InputIterator first, InputIterator last)
  : bufs(first, last)
  {}

  CPP1X_DEFAULT_SGI_ASSIGNABLE(basic_streambuf_generator);

  basic_streambuf_generator&
  operator=(std::initializer_list<streambuf_type *> l)
  {
    bufs = l;
    gpos = ppos = 0;
    return *this;
  }

  basic_streambuf_generator&
  operator=(std::vector<streambuf_type *> buffers) noexcept
  {
    bufs = std::move(buffers);
    gpos = ppos = 0;
    return *this;
  }

  /// \return next streambuf for the input sequence
  streambuf_type * gnext() noexcept
  {
    if (gpos < bufs.size()) {
      return bufs[gpos++];
    }
    return nullptr;
  }

  /// \return next streambuf for the output sequence
  streambuf_type * pnext() noexcept
  {
    if (ppos < bufs.size()) {
      return bufs[ppos++];
    }
    return nullptr;
  }

private:
  std::vector<streambuf_type *> bufs;
  std::size_t gpos = 0;
  std::size_t ppos = 0;
};


template<typename CharT, typename Traits = std::char_traits<CharT>,
  typename Generator = basic_streambuf_generator<CharT, Traits> >
class basic_multibuf
: public std::basic_streambuf<CharT, Traits>
{
  typedef std::basic_streambuf<CharT, Traits> inherit_streambuf_type_;

public:
  typedef typename inherit_streambuf_type_::char_type char_type;
  typedef typename inherit_streambuf_type_::traits_type traits_type;
  typedef typename inherit_streambuf_type_::int_type int_type;
  typedef typename inherit_streambuf_type_::pos_type pos_type;
  typedef typename inherit_streambuf_type_::off_type off_type;

  typedef Generator streambuf_generator;
  typedef typename streambuf_generator::streambuf_type streambuf_type;


  basic_multibuf() = default;

  basic_multibuf(streambuf_generator const& sbs)
  : gen_(sbs)
  {}

  basic_multibuf(streambuf_generator && sbs)
  : gen_(std::move(sbs))
  {}

  streambuf_generator & get_generator() noexcept
  { return gen_; }

  streambuf_generator const& get_generator() const noexcept
  { return gen_; }

  void get_generator(streambuf_generator const& gen)
  { gen_ = gen; }

  void get_generator(streambuf_generator && gen)
  { gen_ = std::move(gen); }

  streambuf_type * gsbuf() const noexcept
  {
    syncgptr();
    return gsb_;
  }

  streambuf_type * psbuf() const noexcept
  {
    syncpptr();
    return psb_;
  }

  void syncgptr() const noexcept
  {
    if (gsb_) {
      safe_syncgptr_();
    }
  }

  void syncpptr() const noexcept
  {
    if (psb_) {
      safe_syncpptr_();
    }
  }

  void update_gptr() noexcept
  {
    if (gsb_) {
      safe_update_gptr_();
    }
  }

  void update_pptr() noexcept
  {
    if (psb_) {
      safe_update_pptr_();
    }
  }

  /// \brief next input sequence
  bool gnext()
  {
    if (gsb_) {
      safe_syncgptr_();
      this->setg(0, 0, 0);
      gsb_ = nullptr;
      return true;
    }
    else {
      return gen_.gnext();
    }
  }

  /// \brief next output sequence
  bool pnext()
  {
    if (psb_) {
      safe_syncpptr_();
      this->setp(0, 0);
      psb_ = nullptr;
      return true;
    }
    else {
      return gen_.pnext();
    }
  }

protected:
  virtual void
  imbue(std::locale const& loc)
  {
    set_loc_ = true;
    inherit_streambuf_type_::imbue(loc);
    if (gsb_) {
      gsb_->pubimbue(loc);
    }
    if (psb_) {
      psb_->pubimbue(loc);
    }
  }

  virtual basic_multibuf*
  setbuf(char_type* s, std::streamsize n)
  {
    set_buf_ = s;
    set_buf_len_ = n;
    if (gsb_ || psb_) {
      safe_syncgptr_();
      safe_syncpptr_();
      if (gsb_) {
        gsb_->pubsetbuf(s, n);
        safe_update_gptr_();
      }
      if (psb_) {
        psb_->pubsetbuf(s, n);
        safe_update_pptr_();
      }
    }
    return this;
  }

  /**
   * \brief Synchronizes the buffer arrays with the controlled sequences.
   * \return -1 on failure.
   *
   * \note failure if failure with the input or output sequence.
   */
  virtual int
  sync()
  {
    int const gret = gsb_ ? gsb_->pubsync() : 0;
    if (gsb_ == psb_) {
      return gret;
    }
    int const pret = psb_ ? psb_->pubsync() : 0;
    return (pret == -1 || gret == -1) ? -1 : 0;
  }

  /**
   * \brief Synchronizes the buffer arrays with the controlled input sequences.
   * \return -1 on failure.
   */
  int gsync()
  { return gsb_ ? gsb_->pubsync() : -1; }

  /**
   * \brief Synchronizes the buffer arrays with the controlled output sequences.
   * \return -1 on failure.
   */
  int psync()
  { return psb_ ? psb_->pubsync() : -1; }

  virtual std::streamsize
  showmanyc()
  { return gsb_ ? gsb_->in_avail() : -1; }

  virtual std::streamsize
  xsgetn(char_type* s, std::streamsize n)
  {
    std::streamsize ret = 0;
    if (const std::streamsize buf_len = this->egptr() - this->gptr())
    {
      ret = std::min(buf_len, n);
      traits_type::copy(s, this->gptr(), static_cast<std::size_t>(ret));
      this->gbump(static_cast<int>(ret));
    }

    if (ret < n) {
      s += ret;
      syncpptr();
      this->setp(0, 0);

      if (!gsb_ || traits_type::eq_int_type(
        gintrusive().underflow(), traits_type::eof()
      )) {
        gnext_buf();
      }

      while (gsb_ && ret < n) {
        std::streamsize const tmp = gsb_->sgetn(s, n - ret);
        if (tmp <= 0) {
          gnext_buf();
          continue;
        }
        if (tmp != n) {
          gnext_buf();
        }
        s += tmp;
        ret += tmp;
      }

      update_gptr();
      update_pptr();
    }

    return ret;
  }

  virtual int_type
  underflow()
  {
    const int_type eof = traits_type::eof();
    int_type ret = eof;

    if (gsb_)
    {
      syncpptr();
      safe_syncgptr_();
      auto & interbuf = gintrusive();
      //interbuf.gbump(this->egptr() - this->eback());
      ret = interbuf.underflow();
      if (!traits_type::eq_int_type(ret, eof)) {
        safe_update_gptr_();
        update_pptr();
        return ret;
      }
      this->setp(0, 0);
      this->setg(0, 0, 0);
    }

    bool is_eof = true;
    while (gnext_buf()
      && (is_eof = traits_type::eq_int_type(ret = gsb_->sgetc(), eof))
    );

    if (!is_eof) {
      if (gsb_ && gintrusive().gptr() < gintrusive().egptr()) {
        safe_update_gptr_();
      }
      else {
        ic_ = traits_type::to_char_type(ret);
        this->setg(&ic_, &ic_, &ic_ + 1);
      }
    }
    update_pptr();

    return ret;
  }

  virtual int_type
  pbackfail(int_type c = traits_type::eof())
  {
    return gsb_
    ? gsb_->sputbackc(traits_type::to_char_type(c))
    : traits_type::eof();
  }

  virtual std::streamsize
  xsputn(char_type const * s, std::streamsize n)
  {
    std::streamsize ret = 0;
    if (const std::streamsize buf_len = this->epptr() - this->pptr())
    {
      ret = std::min(buf_len, n);
      traits_type::copy(this->pptr(), s, static_cast<std::size_t>(ret));
      this->pbump(static_cast<int>(ret));
    }

    if (ret < n) {
      s += ret;
      syncgptr();
      this->setg(0, 0, 0);

      if (!psb_ || traits_type::eq_int_type(
        pintrusive().overflow(), traits_type::eof()
      )) {
        pnext_buf();
      }

      while (psb_ && ret < n) {
        std::streamsize const tmp = psb_->sputn(s, n - ret);
        if (tmp <= 0) {
          pnext_buf();
          continue;
        }
        if (tmp != n) {
          pnext_buf();
        }
        s += tmp;
        ret += tmp;
      }

      update_gptr();
      update_pptr();
    }

    return ret;
  }

  virtual int_type
  overflow(int_type c = traits_type::eof())
  {
    const int_type eof = traits_type::eof();
    int_type ret = eof;

    if (psb_)
    {
      syncgptr();
      safe_syncpptr_();
      auto & interbuf = pintrusive();
      //interbuf.pbump(this->epptr() - this->pbase());
      ret = interbuf.overflow(c);
      if (!traits_type::eq_int_type(ret, eof)) {
        safe_update_pptr_();
        update_gptr();
        return ret;
      }
      this->setp(0, 0);
      this->setg(0, 0, 0);
    }

    bool is_eof = true;
    const char_type conv = traits_type::to_char_type(c);
    while (pnext_buf()
      && (is_eof = traits_type::eq_int_type(ret = psb_->sputc(conv), eof))
    );

    if (!is_eof) {
      if (psb_ && pintrusive().pbase() < pintrusive().epptr()) {
        safe_update_pptr_();
      }
      else {
        oc_ = traits_type::to_char_type(ret);
        this->setp(&oc_, &oc_ + 1);
      }
    }
    update_gptr();

    return ret;
  }

private:
  bool next_buf(streambuf_type * & oldsb, streambuf_type * newsb)
  {
    oldsb = newsb;
    if (oldsb) {
      if (set_loc_) {
        oldsb->pubimbue(inherit_streambuf_type_::getloc());
      }
      if (set_buf_) {
        oldsb->pubsetbuf(set_buf_, set_buf_len_);
      }
    }
    return oldsb;
  }

  bool gnext_buf()
  { return next_buf(gsb_, gen_.gnext()); }

  bool pnext_buf()
  { return next_buf(psb_, gen_.pnext()); }

  intrusive_data_streambuf<CharT, Traits>& gintrusive() const noexcept
  { return intrusive_streambuf(*gsb_); }

  intrusive_data_streambuf<CharT, Traits>& pintrusive() const noexcept
  { return intrusive_streambuf(*psb_); }

  void safe_syncgptr_() const noexcept
  { gintrusive().setg(this->eback(), this->gptr(), this->egptr()); }

  void safe_syncpptr_() const noexcept
  { pintrusive().setp(this->pptr(), this->epptr()); }

  void safe_update_gptr_() noexcept
  {
    auto & interbuf = gintrusive();
    this->setg(interbuf.eback(), interbuf.gptr(), interbuf.egptr());
  }

  void safe_update_pptr_() noexcept
  {
    auto & interbuf = pintrusive();
    this->setp(interbuf.pptr(), interbuf.epptr());
  }

  streambuf_generator gen_;
  streambuf_type * gsb_ = nullptr;
  streambuf_type * psb_ = nullptr;
  char_type * set_buf_ = nullptr;
  std::streamsize set_buf_len_;
  char_type ic_;
  char_type oc_;
  bool set_loc_ = false;
};

typedef basic_multibuf<char> multibuf;
typedef basic_multibuf<wchar_t> wmultibuf;

typedef basic_streambuf_generator<char> multibuf_generator;
typedef basic_streambuf_generator<wchar_t> wmultibuf_generator;

}
}

#endif
