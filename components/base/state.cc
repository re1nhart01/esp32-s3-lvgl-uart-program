#include <callback.hh>
#ifndef STATE_HH
#define STATE_HH

#include <functional>

namespace foundation {
template <typename T, int MaxListeners = 8>
class State {
  T value;
  std::function<void(const T &)> listeners[MaxListeners];
  int count = 0;

public:
  explicit State(const T &initial) : value(initial) {
  }

  const T &get() const { return value; }

  void set(const T &newValue) {
    if (newValue != value) {
      value = newValue;
      for (int i = 0; i < count; i++) {
        if (listeners[i])
          listeners[i](value);
      }
    }
  }

  void subscribe(std::function<void(const T &)> cb) {
    if (count < MaxListeners) {
      listeners[count++] = std::move(cb);
    }
  }
};
} // namespace base_widgets

#endif // STATE_HH