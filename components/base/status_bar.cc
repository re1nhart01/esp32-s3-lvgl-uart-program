#include <memory>

#include "ref.hh"
#include "styling.hh"
#include "component.hh"
#include "macro_component.cc"
#include "view.cc"
#include "label.cc"

namespace foundation {
    struct status_bar_props {
        std::shared_ptr<Ref> ref = nullptr;
        std::shared_ptr<Styling> style;
    };

    class StatusBar final : public Component {
    public:
        status_bar_props props;

        ~StatusBar() override = default;
        explicit StatusBar(const status_bar_props& props)
            : Component(nullptr, nullptr) {
            this->props = props;
            this->parent = nullptr;

            if (this->props.ref != nullptr) {
                this->props.ref->set(this);
            }

        }


        lv_obj_t* render() override {
            std::shared_ptr<Styling> styleV = this->styling();

            auto layout = $view(
            this->parent,
            view_props{
              .ref = nullptr,
              .style = styleV,
              .children = {
                $view(nullptr, view_props{ .width = 0 }),
                $label(label_props{
                  .ref = nullptr,
                  .style = nullptr,
                  .text = "00:00",
                }),
                $view(nullptr, view_props{ .width = 0 }),
              },
              .width = LV_PCT(100),
              .height = 24,
              .justify_content = LV_FLEX_ALIGN_SPACE_BETWEEN,
              .align_items = LV_FLEX_ALIGN_CENTER,
              .track_cross_place = LV_FLEX_ALIGN_CENTER,
              .flex_direction = LV_FLEX_FLOW_ROW,
            });

          this->renderer_view = layout;
          this->renderer_view->set_parent(this->parent);
          this->set_component(layout->render());

          return layout->get_component();
        }

        std::shared_ptr<Styling> styling() override {
            this->style = std::make_shared<Styling>();

            this->style->setBackgroundColor(lv_color_hex(0x303030));
            this->style->setTextColor(lv_color_make(255, 255, 255));
            this->style->setPadding(0, 0, 16, 16);
            this->style->setBorder(lv_color_make(0, 0, 0), 0, 0);
            this->style->setFont(&lv_font_montserrat_12);
            this->style->setBorderRadius(0);

            return this->style;
        }

        StatusBar* append(lv_obj_t* obj) override {
            lv_obj_set_parent(obj, get_component());
            return this;
        }
    };

} //