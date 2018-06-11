//
// Created by Killian Le Clainche on 6/2/2018.
//

#include "helper.hpp"

namespace settings {

    std::map<int, Key *> keyboard_mapping;
    std::map<int, Key *> mouse_mapping;
    std::map<int, Key *> input_mapping;

    sf::RenderWindow window;
    sf::View world_view;
    sf::View ui_view;
    sf::View mouse_view;
    sf::View minimap_view;

    bool update_window = false;

    Panel * minimap;

    unsigned int window_width = 800;
    unsigned int window_height = 600;
    float window_zoom = 1.f;
    float minimap_ratio;

    void set_input(const std::string &key_string, const std::string &value_string, std::map<int, Key *> * mapping) {
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
        /*struct stat buffer{};

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
                    set_input(key, value, mapping);
            }
            input.close();
        }*/
    }

    Key * get_set_key(const int key_value) {
        if(input_mapping.find(key_value) == input_mapping.end()) {
            void * mem = rpmalloc(sizeof(settings::Key));
            Key * key = new(mem) Key();

            input_mapping[key_value] = key;

            return key;
        }
        return nullptr;
    }

    void set_key(const int key_value, std::map<int, Key *> * mapping, int code) {
        Key * key = get_set_key(key_value);

        if(key != nullptr)
            (*mapping)[code] = key;
    }

    void init() {
        window.create(sf::VideoMode(window_width, window_height), "RTM");

        window.setMouseCursorVisible(true);
        window.setMouseCursorGrabbed(false);
        window.setKeyRepeatEnabled(false);
        window.setVerticalSyncEnabled(true);

        window.setVisible(true);
        window.requestFocus();

        world_view.reset(sf::FloatRect(0, 0, window_width * window_zoom, window_height * window_zoom * 2));
        world_view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 0.75f));
        world_view.rotate(45);

        ui_view.reset(sf::FloatRect(0, 0, window_width, window_height * 0.25f));
        ui_view.setViewport(sf::FloatRect(0.f, 0.75f, 1.f, 0.25f));

        mouse_view.reset(sf::FloatRect(0, 0, window_width, window_height * 0.75f));
        mouse_view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 0.75f));

        /*
         * Creates all non-loaded key bindings (their defaults are assigned).
         */

        Key * key;

        if((key = get_set_key(KEY_SCROLL_UP)) != nullptr) {
            keyboard_mapping[sf::Keyboard::W] = key;
            keyboard_mapping[sf::Keyboard::Up] = key;
        }

        if((key = get_set_key(KEY_SCROLL_DOWN)) != nullptr) {
            keyboard_mapping[sf::Keyboard::S] = key;
            keyboard_mapping[sf::Keyboard::Down] = key;
        }

        if((key = get_set_key(KEY_SCROLL_LEFT)) != nullptr) {
            keyboard_mapping[sf::Keyboard::A] = key;
            keyboard_mapping[sf::Keyboard::Left] = key;
        }

        if((key = get_set_key(KEY_SCROLL_RIGHT)) != nullptr) {
            keyboard_mapping[sf::Keyboard::D] = key;
            keyboard_mapping[sf::Keyboard::Right] = key;
        }

        set_key(MOUSE_CLICK, &mouse_mapping, sf::Mouse::Left);

        set_key(KEY_BACK_COMMAND, &keyboard_mapping, sf::Keyboard::B);
        set_key(KEY_BUILD_COLLECTORS, &keyboard_mapping, sf::Keyboard::C);
        set_key(KEY_BUILD_FARM, &keyboard_mapping, sf::Keyboard::F);

    }

    void initMinimap(UserInterface * interfaces) {
        minimap = interfaces->getPanel(MINIMAP_PANEL);
        auto offset = static_cast<float>(minimap->width * sqrt(2)) - minimap->width;
        minimap_view.reset(sf::FloatRect(minimap->x - offset/2, minimap->y - offset/2,
                                         minimap->width + offset, minimap->height + offset));
        minimap_view.setViewport(sf::FloatRect(static_cast<float>(minimap->x)/window_width,
                                           0.75f + static_cast<float>(minimap->y)/window_height,
                                           static_cast<float>(minimap->width * 2)/window_width,
                                           static_cast<float>(minimap->height)/window_height));
        minimap_view.setRotation(45);
        minimap_ratio = (minimap_view.getViewport().width * window_width) / (minimap_view.getViewport().height * window_height);
    }

    void save() {
        /*std::ofstream output;
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
        }*/
    }

    bool update() {
        sf::Event event{};

        bool events = false;

        for(auto &iter : keyboard_mapping) {
            iter.second->update();
        }

        for(auto &iter : mouse_mapping) {
            iter.second->update();
        }

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
                key->dragging = false;
            }

            if(event.type == sf::Event::MouseButtonReleased && mouse_mapping.find(event.mouseButton.button) != mouse_mapping.end()) {

                auto * key = mouse_mapping[event.mouseButton.button];

                key->release();
                key->mouse_x = event.mouseButton.x;
                key->mouse_y = event.mouseButton.y;
            }

            /* Translates mouse wheel scroll into a zoom for the world view */
            if(event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {

                window_zoom -= event.mouseWheelScroll.delta * 0.15;
                if(window_zoom < 0.25) {
                    window_zoom = 0.25;
                }
                else if(window_zoom > 1.5) {
                    window_zoom = 1.5;
                }
            }

            /*
             * Resizes view so that the size of individual objects is unchanged, and instead a different
             * number of objects is shown on the world view
             */
            if(event.type == sf::Event::Resized) {
                window_width = event.size.width;
                window_height = event.size.height;

                /** Resizes minimap in a way that preserves shape */
                minimap_view.setViewport(sf::FloatRect(static_cast<float>(minimap->x)/window_width,
                                                       0.75f + static_cast<float>(minimap->y)/window_height,
                                                       (minimap_ratio * minimap_view.getViewport().height * window_height) / window_width,
                                                       minimap_view.getViewport().height));
            }

            if(event.type == sf::Event::MouseMoved) {

            }
        }

        return events;
    }
}
