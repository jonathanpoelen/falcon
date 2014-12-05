#ifndef FALCON_FN_OPERATORS_OPERATORS_HPP
#define FALCON_FN_OPERATORS_OPERATORS_HPP

#include <falcon/functional/operators.hpp>
#include <falcon/type_traits/static_const.hpp>

namespace falcon {
namespace fn {

using add_fn = falcon::plus<>;
using sub_fn = falcon::minus<>;
using mul_fn = falcon::multiplies<>;
using div_fn = falcon::divides<>;
using mod_fn = falcon::modulus<>;
using add_eq_fn = falcon::plus_equal<>;
using sub_eq_fn = falcon::minus_equal<>;
using mul_eq_fn = falcon::multiplies_equal<>;
using div_eq_fn = falcon::divides_equal<>;
using mod_eq_fn = falcon::modulus_equal<>;
using inc_fn = falcon::increment<>;
using dec_fn = falcon::decrement<>;
using post_inc_fn = falcon::post_increment<>;
using post_dec_fn = falcon::post_decrement<>;
using inc2_fn = falcon::increment2<>;
using dec2_fn = falcon::decrement2<>;
using inc3_fn = falcon::increment3<>;
using dec3_fn = falcon::decrement3<>;
using neg_fn = falcon::negate<>;
using unadd_fn = falcon::unary_plus<>;
using eq_fn = falcon::equal_to<>;
using neq_fn = falcon::not_equal_to<>;
using gt_fn = falcon::greater<>;
using lt_fn = falcon::less<>;
using ge_fn = falcon::greater_equal<>;
using le_fn = falcon::less_equal<>;
using equiv_fn = falcon::equivalent<>;
using equiv2_fn = falcon::equivalent2<>;
using and_fn = falcon::logical_and<>;
using or_fn = falcon::logical_or<>;
using not_fn = falcon::logical_not<>;
using bit_and_fn = falcon::bit_and<>;
using bit_or_fn = falcon::bit_or<>;
using bit_xor_fn = falcon::bit_xor<>;
using bit_and_eq_fn = falcon::bit_and_equal<>;
using bit_or_eq_fn = falcon::bit_or_equal<>;
using bit_xor_eq_fn = falcon::bit_xor_equal<>;
using and_eq_fn = falcon::bit_and_equal<>;
using or_eq_fn = falcon::bit_or_equal<>;
using xor_eq_fn = falcon::bit_xor_equal<>;
using left_shift_fn = falcon::left_shift<>;
using right_shift_fn = falcon::right_shift<>;
using left_shift_eq_fn = falcon::left_shift_equal<>;
using right_shift_eq_fn = falcon::right_shift_equal<>;
using bit_not_fn = falcon::bit_not<>;
using deref_fn = falcon::dereference<>;
using addr_fn = falcon::address<>;
using arrow_fn = falcon::arrow<>;
using idx_fn = falcon::index<>;
using idx2_fn = falcon::index2<>;
using comma_fn = falcon::comma<>;
using ptr_to_mem_fn = falcon::pointer_to_member<>;

#define FALCON_MAKE_NOT_BINARY_OP(name, op)\
struct name##_fn {\
 \
    constexpr name##_fn () noexcept {}\
\
    template<class T, class U>\
    constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(\
      operator()(T&& x, U&& y) const\
    , !(std::forward<T>(x) op std::forward<U>(y)))\
\
    typedef ::falcon::aux_::is_transparent_t is_transparent;\
}

FALCON_MAKE_NOT_BINARY_OP(ngt, >);
FALCON_MAKE_NOT_BINARY_OP(nlt, <);
FALCON_MAKE_NOT_BINARY_OP(nge, >=);
FALCON_MAKE_NOT_BINARY_OP(nle, <=);

#undef FALCON_MAKE_NOT_BINARY_OP


namespace {
constexpr auto const & add = static_const<add_fn>::value;
constexpr auto const & sub = static_const<sub_fn>::value;
constexpr auto const & mul = static_const<mul_fn>::value;
constexpr auto const & div = static_const<div_fn>::value;
constexpr auto const & mod = static_const<mod_fn>::value;
constexpr auto const & add_eq = static_const<add_eq_fn>::value;
constexpr auto const & sub_eq = static_const<sub_eq_fn>::value;
constexpr auto const & mul_eq = static_const<mul_eq_fn>::value;
constexpr auto const & div_eq = static_const<div_eq_fn>::value;
constexpr auto const & mod_eq = static_const<mod_eq_fn>::value;
constexpr auto const & inc = static_const<inc_fn>::value;
constexpr auto const & dec = static_const<dec_fn>::value;
constexpr auto const & post_inc = static_const<post_inc_fn>::value;
constexpr auto const & post_dec = static_const<post_dec_fn>::value;
constexpr auto const & inc2 = static_const<inc2_fn>::value;
constexpr auto const & dec2 = static_const<dec2_fn>::value;
constexpr auto const & inc3 = static_const<inc3_fn>::value;
constexpr auto const & dec3 = static_const<dec3_fn>::value;
constexpr auto const & neg = static_const<neg_fn>::value;
constexpr auto const & unadd = static_const<unadd_fn>::value;
constexpr auto const & eq = static_const<eq_fn>::value;
constexpr auto const & neq = static_const<neq_fn>::value;
constexpr auto const & gt = static_const<gt_fn>::value;
constexpr auto const & lt = static_const<lt_fn>::value;
constexpr auto const & ge = static_const<ge_fn>::value;
constexpr auto const & le = static_const<le_fn>::value;
constexpr auto const & ngt = static_const<ngt_fn>::value;
constexpr auto const & nlt = static_const<nlt_fn>::value;
constexpr auto const & nge = static_const<nge_fn>::value;
constexpr auto const & nle = static_const<nle_fn>::value;
constexpr auto const & equiv = static_const<equiv_fn>::value;
constexpr auto const & equiv2 = static_const<equiv2_fn>::value;
constexpr auto const & and_ = static_const<and_fn>::value;
constexpr auto const & or_ = static_const<or_fn>::value;
constexpr auto const & not_ = static_const<not_fn>::value;
constexpr auto const & bit_and = static_const<bit_and_fn>::value;
constexpr auto const & bit_or = static_const<bit_or_fn>::value;
constexpr auto const & bit_xor = static_const<bit_xor_fn>::value;
constexpr auto const & bit_and_eq = static_const<bit_and_eq_fn>::value;
constexpr auto const & bit_or_eq = static_const<bit_or_eq_fn>::value;
constexpr auto const & bit_xor_eq = static_const<bit_xor_eq_fn>::value;
constexpr auto const & and_eq_ = static_const<bit_and_eq_fn>::value;
constexpr auto const & or_eq_ = static_const<bit_or_eq_fn>::value;
constexpr auto const & xor_eq_ = static_const<bit_xor_eq_fn>::value;
constexpr auto const & left_shift = static_const<left_shift_fn>::value;
constexpr auto const & right_shift = static_const<right_shift_fn>::value;
constexpr auto const & left_shift_eq = static_const<left_shift_eq_fn>::value;
constexpr auto const & right_shift_eq = static_const<right_shift_eq_fn>::value;
constexpr auto const & bit_not = static_const<bit_not_fn>::value;
constexpr auto const & deref = static_const<deref_fn>::value;
constexpr auto const & addr = static_const<addr_fn>::value;
constexpr auto const & arrow = static_const<arrow_fn>::value;
constexpr auto const & idx = static_const<idx_fn>::value;
constexpr auto const & idx2 = static_const<idx2_fn>::value;
constexpr auto const & comma = static_const<comma_fn>::value;
constexpr auto const & ptr_to_mem = static_const<ptr_to_mem_fn>::value;
}

}
}

#endif
