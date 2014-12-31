#ifndef FALCON_IOSTREAM_MFILEBUF_HPP
#define FALCON_IOSTREAM_MFILEBUF_HPP

#include <falcon/c++1x/assignable.hpp>
#include <falcon/iostreams/multibuf.hpp>
#include <falcon/fn/pair.hpp>
#include <falcon/fn/c_str.hpp>

#include <fstream>
#include <vector>
#include <memory>

namespace falcon {
namespace iostreams {

template<
  class CharT, class Traits = std::char_traits<CharT>
, class String = std::string>
struct basic_filebuf_generator
{
  typedef std::basic_filebuf<CharT, Traits> streambuf_type;

  struct file {
    file(String name, std::ios_base::openmode mode)
    : name(std::move(name))
    , mode(mode)
    {}

    String name;
    std::ios_base::openmode mode;
  };

  CPP1X_DEFAULT_SGI_CONSTRUCTOR(basic_filebuf_generator);

  basic_filebuf_generator(std::initializer_list<file> l)
  : files(l)
  {}

  basic_filebuf_generator(std::vector<file> buffers) noexcept
  : files(std::move(buffers))
  {}

  template<class InputIterator>
  basic_filebuf_generator(InputIterator first, InputIterator last)
  : files(first, last)
  {}

  CPP1X_DEFAULT_SGI_ASSIGNABLE(basic_filebuf_generator);

  basic_filebuf_generator&
  operator=(std::initializer_list<file> l)
  {
    files = l;
    gpos = ppos = 0;
    return *this;
  }

  basic_filebuf_generator&
  operator=(std::vector<file> buffers) noexcept
  {
    files = std::move(buffers);
    gpos = ppos = 0;
    return *this;
  }

  void push_back(file f)
  { files.push_back(std::move(f)); }

  void push_back(String filename, std::ios_base::openmode mode)
  { files.emplace_back(std::move(filename), mode); }

  template<class InputIterator>
  void push_back(InputIterator first, InputIterator last)
  { files.insert(files.end(), first, last); }

  /// \return next streambuf for the input sequence
  streambuf_type * gnext() noexcept
  { return next(fn::first, gpos, true); }

  /// \return next streambuf for the output sequence
  streambuf_type * pnext() noexcept
  { return next(fn::second, ppos, false); }

private:
  template<class GetBuf>
  streambuf_type * next(GetBuf get, std::size_t & pos, bool in) noexcept
  {
    while (pos < files.size()) {
      if (bool(files[pos].mode & std::ios::in) == in) {
        if (!bufs) {
          bufs.reset(new typename decltype(bufs)::element_type);
        }
        streambuf_type & buf = get(*bufs.get());
        buf.close();
        if (buf.open(fn::c_str(files[pos].name), files[pos].mode)) {
          ++pos;
          return &buf;
        }
      }
      ++pos;
    }
    return nullptr;
  }

  std::vector<file> files;
  std::unique_ptr<std::pair<streambuf_type, streambuf_type>> bufs;
  std::size_t gpos = 0;
  std::size_t ppos = 0;
};


template<
  class CharT, class Traits = std::char_traits<CharT>
, class String = std::string>
using basic_mfilebuf = basic_multibuf<
  CharT, Traits
, basic_filebuf_generator<CharT, Traits, String>
>;


typedef basic_mfilebuf<char> mfilebuf;
typedef basic_mfilebuf<wchar_t> wmfilebuf;

}
}

#endif
