//
// Created by evgeniy on 4/6/25.
//
#include <iostream>

extern "C" {
    #include "core/waveshare_rgb_lcd_port.h"
    #include "esp_log.h"
    #include "freertos/FreeRTOS.h"
    #include "driver/gpio.h"
    #include "sdkconfig.h"
}

static lv_obj_t* label_counter = nullptr;

class WaveshareDisplay {
    int counter;
public:
    void turnOnBacklight();
    void turnOffBacklight();
    void button_event_handler(lv_event_t * e);
    void displayDemo();

    explicit WaveshareDisplay(const int counter) {
        this->counter = counter;
        waveshare_esp32_s3_rgb_lcd_init();
        ESP_LOGI(TAG, "Waveshare ESP32-S3 RGB LCD Initialized");
    }
    ~WaveshareDisplay() {
        ESP_LOGI(TAG, "WaveshareDisplay object destroyed");
    }
};

    void WaveshareDisplay::button_event_handler(lv_event_t * event) {
        asm volatile (
            "movi a2, 10\n"        // Загружаем 10 в a2 (счетчик)
            "loop_start:\n"
            "addi %0, %0, 1\n"     // Увеличиваем value на 1
            "addi a2, a2, -1\n"    // Уменьшаем счетчик
            "bnez a2, loop_start\n" // Повторяем пока a2 != 0
            : "+r" (counter)          // Используем value как вход/выход
            :                       // Нет дополнительных входов
            : "a2"                  // Указываем, что используем a2 (чтобы компилятор не трогал)
        );

        counter++;
        lv_label_set_text(label_counter, std::format("{}", counter).c_str());
    }

    void WaveshareDisplay::displayDemo() {
        ESP_LOGI(TAG, "Display LVGL demos");


            lv_obj_t *screen = lv_scr_act();
            lv_obj_t *btn = lv_btn_create(screen);

            label_counter = lv_label_create(screen);

            std::string counterText = std::format("{}", counter);
            lv_label_set_text(label_counter, counterText.c_str());
            lv_obj_align(label_counter, LV_ALIGN_TOP_LEFT, 10, 10);

            lv_obj_set_size(btn, 120, 50);
            lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);

            lv_obj_add_event_cb(btn, [](lv_event_t *event) mutable {
                auto *instance = static_cast<WaveshareDisplay*>(lv_event_get_user_data(event));
                if (instance) {
                    instance->button_event_handler(event);
                }
            }, LV_EVENT_CLICKED, this);

            lv_obj_t *label = lv_label_create(btn);
            lv_label_set_text(label, "Press Me!");
            lv_obj_center(label);

            ESP_LOGI("WaveshareRGBLCD", "Button UI displayed");

    }