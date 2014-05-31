#ifndef FALCON_MEMORY_FREE_LIST_HPP
#define FALCON_MEMORY_FREE_LIST_HPP

#include <falcon/bit/byte_cast.hpp>
#include <falcon/c++/reference.hpp>
#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/pack.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include <falcon/utility/move.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(aligned_storage)

#include <memory>
#if __cplusplus >= 201103L
# include <utility>
#else
# include <boost/container/allocator_traits.hpp>
#endif
#include <stdexcept>

namespace falcon {

template<class T, class Alloc = std::allocator<T> >
class free_list
{
  struct Node
  {
    Node * next;
    unsigned char data[1];
  };

public:
  static const std::size_t s_align
    = FALCON_BOOST_OR_STD_NAMESPACE::alignment_of<T>::value;
  static const std::size_t s_heap = (s_align > sizeof(Node)) ? s_align : sizeof(Node);

public:
  typedef typename FALCON_BOOST_OR_STD_NAMESPACE::allocator_traits<Alloc>
    ::template rebind_alloc<byte_t>::type allocator_type;

private:
  typedef typename FALCON_BOOST_OR_STD_NAMESPACE::allocator_traits<Alloc>
    ::template rebind_alloc<T>::type allocator_traits;

public:
  typedef typename allocator_traits::value_type value_type;
  typedef typename allocator_traits::pointer pointer;
  typedef typename allocator_traits::size_type size_type;

public:
  explicit free_list(size_type size_alloc) CPP_NOEXCEPT_OPERATOR2(allocator_type())
  : node_(0)
  , size_alloc_(size_alloc)
  , allocator_()
  {}

  free_list(size_type size_alloc, const allocator_type& allocator)
  CPP_NOEXCEPT_OPERATOR2(allocator_type(allocator))
  : node_(0)
  , size_alloc_(size_alloc)
  , allocator_(allocator)
  {}

  template<class CPP_PACK Args>
  free_list(size_type size_alloc, Args CPP_RVALUE_OR_CONST_REFERENCE CPP_PACK args)
  CPP_NOEXCEPT_OPERATOR2(allocator_type(FALCON_FORWARD(Args, args)CPP_PACK))
  : node_(0)
  , size_alloc_(size_alloc)
  , allocator_(FALCON_FORWARD(Args, args)CPP_PACK)
  {}

#if __cplusplus >= 201103L
  free_list(size_type size_alloc, allocator_type&& allocator)
  CPP_NOEXCEPT_OPERATOR2(allocator_type(std::forward<allocator_type>(allocator)))
  : node_(0)
  , size_alloc_(size_alloc)
  , allocator_(std::forward<allocator_type>(allocator))
  {}

  free_list(free_list&& other)
  CPP_NOEXCEPT_OPERATOR2(std::forward<allocator_type>(other.allocator_))
  : node_(other.node_)
  , size_alloc_(other.size_alloc_)
  , allocator_(std::forward<allocator_type>(other.allocator_))
  { other.node_ = 0; }

  free_list& operator=(free_list&& other)
  CPP_NOEXCEPT_OPERATOR2(
    other.allocator_ = std::forward<allocator_type>(other.allocator_))
  {
    clear();
    node_ = other.node_;
    size_alloc_ = other.size_alloc_;
    allocator_ = std::forward<allocator_type>(other.allocator_);
    other.node_ = 0;
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

  pointer alloc()
  {
    if ( ! node_) {
      return reinterpret_cast<pointer>(
        allocator_traits::allocate(
          allocator_
        , s_heap + size_alloc_ * sizeof(T)) + s_heap
      );
    }
    pointer ret = reinterpret_cast<pointer>(node_->data);
    node_ = node_->next;
    return ret;
  }

  void free(pointer p)
  {
    Node * tmp = node_;
    node_ = reinterpret_cast<Node*>(byte_cast(p) - s_heap);
    node_->next = tmp;
  }

  void clear() CPP_NOEXCEPT
  {
    while (node_) {
      Node * node = node_->next;
      allocator_traits::deallocate(
        allocator_, byte_cast(node_)
      , s_heap + size_alloc_ * sizeof(T));
      node_ = node;
    }
  }

  size_type count_by_alloc() const
  { return size_alloc_; }

  void merge(free_list& other)
  {
    if (other.size_alloc_ < size_alloc_) {
      throw std::underflow_error("free_list::merge");
    }

    if (node_) {
      Node * node = node_;
      while (node->next) {
        node = node->next;
      }
      node->next = other.node_;
    }
    else {
      node_ = other.node_;
    }

    other.node_ = 0;
  }

  bool operator==(const free_list& rhs) const
  { return size_alloc_ == rhs.size_alloc_ && allocator_ == rhs.allocator_; }

  bool operator!=(const free_list& rhs) const
  { return !operator==(rhs); }

private:
  Node * node_;
  size_type size_alloc_;
  allocator_type allocator_;
};

}

#endif
