#include "lvgl.h"
#include "component.hh"
#include <vector>
/*
*   row animation
    // When move finished, start zoom
    lv_anim_set_ready_cb(&a, [](lv_anim_t* a){
        lv_obj_t* obj = static_cast<lv_obj_t*>(a->var);

        // Start zoom animation
        lv_anim_t zoom;
        lv_anim_init(&zoom);
        lv_anim_set_var(&zoom, obj);
        lv_anim_set_time(&zoom, zoom_config.duration);
        lv_anim_set_values(&zoom, zoom_config.start_value, zoom_config.end_value);
        lv_anim_set_path_cb(&zoom, zoom_config.path_cb);
        lv_anim_set_exec_cb(&zoom, [](void* obj, int32_t v) {
            lv_obj_set_style_transform_zoom(static_cast<lv_obj_t*>(obj), v, LV_PART_MAIN);
        });

        // When zoom finished, start opacity animation
        lv_anim_set_ready_cb(&zoom, [](lv_anim_t* a){
            lv_obj_t* obj = static_cast<lv_obj_t*>(a->var);

            // Start opacity animation
            lv_anim_t fade;
            lv_anim_init(&fade);
            lv_anim_set_var(&fade, obj);
            lv_anim_set_time(&fade, opacity_config.duration);
            lv_anim_set_values(&fade, opacity_config.start_value, opacity_config.end_value);
            lv_anim_set_path_cb(&fade, opacity_config.path_cb);
            lv_anim_set_exec_cb(&fade, [](void* obj, int32_t v) {
                lv_obj_set_style_opa(static_cast<lv_obj_t*>(obj), v, LV_PART_MAIN);
            });

            lv_anim_start(&fade);
        });

        lv_anim_start(&zoom);
    });
 *
 *to make parallel animations, just call few animation together
 *
 */

// type_anim:
// 0 - default single animation, list of animation configs could be empty or nullptr
// 1 - parallel animations
// 2 - row animations

namespace foundation::animated {
  enum animation_type {
    single_animation = 0xff,
    parallel_animation = 0xf1,
    chained_animation = 0xf2,
  };

  struct animated_config {
    int32_t start_value = 0;
    int32_t end_value = 0;
    uint32_t duration = 500;
    uint32_t playback_duration = 0;
    uint32_t delay = 0;
    int32_t repeat_count = LV_ANIM_REPEAT_INFINITE;
    lv_anim_path_cb_t path_cb = lv_anim_path_linear;

    enum class Property {
      X, Y, Opacity, Zoom, Rotation
  } property = Property::X;
  };

  struct animated_sub_config {
    animation_type type_anim = animation_type::single_animation;
    std::vector<animated_config> configs = {};
  };


  class Animated : public Component {
    private:
      std::unique_ptr<lv_anim_t> reference;
      std::unique_ptr<Component> component;
      animated_config* config;
      animated_sub_config* sub_config;
    public:
    ~Animated() override = default;
    explicit Animated(Component& component, animated_config* config, animated_sub_config* sub_config) {
      this->config = config;
      this->sub_config = sub_config;
      this->component = std::make_unique<Component>(component);
      this->reference = std::make_unique<lv_anim_t>();
      lv_anim_init(this->reference.get());
    }


    lv_obj_t* render() override {
      const auto obj = this->create_initial(this->parent);

      const auto ref = this->reference.get();
      lv_anim_set_var(this->reference.get(), obj);

      lv_anim_set_time(ref, this->config->duration); // duration 1 sec
      lv_anim_set_values(ref, this->config->start_value, this->config->end_value); // move from -50 to +50
      lv_anim_set_playback_time(ref, this->config->playback_duration); // reverse back
      lv_anim_set_repeat_count(ref, this->config->repeat_count);

      switch (this->config->property) {
        case animated_config::Property::X:
          this->make_move_x_animation();
        break;

        case animated_config::Property::Y:
          this->make_move_y_animation();
        break;

        case animated_config::Property::Opacity:
          this->make_opacity_animation();
        break;

        case animated_config::Property::Rotation:
          this->make_rotation_animation();
        break;

        case animated_config::Property::Zoom:
          this->make_zoom_animation();
        break;
      }

      lv_anim_start(ref);
      return obj;
    }

    void make_move_y_animation() const {
      lv_anim_set_exec_cb(this->reference.get(), [](void* obj, int32_t v) {
          lv_obj_set_y(static_cast<lv_obj_t*>(obj), static_cast<int16_t>(v));
      });

    }

    void make_move_x_animation() const {
      lv_anim_set_exec_cb(this->reference.get(), [](void* obj, int32_t v) {
          lv_obj_set_x(static_cast<lv_obj_t*>(obj), static_cast<int16_t>(v));
      });

    }

    void make_opacity_animation() const {
      lv_anim_set_exec_cb(this->reference.get(), [](void* obj, int32_t opa) {
          lv_obj_set_style_opa(static_cast<lv_obj_t*>(obj), opa, LV_PART_MAIN);
      });
    }

    void make_zoom_animation() const {
      lv_anim_set_exec_cb(this->reference.get(), [](void* obj, int32_t zoom) {
          lv_obj_set_style_transform_zoom(static_cast<lv_obj_t*>(obj), static_cast<int16_t>(zoom), LV_PART_MAIN);
      });
    }

    void make_rotation_animation() const {
      lv_anim_set_exec_cb(this->reference.get(), [](void* obj, int32_t angle) {
          lv_img_set_angle(static_cast<lv_obj_t*>(obj), static_cast<int16_t>(angle));
      });
    }

    std::shared_ptr<Styling> styling() override {
      return {};
    }

    Animated* append(lv_obj_t *obj) override {
      lv_obj_set_parent(obj, get_component());
      return this;
    }

    lv_obj_t* create_initial(lv_obj_t* parental) {
      this->set_parent(parental);
      return this->component->render();
    }
  };
}



