#ifndef FALCON_PARAMETER_IS_PARAMETER_INDEX_TAG_HPP
#define FALCON_PARAMETER_IS_PARAMETER_INDEX_TAG_HPP

#include <falcon/parameter/keep_parameter_index.hpp>
#include <falcon/type_traits/integral_constant.hpp>

namespace falcon {

template<typename T>
struct is_parameter_index_tag
: false_type
{};

template<std::size_t Keep>
struct is_parameter_index_tag<first_parameter_index_tag<Keep>>
: true_type
{};

template<std::size_t Keep>
struct is_parameter_index_tag<last_parameter_index_tag<Keep>>
: true_type
{};

template<std::size_t Start, std::size_t Len>
struct is_parameter_index_tag<range_parameter_index_tag<Start, Len>>
: true_type
{};

template<std::size_t Start, std::size_t Len>
struct is_parameter_index_tag<ignore_parameter_index_tag<Start, Len>>
: true_type
{};

template<std::size_t Start, std::size_t Len>
struct is_parameter_index_tag<reverse_parameter_index_tag<Start, Len>>
: true_type
{};

template<>
struct is_parameter_index_tag<full_parameter_index_tag>
: true_type
{};

template<>
struct is_parameter_index_tag<empty_parameter_index_tag>
: true_type
{};

template<typename Indexes>
struct is_parameter_index_tag<specified_parameter_index_tag<Indexes>>
: true_type
{};


template<typename T>
struct is_parameter_index_or_tag
: is_parameter_index_tag<T>
{};

template<std::size_t... Indexes>
struct is_parameter_index_or_tag<parameter_index<Indexes...>>
: true_type
{};

namespace parameter {
  template<typename Tag>
  using is_index_tag = is_parameter_index_tag<Tag>;

  template<typename Indexes>
  using is_index_tag_or_tag = is_parameter_index_or_tag<Indexes>;
}

}

#endif
