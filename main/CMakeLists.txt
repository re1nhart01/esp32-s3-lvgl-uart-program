idf_component_register(
        SRCS  "core/waveshare_rgb_lcd_port.c" "main.cc" "core/lvgl_port.c" "components/indexer.cc"
        INCLUDE_DIRS "." "core" "components" "components/base/headers" "components/base")

idf_component_get_property(lvgl_lib lvgl__lvgl COMPONENT_LIB)
target_compile_options(${lvgl_lib} PRIVATE -Wno-format)
