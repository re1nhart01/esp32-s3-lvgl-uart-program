#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include "component.hh"

#include "esp_log.h"

namespace foundation {

    struct StackCurrentScreen {
        int id;
        std::string name;
        std::shared_ptr<Component> screen;
    };

    struct StackNavigatorConfig {
        std::string initial_route;
    };

    class StackNavigator {
    private:
        std::shared_ptr<StackCurrentScreen> current_screen = nullptr;
        StackNavigatorConfig config;
        std::unordered_map<std::string, std::shared_ptr<Component>> screens;
        int id_counter = 0;

    public:
        explicit StackNavigator(const StackNavigatorConfig& config) {
            this->config = config;
        }

        void registerScreen(const std::string& name, const std::shared_ptr<Component>& component) {
            screens[name] = component;

                current_screen = std::make_shared<StackCurrentScreen>(StackCurrentScreen{
                    .id = id_counter++,
                    .name = name,
                    .screen = component
                });
        }

        void start() {
            if (screens.count(config.initial_route)) {
                navigate(config.initial_route);
            } else {
            }
        }

        void navigate(const std::string& name) {
            auto it = screens.find(name);
            if (it != screens.end()) {
                auto screen = it->second;

                lv_obj_t* active_screen = lv_scr_act();

                lv_obj_clean(active_screen);

                screen->set_parent(active_screen);

                lv_obj_t* obj = screen->render();
                screen->set_component(obj);

                screen->on_mount();

                current_screen = std::make_shared<StackCurrentScreen>(StackCurrentScreen{
                    .id = ++id_counter,
                    .name = name,
                    .screen = screen
                });
            }
        }


        std::shared_ptr<Component> getCurrentComponent() const {
            return current_screen->screen;
        }

        std::string getCurrentRoute() const {
            return current_screen ? current_screen->name : "";
        }

        bool hasScreen(const std::string& name) const {
            return screens.find(name) != screens.end();
        }
    };

}
