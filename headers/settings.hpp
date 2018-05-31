//
// Created by Killian Le Clainche on 5/27/2018.
//

#ifndef RTMOBAS_GAME_SETTINGS_HPP
#define RTMOBAS_GAME_SETTINGS_HPP

#include "helper.hpp"

namespace settings {

    //Interface for any custom setting used within the game
    class Setting {
        //Loads the setting based on the string passed as a parameter.
        virtual void load(char *);

        //Saves the setting into a string that is saved in a config file.
        virtual char * save();
    };

    /**
     * Key Object, can have multiple key codes -> one key object.
     * his object allows for handling behaviors inside the game
     */
    class Key : Setting {

    private:
        //Helps determine if a double press
        long press_timer = 0L;

    public:

        /** Count of how many key codes are currently pressed. */
        int pressed;

        /** True after release for one tick. */
        bool clicked;

        /** True if click occurred within KEY_QUICK_PRESS amount of time and lasts for one tick. */
        bool quick_pressed;

        /** Tally of how many successive quick_pressed events have occurred. */
        int quick_press_count;

        /** Length of time pressed has stayed TRUE. */
        long pressed_time;

        // From Setting Interface
        void load(char *);

        // From Setting Interface
        char * save();

        /** Called whenever any key code was pressed. */
        void press();

        /** Called whenever any key code was released. */
        void release();

        /** Called on every tick for calculations to be ran. */
        void update();

        //char * to_string();

    };

    enum WindowMode {
        WINDOWED, BORDERLESS, FULLSCREEN
    };

    /** key (integer) -> Key Object for advanced processing */
    std::map<int, Key> keyboard_mapping;
    /** mouse (integer) -> Key Object for advanced processing */
    std::map<int, Key> mouse_mapping;

    // /** The monitor that the window is contained in (or at least the top left corner is located inside). */
    // Monitor monitor;

    /** Determines what mode the window is, used for switching purposes. */
    WindowMode window_mode;

    /**
     * True when the window mode has changed to a new state and requires the window to
     * either be updated or recreated.
     */
    bool update_window = false;

    /** Top left corner of the window */
    int window_x;
    int window_y;

    /** Dimensions of the entire window across all involved monitors. */
    int window_width;
    int window_height;

    /** Useful for switching from a Borderless / Fullscreen Window Mode back to the original state of the Windowed. */
    bool window_maximized = false;

    /** Enable VSYNC (refresh at monitor rate to prevent tearing) */
    bool enable_vsync = false;

    /** Used for any settings that is needed to be saved on application shutdown */
    std::map<char *, Setting> settings;

    void load();

    void save();

    void init();

}

#endif //RTMOBAS_GAME_SETTINGS_HPP
