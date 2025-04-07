#ifndef TEXTINPUT_HH
#define TEXTINPUT_HH


#include "keyboard_manager.cc"
#include "component.hh"

namespace base_widgets {
    class KeyboardManager;

    struct textinput_events {
        lv_event_cb_t on_click = nullptr;
        lv_event_cb_t on_focused = nullptr;
        lv_event_cb_t on_defocused = nullptr;
        lv_event_cb_t on_value_changed = nullptr;
    };

    struct textinput_props {
        const char* placeholder = nullptr;
        std::shared_ptr<Styling> style;
        textinput_events events;
        bool show_keyboard = true;
    };

    class TextInput final : public Component {
    private:
        const textinput_props* props;
        mutable lv_obj_t* keyboard = nullptr;
        base_widgets::KeyboardManager* kbManager{};

        ~TextInput() override {
            delete props;
        };

    public:
        explicit TextInput(lv_obj_t* parent, const textinput_props* props, base_widgets::KeyboardManager* kbManager = nullptr)
            : Component(lv_textarea_create(parent), parent), props(props) {}

        lv_obj_t* render() override {
            lv_obj_t* obj = get_component();

            lv_textarea_set_one_line(obj, true);
            lv_textarea_set_placeholder_text(obj, props->placeholder);

            const auto& e = props->events;

            if (e.on_click)          lv_obj_add_event_cb(obj, e.on_click, LV_EVENT_CLICKED, nullptr);
            if (e.on_focused)        lv_obj_add_event_cb(obj, e.on_focused, LV_EVENT_FOCUSED, nullptr);
            if (e.on_defocused)      lv_obj_add_event_cb(obj, e.on_defocused, LV_EVENT_DEFOCUSED, nullptr);
            if (e.on_value_changed)  lv_obj_add_event_cb(obj, e.on_value_changed, LV_EVENT_VALUE_CHANGED, nullptr);

            if (kbManager && props->show_keyboard) {
                lv_obj_add_event_cb(obj, [](lv_event_t* e) {
                    _lv_obj_t* ta = lv_event_get_target(e);
                    KeyboardManager* kbMgr = static_cast<KeyboardManager*>(lv_event_get_user_data(e));
                    kbMgr->attach(ta);
                }, LV_EVENT_FOCUSED, kbManager);

                lv_obj_add_event_cb(obj, [](lv_event_t* e) {
                    auto kbMgr = static_cast<KeyboardManager*>(lv_event_get_user_data(e));
                    kbMgr->hide();
                }, LV_EVENT_DEFOCUSED, kbManager);
            }

            return obj;
        }

        std::shared_ptr<Styling> styling() override {
            return props->style;
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

} // namespace base_widgets

#endif // TEXTINPUT_HH
