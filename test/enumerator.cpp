#include <falcon/enum/enumerator.hpp>
#include "test/enumerator.hpp"

FALCON_PP_ENUMERATOR(my_enum_class1, default, (A),(B, "b"),C,D);
// FALCON_PP_ENUMERATOR(my_enum_class2, linear(5), (A),(B, "b"),C,D);
// FALCON_PP_ENUMERATOR(my_enum_class3, lbit(0), (A),(B, "b"),C,D);
// FALCON_PP_ENUMERATOR(my_enum_class4, lbit(2048), (A),(B, "b"),C,D);
// FALCON_PP_ENUMERATOR(my_enum_class5, rbit(1024), (A),(B, "b"),C,D);
// FALCON_PP_ENUMERATOR(my_enum_class6, rbit(2048), (A),(B, "b"),C,D);
// FALCON_PP_ENUMERATOR(my_enum_class7, step(2), (A),(B, "b"),C,D);
// FALCON_PP_ENUMERATOR(my_enum_class8, linear_step(5, 2), (A),(B, "b"),C,D);
//
// /**
//  * Exemple pour construire un enum_class avec un type_char autre que char.
//  * Ici wchar_t car preceder de L
//  * @{
//  */
// //triple # pour coller L avec la chaîne de caractère. L#N = L "A". L###N = L"A".
// #define P(N) (N, L###N)
// FALCON_PP_ENUMERATOR(my_enum_class9, default, P(A), (B, "b"));
// #undef P
// //@}
//
// ///NOTE test avec une seule valeur
// //@{
// FALCON_PP_ENUMERATOR(my_enum_class10, default, A);
// FALCON_PP_ENUMERATOR(my_enum_class11, default, (A));
// FALCON_PP_ENUMERATOR(my_enum_class12, default, (A, "a"));
// //@}
//
// ///NOTE changement automatique de la config pour la rentre plus optimiser
// //@{
// FALCON_PP_ENUMERATOR(my_enum_class13, linear_step(0, 2), A,B,C); //step(2)
// FALCON_PP_ENUMERATOR(my_enum_class14, linear_step(5, 1), A,B,C); //linear(5)
// FALCON_PP_ENUMERATOR(my_enum_class15, linear_step(0, 1), A,B,C); //default
// FALCON_PP_ENUMERATOR(my_enum_class16, linear(0), A,B,C); //default
// FALCON_PP_ENUMERATOR(my_enum_class17, step(1), A,B,C); //default
// //@}
//
// ///NOTE ne compile pas et c'est normal car une valeur est donné à A
// //FALCON_PP_ENUMERATOR(my_enum_classX, default, (A=1, "a"));
// ///NOTE ne compile pas car pas de valeur d'enum
// //FALCON_PP_ENUMERATOR(my_enum_classX, default);

typedef my_enum_class1 my_enum_class;

#include <iostream>
#include <sstream>
#include <boost/static_assert.hpp>
#include "test/test.hpp"

template<typename _Enum, typename _Ostream, typename _Ostream2>
static void EnumClassTestImpl(_Ostream& cout, _Ostream2& cerr)
{
	typedef typename _Enum::strings string_container;
	typedef typename string_container::iterator string_iterator;

	typedef typename _Enum::enumeration enumeration_container;
	typedef typename enumeration_container::iterator enumeration_iterator;

	string_container strings;
	string_iterator it = strings.begin();
	string_iterator last = strings.end();
	enumeration_iterator eit = enumeration_container::begin();
	enumeration_iterator elast = enumeration_container::end();

	for (; it != last && eit != elast; ++it, ++eit)
		cout << '[' << strings[*eit] << ']' << *it << '=' << *eit << ',';
	if (it != last || eit != elast)
	{
		enumeration_iterator __eit = enumeration_container::begin();
		cerr << "iterator error: first=" << *__eit
		<< ", next=" << *++__eit
		<< ", eit=" << *eit
		<< ", elast=" << *elast << '\n';
		throw std::runtime_error(typeid(_Enum).name());
	}
}

template<typename _CharT>
struct __get_err
{
	operator std::basic_ostream<_CharT>& ()
	{ return std::wcerr; }
};

template<>
struct __get_err<char>
{
	operator std::basic_ostream<char>& ()
	{ return std::cerr; }
};

template<typename _CharT>
std::basic_ostream<_CharT>& get_err()
{
	return __get_err<_CharT>();
}

template<typename _Enum, typename _CharT>
static void EnumClassTest(const _CharT * scmp)
{
	BOOST_STATIC_ASSERT((std::is_same<_CharT, typename _Enum::strings::char_type>::value));
	std::basic_stringstream<_CharT> oss;
	EnumClassTestImpl<_Enum>(oss, get_err<_CharT>());
	if (oss.str() != scmp){
		get_err<_CharT>() << oss.str() << " != " << scmp << '\n';
		throw 0;
	}
}

void enumerator_test()
{
	{
		//std::cout.exceptions(std::ios::badbit | std::ios::failbit);
		//std::wcout.exceptions(std::ios::badbit | std::ios::failbit);

		EnumClassTest<my_enum_class1>("[A]A=0,[b]b=1,[C]C=2,[D]D=3,");
// 		EnumClassTest<my_enum_class2>("[A]A=5,[b]b=6,[C]C=7,[D]D=8,");
// 		EnumClassTest<my_enum_class3>("[A]A=0,[b]b=1,[C]C=2,[D]D=4,");
// 		EnumClassTest<my_enum_class4>("[A]A=2048,[b]b=4096,[C]C=8192,[D]D=16384,");
// 		EnumClassTest<my_enum_class5>("[A]A=1024,[b]b=512,[C]C=256,[D]D=128,");
// 		EnumClassTest<my_enum_class6>("[A]A=2048,[b]b=1024,[C]C=512,[D]D=256,");
// 		EnumClassTest<my_enum_class7>("[A]A=0,[b]b=2,[C]C=4,[D]D=6,");
// 		EnumClassTest<my_enum_class8>("[A]A=5,[b]b=7,[C]C=9,[D]D=11,");
// 		EnumClassTest<my_enum_class9>(L"[A]A=0,[b]b=1,");
// 		EnumClassTest<my_enum_class10>("[A]A=0,");
// 		EnumClassTest<my_enum_class11>("[A]A=0,");
// 		EnumClassTest<my_enum_class12>("[a]a=0,");
// 		EnumClassTest<my_enum_class13>("[A]A=0,[B]B=2,[C]C=4,");
// 		EnumClassTest<my_enum_class14>("[A]A=5,[B]B=6,[C]C=7,");
// 		EnumClassTest<my_enum_class15>("[A]A=0,[B]B=1,[C]C=2,");
// 		EnumClassTest<my_enum_class16>("[A]A=0,[B]B=1,[C]C=2,");
// 		EnumClassTest<my_enum_class17>("[A]A=0,[B]B=1,[C]C=2,");
	}
// 	{
// 		typedef my_enum_class::strings::iterator iterator;
// 		my_enum_class::strings w;
// 		std::string s;
// 		for (iterator it = w.begin(), last = w.end(); it != last; ++it)
// 			(s += *it) += ',';
// 		CHECK_EQUAL_VALUE(s, "A,b,C,D,");
// 	}
// #if __cplusplus >= 201103L
// 	{
// 		std::string s;
// 		for (auto str: my_enum_class::strings())
// 			(s += str) += ',';
// 		CHECK_EQUAL_VALUE(s, "A,b,C,D,");
// 	}
// #endif
// 	{
// 		typedef my_enum_class::enumeration::iterator iterator;
// 		std::string s;
// 		for (iterator
// 				it = iterator(my_enum_class::A),
// 				last = iterator(falcon::enum_plus<>()(my_enum_class::D, 1));
// 			it != last;
// 			++it)
// 			(s += char(*it + '0')) += ',';
// 		CHECK_EQUAL_VALUE(s, "0,1,2,3,");
// 	}
}

FALCON_GROUP_TEST_TO_MAIN(enumerator_test)
