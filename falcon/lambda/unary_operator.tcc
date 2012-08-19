namespace operators {
	template<int _Num>
	inline constexpr ___lambda<__FALCON_NAME_OPERATOR, placeholder<_Num> > operator __FALCON_SIGN_OPERATOR(const placeholder<_Num>&)
	{ return {__FALCON_NAME_OPERATOR()}; }

	template<typename _Operation, typename _T, typename _U>
	inline constexpr ___lambda<__FALCON_NAME_OPERATOR, ___lambda<_Operation, _T, _U> > operator __FALCON_SIGN_OPERATOR(___lambda<_Operation, _T, _U> l)
	{ return {__FALCON_NAME_OPERATOR(), l}; }

	template<typename _Bind>
	inline constexpr typename std::enable_if<std::is_bind_expression<_Bind>::value, ___lambda<__FALCON_NAME_OPERATOR, _Bind, binder> >::type operator __FALCON_SIGN_OPERATOR(_Bind __bind)
	{ return {__FALCON_NAME_OPERATOR(), __bind}; }
}