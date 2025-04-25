#include "ref.hh"

#include <string>
#include <unordered_map>
#include <utility>
#include "config.hh"

#pragma once

namespace foundation {
  class References {
  private:
    std::string name;
    std::unordered_map<std::string, Ref*> storage;

    References() : name(APP_STORAGE_NAME) {};
    explicit References(std::string  name) : name(std::move(name)) {
      this->storage = std::unordered_map<std::string, Ref*>();
    }
    ~References() {
      for (auto& [key, ref] : storage) {
          delete ref;
      }
    };
  public:
    References& operator=(const References&) = delete;

    void set(const std::string& name, const Component* component) {
      auto ref = new Ref(name);
      ref->set(const_cast<Component*>(component));

      if (this->storage.find(name) != this->storage.end()) {
          this->del(name);
      }

      this->storage[name] = ref;
    }

    bool del(const std::string& name) {
      const auto ref_get = this->storage.find(name);
      const bool exists = ref_get != this->storage.end();

      if (exists) {
          if (auto ref = ref_get->second; ref != nullptr) {
              delete ref;
            }
        }
      this->storage.erase(name);
      return exists;
    }

    Ref* get(const std::string& name) const {
      auto ref_get = this->storage.find(name);
      return ref_get->second;
    }

#if REFERENCE_STORE_SINGLETON
    static References& instance() {
      static References instance;
      return instance;
    }
#endif
  };
}