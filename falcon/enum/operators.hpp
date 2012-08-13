#ifndef _FALCON_ENUM_OPERATORS_HPP
#define _FALCON_ENUM_OPERATORS_HPP

#include <falcon/c++/constexpr.hpp>

namespace falcon {

	template<typename _Enum = void>
	struct enum_increment
	{
		typedef _Enum value_type;

		_Enum& operator()(_Enum& e) const
		{
			e = static_cast<_Enum>(e + 1);
			return e;
		}
	};

	template<>
	struct enum_increment<void>
	{
		template<typename _Enum>
		_Enum& operator()(_Enum& e) const
		{
			e = static_cast<_Enum>(e + 1);
			return e;
		}
	};

	template<typename _Enum = void>
	struct enum_decrement
	{
		typedef _Enum value_type;

		_Enum& operator()(_Enum& e) const
		{
			e = static_cast<_Enum>(e - 1);
			return e;
		}
	};

	template<>
	struct enum_decrement<void>
	{
		template<typename _Enum>
		_Enum& operator()(_Enum& e) const
		{
			e = static_cast<_Enum>(e - 1);
			return e;
		}
	};

	template<typename _Enum = void>
	struct enum_plus
	{
		typedef _Enum value_type;

		CPP_CONSTEXPR _Enum operator()(_Enum e, int n) const
		{
			return static_cast<_Enum>(e + n);
		}
	};

	template<>
	struct enum_plus<void>
	{
		template<typename _Enum>
		CPP_CONSTEXPR _Enum operator()(_Enum e, int n) const
		{
			return static_cast<_Enum>(e + n);
		}
	};

	template<typename _Enum = void>
	struct enum_minus
	{
		typedef _Enum value_type;

		CPP_CONSTEXPR _Enum operator()(_Enum e, int n) const
		{
			return static_cast<_Enum>(e - n);
		}
	};

	template<>
	struct enum_minus<void>
	{
		template<typename _Enum>
		CPP_CONSTEXPR _Enum operator()(_Enum e, int n) const
		{
			return static_cast<_Enum>(e - n);
		}
	};

	template<typename _Enum = void>
	struct enum_left_shift
	{
		typedef _Enum value_type;

		CPP_CONSTEXPR _Enum operator()(_Enum e, int n) const
		{
			return static_cast<_Enum>(e << n);
		}
	};

	template<>
	struct enum_left_shift<void>
	{
		template<typename _Enum>
		CPP_CONSTEXPR _Enum operator()(_Enum e, int n) const
		{
			return static_cast<_Enum>(e << n);
		}
	};

	template<typename _Enum = void>
	struct enum_right_shift
	{
		typedef _Enum value_type;

		CPP_CONSTEXPR _Enum operator()(_Enum e, int n) const
		{
			return static_cast<_Enum>(e >> n);
		}
	};

	template<>
	struct enum_right_shift<void>
	{
		template<typename _Enum>
		CPP_CONSTEXPR _Enum operator()(_Enum e, int n) const
		{
			return static_cast<_Enum>(e >> n);
		}
	};

}

#endif