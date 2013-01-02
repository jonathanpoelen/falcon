#ifndef FALCON_PARAMETER_IS_PARAMETER_INDEX_TAG_HPP
#define FALCON_PARAMETER_IS_PARAMETER_INDEX_TAG_HPP

#include <falcon/parameter/keep_parameter_index.hpp>
#include <falcon/type_traits/integral_constant.hpp>

namespace falcon {

template<typename _Tag>
struct is_parameter_index_tag
: false_type
{};

template<std::size_t _Keep>
struct is_parameter_index_tag<first_parameter_index_tag<_Keep>>
: true_type
{};

template<std::size_t _Keep>
struct is_parameter_index_tag<last_parameter_index_tag<_Keep>>
: true_type
{};

template<std::size_t _Start, std::size_t _Len>
struct is_parameter_index_tag<range_parameter_index_tag<_Start, _Len>>
: true_type
{};

template<std::size_t _Start, std::size_t _Len>
struct is_parameter_index_tag<ignore_parameter_index_tag<_Start, _Len>>
: true_type
{};

template<std::size_t _Start, std::size_t _Len>
struct is_parameter_index_tag<reverse_parameter_index_tag<_Start, _Len>>
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

template<typename _Indexes>
struct is_parameter_index_tag<specified_parameter_index_tag<_Indexes>>
: true_type
{};

}

#endif