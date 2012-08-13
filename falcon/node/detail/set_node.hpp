#ifndef _NODE_DETAIL_SET_NODE_HPP
#define _NODE_DETAIL_SET_NODE_HPP

namespace falcon { namespace node { namespace detail {
	template<typename _Node>
	struct __set_node
	{
		static inline void set_right(_Node *target, _Node *right);
		static inline void set_left(_Node *target, _Node *left);
		static inline void set_up(_Node *target, _Node *up);
		static inline void set_down(_Node *target, _Node *down);
	};


#define _CREATE_SET_NODE(_Name, _Opposite)\
	template<typename _Node>\
	inline void __set_node<_Node>::set_##_Name(_Node *target, _Node *_Name)\
	{\
		if (target->_M_link()._Name)\
			target->_M_link()._Name->_M_link()._Opposite = 0;\
		if (_Name)\
			_Name->_M_link()._Opposite = target;\
		target->_M_link()._Name = _Name;\
	}

	_CREATE_SET_NODE(right, left);
	_CREATE_SET_NODE(left, right);
	_CREATE_SET_NODE(up, down);
	_CREATE_SET_NODE(down, up);

#undef _CREATE_SET_NODE
} } }

#endif