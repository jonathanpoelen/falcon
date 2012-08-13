#ifndef _FALCON_TYPE_TRAITS_NORMALIZE_INDEX_HPP
#define _FALCON_TYPE_TRAITS_NORMALIZE_INDEX_HPP

namespace falcon {
///\brief if @a i is negative the normalize at the last position. First index is 0.
template<int __i, unsigned int Nm>
class normalize_index
{
#ifdef __GXX_EXPERIMENTAL_CXX0X__
	static_assert(Nm != 0, "size is 0");
#endif

	template<int I, bool is_negate, bool in_range>
	struct impl
	{
		static const unsigned int value = I;
	};

	template<int I, bool in_range>
	struct impl<I, true, in_range>
	{
		static const unsigned int value = impl<Nm + I, (int(Nm) + I < 0), (unsigned(Nm + I) < Nm)>::value;
	};

	template<int I>
	struct impl<I, false, false>
	{
		static const unsigned int value = impl<I - Nm, (I - int(Nm) < 0), (unsigned(I - Nm) < Nm)>::value;
	};

public:
	static const unsigned int value = impl<__i, (__i < 0), (unsigned(__i) < Nm)>::value;
};
}

#endif
