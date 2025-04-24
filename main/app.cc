#include "application.hh"
#include "view.cc"

#include "state.cc"
#include "button.cc"
#include "main_screen.cc"
#include "admin_screen.cc"
#include "pincode_screen.cc"


using namespace foundation;


std::shared_ptr<View> root_app_view;
std::shared_ptr<Ref> label_ref_1 = std::make_shared<Ref>("LABEL_0");
std::shared_ptr<State<int> > state_1 = std::make_shared<State<int> >(0);
std::shared_ptr<StackNavigator> stack_navigator = std::make_shared<
  StackNavigator>(StackNavigatorConfig{.initial_route = "/main"});


auto main_screen = std::make_shared<MainScreen>(
    stack_navigator, main_screen_props{.ref = nullptr});
auto admin_screen = std::make_shared<AdminScreen>(
    stack_navigator, admin_screen_props{.ref = nullptr});
auto pincode_screen = std::make_shared<PinCodeScreen>(
    stack_navigator, pincode_screen_props{.ref = nullptr});


class WaveApplication : public Application {
public:
  WaveApplication(lv_obj_t *screen)
    : Application(screen) {
  }

  Component *root_component() override {
    std::shared_ptr<Styling> style = std::make_shared<Styling>();
    std::shared_ptr<Styling> style1 = std::make_shared<Styling>();
    std::shared_ptr<Styling> style2 = std::make_shared<Styling>();

    const auto initial = stack_navigator->getCurrentComponent();

    return initial.get();
  }

  void before_load_application() override {
    stack_navigator->registerScreen("/main", main_screen);
    stack_navigator->registerScreen("/admin", admin_screen);
    stack_navigator->registerScreen("/pincode", pincode_screen);
  }

  void after_load_application() override {
    ESP_LOGI("MyApp", "after_load_application called");
  }
};