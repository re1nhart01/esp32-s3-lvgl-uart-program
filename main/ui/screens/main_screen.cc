#include <utility>

#include "../../../components/base/application.hh"
#include "../../../components/base/component.hh"
#include "../../../components/base/view.cc"

#include "../../../components/base/button.cc"
#include "../../../components/base/label.cc"
#include "../../../components/base/state.cc"

#include "stack_navigator.cc"

namespace base_widgets
{
  class StackNavigator;
}

using namespace base_widgets;

struct main_screen_props
{
  std::shared_ptr<base_widgets::Ref> ref = nullptr;
};

std::shared_ptr<Ref> label_ref = std::make_shared<Ref>("LABEL_0");
std::shared_ptr<State<int>> state = std::make_shared<State<int>>(0);
std::shared_ptr<View> root_element;
static int i = 0;

class MainScreen : public base_widgets::Component
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
        .children
        = {std::make_shared<Label>(label_props{
             .ref = label_ref,
             .style = style2,
             .text = std::format("{}", state->get()),
             .events = {},
           }),
           std::make_shared<Button>(button_props{
             .ref = nullptr,
             .style = style1,
             .text = "Click on Main Screen",
             .on_click =
               [](lv_event_t *e) {
                 // ESP_LOGI("BTN", "Clicked!");
                 // i++;
                 // state->set(i);
                 //
                 // if (label_ref->get() != nullptr) {
                 //     lv_label_set_text(label_ref->get()->get_component(),
                 //     std::to_string(i).c_str());
                 // }
               },
             .on_long_press = [](lv_event_t *e) { /* ... */ },
             .on_pressed = [](lv_event_t *e) { /* ... */ },
             .on_released = [](lv_event_t *e) { /* ... */ },
             .on_focused = [](lv_event_t *e) { /* ... */ },
             .on_defocused = [](lv_event_t *e) { /* ... */ },
           }),
           std::make_shared<Button>(button_props{
             .ref = nullptr,
             .style = style1,
             .text = "navigate to main",
             .on_click
             = [navigator_ref](
                 lv_event_t *e) { navigator_ref->navigate("/admin"); },
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

    state->subscribe([](int value) {
      if(lvgl_port_lock(-1))
        {
          ESP_LOGI("STATE1", "Value changed: %d", value);

          if(label_ref->get() != nullptr)
            {
              ESP_LOGI("STATE2", "Value changed: %d", value);

              char buf[16];
              snprintf(buf, sizeof(buf), "%d", value);

              lv_label_set_text(label_ref->get()->get_component(), buf);
            }
          lvgl_port_unlock();
        }
    });
    this->renderer_view = renderer;
    this->renderer_view->set_parent(this->parent);
    this->set_component(renderer->render());

    return this->renderer_view->get_component();
  }

  std::shared_ptr<Styling> styling() override
  {
    std::shared_ptr<Styling> style = this->style;

    if(style != nullptr) {}

    return style;
  }

  MainScreen *append(lv_obj_t *obj) override
  {
    lv_obj_set_parent(obj, get_component());
    return this;
  }
};
