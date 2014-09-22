#ifndef FALCON_ITERATOR_CONST_ITERATOR_NOT_CONFLICT_HPP
#define FALCON_ITERATOR_CONST_ITERATOR_NOT_CONFLICT_HPP

namespace falcon { namespace iterator {

namespace aux_ {
  template<
    class C,
    class = typename C::iterator,
    class = typename C::const_iterator>
  struct const_iterator_not_conflict_impl
  { typedef typename C::const_iterator type; };

  template<class C, class I>
  class const_iterator_not_conflict_impl<C, I, I>;
}

template<class C>
struct const_iterator_not_conflict
: aux_::const_iterator_not_conflict_impl<C>
{};

#if __cplusplus >= 201103L
template<class C>
using const_iterator_not_conflict_t
  = typename const_iterator_not_conflict<C>::type;
#endif

} }

#endif
