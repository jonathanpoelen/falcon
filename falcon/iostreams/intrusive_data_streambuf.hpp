#ifndef FALCON_IOSTREAMS_INTRUSIVE_DATA_STREAMBUF_HPP
#define FALCON_IOSTREAMS_INTRUSIVE_DATA_STREAMBUF_HPP

#include <iosfwd>

namespace falcon {
namespace iostreams {

// TODO ouvrir/eventrer
template<typename CharT, typename Traits>
class intrusive_data_streambuf final
: std::basic_streambuf<CharT, Traits>
{
  typedef std::basic_streambuf<CharT, Traits> base_;

public:
  using base_::eback;
  using base_::gptr;
  using base_::egptr;
  using base_::gbump;
  using base_::setg;
  using base_::pbase;
  using base_::pptr;
  using base_::epptr;
  using base_::pbump;
  using base_::setp;
  using base_::underflow;
  using base_::uflow;
  using base_::overflow;
};


template<typename CharT, typename Traits>
intrusive_data_streambuf<CharT, Traits> &
intrusive_streambuf(std::basic_streambuf<CharT, Traits> & buf) noexcept
{ return reinterpret_cast<intrusive_data_streambuf<CharT, Traits> &>(buf); }

}
}

#endif
