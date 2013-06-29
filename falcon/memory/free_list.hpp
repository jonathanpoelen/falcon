#ifndef FALCON_MEMORY_FREE_LIST_HPP
#define FALCON_MEMORY_FREE_LIST_HPP

#include <falcon/memory/allocator_rebind.hpp>
#include <falcon/bit/byte_cast.hpp>
#include <falcon/c++/reference.hpp>
#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/extend_pack.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include <falcon/utility/move.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(aligned_storage)

#include <memory>
#if __cplusplus > 201100L
#include <utility>
#endif
#include <stdexcept>

namespace falcon {

template<typename T, typename Alloc = std::allocator<T> >
class free_list
{
  struct Node
  {
    Node * next;
    unsigned char data[1];
  };

public:
  static const std::size_t _S_align = FALCON_BOOST_OR_STD_NAMESPACE::alignment_of<T>::value;
  static const std::size_t _S_heap = (_S_align > sizeof(Node)) ? _S_align : sizeof(Node);

public:
  typedef typename allocator_rebind<Alloc, byte_t>::type allocator_type;
  typedef typename allocator_rebind<Alloc, T>::type::value_type value_type;
  typedef typename allocator_rebind<Alloc, T>::type::pointer pointer;
  typedef typename allocator_rebind<Alloc, T>::type::size_type size_type;

public:
  explicit free_list(size_type size_alloc) CPP_NOEXCEPT_OPERATOR2(allocator_type())
  : m_node(0)
  , m_size_alloc(size_alloc)
  , m_allocator()
  {}

  free_list(size_type size_alloc, const allocator_type& allocator)
  CPP_NOEXCEPT_OPERATOR2(allocator_type(allocator))
  : m_node(0)
  , m_size_alloc(size_alloc)
  , m_allocator(allocator)
  {}

  template<typename CPP_EXTEND_PACK Args>
  free_list(size_type size_alloc, Args CPP_RVALUE_OR_CONST_REFERENCE CPP_EXTEND_PACK args)
  CPP_NOEXCEPT_OPERATOR2(allocator_type(FALCON_FORWARD(Args, args)CPP_EXTEND_PACK))
  : m_node(0)
  , m_size_alloc(size_alloc)
  , m_allocator(FALCON_FORWARD(Args, args)CPP_EXTEND_PACK)
  {}

#if __cplusplus > 201100L
  free_list(size_type size_alloc, allocator_type&& allocator)
  CPP_NOEXCEPT_OPERATOR2(allocator_type(std::forward<allocator_type>(allocator)))
  : m_node(0)
  , m_size_alloc(size_alloc)
  , m_allocator(std::forward<allocator_type>(allocator))
  {}

  free_list(free_list&& other)
  CPP_NOEXCEPT_OPERATOR2(std::forward<allocator_type>(other.m_allocator))
  : m_node(other.m_node)
  , m_size_alloc(other.m_size_alloc)
  , m_allocator(std::forward<allocator_type>(other.m_allocator))
  { other.m_node = 0; }

  free_list& operator=(free_list&& other)
  CPP_NOEXCEPT_OPERATOR2(other.m_allocator = std::forward<allocator_type>(other.m_allocator))
  {
    clear();
    m_node = other.m_node;
    m_size_alloc = other.m_size_alloc;
    m_allocator = std::forward<allocator_type>(other.m_allocator);
    other.m_node = 0;
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
    if ( ! m_node) {
      return reinterpret_cast<pointer>(m_allocator.allocate(_S_heap + m_size_alloc * sizeof(T)) + _S_heap);
    }
    pointer ret = reinterpret_cast<pointer>(m_node->data);
    m_node = m_node->next;
    return ret;
  }

  void free(pointer p)
  {
    Node * tmp = m_node;
    m_node = reinterpret_cast<Node*>(byte_cast(p) - _S_heap);
    m_node->next = tmp;
  }

  void clear() CPP_NOEXCEPT
  {
    while (m_node) {
      Node * node = m_node->next;
      m_allocator.deallocate(byte_cast(m_node), _S_heap + m_size_alloc * sizeof(T));
      m_node = node;
    }
  }

  size_type count_by_alloc() const
  { return m_size_alloc; }

  void merge(free_list& other)
  {
    if (other.m_size_alloc < m_size_alloc) {
      throw std::underflow_error("free_list::merge");
    }

    if (m_node) {
      Node * node = m_node;
      while (node->next) {
        node = node->next;
      }
      node->next = other.m_node;
    }
    else {
      m_node = other.m_node;
    }

    other.m_node = 0;
  }

  bool operator==(const free_list& rhs) const
  { return m_size_alloc == rhs.m_size_alloc && m_allocator == rhs.m_allocator; }

  bool operator!=(const free_list& rhs) const
  { return !operator==(rhs); }

private:
  Node * m_node;
  size_type m_size_alloc;
  allocator_type m_allocator;
};

}

#endif
