#ifndef FALCON_COUNTDOWN_HPP
#define FALCON_COUNTDOWN_HPP

#include <boost/config/select_compiler_config.hpp>
#include <falcon/c++/constexpr.hpp>
#include <limits>

namespace falcon {

template <typename T>
struct basic_countdown
{
  typedef T value_type;

private:
  value_type n_;

public:
  CPP_CONSTEXPR basic_countdown()
  : n_(std::numeric_limits<T>::max())
  {}

  CPP_CONSTEXPR basic_countdown(const T& start)
  : n_(start)
  {}

#if __cplusplus >= 201103L
  explicit operator bool() const
  { return n_ != min_count(); }
#else
  operator void*() const
  { return n_ == min_count() ? 0 : const_cast<basic_countdown*>(this); }
#endif

  void reset(const T& start)
  { n_ = start; }

  CPP_CONSTEXPR T max_count() const
  { return std::numeric_limits<T>::max(); }

  CPP_CONSTEXPR T min_count() const
  { return std::numeric_limits<T>::min(); }

  const T& count() const
  { return n_; }

  bool next()
  {
    --n_;
    return n_ != min_count();
  }
};

typedef basic_countdown<int> icountdown;
typedef basic_countdown<unsigned int> ucountdown;
typedef basic_countdown<long> lcountdown;
typedef basic_countdown<unsigned long> ulcountdown;
#ifdef BOOST_HAS_LONG_LONG
typedef basic_countdown<long long> llcountdown;
typedef basic_countdown<unsigned long long> ullcountdown;
#endif

typedef ucountdown countdown_type;

}

#endif
