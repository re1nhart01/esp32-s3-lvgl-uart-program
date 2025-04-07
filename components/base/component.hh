//
// Created by evgeniy on 3/29/25.
//
#pragma once

#include <memory>
#include "ref.hh"

#include "base_widget.hh"


extern "C" {
#include "lv_demos.h"
#include "lvgl_port.h"
}




namespace base_widgets {
  class Component {
    protected:
        std::shared_ptr<Styling> style;
        lv_obj_t* component = nullptr;
        std::shared_ptr<Component> renderer_view = nullptr;
        lv_obj_t* parent = nullptr;
        Ref* ref = nullptr;

    public:
        virtual ~Component() = default;

        // ✅ Базовий конструктор — дозволяє створити компонент без LVGL-об'єкта
        Component() {
            this->style = std::make_shared<Styling>();
        }

        explicit Component(lv_obj_t* obj, lv_obj_t* parent)
            : component(obj), parent(parent) {
            this->style = std::make_shared<Styling>();
        }

        // virtual void on_mount() = 0;
        // virtual void on_unmount() = 0;

        virtual lv_obj_t* render() = 0;
        virtual std::shared_ptr<Styling> styling() = 0;
        virtual Component* append(lv_obj_t* obj) = 0;

        lv_obj_t* get_component() const {
            return this->component;
        }

        lv_obj_t* set_component(lv_obj_t* v) {
            this->component = v;
            return this->component;
        }

        lv_obj_t* get_parent() const {
            return this->parent;
        }

        void set_parent(lv_obj_t* parent_link) {
            this->parent = parent_link;
        }

        void set_active(bool active) const {
            if (this->component != nullptr) {
                if (active)
                    lv_obj_clear_flag(this->component, LV_OBJ_FLAG_HIDDEN);
                else
                    lv_obj_add_flag(this->component, LV_OBJ_FLAG_HIDDEN);
            }
        }

        void set_style(const std::shared_ptr<Styling>& newStyle) {
            this->style = newStyle;
            if (this->component && this->style) {
                lv_obj_add_style(this->component, this->style->getStyle(), 0);
            }
        }

        std::shared_ptr<Styling> get_style() const {
            return this->style;
        }

        // 🛡 Безпечний хелпер
        bool is_ready() const {
            return this->component != nullptr;
        }
    };
}
