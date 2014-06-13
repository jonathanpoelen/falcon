#ifndef FALCON_MEMORY_FREE_LIST_HPP
#define FALCON_MEMORY_FREE_LIST_HPP

#include <falcon/bit/byte_cast.hpp>
#include <falcon/c++/reference.hpp>
#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/pack.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include <falcon/utility/move.hpp>
#include <falcon/memory/aligned_buffer.hpp>
#include <falcon/memory/addressof.hpp>

#include <memory>
#if __cplusplus >= 201103L
# include <utility>
#else
# include <boost/container/allocator_traits.hpp>
#endif

#include <cassert>

namespace falcon {

template<class T, class Alloc = std::allocator<T> >
class free_list
{
  struct list_node
  {
    aligned_buffer<T> storage;
#if __cplusplus >= 201103L
    list_node * next = nullptr;
#else
    list_node * next;

    list_node()
    : next(0)
    {}
#endif

    T* valptr() CPP_NOEXCEPT
    { return storage.ptr(); }

    const T* valptr() const CPP_NOEXCEPT
    { return storage.ptr(); }
  };

  typedef FALCON_BOOST_OR_STD_NAMESPACE::allocator_traits<Alloc> alloc_traits;
  typedef typename alloc_traits::template rebind_alloc<list_node> node_alloc_type;
  typedef FALCON_BOOST_OR_STD_NAMESPACE
    ::allocator_traits<node_alloc_type> node_alloc_traits;
  typedef typename alloc_traits::template rebind_alloc<T> tp_alloc_type;
  typedef FALCON_BOOST_OR_STD_NAMESPACE
    ::allocator_traits<tp_alloc_type> allocator_traits;

public:
  typedef typename allocator_traits::value_type value_type;
  typedef typename allocator_traits::pointer pointer;
  typedef typename allocator_traits::size_type size_type;
  typedef typename allocator_traits::difference_type difference_type;
  typedef typename allocator_traits::const_pointer const_pointer;
  typedef Alloc allocator_type;
  typedef free_list free_list_type;

private:
  struct list_impl
  : public node_alloc_type
  {
    list_node * head;

    list_impl()
    : node_alloc_type()
    , head(0)
    { }

    list_impl(const node_alloc_type& a)
    : node_alloc_type(a)
    , head(0)
    { }

    template<class CPP_PACK Args>
    list_impl(Args CPP_RVALUE_OR_CONST_REFERENCE CPP_PACK args)
    : node_alloc_type(FALCON_FORWARD(Args, args)CPP_PACK)
    , head(0)
    { }
  };

  node_alloc_type&
  get_node_allocator() CPP_NOEXCEPT
  { return static_cast<node_alloc_type&>(this->impl); }

  const node_alloc_type&
  get_node_allocator() const CPP_NOEXCEPT
  { return static_cast<node_alloc_type const &>(this->impl); }

  list_node*
  get_node()
  {
    auto ptr = node_alloc_traits::allocate(get_node_allocator(), size_alloc_);
    return addressof(*ptr);
  }

public:
  explicit free_list(size_type size_alloc)
  CPP_NOEXCEPT_OPERATOR2(allocator_type())
  : impl()
  , size_alloc_(size_alloc)
  {}

  free_list(size_type size_alloc, const allocator_type& allocator)
  CPP_NOEXCEPT_OPERATOR2(allocator_type(allocator))
  : impl(node_alloc_type(allocator))
  , size_alloc_(size_alloc)
  {}

  template<class CPP_PACK Args>
  free_list(size_type size_alloc, Args CPP_RVALUE_OR_CONST_REFERENCE CPP_PACK args)
  CPP_NOEXCEPT_OPERATOR2(allocator_type(FALCON_FORWARD(Args, args)CPP_PACK))
  : impl(node_alloc_type(FALCON_FORWARD(Args, args)CPP_PACK))
  , size_alloc_(size_alloc)
  {}

#if __cplusplus >= 201103L
  free_list(size_type size_alloc, allocator_type&& allocator)
  CPP_NOEXCEPT_OPERATOR2(allocator_node_type(std::forward<allocator_type>(allocator)))
  : impl(node_alloc_type(std::forward<allocator_type>(allocator)))
  , size_alloc_(size_alloc)
  {}

  free_list(free_list&& other)
  CPP_NOEXCEPT_OPERATOR2(std::move(other.allocator_))
  : impl(std::move(other.impl))
  , size_alloc_(other.size_alloc_)
  { impl.head = 0; }

  /**
  * \sa merge
  */
  free_list& operator=(free_list && other) CPP_NOEXCEPT
  {
    merge(other);
    return *this;
  }

  free_list(const free_list&) = delete;
  free_list& operator=(const free_list&) = delete;
#else
private:
  free_list(const free_list&);
  free_list& operator=(const free_list&);
public:
#endif

  ~free_list() CPP_NOEXCEPT
  {
    clear();
  }

  allocator_type get_allocator() const
  CPP_NOEXCEPT_OPERATOR2(allocator_type(std::declval<free_list>().get_node_allocator()))
  { return allocator_type(get_node_allocator()); }

  pointer alloc()
  {
    if ( empty() ) {
      list_node * node = get_node();
      return pointer(node->valptr());
    }
    list_node * node = impl.head;
    impl.head = impl.head->next;
    return pointer(node->valptr());
  }

  void free(pointer p) CPP_NOEXCEPT
  {
    list_node * node = reinterpret_cast<list_node*>(p);
    node->next = impl.head;
    impl.head = node;
  }

  /**
   * \post \p empty() == true
   */
  void clear() CPP_NOEXCEPT
  {
    while (impl.head) {
      list_node * node = impl.head;
      impl.head = node->next;
      node_alloc_traits::deallocate(get_node_allocator(), node, size_alloc_);
    }
  }

  bool empty() const CPP_NOEXCEPT
  { return !impl.head; }

  size_type count_by_alloc() const CPP_NOEXCEPT
  { return size_alloc_; }

  /**
   * \pre \a *this == \a other
   * \post \p other.empty == true
   */
  void merge(free_list& other) CPP_NOEXCEPT
  {
    assert(other == *this);

    list_node * head = other.impl.head;
    other.impl.head = 0;

    if (empty()) {
      impl.head = head;
    }
    else if (head) {
      list_node * node = impl.head;
      while (node->next) {
        node = node->next;
      }
      node->next = head;
    }
  }

  /**
   * \return true \p rhs.count_by_alloc and \p rhd.get_allocator are the same
   */
  bool operator==(const free_list& rhs) const CPP_NOEXCEPT
  { return size_alloc_ == rhs.size_alloc_ && get_allocator() == rhs.get_allocator(); }

  bool operator!=(const free_list& rhs) const CPP_NOEXCEPT
  { return !operator==(rhs); }

private:
  list_impl impl;
  size_type size_alloc_;
};

}

#endif
