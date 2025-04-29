#pragma once

#include "component.hh"
#include "styling.hh"
#include "view.hh"
#include "label.hh"
#include "macro_component.hh"
#include "ref.hh"

#include <memory>

namespace foundation {

  struct status_bar_props {
    std::shared_ptr<Ref> ref = nullptr;
    std::shared_ptr<Styling> style;
  };

  class StatusBar final : public Component {
  public:
    status_bar_props props;

    explicit StatusBar(const status_bar_props& props);
    ~StatusBar() override = default;

    lv_obj_t* render() override;
    std::shared_ptr<Styling> styling() override;
    StatusBar* append(lv_obj_t* obj) override;
  };

} // namespace foundation
