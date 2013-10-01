#ifndef FALCON_TUPLE_DETAIL_SEPTUPLE_HPP
#define FALCON_TUPLE_DETAIL_SEPTUPLE_HPP

namespace falcon {

template<typename Tuple, typename Sep>
struct __iotuple
{
  Tuple __t;
  const Sep& __s;
};

template<typename Tuple, typename Sep>
__iotuple<Tuple&, Sep> septuple(Tuple& t, const Sep& sep)
{ return {t,sep}; }

template<typename Tuple, typename Sep>
__iotuple<const Tuple&, Sep> septuple(const Tuple& t, const Sep& sep)
{ return {t,sep}; }

}

#endif
