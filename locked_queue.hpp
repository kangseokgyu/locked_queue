#ifndef _LOCKED_QUEUE_HPP_
#define _LOCKED_QUEUE_HPP_

#include <mutex>
#include <queue>

#include "optional.hpp"

namespace jdi {

template <class T> //
class locked_queue {
private:
  std::queue<T> q_;
  std::recursive_mutex lock_;

public:
  locked_queue();
  ~locked_queue();

  void push(const T &e);
  tl::optional<T> pop();
};

template <class T> locked_queue<T>::locked_queue() {}

template <class T> locked_queue<T>::~locked_queue() {}

template <class T> void locked_queue<T>::push(const T &e) {
  std::lock_guard<std::recursive_mutex> guard(lock_);
  q_.push(std::move(e));
}

template <class T> tl::optional<T> locked_queue<T>::pop() {
  std::lock_guard<std::recursive_mutex> guard(lock_);
  if (q_.empty()) {
    return tl::nullopt;
  }

  auto ret = std::move(q_.front());
  q_.pop();
  return tl::make_optional(ret);
}

} // namespace jdi

#endif /* _LOCKED_QUEUE_HPP_ */
