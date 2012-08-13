#ifndef _FALCON_NODE_ITERATOR_HPP
#define _FALCON_NODE_ITERATOR_HPP

#include <iterator>
#include <falcon/preprocessor/iterator.hpp>
#include <falcon/preprocessor/comparison.hpp>
#include <falcon/preprocessor/incremental.hpp>

namespace falcon { namespace node {

	template <typename _Node>
	struct next_node_access_traits
	{
		typedef _Node node_type;

		static inline _Node next(_Node node)
		{ return node->next(); }
	};

	template <typename _Node>
	struct prev_node_access_traits
	{
		typedef _Node node_type;

		static inline _Node next(_Node node)
		{ return node->prev(); }
	};

	template <typename _Node>
	struct up_node_access_traits
	{
		typedef _Node node_type;

		static inline _Node next(_Node node)
		{ return node->up(); }
	};

	template <typename _Node>
	struct down_node_access_traits
	{
		typedef _Node node_type;

		static inline _Node next(_Node node)
		{ return node->down(); }
	};

	template <typename _Node>
	struct left_node_access_traits
	{
		typedef _Node node_type;

		static inline _Node next(_Node node)
		{ return node->left(); }
	};

	template <typename _Node>
	struct right_node_access_traits
	{
		typedef _Node node_type;

		static inline _Node next(_Node node)
		{ return node->right(); }
	};

	template<typename _AccessTraits>
	class basic_node_iterator
	{
		//static_assert(std::is_pointer<_Cross>::value, "node_iterator iterate on node pointer");
		typedef basic_node_iterator<_AccessTraits> self_type;

	public:
		typedef typename _AccessTraits::node_type node_type;

	private:
		typedef std::iterator_traits<node_type> iterator_traits;

	public:
		typedef typename iterator_traits::pointer pointer;
		typedef typename iterator_traits::value_type value_type;
		typedef typename iterator_traits::reference reference;
		typedef typename iterator_traits::difference_type difference_type;

	protected:
		pointer _value;

	public:
		basic_node_iterator()
		: _value(0)
		{}

		basic_node_iterator(const self_type& other)
		: _value(other._value)
		{}

		basic_node_iterator(pointer value)
		: _value(value)
		{}

		basic_node_iterator(value_type& value)
		: _value(&value)
		{}

		self_type& operator=(pointer other)
		{
			_value = other;
			return *this;
		}

		self_type& operator=(const self_type& other)
		{
			_value = other._value;
			return *this;
		}

		reference operator*()
		{ return *_value; }

		pointer operator->()
		{ return _value; }

		const reference operator*() const
		{ return *_value; }

		const value_type* operator->() const
		{ return _value; }

		FALCON_MEMBER_EQUAL2_OPERATOR(self_type, _value, other._value)

		FALCON_MEMBER_INCREMENT(self_type, _value = _AccessTraits::next(_value))
	};


	template <typename _Next, typename _Prev>
	struct double_node_access_traits;

	template <typename _Node, template <class> class _Next, template <class> class _Prev>
	struct double_node_access_traits<_Next<_Node>, _Prev<_Node> >
	{
		typedef _Node node_type;

		static inline _Node next(_Node node)
		{ return _Next<_Node>::next(node); }

		static inline _Node prev(_Node node)
		{ return _Prev<_Node>::prev(node); }
	};

	template<typename _Node, template <class> class _Next, template <class> class _Prev>
	class basic_node_iterator<double_node_access_traits<_Next<_Node>, _Prev<_Node> > >
	{
		//static_assert(std::is_pointer<_Cross>::value, "node_iterator iterate on node pointer");
		typedef double_node_access_traits<_Next<_Node>, _Prev<_Node> > access_traits;
		typedef basic_node_iterator<access_traits> self_type;
		typedef std::iterator_traits<_Node> iterator_traits;

	public:
		typedef typename access_traits::node_type node_type;
		typedef typename iterator_traits::pointer pointer;
		typedef typename iterator_traits::value_type value_type;
		typedef typename iterator_traits::reference reference;
		typedef typename iterator_traits::difference_type difference_type;

	protected:
		pointer _value;

	public:
		basic_node_iterator()
		: _value(0)
		{}

		basic_node_iterator(const self_type& other)
		: _value(other._value)
		{}

		basic_node_iterator(pointer value)
		: _value(value)
		{}

		basic_node_iterator(value_type& value)
		: _value(&value)
		{}

		self_type& operator=(pointer other)
		{
			_value = other;
			return *this;
		}

		self_type& operator=(const self_type& other)
		{
			_value = other._value;
			return *this;
		}

		reference operator*()
		{ return *_value; }

		pointer operator->()
		{ return _value; }

		const reference operator*() const
		{ return *_value; }

		const value_type* operator->() const
		{ return _value; }

		FALCON_MEMBER_EQUAL2_OPERATOR(self_type, _value, other._value)

		FALCON_MEMBER_INCREMENT(self_type, _value = access_traits::next(_value))
		FALCON_MEMBER_DECREMENT(self_type, _value = access_traits::prev(_value))
	};

	template <typename _Traits>
	struct __range_node_iterator
	{
		typedef typename _Traits::node_type node_type;
		typedef typename _Traits::iterator iterator;
		typedef typename _Traits::const_iterator const_iterator;

		node_type __value;

		__range_node_iterator(node_type __v = 0)
		: __value(__v)
		{}

		FALCON_MEMBER_ITERATOR(_Traits::begin(__value), _Traits::end(0))
	};

	template <typename _Node, template<class> class _AccessTraits>
	struct __range_node_iterator<_AccessTraits<_Node*> >
	{
		typedef _Node* node_type;
		typedef basic_node_iterator<_AccessTraits<_Node*> > iterator;
		typedef basic_node_iterator<_AccessTraits<const _Node*> > const_iterator;

		node_type __value;

		__range_node_iterator(node_type __v = 0)
		: __value(__v)
		{}

		FALCON_MEMBER_ITERATOR_ARGS((__value), (0))
	};

	template <typename _Node, template<class> class _Next, template<class> class _Prev>
	struct __range_node_iterator<double_node_access_traits<_Next<_Node*>, _Prev<_Node*> > >
	{
		typedef _Node* node_type;
		typedef basic_node_iterator<_Next<_Node*> > iterator;
		typedef basic_node_iterator<_Next<const _Node*> > const_iterator;
		typedef basic_node_iterator<_Prev<_Node*> > reverse_iterator;
		typedef basic_node_iterator<_Prev<const _Node*> > const_reverse_iterator;

		node_type __value;

		__range_node_iterator(node_type __v = 0)
		: __value(__v)
		{}

		FALCON_MEMBER_ITERATOR_ARGS((__value), (0))
		FALCON_MEMBER_REVERSE_ITERATOR_ARGS((__value), (0))
	};

	template<typename _Node>
	__range_node_iterator<next_node_access_traits<_Node*> > make_range_next_node(_Node& node)
	{
		return __range_node_iterator<next_node_access_traits<_Node*> >(&node);
	}

	template<typename _Node>
	__range_node_iterator<prev_node_access_traits<_Node*> > make_range_prev_node(_Node& node)
	{
		return __range_node_iterator<prev_node_access_traits<_Node*> >(&node);
	}

	template<typename _Node>
	__range_node_iterator<up_node_access_traits<_Node*> > make_range_up_node(_Node& node)
	{
		return __range_node_iterator<up_node_access_traits<_Node*> >(&node);
	}

	template<typename _Node>
	__range_node_iterator<down_node_access_traits<_Node*> > make_range_down_node(_Node& node)
	{
		return __range_node_iterator<down_node_access_traits<_Node*> >(&node);
	}

	template<typename _Node>
	__range_node_iterator<left_node_access_traits<_Node*> > make_range_left_node(_Node& node)
	{
		return __range_node_iterator<left_node_access_traits<_Node*> >(&node);
	}

	template<typename _Node>
	__range_node_iterator<right_node_access_traits<_Node*> > make_range_right_node(_Node& node)
	{
		return __range_node_iterator<right_node_access_traits<_Node*> >(&node);
	}

	template<typename _Node>
	__range_node_iterator<double_node_access_traits<left_node_access_traits<_Node*>, right_node_access_traits<_Node*> > > make_right_to_left_node(_Node& node)
	{
		return __range_node_iterator<double_node_access_traits<left_node_access_traits<_Node*>, right_node_access_traits<_Node*> > >(&node);
	}

	template<typename _Node>
	__range_node_iterator<double_node_access_traits<right_node_access_traits<_Node*>, left_node_access_traits<_Node*> > > make_left_to_right_node(_Node& node)
	{
		return __range_node_iterator<double_node_access_traits<right_node_access_traits<_Node*>, left_node_access_traits<_Node*> > >(&node);
	}

	template<typename _Node>
	__range_node_iterator<double_node_access_traits<up_node_access_traits<_Node*>, down_node_access_traits<_Node*> > > make_down_to_up_node(_Node& node)
	{
		return __range_node_iterator<double_node_access_traits<up_node_access_traits<_Node*>, down_node_access_traits<_Node*> > >(&node);
	}

	template<typename _Node>
	__range_node_iterator<double_node_access_traits<down_node_access_traits<_Node*>, up_node_access_traits<_Node*> > > make_up_to_down_node(_Node& node)
	{
		return __range_node_iterator<double_node_access_traits<down_node_access_traits<_Node*>, up_node_access_traits<_Node*> > >(&node);
	}
} }

#endif