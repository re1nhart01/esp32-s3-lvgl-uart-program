#include <iostream>

extern "C" {
#include "core/waveshare_rgb_lcd_port.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_intr_alloc.h"
}


// static int counter = 0;
static SemaphoreHandle_t uart_mutex;
static lv_obj_t* label_counter = nullptr;
static QueueHandle_t uart_queue = nullptr;
#define BUF_SIZE (1024)

static void uart_interrupt_handler(void *pvParameters) {
    uart_event_t event;
    uint8_t data[BUF_SIZE];

    if (!uart_queue) {
        ESP_LOGE(TAG, "UART queue is NULL!");
        return;
    }

    while (xQueueReceive(uart_queue, &event, portMAX_DELAY)) {
        if (xSemaphoreTake(uart_mutex, portMAX_DELAY)) {
            int len = 0;
            size_t length = 0;
            std::string str = "";
            switch (event.type) {
                case UART_DATA:
                len = uart_read_bytes(UART_NUM_1, data, event.size, pdMS_TO_TICKS(100));

                if (len > 0 && len < sizeof(data)) {
                    data[len] = '\0';
                } else {
                    data[sizeof(data) - 1] = '\0';
                }
                length = std::size(data);
                str = std::string(reinterpret_cast<const char*>(data), length);
                lv_label_set_text(label_counter, std::format("{}", str).c_str());
                break;
                case UART_FIFO_OVF:
                    ESP_LOGW(TAG, "UART FIFO Overflow!");
                uart_flush_input(UART_NUM_1);
                xQueueReset(uart_queue);
                break;
                case UART_BUFFER_FULL:
                    ESP_LOGW(TAG, "UART Buffer Full!");
                uart_flush_input(UART_NUM_1);
                xQueueReset(uart_queue);
                break;
                case UART_PARITY_ERR:
                    ESP_LOGE(TAG, "UART Parity Error");
                break;
                case UART_FRAME_ERR:
                    ESP_LOGE(TAG, "UART Frame Error");
                break;
                default:
                    ESP_LOGW(TAG, "Unhandled UART event: %d", event.type);
                break;
            }
            xSemaphoreGive(uart_mutex);
        }
    }
}

extern "C" {
    uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 122,
        .source_clk = UART_SCLK_DEFAULT,
        .flags = {
            .allow_pd = 0,
            .backup_before_sleep = 0
        }
    };
}

void configure_and_log_uart() {
    uart_mutex = xSemaphoreCreateMutex();
    uart_driver_install(UART_NUM_1, BUF_SIZE * 2, BUF_SIZE * 2, 20, &uart_queue, 0);
    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1, GPIO_NUM_43, GPIO_NUM_44, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_enable_rx_intr(UART_NUM_1);
    xTaskCreate(uart_interrupt_handler, "uart_event_task", 4096, nullptr, 12, nullptr);
}



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


    void WaveshareDisplay::turnOnBacklight() {
        waveshare_rgb_lcd_bl_on();
        ESP_LOGI(TAG, "Backlight turned ON");
    }

    void WaveshareDisplay::turnOffBacklight() {
        // waveshare_rgb_lcd_bl_off();
        ESP_LOGI(TAG, "Backlight turned OFF");
    }

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

        if (lvgl_port_lock(-1)) {
            lv_obj_t *screen = lv_scr_act();
            lv_obj_t *btn = lv_btn_create(screen);

            label_counter = lv_label_create(screen);

            std::string counterText = std::format("{}", counter);
            lv_label_set_text(label_counter, counterText.c_str());
            lv_obj_align(label_counter, LV_ALIGN_TOP_LEFT, 10, 10);

            lv_obj_set_size(btn, 120, 50);
            lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);

            lv_obj_add_event_cb(btn, [](lv_event_t *event) {
                WaveshareDisplay *instance = static_cast<WaveshareDisplay*>(lv_event_get_user_data(event));
                if (instance) {
                    instance->button_event_handler(event);
                }
            }, LV_EVENT_CLICKED, this);

            lv_obj_t *label = lv_label_create(btn);
            lv_label_set_text(label, "Press Me!");
            lv_obj_center(label);

            ESP_LOGI("WaveshareRGBLCD", "Button UI displayed");
            lvgl_port_unlock();
        }
    }

void application_start() {
    WaveshareDisplay display = WaveshareDisplay(0);
    display.turnOnBacklight();
    display.displayDemo();
    configure_and_log_uart();
}

extern "C" void app_main() {
    application_start();
}
