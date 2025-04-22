#include "application.hh"
#include "view.cc"
#include "app.cc"


#define entrypoint [[maybe_unused]]

extern "C" {
#include "core/waveshare_rgb_lcd_port.h"
}

using namespace foundation;

std::shared_ptr<WaveApplication> application;

void entry() {
  waveshare_esp32_s3_rgb_lcd_init();

  if (lvgl_port_lock(-1)) {
    lv_obj_t *screen = lv_scr_act();

    application = std::make_shared<WaveApplication>(screen);
    application->renderApp();

    lvgl_port_unlock();
  }
}

extern "C" void app_main() {
  entry();
}