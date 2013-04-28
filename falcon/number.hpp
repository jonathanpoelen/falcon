#ifndef _FALCON_NUMBER_HPP
#define _FALCON_NUMBER_HPP

///TODO vérifier sur ue machine en little endian et en big endian

#include <list>
#include <stdexcept>
#include <initializer_list>
#include <iostream> ///TODO déplacer dans number_io.hpp et utiliser des facet
#include <falcon/c++1x/syntax.hpp>
#include <falcon/preprocessor/getter.hpp>
#include <falcon/preprocessor/comparison.hpp>
#include <falcon/preprocessor/iterator.hpp>
#include <falcon/iterator/bit_iterator_iterator.hpp>
#include <falcon/type_traits/numeric/minimal_int.hpp>
#include <falcon/mutable_countdown.hpp>

namespace falcon {

template<typename _T>
struct __not_remove_unused_zero
{
	const _T* ptr;
};

template<bool _Signed = true, std::size_t _AllocateSize = 4>
class number
{
	typedef number<_Signed, _AllocateSize> self_type;
	typedef unsigned char scalar_data_type;
	typedef std::list<scalar_data_type> data_type;
	typedef typename data_type::iterator data_iterator;
	typedef typename data_type::const_iterator const_data_iterator;
	typedef typename data_type::reverse_iterator data_reverse_iterator;
	typedef typename data_type::const_reverse_iterator const_data_reverse_iterator;
	typedef unsigned size_t;

protected:
	static const scalar_data_type scalar_size = bit_size<scalar_data_type>::value;
	static const scalar_data_type left_bit = left_bit<scalar_data_type>::value; ///TODO pareil pour un last ou un big endian ? faire un bit_left et bit_right ?

	template <typename _Base>
	class __iterator : public _Base
	{
		friend class number;

		typedef typename _Base::iterator_type iterator_type;

		__iterator(iterator_type it)
		: _Base(it)
		{}

		__iterator(iterator_type it, scalar_data_type mask)
		: _Base(it, mask)
		{}

		void next_inner_iterator()
		{ ++*this; }
	};

protected:
	typedef __iterator<falcon::iterator::bit_iterator_iterator<data_iterator> > iterator;
	typedef __iterator<falcon::iterator::bit_iterator_iterator<const_data_iterator> > const_iterator;
	typedef __iterator<falcon::iterator::bit_reverse_iterator_iterator<data_reverse_iterator> > reverse_iterator;
	typedef __iterator<falcon::iterator::bit_reverse_iterator_iterator<const_data_reverse_iterator> > const_reverse_iterator;

private:
	data_type _data;
	char _flag;

protected:
	FALCON_MEMBER_ITERATOR_ARGS(
		(_data.begin()), (_data.end())
	)
	FALCON_MEMBER_REVERSE_ITERATOR_ARGS(
		(_data.rbegin()), (_data.rend())
	)

	template<typename _Iterator>
	void push_weak(_Iterator __begin, _Iterator __end)
	{ _data.insert(_data.end(), __begin, __end); }

	template<typename _Iterator>
	void push_strong(_Iterator __begin, _Iterator __end)
	{ _data.insert(_data.begin(), __begin, __end); }

	template<typename _Iterator>
	static _Iterator ignore_unused_zero(_Iterator begin, _Iterator end)
	{
		while (begin != end && !*begin)
			--begin;
		return begin;
	}

	data_iterator ignore_unused_zero()
	{ return self_type::ignore_unused_zero<>(_data.begin(), _data.end()); }

	template<typename _Iterator>
	void push_used_strong(_Iterator __begin, _Iterator __end)
	{ push_strong(self_type::ignore_unused_zero(__begin, __end), __end); }

	template<typename _Iterator>
	void push_strong(_Iterator __begin, _Iterator __end, bool remove_unused_zero)
	{
		if (remove_unused_zero)
			push_used_strong(__begin, __end);
		else
			push_strong(__begin, __end);
	}

	bool extend(reverse_iterator &it, reverse_iterator &end)
	{
		if (it == end)
		{
			_data.push_front(0);
			++end.next_inner_iterator();
			return true;
		}
		return false;
	}

public:
	constexpr number()
	: _data()
	, _flag(0)
	{}

	number(std::initializer_list<scalar_data_type> initializer, bool remove_unused_zero = true)
	: _data()
	, _flag(0)
	{
		push_strong(initializer.begin(), initializer.end(), remove_unused_zero);
	}

	template<typename _Iterator>
	number(_Iterator begin, _Iterator end, bool remove_unused_zero = true)
	: _data()
	, _flag(0)
	{
		push_strong(begin, end, remove_unused_zero);
	}

	number(const self_type& other)
	: _data(other._data)
	, _flag(other._flag)
	{}

	template<typename _Int, typename _EnableIf = typename std::enable_if<std::is_integral<_Int>::value, _Int>::type>
	number(_Int n, bool remove_unused_zero = true)
	: _data()
	, _flag(0)
	{
		///TODO gerer le last et le big endian
		static_assert(std::is_integral<_Int>::value, "is not a integer");
		union
		{
			scalar_data_type array[sizeof(n) / scalar_size];
			_Int nn;
		} u;
		u.nn = n;
		push_strong(&*u.array, end<>(u.array), remove_unused_zero);
	}

	void remove_unused_zero()
	{ _data.erase(_data.begin(), ignore_unused_zero()); }

protected:
	void move_left(data_iterator &it, size_t n)
	{
		data_iterator it_prev = it;
		scalar_data_type m = scalar_size - n;
		for (data_iterator end = _data.end(); ++it != end; ++it_prev)
		{
			*it_prev <<= n;
			*it_prev |= *it >> m;
		}
		*it_prev <<= n;
	}

	void move_right(data_iterator &it, size_t n)
	{
		data_iterator begin = _data.begin();
		if (begin != it)
		{
			data_iterator it_next = --it;
			if (begin != it)
			{
				scalar_data_type m = scalar_size - n;
				for (; begin != --it; --it_next)
				{
					*it_next >>= n;
					*it_next |= *it << m;
				}
			}
		}
		if (!(*begin >>= n))
			_data.pop_front();
	}

public:
	size_t to_size_t() const throw(std::overflow_error)
	{
		if (_data.empty())
			return 0;number
		const_data_iterator it = _data.begin();
		const_data_iterator end = _data.end();
		size_t ret = *it;
		for (mutable_countdown<sizeof(size_t)-1> countdown; ++it != end && countdown; )
		{
			ret <<= scalar_size;
			ret |= *it;
		}
		if (it != end)
			throw std::overflow_error("number::to_size_t");
		return ret;
	}

	self_type& operator<<=(size_t n)
	{
		if (!n || _data.empty())
			return *this;
		if (!(n % scalar_size))
		{
			_data.insert(_data.end(), n / __CHAR_BIT__, 0);
			return *this;
		}
		scalar_data_type pbit = 1;
		data_iterator it = _data.begin();
		for (scalar_data_type p = left_bit; !(p & *it); p >>= 1)
			++pbit;
		if (pbit > n)
			move_left(it, n);
		else
		{
			size_t add = (n + scalar_size - pbit) / scalar_size;
			n %= scalar_size;
			scalar_data_type m = scalar_size - n;
			if (pbit <= n)
			{
				_data.push_front(0);
				*_data.begin() = *it >> m;
				--add;
			}
			move_left(it, n);
			_data.insert(_data.end(), add, 0);
		}
		return *this;
	}

	self_type& operator<<=(const self_type& other) throw(std::overflow_error)
	{ return operator<<=(other.to_size_t()); }

	self_type& operator>>=(size_t n)
	{
		if (!n || _data.empty())
			return *this;
		data_iterator it = _data.end();
		data_iterator end = _data.begin();
		while (n >= __CHAR_BIT__ && --it != end)
			n -= __CHAR_BIT__;
		if (it == end && n >= __CHAR_BIT__)
		{
			_data.clear();
			return *this;
		}
		_data.erase(it, _data.end());
		if (n)
			move_right(it, n);
		return *this;
	}

	self_type& operator>>=(const self_type& other) throw(std::overflow_error)
	{ return operator>>=(other.to_size_t()); }

	self_type& operator+=(const self_type& other)
	{
		reverse_iterator it = rbegin();
		reverse_iterator end = rend();
		const_reverse_iterator other_it = other.rbegin();
		const_reverse_iterator other_end = other.rend();

		do
		{
			for (;  it != end && other_it != other_end; ++it, ++other_it)
			{
				if (it || other_it){
					if (it && other_it){
						if (!(_flag & 1)){
							it.zero();
							_flag |= 1;
						}
					} else if (_flag & 1) {
						it.zero();
					} else if (!*it){
						it.one();
					}
				} else if (_flag & 1) {
					it.one();
					_flag &= ~1;
				}
			}
		} while (other_it != other_end && extend(it, end));

		if (_flag & 1)
		{
			while (extend(it, end))
			{
				while (it != end && *it)
					++it;
			}
			it.one();
			_flag &= ~1;
		}
		return *this;
	}

public:
	template <class _CharT, class _Traits>
	std::basic_ostream<_CharT, _Traits>& put(std::basic_ostream<_CharT, _Traits>& os) const
	{
		/*const_iterator it =  begin();
		const_iterator end = end();
		///TODO filtrer d'abord les data_iterator vide
		if (__remove_unused_zero)
		{
			while (it != end && *it)
				++it;
		}*/
		const_iterator it = begin();
		const_iterator _end = end();
		if (it == _end)
			return os << '0';
		for (; it != _end; ++it)
			os << (*it ? '1' : '0');
		return os;
	}

};

///TODO a mettre dans un number_io.hpp
template <class _CharT, class _Traits, bool _Signed, std::size_t _AllocateSize>
std::basic_ostream<_CharT, _Traits>& operator<<(std::basic_ostream<_CharT, _Traits>& __os, const falcon::number<_Signed, _AllocateSize>& __x)
{ return __x.put(__os); }

}

#endif
