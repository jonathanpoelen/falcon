#ifndef FALCON_FN_OPERATORS_HPP
#define FALCON_FN_OPERATORS_HPP

#include <falcon/functional/operators.hpp>
#include <falcon/type_traits/static_const.hpp>

namespace falcon {
namespace fn {

using plus_fn = falcon::plus<>;
using minus_fn = falcon::minus<>;
using multiplies_fn = falcon::multiplies<>;
using divides_fn = falcon::divides<>;
using modulus_fn = falcon::modulus<>;
using plus_equal_fn = falcon::plus_equal<>;
using minus_equal_fn = falcon::minus_equal<>;
using multiplies_equal_fn = falcon::multiplies_equal<>;
using divides_equal_fn = falcon::divides_equal<>;
using modulus_equal_fn = falcon::modulus_equal<>;
using increment_fn = falcon::increment<>;
using decrement_fn = falcon::decrement<>;
using post_increment_fn = falcon::post_increment<>;
using post_decrement_fn = falcon::post_decrement<>;
using increment2_fn = falcon::increment2<>;
using decrement2_fn = falcon::decrement2<>;
using increment3_fn = falcon::increment3<>;
using decrement3_fn = falcon::decrement3<>;
using negate_fn = falcon::negate<>;
using unary_plus_fn = falcon::unary_plus<>;
using equal_to_fn = falcon::equal_to<>;
using not_equal_to_fn = falcon::not_equal_to<>;
using greater_fn = falcon::greater<>;
using less_fn = falcon::less<>;
using greater_equal_fn = falcon::greater_equal<>;
using less_equal_fn = falcon::less_equal<>;
using equivalent_fn = falcon::equivalent<>;
using equivalent2_fn = falcon::equivalent2<>;
using logical_and_fn = falcon::logical_and<>;
using logical_or_fn = falcon::logical_or<>;
using logical_not_fn = falcon::logical_not<>;
using bit_and_fn = falcon::bit_and<>;
using bit_or_fn = falcon::bit_or<>;
using bit_xor_fn = falcon::bit_xor<>;
using bit_and_equal_fn = falcon::bit_and_equal<>;
using bit_or_equal_fn = falcon::bit_or_equal<>;
using bit_xor_equal_fn = falcon::bit_xor_equal<>;
using left_shift_fn = falcon::left_shift<>;
using right_shift_fn = falcon::right_shift<>;
using left_shift_equal_fn = falcon::left_shift_equal<>;
using right_shift_equal_fn = falcon::right_shift_equal<>;
using bit_not_fn = falcon::bit_not<>;
using dereference_fn = falcon::dereference<>;
using address_fn = falcon::address<>;
using arrow_fn = falcon::arrow<>;
using index_fn = falcon::index<>;
using index2_fn = falcon::index2<>;
using comma_fn = falcon::comma<>;
using pointer_to_member_fn = falcon::pointer_to_member<>;

namespace {
constexpr auto const & plus = static_const<plus_fn>::value;
constexpr auto const & minus = static_const<minus_fn>::value;
constexpr auto const & multiplies = static_const<multiplies_fn>::value;
constexpr auto const & divides = static_const<divides_fn>::value;
constexpr auto const & modulus = static_const<modulus_fn>::value;
constexpr auto const & plus_equal = static_const<plus_equal_fn>::value;
constexpr auto const & minus_equal = static_const<minus_equal_fn>::value;
constexpr auto const & multiplies_equal
= static_const<multiplies_equal_fn>::value;
constexpr auto const & divides_equal = static_const<divides_equal_fn>::value;
constexpr auto const & modulus_equal = static_const<modulus_equal_fn>::value;
constexpr auto const & increment = static_const<increment_fn>::value;
constexpr auto const & decrement = static_const<decrement_fn>::value;
constexpr auto const & post_increment = static_const<post_increment_fn>::value;
constexpr auto const & post_decrement = static_const<post_decrement_fn>::value;
constexpr auto const & increment2 = static_const<increment2_fn>::value;
constexpr auto const & decrement2 = static_const<decrement2_fn>::value;
constexpr auto const & increment3 = static_const<increment3_fn>::value;
constexpr auto const & decrement3 = static_const<decrement3_fn>::value;
constexpr auto const & negate = static_const<negate_fn>::value;
constexpr auto const & unary_plus = static_const<unary_plus_fn>::value;
constexpr auto const & equal_to = static_const<equal_to_fn>::value;
constexpr auto const & not_equal_to = static_const<not_equal_to_fn>::value;
constexpr auto const & greater = static_const<greater_fn>::value;
constexpr auto const & less = static_const<less_fn>::value;
constexpr auto const & greater_equal = static_const<greater_equal_fn>::value;
constexpr auto const & less_equal = static_const<less_equal_fn>::value;
constexpr auto const & equivalent = static_const<equivalent_fn>::value;
constexpr auto const & equivalent2 = static_const<equivalent2_fn>::value;
constexpr auto const & logical_and = static_const<logical_and_fn>::value;
constexpr auto const & logical_or = static_const<logical_or_fn>::value;
constexpr auto const & logical_not = static_const<logical_not_fn>::value;
constexpr auto const & bit_and = static_const<bit_and_fn>::value;
constexpr auto const & bit_or = static_const<bit_or_fn>::value;
constexpr auto const & bit_xor = static_const<bit_xor_fn>::value;
constexpr auto const & bit_and_equal = static_const<bit_and_equal_fn>::value;
constexpr auto const & bit_or_equal = static_const<bit_or_equal_fn>::value;
constexpr auto const & bit_xor_equal = static_const<bit_xor_equal_fn>::value;
constexpr auto const & left_shift = static_const<left_shift_fn>::value;
constexpr auto const & right_shift = static_const<right_shift_fn>::value;
constexpr auto const & left_shift_equal = static_const<left_shift_equal_fn>::value;
constexpr auto const & right_shift_equal = static_const<right_shift_equal_fn>::value;
constexpr auto const & bit_not = static_const<bit_not_fn>::value;
constexpr auto const & dereference = static_const<dereference_fn>::value;
constexpr auto const & address = static_const<address_fn>::value;
constexpr auto const & arrow = static_const<arrow_fn>::value;
constexpr auto const & index = static_const<index_fn>::value;
constexpr auto const & index2 = static_const<index2_fn>::value;
constexpr auto const & comma = static_const<comma_fn>::value;
constexpr auto const & pointer_to_member = static_const<pointer_to_member_fn>::value;
}

}
}

#endif
