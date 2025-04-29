//
// Created by evgeniy on 4/23/25.
//



#define $view(...) std::make_shared<View>(__VA_ARGS__)
#define $label(...) std::make_shared<Label>(__VA_ARGS__)
#define $image(...) std::make_shared<Image>(__VA_ARGS__)
#define $input(...) std::make_shared<TextInput>(__VA_ARGS__)
#define $button(...) std::make_shared<Button>(__VA_ARGS__)
#define $statusbar(...) std::make_shared<StatusBar>(__VA_ARGS__)



namespace foundation {
  struct entrypoint {};
}

#define entry(func) \
extern "C" void app_main() { \
ESP_LOGI("APPLICATION ENTRYPOINT", "START"); \
func(); \

#define end \
}