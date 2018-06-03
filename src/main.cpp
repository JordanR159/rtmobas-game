#include "helper.hpp"

using namespace sf;

int main()
{
    //start of every process for rpmalloc
    rpmalloc_initialize();
    settings::load();

    settings::init();

    settings::save();

    char *map_path = strdup("../resources/maps/basic.bmp");
    char *spawn_path = strdup("../resources/maps/basic.txt");
    World world(map_path, spawn_path);
    InterfacePanels interfaces(static_cast<int>(settings::ui_view.getSize().x), static_cast<int>(settings::ui_view.getSize().y), &world);

    settings::minimap_view.reset(FloatRect(interfaces.minimap.xposition, interfaces.minimap.yposition,
                                           interfaces.minimap.panel_size, interfaces.minimap.panel_size));
    settings::minimap_view.setViewport(FloatRect(static_cast<float>(interfaces.minimap.xposition)/settings::window_width,
                                            0.75f + static_cast<float>(interfaces.minimap.yposition)/settings::window_height,
                                                 static_cast<float>(interfaces.minimap.panel_size)/settings::window_width,
                                                 static_cast<float>(interfaces.minimap.panel_size)/settings::window_height));

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
        if(settings::world_view.getCenter().x > world.world_width_tiles * TILE_SIZE)
            settings::world_view.setCenter(world.world_width_tiles * TILE_SIZE, settings::world_view.getCenter().y);
        if(settings::world_view.getCenter().y < 0)
            settings::world_view.setCenter(settings::world_view.getCenter().x, 0);
        if(settings::world_view.getCenter().y > world.world_height_tiles * TILE_SIZE)
            settings::world_view.setCenter(settings::world_view.getCenter().x, world.world_height_tiles * TILE_SIZE);

        /** Set the zoom on the world view */
        settings::world_view.setSize(settings::window_width * settings::window_zoom,
                               settings::window_height * settings::window_zoom * 2);

        settings::window.clear();

        world.update();
        interfaces.update();

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