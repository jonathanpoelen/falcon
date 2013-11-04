// #include <test/A.h>
// #include <type_traits>
// #include <vector>
// #include <iostream>
// #include <falcon/memory/grouping_new.hpp>
//
// #include <falcon/mpl/seq.hpp>
// #include <falcon/mpl/integral.hpp>
// // #include <falcon/mpl/pair.hpp>
//
// using namespace falcon::mpl;
// using namespace falcon::mpl::placeholders;
//
// template< typename N1, typename N2 >
// struct int_plus
// : int_<( N1::value + N2::value )>
// {};
//

#include <iostream>
#include <vector>
#include <falcon/c++1x/unpack.hpp>
#include <falcon/parameter/parameter_index.hpp>
// #include <falcon/iostreams/ioflags.hpp>
#include <falcon/string/basic_cstring.hpp>

namespace falcon { namespace ostream {

template <
  typename CharT
, typename Traits = std::char_traits<CharT>
, typename Allocator = std::allocator<CharT>>
class basic_format
{
  typedef const CharT * const_pointer;
  typedef std::basic_string<CharT, Traits, Allocator> string_type;

public:
  struct item_type {
    const_pointer pptr;
    const_pointer epptr;
    std::size_t n;
  };

  using iterator = std::vector<item_type>::const_iterator;
  using const_iterator = iterator;
  using reverse_iterator = std::vector<item_type>::const_reverse_iterator;
  using const_reverse_iterator = reverse_iterator;

public:
  basic_format() = default;

  basic_format(const string_type & sfmt)
  : fmt(sfmt)
  {
    elems.reserve(4);
    compute_format();
  }

  basic_format(string_type && sfmt)
  : fmt(std::move(sfmt))
  {
    elems.reserve(4);
    compute_format();
  }

  template<typename... Args>
  void operator()(std::basic_ostream<CharT, Traits> & os, const Args&... args) const {
    apply(build_parameter_index_t<sizeof...(Args)>(), os, args...);
  }

  const string_type & format() const
  { return fmt; }

  void format(const string_type & sfmt)
  {
    fmt = sfmt;
    compute_format();
  }

  void format(string_type && sfmt)
  {
    fmt = std::move(sfmt);
    compute_format();
  }

  const_iterator begin() const
  { return elems.begin(); }

  const_iterator end() const
  { return elems.end(); }

  const_iterator cbegin() const
  { return elems.begin(); }

  const_iterator cend() const
  { return elems.end(); }

  const_reverse_iterator rbegin() const
  { return elems.rbegin(); }

  const_reverse_iterator rend() const
  { return elems.rend(); }

  const_reverse_iterator crbegin() const
  { return elems.rbegin(); }

  const_reverse_iterator crend() const
  { return elems.rend(); }

private:
  template<std::size_t... Indexes, typename... Args>
  void apply(parameter_index<Indexes...>,
             std::basic_ostream<CharT, Traits> & os, const Args&... args) const {
    for (item_type & e: elems) {
      os << string_type(e.pptr, e.epptr);
      if (e.n) {
        CPP1X_UNPACK((Indexes+1 == e.n ? void(os << args) : void()));
      }
    }
  }

  void compute_format()
  {
    elems.reserve(4);
    const_pointer pos = fmt.data();
    const_pointer last = pos + fmt.size();
    constexpr typename Traits::char_type zero('0');
    typename string_type::size_type n;
    bool test;
    for (const_pointer first = pos; first != last;) {
      if (Traits::eq(*first, '%')) {
        if (++first == last) {
          break;
        }

        if ((test = Traits::eq(*first, '%')) || !(n = *first - zero)) {
          if (++first == last) {
            break;
          }
          elems.push_back({pos, first-(test ? 1 : 2), 0});
          pos = first;
          continue;
        }

        elems.push_back({pos, first-1, 0});

        if (++first != last && std::isdigit(*first)) {
          n *= 10;
          n += *first - zero;
          if (++first != last && std::isdigit(*first)) {
            n *= 10;
            n += *first - zero;
            if (++first != last && std::isdigit(*first)) {
              n *= 10;
            }
          }
        }

        pos = first;

        elems.back().n = n;
        continue;
      }
      ++first;
    }
    if (pos != last) {
      elems.push_back({pos, last, 0});
    }
  }

private:
  std::vector<item_type> elems;
  string_type fmt;
};

template <
typename CharT
, typename Traits = std::char_traits<CharT>
, typename Allocator = std::allocator<CharT>>
basic_format<CharT, Traits, Allocator>
formatter(const std::basic_string<CharT, Traits, Allocator> & s) {
  return {s};
}

template <typename CharT, typename Traits, std::size_t... Indexes, typename... Args>
std::basic_ostream<CharT, Traits> &
__puts(parameter_index<Indexes...>, std::basic_ostream<CharT, Traits> & os,
       const CharT * fmt, std::size_t fmtlen, const Args&... args)
{
  static_assert(sizeof...(args) < 1000, "too many arguments (the limit is 999)");
  using string_type = const_cstring;
  using traits = string_type::traits_type;
  using const_pointer = const CharT *;
  using size_type = string_type::size_type;
  const_pointer pos = fmt;
  const_pointer last = fmt + fmtlen;
  traits::char_type zero('0');
  bool test;
  size_type n;
  for (const_pointer first = fmt; first != last;) {
    if (traits::eq(*first, '%')) {
      if (++first == last) {
        break;
      }

      if ((test = traits::eq(*first, '%')) || !(n = *first - zero)) {
        if (++first == last) {
          break ;
        }
        os << string_type(pos, first-(test ? 1 : 2));
        pos = first;
        continue;
      }

      os << string_type(pos, first-1);

      if (++first != last && std::isdigit(*first)) {
        n *= 10;
        if (sizeof...(args) > 9) {
          n += *first - zero;
          if (++first != last && std::isdigit(*first)) {
            n *= 10;
            if (sizeof...(args) > 99) {
              n += *first - zero;
              if (++first != last && std::isdigit(*first)) {
                n *= 10;
              }
            }
          }
        }
      }

      if (n > sizeof...(args)) {
        throw std::runtime_error("too many arguments");
      }

      pos = first;
      --n;
      CPP1X_UNPACK((Indexes == n ? void(os << args) : void()));
      continue;
    }
    ++first;
  }
  return os << string_type(pos, last);
}

template <typename CharT, typename Traits, typename... Args>
std::basic_ostream<CharT, Traits> &
puts(std::basic_ostream<CharT, Traits> & os, const char * fmt, const Args&... args)
{
  return __puts(build_parameter_index_t<sizeof...(args)>(), os, fmt,
                std::char_traits<char>::length(fmt), args...);
}

} }

int main()
{
  falcon::ostream::puts(std::cout, "%1%02 %%029 %2\n", 4, 5);
  falcon::ostream::formatter(falcon::const_cstring("%1%02 %%029 %2\n"))(std::cout,  4, 5);


//   using sequence = seq<_1,_2,_3>;
//   using first = begin<sequence>::type;
//   using last = end<sequence>::type;
//   using t1 = deref<first>::type;
//   using first2 = next<first>::type;
//   using t2 = deref<first2>::type;
//   return t1::value + t2::value + deref<prior<last>::type>::type::value;



//   typedef apply_impl< int_plus<_1,_2>, int_<2>, int_<3>, int_<2> >::type r1;
//   return r1::value;
//   typedef apply_impl< if_<arg<4>,_2,_3>, _1, _2, _3, int_<0> >::type r1;
//   typedef apply_or_type_impl_t< if_<_1, _2, _3>, int_<0>, int_<30>, int_<4> > r1;
//   typedef apply< pair<if_<int_plus<_1,_1>, _2, pair<_3,_4>>, _2>, int_<0>, int_<20>, int_<30>, int_<40> >::type r1;
//   typedef apply< pair< if_< int_plus< _1, _1 >, _2, pair< _3, _4 > >, _2 >, int_< 0 >, int_< 20 >, int_< 30 >, int_< 40 > >::type r1;
//   return r1::first::first::value;


//   auto t = falcon::optimal_grouping_allocate<char, int>(falcon::allocate_wrapper<char>(),
//                                                         size_t(12), size_t(32));
//   get<1>(t) = const_cast<char*>("plop");
//   std::cout
//   << (get<0>(t)) << "\n"
//   << (get<1>(t)) << "\n"
//   << (get<2>(t)) << "\n"
//   ;
//
//   auto t2 = falcon::grouping_allocate<char, int>(falcon::allocate_wrapper<char>(),
//                                                  size_t(12), size_t(32));
//   get<0>(t2) = const_cast<char*>("plop");
//   std::cout
//   << (get<0>(t2)) << "\n"
//   << (get<1>(t2)) << "\n"
//   ;

//   falcon::grouping_new<int, char>(2, 4);
//   falcon::grouping_new(falcon::new_element<int>{2}, falcon::new_element<char>{4});
}

