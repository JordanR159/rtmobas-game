#include "helper.hpp"

using namespace sf;
using namespace settings;

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

        /** Allows scrolling of world view */
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

        /** Note: selection boxes are currently sized correctly, however positioning is incorrect due to
         * complications created by the isomatric design of the world
         */
        if(settings::mouse_mapping[sf::Mouse::Left]->pressed) {
            settings::Key *mouse = settings::mouse_mapping[sf::Mouse::Left];
            int curr_x = Mouse::getPosition(settings::window).x;
            int curr_y = Mouse::getPosition(settings::window).y;
            if(!mouse->dragging)
            {
                int diff_x = abs(mouse->mouse_x - curr_x);
                int diff_y = abs(mouse->mouse_y - curr_y);
                if(sqrt(pow(diff_x, 2) + pow(diff_y, 2)) > settings::Key::MOUSE_DRAG_TOLERANCE)
                    mouse->dragging = true;
            }
            if(mouse->dragging) {
                /** Scaling accomadates for fact that world view height does not match window height */
                float height_scale = world_view.getSize().y / (window_height * 0.75f);

                /** The pivot point for when the selection box is rotated. Always location of initial click */
                int start_x = int(mouse->mouse_x + mouse->select_start.x - world_view.getSize().x/2);
                int start_y = int(mouse->mouse_y * height_scale + mouse->select_start.y - world_view.getSize().y / (2 * height_scale));

                /** Calculated to find the top left point of the box */
                int end_x = int(curr_x + world_view.getCenter().x - world_view.getSize().x/2);
                int end_y = int(curr_y * height_scale + world_view.getCenter().y - world_view.getSize().y / (2 * height_scale));

                /** Offset (top left point) for the selection box so that it appears in the correct area */
                int point_x = min(start_x, end_x);
                int point_y = min(start_y, end_y);

                int pivot_x = start_x - point_x;
                int pivot_y = start_y - point_y;

                /** Length of the box, adjusted to account for scaling differences */
                int length_x = abs(mouse->mouse_x - curr_x);
                int length_y = int(abs(mouse->mouse_y - curr_y) * height_scale);

                /** Rotates and scales a box about the pivot to match orientation of window */
                Vector2f *points = rotateRectangle(point_x, point_y, pivot_x, pivot_y, pivot_x - length_x,
                                                   pivot_y - length_y, 5 * M_PI_4);
                settings::select_box[0].position = points[0];
                settings::select_box[1].position = points[1];
                settings::select_box[2].position = points[2];
                settings::select_box[3].position = points[3];
            }
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

        if(settings::mouse_mapping[sf::Mouse::Left]->dragging) {
            RenderStates states(settings::select_texture);
            settings::window.draw(settings::select_box, states);
        }

        settings::window.setView(settings::ui_view);
        settings::window.draw(interfaces);

        /** Minimap has its own viewport drawn to prevent reticle from clipping into ui */
        settings::window.setView(settings::minimap_view);
        settings::window.draw(interfaces.minimap);

        settings::window.display();
    }

    //end of every process for rpmalloc
    rpmalloc_finalize();

    return 0;
}