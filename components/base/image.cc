#include "component.hh"
#include "base64.cc"

namespace foundation {
  struct image_props {
    std::shared_ptr<Ref> ref = nullptr;
    std::shared_ptr<Styling> style;

    short real_width = 0;
    short real_height = 0;
  };

  class Image final : public Component {
        image_props props;
        const std::string* base64_source = nullptr;
    lv_img_dsc_t img_dsc;
    public:
        explicit Image(const lv_img_dsc_t source, const image_props& props)
          : Component(nullptr, nullptr) {
        this->props = props;
        set_style(props.style);

        this->img_dsc = source;

        if(this->props.ref != nullptr) {
            this->props.ref->set(this);
          }
      }

      ~Image() override = default;

        lv_obj_t* render() override {
          if (get_component() == nullptr || this->parent == nullptr) {
              this->set_component(this->create_initial(this->parent));
          }

          lv_obj_t* comp = get_component();
          lv_img_set_src(comp, &this->img_dsc);
          lv_obj_align(comp, LV_ALIGN_CENTER, 0, 0);



          std::shared_ptr<Styling> style = this->styling();

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

        Image* append(lv_obj_t *obj) override {
            lv_obj_set_parent(obj, get_component());
            return this;
        }

        lv_obj_t* create_initial(lv_obj_t* parental) {
            return lv_img_create(parental);
        }
  };

}