namespace operators {
	template<int _Num, int _Num2>
	inline constexpr ___lambda<__FALCON_NAME_OPERATOR, placeholder<_Num>, placeholder<_Num2> > operator __FALCON_SIGN_OPERATOR(const placeholder<_Num>&, const placeholder<_Num2>&)
	{ return {__FALCON_NAME_OPERATOR()}; }

	template<int _Num, typename _Operation, typename _TL, typename _UL>
	inline constexpr ___lambda<__FALCON_NAME_OPERATOR, ___lambda<_Operation, _TL, _UL>, placeholder<_Num> > operator __FALCON_SIGN_OPERATOR(___lambda<_Operation, _TL, _UL> l, const placeholder<_Num>&)
	{ return {__FALCON_NAME_OPERATOR(), l}; }

	template<int _Num, typename _Operation, typename _TL, typename _UL>
	inline constexpr ___lambda<__FALCON_NAME_OPERATOR, placeholder<_Num>, ___lambda<_Operation, _TL, _UL> > operator __FALCON_SIGN_OPERATOR(const placeholder<_Num>&, ___lambda<_Operation, _TL, _UL> r)
	{ return {__FALCON_NAME_OPERATOR(), r}; }

	template<int _Num, typename _T>
	inline constexpr typename std::enable_if<!is_placeholder<_T>::value && !std::is_bind_expression<_T>::value && std::is_lvalue_reference<_T&>::value, ___lambda<__FALCON_NAME_OPERATOR, __FALCON_CALIFIER_FIRST_PARAM _T&, placeholder<_Num> > >::type operator __FALCON_SIGN_OPERATOR(__FALCON_CALIFIER_FIRST_PARAM _T& a, const placeholder<_Num>&)
	{ return {__FALCON_NAME_OPERATOR(), a}; }

	template<int _Num, typename _T>
	inline constexpr typename std::enable_if<!is_placeholder<_T>::value && !std::is_bind_expression<_T>::value && std::is_rvalue_reference<_T&&>::value, ___lambda<__FALCON_NAME_OPERATOR, _T, placeholder<_Num> > >::type operator __FALCON_SIGN_OPERATOR(_T&& a, const placeholder<_Num>&)
	{ return {__FALCON_NAME_OPERATOR(), a}; }

	template<int _Num, typename _Bind>
	inline constexpr typename std::enable_if<std::is_bind_expression<_Bind>::value && std::is_lvalue_reference<_Bind&>::value, ___lambda<__FALCON_NAME_OPERATOR, __pair<_Bind&, placeholder<_Num> >, binder> >::type operator __FALCON_SIGN_OPERATOR(_Bind& __bind, const placeholder<_Num>&)
	{ return {__FALCON_NAME_OPERATOR(), __bind}; }

	template<int _Num, typename _Bind>
	inline constexpr typename std::enable_if<std::is_bind_expression<_Bind>::value && std::is_rvalue_reference<_Bind&&>::value, ___lambda<__FALCON_NAME_OPERATOR, __pair<_Bind&, placeholder<_Num> >, binder> >::type operator __FALCON_SIGN_OPERATOR(_Bind&& __bind, const placeholder<_Num>&)
	{ return {__FALCON_NAME_OPERATOR(), __bind}; }

	template<int _Num, typename _T>
	inline constexpr typename std::enable_if<!is_placeholder<_T>::value && !std::is_bind_expression<_T>::value && std::is_lvalue_reference<_T&>::value, ___lambda<__FALCON_NAME_OPERATOR, placeholder<_Num>, _T&> >::type operator __FALCON_SIGN_OPERATOR(const placeholder<_Num>&, _T& b)
	{ return {__FALCON_NAME_OPERATOR(), b}; }

	template<int _Num, typename _T>
	inline constexpr typename std::enable_if<!is_placeholder<_T>::value && !std::is_bind_expression<_T>::value && std::is_rvalue_reference<_T&&>::value, ___lambda<__FALCON_NAME_OPERATOR, placeholder<_Num>, _T> >::type operator __FALCON_SIGN_OPERATOR(const placeholder<_Num>&, _T&& b)
	{ return {__FALCON_NAME_OPERATOR(), b}; }

	template<int _Num, typename _Bind>
	inline constexpr typename std::enable_if<std::is_bind_expression<_Bind>::value && std::is_lvalue_reference<_Bind&>::value, ___lambda<__FALCON_NAME_OPERATOR, __pair<placeholder<_Num>, _Bind&>, binder> >::type operator __FALCON_SIGN_OPERATOR(const placeholder<_Num>&, _Bind& __bind)
	{ return {__FALCON_NAME_OPERATOR(), __bind}; }

	template<int _Num, typename _Bind>
	inline constexpr typename std::enable_if<std::is_bind_expression<_Bind>::value && std::is_rvalue_reference<_Bind&&>::value, ___lambda<__FALCON_NAME_OPERATOR, __pair<placeholder<_Num>, _Bind>, binder> >::type operator __FALCON_SIGN_OPERATOR(const placeholder<_Num>&, _Bind&& __bind)
	{ return {__FALCON_NAME_OPERATOR(), __bind}; }

	template<typename _Operation, typename _T, typename _U, typename _Operation2, typename _T2, typename _U2>
	inline constexpr ___lambda<__FALCON_NAME_OPERATOR, ___lambda<_Operation, _T, _U>, ___lambda<_Operation2, _T2, _U2> > operator __FALCON_SIGN_OPERATOR(___lambda<_Operation, _T, _U> left, ___lambda<_Operation2, _T2, _U2> right)
	{ return {__FALCON_NAME_OPERATOR(), left, right}; }

	template<typename _T, typename _Operation, typename _TL, typename _UL>
	inline constexpr typename std::enable_if</* !is_placeholder<_T>::value*/ std::is_lvalue_reference<_T&>::value, ___lambda<__FALCON_NAME_OPERATOR, ___lambda<_Operation, _TL, _UL>, const _T&> >::type operator __FALCON_SIGN_OPERATOR(___lambda<_Operation, _TL, _UL> l, const _T& b)
	{ return {__FALCON_NAME_OPERATOR(), l,b}; }

	template<typename _T, typename _Operation, typename _TL, typename _UL>
	inline constexpr typename std::enable_if</* !is_placeholder<_T>::value*/ std::is_rvalue_reference<_T&&>::value, ___lambda<__FALCON_NAME_OPERATOR, ___lambda<_Operation, _TL, _UL>, _T> >::type operator __FALCON_SIGN_OPERATOR(___lambda<_Operation, _TL, _UL> l, _T&& b)
	{ return {__FALCON_NAME_OPERATOR(), l,b}; }

	template<typename _T, typename _Operation, typename _TL, typename _UL>
	inline constexpr typename std::enable_if</* !is_placeholder<_T>::value &&*/ std::is_lvalue_reference<_T&>::value, ___lambda<__FALCON_NAME_OPERATOR, __FALCON_CALIFIER_FIRST_PARAM _T&, ___lambda<_Operation, _TL, _UL> > >::type operator __FALCON_SIGN_OPERATOR(__FALCON_CALIFIER_FIRST_PARAM _T& a, ___lambda<_Operation, _TL, _UL> l)
	{ return {__FALCON_NAME_OPERATOR(), a,l}; }

	template<typename _T, typename _Operation, typename _TL, typename _UL>
	inline constexpr typename std::enable_if</* !is_placeholder<_T>::value*/ std::is_rvalue_reference<_T&&>::value,  ___lambda<__FALCON_NAME_OPERATOR, _T, ___lambda<_Operation, _TL, _UL> > >::type operator __FALCON_SIGN_OPERATOR(_T&& a, ___lambda<_Operation, _TL, _UL> l)
	{ return {__FALCON_NAME_OPERATOR(), a,l}; }

	template<typename _Bind, typename _Bind2>
	inline constexpr typename std::enable_if<std::is_bind_expression<_Bind>::value && std::is_bind_expression<_Bind2>::value, ___lambda<__FALCON_NAME_OPERATOR, ___lambda<binder, _Bind, _Bind2>, binder> >::type operator __FALCON_SIGN_OPERATOR(_Bind __bind, _Bind2 __bind2)
	{ return {__FALCON_NAME_OPERATOR(), __bind, __bind2}; }
}