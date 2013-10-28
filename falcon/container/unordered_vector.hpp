#ifndef FALCON_CONTAINER_UNORDERED_VECTOR_HPP
#define FALCON_CONTAINER_UNORDERED_VECTOR_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/noexcept.hpp>
#include <falcon/algorithm/unordered_algorithm.hpp>

#include <vector>
#if __cplusplus >= 201103L
# include <utility>
#endif

namespace falcon {

/**
 * \ingroup sequence
 */
template<typename T, typename Allocator = std::allocator<T> >
class unordered_vector
{
  typedef std::vector<T, Allocator> container_type;

public:
  typedef typename container_type::value_type value_type;
  typedef typename container_type::pointer pointer;
  typedef typename container_type::const_pointer const_pointer;
  typedef typename container_type::reference reference;
  typedef typename container_type::const_reference const_reference;

  typedef typename container_type::iterator iterator;
  typedef typename container_type::const_iterator const_iterator;
  typedef typename container_type::reverse_iterator reverse_iterator;
  typedef typename container_type::const_reverse_iterator const_reverse_iterator;

  typedef typename container_type::size_type size_type;
  typedef typename container_type::difference_type difference_type;
  typedef typename container_type::allocator_type allocator_type;


  explicit unordered_vector(const Allocator & alloc = Allocator())
  : c(alloc)
  {}

  explicit unordered_vector(size_type count,
#if __cplusplus >= 201103L
                            const T & value,
#else
                            const T & value = T(),
#endif
                            const Allocator & alloc = Allocator())
  : c(count, value, alloc)
  {}

  template< class InputIt >
  unordered_vector(InputIt first, InputIt last,
                   const Allocator & alloc = Allocator())
  : c(first, last, alloc)
  {}

  unordered_vector(const unordered_vector & other)
  : c(other.c)
  {}

  unordered_vector(const container_type & other)
  : c(other)
  {}

#if __cplusplus >= 201103L
  unordered_vector(const unordered_vector & other, const Allocator & alloc)
  : c(std::move(other.c), alloc)
  {}

  unordered_vector(unordered_vector && other)
  : c(std::move(other.c))
  {}

  unordered_vector(unordered_vector && other, const Allocator & alloc)
  : c(std::move(other.c), alloc)
  {}

  unordered_vector(const container_type & other, const Allocator & alloc)
  : c(std::move(other), alloc)
  {}

  unordered_vector(container_type && other)
  : c(std::move(other))
  {}

  unordered_vector(container_type && other, const Allocator & alloc)
  : c(std::move(other), alloc)
  {}

  unordered_vector(std::initializer_list<T> init,
                   const Allocator & alloc = Allocator())
  : c(init, alloc)
  {}

#if __cplusplus < 201403L
  explicit unordered_vector(size_type count)
  : c(count)
  {}
#else
  explicit unordered_vector(size_type count, const Allocator & alloc = Allocator());
  : c(count, alloc)
  {}
#endif
#endif

  unordered_vector & operator=(const unordered_vector & other)
  {
    c = other.c;
    return *this;
  }

  unordered_vector & operator=(const container_type& other)
  {
    c = other;
    return *this;
  }

#if __cplusplus >= 201103L
  unordered_vector & operator=(unordered_vector && other) noexcept
  {
    c = other.c;
    return *this;
  }

  unordered_vector & operator=(container_type && other) noexcept
  {
    c = std::move(other);
    return *this;
  }

  unordered_vector & operator=(std::initializer_list<T> ilist)
  {
    c = ilist;
    return *this;
  }
#endif

  void assign( size_type count, const T& value )
  { c.assign(count, value); }

  template< class InputIt >
  void assign( InputIt first, InputIt last )
  { c.assign(first, last); }

#if __cplusplus >= 201103L
  void assign( std::initializer_list<T> ilist )
  { c.assign(ilist); }
#endif

  allocator_type get_allocator() const
  { return c.get_allocator(); }

  /// Elements access @{
  reference at(size_type pos)
  { return c.at(pos); }

  const_reference at(size_type pos) const
  { return c.at(pos); }

  reference operator[](size_type pos)
  { return c[pos]; }

  CPP_CONSTEXPR_NOT_CONST const_reference operator[](size_type pos) const
  { return c[pos]; }

  reference front()
  { return c.front(); }

  CPP_CONSTEXPR_NOT_CONST const_reference front() const
  { return c.front(); }

  reference back()
  { return c.back(); }

  CPP_CONSTEXPR_NOT_CONST const_reference back() const
  { return c.back(); }

  T* data() CPP_NOEXCEPT
  { return c.data(); }

  const T* data() const CPP_NOEXCEPT
  { return c.data(); }
  ///@}

  /// Iterators @{
  iterator begin()
  { return c.begin(); }

  const_iterator begin() const
  { return c.begin(); }

  iterator end()
  { return c.end(); }

  const_iterator end() const
  { return c.end(); }

  iterator rbegin()
  { return c.rbegin(); }

  const_iterator rbegin() const
  { return c.rbegin(); }

  iterator rend()
  { return c.rend(); }

  const_iterator rend() const
  { return c.rend(); }

#if __cplusplus >= 201103L
  const_iterator cbegin() const
  { return c.begin(); }

  const_iterator cend() const
  { return c.end(); }

  const_iterator crbegin() const
  { return c.rbegin(); }

  const_iterator crend() const
  { return c.rend(); }
#endif
  ///@}

  /// Capacity @{
  bool empty() const CPP_NOEXCEPT
  { return c.empty(); }

  size_type size() const CPP_NOEXCEPT
  { return c.size(); }

  size_type max_size() const CPP_NOEXCEPT
  { return c.max_size(); }

  void reserve( size_type new_cap )
  { c.reserve(new_cap); }

  size_type capacity() const CPP_NOEXCEPT
  { return c.capacity(); }

#if __cplusplus >= 201103L
  void shrink_to_fit()
  { c.shrink_to_fit(); }
#endif
  ///@}

  /// Modifiers @{
  void clear() CPP_NOEXCEPT
  { c.clear(); }

#if __cplusplus >= 201103L
  void resize( size_type count )
  { c.resize(count); }

  void resize( size_type count, const value_type & value)
#else
  void resize( size_type count, T value = T() )
#endif
  { c.resize(count, value); }

  void swap( unordered_vector & other )
  { c.swap(other.c); }

#if __cplusplus >= 201103L
  iterator erase(const_iterator pos)
#else
  iterator erase(iterator pos)
#endif
  { return unordered_erase(c, pos); }

#if __cplusplus >= 201103L
  iterator erase(const_iterator first, const_iterator last)
#else
  iterator erase(iterator first, iterator last)
#endif
  { return unordered_erase(c, first, last); }

  void push_back(const value_type & value)
  { c.push_back(value); }

#if __cplusplus >= 201103L
  void push_back(value_type && value)
  { c.push_back(std::move(value)); }

  template<typename... Args>
  void emplace_back(Args&&... args)
  { c.emplace_back(std::forward<Args>(args)...); }

  void insert(T && value)
  { c.push_back(std::move(value)); }

  void insert(std::initializer_list<T> ilist)
  { c.insert(c.end(), ilist); }
#endif

  void insert(size_type count, const T& value)
  { c.insert(c.end(), count, value); }

  template< class InputIt >
  void insert(InputIt first, InputIt last)
  { c.insert(c.end(), first, last); }

  void insert(const T & value)
  { c.push_back(value); }

  void remove(const T& x)
  { c.erase(unordered_remove(c.begin(), c.end(), x), c.end()); }

  template<typename UnaryPredicate>
  void remove_if(UnaryPredicate pred)
  { c.erase(unordered_remove_if(c.begin(), c.end(), pred), c.end()); }
  ///@}

protected:
  container_type c;
};


template<typename T, typename Allocator>
void swap(const unordered_vector<T, Allocator> & x,
          const unordered_vector<T, Allocator> & y)
{ x.swap(y); }


template<typename T, typename Allocator>
unordered_vector< T, Allocator > &
unordered_vector_cast(std::vector<T, Allocator> & x)
{ return reinterpret_cast<unordered_vector< T, Allocator > &>(x); }

template<typename T, typename Allocator>
const unordered_vector< T, Allocator > &
unordered_vector_cast(const std::vector<T, Allocator> & x)
{ return reinterpret_cast<const unordered_vector< T, Allocator > &>(x); }

#if __cplusplus >= 201103L
template<typename T, typename Allocator>
unordered_vector< T, Allocator > &
unordered_vector_cast(std::vector<T, Allocator> && x)
{ return reinterpret_cast<unordered_vector< T, Allocator > &&>(x); }
#endif


template<typename T, typename Allocator>
std::vector< T, Allocator > &
sequence_unordered_vector(unordered_vector<T, Allocator> & x)
{ return reinterpret_cast<std::vector< T, Allocator > &>(x); }

template<typename T, typename Allocator>
const std::vector< T, Allocator > &
sequence_unordered_vector(const unordered_vector<T, Allocator> & x)
{ return reinterpret_cast<const std::vector< T, Allocator > &>(x); }

#if __cplusplus >= 201103L
template<typename T, typename Allocator>
std::vector< T, Allocator > &&
sequence_unordered_vector(unordered_vector<T, Allocator> && x)
{ return reinterpret_cast<std::vector< T, Allocator > &&>(x); }
#endif


template<typename T, typename Allocator>
bool operator==(const unordered_vector<T, Allocator> & x,
                const unordered_vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) == sequence_unordered_vector(y); }

template<typename T, typename Allocator>
bool operator==(const std::vector<T, Allocator> & x,
                const unordered_vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) == sequence_unordered_vector(y); }

template<typename T, typename Allocator>
bool operator==(const unordered_vector<T, Allocator> & x,
                const std::vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) == sequence_unordered_vector(y); }


template<typename T, typename Allocator>
bool operator!=(const unordered_vector<T, Allocator> & x,
                const unordered_vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) != sequence_unordered_vector(y); }

template<typename T, typename Allocator>
bool operator!=(const std::vector<T, Allocator> & x,
                const unordered_vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) != sequence_unordered_vector(y); }

template<typename T, typename Allocator>
bool operator!=(const unordered_vector<T, Allocator> & x,
                const std::vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) != sequence_unordered_vector(y); }


template<typename T, typename Allocator>
bool operator<(const unordered_vector<T, Allocator> & x,
                const unordered_vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) < sequence_unordered_vector(y); }

template<typename T, typename Allocator>
bool operator<(const std::vector<T, Allocator> & x,
                const unordered_vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) < sequence_unordered_vector(y); }

template<typename T, typename Allocator>
bool operator<(const unordered_vector<T, Allocator> & x,
                const std::vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) < sequence_unordered_vector(y); }


template<typename T, typename Allocator>
bool operator<=(const unordered_vector<T, Allocator> & x,
                const unordered_vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) <= sequence_unordered_vector(y); }

template<typename T, typename Allocator>
bool operator<=(const std::vector<T, Allocator> & x,
                const unordered_vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) <= sequence_unordered_vector(y); }

template<typename T, typename Allocator>
bool operator<=(const unordered_vector<T, Allocator> & x,
                const std::vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) <= sequence_unordered_vector(y); }


template<typename T, typename Allocator>
bool operator>(const unordered_vector<T, Allocator> & x,
                const unordered_vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) > sequence_unordered_vector(y); }

template<typename T, typename Allocator>
bool operator>(const std::vector<T, Allocator> & x,
                const unordered_vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) > sequence_unordered_vector(y); }

template<typename T, typename Allocator>
bool operator>(const unordered_vector<T, Allocator> & x,
                const std::vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) > sequence_unordered_vector(y); }


template<typename T, typename Allocator>
bool operator>=(const unordered_vector<T, Allocator> & x,
                const unordered_vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) >= sequence_unordered_vector(y); }

template<typename T, typename Allocator>
bool operator>=(const std::vector<T, Allocator> & x,
                const unordered_vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) >= sequence_unordered_vector(y); }

template<typename T, typename Allocator>
bool operator>=(const unordered_vector<T, Allocator> & x,
                const std::vector<T, Allocator> & y)
{ return sequence_unordered_vector(x) >= sequence_unordered_vector(y); }

}

#endif
