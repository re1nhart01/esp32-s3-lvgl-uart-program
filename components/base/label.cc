#ifndef LABEL_HH
#define LABEL_HH

#include "component.hh"

namespace foundation {

    struct label_events {
        lv_event_cb_t on_click = nullptr;
        lv_event_cb_t on_long_press = nullptr;
        lv_event_cb_t on_pressed = nullptr;
        lv_event_cb_t on_released = nullptr;
        lv_event_cb_t on_focused = nullptr;
        lv_event_cb_t on_defocused = nullptr;
    };

    struct label_props {
        std::shared_ptr<Ref> ref = nullptr;
        std::shared_ptr<Styling> style;

        std::string text;
        label_events events;
    } typedef label_props;

    class Label final : public Component {
    private:
    public:
        label_props props;

        explicit Label(const label_props& props)
            : Component(nullptr, nullptr) {
            this->props = props;
            this->parent = nullptr;

            if (this->props.ref != nullptr) {
                this->props.ref->set(this);
            }

        }

        ~Label() override = default;

        lv_obj_t* render() override {
            lv_obj_t* parent_obj = this->get_parent();
            if (!parent_obj) return nullptr;
            set_component(lv_label_create(parent_obj));

            auto* obj = this->get_component();

            lv_label_set_text(obj, props.text.c_str());



            const auto& e = props.events;

            if (e.on_click)       lv_obj_add_event_cb(obj, e.on_click, LV_EVENT_CLICKED, nullptr);
            if (e.on_long_press)  lv_obj_add_event_cb(obj, e.on_long_press, LV_EVENT_LONG_PRESSED, nullptr);
            if (e.on_pressed)     lv_obj_add_event_cb(obj, e.on_pressed, LV_EVENT_PRESSED, nullptr);
            if (e.on_released)    lv_obj_add_event_cb(obj, e.on_released, LV_EVENT_RELEASED, nullptr);
            if (e.on_focused)     lv_obj_add_event_cb(obj, e.on_focused, LV_EVENT_FOCUSED, nullptr);
            if (e.on_defocused)   lv_obj_add_event_cb(obj, e.on_defocused, LV_EVENT_DEFOCUSED, nullptr);

            return obj;
        }

        std::shared_ptr<Styling> styling() override {
            return props.style;
        }

        Label* append(lv_obj_t* obj) override {
            lv_obj_set_parent(obj, get_component());
            return this;
        }
    };

} // namespace foundation

#endif // LABEL_HH
