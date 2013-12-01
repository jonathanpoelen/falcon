#ifndef FALCON_MPL_ITERATOR_CATEGORY_HPP
#define FALCON_MPL_ITERATOR_CATEGORY_HPP

namespace falcon {
namespace mpl {

template<typename Iterator>
struct iterator_category
{ using type = typename Iterator::category; };

template<typename Iterator>
using iterator_category_t = typename iterator_category<Iterator>::type;

}
}

#endif
