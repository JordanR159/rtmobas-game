//
// Created by Killian Le Clainche on 5/27/2018.
//

#ifndef RTMOBAS_GAME_SETTINGS_HPP
#define RTMOBAS_GAME_SETTINGS_HPP

#include "helper.hpp"

#define SETTINGS_MOUSE_DRAG_TOLERANCE 10

#define KEY_CONTROL_ZERO 0
#define KEY_CONTROL_ONE 1
#define KEY_CONTROL_TWO 2
#define KEY_CONTROL_THREE 3
#define KEY_CONTROL_FOUR 4
#define KEY_CONTROL_FIVE 5
#define KEY_CONTROL_SIX 6
#define KEY_CONTROL_SEVEN 7
#define KEY_CONTROL_EIGHT 8
#define KEY_CONTROL_NINE 9

#define KEY_SCROLL_UP 10
#define KEY_SCROLL_DOWN 11
#define KEY_SCROLL_LEFT 12
#define KEY_SCROLL_RIGHT 13

#define KEY_CREATE_CONTROL 20
#define KEY_ADD_CONTROL 21
#define KEY_REMOVE_CONTROL 22

#define MOUSE_SELECT_CLICK 30
#define MOUSE_COMMAND_CLICK 31

#define KEY_BACK_COMMAND 100
#define KEY_BUILD_COLLECTORS 101
#define KEY_BUILD_FARM 102
#define KEY_BUILD_GOLD_MINE 103
#define KEY_BUILD_METAL_MINE 104
#define KEY_BUILD_CRYSTAL_HARVESTER 105
#define KEY_BUILD_OIL_DRILL 106

class UserInterface;
class Panel;

namespace settings {

    /** Interface for any custom setting used within the game. */
    class Setting {
        /** Loads the setting based on the string passed as a parameter. */
        virtual void load(char *);

        /** Saves the setting into a string that is saved in a config file. */
        virtual char * save();
    };

    /**
     * Setting that uses an int to represent data.
     */
    class Int : Setting {
        int value = 0;
    };

    /**
     * Setting that uses an unsigned int to represent data.
     */
    class UInt : Setting {
        unsigned int value = 0;
    };

    /**
     * Setting that uses a char string to represent data.
     */
    class String : Setting {
        const char * value = nullptr;
    };

    /**
     * Key Object, can have multiple key codes -> one key object.
     * his object allows for handling behaviors inside the game
     */
    class Key {

    private:
        /** Helps determine if a double press*/
        long long int release_timer = 0L;

    public:
        /** Count of how many key codes are currently pressed. */
        int pressed = 0;

        /** True for first tick after a key is initially pressed, false afterwards until next press */
        bool just_pressed;

        /** True after release for one tick. */
        bool clicked = false;

        /** True if click occurred within KEY_QUICK_PRESS amount of time and lasts for one tick. */
        bool quick_pressed = false;

        /** Tally of how many successive quick_pressed events have occurred. */
        int quick_press_count = 0;

        /** Length of time pressed has stayed TRUE. */
        long long int pressed_timer = 0;

        /** Used for the Mouse Key Event for determining location during click */
        int mouse_x = 0;
        int mouse_y = 0;

        /** Used to determine location of a click relative to the world */
        float adjusted_mouse_x = 0;
        float adjusted_mouse_y = 0;

        /**
         * Used for the Mouse Key Event for determining if the mouse has moved
         * a large distance away from initial pressing anytime during the press
         * state.
         */
        bool dragging = false;

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
    extern std::map<int, std::vector<Key *>> keyboard_mapping;
    /** mouse (integer) -> Key Object for advanced processing */
    extern std::map<int, std::vector<Key *>> mouse_mapping;

    extern std::map<int, Key *> input_mapping;

    /** Minimap panel that is readjusted on resize events */
    extern Panel * minimap;

    /** Ratio between width and height of minimap view */
    extern float minimap_ratio;

    // /** The monitor that the window is contained in (or at least the top left corner is located inside). */
    // Monitor monitor;

    /** The window object used by SFML, initialized by settings::init() */
    extern sf::RenderWindow window;

    /** The view (lens) that the player sees the world through. */
    extern sf::View world_view;

    /** Non-moving view (lens) that allows the player to see the displayed UI. */
    extern sf::View ui_view;

    /** Non-moving view (lens) that is used to draw mouse feedback */
    extern sf::View mouse_view;

    /** Partly moving view that is used to show current area of map being seen */
    extern sf::View minimap_view;

    /** Determines what mode the window is, used for switching purposes. */
    extern WindowMode window_mode;

    /**
     * True when the window mode has changed to a new state and requires the window to
     * either be updated or recreated.
     */
    extern bool update_window;

    /** Top left corner of the window */
    extern int window_x;
    extern int window_y;

    /** Dimensions of the entire window across all involved monitors. */
    extern unsigned int window_width;
    extern unsigned int window_height;

    /** Zoom multiplier for the window */
    extern float window_zoom;

    /** Useful for switching from a Borderless / Fullscreen Window Mode back to the original state of the Windowed. */
    extern bool window_maximized;

    /** Enable VSYNC (refresh at monitor rate to prevent tearing) */
    extern bool enable_vsync;

    /** Used for any settings that is needed to be saved on application shutdown */
    extern std::map<char *, Setting> settings;

    /** Loads all previously saved data inside the two cfg files and creates the base content for them. */
    void load();

    /** Saves any changes made to the settings into the two cfg files. */
    void save();

    /** Initializes the game, including the window, views, inputs, and other important start-up functions. */
    void init();

    /** Initializes the game the minimap */
    void initMinimap(UserInterface * interfaces);

    /** Processes the new inputs and updates states of mappings. */
    bool update();

}

#endif //RTMOBAS_GAME_SETTINGS_HPP
