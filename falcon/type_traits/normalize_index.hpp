#ifndef FALCON_TYPE_TRAITS_NORMALIZE_INDEX_HPP
#define FALCON_TYPE_TRAITS_NORMALIZE_INDEX_HPP

namespace falcon {
///\brief if @a i is negative the normalize at the last position. First index is 0.
template<long __i, unsigned Nm>
class normalize_index
{
#if __cplusplus >= 201103L
	static_assert(Nm != 0, "size is 0");
#endif

	template<long I, bool is_negate, bool in_range>
	struct impl
	{ static const unsigned value = I; };

	template<long I, bool in_range>
	struct impl<I, true, in_range>
	{
		static const unsigned value
      = impl<long(Nm + I), (long(Nm) + I < 0), (unsigned(Nm + I) < Nm)>::value;
	};

	template<long I>
	struct impl<I, false, false>
	{
		static const unsigned value
      = impl<long(I - Nm), (I - long(Nm) < 0), (unsigned(I - Nm) < Nm)>::value;
	};

public:
	static const unsigned value
    = impl<__i, (__i < 0), (unsigned(__i) < Nm)>::value;
};
}

#endif
