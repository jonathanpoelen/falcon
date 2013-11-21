#ifndef FALCON_MPL_DETAIL_FWD_HPP
#define FALCON_MPL_DETAIL_FWD_HPP

namespace falcon {
namespace mpl {
namespace detail {

struct mpl_apply_def
{ using __mpl_def = mpl_apply_def; };

struct mpl_container_def
{ using __mpl_container = mpl_container_def; };

template<typename T, typename Integral = typename T::__mpl_def>
constexpr bool is_mpl_def(int, Integral = mpl_apply_def())
{ return 1; }

template<typename T>
constexpr bool is_mpl_def(unsigned)
{ return 0; }

template<typename T, typename Integral = typename T::__mpl_container>
constexpr bool is_mpl_sequence(int, Integral = mpl_container_def())
{ return 1; }

template<typename T>
constexpr bool is_mpl_sequence(unsigned)
{ return 0; }

template<typename Seq, bool = is_mpl_sequence<Seq>(1)>
class sequence_handler;

template<typename Seq>
struct sequence_handler<Seq, true>
{ using type = typename Seq::type; };

template<typename Seq>
using sequence_t = typename sequence_handler<Seq>::type;

template<typename...>
struct seq;

class na;

}

namespace aux {

template<typename Seq>
class size;

template<typename Seq>
class empty;

template <typename Seq>
class begin;

template <typename Seq>
class end;

template<typename Seq>
class front;

template<typename Seq>
class back;

template<typename Seq, typename Pos, typename Default = detail::na>
class at;

template<typename Seq, typename Pos, typename T>
class insert;

template<typename Seq, typename Pos, typename Range>
class insert_range;

template<typename Seq, typename Pos, typename Last>
class erase;

template<typename Seq>
class clear;

template<typename Seq, typename T>
class push_back;

template<typename Seq, typename T>
class push_front;

template<typename Seq>
class pop_back;

template<typename Seq>
class pop_front;

template<typename Seq, typename Key>
class count;

template<typename Seq, typename Key>
class order;

template<typename Seq, typename Key>
class has_key;

template<typename Seq, typename T>
class key_type;

template<typename Seq, typename T>
class value_type;

template<typename Seq, typename Key>
class erase_key;

}
}
}

#endif
