#ifndef _FALCON_ENDIAN_HPP
#define _FALCON_ENDIAN_HPP

namespace falcon {

	inline bool __little_endian()
	{
		short tester = 0x0001;
   return *reinterpret_cast<char*>(&tester) != 0;
	}

	inline bool little_endian()
	{
		static bool is_little_endian = __little_endian();
		return is_little_endian;
	}

	inline bool big_endian()
	{ return !little_endian(); }

	///TODO to_big_endian to_little_endian

}

#endif
