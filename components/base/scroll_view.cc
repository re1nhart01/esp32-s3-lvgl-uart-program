//
// Created by evgeniy on 3/29/25.
//

#pragma once

#ifndef VIEW_HH
#define VIEW_HH

#include "component.hh"
#include "../lvgl__lvgl/demos/lv_demos.h"
#include <memory>
#include <vector>

extern "C" {
    #include "waveshare_rgb_lcd_port.h"
    #include "sdkconfig.h"
}

//LV_DIR_HOR чи LV_DIR_ALL

namespace foundation {

struct scroll_view_props {
    std::shared_ptr<Ref> ref = nullptr;
    std::shared_ptr<Styling> style;

    std::vector<std::shared_ptr<Component>> children;
    short width = LV_PCT(100);
    short height = LV_SIZE_CONTENT;
    lv_flex_align_t justify_content = LV_FLEX_ALIGN_START;
    lv_flex_align_t align_items = LV_FLEX_ALIGN_CENTER;
    lv_flex_align_t track_cross_place = LV_FLEX_ALIGN_START;
    lv_flex_flow_t flex_direction = LV_FLEX_FLOW_COLUMN;

    bool horizontal = false;
    bool disabled = false;
};


    class ScrollView final : public Component {
        scroll_view_props props;
        std::vector<std::shared_ptr<Component>> children;
    public:
        explicit ScrollView(lv_obj_t *parent, const scroll_view_props& props)
            : Component(this->create_initial(parent), parent)
        {
            this->props = props;
            set_style(props.style);
            if (!props.children.empty()) {
                this->children.insert(this->children.end(), props.children.begin(), props.children.end());
            }

            if (this->props.ref != nullptr) {
                this->props.ref->set(this);
            }
        }

        ~ScrollView() override = default;

        lv_obj_t* render() override {
            if (get_component() == nullptr || this->parent == nullptr) {
                this->set_component(this->create_initial(this->parent));
            }
            lv_obj_t* comp = get_component();
            lv_obj_set_layout(comp, LV_LAYOUT_FLEX);
            lv_obj_set_size(comp, props.width, props.height);
            lv_obj_set_flex_flow(comp, props.flex_direction);
            lv_obj_set_flex_align(comp, props.justify_content, props.align_items, props.track_cross_place);

            lv_obj_set_scroll_dir(comp, props.horizontal ? LV_DIR_HOR : LV_DIR_VER);
            lv_obj_set_scrollbar_mode(comp, props.disabled ? LV_SCROLLBAR_MODE_OFF : LV_SCROLLBAR_MODE_ACTIVE);



            std::shared_ptr<Styling> style = this->styling();

            for (const auto& child : this->children) {
                const std::shared_ptr<Component>& component_children  = child;
                if (component_children != nullptr) {
                    child->set_active(true);
                    child->set_parent(comp);
                    child->render();

                    lv_obj_set_parent(component_children->get_component(), comp);
                }
            }

            if (style != nullptr) {
                lv_obj_add_style(this->get_component(), style->getStyle(), LV_PART_MAIN);
            }

            return comp;
        }

        std::shared_ptr<Styling> styling() override {
          if (this->props.style) {
              return this->props.style;
          }
          return {};
        }

        ScrollView* append(lv_obj_t *obj) override {
            lv_obj_set_parent(obj, get_component());
            return this;
        }

        lv_obj_t* create_initial(lv_obj_t* parental) {
            return lv_obj_create(parental);
        }
    };





} // namespace foundation

#endif //VIEW_HH
