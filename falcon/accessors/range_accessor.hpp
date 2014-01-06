#ifndef FALCON_ACCESSOR_RANGE_ACCESSOR_HPP
#define FALCON_ACCESSOR_RANGE_ACCESSOR_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/noexcept.hpp>

namespace falcon {

template <class RangeAccessTraits>
struct begin_accessor
{
	typedef RangeAccessTraits traits_type;
	typedef typename traits_type::container_type container_type;
	typedef typename traits_type::iterator iterator;
	typedef iterator result_type;

	CPP_CONSTEXPR result_type operator()(container_type& cont) const
  CPP_NOEXCEPT_OPERATOR2(traits_type::begin(cont))
  { return traits_type::begin(cont); }
};

template <class RangeAccessTraits>
struct end_accessor
{
	typedef RangeAccessTraits traits_type;
	typedef typename traits_type::container_type container_type;
	typedef typename traits_type::iterator iterator;
	typedef iterator result_type;

	CPP_CONSTEXPR result_type operator()(container_type& cont) const
  CPP_NOEXCEPT_OPERATOR2(traits_type::end(cont))
  { return traits_type::end(cont); }
};

}

#endif
