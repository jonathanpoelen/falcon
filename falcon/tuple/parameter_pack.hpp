#ifndef _FALCONTUPLE_PARAMETER_PACK_HPP
#define _FALCONTUPLE_PARAMETER_PACK_HPP

#include <falcon/parameter/pack_element.hpp>
#include <falcon/type_traits/build_class.hpp>

#include <tuple>

namespace falcon {

template<class T, class Indexes>
class tuple_to_parameter_pack_with_parameter_index;

namespace aux_ {
  template<class Pack, class T, std::size_t... Indexes>
  struct tuple_to_parameter_pack_with_parameter_index
  { typedef Pack type; };

  template<
    class T, class... Elements, std::size_t Index, std::size_t... Indexes>
  struct tuple_to_parameter_pack_with_parameter_index
    <parameter_pack<Elements...>, T, Index, Indexes...>
  {
    typedef typename tuple_to_parameter_pack_with_parameter_index<
      parameter_pack<
        Elements...,
        typename std::tuple_element<Index, T>::type
      >, T, Indexes...
    >::type type;
  };
}

template<class T, std::size_t... Indexes>
struct tuple_to_parameter_pack_with_parameter_index<T, parameter_index<Indexes...>>
{
	typedef typename aux_::tuple_to_parameter_pack_with_parameter_index<
		parameter_pack<>, T, Indexes...
	>::type type;
};


template<std::size_t Start, std::size_t Stop, class T, std::size_t Step = 1>
class build_range_tuple_to_parameter_pack
{
	static const std::size_t size_ = std::tuple_size<T>::value;
	static const std::size_t stop_ = (Stop > size_ ? size_ : Stop);
	static const std::size_t start_ = (Start < stop_ ? Start : stop_);
	typedef typename build_range_parameter_index<start_, stop_, Step>::type indexes_;
public:
	typedef typename tuple_to_parameter_pack_with_parameter_index<T, indexes_>::type type;
};

template<class T>
struct tuple_to_parameter_pack
{
	typedef typename tuple_to_parameter_pack_with_parameter_index<
		T,
		typename build_parameter_index<std::tuple_size<T>::value>::type
	>::type type;
};

template<class Pack>
struct parameter_pack_to_tuple
{ typedef typename build_class<std::tuple, Pack>::type type; };

template <class Tuple, class Indexes>
struct tuple_pack_element
{
	typedef typename parameter_pack_to_tuple<
		typename tuple_to_parameter_pack_with_parameter_index<Tuple, Indexes>::type
	>::type type;
};

}

#endif
