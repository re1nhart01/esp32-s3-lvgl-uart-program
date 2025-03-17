//
// Created by evgeniy on 3/18/25.
//

#ifndef BASE_WIDGET_HH
#define BASE_WIDGET_HH

#endif //BASE_WIDGET_HH

extern "C" {
#include "lv_demos.h"
#include "lvgl_port.h"
}




class BaseWidget {
  public:

  lv_obj_t* render();
};