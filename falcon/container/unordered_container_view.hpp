#ifndef FALCON_CONTAINER_UNORDERED_CONTAINER_VIEW_HPP
#define FALCON_CONTAINER_UNORDERED_CONTAINER_VIEW_HPP

#include <falcon/algorithm/unordered.hpp>
#include <initializer_list>
#include <utility>

namespace falcon {

template<class Cont>
struct unordered_container_view
{
  typedef Cont container_type;

  typedef typename container_type::size_type size_type;
  typedef typename container_type::value_type value_type;
  typedef typename container_type::pointer pointer;
  typedef typename container_type::const_pointer const_pointer;
  typedef typename container_type::reference reference;
  typedef typename container_type::const_reference const_reference;

  typedef typename container_type::iterator iterator;
  typedef typename container_type::const_iterator const_iterator;
  typedef typename container_type::reverse_iterator reverse_iterator;
  typedef typename container_type::const_reverse_iterator const_reverse_iterator;

  unordered_container_view() = default;

  unordered_container_view(container_type & cont) noexcept
  : c(&cont)
  {}

  unordered_container_view & operator=(container_type & cont)
  {
    c = &cont;
    return *this;
  }

  unordered_container_view & operator=(unordered_container_view const & other) = default;

  iterator erase(const_iterator pos)
  { return unordered_erase(c, pos); }

  iterator erase(const_iterator first, const_iterator last)
  { return unordered_erase(*c, first, last); }

  void push_back(const value_type & value)
  { c->push_back(value); }

  void push_back(value_type && value)
  { c->push_back(std::move(value)); }

  template<typename... Args>
  void emplace_back(Args &&... args)
  { c->emplace_back(std::forward<Args>(args)...); }

  void insert(value_type && value)
  { c->push_back(std::move(value)); }

  void insert(std::initializer_list<value_type> ilist)
  { c->insert(c->end(), ilist); }

  void insert(size_type count, const value_type & value)
  { c->insert(c->end(), count, value); }

  template< class InputIt >
  void insert(InputIt first, InputIt last)
  { c->insert(c->end(), first, last); }

  void insert(const value_type & value)
  { c->push_back(value); }

  void remove(const value_type & x)
  { c->erase(unordered_remove(c->begin(), c->end(), x), c->end()); }

  template<typename UnaryPredicate>
  void remove_if(UnaryPredicate pred)
  { c->erase(unordered_remove_if(c->begin(), c->end(), pred), c->end()); }

private:
  container_type * c = nullptr;
};

template<class Cont>
unordered_container_view<Cont>
unordered_view(Cont & cont) noexcept
{ return unordered_container_view<Cont>(cont); }

}

#endif
