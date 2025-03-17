//
// Created by evgeniy on 3/18/25.
//

#ifndef BASE_STYLING_HH
#define BASE_STYLING_HH
#endif //BASE_STYLING_HH

#include "lv_demos.h"
#include "lvgl_port.h"

class Styling {
private:
    lv_style_t style;

public:
    Styling() {
        lv_style_init(&style);
    }

    ~Styling() {
        lv_style_reset(&style);
    }

    lv_style_t* getStyle() {
        return &style;
    }

    // Установка цвета фона
    void setBackgroundColor(lv_color_t color) {
        lv_style_set_bg_color(&style, color);
    }

    // Установка градиента фона
    void setBackgroundGradient(lv_color_t start, lv_color_t end, lv_grad_dir_t dir) {
        lv_style_set_bg_grad_color(&style, end);
        lv_style_set_bg_grad_dir(&style, dir);
    }

    // Установка прозрачности фона
    void setBackgroundOpacity(lv_opa_t opa) {
        lv_style_set_bg_opa(&style, opa);
    }

    // Установка закругленных углов
    void setBorderRadius(lv_coord_t radius) {
        lv_style_set_radius(&style, radius);
    }

    // Установка границ
    void setBorder(lv_color_t color, lv_coord_t width, lv_opa_t opa) {
        lv_style_set_border_color(&style, color);
        lv_style_set_border_width(&style, width);
        lv_style_set_border_opa(&style, opa);
    }

    // Установка тени
    void setShadow(lv_color_t color, lv_coord_t width, lv_coord_t spread) {
        lv_style_set_shadow_color(&style, color);
        lv_style_set_shadow_width(&style, width);
        lv_style_set_shadow_spread(&style, spread);
    }

    // Установка паддингов
    void setPadding(lv_coord_t top, lv_coord_t bottom, lv_coord_t left, lv_coord_t right) {
        lv_style_set_pad_top(&style, top);
        lv_style_set_pad_bottom(&style, bottom);
        lv_style_set_pad_left(&style, left);
        lv_style_set_pad_right(&style, right);
    }

    // Установка размеров
    void setSize(lv_coord_t width, lv_coord_t height) {
        lv_style_set_width(&style, width);
        lv_style_set_height(&style, height);
    }

    // Установка минимального и максимального размера
    void setMinMaxSize(lv_coord_t min_w, lv_coord_t min_h, lv_coord_t max_w, lv_coord_t max_h) {
        lv_style_set_min_width(&style, min_w);
        lv_style_set_min_height(&style, min_h);
        lv_style_set_max_width(&style, max_w);
        lv_style_set_max_height(&style, max_h);
    }

    // Установка цвета текста
    void setTextColor(lv_color_t color) {
        lv_style_set_text_color(&style, color);
    }

    // Установка шрифта
    void setFont(const lv_font_t* font) {
        lv_style_set_text_font(&style, font);
    }

    // Установка выравнивания текста
    void setTextAlign(lv_text_align_t align) {
        lv_style_set_text_align(&style, align);
    }

    // Установка прозрачности текста
    void setTextOpacity(lv_opa_t opa) {
        lv_style_set_text_opa(&style, opa);
    }

    // Установка цвета линии (например, для разделителей)
    void setLineColor(lv_color_t color) {
        lv_style_set_line_color(&style, color);
    }

    // Установка ширины линии
    void setLineWidth(lv_coord_t width) {
        lv_style_set_line_width(&style, width);
    }

    // Установка цвета изображения (например, для иконок)
    void setImageColor(lv_color_t color) {
        lv_style_set_img_recolor(&style, color);
    }

    // Установка прозрачности изображения
    void setImageOpacity(lv_opa_t opa) {
        lv_style_set_img_opa(&style, opa);
    }

    // Применение стиля к объекту
    void applyTo(lv_obj_t* obj) {
        lv_obj_add_style(obj, &style, LV_PART_MAIN);
    }
};