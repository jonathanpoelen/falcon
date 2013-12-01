#ifndef FALCON_MPL_BEGIN_END_FWD_HPP
#define FALCON_MPL_BEGIN_END_FWD_HPP

namespace falcon {
namespace mpl {

template< typename Tag > struct begin_impl;
template< typename Tag > struct end_impl;

template< typename Sequence > struct begin;
template< typename Sequence > struct end;

}
}

#endif
