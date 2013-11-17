#ifndef FALCON_TPL_SEQUENCE_HPP
#define FALCON_TPL_SEQUENCE_HPP

namespace falcon {
namespace tpl {
#if __cplusplus >= 201103L
	template<template<class...> class... Temps>
	class sequence;
#else
	template<typename>
	class sequence;

	template<template<class> class Temp>
	class __sequence1;

	template<template<class> class Temp>
	class sequence<__sequence1<Temp> >
	{};

	template<template<class, class> class Temp>
	class __sequence2;

	template<template<class, class> class Temp>
	class sequence<__sequence2<Temp> >
	{};

	template<template<class, class, class> class Temp>
	class __sequence3;

	template<template<class, class, class> class Temp>
	class sequence<__sequence3<Temp> >
	{};
#endif
}
}

#endif
