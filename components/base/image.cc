#include "component.hh"
#include "base64.cc"

namespace base_widgets {
  struct image_props {
    std::shared_ptr<Ref> ref = nullptr;
    std::shared_ptr<Styling> style;

  };

  class Image final : public Component {
        image_props props;
        const std::string& base64_source;

    public:
        explicit Image(const std::string& base64, const image_props &props)
          : base64_source(base64) {
        this->props = props;
        set_style(props.style);

        if(this->props.ref != nullptr) {
            this->props.ref->set(this);
          }
      }

      explicit Image(const image_props &props)
          : Component(nullptr, nullptr), base64_source("") {
        this->props = props;
        set_style(props.style);

        if(this->props.ref != nullptr) {
            this->props.ref->set(this);
          }
      }

      ~Image() override = default;

        lv_obj_t* render() override {
            if (get_component() == nullptr || this->parent == nullptr) {
                this->set_component(this->create_initial(this->parent));
            }

          std::string decoded_string  = base64_decode(this->base64_source);

          lv_obj_t* img = lv_img_create(lv_scr_act());
          lv_img_set_src(img, decoded_string.data());
          lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);

          lv_obj_t* comp = get_component();


          std::shared_ptr<Styling> style = this->styling();

          if (style != nullptr) {
              lv_obj_add_style(this->get_component(), style->getStyle(), LV_PART_MAIN);
          }

            return comp;
        }

        std::shared_ptr<Styling> styling() override {
            if (this->props.style)
                return this->props.style;
            return {};
        }

        Image* append(lv_obj_t *obj) override {
            lv_obj_set_parent(obj, get_component());
            return this;
        }

        lv_obj_t* create_initial(lv_obj_t* parental) {
            return lv_img_create(parental);
        }
  };

}