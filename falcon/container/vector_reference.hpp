#ifndef FALCON_CONTAINER_VECTOR_REFERENCE_HPP
#define FALCON_CONTAINER_VECTOR_REFERENCE_HPP

#include <vector>
#include <functional>
#include <type_traits>
#include <falcon/c++/noexcept.hpp>
#include <falcon/iterator/get_accessor_iterator.hpp>

namespace falcon {
	template<typename T>
#if defined(FALCON_FORCE_REFERENCE_COMPOUND_CONTAINER) || defined(FALCON_FORCE_REFERENCE_COMPOUND_VECTOR)
	using reference_compound_container_value = T&;
#else
	struct reference_compound_container_value
	{ typedef T type; };
#endif
}

namespace std {

#if defined(FALCON_FORCE_REFERENCE_COMPOUND_CONTAINER) || defined(FALCON_FORCE_REFERENCE_COMPOUND_VECTOR)
template<typename T>
struct allocator<T&>
: allocator<T>
{};
#endif

template<typename T, typename Allocator>
#if defined(FALCON_FORCE_REFERENCE_COMPOUND_CONTAINER) || defined(FALCON_FORCE_REFERENCE_COMPOUND_VECTOR)
class vector<T&, Allocator>
#else
class vector<falcon::reference_compound_container_value<T>, Allocator>
#endif
: public std::vector<std::reference_wrapper<T>, typename Allocator::template rebind<std::reference_wrapper<T>>::other>
{
	typedef std::reference_wrapper<T> __reference_wrapper;

public:
	typedef std::vector<__reference_wrapper, typename Allocator::template rebind<std::reference_wrapper<T>>::other> vector_base;

	typedef typename vector_base::size_type size_type;
	typedef typename vector_base::allocator_type allocator_type;
	typedef typename vector_base::difference_type difference_type;

	typedef T& value_type;
	typedef T* pointer;
	typedef value_type reference;
	typedef const T& const_reference;
	typedef const T* const_pointer;

	typedef typename falcon::iterator::build_get_accessor_iterator<typename vector_base::iterator>::type iterator;
	typedef typename falcon::iterator::build_get_accessor_iterator<typename vector_base::const_iterator>::type const_iterator;
	typedef typename falcon::iterator::build_get_accessor_iterator<typename vector_base::reverse_iterator>::type reverse_iterator;
	typedef typename falcon::iterator::build_get_accessor_iterator<typename vector_base::const_reverse_iterator>::type const_reverse_iterator;

public:
	//using vector_base::vector;

	/**
	 *  @brief  Default constructor creates no elements.
	 */
	vector()
	: vector_base()
	{}

	/**
	 *  @brief  Creates a %vector with no elements.
	 *  @param  __a  An allocator object.
	 */
	explicit vector(const allocator_type& __a)
	: vector_base(__a)
	{}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	/**
	 *  @brief  Creates a %vector with default constructed elements.
	 *  @param  __n  The number of elements to initially create.
	 *
	 *  This constructor fills the %vector with @a __n default
	 *  constructed elements.
	 */
	explicit vector(size_type __n)
	: vector_base(__n)
	{}
#endif

	/**
	 *  @brief  Creates a %vector with copies of an exemplar element.
	 *  @param  __n  The number of elements to initially create.
	 *  @param  __value  An element to copy.
	 *  @param  __a  An allocator.
	 *
	 *  This constructor fills the %vector with @a __n copies of @a __value.
	 */
	vector(size_type __n, const __reference_wrapper& __value,
				 const allocator_type& __a = allocator_type())
	: vector_base(__n, __value, __a)
	{}

	/**
	 *  @brief  %Vector copy constructor.
	 *  @param  __x  A %vector of identical element and allocator types.
	 *
	 *  The newly-created %vector uses a copy of the allocation
	 *  object used by @a __x.  All the elements of @a __x are copied,
	 *  but any extra memory in
	 *  @a __x (for fast expansion) will not be copied.
	 */
	vector(const vector_base& __x)
	: vector_base(__x)
	{}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	/**
	 *  @brief  %Vector move constructor.
	 *  @param  __x  A %vector of identical element and allocator types.
	 *
	 *  The newly-created %vector contains the exact contents of @a __x.
	 *  The contents of @a __x are a valid, but unspecified %vector.
	 */
	vector(vector_base __x) noexcept
	: vector_base(std::move(__x))
	{}

	/**
	 *  @brief  %Vector move constructor.
	 *  @param  __x  A %vector of identical element and allocator types.
	 *
	 *  The newly-created %vector contains the exact contents of @a __x.
	 *  The contents of @a __x are a valid, but unspecified %vector.
	 */
	vector(vector&& __x) noexcept
	: vector_base(static_cast<vector_base&&>(__x))
	{}

	/// Copy constructor with alternative allocator
	vector(const vector_base& __x, const allocator_type& __a)
	: vector_base(__x, __a)
	{}

	/// Move constructor with alternative allocator
	vector(vector_base&& __rv, const allocator_type& __m)
	: vector_base(std::move(__rv), __m)
	{}

	/// Move constructor with alternative allocator
	vector(vector&& __rv, const allocator_type& __m)
	: vector_base(static_cast<vector_base&&>(__rv), __m)
	{}

	/**
	 *  @brief  Builds a %vector from an initializer list.
	 *  @param  __l  An initializer_list.
	 *  @param  __a  An allocator.
	 *
	 *  Create a %vector consisting of copies of the elements in the
	 *  initializer_list @a __l.
	 *
	 *  This will call the element type's copy constructor N times
	 *  (where N is @a __l.size()) and do no memory reallocation.
	 */
	vector(std::initializer_list<__reference_wrapper> __l,
				 const allocator_type& __a = allocator_type())
	: vector_base(__l, __a)
	{}
#endif

	/**
	 *  @brief  Builds a %vector from a range.
	 *  @param  __first  An input iterator.
	 *  @param  __last  An input iterator.
	 *  @param  __a  An allocator.
	 *
	 *  Create a %vector consisting of copies of the elements from
	 *  [first,last).
	 *
	 *  If the iterators are forward, bidirectional, or
	 *  random-access, then this will call the elements' copy
	 *  constructor N times (where N is distance(first,last)) and do
	 *  no memory reallocation.  But if only input iterators are
	 *  used, then this will do at most 2N calls to the copy
	 *  constructor, and logN memory reallocations.
	 */
	template<typename _InputIterator, typename E = typename std::enable_if<!std::is_integral<_InputIterator>::value>::type>
	vector(_InputIterator __first, _InputIterator __last,
				 const allocator_type& __a = allocator_type())
	: vector_base(__first, __last, __a)
	{}

	// iterators
	/**
	 *  Returns a read/write iterator that points to the first
	 *  element in the %vector.  Iteration is done in ordinary
	 *  element order.
	 */
	iterator begin() CPP_NOEXCEPT
	{ return iterator(impl().begin()); }

	/**
	 *  Returns a read-only (constant) iterator that points to the
	 *  first element in the %vector.  Iteration is done in ordinary
	 *  element order.
	 */
	const_iterator begin() const CPP_NOEXCEPT
	{ return const_iterator(impl().begin()); }

	/**
	 *  Returns a read/write iterator that points one past the last
	 *  element in the %vector.  Iteration is done in ordinary
	 *  element order.
	 */
	iterator end() CPP_NOEXCEPT
	{ return iterator(impl().end()); }

	/**
	 *  Returns a read-only (constant) iterator that points one past
	 *  the last element in the %vector.  Iteration is done in
	 *  ordinary element order.
	 */
	const_iterator end() const CPP_NOEXCEPT
	{ return const_iterator(impl().end()); }

	/**
	 *  Returns a read/write reverse iterator that points to the
	 *  last element in the %vector.  Iteration is done in reverse
	 *  element order.
	 */
	reverse_iterator rbegin() CPP_NOEXCEPT
	{ return reverse_iterator(impl().rbegin()); }

	/**
	 *  Returns a read-only (constant) reverse iterator that points
	 *  to the last element in the %vector.  Iteration is done in
	 *  reverse element order.
	 */
	const_reverse_iterator rbegin() const CPP_NOEXCEPT
	{ return const_reverse_iterator(impl().rbegin()); }

	/**
	 *  Returns a read/write reverse iterator that points to one
	 *  before the first element in the %vector.  Iteration is done
	 *  in reverse element order.
	 */
	reverse_iterator rend() CPP_NOEXCEPT
	{ return reverse_iterator(impl().rend()); }

	/**
	 *  Returns a read-only (constant) reverse iterator that points
	 *  to one before the first element in the %vector.  Iteration
	 *  is done in reverse element order.
	 */
	const_reverse_iterator rend() const CPP_NOEXCEPT
	{ return const_reverse_iterator(impl().rend()); }

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	/**
	 *  Returns a read-only (constant) iterator that points to the
	 *  first element in the %vector.  Iteration is done in ordinary
	 *  element order.
	 */
	const_iterator cbegin() const noexcept
	{ return begin(); }

	/**
	 *  Returns a read-only (constant) iterator that points one past
	 *  the last element in the %vector.  Iteration is done in
	 *  ordinary element order.
	 */
	const_iterator cend() const noexcept
	{ return end(); }

	/**
	 *  Returns a read-only (constant) reverse iterator that points
	 *  to the last element in the %vector.  Iteration is done in
	 *  reverse element order.
	 */
	const_reverse_iterator crbegin() const noexcept
	{ return rbegin(); }

	/**
	 *  Returns a read-only (constant) reverse iterator that points
	 *  to one before the first element in the %vector.  Iteration
	 *  is done in reverse element order.
	 */
	const_reverse_iterator crend() const noexcept
	{ return rend(); }
#endif

	/**
	 *  @brief  Subscript access to the data contained in the %vector.
	 *  @param __n The index of the element for which data should be
	 *  accessed.
	 *  @return  Read/write reference to data.
	 *
	 *  This operator allows for easy, array-style, data access.
	 *  Note that data access with this operator is unchecked and
	 *  out_of_range lookups are not defined. (For checked lookups
	 *  see at().)
	 */
	reference operator[](size_type __n)
	{ return impl().operator[](__n).get(); }

	/**
	 *  @brief  Subscript access to the data contained in the %vector.
	 *  @param __n The index of the element for which data should be
	 *  accessed.
	 *  @return  Read-only (constant) reference to data.
	 *
	 *  This operator allows for easy, array-style, data access.
	 *  Note that data access with this operator is unchecked and
	 *  out_of_range lookups are not defined. (For checked lookups
	 *  see at().)
	 */
	const_reference operator[](size_type __n) const
	{ return impl().operator[](__n).get(); }

	/**
	 *  @brief  Provides access to the data contained in the %vector.
	 *  @param __n The index of the element for which data should be
	 *  accessed.
	 *  @return  Read/write reference to data.
	 *  @throw  std::out_of_range  If @a __n is an invalid index.
	 *
	 *  This function provides for safer data access.  The parameter
	 *  is first checked that it is in the range of the vector.  The
	 *  function throws out_of_range if the check fails.
	 */
	reference at(size_type __n)
	{ return impl().at(__n).get(); }

	/**
	 *  @brief  Provides access to the data contained in the %vector.
	 *  @param __n The index of the element for which data should be
	 *  accessed.
	 *  @return  Read-only (constant) reference to data.
	 *  @throw  std::out_of_range  If @a __n is an invalid index.
	 *
	 *  This function provides for safer data access.  The parameter
	 *  is first checked that it is in the range of the vector.  The
	 *  function throws out_of_range if the check fails.
	 */
	const_reference at(size_type __n) const
	{ return impl().at(__n).get(); }

	/**
	 *  Returns a read/write reference to the data at the first
	 *  element of the %vector.
	 */
	reference front()
	{ return impl().front().get(); }

	/**
	 *  Returns a read-only (constant) reference to the data at the first
	 *  element of the %vector.
	 */
	const_reference front() const
	{ return impl().front().get(); }

	/**
	 *  Returns a read/write reference to the data at the last
	 *  element of the %vector.
	 */
	reference back()
	{ return impl().back().get(); }

	/**
	 *  Returns a read-only (constant) reference to the data at the
	 *  last element of the %vector.
	 */
	const_reference back() const
	{ return impl().back().get(); }

	using vector_base::insert;

	/**
	 *  @brief  Inserts given value into %vector before specified iterator.
	 *  @param  __position  An iterator into the %vector.
	 *  @param  __x  Data to be inserted.
	 *  @return  An iterator that points to the inserted data.
	 *
	 *  This function will insert a copy of the given value before
	 *  the specified location.  Note that this kind of operation
	 *  could be expensive for a %vector and if it is frequently
	 *  used the user should consider using std::list.
	 */
	iterator insert(iterator __position, const value_type& __x)
	{ return iterator(impl().insert(__position.base(), __x)); }

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	/**
	 *  @brief  Inserts an initializer_list into the %vector.
	 *  @param  __position  An iterator into the %vector.
	 *  @param  __l  An initializer_list.
	 *
	 *  This function will insert copies of the data in the
	 *  initializer_list @a l into the %vector before the location
	 *  specified by @a position.
	 *
	 *  Note that this kind of operation could be expensive for a
	 *  %vector and if it is frequently used the user should
	 *  consider using std::list.
	 */
	void insert(iterator __position, std::initializer_list<value_type> __l)
	{ impl().insert(__position.base(), __l.begin(), __l.end()); }
#endif

	/**
	 *  @brief  Inserts a range into the %vector.
	 *  @param  __position  An iterator into the %vector.
	 *  @param  __first  An input iterator.
	 *  @param  __last   An input iterator.
	 *
	 *  This function will insert copies of the data in the range
	 *  [__first,__last) into the %vector before the location specified
	 *  by @a pos.
	 *
	 *  Note that this kind of operation could be expensive for a
	 *  %vector and if it is frequently used the user should
	 *  consider using std::list.
	 */
	template<typename _InputIterator>
	void insert(iterator __position, _InputIterator __first, _InputIterator __last)
	{ return iterator(impl().insert(__position.base(), __first, __last)); }

	using vector_base::erase;

	/**
	 *  @brief  Remove element at given position.
	 *  @param  __position  Iterator pointing to element to be erased.
	 *  @return  An iterator pointing to the next element (or end()).
	 *
	 *  This function will erase the element at the given position and thus
	 *  shorten the %vector by one.
	 *
	 *  Note This operation could be expensive and if it is
	 *  frequently used the user should consider using std::list.
	 *  The user is also cautioned that this function only erases
	 *  the element, and that if the element is itself a pointer,
	 *  the pointed-to memory is not touched in any way.  Managing
	 *  the pointer is the user's responsibility.
	 */
	iterator erase(iterator __position)
	{ return iterator(impl().erase(__position.base())); }

	/**
	 *  @brief  Remove a range of elements.
	 *  @param  __first  Iterator pointing to the first element to be erased.
	 *  @param  __last  Iterator pointing to one past the last element to be
	 *                  erased.
	 *  @return  An iterator pointing to the element pointed to by @a __last
	 *           prior to erasing (or end()).
	 *
	 *  This function will erase the elements in the range
	 *  [__first,__last) and shorten the %vector accordingly.
	 *
	 *  Note This operation could be expensive and if it is
	 *  frequently used the user should consider using std::list.
	 *  The user is also cautioned that this function only erases
	 *  the elements, and that if the elements themselves are
	 *  pointers, the pointed-to memory is not touched in any way.
	 *  Managing the pointer is the user's responsibility.
	 */
	iterator erase(iterator __first, iterator __last)
	{ return iterator(impl().erase(__first.base(), __last.base())); }

	/**
	 *  @brief  Swaps data with another %vector.
	 *  @param  __x  A %vector of the same element and allocator types.
	 *
	 *  This exchanges the elements between two vectors in constant time.
	 *  (Three pointers, so it should be quite fast.)
	 *  Note that the global std::swap() function is specialized such that
	 *  std::swap(v1,v2) will feed to this function.
	 */
	void swap(vector& __x)
#ifdef __GXX_EXPERIMENTAL_CXX0X__
	noexcept(typename std::allocator_traits<allocator_type>::propagate_on_container_swap())
#endif
	{ swap(__x.impl()); }

	/**
	 *  @brief  Swaps data with another %vector.
	 *  @param  __x  A %vector of the same element and allocator types.
	 *
	 *  This exchanges the elements between two vectors in constant time.
	 *  (Three pointers, so it should be quite fast.)
	 *  Note that the global std::swap() function is specialivector_referencezed such that
	 *  std::swap(v1,v2) will feed to this function.
	 */
	void swap(vector_base& __x)
#ifdef __GXX_EXPERIMENTAL_CXX0X__
	noexcept(typename std::allocator_traits<allocator_type>::propagate_on_container_swap())
#endif
	{ impl().swap(impl(), __x); }

	const vector_base& impl() const CPP_NOEXCEPT
	{ return *this; }

	vector_base& impl() CPP_NOEXCEPT
	{ return *this; }

	operator vector_base& () CPP_NOEXCEPT
	{ return impl(); }

	operator const vector_base& () const CPP_NOEXCEPT
	{ return impl(); }
};

}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
namespace falcon {
	template<typename T, typename Allocator = std::allocator<T>>
	using vector_reference = std::vector<reference_compound_container_value<T>, Allocator>;

	namespace container {
		/// Alias for falcon::vector_refrence<T> if T is a reference otherwise std::vector<T>
		template<
			typename T,
			typename Allocator = std::allocator<
				typename std::remove_reference<T>::type
			>
		>
		using vector = typename std::conditional<
			std::is_reference<T>::value,
			std::vector<
				reference_compound_container_value<
					typename std::remove_reference<T>::type
				>,
				Allocator
			>,
			std::vector<T, Allocator>
		>::type;
	}
}
#endif

#endif