//
// Created by evgeniy on 3/18/25.
//

#pragma once

#include "lv_demos.h"
#include "lvgl_port.h"

class Styling
{
private:
  lv_style_t style;
  short width = -1;
  short height = -1;

public:
  Styling() { lv_style_init(&style); }

  ~Styling() { lv_style_reset(&style); }

  lv_style_t *getStyle() { return &style; }

  // Установка цвета фона
  Styling setBackgroundColor(lv_color_t color)
  {
    lv_style_set_bg_color(&style, color);
    return *this;
  }

  // Установка градиента фона
  Styling *
  setBackgroundGradient(lv_color_t start, lv_color_t end, lv_grad_dir_t dir)
  {
    lv_style_set_bg_grad_color(&style, end);
    lv_style_set_bg_grad_dir(&style, dir);
    return this;
  }

  // Установка прозрачности фона
  Styling *setBackgroundOpacity(lv_opa_t opa)
  {
    lv_style_set_bg_opa(&style, opa);
    return this;
  }

  // Установка закругленных углов
  Styling *setBorderRadius(lv_coord_t radius)
  {
    lv_style_set_radius(&style, radius);
    return this;
  }

  // Установка границ
  Styling *setBorder(lv_color_t color, lv_coord_t width, lv_opa_t opa)
  {
    lv_style_set_border_color(&style, color);
    lv_style_set_border_width(&style, width);
    lv_style_set_border_opa(&style, opa);
    return this;
  }

  // Установка тени
  Styling *setShadow(lv_color_t color, lv_coord_t width, lv_coord_t spread)
  {
    lv_style_set_shadow_color(&style, color);
    lv_style_set_shadow_width(&style, width);
    lv_style_set_shadow_spread(&style, spread);
    return this;
  }

  // Установка паддингов
  Styling *setPadding(lv_coord_t top, lv_coord_t bottom, lv_coord_t left,
                      lv_coord_t right)
  {
    lv_style_set_pad_top(&style, top);
    lv_style_set_pad_bottom(&style, bottom);
    lv_style_set_pad_left(&style, left);
    lv_style_set_pad_right(&style, right);
    return this;
  }

  // Установка размеров
  Styling *setSize(lv_coord_t width, lv_coord_t height)
  {
    lv_style_set_width(&style, width);
    lv_style_set_height(&style, height);
    return this;
  }

  // Установка минимального и максимального размера
  Styling *setMinMaxSize(lv_coord_t min_w, lv_coord_t min_h, lv_coord_t max_w,
                         lv_coord_t max_h)
  {
    lv_style_set_min_width(&style, min_w);
    lv_style_set_min_height(&style, min_h);
    lv_style_set_max_width(&style, max_w);
    lv_style_set_max_height(&style, max_h);
    return this;
  }

  // Установка цвета текста
  Styling *setTextColor(lv_color_t color)
  {
    lv_style_set_text_color(&style, color);
    return this;
  }

  // Установка шрифта
  Styling *setFont(const lv_font_t *font)
  {
    lv_style_set_text_font(&style, font);
    return this;
  }

  // Установка выравнивания текста
  Styling *setTextAlign(lv_text_align_t align)
  {
    lv_style_set_text_align(&style, align);
    return this;
  }

  // Установка прозрачности текста
  Styling *setTextOpacity(lv_opa_t opa)
  {
    lv_style_set_text_opa(&style, opa);
    return this;
  }

  // Установка цвета линии (например, для разделителей)
  Styling *setLineColor(lv_color_t color)
  {
    lv_style_set_line_color(&style, color);
    return this;
  }

  // Установка ширины линии
  Styling *setLineWidth(lv_coord_t width)
  {
    lv_style_set_line_width(&style, width);
    return this;
  }

  // Установка цвета изображения (например, для иконок)
  Styling *setImageColor(lv_color_t color)
  {
    lv_style_set_img_recolor(&style, color);
    return this;
  }

  // Установка прозрачности изображения
  Styling *setImageOpacity(lv_opa_t opa)
  {
    lv_style_set_img_opa(&style, opa);
    return this;
  }

  // Применение стиля к объекту
  Styling *applyTo(lv_obj_t *obj)
  {
    lv_obj_add_style(obj, &style, LV_PART_MAIN);
    return this;
  }

  // Продолжение класса Styling
  Styling* setClipCorner(bool clip) {
    lv_style_set_clip_corner(&style, clip);
    return this;
  }

  Styling* setBgImgSrc(const void* src) {
    lv_style_set_bg_img_src(&style, src);
    return this;
  }

  Styling* setOutline(lv_color_t color, lv_coord_t width, lv_opa_t opa) {
    lv_style_set_outline_color(&style, color);
    lv_style_set_outline_width(&style, width);
    lv_style_set_outline_opa(&style, opa);
    return this;
  }

  Styling* setTransformAngle(int16_t angle) {
    lv_style_set_transform_angle(&style, angle);
    return this;
  }

  Styling* setTransformZoom(uint16_t zoom) {
    lv_style_set_transform_zoom(&style, zoom);
    return this;
  }

  Styling* setAlign(lv_align_t align) {
    lv_style_set_align(&style, align);
    return this;
  }

  Styling* setTransition(const lv_style_transition_dsc_t* transition) {
    lv_style_set_transition(&style, transition);
    return this;
  }

  Styling* setWidth(const short width) {
    this->width = width;
    return this;
  }

  Styling* setHeight(const short height) {
    this->height = height;
    return this;
  }

  Styling* setSizeW(const short width, const short height) {
    this->width = width;
    this->height = height;
    return this;
  }
};