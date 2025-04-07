#include <iostream>
#include "styling.hh"

extern "C" {
#include "lv_demos.h"
#include "lvgl_port.h"
}

#pragma once

#ifndef BASE_WIDGET_HH
#define BASE_WIDGET_HH

#endif //BASE_WIDGET_HH
//
//    LV_EVENT_PRESSED,             /**< The object has been pressed*/
//    LV_EVENT_PRESSING,            /**< The object is being pressed (called continuously while pressing)*/
//    LV_EVENT_PRESS_LOST,          /**< The object is still being pressed but slid cursor/finger off of the object */
//    LV_EVENT_SHORT_CLICKED,       /**< The object was pressed for a short period of time, then released it. Not called if scrolled.*/
//    LV_EVENT_LONG_PRESSED,        /**< Object has been pressed for at least `long_press_time`.  Not called if scrolled.*/
//    LV_EVENT_LONG_PRESSED_REPEAT, /**< Called after `long_press_time` in every `long_press_repeat_time` ms.  Not called if scrolled.*/
//    LV_EVENT_CLICKED,             /**< Called on release if not scrolled (regardless to long press)*/
//    LV_EVENT_RELEASED,            /**< Called in every cases when the object has been released*/
//    LV_EVENT_SCROLL_BEGIN,        /**< Scrolling begins. The event parameter is a pointer to the animation of the scroll. Can be modified*/
//    LV_EVENT_SCROLL_END,          /**< Scrolling ends*/
//    LV_EVENT_SCROLL,              /**< Scrolling*/
//    LV_EVENT_GESTURE,             /**< A gesture is detected. Get the gesture with `lv_indev_get_gesture_dir(lv_indev_get_act());` */
//    LV_EVENT_KEY,                 /**< A key is sent to the object. Get the key with `lv_indev_get_key(lv_indev_get_act());`*/
//    LV_EVENT_FOCUSED,             /**< The object is focused*/
//    LV_EVENT_DEFOCUSED,           /**< The object is defocused*/
//    LV_EVENT_LEAVE,               /**< The object is defocused but still selected*/
//    LV_EVENT_HIT_TEST,



class BaseWidget {
protected:
  lv_obj_t *widget;
  lv_obj_t* screen_ref;
  BaseWidget* child;

  virtual ~BaseWidget() = default;

  BaseWidget(BaseWidget* child, lv_obj_t* screen_ref, BaseWidget* parent_ref): widget(nullptr) {
    this->child = child;
    this->screen_ref = screen_ref;
    this->parent_ref = parent_ref;
  }

public:
  BaseWidget* parent_ref;

  virtual lv_obj_t* render() = 0;
  lv_obj_t* get_internal_lv_obj() const;
  void set_child(BaseWidget* child_);
  virtual void append_to(const BaseWidget *parent) = 0;
  virtual void set_active(bool active) = 0;
  virtual BaseWidget* set_style(Styling* style_obj) = 0;
};

inline void BaseWidget::set_child(BaseWidget* child_) {
  this->child = child_;
  if (this->child) this->child->parent_ref = this;
}

inline lv_obj_t* BaseWidget::get_internal_lv_obj() const {
  return this->widget;
}