#ifndef FALCON_STRING_CSTRING_HPP
#define FALCON_STRING_CSTRING_HPP

#include <falcon/config.hpp>
#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include <falcon/string/cstringfwd.hpp>
#include <falcon/string/stox.hpp>
#include <falcon/container/range_access.hpp>
#include <falcon/iterator/normal_iterator.hpp>

#include <iosfwd>
#include <limits>
#include <utility>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#if __cplusplus >= 201103L
# include <type_traits>
# include <initializer_list>
#else
# include <boost/type_traits/decay.hpp
# include <boost/type_traits/is_array.hpp>
# include <boost/type_traits/is_pointer.hpp>
# include <boost/type_traits/is_integral.hpp>
#endif

namespace falcon { namespace aux_ {

template<typename CharT, typename Traits, typename String,
  bool is_pointer_or_array = FALCON_BOOST_OR_STD_NAMESPACE::is_pointer<
    typename FALCON_BOOST_OR_STD_NAMESPACE::decay<String>::type
  >::value && ! FALCON_BOOST_OR_STD_NAMESPACE::is_array<
    typename FALCON_BOOST_OR_STD_NAMESPACE::decay<String>::type
  >::value
>
struct dispath_cs_cons
{
  CPP_CONSTEXPR static CharT * begin(String & s)
  { return &*::falcon::begin(s); }
  CPP_CONSTEXPR static std::size_t size(String & s)
  { return std::size_t(::falcon::end(s) - ::falcon::begin(s)); }
};

#if __cplusplus > 201103L
template<class Traits>
struct to_constexpr_traits_length
: Traits
{};

template<class CharT>
struct constexpr_length
{
  constexpr static std::size_t length(const CharT * s)
  {
    const CharT * p = s;
    while (*s) {
      ++s;
    }
    return std::size_t(s-p);
  }
};

template<>
struct to_constexpr_traits_length<std::char_traits<char>>
: constexpr_length<char>
{};

template<>
struct to_constexpr_traits_length<std::char_traits<wchar_t>>
: constexpr_length<wchar_t>
{};

template<>
struct to_constexpr_traits_length<std::char_traits<char16_t>>
: constexpr_length<char16_t>
{};

template<>
struct to_constexpr_traits_length<std::char_traits<char32_t>>
: constexpr_length<char32_t>
{};
#endif

template<typename CharT, typename Traits, typename String>
struct dispath_cs_cons<CharT, Traits, String, true>
{
  CPP_CONSTEXPR static CharT * begin(String s)
  { return s; }
#if __cplusplus > 201103L
  CPP_CONSTEXPR static std::size_t size(String s)
  { return to_constexpr_traits_length<Traits>::length(s); }
#else
  static std::size_t size(String s)
  { return Traits::length(s); }
#endif
};

}

struct cstring_array_size{};
struct cstring_array_capacity{};

}

namespace std {

/**
 * @brief Managing sequences of constants characters and constant character-like objects.
 */
template<typename CharT, typename Traits>
class basic_string<CharT, Traits, ::falcon::cstring_allocator<CharT> >
{
  typedef basic_string<CharT, Traits, ::falcon::cstring_allocator<const CharT> > const_cstring;

public:
  typedef Traits traits_type;

  typedef CharT             value_type;

  typedef CharT *           pointer;
  typedef const CharT *     const_pointer;
  typedef CharT &           reference;
  typedef const CharT &     const_reference;
  typedef std::size_t       size_type;
  typedef std::ptrdiff_t    difference_type;

  typedef ::falcon::iterator::normal_iterator<const_pointer>  const_iterator;
  typedef ::falcon::iterator::normal_iterator<pointer>        iterator;

  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef std::reverse_iterator<iterator>       reverse_iterator;

public:
  static const size_type npos = static_cast<size_type>(-1ul);

private:
  pointer m_begin;
  size_type m_size;
  size_type m_capacity;

public:
  CPP_CONSTEXPR basic_string() CPP_NOEXCEPT
  : m_begin(0)
  , m_size(0)
  , m_capacity(0)
  {}

  CPP_CONSTEXPR basic_string(basic_string &&) = default;

#if __cplusplus >= 201103L
  constexpr basic_string(std::nullptr_t) noexcept
  : m_begin(0)
  , m_size(0)
  , m_capacity(0)
  {}
#endif

  template<typename String>
  basic_string(String & s) CPP_NOEXCEPT
  : m_begin(::falcon::aux_::dispath_cs_cons<CharT, Traits, String>::begin(s))
  , m_size(::falcon::aux_::dispath_cs_cons<CharT, Traits, String>::size(s))
  , m_capacity(m_size)
  {}

  template<typename String>
  basic_string(const String & s) CPP_NOEXCEPT
  : m_begin(::falcon::aux_::dispath_cs_cons<CharT, Traits, const String>::begin(s))
  , m_size(::falcon::aux_::dispath_cs_cons<CharT, Traits, const String>::size(s))
  , m_capacity(m_size)
  {}

  template<std::size_t N>
  basic_string(CharT (&s)[N]) CPP_NOEXCEPT
  : m_begin(s)
  , m_size(traits_type::length(s))
  , m_capacity(N)
  {}

  basic_string(pointer s, size_type __size, size_type __capacity) CPP_NOEXCEPT
  : m_begin(s)
  , m_size(__size)
  , m_capacity(__capacity)
  {}

  template<std::size_t N>
  basic_string(CharT (&s)[N], ::falcon::cstring_array_size) CPP_NOEXCEPT
  : m_begin(s)
  , m_size(N-1)
  , m_capacity(N)
  {}

  template<std::size_t N>
  basic_string(CharT (&s)[N], ::falcon::cstring_array_capacity) CPP_NOEXCEPT
  : m_begin(s)
  , m_size(traits_type::length(s))
  , m_capacity(N)
  {}

  template<std::size_t N>
  basic_string(CharT (&s)[N], size_type __size, ::falcon::cstring_array_capacity) CPP_NOEXCEPT
  : m_begin(s)
  , m_size(__size)
  , m_capacity(N)
  {}

  basic_string(pointer s, size_type __size) CPP_NOEXCEPT
  : m_begin(s)
  , m_size(__size)
  , m_capacity(__size)
  {}

  basic_string(pointer first, pointer last) CPP_NOEXCEPT
  : m_begin(first)
  , m_size(last - first)
  , m_capacity(m_size)
  {}

  basic_string(const basic_string& str) CPP_NOEXCEPT
  : m_begin(str.m_begin)
  , m_size(str.m_size)
  , m_capacity(str.m_capacity)
  {}

  basic_string& operator=(basic_string&&) = default;

  basic_string& operator=(const basic_string& str) CPP_NOEXCEPT
  {
    m_begin = str.m_begin;
    m_size = str.m_size;
    m_capacity = str.m_capacity;
    return *this;
  }

  basic_string& operator=(pointer s) CPP_NOEXCEPT
  { return assign(s); }

#if __cplusplus >= 201103L
  basic_string& operator=(std::nullptr_t) noexcept
  {
    clear();
    return *this;
  }
#endif

  reference operator[](size_type index) CPP_NOEXCEPT
  { return m_begin[index]; }

  const_reference operator[](size_type index) const CPP_NOEXCEPT
  { return m_begin[index]; }

  /**
   *  Returns a reference to the data at the first element of the %string.
   */
  reference front() CPP_NOEXCEPT
  { return operator[](0); }

  /**
   *  Returns a read-only (constant) reference to the data at the first
   *  element of the %string.
   */
  const_reference front() const CPP_NOEXCEPT
  { return operator[](0); }

  /**
   *  Returns a reference to the data at the last element of the %string.
   */
  reference back() CPP_NOEXCEPT
  { return operator[](m_size - 1); }

  /**
   *  Returns a read-only (constant) reference to the data at the
   *  last element of the %string.
   */
  const_reference back() const CPP_NOEXCEPT
  { return operator[](m_size - 1); }

  reference at(size_type index)
  {
    if(index >= m_size)
        throw std::out_of_range("basic_string::at");
    return m_begin[index];
  }

  const_reference at(size_type index) const
  {
    if(index >= m_size)
        throw std::out_of_range("basic_string::at");
    return m_begin[index];
  }

  size_type size() const CPP_NOEXCEPT
  { return m_size; }
  size_type length() const CPP_NOEXCEPT
  { return size(); }

  size_type max_size() const CPP_NOEXCEPT
  { return static_cast<size_type>(-1); }

  /**
   *  @brief  Resizes the %string to the specified number of characters.
   *  @param  n  Number of characters the %string should contain.
   *  @param  c  Character to fill any new elements.
   *
   *  This function will %resize the %string to the specified
   *  number of characters.  If the number is smaller than the
   *  %string's current size the %string is truncated, otherwise
   *  the %string is extended and new elements are %set to @a c.
   */
  void resize(size_type n, CharT c)
  {
    if (m_capacity < n)
      throw std::length_error("basic_string::resize");
    priv_assign(priv_data(), n, c);
    m_capacity = n;
    priv_set_length(n);
  }

  void resize(size_type n) CPP_NOEXCEPT
  { resize(n, CharT()); }

  ///  A non-binding request to reduce capacity() to size().
  void shrink_to_fit()
  { m_capacity = m_size; }

  /**
   *  Returns the total number of characters that the %string can hold
   *  before needing to allocate more memory.
   */
  size_type capacity() const CPP_NOEXCEPT
  { return m_capacity; }

  void clear() CPP_NOEXCEPT
  { m_size = 0; }

  bool empty() const CPP_NOEXCEPT
  { return ! m_size; }

  // Modifiers:
  /**
   *  @brief  Append a string to this string.
   *  @param str  The string to append.
   *  @return  Reference to this string.
   */
  basic_string& operator+=(const basic_string& str)
  { return this->append(str); }

  /**
   *  @brief  Append a string to this string.
   *  @param str  The string to append.
   *  @return  Reference to this string.
   */
  basic_string& operator+=(const const_cstring& str)
  { return this->append(str); }

  /**
   *  @brief  Append a C string.
   *  @param s  The C string to append.
   *  @return  Reference to this string.
   */
  basic_string& operator+=(const CharT * s)
  { return this->append(s); }

  /**
   *  @brief  Append a character.
   *  @param c  The character to append.
   *  @return  Reference to this string.
   */
  basic_string& operator+=(CharT c)
  {
    this->push_back(c);
    return *this;
  }

#if __cplusplus >= 201103L
  /**
   *  @brief  Append an initializer_list of characters.
   *  @param l  The initializer_list of characters to be appended.
   *  @return  Reference to this string.
   */
  basic_string& operator+=(std::initializer_list<CharT> l)
  { return this->append(l.begin(), l.size()); }
#endif

  /**
   *  @brief  Append a string to this string.
   *  @param str  The string to append.
   *  @return  Reference to this string.
   *  @throw  std::length_error if new length exceeds @a capacity().
   */
  basic_string& append(const const_cstring& str)
  {
    if (this->capacity() < str.size() + this->size()) {
      throw std::length_error("basic_string::append");
    }
    priv_assign(priv_iend(), str.data(), str.size());
    priv_set_length(str.size());
    return *this;
  }

  basic_string& append(const basic_string& str)
  { return append(str.priv_const_cstring()); }

  /**
   *  @brief  Append a substring.
   *  @param str  The string to append.
   *  @param pos  Index of the first character of str to append.
   *  @param n  The number of characters to append.
   *  @return  Reference to this string.
   *  @throw  std::out_of_range if @a pos is not a valid index.
   *  @throw  std::length_error if final size is not < capacity().
   *
   *  This function appends @a n characters from @a str
   *  starting at @a pos to this string.  If @a n is is larger
   *  than the number of available characters in @a str, the
   *  remainder of @a str is appended.
   */
  basic_string& append(const const_cstring& str, size_type pos, size_type n)
  {
    if (pos < str.size()) {
      throw std::out_of_range("basic_string::append");
    }
    n = str.priv_limit(pos, n);
    const size_type __len = n + this->size();
    if (__len >= this->capacity())
      throw std::length_error("basic_string::append");
    priv_copy(priv_iend(), str.data() + pos, n);
    priv_set_length(__len);
    return *this;
  }

  basic_string& append(const basic_string& str, size_type pos, size_type n)
  { return append(str.priv_const_cstring(), pos, n); }

  /**
   *  @brief  Append a C substring.
   *  @param s  The C string to append.
   *  @param n  The number of characters to append.
   *  @return  Reference to this string.
   *  @throw  std::length_error if final size is not < capacity().
   */
  basic_string& append(const CharT * s, size_type n)
  {
    const size_type __len = n + this->size();
    if (__len >= this->capacity())
      throw std::length_error("basic_string::append");
    priv_copy(priv_iend(), s, n);
    priv_set_length(__len);
    return *this;
  }

  /**
   *  @brief  Append a C string.
   *  @param s  The C string to append.
   *  @return  Reference to this string.
   */
  basic_string& append(const CharT * s)
  { return this->append(s, traits_type::length(s)); }

  /**
   *  @brief  Append multiple characters.
   *  @param n  The number of characters to append.
   *  @param c  The character to use.
   *  @return  Reference to this string.
   *  @throw  std::length_error if final size is not < capacity().
   *
   *  Appends n copies of c to this string.
   */
  basic_string& append(size_type n, CharT c)
  {
    const size_type __len = n + this->size();
    if (__len >= this->capacity())
      throw std::length_error("basic_string::append");
    priv_assign(priv_iend(), n, c);
    priv_set_length(__len);
    return *this;
  }

#if __cplusplus >= 201103L
  /**
   *  @brief  Append an initializer_list of characters.
   *  @param l  The initializer_list of characters to append.
   *  @return  Reference to this string.
   */
  basic_string& append(std::initializer_list<CharT> l)
  { return this->append(l.begin(), l.size()); }
#endif // C++11

  /**
   *  @brief  Append a range of characters.
   *  @param first  Iterator referencing the first character to append.
   *  @param last  Iterator marking the end of the range.
   *  @return  Reference to this string.
   *
   *  Appends characters in the range [first,last) to this string.
   */
  template<class InputIterator>
  basic_string& append(InputIterator first, InputIterator last)
  { return this->replace(priv_iend(), priv_iend(), first, last); }

  /**
   *  @brief  Append a single character.
   *  @param c  Character to append.
   */
  void push_back(CharT c)
  {
    const size_type __len = 1 + this->size();
    if (__len >= this->capacity())
      throw std::length_error("basic_string::append");
    traits_type::assign(*priv_iend(), c);
    priv_set_length(__len);
  }

  /**
   *  @brief  Set value to contents of another string.
   *  @param  str  Source string to use.
   *  @return  Reference to this string.
   *  @throw  std::length_error if !(str.size() < capacity()).
   */
  basic_string& assign(const const_cstring& str)
  { return assign(str.priv_data(), str.size()); }

  basic_string & assign(const basic_string& str) CPP_NOEXCEPT
  { return assign(str.priv_data(), str.size()); }

  basic_string&  assign(pointer first, pointer last) CPP_NOEXCEPT
  { return assign(first, last - first); }

  basic_string& assign(pointer s, size_type len) CPP_NOEXCEPT
  {
    if (len >= this->capacity())
      throw std::length_error("basic_string::assign");
    priv_assign(m_begin, s, len);
    priv_set_length(len);
    return *this;
  }

  /**
   *  @brief  Set value to a substring of a string.
   *  @param str  The string to use.
   *  @param pos  Index of the first character of str.
   *  @param n  Number of characters to use.
   *  @return  Reference to this string.
   *  @throw  std::out_of_range if @a pos is not a valid index.
   *  @throw  std::length_error if final size is not < capacity().
   *
   *  This function sets this string to the substring of @a str
   *  consisting of @a n characters at @a pos.  If @a n is
   *  is larger than the number of available characters in @a
   *  str, the remainder of @a str is used.
   */
  basic_string& assign(const const_cstring& str, size_type pos,
                        size_type n) CPP_NOEXCEPT
  {
    const size_type __len = str.size();
    if (__len < pos)
      throw std::out_of_range("basic_string::append");
    return assign(str.priv_data(), str.priv_limit(pos, n));
  }

  basic_string& assign(const basic_string& str, size_type pos,
                        size_type n) CPP_NOEXCEPT
  { return assign(str.priv_const_cstring(), pos, n); }

  basic_string& assign(const value_type * s) CPP_NOEXCEPT
  { return assign(s, s + traits_type::length(s)); }

  /**
   *  @brief  Set value to multiple characters.
   *  @param n  Length of the resulting string.
   *  @param c  The character to use.
   *  @return  Reference to this string.
   *  @throw  std::length_error if n >= this->capacity().
   *
   *  This function sets the value of this string to @a n copies of
   *  character @a c.
   */
  basic_string& assign(size_type n, CharT c)
  {
    if (n >= this->capacity()) {
      throw std::length_error("basic_string::assign");
    }
    priv_assign(priv_data(), n, c);
    return *this;
  }

  /**
   *  @brief  Set value to a range of characters.
   *  @param first  Iterator referencing the first character to append.
   *  @param last  Iterator marking the end of the range.
   *  @return  Reference to this string.
   *
   *  Sets value of string to characters in the range [first,last).
   */
  template<class InputIterator>
  basic_string& assign(InputIterator first, InputIterator last)
  { return this->replace(begin(), end(), first, last); }

#if __cplusplus >= 201103L
  /**
   *  @brief  Set value to an initializer_list of characters.
   *  @param l  The initializer_list of characters to assign.
   *  @return  Reference to this string.
   */
  basic_string& assign(std::initializer_list<CharT> l)
  { return this->assign(l.begin(), l.size()); }
#endif

  /**
   *  @brief  Insert multiple characters.
   *  @param p  Iterator referencing location in string to insert at.
   *  @param n  Number of characters to insert
   *  @param c  The character to insert.
   *  @throw  std::length_error  If new length exceeds @c max_size().
   *
   *  Inserts @a n copies of character @a c starting at the
   *  position referenced by iterator @a p.  If adding
   *  characters causes the length to exceed max_size(),
   *  length_error is thrown.  The value of the string doesn't
   *  change if an error is thrown.
   */
  void insert(iterator p, size_type n, CharT c)
  { priv_replace_aux(p.base() - priv_data(), 0, n, c);  }

  /**
   *  @brief  Insert a range of characters.
   *  @param p  Iterator referencing location in string to insert at.
   *  @param beg  Start of range.
   *  @param end  End of range.
   *  @throw  std::length_error  If new length exceeds @c max_size().
   *
   *  Inserts characters in range [beg,end).  If adding
   *  characters causes the length to exceed max_size(),
   *  length_error is thrown.  The value of the string doesn't
   *  change if an error is thrown.
   */
  template<class InputIterator>
  void insert(iterator p, InputIterator first, InputIterator last)
  { this->replace(p, p, first, last); }

#if __cplusplus >= 201103L
  /**
   *  @brief  Insert an initializer_list of characters.
   *  @param p  Iterator referencing location in string to insert at.
   *  @param __l  The initializer_list of characters to insert.
   *  @throw  std::length_error  If new length exceeds @c max_size().
   */
  void insert(iterator p, std::initializer_list<CharT> l)
  { this->insert(p - begin(), l.begin(), l.size()); }
#endif

  /**
   *  @brief  Insert value of a string.
   *  @param pos1  Iterator referencing location in string to insert at.
   *  @param str  The string to insert.
   *  @return  Reference to this string.
   *  @throw  std::length_error  If new length exceeds @c max_size().
   *
   *  Inserts value of @a str starting at @a pos1.  If adding
   *  characters causes the length to exceed max_size(),
   *  length_error is thrown.  The value of the string doesn't
   *  change if an error is thrown.
   */
  basic_string& insert(size_type pos1, const basic_string& str)
  { return this->insert(pos1, str, size_type(0), str.size()); }

  basic_string& insert(size_type pos1, const const_cstring& str)
  { return this->insert(pos1, str, size_type(0), str.size()); }

  /**
   *  @brief  Insert a substring.
   *  @param pos1  Iterator referencing location in string to insert at.
   *  @param str  The string to insert.
   *  @param pos2  Start of characters in str to insert.
   *  @param n  Number of characters to insert.
   *  @return  Reference to this string.
   *  @throw  std::length_error  If new length exceeds @c max_size().
   *  @throw  std::out_of_range  If @a pos1 > size() or
   *  @a pos2 > @a str.size().
   *
   *  Starting at @a pos1, insert @a n character of @a str
   *  beginning with @a pos2.  If adding characters causes the
   *  length to exceed max_size(), length_error is thrown.  If @a
   *  pos1 is beyond the end of this string or @a pos2 is
   *  beyond the end of @a str, out_of_range is thrown.  The
   *  value of the string doesn't change if an error is thrown.
   */
  basic_string& insert(size_type pos1, const const_cstring& str,
                        size_type pos2, size_type n)
  {
    if (pos2 >= str.size())
      throw std::out_of_range("basic_string::insert");
    return this->insert(pos1, str.priv_data() + pos2, str.priv_limit(pos2, n));
  }

  basic_string& insert(size_type pos1, const basic_string& str,
                        size_type pos2, size_type n)
  { return this->insert(pos1, str.priv_const_cstring(), pos2, n); }

  /**
   *  @brief  Insert a C substring.
   *  @param pos  Iterator referencing location in string to insert at.
   *  @param s  The C string to insert.
   *  @param n  The number of characters to insert.
   *  @return  Reference to this string.
   *  @throw  std::length_error  If new length exceeds @c capacity().
   *  @throw  std::out_of_range  If @a pos is beyond the end of this
   *  string.
   *
   *  Inserts the first @a n characters of @a s starting at @a
   *  pos.  If adding characters causes the length to exceed
   *  max_size(), length_error is thrown.  If @a pos is beyond
   *  end(), out_of_range is thrown.  The value of the string
   *  doesn't change if an error is thrown.
   */
  basic_string& insert(size_type pos, const CharT * s, size_type n)
  {
    if (pos >= size())
      throw std::out_of_range("basic_string::insert");
    if (size() + n >= this->capacity())
      throw std::length_error("basic_string::insert");
    return priv_insert_safe(pos, s, n);
  }

  /**
   *  @brief  Insert a C string.
   *  @param pos  Iterator referencing location in string to insert at.
   *  @param s  The C string to insert.
   *  @return  Reference to this string.
   *  @throw  std::length_error  If new length exceeds @c max_size().
   *  @throw  std::out_of_range  If @a pos is beyond the end of this
   *  string.
   *
   *  Inserts the first @a n characters of @a s starting at @a pos.  If
   *  adding characters causes the length to exceed max_size(),
   *  length_error is thrown.  If @a pos is beyond end(), out_of_range is
   *  thrown.  The value of the string doesn't change if an error is
   *  thrown.
   */
  basic_string& insert(size_type pos, const CharT* s)
  { return this->insert(pos, s, traits_type::length(s)); }

  /**
   *  @brief  Insert multiple characters.
   *  @param pos  Index in string to insert at.
   *  @param n  Number of characters to insert
   *  @param c  The character to insert.
   *  @return  Reference to this string.
   *  @throw  std::length_error  If new length exceeds @c max_size().
   *  @throw  std::out_of_range  If @a pos is beyond the end of this.
   *  string.
   *
   *  Inserts @a n copies of character @a c starting at index
   *  @a pos.  If adding characters causes the length to exceed
   *  max_size(), length_error is thrown.  If @a pos > length(),
   *  out_of_range is thrown.  The value of the string doesn't
   *  change if an error is thrown.
   */
  basic_string& insert(size_type pos, size_type n, CharT c)
  {
    if (pos >= size())
      throw std::out_of_range("basic_string::insert");
    if (size() + 1 >= this->capacity())
      throw std::length_error("basic_string::insert");

    CharT * p = priv_data() + pos;
    priv_move(p + n, p, size() - pos);
    priv_assign(p, n, c);
    m_size += n;
    return *this;
  }

  /**
   *  @brief  Insert one character.
   *  @param p  Iterator referencing position in string to insert at.
   *  @param c  The character to insert.
   *  @return  Iterator referencing newly inserted char.
   *  @throw  std::length_error  If new length exceeds @c capacity().
   *
   *  Inserts character @a c at position referenced by @a p.
   *  If adding character causes the length to exceed max_size(),
   *  length_error is thrown.  If @a p is beyond end of string,
   *  out_of_range is thrown.  The value of the string doesn't
   *  change if an error is thrown.
   */
  iterator insert(iterator p, CharT c)
  {
    if (size() + 1 >= this->capacity())
      throw std::length_error("basic_string::insert");
    CharT * const __p = p.base();
    priv_move(__p + 1, __p, priv_iend() - __p);
    traits_type::assign(*__p, c);
    ++m_size;
    return p;
  }

  /**
   *  @brief  Remove characters.
   *  @param pos  Index of first character to remove (default 0).
   *  @param n  Number of characters to remove (default remainder).
   *  @return  Reference to this string.
   *  @throw  std::out_of_range  If @a pos is beyond the end of this
   *  string.
   *
   *  Removes @a n characters from this string starting at @a
   *  pos.  The length of the string is reduced by @a n.  If
   *  there are < @a n characters to remove, the remainder of
   *  the string is truncated.  If @a p is beyond end of string,
   *  out_of_range is thrown.  The value of the string doesn't
   *  change if an error is thrown.
   */
  basic_string& erase(size_type pos = 0, size_type n = npos)
  {
    if (pos >= size()) {
      throw std::out_of_range("basic_string::erase");
    }
    n = priv_limit(pos, n);
    size_type len = this->size() - (pos + n);
    if (len) {
      priv_move(priv_data() + pos, priv_data() + pos + n, len);
    }
    m_size -= n;
    return *this;
  }

  /**
   *  @brief  Remove one character.
   *  @param position  Iterator referencing the character to remove.
   *  @return  iterator referencing same location after removal.
   *
   *  Removes the character at @a position from this string. The value
   *  of the string doesn't change if an error is thrown.
   */
  iterator erase(iterator position)
  {
    CharT * p = position.base();
    priv_move(p, p + 1, priv_iend() - p);
    --m_size;
    return position;
  }

  /**
   *  @brief  Remove a range of characters.
   *  @param first  Iterator referencing the first character to remove.
   *  @param last  Iterator referencing the end of the range.
   *  @return  Iterator referencing location of first after removal.
   *
   *  Removes the characters in the range [first,last) from this string.
   *  The value of the string doesn't change if an error is thrown.
   */
  iterator erase(iterator first, iterator last)
  {
    const size_type __size = last - first;
    CharT * p = first.base();
    priv_move(p, p + __size, priv_iend() - last.base());
    m_size -= __size;
    return first;
  }

#if __cplusplus >= 201103L
  /**
   *  @brief  Remove the last character.
   *
   *  The string must be non-empty.
   */
  void pop_back()
  {
    traits_type::assign(*(priv_iend() - 1), *priv_iend());
    return *this;
  }
#endif

  /**
   *  @brief  Replace characters with value from another string.
   *  @param pos  Index of first character to replace.
   *  @param n  Number of characters to be replaced.
   *  @param str  String to insert.
   *  @return  Reference to this string.
   *  @throw  std::out_of_range  If @a pos is beyond the end of this
   *  string.
   *  @throw  std::length_error  If new length exceeds @c max_size().
   *
   *  Removes the characters in the range [pos,pos+n) from
   *  this string.  In place, the value of @a str is inserted.
   *  If @a pos is beyond end of string, out_of_range is thrown.
   *  If the length of the result exceeds max_size(), length_error
   *  is thrown.  The value of the string doesn't change if an
   *  error is thrown.
   */
  basic_string& replace(size_type pos, size_type n, const basic_string& str)
  { return this->replace(pos, n, str.priv_data(), str.size()); }

  basic_string& replace(size_type pos, size_type n, const const_cstring& str)
  { return this->replace(pos, n, str.priv_data(), str.size()); }

  /**
   *  @brief  Replace characters with value from another string.
   *  @param pos1  Index of first character to replace.
   *  @param n1  Number of characters to be replaced.
   *  @param str  String to insert.
   *  @param pos2  Index of first character of str to use.
   *  @param n2  Number of characters from str to use.
   *  @return  Reference to this string.
   *  @throw  std::out_of_range  If @a pos1 > size() or @a pos2 >
   *  str.size().
   *  @throw  std::length_error  If new length exceeds @c max_size().
   *
   *  Removes the characters in the range [pos1,pos1 + n) from this
   *  string.  In place, the value of @a str is inserted.  If @a pos is
   *  beyond end of string, out_of_range is thrown.  If the length of the
   *  result exceeds max_size(), length_error is thrown.  The value of the
   *  string doesn't change if an error is thrown.
   */
  basic_string& replace(size_type pos1, size_type n1, const basic_string& str,
                         size_type pos2, size_type n2)
  {
    if (pos2 > str.size()) {
      throw std::out_of_range("basic_string::replace");
    }
    return this->replace(pos1, n1, str.priv_data() + pos2, str.priv_limit(pos2, n2));
  }

  basic_string& replace(size_type pos1, size_type n1, const const_cstring& str,
                         size_type pos2, size_type n2)
  {
    if (pos2 > str.size()) {
      throw std::out_of_range("basic_string::replace");
    }
    return this->replace(pos1, n1, str.priv_data() + pos2, str.priv_limit(pos2, n2));
  }

  /**
   *  @brief  Replace characters with value of a C substring.
   *  @param pos  Index of first character to replace.
   *  @param n1  Number of characters to be replaced.
   *  @param s  C string to insert.
   *  @param n2  Number of characters from @a s to use.
   *  @return  Reference to this string.
   *  @throw  std::out_of_range  If @a pos1 > size().
   *  @throw  std::length_error  If new length exceeds @c capacity().
   *
   *  Removes the characters in the range [pos,pos + n1)
   *  from this string.  In place, the first @a n2 characters of
   *  @a s are inserted, or all of @a s if @a n2 is too large.  If
   *  @a pos is beyond end of string, out_of_range is thrown.  If
   *  the length of result exceeds capacity(), length_error is
   *  thrown.  The value of the string doesn't change if an error
   *  is thrown.
   */
  basic_string& replace(size_type pos, size_type n1, const CharT* s, size_type n2)
  {
    if (pos > this->size()) {
      throw std::out_of_range("basic_string::replace");
    }
    n1 = priv_limit(pos, n1);
    if (n2 - n1 + this->size() >= this->capacity()) {
      throw std::length_error("basic_string::replace");
    }
    return priv_replace_safe(pos, n1, s, n2);
  }

  /**
   *  @brief  Replace characters with value of a C string.
   *  @param pos  Index of first character to replace.
   *  @param n1  Number of characters to be replaced.
   *  @param s  C string to insert.
   *  @return  Reference to this string.
   *  @throw  std::out_of_range  If @a pos > size().
   *  @throw  std::length_error  If new length exceeds @c max_size().
   *
   *  Removes the characters in the range [pos,pos + n1)
   *  from this string.  In place, the characters of @a s are
   *  inserted.  If @a pos is beyond end of string, out_of_range
   *  is thrown.  If the length of result exceeds max_size(),
   *  length_error is thrown.  The value of the string doesn't
   *  change if an error is thrown.
   */
  basic_string& replace(size_type pos, size_type n1, const CharT * s)
  { return this->replace(pos, n1, s, traits_type::length(s)); }

  /**
   *  @brief  Replace characters with multiple characters.
   *  @param pos  Index of first character to replace.
   *  @param n1  Number of characters to be replaced.
   *  @param n2  Number of characters to insert.
   *  @param c  Character to insert.
   *  @return  Reference to this string.
   *  @throw  std::out_of_range  If @a pos > size().
   *  @throw  std::length_error  If new length exceeds @c max_size().
   *
   *  Removes the characters in the range [pos,pos + n1) from this
   *  string.  In place, @a n2 copies of @a c are inserted.
   *  If @a pos is beyond end of string, out_of_range is thrown.
   *  If the length of result exceeds max_size(), length_error is
   *  thrown.  The value of the string doesn't change if an error
   *  is thrown.
   */
  basic_string& replace(size_type pos, size_type n1, size_type n2, CharT c)
  {
    if (pos > size()) {
      throw std::out_of_range("basic_string::replace");
    }
    return priv_replace_aux(pos, priv_limit(pos, n1), n2, c);
  }

  /**
   *  @brief  Replace range of characters with string.
   *  @param first  Iterator referencing start of range to replace.
   *  @param last  Iterator referencing end of range to replace.
   *  @param str  String value to insert.
   *  @return  Reference to this string.
   *  @throw  std::length_error  If new length exceeds @c max_size().
   *
   *  Removes the characters in the range [first,last).  In place,
   *  the value of @a str is inserted.  If the length of result
   *  exceeds max_size(), length_error is thrown.  The value of
   *  the string doesn't change if an error is thrown.
   */
  basic_string& replace(iterator first, iterator last, const basic_string& str)
  { return this->replace(first, last, str.priv_data(), str.size()); }

  basic_string& replace(iterator first, iterator last, const const_cstring& str)
  { return this->replace(first, last, str.priv_data(), str.size()); }

  /**
   *  @brief  Replace range of characters with C substring.
   *  @param first  Iterator referencing start of range to replace.
   *  @param last  Iterator referencing end of range to replace.
   *  @param s  C string value to insert.
   *  @param n  Number of characters from s to insert.
   *  @return  Reference to this string.
   *  @throw  std::length_error  If new length exceeds @c max_size().
   *
   *  Removes the characters in the range [first,last).  In place,
   *  the first @a n characters of @a s are inserted.  If the
   *  length of result exceeds max_size(), length_error is thrown.
   *  The value of the string doesn't change if an error is
   *  thrown.
   */
  basic_string& replace(iterator first, iterator last, const CharT* s, size_type n)
  { return this->replace(first - priv_ibegin(), last - first, s, n); }

  /**
   *  @brief  Replace range of characters with C string.
   *  @param first  Iterator referencing start of range to replace.
   *  @param last  Iterator referencing end of range to replace.
   *  @param s  C string value to insert.
   *  @return  Reference to this string.
   *  @throw  std::length_error  If new length exceeds @c max_size().
   *
   *  Removes the characters in the range [first,last).  In place,
   *  the characters of @a s are inserted.  If the length of
   *  result exceeds max_size(), length_error is thrown.  The
   *  value of the string doesn't change if an error is thrown.
   */
  basic_string& replace(iterator first, iterator last, const CharT* s)
  { return this->replace(first, last, s, traits_type::length(s)); }

  /**
   *  @brief  Replace range of characters with multiple characters
   *  @param first  Iterator referencing start of range to replace.
   *  @param last  Iterator referencing end of range to replace.
   *  @param n  Number of characters to insert.
   *  @param c  Character to insert.
   *  @return  Reference to this string.
   *  @throw  std::length_error  If new length exceeds @c max_size().
   *
   *  Removes the characters in the range [first,last).  In place,
   *  @a n copies of @a c are inserted.  If the length of
   *  result exceeds max_size(), length_error is thrown.  The
   *  value of the string doesn't change if an error is thrown.
   */
  basic_string& replace(iterator first, iterator last, size_type n, CharT c)
  { return priv_replace_aux(first.base() - priv_data(), last - first, n, c); }

  /**
   *  @brief  Replace range of characters with range.
   *  @param first  Iterator referencing start of range to replace.
   *  @param last  Iterator referencing end of range to replace.
   *  @param k1  Iterator referencing start of range to insert.
   *  @param k2  Iterator referencing end of range to insert.
   *  @return  Reference to this string.
   *  @throw  std::length_error  If new length exceeds @c max_size().
   *
   *  Removes the characters in the range [first,last).  In place,
   *  characters in the range [k1,k2) are inserted.  If the
   *  length of result exceeds max_size(), length_error is thrown.
   *  The value of the string doesn't change if an error is
   *  thrown.
   */
  template<class InputIterator>
  basic_string& replace(iterator first, iterator last,
                         InputIterator k1, InputIterator k2)
  {
    typedef typename FALCON_BOOST_OR_STD_NAMESPACE::is_integral<InputIterator>::type Integral;
    return priv_replace_dispatch(first, last, k1, k2, Integral());
  }

  // Specializations for the common case of pointer and iterator:
  // useful to avoid the overhead of temporary buffering in priv_replace.
  basic_string& replace(iterator first, iterator last, CharT* k1, CharT* k2)
  { return this->replace(first - begin(), last - first, k1, k2 - k1); }

  basic_string& replace(iterator first, iterator last,
                         const CharT * k1, const CharT * k2)
  { return this->replace(first - begin(), last - first, k1, k2 - k1); }

  basic_string& replace(iterator first, iterator last, iterator k1, iterator k2)
  { return this->replace(first - begin(), last - first, k1/*.base()*/, k2 - k1); }

  basic_string& replace(iterator first, iterator last,
                         const_iterator k1, const_iterator k2)
  { return this->replace(first - begin(), last - first, k1/*.base()*/, k2 - k1); }

#if __cplusplus >= 201103L
  /**
   *  @brief  Replace range of characters with initializer_list.
   *  @param first  Iterator referencing start of range to replace.
   *  @param last  Iterator referencing end of range to replace.
   *  @param __l  The initializer_list of characters to insert.
   *  @return  Reference to this string.
   *  @throw  std::length_error  If new length exceeds @c max_size().
   *
   *  Removes the characters in the range [first,last).  In place,
   *  characters in the range [k1,k2) are inserted.  If the
   *  length of result exceeds max_size(), length_error is thrown.
   *  The value of the string doesn't change if an error is
   *  thrown.
   */
  basic_string& replace(iterator first, iterator last,
                         std::initializer_list<CharT> l)
  { return this->replace(first, last, l.begin(), l.end()); }
#endif

  /**
   *  @brief  Copy substring into C string.
   *  @param s  C string to copy value into.
   *  @param n  Number of characters to copy.
   *  @param pos  Index of first character to copy.
   *  @return  Number of characters actually copied
   *  @throw  std::out_of_range  If pos > size().
   *
   *  Copies up to @a n characters starting at @a pos into the C string @a
   *  s.  If @a pos is %greater than size(), out_of_range is thrown.
   */
  size_type copy(CharT * s, size_type n, size_type pos = 0) const
  { return priv_const_cstring().copy(s, n, pos); }

  /**
   *  @brief Returns const pointer to the beginning of string (equivalent to begin())
   *
   *  This is a handle to internal data.  Do not modify or dire things may
   *  happen.
   */
  const_pointer c_str() const CPP_NOEXCEPT
  {
    priv_set_terminal();
    return m_begin;
  }

  /**
   *  @brief  Return const pointer to contents.
   *
   *  This is a handle to internal data.  Do not modify or dire things may
   *  happen.
   */
  const_pointer data() const CPP_NOEXCEPT
  { return m_begin; }

  void swap(basic_string& str) CPP_NOEXCEPT
  {
    using std::swap;
    swap(m_begin, str.m_begin);
    swap(m_size, str.m_size);
  }

  iterator begin() CPP_NOEXCEPT
  { return iterator(m_begin); }
  const_iterator begin() const CPP_NOEXCEPT
  { return const_iterator(m_begin); }

  iterator end() CPP_NOEXCEPT
  { return iterator(m_begin + m_size); }
  const_iterator end() const CPP_NOEXCEPT
  { return const_iterator(m_begin + m_size); }

  reverse_iterator rbegin() CPP_NOEXCEPT
  { return reverse_iterator(m_begin + m_size); }
  const_reverse_iterator rbegin() const CPP_NOEXCEPT
  { return const_reverse_iterator(m_begin + m_size); }

  reverse_iterator rend() CPP_NOEXCEPT
  { return reverse_iterator(m_begin); }
  const_reverse_iterator rend() const CPP_NOEXCEPT
  { return const_reverse_iterator(m_begin); }

#if __cplusplus >= 201103L
  /**
   *  Returns a read-only (constant) iterator that points to the first
   *  character in the %string.
   */
  constexpr const_iterator cbegin() const noexcept
  { return const_iterator(m_begin); }

  /**
   *  Returns a read-only (constant) iterator that points one past the
   *  last character in the %string.
   */
  constexpr const_iterator cend() const noexcept
  { return const_iterator(m_begin + m_size); }

  /**
   *  Returns a read-only (constant) reverse iterator that points
   *  to the last character in the %string.  Iteration is done in
   *  reverse element order.
   */
  constexpr const_reverse_iterator crbegin() const noexcept
  { return const_reverse_iterator(m_begin + m_size); }

  /**
   *  Returns a read-only (constant) reverse iterator that points
   *  to one before the first character in the %string.  Iteration
   *  is done in reverse element order.
   */
  constexpr const_reverse_iterator crend() const noexcept
  { return const_reverse_iterator(m_begin); }
#endif

  /**
   *  @brief  Find position of a C substring.
   *  @param s  C string to locate.
   *  @param pos  Index of character to search from.
   *  @param n  Number of characters from @a s to search for.
   *  @return  Index of start of first occurrence.
   *
   *  Starting from @a pos, searches forward for the first @a n characters
   *  in @a s within this string.  If found, returns the index where it
   *  begins.  If not found, returns npos.
   */
  size_type find(const_pointer s, size_type pos, size_type n) const CPP_NOEXCEPT
  { return priv_const_cstring().find(s, pos, n); }

  /**
   *  @brief  Find position of a string.
   *  @param str  String to locate.
   *  @param pos  Index of character to search from (default 0).
   *  @return  Index of start of first occurrence.
   *
   *  Starting from @a pos, searches forward for value of @a str within
   *  this string.  If found, returns the index where it begins.  If not
   *  found, returns npos.
   */
  size_type find(const basic_string& str, size_type pos = 0) const CPP_NOEXCEPT
  { return priv_const_cstring().find(str, pos); }

  size_type find(const const_cstring& str, size_type pos = 0) const CPP_NOEXCEPT
  { return priv_const_cstring().find(str, pos); }

  /**
   *  @brief  Find position of a C string.
   *  @param s  C string to locate.
   *  @param pos  Index of character to search from (default 0).
   *  @return  Index of start of first occurrence.
   *
   *  Starting from @a pos, searches forward for the value of @a s within
   *  this string.  If found, returns the index where it begins.  If not
   *  found, returns npos.
   */
  size_type find(const_pointer s, size_type pos = 0) const CPP_NOEXCEPT
  { return priv_const_cstring().find(s, pos); }

  /**
   *  @brief  Find position of a character.
   *  @param c  Character to locate.
   *  @param pos  Index of character to search from (default 0).
   *  @return  Index of first occurrence.
   *
   *  Starting from @a pos, searches forward for @a c within this string.
   *  If found, returns the index where it was found.  If not found,
   *  returns npos.
   */
  size_type find(value_type c, size_type pos = 0) const CPP_NOEXCEPT
  { return priv_const_cstring().find(c, pos); }

  /**
   *  @brief  Find last position of a C substring.
   *  @param s  C string to locate.
   *  @param pos  Index of character to search back from.
   *  @param n  Number of characters from s to search for.
   *  @return  Index of start of last occurrence.
   *
   *  Starting from @a pos, searches backward for the first @a n
   *  characters in @a s within this string.  If found, returns the index
   *  where it begins.  If not found, returns npos.
   */
  size_type rfind(const_pointer s, size_type pos, size_type n) const CPP_NOEXCEPT
  { return priv_const_cstring().rfind(s, pos, n); }

  /**
   *  @brief  Find last position of a string.
   *  @param str  String to locate.
   *  @param pos  Index of character to search back from (default end).
   *  @return  Index of start of last occurrence.
   *
   *  Starting from @a pos, searches backward for value of @a str within
   *  this string.  If found, returns the index where it begins.  If not
   *  found, returns npos.
   */
  size_type rfind(const basic_string& str, size_type pos = npos) const CPP_NOEXCEPT
  { return priv_const_cstring().rfind(str, pos); }

  size_type rfind(const const_cstring& str, size_type pos = npos) const CPP_NOEXCEPT
  { return priv_const_cstring().rfind(str, pos); }

  /**
   *  @brief  Find last position of a C string.
   *  @param s  C string to locate.
   *  @param pos  Index of character to start search at (default end).
   *  @return  Index of start of  last occurrence.
   *
   *  Starting from @a pos, searches backward for the value of @a s within
   *  this string.  If found, returns the index where it begins.  If not
   *  found, returns npos.
   */
  size_type rfind(const_pointer s, size_type pos = npos) const CPP_NOEXCEPT
  { return priv_const_cstring().rfind(s, pos); }

  /**
   *  @brief  Find last position of a character.
   *  @param c  Character to locate.
   *  @param pos  Index of character to search back from (default end).
   *  @return  Index of last occurrence.
   *
   *  Starting from @a pos, searches backward for @a c within this string.
   *  If found, returns the index where it was found.  If not found,
   *  returns npos.
   */
  size_type rfind(value_type c, size_type pos = npos) const CPP_NOEXCEPT
  { return priv_const_cstring().rfind(c, pos); }

  /**
   *  @brief  Find position of a character of C substring.
   *  @param s  String containing characters to locate.
   *  @param pos  Index of character to search from.
   *  @param n  Number of characters from s to search for.
   *  @return  Index of first occurrence.
   *
   *  Starting from @a pos, searches forward for one of the first @a n
   *  characters of @a s within this string.  If found, returns the index
   *  where it was found.  If not found, returns npos.
   */
  size_type find_first_of(const_pointer s, size_type pos, size_type n) const CPP_NOEXCEPT
  { return priv_const_cstring().find_first_of(s, pos, n); }

  /**
   *  @brief  Find position of a character of string.
   *  @param str  String containing characters to locate.
   *  @param pos  Index of character to search from (default 0).
   *  @return  Index of first occurrence.
   *
   *  Starting from @a pos, searches forward for one of the characters of
   *  @a str within this string.  If found, returns the index where it was
   *  found.  If not found, returns npos.
   */
  size_type find_first_of(const basic_string& str, size_type pos = 0) const CPP_NOEXCEPT
  { return priv_const_cstring().find_first_of(str, pos); }

  size_type find_first_of(const const_cstring& str, size_type pos = 0) const CPP_NOEXCEPT
  { return priv_const_cstring().find_first_of(str, pos); }

  /**
   *  @brief  Find position of a character of C string.
   *  @param s  String containing characters to locate.
   *  @param pos  Index of character to search from (default 0).
   *  @return  Index of first occurrence.
   *
   *  Starting from @a pos, searches forward for one of the characters of
   *  @a s within this string.  If found, returns the index where it was
   *  found.  If not found, returns npos.
   */
  size_type find_first_of(const_pointer s, size_type pos = 0) const CPP_NOEXCEPT
  { return priv_const_cstring().find_first_of(s, pos); }

  /**
   *  @brief  Find position of a character.
   *  @param c  Character to locate.
   *  @param pos  Index of character to search from (default 0).
   *  @return  Index of first occurrence.
   *
   *  Starting from @a pos, searches forward for the character @a c within
   *  this string.  If found, returns the index where it was found.  If
   *  not found, returns npos.
   *
   *  Note: equivalent to find(c, pos).
   */
  size_type find_first_of(value_type c, size_type pos = 0) const CPP_NOEXCEPT
  { return priv_const_cstring().find_first_of(c, pos); }

  /**
   *  @brief  Find last position of a character of string.
   *  @param str  String containing characters to locate.
   *  @param pos  Index of character to search back from (default end).
   *  @return  Index of last occurrence.
   *
   *  Starting from @a pos, searches backward for one of the characters of
   *  @a str within this string.  If found, returns the index where it was
   *  found.  If not found, returns npos.
   */
  size_type find_last_of(const basic_string& str,
                         size_type pos = npos) const CPP_NOEXCEPT
  { return priv_const_cstring().find_last_of(str, pos); }

  size_type find_last_of(const const_cstring& str,
                         size_type pos = npos) const CPP_NOEXCEPT
  { return priv_const_cstring().find_last_of(str, pos); }

  /**
   *  @brief  Find last position of a character of C substring.
   *  @param s  C string containing characters to locate.
   *  @param pos  Index of character to search back from.
   *  @param n  Number of characters from s to search for.
   *  @return  Index of last occurrence.
   *
   *  Starting from @a pos, searches backward for one of the first @a n
   *  characters of @a s within this string.  If found, returns the index
   *  where it was found.  If not found, returns npos.
   */
  size_type find_last_of(const_pointer s, size_type pos, size_type n) const CPP_NOEXCEPT
  { return priv_const_cstring().find_last_of(s, pos, n); }

  /**
   *  @brief  Find last position of a character of C string.
   *  @param s  C string containing characters to locate.
   *  @param pos  Index of character to search back from (default end).
   *  @return  Index of last occurrence.
   *
   *  Starting from @a pos, searches backward for one of the characters of
   *  @a s within this string.  If found, returns the index where it was
   *  found.  If not found, returns npos.
   */
  size_type find_last_of(const_pointer s, size_type pos = npos) const CPP_NOEXCEPT
  { return priv_const_cstring().find_last_of(s, pos); }

  /**
   *  @brief  Find last position of a character.
   *  @param c  Character to locate.
   *  @param pos  Index of character to search back from (default end).
   *  @return  Index of last occurrence.
   *
   *  Starting from @a pos, searches backward for @a c within this string.
   *  If found, returns the index where it was found.  If not found,
   *  returns npos.
   *
   *  Note: equivalent to rfind(c, pos).
   */
  size_type find_last_of(value_type c, size_type pos = npos) const CPP_NOEXCEPT
  { return priv_const_cstring().find_last_of(c, pos); }

  /**
   *  @brief  Find position of a character not in string.
   *  @param str  String containing characters to avoid.
   *  @param pos  Index of character to search from (default 0).
   *  @return  Index of first occurrence.
   *
   *  Starting from @a pos, searches forward for a character not contained
   *  in @a str within this string.  If found, returns the index where it
   *  was found.  If not found, returns npos.
   */
  size_type find_first_not_of(const basic_string& str,
                              size_type pos = 0) const CPP_NOEXCEPT
  { return priv_const_cstring().find_first_not_of(str, pos); }

  size_type find_first_not_of(const const_cstring& str,
                              size_type pos = 0) const CPP_NOEXCEPT
  { return priv_const_cstring().find_first_not_of(str, pos); }

  /**
   *  @brief  Find position of a character not in C substring.
   *  @param s  C string containing characters to avoid.
   *  @param pos  Index of character to search from.
   *  @param n  Number of characters from s to consider.
   *  @return  Index of first occurrence.
   *
   *  Starting from @a pos, searches forward for a character not contained
   *  in the first @a n characters of @a s within this string.  If found,
   *  returns the index where it was found.  If not found, returns npos.
   */
  size_type find_first_not_of(const_pointer s, size_type pos, size_type n) const CPP_NOEXCEPT
  { return priv_const_cstring().find_first_not_of(s, pos, n); }

  /**
   *  @brief  Find position of a character not in C string.
   *  @param s  C string containing characters to avoid.
   *  @param pos  Index of character to search from (default 0).
   *  @return  Index of first occurrence.
   *
   *  Starting from @a pos, searches forward for a character not contained
   *  in @a s within this string.  If found, returns the index where it
   *  was found.  If not found, returns npos.
   */
  size_type find_first_not_of(const_pointer s, size_type pos = 0) const CPP_NOEXCEPT
  { return priv_const_cstring().find_first_not_of(s, pos); }

  /**
   *  @brief  Find position of a different character.
   *  @param c  Character to avoid.
   *  @param pos  Index of character to search from (default 0).
   *  @return  Index of first occurrence.
   *
   *  Starting from @a pos, searches forward for a character other than @a c
   *  within this string.  If found, returns the index where it was found.
   *  If not found, returns npos.
   */
  size_type find_first_not_of(value_type c, size_type pos = 0) const CPP_NOEXCEPT
  { return priv_const_cstring().find_first_not_of(c, pos); }

  /**
   *  @brief  Find last position of a character not in string.
   *  @param str  String containing characters to avoid.
   *  @param pos  Index of character to search back from (default end).
   *  @return  Index of last occurrence.
   *
   *  Starting from @a pos, searches backward for a character not
   *  contained in @a str within this string.  If found, returns the index
   *  where it was found.  If not found, returns npos.
   */
  size_type find_last_not_of(const basic_string& str,
                             size_type pos = npos) const CPP_NOEXCEPT
  { return priv_const_cstring().find_last_not_of(str, pos); }

  size_type find_last_not_of(const const_cstring& str,
                             size_type pos = npos) const CPP_NOEXCEPT
  { return priv_const_cstring().find_last_not_of(str, pos); }

  /**
   *  @brief  Find last position of a character not in C substring.
   *  @param s  C string containing characters to avoid.
   *  @param pos  Index of character to search back from.
   *  @param n  Number of characters from s to consider.
   *  @return  Index of last occurrence.
   *
   *  Starting from @a pos, searches backward for a character not
   *  contained in the first @a n characters of @a s within this string.
   *  If found, returns the index where it was found.  If not found,
   *  returns npos.
   */
  size_type find_last_not_of(const_pointer s, size_type pos, size_type n) const CPP_NOEXCEPT
  { return priv_const_cstring().find_last_not_of(s, pos, n); }

  /**
   *  @brief  Find last position of a character not in C string.
   *  @param s  C string containing characters to avoid.
   *  @param pos  Index of character to search back from (default end).
   *  @return  Index of last occurrence.
   *
   *  Starting from @a pos, searches backward for a character not
   *  contained in @a s within this string.  If found, returns the index
   *  where it was found.  If not found, returns npos.
   */
  size_type find_last_not_of(const_pointer s, size_type pos = npos) const CPP_NOEXCEPT
  { return priv_const_cstring().find_last_not_of(s, pos); }

  /**
   *  @brief  Find last position of a different character.
   *  @param c  Character to avoid.
   *  @param pos  Index of character to search back from (default end).
   *  @return  Index of last occurrence.
   *
   *  Starting from @a pos, searches backward for a character other than
   *  @a c within this string.  If found, returns the index where it was
   *  found.  If not found, returns npos.
   */
  size_type find_last_not_of(value_type c, size_type pos = npos) const CPP_NOEXCEPT
  { return priv_const_cstring().find_last_not_of(c, pos); }

  /**
   *  @brief  Get a substring.
   *  @param pos  Index of first character (default 0).
   *  @param n  Number of characters in substring (default remainder).
   *  @return  The new string.
   *  @throw  std::out_of_range  If pos > size().
   *
   *  Construct and return a new string using the @a n characters starting
   *  at @a pos.  If the string is too short, use the remainder of the
   *  characters.  If @a pos is beyond the end of the string, out_of_range
   *  is thrown.
   */
  basic_string substr(size_type pos = 0, size_type n = npos) const
  {
    if (pos > size())
      throw std::out_of_range("basic_string::substr");
    return basic_string(m_begin + pos, m_begin + pos + priv_limit(pos, n));
  }

  /**
   *  @brief  Compare to a string.
   *  @param str  String to compare against.
   *  @return  Integer < 0, 0, or > 0.
   *
   *  Returns an integer < 0 if this string is ordered before @a str, 0 if
   *  their values are equivalent, or > 0 if this string is ordered after
   *  @a str.  Determines the effective length rlen of the strings to
   *  compare as the smallest of size() and str.size().  The function
   *  then compares the two strings by calling traits::compare(data(),
   *  str.data(),rlen).  If the result of the comparison is nonzero returns
   *  it, otherwise the shorter one is ordered first.
   */
  int compare(const basic_string& str) const CPP_NOEXCEPT
  { return priv_const_cstring().compare(str); }

  int compare(const const_cstring& str) const CPP_NOEXCEPT
  { return priv_const_cstring().compare(str); }

  /**
   *  @brief  Compare substring to a string.
   *  @param pos  Index of first character of substring.
   *  @param n  Number of characters in substring.
   *  @param str  String to compare against.
   *  @return  Integer < 0, 0, or > 0.
   *
   *  Form the substring of this string from the @a n characters starting
   *  at @a pos.  Returns an integer < 0 if the substring is ordered
   *  before @a str, 0 if their values are equivalent, or > 0 if the
   *  substring is ordered after @a str.  Determines the effective length
   *  rlen of the strings to compare as the smallest of the length of the
   *  substring and @a str.size().  The function then compares the two
   *  strings by calling traits::compare(substring.data(),str.data(),rlen).
   *  If the result of the comparison is nonzero returns it, otherwise the
   *  shorter one is ordered first.
   */
  int compare(size_type pos, size_type n, const basic_string& str) const
  { return priv_const_cstring().compare(pos, n, str); }

  int compare(size_type pos, size_type n, const const_cstring& str) const
  { return priv_const_cstring().compare(pos, n, str); }

  /**
   *  @brief  Compare substring to a substring.
   *  @param pos1  Index of first character of substring.
   *  @param n1  Number of characters in substring.
   *  @param str  String to compare against.
   *  @param pos2  Index of first character of substring of str.
   *  @param n2  Number of characters in substring of str.
   *  @return  Integer < 0, 0, or > 0.
   *
   *  Form the substring of this string from the @a n1 characters starting
   *  at @a pos1.  Form the substring of @a str from the @a n2 characters
   *  starting at @a pos2.  Returns an integer < 0 if this substring is
   *  ordered before the substring of @a str, 0 if their values are
   *  equivalent, or > 0 if this substring is ordered after the substring
   *  of @a str.  Determines the effective length rlen of the strings
   *  to compare as the smallest of the lengths of the substrings.  The
   *  function then compares the two strings by calling
   *  traits::compare(substring.data(),str.substr(pos2,n2).data(),rlen).
   *  If the result of the comparison is nonzero returns it, otherwise the
   *  shorter one is ordered first.
   */
  int compare(size_type pos1, size_type n1, const basic_string& str,
              size_type pos2, size_type n2) const
  { return priv_const_cstring().compare(pos1, n1, str, pos2, n2); }

  int compare(size_type pos1, size_type n1, const const_cstring& str,
              size_type pos2, size_type n2) const
  { return priv_const_cstring().compare(pos1, n1, str, pos2, n2); }

  /**
   *  @brief  Compare to a C string.
   *  @param s  C string to compare against.
   *  @return  Integer < 0, 0, or > 0.
   *
   *  Returns an integer < 0 if this string is ordered before @a s, 0 if
   *  their values are equivalent, or > 0 if this string is ordered after
   *  @a s.  Determines the effective length rlen of the strings to
   *  compare as the smallest of size() and the length of a string
   *  constructed from @a s.  The function then compares the two strings
   *  by calling traits::compare(data(),s,rlen).  If the result of the
   *  comparison is nonzero returns it, otherwise the shorter one is
   *  ordered first.
   */
  int compare(const_pointer s) const CPP_NOEXCEPT
  { return priv_const_cstring().compare(s); }

  /**
   *  @brief  Compare substring to a C string.
   *  @param pos  Index of first character of substring.
   *  @param n1  Number of characters in substring.
   *  @param s  C string to compare against.
   *  @return  Integer < 0, 0, or > 0.
   *
   *  Form the substring of this string from the @a n1 characters starting
   *  at @a pos.  Returns an integer < 0 if the substring is ordered
   *  before @a s, 0 if their values are equivalent, or > 0 if the
   *  substring is ordered after @a s.  Determines the effective length
   *  rlen of the strings to compare as the smallest of the length of the
   *  substring and the length of a string constructed from @a s.  The
   *  function then compares the two string by calling
   *  traits::compare(substring.data(),s,rlen).  If the result of the
   *  comparison is nonzero returns it, otherwise the shorter one is
   *  ordered first.
   */
  int compare(size_type pos, size_type n1, const_pointer s) const
  { return priv_const_cstring().compare(pos, n1, s); }

  /**
   *  @brief  Compare substring against a character %array.
   *  @param pos1  Index of first character of substring.
   *  @param n1  Number of characters in substring.
   *  @param s  character %array to compare against.
   *  @param n2  Number of characters of s.
   *  @return  Integer < 0, 0, or > 0.
   *
   *  Form the substring of this string from the @a n1 characters starting
   *  at @a pos1.  Form a string from the first @a n2 characters of @a s.
   *  Returns an integer < 0 if this substring is ordered before the string
   *  from @a s, 0 if their values are equivalent, or > 0 if this substring
   *  is ordered after the string from @a s.   Determines the effective
   *  length rlen of the strings to compare as the smallest of the length
   *  of the substring and @a n2.  The function then compares the two
   *  strings by calling traits::compare(substring.data(),s,rlen).  If the
   *  result of the comparison is nonzero returns it, otherwise the shorter
   *  one is ordered first.
   *
   *  NB: s must have at least n2 characters, &apos;\\0&apos; has
   *  no special meaning.
   */
  int compare(size_type pos, size_type n1, const_pointer s, size_type n2) const
  { return priv_const_cstring().compare(pos, n1, s, n2); }

private:
  size_type priv_limit(size_type pos, size_type off) const CPP_NOEXCEPT
  { return std::min(off, this->size() - pos); }

  // When n = 1 way faster than the general multichar
  // traits_type::copy/move/assign.
  static void priv_copy(CharT* d, const CharT* s, size_type n) CPP_NOEXCEPT
  {
    if (n == 1)
      traits_type::assign(*d, *s);
    else
      traits_type::copy(d, s, n);
  }

  static void priv_move(CharT* d, const CharT * s, size_type n) CPP_NOEXCEPT
  {
    if (n == 1)
      traits_type::assign(*d, *s);
    else
      traits_type::move(d, s, n);
  }

  static void priv_assign(CharT* d, size_type n, CharT c) CPP_NOEXCEPT
  {
    if (n == 1)
      traits_type::assign(*d, c);
    else
      traits_type::assign(d, n, c);
  }

  CPP_CONSTEXPR
#ifdef IN_IDE_PARSER
  basic_string&
#else
  const_cstring
#endif
  priv_const_cstring() const CPP_NOEXCEPT
  { return const_cstring(m_begin, m_size); }

  pointer priv_ibegin() const CPP_NOEXCEPT
  { return m_begin; }
  pointer priv_data() const CPP_NOEXCEPT
  { return m_begin; }

  pointer priv_iend() const CPP_NOEXCEPT
  { return m_begin + m_size; }

  void priv_set_length(size_type len) CPP_NOEXCEPT
  { m_size = len; }

  void priv_set_terminal() const CPP_NOEXCEPT
  {
    if (m_capacity) {
      traits_type::assign(m_begin[m_size], CharT());
    }
  }

  /**
   *  @brief  Replace characters with multiple characters.
   *  @param pos  Index of first character to replace. Should be a valid position.
   *  @param n1  Number of characters to be replaced.
   *  @param n2  Number of characters to insert.
   *  @param c  Character to insert.
   */
  basic_string& priv_replace_aux(size_type pos, size_type n1, size_type n2, CharT c)
  {
    if (n2 - n1 + this->size() >= this->capacity()) {
      throw std::length_error("basic_string::priv_replace_aux");
    }

    CharT * p = priv_data() + pos;
    if (n1 != n2) {
      const size_type len = size() - (pos + n1);
      priv_move(p + n2, p + n1, len);
    }
    priv_assign(p, n2, c);

    return *this;
  }

  basic_string& priv_replace_safe(size_type pos, size_type n1,
                                  const CharT * s, size_type n2) CPP_NOEXCEPT
  {
    CharT * p = priv_data() + pos;
    const size_type n = std::min(n1, n2);
    if (s >= p + n || s + n <= p) {
      priv_copy(p, s, n);
    }
    else if (s < p) {
      const size_type nleft = static_cast<size_type>(p - s);
      const size_type nright = n - nleft;
      priv_copy(p + nleft, p, nright);
      priv_copy(p, s, nleft);
    }
    else if (s < p + n) {
      const size_type nright = static_cast<size_type>(s - p);
      const size_type nleft = n - nright;
      priv_copy(p, s, nleft);
      priv_copy(p + nleft, p + n, nright);
    }

    if (n < n1) {
      priv_move(p + n, p + n1, size() - n1);
    }
    else if (n < n2) {
      priv_insert_safe(pos + n, s, size() - n2);
    }

    m_size += n2 - n1;

    return *this;
  }

  basic_string& priv_insert_safe(size_type pos, const CharT * s,
                                 size_type n) CPP_NOEXCEPT
  {
    CharT * p = priv_data() + pos;
    if (s > p && s + n > priv_iend()) {
      const size_type nleft = static_cast<size_type>(s - p);
      for (size_type i = 0; i < nleft; ++i) {
        CharT * pp = p + i;
        CharT * plast = pp + (n - (n - i) % nleft);
        const CharT c = *pp;
        for (; pp < plast; pp += nleft) {
          traits_type::assign(*pp, *(pp + nleft));
        }
        traits_type::assign(*pp, c);
      }
      traits_type::assign(m_begin[m_size + n], CharT());
      priv_copy(p + n + nleft, p, size() - pos - nleft);
    }
    else if (s + n <= p || s >= priv_iend() + n) {
      priv_copy(p + n, p, size() - pos);
      priv_copy(p, s, n);
    }
    else if (s < p) {
      priv_copy(p + n, p, size() - pos);
      const size_type nleft = static_cast<size_type>(p - s);
      const size_type nright = n - nleft;
      priv_move(p + nleft, p, nright);
      priv_copy(p, s, nleft);
    }
    else {
      priv_move(p + n, p, size() - pos);
      priv_copy(p, s + n, n);
    }
    m_size += n;
    return *this;
  }

  template<typename InputIterator>
  basic_string& priv_replace_dispatch(iterator first, iterator last,
                                      InputIterator k1, InputIterator k2,
                                      FALCON_BOOST_OR_STD_NAMESPACE::false_type)
  {
    return priv_replace_aux(first.base() - priv_data(), last - first,
                            priv_data() + (k1.base() - priv_data()), k2 - k1);
  }

  template<class Integer>
  basic_string& priv_replace_dispatch(iterator i1, iterator i2,
                                      Integer n, Integer val,
                                      FALCON_BOOST_OR_STD_NAMESPACE::true_type)
  { return priv_replace_aux(i1.base() - priv_data(), i2 - i1, n, val); }
};

template<typename CharT, typename Traits>
class basic_string<CharT, Traits, ::falcon::cstring_allocator<const CharT> >
{
  typedef basic_string<CharT, Traits, ::falcon::cstring_allocator<CharT> > cstring;

public:
  typedef Traits traits_type;

  typedef CharT             value_type;

  typedef const CharT *     pointer;
  typedef const CharT *     const_pointer;
  typedef const CharT &     reference;
  typedef const CharT &     const_reference;
  typedef std::size_t       size_type;
  typedef std::ptrdiff_t    difference_type;

  typedef ::falcon::iterator::normal_iterator<const_pointer>  const_iterator;
  typedef ::falcon::iterator::normal_iterator<pointer>        iterator;

  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef std::reverse_iterator<iterator>       reverse_iterator;

public:
  static const size_type npos = static_cast<size_type>(-1ul);

private:
  pointer m_begin;
  size_type m_size;

public:
  CPP_CONSTEXPR basic_string() CPP_NOEXCEPT
  : m_begin(0)
  , m_size(0)
  {}

  CPP_CONSTEXPR basic_string(basic_string &&) = default;

#if __cplusplus >= 201103L
  constexpr basic_string(std::nullptr_t) noexcept
  : m_begin(0)
  , m_size(0)
  {}
#endif

  template<std::size_t N>
  CPP_CONSTEXPR basic_string(const CharT (&s)[N]) CPP_NOEXCEPT
  : m_begin(s)
  , m_size(::falcon::aux_::dispath_cs_cons<const CharT, Traits, CharT const *, true>::size(s))
  {}

  template<std::size_t N>
  CPP_CONSTEXPR basic_string(const CharT (&s)[N], ::falcon::cstring_array_size) CPP_NOEXCEPT
  : m_begin(s)
  , m_size(N - 1)
  {}

  template<typename String>
  CPP_CONSTEXPR basic_string(String & s) CPP_NOEXCEPT
  : m_begin(::falcon::aux_::dispath_cs_cons<const CharT, Traits, String>::begin(s))
  , m_size(::falcon::aux_::dispath_cs_cons<const CharT, Traits, String>::size(s))
  {}

  template<typename String>
  CPP_CONSTEXPR basic_string(const String & s) CPP_NOEXCEPT
  : m_begin(::falcon::aux_::dispath_cs_cons<const CharT, Traits, const String>::begin(s))
  , m_size(::falcon::aux_::dispath_cs_cons<const CharT, Traits, const String>::size(s))
  {}

  CPP_CONSTEXPR basic_string(pointer s, size_type __size) CPP_NOEXCEPT
  : m_begin(s)
  , m_size(__size)
  {}

  CPP_CONSTEXPR basic_string(pointer first, pointer last) CPP_NOEXCEPT
  : m_begin(first)
  , m_size(size_type(last - first))
  {}

  CPP_CONSTEXPR basic_string(const basic_string& str) CPP_NOEXCEPT
  : m_begin(str.m_begin)
  , m_size(str.m_size)
  {}

  basic_string(const cstring& str) CPP_NOEXCEPT
  : m_begin(str.data())
  , m_size(str.size())
  {}

  basic_string& operator=(basic_string&&) = default;

  basic_string& operator=(const basic_string& str) CPP_NOEXCEPT
  { return assign(str); }

  basic_string& operator=(const cstring& str) CPP_NOEXCEPT
  { return assign(str); }

  basic_string& operator=(pointer s) CPP_NOEXCEPT
  { return assign(s); }

#if __cplusplus >= 201103L
  basic_string& operator=(std::nullptr_t) noexcept
  {
    clear();
    return *this;
  }
#endif

  CPP_CONSTEXPR const_reference operator[](size_type index) const CPP_NOEXCEPT
  { return m_begin[index]; }

  /**
   *  Returns a read-only (constant) reference to the data at the first
   *  element of the %string.
   */
  CPP_CONSTEXPR const_reference front() const CPP_NOEXCEPT
  { return operator[](0); }

  /**
   *  Returns a read-only (constant) reference to the data at the
   *  last element of the %string.
   */
  CPP_CONSTEXPR const_reference back() const CPP_NOEXCEPT
  { return operator[](m_size - 1); }

  CPP_CONSTEXPR const_reference at(size_type index) const
  {
    return ((m_begin + index >= m_size) ?
      throw std::out_of_range("basic_string::at") :
      void()), m_begin[index];
  }

  CPP_CONSTEXPR size_type size() const CPP_NOEXCEPT
  { return m_size; }
  CPP_CONSTEXPR size_type length() const CPP_NOEXCEPT
  { return size(); }

  CPP_CONSTEXPR size_type max_size() const CPP_NOEXCEPT
  { return size(); }

  CPP_CONSTEXPR bool empty() const CPP_NOEXCEPT
  { return ! m_size; }

  void clear() CPP_NOEXCEPT
  { m_size = 0; }

  basic_string& assign(const basic_string& str) CPP_NOEXCEPT
  { return assign(str.m_begin, str.m_size); }

  basic_string & assign(const cstring& str) CPP_NOEXCEPT
  { return assign(str.data(), str.size()); }

  basic_string&  assign(pointer first, pointer last) CPP_NOEXCEPT
  { return assign(first, last - first); }

  basic_string& assign(pointer s, size_type len) CPP_NOEXCEPT
  {
    m_begin = s;
    m_size = len;
    return *this;
  }

  basic_string& assign(const basic_string& str, size_type pos,
                       size_type len) CPP_NOEXCEPT
  { return assign(str + pos, len); }

  basic_string& assign(const cstring& str, size_type pos, size_type len) CPP_NOEXCEPT
  { return assign(str.data() + pos, len); }

  basic_string& assign(pointer s) CPP_NOEXCEPT
  { assign(s, traits_type::length(s)); }

  /**
   *  @brief  Copy substring into C string.
   *  @param s  C string to copy value into.
   *  @param n  Number of characters to copy.
   *  @param pos  Index of first character to copy.
   *  @return  Number of characters actually copied
   *  @throw  std::out_of_range  If pos > size().
   *
   *  Copies up to @a n characters starting at @a pos into the C string @a
   *  s.  If @a pos is %greater than size(), out_of_range is thrown.
   */
  size_type copy(CharT * s, size_type n, size_type pos = 0) const
  {
    if (pos > size())
      throw std::out_of_range("basic_string::copy");
    n = priv_limit(pos, n);
    traits_type::copy(s, data() + pos, n);
    return n;
  }

  /**
   *  @brief Returns const pointer to the beginning of string (equivalent to begin())
   *
   *  This is a handle to internal data.  Do not modify or dire things may
   *  happen.
   */
  CPP_CONSTEXPR const_pointer c_str() const CPP_NOEXCEPT
  { return m_begin; }

  /**
   *  @brief  Return const pointer to contents.
   *
   *  This is a handle to internal data.  Do not modify or dire things may
   *  happen.
   */
  CPP_CONSTEXPR const_pointer data() const CPP_NOEXCEPT
  { return m_begin; }

  void swap(basic_string& str) CPP_NOEXCEPT
  {
    using std::swap;
    swap(m_begin, str.m_begin);
    swap(m_size, str.m_size);
  }

  CPP_CONSTEXPR const_iterator begin() const CPP_NOEXCEPT
  { return const_iterator(m_begin); }

  CPP_CONSTEXPR const_iterator end() const CPP_NOEXCEPT
  { return const_iterator(m_begin + m_size); }

  CPP_CONSTEXPR const_reverse_iterator rbegin() const CPP_NOEXCEPT
  { return const_reverse_iterator(m_begin + m_size); }

  CPP_CONSTEXPR const_reverse_iterator rend() const CPP_NOEXCEPT
  { return const_reverse_iterator(m_begin); }

#if __cplusplus >= 201103L
  /**
   *  Returns a read-only (constant) iterator that points to the first
   *  character in the %string.
   */
  constexpr const_iterator cbegin() const noexcept
  { return const_iterator(m_begin); }

  /**
   *  Returns a read-only (constant) iterator that points one past the
   *  last character in the %string.
   */
  constexpr const_iterator cend() const noexcept
  { return const_iterator(m_begin + m_size); }

  /**
   *  Returns a read-only (constant) reverse iterator that points
   *  to the last character in the %string.  Iteration is done in
   *  reverse element order.
   */
  constexpr const_reverse_iterator crbegin() const noexcept
  { return const_reverse_iterator(m_begin + m_size); }

  /**
   *  Returns a read-only (constant) reverse iterator that points
   *  to one before the first character in the %string.  Iteration
   *  is done in reverse element order.
   */
  constexpr const_reverse_iterator crend() const noexcept
  { return const_reverse_iterator(m_begin); }
#endif

  /**
   *  @brief  Find position of a C substring.
   *  @param s  C string to locate.
   *  @param pos  Index of character to search from.
   *  @param n  Number of characters from @a s to search for.
   *  @return  Index of start of first occurrence.
   *
   *  Starting from @a pos, searches forward for the first @a n characters
   *  in @a s within this string.  If found, returns the index where it
   *  begins.  If not found, returns npos.
   */
  size_type find(const_pointer s, size_type pos, size_type n) const CPP_NOEXCEPT
  {
    const size_type __size = size();
    const_pointer __data = data();

    if (n == 0)
      return pos <= __size ? pos : npos;

    if (n <= __size)
    {
      for (; pos <= __size - n; ++pos)
        if (traits_type::eq(__data[pos], s[0])
          && traits_type::compare(__data + pos + 1, s + 1, n - 1) == 0)
          return pos;
    }
    return npos;
  }

  /**
   *  @brief  Find position of a string.
   *  @param str  String to locate.
   *  @param pos  Index of character to search from (default 0).
   *  @return  Index of start of first occurrence.
   *
   *  Starting from @a pos, searches forward for value of @a str within
   *  this string.  If found, returns the index where it begins.  If not
   *  found, returns npos.
   */
  size_type find(const basic_string& str, size_type pos = 0) const CPP_NOEXCEPT
  { return this->find(str.data(), pos, str.size()); }

  size_type find(const cstring& str, size_type pos = 0) const CPP_NOEXCEPT
  { return this->find(str.data(), pos, str.size()); }

  /**
   *  @brief  Find position of a C string.
   *  @param s  C string to locate.
   *  @param pos  Index of character to search from (default 0).
   *  @return  Index of start of first occurrence.
   *
   *  Starting from @a pos, searches forward for the value of @a s within
   *  this string.  If found, returns the index where it begins.  If not
   *  found, returns npos.
   */
  size_type find(const_pointer s, size_type pos = 0) const CPP_NOEXCEPT
  { return this->find(s, pos, traits_type::length(s)); }

  /**
   *  @brief  Find position of a character.
   *  @param c  Character to locate.
   *  @param pos  Index of character to search from (default 0).
   *  @return  Index of first occurrence.
   *
   *  Starting from @a pos, searches forward for @a c within this string.
   *  If found, returns the index where it was found.  If not found,
   *  returns npos.
   */
  size_type find(value_type c, size_type pos = 0) const CPP_NOEXCEPT
  {
    size_type __ret = npos;
    const size_type __size = size();
    if (pos < __size)
    {
      const_pointer __data = data();
      const size_type n = __size - pos;
      const_pointer p = traits_type::find(__data + pos, n, c);
      if (p)
        __ret = p - __data;
    }
    return __ret;
  }

  /**
   *  @brief  Find last position of a C substring.
   *  @param s  C string to locate.
   *  @param pos  Index of character to search back from.
   *  @param n  Number of characters from s to search for.
   *  @return  Index of start of last occurrence.
   *
   *  Starting from @a pos, searches backward for the first @a n
   *  characters in @a s within this string.  If found, returns the index
   *  where it begins.  If not found, returns npos.
   */
  size_type rfind(const_pointer s, size_type pos, size_type n) const CPP_NOEXCEPT
  {
    const size_type __size = size();
    if (n <= __size)
    {
      pos = priv_limit(pos, n);
      const_pointer __data = data();
      do
      {
        if (traits_type::compare(__data + pos, s, n) == 0)
          return pos;
      }
      while (pos-- > 0);
    }
    return npos;
  }

  /**
   *  @brief  Find last position of a string.
   *  @param str  String to locate.
   *  @param pos  Index of character to search back from (default end).
   *  @return  Index of start of last occurrence.
   *
   *  Starting from @a pos, searches backward for value of @a str within
   *  this string.  If found, returns the index where it begins.  If not
   *  found, returns npos.
   */
  size_type rfind(const basic_string& str, size_type pos = npos) const CPP_NOEXCEPT
  { return this->rfind(str.data(), pos, str.size()); }

  size_type rfind(const cstring& str, size_type pos = npos) const CPP_NOEXCEPT
  { return this->rfind(str.data(), pos, str.size()); }

  /**
   *  @brief  Find last position of a C string.
   *  @param s  C string to locate.
   *  @param pos  Index of character to start search at (default end).
   *  @return  Index of start of  last occurrence.
   *
   *  Starting from @a pos, searches backward for the value of @a s within
   *  this string.  If found, returns the index where it begins.  If not
   *  found, returns npos.
   */
  size_type rfind(const_pointer s, size_type pos = npos) const CPP_NOEXCEPT
  { return this->rfind(s, pos, traits_type::length(s)); }

  /**
   *  @brief  Find last position of a character.
   *  @param c  Character to locate.
   *  @param pos  Index of character to search back from (default end).
   *  @return  Index of last occurrence.
   *
   *  Starting from @a pos, searches backward for @a c within this string.
   *  If found, returns the index where it was found.  If not found,
   *  returns npos.
   */
  size_type rfind(value_type c, size_type pos = npos) const CPP_NOEXCEPT
  {
    size_type __size = size();
    if (__size)
    {
      if (--__size > pos)
        __size = pos;
      for (++__size; __size-- > 0; )
        if (traits_type::eq(data()[__size], c))
          return __size;
    }
    return npos;
  }

  /**
   *  @brief  Find position of a character of C substring.
   *  @param s  String containing characters to locate.
   *  @param pos  Index of character to search from.
   *  @param n  Number of characters from s to search for.
   *  @return  Index of first occurrence.
   *
   *  Starting from @a pos, searches forward for one of the first @a n
   *  characters of @a s within this string.  If found, returns the index
   *  where it was found.  If not found, returns npos.
   */
  size_type find_first_of(const_pointer s, size_type pos, size_type n) const CPP_NOEXCEPT
  {
    for (; n && pos < this->size(); ++pos)
    {
      const_pointer p = traits_type::find(s, n, data()[pos]);
      if (p)
        return pos;
    }
    return npos;
  }

  /**
   *  @brief  Find position of a character of string.
   *  @param str  String containing characters to locate.
   *  @param pos  Index of character to search from (default 0).
   *  @return  Index of first occurrence.
   *
   *  Starting from @a pos, searches forward for one of the characters of
   *  @a str within this string.  If found, returns the index where it was
   *  found.  If not found, returns npos.
   */
  size_type find_first_of(const basic_string& str, size_type pos = 0) const CPP_NOEXCEPT
  { return this->find_first_of(str.data(), pos, str.size()); }

  size_type find_first_of(const cstring& str, size_type pos = 0) const CPP_NOEXCEPT
  { return this->find_first_of(str.data(), pos, str.size()); }

  /**
   *  @brief  Find position of a character of C string.
   *  @param s  String containing characters to locate.
   *  @param pos  Index of character to search from (default 0).
   *  @return  Index of first occurrence.
   *
   *  Starting from @a pos, searches forward for one of the characters of
   *  @a s within this string.  If found, returns the index where it was
   *  found.  If not found, returns npos.
   */
  size_type find_first_of(const_pointer s, size_type pos = 0) const CPP_NOEXCEPT
  { return this->find_first_of(s, pos, traits_type::length(s)); }

  /**
   *  @brief  Find position of a character.
   *  @param c  Character to locate.
   *  @param pos  Index of character to search from (default 0).
   *  @return  Index of first occurrence.
   *
   *  Starting from @a pos, searches forward for the character @a c within
   *  this string.  If found, returns the index where it was found.  If
   *  not found, returns npos.
   *
   *  Note: equivalent to find(c, pos).
   */
  size_type find_first_of(value_type c, size_type pos = 0) const CPP_NOEXCEPT
  { return this->find(c, pos); }

  /**
   *  @brief  Find last position of a character of string.
   *  @param str  String containing characters to locate.
   *  @param pos  Index of character to search back from (default end).
   *  @return  Index of last occurrence.
   *
   *  Starting from @a pos, searches backward for one of the characters of
   *  @a str within this string.  If found, returns the index where it was
   *  found.  If not found, returns npos.
   */
  size_type find_last_of(const basic_string& str,
                         size_type pos = npos) const CPP_NOEXCEPT
  { return this->find_last_of(str.data(), pos, str.size()); }

  size_type find_last_of(const cstring& str,
                         size_type pos = npos) const CPP_NOEXCEPT
  { return this->find_last_of(str.data(), pos, str.size()); }

  /**
   *  @brief  Find last position of a character of C substring.
   *  @param s  C string containing characters to locate.
   *  @param pos  Index of character to search back from.
   *  @param n  Number of characters from s to search for.
   *  @return  Index of last occurrence.
   *
   *  Starting from @a pos, searches backward for one of the first @a n
   *  characters of @a s within this string.  If found, returns the index
   *  where it was found.  If not found, returns npos.
   */
  size_type find_last_of(const_pointer s, size_type pos, size_type n) const CPP_NOEXCEPT
  {
    size_type __size = this->size();
    if (__size && n)
    {
      if (--__size > pos)
        __size = pos;
      do
      {
        if (traits_type::find(s, n, data()[__size]))
          return __size;
      }
      while (__size-- != 0);
    }
    return npos;
  }

  /**
   *  @brief  Find last position of a character of C string.
   *  @param s  C string containing characters to locate.
   *  @param pos  Index of character to search back from (default end).
   *  @return  Index of last occurrence.
   *
   *  Starting from @a pos, searches backward for one of the characters of
   *  @a s within this string.  If found, returns the index where it was
   *  found.  If not found, returns npos.
   */
  size_type find_last_of(const_pointer s, size_type pos = npos) const CPP_NOEXCEPT
  { return this->find_last_of(s, pos, traits_type::length(s)); }

  /**
   *  @brief  Find last position of a character.
   *  @param c  Character to locate.
   *  @param pos  Index of character to search back from (default end).
   *  @return  Index of last occurrence.
   *
   *  Starting from @a pos, searches backward for @a c within this string.
   *  If found, returns the index where it was found.  If not found,
   *  returns npos.
   *
   *  Note: equivalent to rfind(c, pos).
   */
  size_type find_last_of(value_type c, size_type pos = npos) const CPP_NOEXCEPT
  { return this->rfind(c, pos); }

  /**
   *  @brief  Find position of a character not in string.
   *  @param str  String containing characters to avoid.
   *  @param pos  Index of character to search from (default 0).
   *  @return  Index of first occurrence.
   *
   *  Starting from @a pos, searches forward for a character not contained
   *  in @a str within this string.  If found, returns the index where it
   *  was found.  If not found, returns npos.
   */
  size_type find_first_not_of(const basic_string& str,
                              size_type pos = 0) const CPP_NOEXCEPT
  { return this->find_first_not_of(str.data(), pos, str.size()); }

  size_type find_first_not_of(const cstring& str,
                              size_type pos = 0) const CPP_NOEXCEPT
  { return this->find_first_not_of(str.data(), pos, str.size()); }

  /**
   *  @brief  Find position of a character not in C substring.
   *  @param s  C string containing characters to avoid.
   *  @param pos  Index of character to search from.
   *  @param n  Number of characters from s to consider.
   *  @return  Index of first occurrence.
   *
   *  Starting from @a pos, searches forward for a character not contained
   *  in the first @a n characters of @a s within this string.  If found,
   *  returns the index where it was found.  If not found, returns npos.
   */
  size_type find_first_not_of(const_pointer s, size_type pos, size_type n) const CPP_NOEXCEPT
  {
    for (; pos < this->size(); ++pos) {
      if (!traits_type::find(s, n, data()[pos]))
        return pos;
    }
    return npos;
  }

  /**
   *  @brief  Find position of a character not in C string.
   *  @param s  C string containing characters to avoid.
   *  @param pos  Index of character to search from (default 0).
   *  @return  Index of first occurrence.
   *
   *  Starting from @a pos, searches forward for a character not contained
   *  in @a s within this string.  If found, returns the index where it
   *  was found.  If not found, returns npos.
   */
  size_type find_first_not_of(const_pointer s, size_type pos = 0) const CPP_NOEXCEPT
  { return this->find_first_not_of(s, pos, traits_type::length(s)); }

  /**
   *  @brief  Find position of a different character.
   *  @param c  Character to avoid.
   *  @param pos  Index of character to search from (default 0).
   *  @return  Index of first occurrence.
   *
   *  Starting from @a pos, searches forward for a character other than @a c
   *  within this string.  If found, returns the index where it was found.
   *  If not found, returns npos.
   */
  size_type find_first_not_of(value_type c, size_type pos = 0) const CPP_NOEXCEPT
  {
    for (; pos < this->size(); ++pos) {
      if (!traits_type::eq(data()[pos], c))
        return pos;
    }
    return npos;
  }

  /**
   *  @brief  Find last position of a character not in string.
   *  @param str  String containing characters to avoid.
   *  @param pos  Index of character to search back from (default end).
   *  @return  Index of last occurrence.
   *
   *  Starting from @a pos, searches backward for a character not
   *  contained in @a str within this string.  If found, returns the index
   *  where it was found.  If not found, returns npos.
   */
  size_type find_last_not_of(const basic_string& str,
                             size_type pos = npos) const CPP_NOEXCEPT
  { return this->find_last_not_of(str.data(), pos, str.size()); }

  size_type find_last_not_of(const cstring& str,
                             size_type pos = npos) const CPP_NOEXCEPT
  { return this->find_last_not_of(str.data(), pos, str.size()); }

  /**
   *  @brief  Find last position of a character not in C substring.
   *  @param s  C string containing characters to avoid.
   *  @param pos  Index of character to search back from.
   *  @param n  Number of characters from s to consider.
   *  @return  Index of last occurrence.
   *
   *  Starting from @a pos, searches backward for a character not
   *  contained in the first @a n characters of @a s within this string.
   *  If found, returns the index where it was found.  If not found,
   *  returns npos.
   */
  size_type find_last_not_of(const_pointer s, size_type pos, size_type n) const CPP_NOEXCEPT
  {
    size_type __size = this->size();
    if (__size)
    {
      if (--__size > pos)
        __size = pos;
      do
      {
        if (!traits_type::find(s, n, data()[__size]))
          return __size;
      }
      while (__size--);
    }
    return npos;
  }

  /**
   *  @brief  Find last position of a character not in C string.
   *  @param s  C string containing characters to avoid.
   *  @param pos  Index of character to search back from (default end).
   *  @return  Index of last occurrence.
   *
   *  Starting from @a pos, searches backward for a character not
   *  contained in @a s within this string.  If found, returns the index
   *  where it was found.  If not found, returns npos.
   */
  size_type find_last_not_of(const_pointer s, size_type pos = npos) const CPP_NOEXCEPT
  { return this->find_last_not_of(s, pos, traits_type::length(s)); }

  /**
   *  @brief  Find last position of a different character.
   *  @param c  Character to avoid.
   *  @param pos  Index of character to search back from (default end).
   *  @return  Index of last occurrence.
   *
   *  Starting from @a pos, searches backward for a character other than
   *  @a c within this string.  If found, returns the index where it was
   *  found.  If not found, returns npos.
   */
  size_type find_last_not_of(value_type c, size_type pos = npos) const CPP_NOEXCEPT
  {
    size_type __size = this->size();
    if (__size)
    {
      if (--__size > pos)
        __size = pos;
      do
      {
        if (!traits_type::eq(data()[__size], c))
          return __size;
      }
      while (__size--);
    }
    return npos;
  }

  /**
   *  @brief  Get a substring.
   *  @param pos  Index of first character (default 0).
   *  @param n  Number of characters in substring (default remainder).
   *  @return  The new string.
   *  @throw  std::out_of_range  If pos > size().
   *
   *  Construct and return a new string using the @a n characters starting
   *  at @a pos.  If the string is too short, use the remainder of the
   *  characters.  If @a pos is beyond the end of the string, out_of_range
   *  is thrown.
   */
  CPP_CONSTEXPR basic_string substr(size_type pos = 0, size_type n = npos) const
  {
    return ((pos > size()) ?
      throw std::out_of_range("basic_string::substr") :
      void()), basic_string(m_begin + pos, m_begin + pos + priv_limit(pos, n));
  }

  /**
   *  @brief  Compare to a string.
   *  @param str  String to compare against.
   *  @return  Integer < 0, 0, or > 0.
   *
   *  Returns an integer < 0 if this string is ordered before @a str, 0 if
   *  their values are equivalent, or > 0 if this string is ordered after
   *  @a str.  Determines the effective length rlen of the strings to
   *  compare as the smallest of size() and str.size().  The function
   *  then compares the two strings by calling traits::compare(data(),
   *  str.data(),rlen).  If the result of the comparison is nonzero returns
   *  it, otherwise the shorter one is ordered first.
   */
  int compare(const basic_string& str) const CPP_NOEXCEPT
  {
    const size_type __size = this->size();
    const size_type __osize = str.size();
    const size_type __len = std::min(__size, __osize);

    int __r = traits_type::compare(data(), str.data(), __len);
    if (!__r)
      __r = priv_compare(__size, __osize);
    return __r;
  }

  int compare(const cstring& str) const CPP_NOEXCEPT
  { return compare(priv_const_cstring(str)); }

  /**
   *  @brief  Compare substring to a string.
   *  @param pos  Index of first character of substring.
   *  @param n  Number of characters in substring.
   *  @param str  String to compare against.
   *  @return  Integer < 0, 0, or > 0.
   *
   *  Form the substring of this string from the @a n characters starting
   *  at @a pos.  Returns an integer < 0 if the substring is ordered
   *  before @a str, 0 if their values are equivalent, or > 0 if the
   *  substring is ordered after @a str.  Determines the effective length
   *  rlen of the strings to compare as the smallest of the length of the
   *  substring and @a str.size().  The function then compares the two
   *  strings by calling traits::compare(substring.data(),str.data(),rlen).
   *  If the result of the comparison is nonzero returns it, otherwise the
   *  shorter one is ordered first.
   */
  int compare(size_type pos, size_type n, const basic_string& str) const
  {
    if (size() < pos)
      throw std::out_of_range("basic_string::compare");
    n = priv_limit(pos, n);
    const size_type __osize = str.size();
    const size_type __len = std::min(n, __osize);
    int __r = traits_type::compare(data() + pos, str.data(), __len);
    if (!__r)
      __r = priv_compare(n, __osize);
    return __r;
  }

  int compare(size_type pos, size_type n, const cstring& str) const
  { return compare(pos, n, basic_string(str.begin(), str.end())); }

  /**
   *  @brief  Compare substring to a substring.
   *  @param pos1  Index of first character of substring.
   *  @param n1  Number of characters in substring.
   *  @param str  String to compare against.
   *  @param pos2  Index of first character of substring of str.
   *  @param n2  Number of characters in substring of str.
   *  @return  Integer < 0, 0, or > 0.
   *
   *  Form the substring of this string from the @a n1 characters starting
   *  at @a pos1.  Form the substring of @a str from the @a n2 characters
   *  starting at @a pos2.  Returns an integer < 0 if this substring is
   *  ordered before the substring of @a str, 0 if their values are
   *  equivalent, or > 0 if this substring is ordered after the substring
   *  of @a str.  Determines the effective length rlen of the strings
   *  to compare as the smallest of the lengths of the substrings.  The
   *  function then compares the two strings by calling
   *  traits::compare(substring.data(),str.substr(pos2,n2).data(),rlen).
   *  If the result of the comparison is nonzero returns it, otherwise the
   *  shorter one is ordered first.
   */
  int compare(size_type pos1, size_type n1, const basic_string& str,
              size_type pos2, size_type n2) const
  {
    if (size() < pos1 || str.size() < pos2)
      throw std::out_of_range("basic_string::compare");
    n1 = priv_limit(pos1, n1);
    n2 = str.priv_limit(pos2, n2);
    const size_type __len = std::min(n1, n2);
    int __r = traits_type::compare(data() + pos1, str.data() + pos2, __len);
    if (!__r)
      __r = priv_compare(n1, n2);
    return __r;
  }

  int compare(size_type pos1, size_type n1, const cstring& str,
              size_type pos2, size_type n2) const
  { return compare(pos1, n1, basic_string(str.begin(), str.end()), pos2, n2); }

  /**
   *  @brief  Compare to a C string.
   *  @param s  C string to compare against.
   *  @return  Integer < 0, 0, or > 0.
   *
   *  Returns an integer < 0 if this string is ordered before @a s, 0 if
   *  their values are equivalent, or > 0 if this string is ordered after
   *  @a s.  Determines the effective length rlen of the strings to
   *  compare as the smallest of size() and the length of a string
   *  constructed from @a s.  The function then compares the two strings
   *  by calling traits::compare(data(),s,rlen).  If the result of the
   *  comparison is nonzero returns it, otherwise the shorter one is
   *  ordered first.
   */
  int compare(const_pointer s) const CPP_NOEXCEPT
  {
    const size_type __size = this->size();
    const size_type __osize = traits_type::length(s);
    const size_type __len = std::min(__size, __osize);
    int __r = traits_type::compare(data(), s, __len);
    if (!__r)
      __r = priv_compare(__size, __osize);
    return __r;
  }

  /**
   *  @brief  Compare substring to a C string.
   *  @param pos  Index of first character of substring.
   *  @param n1  Number of characters in substring.
   *  @param s  C string to compare against.
   *  @return  Integer < 0, 0, or > 0.
   *
   *  Form the substring of this string from the @a n1 characters starting
   *  at @a pos.  Returns an integer < 0 if the substring is ordered
   *  before @a s, 0 if their values are equivalent, or > 0 if the
   *  substring is ordered after @a s.  Determines the effective length
   *  rlen of the strings to compare as the smallest of the length of the
   *  substring and the length of a string constructed from @a s.  The
   *  function then compares the two string by calling
   *  traits::compare(substring.data(),s,rlen).  If the result of the
   *  comparison is nonzero returns it, otherwise the shorter one is
   *  ordered first.
   */
  int compare(size_type pos, size_type n1, const_pointer s) const
  {
    if (size() < pos)
      throw std::out_of_range("basic_string::compare");
    n1 = priv_limit(pos, n1);
    const size_type __osize = traits_type::length(s);
    const size_type __len = std::min(n1, __osize);
    int __r = traits_type::compare(data() + pos, s, __len);
    if (!__r)
      __r = priv_compare(n1, __osize);
    return __r;
  }

  /**
   *  @brief  Compare substring against a character %array.
   *  @param pos1  Index of first character of substring.
   *  @param n1  Number of characters in substring.
   *  @param s  character %array to compare against.
   *  @param n2  Number of characters of s.
   *  @return  Integer < 0, 0, or > 0.
   *
   *  Form the substring of this string from the @a n1 characters starting
   *  at @a pos1.  Form a string from the first @a n2 characters of @a s.
   *  Returns an integer < 0 if this substring is ordered before the string
   *  from @a s, 0 if their values are equivalent, or > 0 if this substring
   *  is ordered after the string from @a s.   Determines the effective
   *  length rlen of the strings to compare as the smallest of the length
   *  of the substring and @a n2.  The function then compares the two
   *  strings by calling traits::compare(substring.data(),s,rlen).  If the
   *  result of the comparison is nonzero returns it, otherwise the shorter
   *  one is ordered first.
   *
   *  NB: s must have at least n2 characters, &apos;\\0&apos; has
   *  no special meaning.
   */
  int compare(size_type pos, size_type n1, const_pointer s, size_type n2) const
  {
    if (size() < pos)
      throw std::out_of_range("basic_string::compare");
    n1 = priv_limit(pos, n1);
    const size_type __len = std::min(n1, n2);
    int __r = traits_type::compare(data() + pos, s, __len);
    if (!__r)
      __r = priv_compare(n1, n2);
    return __r;
  }



private:
  size_type priv_limit(size_type pos, size_type off) const CPP_NOEXCEPT
  { return std::min(off, this->size() - pos); }

  basic_string priv_const_cstring(const cstring& str) const
  { return basic_string(str.data(), str.size()); }

  static int priv_compare(size_type n1, size_type n2) CPP_NOEXCEPT
  {
    const difference_type __d = difference_type(n1 - n2);

    if (__d > std::numeric_limits<int>::max())
      return std::numeric_limits<int>::max();
    else if (__d < std::numeric_limits<int>::min())
      return std::numeric_limits<int>::min();
    else
      return int(__d);
  }
};


template<typename CharT, typename Traits>
bool operator==(
  const basic_string< CharT, Traits, ::falcon::cstring_allocator< const CharT > > & a,
  const basic_string< CharT, Traits, ::falcon::cstring_allocator< CharT > > & b
) {
  return a == basic_string< CharT, Traits, ::falcon::cstring_allocator< const CharT > >(b);
}

template<typename CharT, typename Traits>
bool operator==(
  const basic_string< CharT, Traits, ::falcon::cstring_allocator< CharT > > & a,
  const basic_string< CharT, Traits, ::falcon::cstring_allocator< const CharT > > & b
) {
  return basic_string< CharT, Traits, ::falcon::cstring_allocator< const CharT > >(a) == b;
}


template<typename CharT, typename Traits>
bool operator<(
  const basic_string< CharT, Traits, ::falcon::cstring_allocator< const CharT > > & a,
  const basic_string< CharT, Traits, ::falcon::cstring_allocator< CharT > > & b
) {
  return a < basic_string< CharT, Traits, ::falcon::cstring_allocator< const CharT > >(b);
}

template<typename CharT, typename Traits>
bool operator<(
  const basic_string< CharT, Traits, ::falcon::cstring_allocator< CharT > > & a,
  const basic_string< CharT, Traits, ::falcon::cstring_allocator< const CharT > > & b
) {
  return basic_string< CharT, Traits, ::falcon::cstring_allocator< const CharT > >(a) < b;
}


template<typename CharT, typename Traits>
bool operator!=(
  const basic_string< CharT, Traits, ::falcon::cstring_allocator< const CharT > > & a,
  const basic_string< CharT, Traits, ::falcon::cstring_allocator< CharT > > & b
) {
  return a != basic_string< CharT, Traits, ::falcon::cstring_allocator< const CharT > >(b);
}

template<typename CharT, typename Traits>
bool operator!=(
  const basic_string< CharT, Traits, ::falcon::cstring_allocator< CharT > > & a,
  const basic_string< CharT, Traits, ::falcon::cstring_allocator< const CharT > > & b
) {
  return basic_string< CharT, Traits, ::falcon::cstring_allocator< const CharT > >(a) != b;
}


template<typename CharT, typename Traits>
bool operator<=(
  const basic_string< CharT, Traits, ::falcon::cstring_allocator< const CharT > > & a,
  const basic_string< CharT, Traits, ::falcon::cstring_allocator< CharT > > & b
) {
  return a <= basic_string< CharT, Traits, ::falcon::cstring_allocator< const CharT > >(b);
}

template<typename CharT, typename Traits>
bool operator<=(
  const basic_string< CharT, Traits, ::falcon::cstring_allocator< CharT > > & a,
  const basic_string< CharT, Traits, ::falcon::cstring_allocator< const CharT > > & b
) {
  return basic_string< CharT, Traits, ::falcon::cstring_allocator< const CharT > >(a) <= b;
}


template<typename CharT, typename Traits>
bool operator>=(
  const basic_string< CharT, Traits, ::falcon::cstring_allocator< const CharT > > & a,
  const basic_string< CharT, Traits, ::falcon::cstring_allocator< CharT > > & b
) {
  return a >= basic_string< CharT, Traits, ::falcon::cstring_allocator< const CharT > >(b);
}

template<typename CharT, typename Traits>
bool operator>=(
  const basic_string< CharT, Traits, ::falcon::cstring_allocator< CharT > > & a,
  const basic_string< CharT, Traits, ::falcon::cstring_allocator< const CharT > > & b
) {
  return basic_string< CharT, Traits, ::falcon::cstring_allocator< const CharT > >(a) >= b;
}


template<typename CharT, typename Traits>
bool operator>(
  const basic_string< CharT, Traits, ::falcon::cstring_allocator< const CharT > > & a,
  const basic_string< CharT, Traits, ::falcon::cstring_allocator< CharT > > & b
) {
  return a > basic_string< CharT, Traits, ::falcon::cstring_allocator< const CharT > >(b);
}

template<typename CharT, typename Traits>
bool operator>(
  const basic_string< CharT, Traits, ::falcon::cstring_allocator< CharT > > & a,
  const basic_string< CharT, Traits, ::falcon::cstring_allocator< const CharT > > & b
) {
  return basic_string< CharT, Traits, ::falcon::cstring_allocator< const CharT > >(a) > b;
}

}

namespace falcon {

template <typename CharT, std::size_t N>
typename build_basic_cstring<CharT>::type
cstring_array(CharT (&s)[N]) CPP_NOEXCEPT
{ return typename build_basic_cstring<CharT>::type(s, cstring_array_size()); }

template <typename CharT, std::size_t N>
typename build_basic_cstring<CharT>::type
cstring_array(CharT (&s)[N], std::size_t size) CPP_NOEXCEPT
{ return typename build_basic_cstring<CharT>::type(s, size, cstring_array_capacity()); }

template <typename CharT, std::size_t N>
CPP_CONSTEXPR typename build_basic_cstring<const CharT>::type
cstring_array(const CharT (&s)[N]) CPP_NOEXCEPT
{ return typename build_basic_cstring<const CharT>::type(s, cstring_array_size()); }

template <typename CharT, std::size_t N>
CPP_CONSTEXPR typename build_basic_cstring<const CharT>::type
constexpr_cstring(const CharT (&s)[N]) CPP_NOEXCEPT
{ return typename build_basic_cstring<const CharT>::type(s, cstring_array_size()); }


template <typename CharT, std::size_t N>
typename build_basic_cstring<CharT>::type
make_cstring(CharT (&s)[N], cstring_array_size) CPP_NOEXCEPT
{ return typename build_basic_cstring<CharT>::type(s, cstring_array_size()); }

template <typename CharT, std::size_t N>
typename build_basic_cstring<CharT>::type
make_cstring(CharT (&s)[N], cstring_array_capacity) CPP_NOEXCEPT
{ return typename build_basic_cstring<CharT>::type(s, cstring_array_capacity()); }

template <typename CharT, std::size_t N>
typename build_basic_cstring<CharT>::type
make_cstring(CharT (&s)[N], std::size_t size, cstring_array_size) CPP_NOEXCEPT
{ return typename build_basic_cstring<CharT>::type(s, size, cstring_array_size()); }

template <typename CharT>
typename build_basic_cstring<CharT>::type
make_cstring(CharT * s, std::size_t n) CPP_NOEXCEPT
{ return typename build_basic_cstring<CharT>::type(s, n); }

template <typename CharT>
typename build_basic_cstring<CharT>::type
make_cstring(CharT * first, CharT * last) CPP_NOEXCEPT
{ return typename build_basic_cstring<CharT>::type(first, last); }

template <typename CharT>
typename build_basic_cstring<CharT>::type
make_cstring(CharT * s) CPP_NOEXCEPT
{ return typename build_basic_cstring<CharT>::type(s); }


template <typename CharT, std::size_t N>
CPP_CONSTEXPR typename build_basic_cstring<const CharT>::type
make_cstring(const CharT (&s)[N], cstring_array_size) CPP_NOEXCEPT
{ return typename build_basic_cstring<const CharT>::type(s, s + N - 1); }

template <typename CharT>
CPP_CONSTEXPR typename build_basic_cstring<const CharT>::type
make_cstring(const CharT * s, std::size_t n) CPP_NOEXCEPT
{ return typename build_basic_cstring<const CharT>::type(s, n); }

template <typename CharT>
CPP_CONSTEXPR typename build_basic_cstring<const CharT>::type
make_cstring(const CharT * first, const CharT * last) CPP_NOEXCEPT
{ return typename build_basic_cstring<const CharT>::type(first, last); }

template <typename CharT>
CPP_CONSTEXPR typename build_basic_cstring<const CharT>::type
make_cstring(const CharT * s) CPP_NOEXCEPT
{ return typename build_basic_cstring<const CharT>::type(s); }


inline std::string to_string(const cstring& str)
{ return std::string(str.data(), str.size()); }

inline std::string to_string(const const_cstring& str)
{ return std::string(str.data(), str.size()); }

inline std::wstring to_wstring(const cwstring& str)
{ return std::wstring(str.data(), str.size()); }

inline std::wstring to_wstring(const const_cwstring& str)
{ return std::wstring(str.data(), str.size()); }

template<typename CharT, typename Traits>
inline std::basic_string<CharT, Traits>
to_string(const basic_cstring<CharT, Traits>& str)
{ return std::basic_string<CharT, Traits>(str.data(), str.size()); }

}

#endif
