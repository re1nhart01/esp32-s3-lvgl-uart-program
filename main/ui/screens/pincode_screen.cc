#include <utility>

#include "component.hh"
#include "macro.hh"
#include "stack_navigator.hh"

namespace foundation
{
  class StackNavigator;
}

using namespace foundation;

struct pincode_screen_props
{
  std::shared_ptr<foundation::Ref> ref = nullptr;
};



class PinCodeScreen : public foundation::Component
{
  pincode_screen_props props;
  std::shared_ptr<StackNavigator> navigator;

public:
  explicit PinCodeScreen(std::shared_ptr<StackNavigator> stack,
                      const pincode_screen_props &props)
      : Component(nullptr, nullptr)
  {
    this->props = props;
    this->navigator = std::move(stack);
    if(this->props.ref != nullptr)
      {
        this->props.ref->set(this);
      }
  }

  ~PinCodeScreen() override = default;

  lv_obj_t *render() override {
    return this->delegate($view(
      this->parent,
      view_props{
        .ref = nullptr,
        .style = this->styling(),
        .children = {
          $statusbar(status_bar_props{
            .ref = nullptr,
            .style = nullptr,
          }),

        },
        screen_container_props,
      }));
  }



  std::shared_ptr<Styling> styling() override {
    this->style = std::make_shared<Styling>();

    this->style->setTextColor(lv_color_make(255, 255, 255));
    this->style->setPadding(0, 0, 0, 0);
    this->style->setBorderRadius(0);
    this->style->setBorder(lv_color_make(255, 255, 255), 0, 0);

    return this->style;
  }

  PinCodeScreen* append(lv_obj_t *obj) override
  {
    lv_obj_set_parent(obj, get_component());
    return this;
  }
};
