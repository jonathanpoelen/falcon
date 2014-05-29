#ifndef FALCON_ITERATOR_BIT_ITERATOR_HPP
#define FALCON_ITERATOR_BIT_ITERATOR_HPP

#include <falcon/iterator/iterator_handler.hpp>
#include <falcon/bit/size.hpp>
#include <falcon/bit/bit_reference.hpp>
#include <falcon/type_traits/use.hpp>
#include <falcon/type_traits/integral_constant.hpp>
#include <falcon/type_traits/default_or_type.hpp>

namespace falcon {
namespace iterator {

namespace _aux {
  template <
    class Iterator
  , class T = typename std::iterator_traits<Iterator>::pointer>
  struct bit_iterator_is_const
  : false_type
  {};

  template <class Iterator, class T>
  struct bit_iterator_is_const<Iterator, const T *>
  : true_type
  {};

  template <class Iterator>
  struct bit_iterator_is_const<Iterator, void>
  : true_type
  {};
}


template<class Iterator, bool IsConst = _aux::bit_iterator_is_const<Iterator>::value>
class bit_iterator;

namespace detail
{
  template <class Iterator, bool IsConst>
  struct bit_iterator_base
  {
    struct bit_reference_type {
      typedef falcon::bit_reference<
        class std::iterator_traits<Iterator>::value_type
      > type;
    };

    typedef typename iterator_handler_types<
      bit_iterator<Iterator, IsConst>
    , Iterator
    , use_default
    , bool
    , use_default
    , void
    , class eval_if<IsConst, use<bool>, bit_reference_type>::type
    >::type type;
  };
}

template<class Iterator, bool IsConst>
class bit_iterator
: public detail::bit_iterator_base<Iterator, IsConst>::type
{
  typedef typename bit_iterator::handler_type inherit_type;

  friend class iterator_core_access;

  unsigned offset_;

public:
  typedef typename inherit_type::iterator_type iterator_type;
  typedef typename inherit_type::reference reference;
  typedef typename inherit_type::difference_type difference_type;


  bit_iterator()
  : inherit_type()
  , offset_(0)
  {}

  bit_iterator(iterator_type x, unsigned offset__)
  : inherit_type(x)
  , offset_(offset__)
  {}

  unsigned offset() const
  { return offset_; }

private:
  typedef typename std::iterator_traits<Iterator>::value_type mask_t;
  static const unsigned s_word_bit = bit::size<mask_t>::value;

  mask_t mask() const
  { return static_cast<mask_t>(1ul << offset_); }

  reference dereference(false_type)
  { return reference(&*this->base_reference(), mask()); }

  reference dereference(false_type) const
  { return reference(&*this->base_reference(), mask()); }

  reference dereference(true_type) const
  { return !!(*this->base_reference() & mask()); }

  reference dereference()
  { return dereference(falcon::integral_constant<bool, IsConst>()); }

  reference dereference() const
  { return dereference(falcon::integral_constant<bool, IsConst>()); }

  void increment()
  {
    if (offset_++ == s_word_bit - 1u)
    {
      offset_ = 0;
      ++this->base_reference();
    }
  }

  void decrement()
  {
    if (offset_-- == 0)
    {
      offset_ = s_word_bit - 1u;
      --this->base_reference();
    }
  }

  void advance(difference_type i)
  {
    difference_type n = i + offset_;
    this->base_reference() += n / int(s_word_bit);
    n = n % int(s_word_bit);
    if (n < 0)
    {
      n += int(s_word_bit);
      --this->base_reference();
    }
    offset_ = static_cast<unsigned>(n);
  }

  difference_type difference(const bit_iterator& x) const
  {
    return difference_type(
      (this->base_reference() - this->base_reference(x))
      * s_word_bit + offset_
      - x.offset_
    );
  }

  bool equal(const bit_iterator& other) const
  { return offset_ == other.offset_
  && this->base_reference() == other.base_reference(); }

  bool less(const bit_iterator& other) const
  { return this->base_reference() < other.base_reference()
  || (offset_ < other.offset_
  && this->base_reference() == other.base_reference()); }
};

#if __cplusplus >= 201103L
template <class Iterator>
using const_bit_iterator = bit_iterator<Iterator, true>;
#endif


template <class Iterator>
bit_iterator<Iterator> make_bit_iterator(Iterator x, unsigned offset)
{ return bit_iterator<Iterator>(x, offset); }

template <class Iterator>
bit_iterator<Iterator, true> make_const_bit_iterator(Iterator x, unsigned offset)
{ return bit_iterator<Iterator, true>(x, offset); }

}}

#endif
