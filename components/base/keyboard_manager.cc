#ifndef KEYBOARD_MANAGER_HH
#define KEYBOARD_MANAGER_HH

extern "C" {
#include "lv_demos.h"
#include "lvgl_port.h"
}

namespace base_widgets {

    class KeyboardManager {
    private:
        lv_obj_t* keyboard = nullptr;

    public:
        void create(lv_obj_t* parent) {
            if (!keyboard) {
                keyboard = lv_keyboard_create(parent);
                lv_obj_add_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
                lv_obj_align(keyboard, LV_ALIGN_BOTTOM_MID, 0, 0);
            }
        }

        void attach(lv_obj_t* textarea) {
            if (!keyboard) return;
            lv_keyboard_set_textarea(keyboard, textarea);
            lv_obj_clear_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
        }

        void hide() {
            if (keyboard) {
                lv_obj_add_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
                lv_keyboard_set_textarea(keyboard, nullptr);
            }
        }

        bool is_visible() const {
            return keyboard && !lv_obj_has_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
        }

        lv_obj_t* get_keyboard() const {
            return keyboard;
        }
    };

} // namespace base_widgets

#endif // KEYBOARD_MANAGER_HH
