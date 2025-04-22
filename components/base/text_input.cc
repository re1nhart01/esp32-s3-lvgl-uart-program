#ifndef TEXTINPUT_HH
#define TEXTINPUT_HH

#pragma once

#include "keyboard_manager.cc"
#include "component.hh"
#include <functional>
#include <string>

namespace foundation {
    class KeyboardManager;

    struct textinput_props {
        std::shared_ptr<Ref> ref = nullptr;
        std::shared_ptr<Styling> style;

        const char* placeholder = nullptr;
        lv_event_cb_t on_click = nullptr;
        lv_event_cb_t on_focused = nullptr;
        lv_event_cb_t on_defocused = nullptr;
        lv_event_cb_t on_value_changed = nullptr;
        std::function<void(std::string value)> on_submit = nullptr;
    };

    class TextInput final : public Component {
    protected:
        mutable lv_obj_t* keyboard = nullptr;
        KeyboardManager* kbManager;

    public:
        textinput_props props;

        explicit TextInput(const textinput_props& props,
                           KeyboardManager *kbManager = nullptr)
            : Component(nullptr, nullptr)
        {
          this->props = props;
          this->kbManager = kbManager;

          if (this->props.on_submit != nullptr) {
              this->kbManager->attach_on_submit_event(this->props.on_submit);
          }

          if (this->props.ref != nullptr) {
              this->props.ref->set(this);
          }
        }

        ~TextInput() override = default;

        lv_obj_t* render() override {
            lv_obj_t *parent_obj = this->get_parent();
            if (!parent_obj)
                return nullptr;
            set_component(lv_textarea_create(parent_obj));

            lv_obj_t* obj = this->get_component();

            lv_textarea_set_one_line(obj, true);
            lv_textarea_set_placeholder_text(obj, props.placeholder);



            const auto& e = props;

            if (e.on_click)          lv_obj_add_event_cb(obj, e.on_click, LV_EVENT_CLICKED, nullptr);
            if (e.on_focused)        lv_obj_add_event_cb(obj, e.on_focused, LV_EVENT_FOCUSED, nullptr);
            if (e.on_defocused)      lv_obj_add_event_cb(obj, e.on_defocused, LV_EVENT_DEFOCUSED, nullptr);
            if (e.on_value_changed)  lv_obj_add_event_cb(obj, e.on_value_changed, LV_EVENT_VALUE_CHANGED, nullptr);

            if (kbManager != nullptr) {
                lv_obj_add_event_cb(obj, [](lv_event_t* e) {
                    _lv_obj_t* ta = lv_event_get_target(e);
                    auto* instance = static_cast<TextInput*>(lv_event_get_user_data(e));

                    if (instance->kbManager != nullptr) {
                        instance->kbManager->create(lv_scr_act());
                    }

                    if (instance->props.on_submit != nullptr) {
                        instance->kbManager->attach_on_submit_event(instance->props.on_submit);
                    }
                    instance->kbManager->attach(ta);
                }, LV_EVENT_FOCUSED, this);

                lv_obj_add_event_cb(obj, [](lv_event_t* e) {
                    auto* instance = static_cast<TextInput*>(lv_event_get_user_data(e));

                  // if (instance->props.on_submit != nullptr) {
                  //     instance->kbManager->detach_on_submit_event(instance->props.on_submit);
                  // }

                    instance->kbManager->hide();
                }, LV_EVENT_DEFOCUSED, this);
            }

            return obj;
        }

        std::shared_ptr<Styling> styling() override {
          if (this->props.style) {
              return this->props.style;
          }
          return {};
        }

        TextInput* append(lv_obj_t* obj) override {
            lv_obj_set_parent(obj, get_component());
            return this;
        }

        const char* get_text() const {
            return lv_textarea_get_text(get_component());
        }

        void set_text(const char* txt) const {
            lv_textarea_set_text(get_component(), txt);
        }
    };

} // namespace foundation

#endif // TEXTINPUT_HH
