//
// Created by evgeniy on 4/6/25.
//

#include "../../../components/base/application.hh"
#include "../../../components/base/component.hh"
#include "../../../components/base/view.cc"

#include "../../../components/base/button.cc"
#include "../../../components/base/label.cc"
#include "../../../components/base/state.cc"
#include "stack_navigator.cc"

using namespace base_widgets;

struct admin_screen_props
{
  std::shared_ptr<base_widgets::Ref> ref = nullptr;
};

class AdminScreen : public base_widgets::Component
{
  admin_screen_props props;
  std::shared_ptr<StackNavigator> navigator;

public:
  explicit AdminScreen(std::shared_ptr<StackNavigator> stack,
                       const admin_screen_props &props)
      : Component(nullptr, nullptr)
  {
    this->props = props;
    this->navigator = std::move(stack);
    if(this->props.ref != nullptr)
      {
        this->props.ref->set(this);
      }
  }

  ~AdminScreen() override = default;

  lv_obj_t *render() override
  {
    std::shared_ptr<Styling> style = this->styling();
    std::shared_ptr<Styling> style1 = std::make_shared<Styling>();
    std::shared_ptr<Styling> style2 = std::make_shared<Styling>();

    // if (style != nullptr) {
    //     lv_obj_add_style(this->get_component(), style->getStyle(),
    //     LV_PART_MAIN);
    // }

    auto navigator_ref = this->navigator;

    auto renderer = std::make_shared<View>(
      this->parent,
      view_props{
        .ref = nullptr,
        .style = style,
        .children = {std::make_shared<Label>(label_props{
                       .ref = nullptr,
                       .style = style2,
                       .text = "text",
                       .events = {},
                     }),
                     std::make_shared<Button>(button_props{
                       .ref = nullptr,
                       .style = style1,
                       .text = "navigate to admin",
                       .on_click =
                         [navigator_ref](lv_event_t *e) {
                           navigator_ref->navigate("/main");
                         },
                       .on_long_press = [](lv_event_t *e) { /* ... */ },
                       .on_pressed = [](lv_event_t *e) { /* ... */ },
                       .on_released = [](lv_event_t *e) { /* ... */ },
                       .on_focused = [](lv_event_t *e) { /* ... */ },
                       .on_defocused = [](lv_event_t *e) { /* ... */ },
                     })},
        .width = 620,
        .height = 180,
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

  std::shared_ptr<Styling> styling() override
  {
    std::shared_ptr<Styling> style = this->style;

    if(style != nullptr) {}

    return style;
  }

  AdminScreen *append(lv_obj_t *obj) override
  {
    lv_obj_set_parent(obj, get_component());
    return this;
  }
};
