#include <utility>

#include "circular_progress.hh"

#include "component.hh"
#include "macro.hh"

namespace foundation {
  CircularProgress::CircularProgress(circular_props  props)
      : Component(nullptr, nullptr), props(std::move(props)) {
    this->parent = nullptr;


    this->is_show_label = props.show_label_default;

    if (this->props.ref != nullptr) {
        this->props.ref->set(this);
    }
  }

  lv_obj_t* CircularProgress::render() {
    lv_obj_t* parent_obj = this->get_parent();
    if (!parent_obj) return nullptr;

    auto props = this->props;

    this->set_component(lv_arc_create(parent_obj));
    const auto arc = this->get_component();

    lv_arc_set_range(arc, props.min_dy, props.max_dy);             // Диапазон значений (например, SpO₂)
    lv_arc_set_value(arc, props.default_dy);                 // Значение кислорода
    lv_obj_clear_flag(arc, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_bg_opa(arc, LV_OPA_TRANSP, 0);
    lv_arc_set_bg_angles(arc, 135, 45);        // Отображать полукруг
    lv_arc_set_rotation(arc, 0);             // Начало сверху
    lv_obj_set_size(arc, props.w, props.h);

    lv_obj_remove_style(arc, nullptr, LV_PART_KNOB);
    lv_obj_clear_flag(arc, LV_OBJ_FLAG_CLICKABLE);  // Не кликабельный

    if (style != nullptr) {
        lv_obj_add_style(this->get_component(), this->styling()->getStyle(), LV_PART_MAIN);
    }

    if (this->is_show_label) {
        this->label = $label(label_props{
          .text = "100%",
        });

        this->label->set_parent(arc);
        this->label->render();

        lv_obj_align_to(this->label->get_component(), arc, LV_ALIGN_CENTER, 0, 0);
    }

    return arc;
  }

  void CircularProgress::show_label(const bool value) const {

  };

  void CircularProgress::update(const short value) const {
    if (const auto arc = this->get_component(); arc != nullptr) {
        const short correct_value =
         value < this->props.min_dy ?
          this->props.min_dy :
          value > this->props.max_dy ?
          this->props.max_dy : value;
      lv_arc_set_value(arc, correct_value);
      if (this->is_show_label) {
          this->label->update(std::format("{}{}", value, this->props.label_symbol));
      }
    }

  };

  std::shared_ptr<Styling> CircularProgress::styling() {
    if (this->props.style != nullptr) {
        lv_style_set_arc_color(this->props.style->getStyle(), lv_color_hex(0x000000));
    }
    return this->props.style;
  }

  CircularProgress* CircularProgress::append(lv_obj_t* obj) {
    lv_obj_set_parent(obj, get_component());
    return this;
  }

} // namespace foundation
