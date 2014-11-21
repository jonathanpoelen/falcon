#ifndef FALCON_NONCOPYABLE_HPP
#define FALCON_NONCOPYABLE_HPP

namespace falcon {

struct noncopyable {
  noncopyable() = default;
  noncopyable(noncopyable const &) = delete;
  noncopyable & operator=(noncopyable const &) = delete;
};

struct noncopyable_but_movable {
  noncopyable_but_movable() = default;
  noncopyable_but_movable(noncopyable_but_movable &&) = default;
  noncopyable_but_movable(noncopyable_but_movable const &) = delete;
  noncopyable_but_movable & operator=(noncopyable_but_movable &&) = default;
  noncopyable_but_movable & operator=(noncopyable_but_movable const &) = delete;
};

}

#endif
