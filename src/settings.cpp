//
// Created by Killian Le Clainche on 5/30/2018.
//

#include <settings.hpp>
#include <chrono>
#include <sys/stat.h>
#include <sstream>

const long long int KEY_DOUBLE_PRESS = 1000 / 5;

namespace settings {

    const int Key::SCROLL_UP = 1;
    const int Key::SCROLL_DOWN = 2;
    const int Key::SCROLL_LEFT = 3;
    const int Key::SCROLL_RIGHT = 4;

    std::map<int, Key *> keyboard_mapping;
    std::map<int, Key *> mouse_mapping;
    std::map<int, Key *> input_mapping;

    sf::RenderWindow window;
    sf::View view;

    bool update_window = false;

    unsigned int window_width = 800;
    unsigned int window_height = 600;

    void Key::press() {

        std::cout << "pressed" << std::endl;
        this->pressed ++;

        if(this->pressed == 1) {
            this->quick_pressed = false;

            long long int ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

            if(ms - this->release_timer < KEY_DOUBLE_PRESS)
                this->quick_press_count ++;

            this->pressed_timer = ms;
        }
    }

    void Key::release() {
        this->pressed --;
        std::cout << "released" << std::endl;

        if(this->pressed == 0) {
            this->clicked = true;

            long long int ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

            if(ms - this->pressed_timer < KEY_DOUBLE_PRESS)
                this->quick_pressed = true;

            this->release_timer = ms;
        }
    }

    void Key::update() {
        this->clicked = false;
        this->quick_pressed = false;

        if(this->quick_press_count > 0) {
            long long int ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

            if(ms - this->release_timer > KEY_DOUBLE_PRESS)
                this->quick_press_count = 0;
        }
    }

    void setInput(const std::string &key_string, const std::string &value_string, std::map<int, Key *> * mapping) {
        void * mem = rpmalloc(sizeof(Key));
        Key * key = new(mem) Key();

        int input = atoi(key_string.c_str());

        input_mapping[input] = key;

        std::istringstream value_stream(value_string);
        std::string token_value;

        int value;

        while(getline(value_stream, token_value, ',')) {
            value = atoi(token_value.c_str());

            (*mapping)[value] = key;
        }
    }

    void load() {
        struct stat buffer{};

        if(!stat(INPUT_SETTINGS_LOCATION, &buffer)) {
            std::ifstream input(INPUT_SETTINGS_LOCATION);
            std::map<int, Key *> * mapping = &keyboard_mapping;
            while(input) {
                std::string key;
                std::string value;
                std::getline(input, key, ':');
                std::getline(input, value, '\n');
                if(key == "MOUSE_INPUT")
                    mapping = &mouse_mapping;
                else
                    setInput(key, value, mapping);
            }
            input.close();
        }
    }

    void init() {
        window.create(sf::VideoMode(window_width, window_height), "RTM");

        window.setMouseCursorVisible(true);
        window.setMouseCursorGrabbed(false);
        window.setKeyRepeatEnabled(false);
        window.setVerticalSyncEnabled(true);

        window.setVisible(true);

        window.requestFocus();

        view.reset(FloatRect(0, 0, window_width, window_height));
        view.setViewport(FloatRect(0.f, 0.f, 1.f, 1.f));
        view.rotate(0);
        window.setView(view);
    }

    void save() {
        std::ofstream output;
        output.open(INPUT_SETTINGS_LOCATION);

        for (auto &iter : input_mapping) {
            output << iter.first << ':';

            int count = 0;

            for(auto &mapIter : keyboard_mapping) {
                if(mapIter.second == iter.second) {
                    if(count != 0)
                        output << ',';
                    output << mapIter.first;
                    count++;
                }
            }

            for(auto &mapIter : mouse_mapping) {
                if(mapIter.second == iter.second) {
                    if(count != 0)
                        output << ',';
                    output << mapIter.first;
                    count++;
                }
            }

            output << std::endl;
        }
    }

    bool update() {
        sf::Event event{};

        bool events = false;

        while(window.pollEvent(event)) {
            events = true;

            if(event.type == sf::Event::Closed) {
std::cout << "Closed" << std::endl;
                window.close();
            }

            if(event.type == sf::Event::KeyPressed && keyboard_mapping.find(event.key.code) != keyboard_mapping.end())
                keyboard_mapping[event.key.code]->press();

            if(event.type == sf::Event::KeyReleased && keyboard_mapping.find(event.key.code) != keyboard_mapping.end())
                keyboard_mapping[event.key.code]->release();

            if(event.type == sf::Event::MouseButtonPressed && mouse_mapping.find(event.mouseButton.button) != mouse_mapping.end()) {

                auto * key = mouse_mapping[event.mouseButton.button];

                key->press();
                key->mouse_x = event.mouseButton.x;
                key->mouse_y = event.mouseButton.y;
            }

            if(event.type == sf::Event::MouseButtonReleased && mouse_mapping.find(event.mouseButton.button) != mouse_mapping.end()) {

                auto * key = mouse_mapping[event.mouseButton.button];

                key->release();
                key->mouse_x = event.mouseButton.x;
                key->mouse_y = event.mouseButton.y;
            }
        }

        for(auto &iter : keyboard_mapping) {
            iter.second->update();
        }

        for(auto &iter : mouse_mapping) {
            iter.second->update();
        }

        return events;
    }
}
