#include <utility>

#include "component.hh"
#include "view.cc"

#include "status_bar.cc"
#include "state.cc"
#include "text_input.cc"
#include "macro_component.cc"
#include "stack_navigator.cc"

namespace foundation
{
  class StackNavigator;
}

using namespace foundation;

struct main_screen_props
{
  std::shared_ptr<foundation::Ref> ref = nullptr;
};

class MainScreen : public Component
{
  main_screen_props props;
  std::shared_ptr<StackNavigator> navigator;

public:
  explicit MainScreen(std::shared_ptr<StackNavigator> stack,
                      const main_screen_props &props)
      : Component(nullptr, nullptr)
  {
    this->props = props;
    this->navigator = std::move(stack);
    if(this->props.ref != nullptr)
      {
        this->props.ref->set(this);
      }
  }

  ~MainScreen() override = default;

  lv_obj_t *render() override
  {
    std::shared_ptr<Styling> style = this->styling();
    std::shared_ptr<Styling> style1 = std::make_shared<Styling>();
    std::shared_ptr<Styling> style2 = std::make_shared<Styling>();

    auto navigator_ref = this->navigator;

    auto renderer = $view(
      this->parent,
      view_props{
        .ref = nullptr,
        .style = style,
        .children = {
          $statusbar(status_bar_props{
            .ref = nullptr,
            .style = nullptr,
          }),
          $label(label_props{
                       .ref = nullptr,
                       .style = style2,
                       .text = "text",
                     }),
                     $button(button_props{
                       .ref = nullptr,
                       .style = style1,
                       .text = "navigate to admin",
                       .on_click =
                         [navigator_ref](lv_event_t *e) {
                           navigator_ref->navigate("/main");
                         },
                     }),
                    $input(textinput_props{
                        .ref = nullptr,
                        .style = style1,
                        .placeholder = "text",
                        .on_submit = [](std::string value) {
                          ESP_LOGI("LoG", "%s", value.c_str());
                        }
                    }, nullptr),
        },
        .width = LV_PCT(100),
        .height = LV_PCT(100),
        .justify_content = LV_FLEX_ALIGN_SPACE_BETWEEN,
        .align_items = LV_FLEX_ALIGN_CENTER,
        .track_cross_place = LV_FLEX_ALIGN_CENTER,
        .flex_direction = LV_FLEX_FLOW_COLUMN,
      });

    this->renderer_view = renderer;
    this->renderer_view->set_parent(this->parent);
    this->set_component(renderer->render());

    return renderer->get_component();
  }



  std::shared_ptr<Styling> styling() override {
    this->style = std::make_shared<Styling>();

    this->style->setTextColor(lv_color_make(255, 255, 255));
    this->style->setPadding(0, 0, 0, 0);
    this->style->setBorderRadius(0);
    this->style->setBorder(lv_color_make(255, 255, 255), 0, 0);

    return this->style;
  }

  MainScreen* append(lv_obj_t *obj) override
  {
    lv_obj_set_parent(obj, get_component());
    return this;
  }
};
