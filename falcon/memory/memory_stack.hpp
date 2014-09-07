#ifndef FALCON_MEMORY_MEMORY_STACK_HPP
#define FALCON_MEMORY_MEMORY_STACK_HPP

#include <utility>

#include <falcon/c++/pack.hpp>
#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/reference.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/empty_class.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include <falcon/utility/move.hpp>
#if __cplusplus >= 201103L
# include <type_traits>
#else
#include <boost/type_traits/aligned_storage.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/remove_extent.hpp>
#include <boost/type_traits/is_integral.hpp>
#endif

namespace falcon {

namespace aux_ {

  template<class T>
  struct memory_stack_type
  {
    typedef T type;
    typedef T base_type;
    typedef typename FALCON_BOOST_OR_STD_NAMESPACE::aligned_storage<
      sizeof(T),
      FALCON_BOOST_OR_STD_NAMESPACE::alignment_of<T>::value
    >::type memory_type;
  };

  template<class T, std::size_t N>
  struct memory_stack_type<T[N]>
  {
    typedef T type[N];
    typedef T base_type;
    typedef typename memory_stack_type<T>::memory_type memory_type[N];
  };

  template<class T>
  struct memory_stack_base
  {
    typedef typename memory_stack_type<T>::type type;
    typedef typename memory_stack_type<T>::memory_type memory_type;
    typedef typename memory_stack_type<T>::base_type * pointer;
    typedef typename memory_stack_type<T>::base_type const * const_pointer;

  private:
    memory_type m_data;

  public:
    CPP_CONSTEXPR_NOT_CONST const memory_type& data() const
    {
      return m_data;
    }

    CPP_CONSTEXPR_NOT_CONST type& get()
    {
      return reinterpret_cast<type&>(m_data);
    }

    CPP_CONSTEXPR_NOT_CONST const type& get() const
    {
      return reinterpret_cast<const type&>(m_data);
    }

    CPP_CONSTEXPR_NOT_CONST memory_type& data()
    {
      return m_data;
    }

    CPP_CONSTEXPR_NOT_CONST pointer address()
    {
      return reinterpret_cast<T*>(&m_data);
    }

    CPP_CONSTEXPR_NOT_CONST const_pointer address() const
    {
      return reinterpret_cast<const T*>(&m_data);
    }

    CPP_CONSTEXPR std::size_t size() const
    {
      return sizeof(memory_type);
    }
  };

  template <typename T,
  #if __cplusplus >= 201103L
    bool = std::is_trivial<typename std::remove_extent<T>::type>::value>
  #else
    bool = boost::is_integral<typename boost::remove_extent<T>::type>::value>
  #endif
  struct memory_stack
  : memory_stack_base<T>
  {
    typedef typename memory_stack_base<T>::type type;
    typedef typename memory_stack_base<T>::memory_type memory_type;


    template<class CPP_PACK Args>
    void construct(Args CPP_RVALUE CPP_PACK args)
    CPP_NOEXCEPT_OPERATOR2(T(std::declval<Args>()...))
    {
      new (this->address()) T(FALCON_FORWARD(Args, args)CPP_PACK);
    }

    void destroy() CPP_NOEXCEPT
    {
      this->get().~T();
    }
  };

  template <typename T>
  struct memory_stack<T, true>
  : memory_stack_base<T>
  {
    typedef typename memory_stack_base<T>::type type;
    typedef typename memory_stack_base<T>::memory_type memory_type;


  #if __cplusplus >= 201103L
    template<class... Args>
    void construct(Args&&... args) noexcept
    {
      this->get() = {std::forward<Args>(args)...};
    }

    void construct(T&& value) noexcept
    {
      this->get() = std::forward<T>(value);
    }
  #endif

    template<class U>
    void construct(const U& value) CPP_NOEXCEPT
    {
      this->get() = value;
    }

    void destroy() CPP_NOEXCEPT
    {}
  };

  #if __cplusplus >= 201103L
  CPP_GLOBAL_CONSTEXPR CPP_EMPTY_CLASS(emplace_t) emplace;
  #endif

  template <typename T, std::size_t N>
  struct memory_stack<T[N], false>
  : memory_stack_base<T[N]>
  {
    typedef typename memory_stack_base<T[N]>::type type;
    typedef typename memory_stack_base<T[N]>::memory_type memory_type;


    template<class CPP_PACK Args>
    void construct(Args CPP_RVALUE CPP_PACK args)
    CPP_NOEXCEPT_OPERATOR2(T(std::declval<Args>()...))
    {
      std::size_t i = 0;
      try
      {
        T * p = this->address();
        for (; i != N; ++i, ++p)
          new (p) T(FALCON_FORWARD(Args, args)CPP_PACK);
      }
      catch (...)
      {
        destroy_n(i);
        throw;
      }
    }

  #if __cplusplus >= 201103L
    void construct(const emplace_t&)
    CPP_NOEXCEPT_OPERATOR2(construct())
    {
      construct();
    }
  #endif

  private:
    void destroy_n(std::size_t i) CPP_NOEXCEPT
    {
      T * p = this->address();
      while (i)
        p[--i].~T();
    }

  #if __cplusplus >= 201103L
    template<class U, typename... Args>
    void priv_construct(std::size_t& n, T * p, U&& a, Args&&... args)
    CPP_NOEXCEPT_OPERATOR2(
      void(T(std::forward<U>(a))),
      priv_construct(std::declval<std::size_t&>(), nullptr, std::declval<Args>()...)
    )
    {
      new (p) T(std::forward<U>(a));
      priv_construct(++n, p+1, std::forward<Args>(args)...);
    }

    void priv_construct(std::size_t& n, T * p)
    CPP_NOEXCEPT_OPERATOR2(T())
    {
      for (; n != N; ++n, ++p)
        new (p) T();
    }

  public:
    template<class... Args>
    void construct(const emplace_t&, Args&&... args)
    CPP_NOEXCEPT_OPERATOR2(priv_construct(
      std::declval<std::size_t&>(), nullptr, std::declval<Args>()...
    ))
    {
      std::size_t i = 0;
      try
      {
        priv_construct(i, this->address(), std::forward<Args>(args)...);
      }
      catch (...)
      {
        destroy_n(i);
        throw;
      }
    }
  #else
  public:
  #endif

    void destroy() CPP_NOEXCEPT
    {
      destroy_n(N);
    }
  };

  template <typename T, std::size_t N>
  struct memory_stack<T[N], true>
  : memory_stack_base<T[N]>
  {
  public:
    typedef typename memory_stack_base<T[N]>::type type;
    typedef typename memory_stack_base<T[N]>::memory_type memory_type;


  #if __cplusplus >= 201103L
    template<class... Args>
    void construct(Args&&... args)
    noexcept(noexcept(T(std::forward<Args>(args)...)))
    {
      T* p = this->address();
      for (std::size_t i = 0; i != N; ++i, ++p)
        new (p) T{std::forward<Args>(args)...};
    }
  #endif

    template<class U>
    void construct(const U& value)
    CPP_NOEXCEPT_OPERATOR2(this->get()[0] = value)
    {
      for (std::size_t i = 0; i != N; ++i)
        this->get()[i] = value;
    }

  #if __cplusplus >= 201103L
  private:
    template<class U, typename... Args>
    void priv_construct(std::size_t n, T* p, U&& a, Args&&... args)
    CPP_NOEXCEPT_OPERATOR2(
      void(T(std::forward<U>(a))),
      priv_construct(0, nullptr, std::declval<Args>()...)
    )
    {
      new (p) T(std::forward<U>(a));
      priv_construct(n+1, p+1, std::forward<Args>(args)...);
    }

    void priv_construct(std::size_t n, T* p = 0)
    CPP_NOEXCEPT_OPERATOR2(T())
    {
      for (; n != N; ++n, ++p)
        new (p) T();
    }

  public:
    template<class... Args>
    void construct(const emplace_t&, Args&&... args)
    CPP_NOEXCEPT_OPERATOR2(priv_construct(0, nullptr, std::declval<Args>()...))
    {
      priv_construct(0, this->address(), std::forward<Args>(args)...);
    }
  #endif

    void destroy() CPP_NOEXCEPT
    {}
  };
}

/**
 * \brief Reserve memory in the stack.
 * \attention The internal object is not automatically destroy.
 */
template<class T>
struct memory_stack
: aux_::memory_stack<T>
{
	typedef typename aux_::memory_stack<T>::type type;
	typedef typename aux_::memory_stack<T>::memory_type memory_type;
	typedef typename aux_::memory_stack<T>::pointer pointer;
	typedef typename aux_::memory_stack<T>::const_pointer const_pointer;

	using aux_::memory_stack<T>::get;
	using aux_::memory_stack<T>::data;
	using aux_::memory_stack<T>::address;
	using aux_::memory_stack<T>::construct;
	using aux_::memory_stack<T>::destroy;
};

}

#endif
