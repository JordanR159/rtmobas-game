//
// Created by Killian Le Clainche on 5/27/2018.
//

#ifndef RTMOBAS_GAME_SETTINGS_HPP
#define RTMOBAS_GAME_SETTINGS_HPP

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

        bool dragging = false;

        /** Called whenever any key code was pressed. */
        void press();

        /** Called whenever any key code was released. */
        void release();

        /** Called on every tick for calculations to be ran. */
        void update();

        //char * to_string();

        static const int MOUSE_DRAG_TOLERANCE;

        //Movement around the world
        static const int SCROLL_UP ;
        static const int SCROLL_DOWN;
        static const int SCROLL_LEFT;
        static const int SCROLL_RIGHT;

        //Mouse interactions
        static const int CLICK;

        //Hotkeys for UI
        static const int HOTKEY_BACK_COMMAND;
        static const int HOTKEY_BUILD_COLLECTORS;
        static const int HOTKEY_BUILD_FARM;

    };

    enum WindowMode {
        WINDOWED, BORDERLESS, FULLSCREEN
    };

    /** key (integer) -> Key Object for advanced processing */
    extern std::map<int, Key *> keyboard_mapping;
    /** mouse (integer) -> Key Object for advanced processing */
    extern std::map<int, Key *> mouse_mapping;

    extern std::map<int, Key *> input_mapping;

    // /** The monitor that the window is contained in (or at least the top left corner is located inside). */
    // Monitor monitor;

    /** The window object used by SFML, initialized by settings::init() */
    extern sf::RenderWindow window;

    /** The view (lens) that the player sees the world through. */
    extern sf::View world_view;

    /** Non-moving view (lens) that allows the player to see the displayed UI. */
    extern sf::View ui_view;
    extern sf::View minimap_view;

    /** Non-moving view (lens) that is used to draw mouse feedback */
    extern sf::View mouse_view;

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

    /** Processes the new inputs and updates states of mappings. */
    bool update();

}

#endif //RTMOBAS_GAME_SETTINGS_HPP
