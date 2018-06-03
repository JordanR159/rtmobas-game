#include "helper.hpp"

using namespace sf;

settings::Key * get_set_key(const int key_value) {
    if(settings::input_mapping.find(key_value) == settings::input_mapping.end()) {
        void * mem = rpmalloc(sizeof(settings::Key));
        settings::Key * key = new(mem) settings::Key();

        settings::input_mapping[key_value] = key;

        return key;
    }
    return nullptr;
}

int main()
{
    //start of every process for rpmalloc
    rpmalloc_initialize();
    settings::load();

    settings::init();
    settings::Key * key;

    if((key = get_set_key(settings::Key::SCROLL_UP)) != nullptr) {
        settings::keyboard_mapping[sf::Keyboard::W] = key;
        settings::keyboard_mapping[sf::Keyboard::Up] = key;
    }

    if((key = get_set_key(settings::Key::SCROLL_DOWN)) != nullptr) {
        settings::keyboard_mapping[sf::Keyboard::S] = key;
        settings::keyboard_mapping[sf::Keyboard::Down] = key;
    }

    if((key = get_set_key(settings::Key::SCROLL_LEFT)) != nullptr) {
        settings::keyboard_mapping[sf::Keyboard::A] = key;
        settings::keyboard_mapping[sf::Keyboard::Left] = key;
    }

    if((key = get_set_key(settings::Key::SCROLL_RIGHT)) != nullptr) {
        settings::keyboard_mapping[sf::Keyboard::D] = key;
        settings::keyboard_mapping[sf::Keyboard::Right] = key;
    }
    settings::save();

    char *map_path = strdup("../resources/maps/basic.bmp");
    char *spawn_path = strdup("../resources/maps/basic.txt");
    World world(map_path, spawn_path);
    InterfacePanels interfaces(int(settings::ui_view.getSize().x), int(settings::ui_view.getSize().y));

    settings::minimap_view.reset(FloatRect(interfaces.minimap.xposition, interfaces.minimap.yposition,
                                           interfaces.minimap.panel_size, interfaces.minimap.panel_size));
    settings::minimap_view.setViewport(FloatRect(float(interfaces.minimap.xposition)/settings::window_width,
                                            0.75f + float(interfaces.minimap.yposition)/settings::window_height,
                                            float(interfaces.minimap.panel_size)/settings::window_width,
                                            float(interfaces.minimap.panel_size)/settings::window_height));

    double speed = 20.0;

    //glm::mat4 worldMatrix = glm::rotate(glm::rotate(glm::mat4(1.0), -M_PI / 180 * 45.0, glm::vec3(0, 0, 1)), -M_PI / 180 * 45.0, glm::vec3(0, 1, 0));
    while (settings::window.isOpen())
    {
        settings::update();

        Vector2f movement = Vector2f(0.0, 0.0);

        if(settings::input_mapping[settings::Key::SCROLL_UP]->pressed) {
            movement.x += speed;
            movement.y -= speed;
        }

        if(settings::input_mapping[settings::Key::SCROLL_DOWN]->pressed) {
            movement.x -= speed;
            movement.y += speed;
        }

        if(settings::input_mapping[settings::Key::SCROLL_LEFT]->pressed) {
            movement.x -= speed;
            movement.y -= speed;
        }

        if(settings::input_mapping[settings::Key::SCROLL_RIGHT]->pressed) {
            movement.x += speed;
            movement.y += speed;
        }

        settings::world_view.move(movement.x, movement.y);

        /** Prevent world view from going too far off of the world */
        if(settings::world_view.getCenter().x < 0)
            settings::world_view.setCenter(0, settings::world_view.getCenter().y);
        if(settings::world_view.getCenter().x > world.world_width)
            settings::world_view.setCenter(world.world_width, settings::world_view.getCenter().y);
        if(settings::world_view.getCenter().y < 0)
            settings::world_view.setCenter(settings::world_view.getCenter().x, 0);
        if(settings::world_view.getCenter().y > world.world_height)
            settings::world_view.setCenter(settings::world_view.getCenter().x, world.world_height);

        /** Set the zoom on the world view */
        settings::world_view.setSize(settings::window_width * settings::window_zoom,
                               settings::window_height * settings::window_zoom * 2);
        interfaces.minimap.updateReticle(int(settings::world_view.getCenter().x), int(settings::world_view.getCenter().y),
            int(settings::world_view.getSize().x*2), int(settings::world_view.getSize().y),
            int(world.world_width), int(world.world_height));

        settings::window.clear();

        /** Switch to and draw every viewport for the window */
        settings::window.setView(settings::world_view);
        settings::window.draw(world);

        settings::window.setView(settings::ui_view);
        settings::window.draw(interfaces);

        settings::window.setView(settings::minimap_view);
        settings::window.draw(interfaces.minimap);

        settings::window.display();
    }

    //end of every process for rpmalloc
    rpmalloc_finalize();

    return 0;
}