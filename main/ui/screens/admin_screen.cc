//
// Created by evgeniy on 4/6/25.
//

#include "../../../components/base/application.hh"
#include "../../../components/base/component.hh"
#include "../../../components/base/view.cc"

#include "../../../components/base/button.cc"
#include "../../../components/base/image.cc"
#include "../../../components/base/label.cc"
#include "../../../components/base/state.cc"
#include "../../../components/base/text_input.cc"
#include "stack_navigator.cc"

using namespace base_widgets;

struct admin_screen_props
{
  std::shared_ptr<base_widgets::Ref> ref = nullptr;
};

std::unique_ptr<KeyboardManager> admin_keyboard = std::make_unique<KeyboardManager>();
std::shared_ptr<Styling> imageStyle = std::make_shared<Styling>();

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

  ~AdminScreen() {
    Component::~Component();
  };

  void on_mount() override {
    Component::on_mount();

  };


  lv_obj_t *render() override
  {
    std::shared_ptr<Styling> style = this->styling();
    std::shared_ptr<Styling> style1 = std::make_shared<Styling>();
    std::shared_ptr<Styling> style2 = std::make_shared<Styling>();

    auto navigator_ref = this->navigator;

    LV_IMG_DECLARE(img_lvgl_logo);

    imageStyle->setSize(100, 100);

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
                     }),
                    std::make_shared<TextInput>(textinput_props{
                        .ref = nullptr,
                        .style = style1,
                        .placeholder = "text",
                        .on_click = [](lv_event_t *e) {  },
                        .on_focused = [](lv_event_t *e) { /* ... */ },
                        .on_defocused = [](lv_event_t *e) { /* ... */ },
                        .on_value_changed = [](lv_event_t *e) { /* ... */ },
                        .on_submit = [](std::string value) {
                          ESP_LOGI("LoG", "%s", value.c_str());
                          admin_keyboard.get()->hide();
                        }
                    }, admin_keyboard.get()),
          //           std::make_shared<Image>(img_lvgl_logo, image_props{
          //             .ref = nullptr,
          //             .style = imageStyle,
          //           }),
          // std::make_shared<Image>(img_lvgl_logo, image_props{
          //             .ref = nullptr,
          //             .style = imageStyle,
          //           })
          // ,std::make_shared<Image>(img_lvgl_logo, image_props{
          //             .ref = nullptr,
          //             .style = imageStyle,
          // }),std::make_shared<Image>(img_lvgl_logo, image_props{
          //   .ref = nullptr,
          //   .style = imageStyle,
          // })
        },
        .width = LV_PCT(100),
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
