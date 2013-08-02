#ifndef _FALCON_STRING_BASIC_CSTRING_HPP
#define _FALCON_STRING_BASIC_CSTRING_HPP

#include <iosfwd>
#include <limits>
#include <iterator>
#include <stdexcept>
#include <utility>
#if __cplusplus < 201103L
# include <boost/type_traits/remove_const.hpp>
# include <boost/type_traits/remove_reference.hpp>
# include <boost/type_traits/is_pointer.hpp>
# include <boost/type_traits/is_array.hpp>
#endif
#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include <falcon/type_traits/enable_if.hpp>
#include <falcon/type_traits/is_same.hpp>
#include <falcon/string/cstringfwd.hpp>
#include <falcon/ostream/insert.hpp>
#include <falcon/detail/string_convertion.hpp>
#include <typeinfo>
namespace falcon {

/**
 * @brief Managing sequences of constants characters and constant character-like objects.
 *
 */
template <typename _CharT, typename _Traits>
class basic_cstring
{
public:
  typedef _Traits traits_type;

  typedef typename FALCON_BOOST_OR_STD_NAMESPACE::remove_const<_CharT>::type value_type;

  typedef _CharT*           pointer;
  typedef const value_type* const_pointer;
  typedef _CharT&           reference;
  typedef const value_type& const_reference;
  typedef std::size_t       size_type;
  typedef std::ptrdiff_t    difference_type;

  typedef const_pointer	const_iterator;
  typedef pointer			iterator;

  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef std::reverse_iterator<iterator>       reverse_iterator;

public:
  static const size_type npos = static_cast<size_type>(-1);

private:
  pointer m_begin;
  pointer m_end;

public:
  CPP_CONSTEXPR basic_cstring() CPP_NOEXCEPT
  : m_begin(0)
  , m_end(0)
  {}

#if __cplusplus >= 201103L
  constexpr basic_cstring(std::nullptr_t) noexcept
  : m_begin(0)
  , m_end(0)
  {}
#endif

private:
  template<typename _String,
  bool is_pointer = FALCON_BOOST_OR_STD_NAMESPACE::is_pointer<
      typename FALCON_BOOST_OR_STD_NAMESPACE::remove_reference<_String>::type
  >::value,
  bool is_array = FALCON_BOOST_OR_STD_NAMESPACE::is_array<
      typename FALCON_BOOST_OR_STD_NAMESPACE::remove_reference<_String>::type
  >::value>
  struct __dispath_cons
  {
    CPP_CONSTEXPR static pointer begin(const _String& s)
    { return s.begin(); }
    CPP_CONSTEXPR static pointer end(const _String& s)
    { return s.end(); }
  };

  template<typename _String>
  struct __dispath_cons<_String, true, false>
  {
    static pointer begin(_String s)
    { return s; }
    static pointer end(_String s)
    { return s + traits_type::length(s); }
  };

  template<typename _String>
  struct __dispath_cons<_String, false, true>
  {
    CPP_CONSTEXPR static pointer begin(_String&& s)
    { return &s[0]; }
    CPP_CONSTEXPR static pointer end(_String&& s)
    { return &s[0] + std::extent<typename std::remove_reference<_String>::type>::value - 1; }
  };

public:
  template<typename _String>
  CPP_CONSTEXPR basic_cstring(_String&& s) CPP_NOEXCEPT
  : m_begin(__dispath_cons<_String>::begin(s))
  , m_end(__dispath_cons<_String>::end(s))
  {}

  CPP_CONSTEXPR basic_cstring(pointer s, size_type __size) CPP_NOEXCEPT
  : m_begin(s)
  , m_end(s + __size)
  {}

  CPP_CONSTEXPR basic_cstring(pointer first, pointer last) CPP_NOEXCEPT
  : m_begin(first)
  , m_end(last)
  {}

  CPP_CONSTEXPR basic_cstring(const basic_cstring& s) CPP_NOEXCEPT
  : m_begin(s.m_begin)
  , m_end(s.m_end)
  {}

  template<typename _CharT2>
  CPP_CONSTEXPR basic_cstring(const basic_cstring<_CharT2, _Traits> s,
                              typename enable_if_c<is_same<const _CharT2, _CharT>, int>::type = 0) CPP_NOEXCEPT
  : m_begin(s.c_str())
  , m_end(m_begin + s.size())
  {}

  basic_cstring& operator=(const basic_cstring& s) CPP_NOEXCEPT
  { return assign(s); }

  template<typename _CharT2>
  basic_cstring& operator=(const basic_cstring<_CharT2, _Traits>& s) CPP_NOEXCEPT
  { return assign(s); }

  basic_cstring& operator=(pointer s) CPP_NOEXCEPT
  { return assign(s); }

#if __cplusplus >= 201103L
  basic_cstring& operator=(std::nullptr_t) noexcept
  { return clear(); }

  explicit operator std::basic_string<value_type, _Traits> () const
  { return std::basic_string<value_type, _Traits>(data(), size()); }
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
  CPP_CONSTEXPR const_reference front() const CPP_NOEXCEPT
  { return operator[](0); }

  /**
   *  Returns a reference to the data at the last element of the %string.
   */
  reference back() CPP_NOEXCEPT
  { return operator[](m_end - 1); }

  /**
   *  Returns a read-only (constant) reference to the data at the
   *  last element of the %string.
   */
  CPP_CONSTEXPR const_reference back() const CPP_NOEXCEPT
  { return operator[](m_end - 1); }

  reference at(size_type index)
  {
    if(m_begin + index >= m_end)
        throw std::out_of_range("basic_cstring::at");
    return m_begin[index];
  }

  CPP_CONSTEXPR const_reference at(size_type index) const
  {
    if(m_begin + index >= m_end)
        throw std::out_of_range("basic_cstring::at");
    return m_begin[index];
  }

  CPP_CONSTEXPR size_type size() const CPP_NOEXCEPT
  { return m_end - m_begin; }
  CPP_CONSTEXPR size_type length() const CPP_NOEXCEPT
  { return m_end - m_begin; }

  CPP_CONSTEXPR size_type max_size() const CPP_NOEXCEPT
  { return static_cast<size_type>(-1); }

  CPP_CONSTEXPR bool empty() const CPP_NOEXCEPT
  { return m_begin == m_end; }

  void clear() CPP_NOEXCEPT
  { m_end = m_begin; }

  void resize(size_type new_len)
  {
    if(m_begin + new_len < m_end)
      m_end = m_begin + new_len;
  }

  basic_cstring& assign(const basic_cstring& s) CPP_NOEXCEPT
  { return assign(s.m_begin, s.m_end); }

  template<typename _CharT2>
  basic_cstring& assign(const basic_cstring<_CharT2, _Traits>& s) CPP_NOEXCEPT
  { return assign(s.m_begin, s.m_end); }

  basic_cstring&  assign(pointer first, pointer last) CPP_NOEXCEPT
  {
    m_begin = first;
    m_end = last;
    return *this;
  }

  basic_cstring& assign(pointer s, size_type len) CPP_NOEXCEPT
  { return assign(s, s + len); }

  basic_cstring& assign(const basic_cstring& s, size_type pos,
                        size_type len) CPP_NOEXCEPT
  { return assign(s + pos, len); }

  template<typename _CharT2>
  basic_cstring& assign(const basic_cstring<_CharT2, _Traits>& s,
                        size_type pos, size_type len) CPP_NOEXCEPT
  { return assign(s + pos, len); }

  basic_cstring& assign(pointer s) CPP_NOEXCEPT
  {
    m_begin = s ? s : 0;
    m_end = s ? s + traits_type::length(s) : 0;
    return *this;
  }

  basic_cstring& erase() CPP_NOEXCEPT
  {
    clear();
    return *this;
  }

  basic_cstring& erase(size_type pos) CPP_NOEXCEPT
  {
    if (size() <= pos)
        clear();
    else
        m_begin += pos;
    return *this;
  }

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
  size_type copy(_CharT* __s, size_type __n, size_type __pos = 0) const
  {
    if (size() <= __pos)
        throw std::out_of_range("basic_cstring::copy");
    __n = _M_limit(__pos, __n);
    if (__n)
        _S_copy(__s, data() + __pos, __n);
    return __n;
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

  void swap(basic_cstring& s) CPP_NOEXCEPT
  {
    using std::swap;
    swap(m_begin, s.m_begin);
    swap(m_end, s.m_end);
  }

  iterator begin() CPP_NOEXCEPT
  { return m_begin; }
  CPP_CONSTEXPR const_iterator begin() const CPP_NOEXCEPT
  { return m_begin; }

  iterator end() CPP_NOEXCEPT
  { return m_end; }
  CPP_CONSTEXPR const_iterator end() const CPP_NOEXCEPT
  { return m_end; }

  reverse_iterator rbegin() CPP_NOEXCEPT
  { return reverse_iterator(m_end); }
  CPP_CONSTEXPR const_reverse_iterator rbegin() const CPP_NOEXCEPT
  { return reverse_iterator(m_end); }

  reverse_iterator rend() CPP_NOEXCEPT
  { return reverse_iterator(m_begin); }
  CPP_CONSTEXPR const_reverse_iterator rend() const CPP_NOEXCEPT
  { return reverse_iterator(m_begin); }

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
  { return const_iterator(m_end); }

  /**
   *  Returns a read-only (constant) reverse iterator that points
   *  to the last character in the %string.  Iteration is done in
   *  reverse element order.
   */
  constexpr const_reverse_iterator crbegin() const noexcept
  { return const_reverse_iterator(m_end); }

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
  size_type find(const_pointer __s, size_type __pos, size_type __n) const CPP_NOEXCEPT
  {
    const size_type __size = size();
    const_pointer __data = data();

    if (__n == 0)
      return __pos <= __size ? __pos : npos;

    if (__n <= __size)
    {
      for (; __pos <= __size - __n; ++__pos)
        if (traits_type::eq(__data[__pos], __s[0])
          && traits_type::compare(__data + __pos + 1,
                                  __s + 1, __n - 1) == 0)
          return __pos;
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
  size_type find(const basic_cstring& __str, size_type __pos = 0) const CPP_NOEXCEPT
  { return this->find(__str.data(), __pos, __str.size()); }

  template<typename _CharT2>
  size_type find(const basic_cstring<_CharT2, _Traits>& __str,
                      size_type __pos = 0) const CPP_NOEXCEPT
  { return this->find(__str.data(), __pos, __str.size()); }

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
  size_type find(const_pointer __s, size_type __pos = 0) const CPP_NOEXCEPT
  { return this->find(__s, __pos, traits_type::length(__s)); }

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
  size_type find(value_type __c, size_type __pos = 0) const CPP_NOEXCEPT
  {
    size_type __ret = npos;
    const size_type __size = size();
    if (__pos < __size)
    {
      const_pointer __data = data();
      const size_type __n = __size - __pos;
      const_pointer __p = traits_type::find(__data + __pos, __n, __c);
      if (__p)
        __ret = __p - __data;
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
  size_type rfind(const_pointer __s, size_type __pos, size_type __n) const CPP_NOEXCEPT
  {
    const size_type __size = size();
    if (__n <= __size)
    {
      __pos = std::min(size_type(__size - __n), __pos);
      const_pointer __data = data();
      do
      {
        if (traits_type::compare(__data + __pos, __s, __n) == 0)
          return __pos;
      }
      while (__pos-- > 0);
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
  size_type rfind(const basic_cstring& __str,
                  size_type __pos = npos) const CPP_NOEXCEPT
  { return this->rfind(__str.data(), __pos, __str.size()); }

  template<typename _CharT2>
  size_type rfind(const basic_cstring<_CharT2, _Traits>& __str,
                  size_type __pos = npos) const CPP_NOEXCEPT
  { return this->rfind(__str.data(), __pos, __str.size()); }

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
  size_type rfind(const_pointer __s, size_type __pos = npos) const CPP_NOEXCEPT
  { return this->rfind(__s, __pos, traits_type::length(__s)); }

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
  size_type rfind(value_type __c, size_type __pos = npos) const CPP_NOEXCEPT
  {
    size_type __size = size();
    if (__size)
    {
      if (--__size > __pos)
        __size = __pos;
      for (++__size; __size-- > 0; )
        if (traits_type::eq(data()[__size], __c))
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
  size_type find_first_of(const_pointer __s, size_type __pos, size_type __n) const CPP_NOEXCEPT
  {
    for (; __n && __pos < this->size(); ++__pos)
    {
      const_pointer __p = traits_type::find(__s, __n, data()[__pos]);
      if (__p)
        return __pos;
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
  size_type find_first_of(const basic_cstring& __str, size_type __pos = 0) const CPP_NOEXCEPT
  { return this->find_first_of(__str.data(), __pos, __str.size()); }

  template<typename _CharT2>
  size_type find_first_of(const basic_cstring<_CharT2, _Traits>& __str,
                          size_type __pos = 0) const CPP_NOEXCEPT
  { return this->find_first_of(__str.data(), __pos, __str.size()); }

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
  size_type find_first_of(const_pointer __s, size_type __pos = 0) const CPP_NOEXCEPT
  { return this->find_first_of(__s, __pos, traits_type::length(__s)); }

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
  size_type find_first_of(_CharT __c, size_type __pos = 0) const CPP_NOEXCEPT
  { return this->find(__c, __pos); }

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
  size_type find_last_of(const basic_cstring& __str, size_type __pos = npos) const CPP_NOEXCEPT
  { return this->find_last_of(__str.data(), __pos, __str.size()); }

  template<typename _CharT2>
  size_type find_last_of(const basic_cstring<_CharT2, _Traits>& __str,
                          size_type __pos = npos) const CPP_NOEXCEPT
  { return this->find_last_of(__str.data(), __pos, __str.size()); }

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
  size_type find_last_of(const_pointer __s, size_type __pos, size_type __n) const CPP_NOEXCEPT
  {
    size_type __size = this->size();
    if (__size && __n)
    {
      if (--__size > __pos)
        __size = __pos;
      do
      {
        if (traits_type::find(__s, __n, data()[__size]))
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
  size_type find_last_of(const_pointer __s, size_type __pos = npos) const CPP_NOEXCEPT
  { return this->find_last_of(__s, __pos, traits_type::length(__s)); }

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
  size_type find_last_of(_CharT __c, size_type __pos = npos) const CPP_NOEXCEPT
  { return this->rfind(__c, __pos); }

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
  size_type find_first_not_of(const basic_cstring& __str,
                              size_type __pos = 0) const CPP_NOEXCEPT
  { return this->find_first_not_of(__str.data(), __pos, __str.size()); }

  template<typename _CharT2>
  size_type find_first_not_of(const basic_cstring<_CharT2, _Traits>& __str,
                              size_type __pos = 0) const CPP_NOEXCEPT
  { return this->find_first_not_of(__str.data(), __pos, __str.size()); }

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
  size_type find_first_not_of(const_pointer __s, size_type __pos, size_type __n) const CPP_NOEXCEPT
  {
    for (; __pos < this->size(); ++__pos) {
      if (!traits_type::find(__s, __n, data()[__pos]))
        return __pos;
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
  size_type find_first_not_of(const_pointer __s, size_type __pos = 0) const CPP_NOEXCEPT
  { return this->find_first_not_of(__s, __pos, traits_type::length(__s)); }

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
  size_type find_first_not_of(_CharT __c, size_type __pos = 0) const CPP_NOEXCEPT
  {
    for (; __pos < this->size(); ++__pos) {
      if (!traits_type::eq(data()[__pos], __c))
        return __pos;
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
  size_type find_last_not_of(const basic_cstring& __str,
                             size_type __pos = npos) const CPP_NOEXCEPT
  { return this->find_last_not_of(__str.data(), __pos, __str.size()); }

  template<typename _CharT2>
  size_type find_last_not_of(const basic_cstring<_CharT2, _Traits>& __str,
                             size_type __pos = npos) const CPP_NOEXCEPT
  { return this->find_last_not_of(__str.data(), __pos, __str.size()); }

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
  size_type find_last_not_of(const_pointer __s, size_type __pos, size_type __n) const CPP_NOEXCEPT
  {
    size_type __size = this->size();
    if (__size)
    {
      if (--__size > __pos)
        __size = __pos;
      do
      {
        if (!traits_type::find(__s, __n, data()[__size]))
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
  size_type find_last_not_of(const_pointer __s, size_type __pos = npos) const CPP_NOEXCEPT
  { return this->find_last_not_of(__s, __pos, traits_type::length(__s)); }

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
  size_type find_last_not_of(_CharT __c, size_type __pos = npos) const CPP_NOEXCEPT
  {
    size_type __size = this->size();
    if (__size)
    {
      if (--__size > __pos)
        __size = __pos;
      do
      {
        if (!traits_type::eq(data()[__size], __c))
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
  CPP_CONSTEXPR basic_cstring substr(size_type __pos = 0, size_type __n = npos) const
  {
    if (size() < __pos + __n)
      throw std::out_of_range("basic_cstring::substr");
    return basic_cstring(m_begin + __pos, m_begin + __pos + __n);
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
  int compare(const basic_cstring& s) const CPP_NOEXCEPT
{
    const size_type __size = this->size();
    const size_type __osize = s.size();
    const size_type __len = std::min(__size, __osize);

    int __r = traits_type::compare(data(), s.data(), __len);
    if (!__r)
      __r = _S_compare(__size, __osize);
    return __r;
  }

  template<typename _CharT2>
  int compare(const basic_cstring<_CharT2, _Traits>& s) const CPP_NOEXCEPT
  {
    const size_type __size = this->size();
    const size_type __osize = s.size();
    const size_type __len = std::min(__size, __osize);

    int __r = traits_type::compare(data(), s.data(), __len);
    if (!__r)
      __r = _S_compare(__size, __osize);
    return __r;
  }

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
  int compare(size_type __pos, size_type __n, const basic_cstring& __str) const
  {
    if (size() < __pos)
      throw std::out_of_range("basic_cstring::compare");
    __n = _M_limit(__pos, __n);
    const size_type __osize = __str.size();
    const size_type __len = std::min(__n, __osize);
    int __r = traits_type::compare(data() + __pos, __str.data(), __len);
    if (!__r)
      __r = _S_compare(__n, __osize);
    return __r;
  }

  template<typename _CharT2>
  int compare(size_type __pos, size_type __n,
              const basic_cstring<_CharT2, _Traits>& __str) const
  {
    if (size() < __pos)
      throw std::out_of_range("basic_cstring::compare");
    __n = _M_limit(__pos, __n);
    const size_type __osize = __str.size();
    const size_type __len = std::min(__n, __osize);
    int __r = traits_type::compare(data() + __pos, __str.data(), __len);
    if (!__r)
      __r = _S_compare(__n, __osize);
    return __r;
  }

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
  int compare(size_type __pos1, size_type __n1, const basic_cstring& __str,
              size_type __pos2, size_type __n2) const
  {
    if (size() < __pos1 || __str.size() < __pos2)
      throw std::out_of_range("basic_cstring::compare");
    __n1 = _M_limit(__pos1, __n1);
    __n2 = __str._M_limit(__pos2, __n2);
    const size_type __len = std::min(__n1, __n2);
    int __r = traits_type::compare(data() + __pos1, __str.data() + __pos2, __len);
    if (!__r)
      __r = _S_compare(__n1, __n2);
    return __r;
  }

  template<typename _CharT2>
  int compare(size_type __pos1, size_type __n1,
              const basic_cstring<_CharT2, _Traits>& __str,
              size_type __pos2, size_type __n2) const
  {
      if (size() < __pos1 || __str.size() < __pos2)
          throw std::out_of_range("basic_cstring::compare");
      __n1 = _M_limit(__pos1, __n1);
      __n2 = __str._M_limit(__pos2, __n2);
      const size_type __len = std::min(__n1, __n2);
      int __r = traits_type::compare(data() + __pos1, __str.data() + __pos2, __len);
      if (!__r)
          __r = _S_compare(__n1, __n2);
      return __r;
  }

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
  int compare(const_pointer __s) const CPP_NOEXCEPT
  {
    const size_type __size = this->size();
    const size_type __osize = traits_type::length(__s);
    const size_type __len = std::min(__size, __osize);
    int __r = traits_type::compare(data(), __s, __len);
    if (!__r)
      __r = _S_compare(__size, __osize);
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
  int compare(size_type __pos, size_type __n1, const_pointer __s) const
  {
    if (size() < __pos)
      throw std::out_of_range("basic_cstring::compare");
    __n1 = _M_limit(__pos, __n1);
    const size_type __osize = traits_type::length(__s);
    const size_type __len = std::min(__n1, __osize);
    int __r = traits_type::compare(data() + __pos, __s, __len);
    if (!__r)
      __r = _S_compare(__n1, __osize);
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
  int compare(size_type __pos, size_type __n1, const_pointer __s, size_type __n2) const
  {
    if (size() < __pos)
      throw std::out_of_range("basic_cstring::compare");
    __n1 = _M_limit(__pos, __n1);
    const size_type __len = std::min(__n1, __n2);
    int __r = traits_type::compare(data() + __pos, __s, __len);
    if (!__r)
      __r = _S_compare(__n1, __n2);
    return __r;
  }

private:
  size_type _M_limit(size_type __pos, size_type __off) const CPP_NOEXCEPT
  {
    const bool __testoff =  __off < this->size() - __pos;
    return __testoff ? __off : this->size() - __pos;
  }

  // When __n = 1 way faster than the general multichar
  // traits_type::copy/move/assign.
  static void _S_copy(_CharT* __d, const_pointer __s, size_type __n) CPP_NOEXCEPT
  {
    if (__n == 1)
      traits_type::assign(*__d, *__s);
    else
      traits_type::copy(__d, __s, __n);
  }

  static int _S_compare(size_type __n1, size_type __n2) CPP_NOEXCEPT
  {
    const difference_type __d = difference_type(__n1 - __n2);

    if (__d > std::numeric_limits<int>::max())
      return std::numeric_limits<int>::max();
    else if (__d < std::numeric_limits<int>::min())
      return std::numeric_limits<int>::min();
    else
      return int(__d);
  }
};

#if __cplusplus >= 201103L

template <typename _CharT,
	typename _Traits = std::char_traits<_CharT>, std::size_t _N>
constexpr basic_cstring<_CharT, _Traits> make_cstring(_CharT (&s)[_N]) noexcept
{ return basic_cstring<_CharT, _Traits>(s, s + _N - 1); }

template <typename _CharT,
	typename _Traits = std::char_traits<typename std::remove_const<_CharT>::type> >
constexpr basic_cstring<_CharT, _Traits>
make_cstring(_CharT* s, std::size_t n) noexcept
{ return basic_cstring<_CharT, _Traits>(s, n); }

template <typename _CharT,
	typename _Traits = std::char_traits<typename std::remove_const<_CharT>::type> >
constexpr basic_cstring<_CharT, _Traits>
make_cstring(_CharT* first, _CharT* last) noexcept
{ return basic_cstring<_CharT, _Traits>(first, last); }

template <typename _CharT,
	typename _Traits = std::char_traits<typename std::remove_const<_CharT>::type> >
basic_cstring<_CharT, _Traits> make_cstring(_CharT* s) noexcept
{ return basic_cstring<_CharT, _Traits>(s); }

#else

template <typename _CharT, std::size_t _N>
basic_cstring<_CharT> make_cstring(_CharT (&s)[_N])
{ return basic_cstring<_CharT>(s, s + _N - 1); }

template <typename _CharT>
basic_cstring<_CharT> make_cstring(_CharT* s, std::size_t n)
{ return basic_cstring<_CharT>(s, n); }

template <typename _CharT>
basic_cstring<_CharT> make_cstring(_CharT* first, _CharT* last)
{ return basic_cstring<_CharT>(first, last); }

template <typename _CharT>
basic_cstring<_CharT> make_cstring(_CharT* s)
{ return basic_cstring<_CharT>(s); }

#endif


template<typename _CharT>
struct __cstring_const_pointer
{ typedef const _CharT* __pointer; };

template<typename _CharT>
struct __cstring_const_pointer<const _CharT>
{ typedef const _CharT* __pointer; };

// operator ==
/**
 *  @brief  Test equivalence of two cstrings.
 *  @param lhs  First cstring.
 *  @param rhs  Second cstring.
 *  @return  True if @a lhs.compare(@a rhs) == 0.  False otherwise.
 */
template<typename _CharT, typename _CharT2, typename _Traits>
inline bool operator==(const basic_cstring<_CharT, _Traits>& __lhs,
                       const basic_cstring<_CharT2, _Traits>& __rhs) CPP_NOEXCEPT
{ return __lhs.compare(__rhs) == 0; }

/**
 *  @brief  Test equivalence of C string and cstring.
 *  @param lhs  C string.
 *  @param rhs  Cstring.
 *  @return  True if @a rhs.compare(@a lhs) == 0.  False otherwise.
 */
template<typename _CharT, typename _Traits>
inline bool operator==(typename __cstring_const_pointer<_CharT>::__pointer __lhs,
                       const basic_cstring<_CharT, _Traits>& __rhs) CPP_NOEXCEPT
{ return __rhs.compare(__lhs) == 0; }

/**
 *  @brief  Test equivalence of cstring and C string.
 *  @param lhs  Cstring.
 *  @param rhs  C string.
 *  @return  True if @a lhs.compare(@a rhs) == 0.  False otherwise.
 */
template<typename _CharT, typename _Traits>
inline bool operator==(const basic_cstring<_CharT, _Traits>& __lhs,
                       typename __cstring_const_pointer<_CharT>::__pointer __rhs) CPP_NOEXCEPT
{ return __lhs.compare(__rhs) == 0; }

/**
 *  @brief  Test equivalence of string and cstring.
 *  @param lhs  string.
 *  @param rhs  Cstring.
 *  @return  True if @a lhs.compare(@a rhs) == 0.  False otherwise.
 */
template<typename _CharT, typename _CharT2, typename _Traits, typename _Alloc>
inline bool operator==(const std::basic_string<_CharT, _Traits, _Alloc>& __lhs,
                       const basic_cstring<_CharT2, _Traits>& __rhs) CPP_NOEXCEPT
{ return __lhs.compare(0, __rhs.size(), __rhs.c_str()) == 0; }

/**
 *  @brief  Test equivalence of cstring and string.
 *  @param lhs  cstring.
 *  @param rhs  string.
 *  @return  True if @a rhs.compare(@a lhs) == 0.  False otherwise.
 */
template<typename _CharT, typename _CharT2, typename _Traits, typename _Alloc>
inline bool operator==(const basic_cstring<_CharT, _Traits>& __lhs,
                       const std::basic_string<_CharT2, _Traits, _Alloc>& __rhs) CPP_NOEXCEPT
{ return (__rhs == __lhs); }

// operator !=
/**
 *  @brief  Test difference of two cstrings.
 *  @param lhs  First cstring.
 *  @param rhs  Second cstring.
 *  @return  True if @a lhs.compare(@a rhs) != 0.  False otherwise.
 */
template<typename _CharT, typename _CharT2, typename _Traits>
inline bool operator!=(const basic_cstring<_CharT, _Traits>& __lhs,
                       const basic_cstring<_CharT2, _Traits>& __rhs) CPP_NOEXCEPT
{ return !(__lhs == __rhs); }

/**
 *  @brief  Test difference of C string and cstring.
 *  @param lhs  C string.
 *  @param rhs  Cstring.
 *  @return  True if @a rhs.compare(@a lhs) != 0.  False otherwise.
 */
template<typename _CharT, typename _Traits>
inline bool operator!=(typename __cstring_const_pointer<_CharT>::__pointer __lhs,
                       const basic_cstring<_CharT, _Traits>& __rhs) CPP_NOEXCEPT
{ return !(__lhs == __rhs); }

/**
 *  @brief  Test difference of cstring and C string.
 *  @param lhs  Cstring.
 *  @param rhs  C string.
 *  @return  True if @a lhs.compare(@a rhs) != 0.  False otherwise.
 */
template<typename _CharT, typename _CharT2, typename _Traits, typename _Alloc>
inline bool operator!=(const basic_cstring<_CharT, _Traits>& __lhs,
                       const std::basic_string<_CharT2, _Traits, _Alloc>& __rhs) CPP_NOEXCEPT
{ return !(__lhs == __rhs); }

/**
 *  @brief  Test difference of string and cstring.
 *  @param lhs  string.
 *  @param rhs  Cstring.
 *  @return  True if @a rhs.compare(@a lhs) != 0.  False otherwise.
 */
template<typename _CharT, typename _CharT2, typename _Traits, typename _Alloc>
inline bool operator!=(const std::basic_string<_CharT, _Traits, _Alloc>& __lhs,
                       const basic_cstring<_CharT2, _Traits>& __rhs) CPP_NOEXCEPT
{ return !(__lhs == __rhs); }

/**
 *  @brief  Test difference of cstring and string.
 *  @param lhs  Cstring.
 *  @param rhs  string.
 *  @return  True if @a lhs.compare(@a rhs) != 0.  False otherwise.
 */
template<typename _CharT, typename _Traits>
inline bool operator!=(const basic_cstring<_CharT, _Traits>& __lhs,
                       typename __cstring_const_pointer<_CharT>::__pointer __rhs) CPP_NOEXCEPT
{ return !(__lhs == __rhs); }

// operator <
/**
 *  @brief  Test if string precedes cstring.
 *  @param lhs  First cstring.
 *  @param rhs  Second cstring.
 *  @return  True if @a lhs precedes @a rhs.  False otherwise.
 */
template<typename _CharT, typename _CharT2, typename _Traits>
inline bool operator<(const basic_cstring<_CharT, _Traits>& __lhs,
                      const basic_cstring<_CharT2, _Traits>& __rhs) CPP_NOEXCEPT
{ return __lhs.compare(__rhs) < 0; }

/**
 *  @brief  Test if cstring precedes C string.
 *  @param lhs  Cstring.
 *  @param rhs  C string.
 *  @return  True if @a lhs precedes @a rhs.  False otherwise.
 */
template<typename _CharT, typename _Traits>
inline bool operator<(const basic_cstring<_CharT, _Traits>& __lhs,
                      typename __cstring_const_pointer<_CharT>::__pointer __rhs) CPP_NOEXCEPT
{ return __lhs.compare(__rhs) < 0; }

/**
 *  @brief  Test if C string precedes cstring.
 *  @param lhs  C string.
 *  @param rhs  Cstring.
 *  @return  True if @a lhs precedes @a rhs.  False otherwise.
 */
template<typename _CharT, typename _Traits>
inline bool operator<(typename __cstring_const_pointer<_CharT>::__pointer __lhs,
                      const basic_cstring<_CharT, _Traits>& __rhs) CPP_NOEXCEPT
{ return __rhs.compare(__lhs) > 0; }

/**
 *  @brief  Test if cstring precedes string.
 *  @param lhs  Cstring.
 *  @param rhs  string.
 *  @return  True if @a lhs precedes @a rhs.  False otherwise.
 */
template<typename _CharT, typename _CharT2, typename _Traits, typename _Alloc>
inline bool operator<(const basic_cstring<_CharT, _Traits>& __lhs,
                      const std::basic_string<_CharT2, _Traits, _Alloc>& __rhs) CPP_NOEXCEPT
{ return __rhs.compare(0, __lhs.size(), __lhs.c_str()) < 0; }

/**
 *  @brief  Test if string precedes cstring.
 *  @param lhs  string.
 *  @param rhs  Cstring.
 *  @return  True if @a lhs precedes @a rhs.  False otherwise.
 */
template<typename _CharT, typename _CharT2, typename _Traits, typename _Alloc>
inline bool operator<(const std::basic_string<_CharT, _Traits, _Alloc>& __lhs,
                      const basic_cstring<_CharT2, _Traits>& __rhs) CPP_NOEXCEPT
{ return __rhs.compare(0, __lhs.size(), __lhs.c_str()) > 0; }

// operator >
/**
 *  @brief  Test if cstring follows cstring.
 *  @param lhs  First cstring.
 *  @param rhs  Second cstring.
 *  @return  True if @a lhs follows @a rhs.  False otherwise.
 */
template<typename _CharT, typename _CharT2, typename _Traits>
inline bool operator>(const basic_cstring<_CharT, _Traits>& __lhs,
                      const basic_cstring<_CharT2, _Traits>& __rhs) CPP_NOEXCEPT
{ return __lhs.compare(__rhs) > 0; }

/**
 *  @brief  Test if cstring follows C string.
 *  @param lhs  Cstring.
 *  @param rhs  C string.
 *  @return  True if @a lhs follows @a rhs.  False otherwise.
 */
template<typename _CharT, typename _Traits>
inline bool operator>(const basic_cstring<_CharT, _Traits>& __lhs,
                      typename __cstring_const_pointer<_CharT>::__pointer __rhs) CPP_NOEXCEPT
{ return __lhs.compare(__rhs) > 0; }

/**
 *  @brief  Test if C string follows cstring.
 *  @param lhs  C string.
 *  @param rhs  Cstring.
 *  @return  True if @a lhs follows @a rhs.  False otherwise.
 */
template<typename _CharT, typename _Traits>
inline bool operator>(typename __cstring_const_pointer<_CharT>::__pointer __lhs,
                      const basic_cstring<_CharT, _Traits>& __rhs) CPP_NOEXCEPT
{ return __rhs.compare(__lhs) < 0; }

/**
 *  @brief  Test if cstring follows string.
 *  @param lhs  Cstring.
 *  @param rhs  String.
 *  @return  True if @a lhs follows @a rhs.  False otherwise.
 */
template<typename _CharT, typename _CharT2, typename _Traits, typename _Alloc>
inline bool operator>(const basic_cstring<_CharT, _Traits>& __lhs,
                      const std::basic_string<_CharT2, _Traits, _Alloc>& __rhs) CPP_NOEXCEPT
{ return __rhs.compare(0, __lhs.size(), __lhs.c_str()) < 0; }

/**
 *  @brief  Test if string follows cstring.
 *  @param lhs  String.
 *  @param rhs  Cstring.
 *  @return  True if @a lhs follows @a rhs.  False otherwise.
 */
template<typename _CharT, typename _CharT2, typename _Traits, typename _Alloc>
inline bool operator>(const std::basic_string<_CharT, _Traits, _Alloc>& __lhs,
                      const basic_cstring<_CharT2, _Traits>& __rhs) CPP_NOEXCEPT
{ return __lhs.compare(0, __rhs.size(), __rhs.c_str()) > 0; }

// operator <=
/**
 *  @brief  Test if cstring doesn't follow cstring.
 *  @param lhs  First cstring.
 *  @param rhs  Second cstring.
 *  @return  True if @a lhs doesn't follow @a rhs.  False otherwise.
 */
template<typename _CharT, typename _CharT2, typename _Traits>
inline bool operator<=(const basic_cstring<_CharT, _Traits>& __lhs,
                       const basic_cstring<_CharT2, _Traits>& __rhs) CPP_NOEXCEPT
{ return __lhs.compare(__rhs) <= 0; }

/**
 *  @brief  Test if cstring doesn't follow C string.
 *  @param lhs  Cstring.
 *  @param rhs  C string.
 *  @return  True if @a lhs doesn't follow @a rhs.  False otherwise.
 */
template<typename _CharT, typename _Traits>
inline bool operator<=(const basic_cstring<_CharT, _Traits>& __lhs,
                       typename __cstring_const_pointer<_CharT>::__pointer __rhs) CPP_NOEXCEPT
{ return __lhs.compare(__rhs) <= 0; }

/**
 *  @brief  Test if C string doesn't follow cstring.
 *  @param lhs  C string.
 *  @param rhs  Cstring.
 *  @return  True if @a lhs doesn't follow @a rhs.  False otherwise.
 */
template<typename _CharT, typename _Traits>
inline bool operator<=(typename __cstring_const_pointer<_CharT>::__pointer __lhs,
                       const basic_cstring<_CharT, _Traits>& __rhs) CPP_NOEXCEPT
{ return __rhs.compare(__lhs) >= 0; }

/**
 *  @brief  Test if cstring doesn't follow string.
 *  @param lhs  Cstring.
 *  @param rhs  string.
 *  @return  True if @a lhs doesn't follow @a rhs.  False otherwise.
 */
template<typename _CharT, typename _CharT2, typename _Traits, typename _Alloc>
inline bool operator<=(const basic_cstring<_CharT, _Traits>& __lhs,
                       const std::basic_string<_CharT2, _Traits, _Alloc>& __rhs) CPP_NOEXCEPT
{ return __lhs.compare(0, __rhs.size(), __rhs.c_str()) <= 0; }

/**
 *  @brief  Test if string doesn't follow cstring.
 *  @param lhs  string.
 *  @param rhs  Cstring.
 *  @return  True if @a lhs doesn't follow @a rhs.  False otherwise.
 */
template<typename _CharT, typename _CharT2, typename _Traits, typename _Alloc>
inline bool operator<=(const std::basic_string<_CharT, _Traits, _Alloc>& __lhs,
                       const basic_cstring<_CharT2, _Traits>& __rhs) CPP_NOEXCEPT
{ return __rhs.compare(0, __lhs.size(), __lhs.c_str()) >= 0; }

// operator >=
/**
 *  @brief  Test if cstring doesn't precede cstring.
 *  @param lhs  First cstring.
 *  @param rhs  Second cstring.
 *  @return  True if @a lhs doesn't precede @a rhs.  False otherwise.
 */
template<typename _CharT, typename _CharT2, typename _Traits>
inline bool operator>=(const basic_cstring<_CharT, _Traits>& __lhs,
                       const basic_cstring<_CharT2, _Traits>& __rhs) CPP_NOEXCEPT
{ return __lhs.compare(__rhs) >= 0; }

/**
 *  @brief  Test if cstring doesn't precede C string.
 *  @param lhs  Cstring.
 *  @param rhs  C string.
 *  @return  True if @a lhs doesn't precede @a rhs.  False otherwise.
 */
template<typename _CharT, typename _Traits>
inline bool operator>=(const basic_cstring<_CharT, _Traits>& __lhs,
                       typename __cstring_const_pointer<_CharT>::__pointer __rhs) CPP_NOEXCEPT
{ return __lhs.compare(__rhs) >= 0; }

/**
 *  @brief  Test if C string doesn't precede cstring.
 *  @param lhs  C string.
 *  @param rhs  Cstring.
 *  @return  True if @a lhs doesn't precede @a rhs.  False otherwise.
 */
template<typename _CharT, typename _Traits>
inline bool operator>=(typename __cstring_const_pointer<_CharT>::__pointer __lhs,
                       const basic_cstring<_CharT, _Traits>& __rhs) CPP_NOEXCEPT
{ return __rhs.compare(__lhs) <= 0; }

/**
 *  @brief  Test if cstring doesn't precede string.
 *  @param lhs  Cstring.
 *  @param rhs  String.
 *  @return  True if @a lhs doesn't precede @a rhs.  False otherwise.
 */
template<typename _CharT, typename _CharT2, typename _Traits, typename _Alloc>
inline bool operator>=(const basic_cstring<_CharT, _Traits>& __lhs,
                       const std::basic_string<_CharT2, _Traits, _Alloc>& __rhs) CPP_NOEXCEPT
{ return __rhs.compare(0, __lhs.size(), __lhs.c_str()) <= 0; }

/**
 *  @brief  Test if C string doesn't precede cstring.
 *  @param lhs  String.
 *  @param rhs  Cstring.
 *  @return  True if @a lhs doesn't precede @a rhs.  False otherwise.
 */
template<typename _CharT, typename _CharT2, typename _Traits, typename _Alloc>
inline bool operator>=(const std::basic_string<_CharT, _Traits, _Alloc>& __lhs,
                       const basic_cstring<_CharT2, _Traits>& __rhs) CPP_NOEXCEPT
{ return __lhs.compare(0, __rhs.size(), __rhs.c_str()) >= 0; }


/**
 *  @brief  Concatenate two cstring.
 *  @param __lhs  First cstring.
 *  @param __rhs  Last cstring.
 *  @return  New string with value of @a __lhs followed by @a __rhs.
 */
template<typename _CharT, typename _CharT2, typename _Traits>
inline std::basic_string<typename _Traits::char_type, _Traits>
operator+(const basic_cstring<_CharT, _Traits>& __lhs,
          const basic_cstring<_CharT2, _Traits>& __rhs)
{
	std::basic_string<typename _Traits::char_type, _Traits> __str;
	__str.reserve(__lhs.size() + __rhs.size());
	__str.append(__lhs);
	__str.append(__rhs);
	return __str;
}

/**
 *  @brief  Concatenate string and cstring.
 *  @param __lhs  First string.
 *  @param __rhs  Last cstring.
 *  @return  New string with value of @a __lhs followed by @a __rhs.
 */
template<typename _CharT, typename _CharT2, typename _Traits, typename _Alloc>
inline std::basic_string<typename _Traits::char_type, _Traits, _Alloc>
operator+(const std::basic_string<_CharT, _Traits, _Alloc>& __lhs,
          const basic_cstring<_CharT2, _Traits>& __rhs)
{
	std::basic_string<typename _Traits::char_type, _Traits, _Alloc> __str;
	__str.reserve(__lhs.size() + __rhs.size());
	__str.append(__lhs);
	__str.append(__rhs.c_str(), __rhs.size());
	return __str;
}

/**
 *  @brief  Concatenate cstring and string.
 *  @param __lhs  First cstring.
 *  @param __rhs  Last string.
 *  @return  New string with value of @a __lhs followed by @a __rhs.
 */
template<typename _CharT, typename _CharT2, typename _Traits, typename _Alloc>
inline std::basic_string<typename _Traits::char_type, _Traits, _Alloc>
operator+(const basic_cstring<_CharT, _Traits>& __lhs,
          const std::basic_string<_CharT2, _Traits, _Alloc>& __rhs)
{
	std::basic_string<typename _Traits::char_type, _Traits, _Alloc> __str;
	__str.reserve(__lhs.size() + __rhs.size());
	__str.append(__lhs.c_str(), __lhs.size());
	__str.append(__rhs);
	return __str;
}

/**
 *  @brief  Append a cstring to string.
 *  @param __lhs  string.
 *  @param __rhs  The cstring to append.
 *  @return  Reference to __lhs.
 */
template<typename _CharT, typename _CharT2, typename _Traits, typename _Alloc>
inline std::basic_string<typename _Traits::char_type, _Traits, _Alloc>&
operator+=(std::basic_string<_CharT, _Traits, _Alloc>& __lhs,
           const basic_cstring<_CharT2, _Traits>& __rhs)
{ return __lhs.append(__rhs.c_str(), __rhs.size()); }

/**
 *  @brief  Append a cstring to string.
 *  @param __lhs  string.
 *  @param __rhs  The cstring to append.
 *  @return  Reference to __lhs.
 */
template<typename _CharT, typename _CharT2, typename _Traits, typename _Alloc>
inline std::basic_string<typename _Traits::char_type, _Traits, _Alloc>&
operator+=(std::basic_string<typename _Traits::char_type, _Traits, _Alloc>& __lhs,
           const basic_cstring<const _CharT, _Traits>& __rhs)
{ return __lhs.append(__rhs.c_str(), __rhs.size()); }


/**
 *  @brief  Write string to a stream.
 *  @param os  Output stream.
 *  @param str  String to write out.
 *  @return  Reference to the output stream.
 *
 *  Output characters of @a str into os following the same rules as for
 *  writing a C string.
 */
template<typename _CharT, typename _Traits, typename _StringCharT, typename _StringTraits>
inline std::basic_ostream<_CharT, _Traits>&
operator<<(std::basic_ostream<_CharT, _Traits>& __os,
           const basic_cstring<_StringCharT, _StringTraits>& __str)
{ return ostream_insert(__os, __str.data(), __str.size()); }


/**
 *  @brief  Swap contents of two strings.
 *  @param lhs  First string.
 *  @param rhs  Second string.
 *
 *  Exchanges the contents of @a lhs and @a rhs in constant time.
 */
template<typename _CharT, typename _Traits>
inline void swap(basic_cstring<_CharT, _Traits>& __lhs,
                 basic_cstring<_CharT, _Traits>& __rhs) CPP_NOEXCEPT
{ __lhs.swap(__rhs); }


#define __FALCON_BASIC_CSTRING_TO_IMPL(result_type, fname, std_fname, cstring_type)\
	inline result_type fname(const cstring_type& __str, std::size_t* __idx = 0, int __base = 10)\
	{ return ::falcon::detail::stoa<result_type>\
	(&std_fname, #fname, __str.c_str(), __idx, __base); }

#define __FALCON_BASIC_CSTRING_TO(result_type, fname, type)\
	__FALCON_BASIC_CSTRING_TO_IMPL(result_type, fname, strto##type, cstring)\
	__FALCON_BASIC_CSTRING_TO_IMPL(result_type, fname, strto##type, const_cstring)\
	__FALCON_BASIC_CSTRING_TO_IMPL(result_type, fname, wcsto##type, cwstring)\
	__FALCON_BASIC_CSTRING_TO_IMPL(result_type, fname, wcsto##type, const_cwstring)

__FALCON_BASIC_CSTRING_TO(int, stoi, l)
__FALCON_BASIC_CSTRING_TO(long, stol, l)
__FALCON_BASIC_CSTRING_TO(unsigned long, stoul, ul)
#if __cplusplus >= 201103L
__FALCON_BASIC_CSTRING_TO(long long, stoll, ull)
__FALCON_BASIC_CSTRING_TO(unsigned long long, stoull, ull)
#endif

#undef __FALCON_BASIC_CSTRING_TO_IMPL

#define __FALCON_BASIC_CSTRING_TO_IMPL(result_type, fname, std_fname, cstring_type)\
	inline result_type fname(const cstring_type& __str, std::size_t* __idx = 0)\
	{ return ::falcon::detail::stoa<result_type>\
	(&std_fname, #fname, __str.c_str(), __idx); }

__FALCON_BASIC_CSTRING_TO(float, stof, f)
__FALCON_BASIC_CSTRING_TO(double, stod, d)
#if __cplusplus >= 201103L
__FALCON_BASIC_CSTRING_TO(double long, stold, ld)
#endif

#undef __FALCON_BASIC_CSTRING_TO
#undef __FALCON_BASIC_CSTRING_TO_IMPL

inline std::string to_string(const cstring& s)
{ return std::string(s.data(), s.size()); }

inline std::string to_string(const const_cstring& s)
{ return std::string(s.data(), s.size()); }

inline std::wstring to_wstring(const cwstring& s)
{ return std::wstring(s.data(), s.size()); }

inline std::wstring to_wstring(const const_cwstring& s)
{ return std::wstring(s.data(), s.size()); }

}

#if __cplusplus >= 201103L
namespace  std {

template<typename _CharT, typename _Traits>
struct hash<falcon::basic_cstring<_CharT, _Traits> >
{
  typedef size_t result_type;
  typedef falcon::basic_cstring<_CharT, _Traits> argument_type;

  result_type operator()(const argument_type& s) const noexcept
  {
    result_type __h = static_cast<result_type>(0xc70f6907UL);
    for (_CharT c: s) {
      __h ^= static_cast<result_type>(c) + (__h << 6) + (__h >> 2);
    }
    return __h;
  }
};

}
#endif


#endif
