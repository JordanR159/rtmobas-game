//
// Created by Killian Le Clainche on 6/2/2018.
//

#include "helper.hpp"

namespace settings {

    const long long int KEY_DOUBLE_PRESS = 1000 / 5;

    void Key::press() {
        this->pressed ++;
        this->just_pressed = true;

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
        this->just_pressed = false;
        this->quick_pressed = false;

        if(this->quick_press_count > 0) {
            long long int ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

            if(ms - this->release_timer > KEY_DOUBLE_PRESS)
                this->quick_press_count = 0;
        }
    }
}