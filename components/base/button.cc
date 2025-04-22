#ifndef BUTTON_HH
#define BUTTON_HH

#include "component.hh"
#include "esp_log.h"
#include <functional>
#include <utility>

namespace foundation {
static void event_adapter(lv_event_t *event);

struct button_props {
  std::shared_ptr<Ref> ref = nullptr;
  std::shared_ptr<Styling> style;

  std::string text;
  std::function<void(lv_event_t *)> on_click = nullptr;
  std::function<void(lv_event_t *)> on_long_press = nullptr;
  std::function<void(lv_event_t *)> on_pressed = nullptr;
  std::function<void(lv_event_t *)> on_released = nullptr;
  std::function<void(lv_event_t *)> on_focused = nullptr;
  std::function<void(lv_event_t *)> on_defocused = nullptr;
};

class Button : public Component {
private:
  lv_obj_t *label = nullptr;

public:
  button_props props;

  ~Button() override = default;

  explicit Button(const button_props &props)
    : Component(nullptr, nullptr) {
    this->props = props;

    if (this->props.ref != nullptr) {
      this->props.ref->set(this);
    }

  }

  lv_obj_t *render() override {
    lv_obj_t *parent_obj = this->get_parent();
    if (!parent_obj)
      return nullptr;
    set_component(lv_btn_create(parent_obj));

    auto *obj = this->get_component();

    if (!this->props.text.empty()) {
      this->label = lv_label_create(obj);
    }

    if (!props.text.empty()) {
      lv_label_set_text(this->label, props.text.c_str());
    }
    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_add_event_cb(obj, event_adapter, LV_EVENT_CLICKED, this);
    lv_obj_add_event_cb(obj, event_adapter, LV_EVENT_PRESSED, this);
    lv_obj_add_event_cb(obj, event_adapter, LV_EVENT_RELEASED, this);
    lv_obj_add_event_cb(obj, event_adapter, LV_EVENT_LONG_PRESSED, this);

    return obj;
  }

  std::shared_ptr<Styling> styling() override {
    if (this->props.style) {
        return this->props.style;
    }
    return {};
  }

  Button *append(lv_obj_t *obj) override {
    lv_obj_set_parent(obj, get_component());
    return this;
  }
};

static void event_adapter(lv_event_t *event) {
  auto *instance = static_cast<Button *>(lv_event_get_user_data(event));
  if (!instance)
    return;

  const auto &events = instance->props;

  switch (event->code) {
  case LV_EVENT_CLICKED:
    if (events.on_click)
      events.on_click(event);
    break;
  case LV_EVENT_LONG_PRESSED:
    if (events.on_long_press)
      events.on_long_press(event);
    break;
  case LV_EVENT_PRESSED:
    if (events.on_pressed)
      events.on_pressed(event);
    break;
  case LV_EVENT_RELEASED:
    if (events.on_released)
      events.on_released(event);
    break;
  case LV_EVENT_FOCUSED:
    if (events.on_focused)
      events.on_focused(event);
    break;
  case LV_EVENT_DEFOCUSED:
    if (events.on_defocused)
      events.on_defocused(event);
    break;
  default:
    ESP_LOGW("button", "Unknown event code %d", event->code);
  }
}

} // namespace foundation

#endif // BUTTON_HH