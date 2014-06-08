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
#include <stdexcept>

namespace falcon {

namespace _aux {
  struct free_list_node_base
  {
#if __cplusplus >= 201103L
    free_list_node_base * next = nullptr;
#else
    free_list_node_base * next;

    free_list_node_base()
    : next(0)
    {}
#endif
  };

  template<class T>
  struct free_list_node
  : free_list_node_base
  {
    aligned_buffer<T> storage;

    T* valptr() CPP_NOEXCEPT
    { return storage.ptr(); }

    const T* valptr() const CPP_NOEXCEPT
    { return storage.ptr(); }
  };
}

template<class T, class Alloc = std::allocator<T> >
class free_list
{
  typedef _aux::free_list_node<T> Node;
  typedef FALCON_BOOST_OR_STD_NAMESPACE::allocator_traits<Alloc> alloc_traits;
  typedef typename alloc_traits::template rebind_alloc<Node> node_alloc_type;
  typedef FALCON_BOOST_OR_STD_NAMESPACE
    ::allocator_traits<node_alloc_type> node_alloc_traits;
  typedef typename alloc_traits::template rebind_alloc<T> tp_alloc_type;
  typedef FALCON_BOOST_OR_STD_NAMESPACE
    ::allocator_traits<tp_alloc_type>  allocator_traits;

public:
  typedef typename allocator_traits::value_type value_type;
  typedef typename allocator_traits::pointer pointer;
  typedef typename allocator_traits::size_type size_type;
  typedef Alloc allocator_type;

private:
  struct list_impl
  : public node_alloc_type
  {
    _aux::free_list_node_base * head;

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

    Node * get_node() const CPP_NOEXCEPT
    { return reinterpret_cast<Node*>(head); }

    Node * to_node(pointer p) const CPP_NOEXCEPT
    {
      return reinterpret_cast<Node*>(reinterpret_cast<char*>(
#if __cplusplus >= 201103L
        std::pointer_traits<pointer>::pointer_to(*p)
#else
        p
#endif
      ) - (sizeof(Node) - sizeof(_aux::free_list_node_base)));
    }
  };

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

  free_list& operator=(free_list&& other)
  CPP_NOEXCEPT_OPERATOR2(other.allocator_ = std::move(other.allocator_))
  {
    clear();
    impl = std::move(other.impl);
    size_alloc_ = other.size_alloc_;
    other.impl.head = 0;
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
  { return allocator_type(*static_cast<node_alloc_type const *>(&this->impl)); }

private:
  node_alloc_type&
  get_Node_allocator() noexcept
  { return *static_cast<node_alloc_type*>(&this->impl); }

  Node*
  get_node()
  {
    auto ptr = node_alloc_traits::allocate(get_Node_allocator(), size_alloc_);
    return addressof(*ptr);
  }

public:
  pointer alloc()
  {
    if ( ! impl.head ) {
      Node * node = get_node();
      return pointer(node->valptr());
    }
    Node * node = impl.get_node();
    impl.head = impl.head->next;
    return pointer(node->valptr());
  }

  void free(pointer p) CPP_NOEXCEPT
  {
    Node * node = impl.to_node(p);
    node->next = impl.head;
    impl.head = node;
  }

  void clear() CPP_NOEXCEPT
  {
    while (impl.head) {
      Node * node = impl.get_node();
      impl.head = node->next;
      node_alloc_traits::deallocate(get_Node_allocator(), node, size_alloc_);
    }
  }

  size_type count_by_alloc() const
  { return size_alloc_; }

  void merge(free_list& other)
  {
    if (other.size_alloc_ < size_alloc_) {
      throw std::underflow_error("free_list::merge");
    }

    if (impl.head) {
      Node * node = impl.head;
      while (node->next) {
        node = node->next;
      }
      node->next = other.impl.head;
    }
    else {
      impl.head = other.impl.head;
    }

    other.impl.head = 0;
  }

  bool operator==(const free_list& rhs) const
  {
    return size_alloc_ == rhs.size_alloc_
      && get_Node_allocator() == rhs.get_Node_allocator();
  }

  bool operator!=(const free_list& rhs) const
  { return !operator==(rhs); }

private:
  list_impl impl;
  size_type size_alloc_;
};

}

#endif
