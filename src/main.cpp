#include "helper.hpp"

using namespace sf;
using namespace settings;

int main()
{
    //start of every process for rpmalloc
    rpmalloc_initialize();
    load();

    init();

    save();

    char *map_path = strdup("../resources/maps/basic.bmp");
    char *spawn_path = strdup("../resources/maps/basic.txt");
    World world(map_path, spawn_path);
    InterfacePanels interfaces(static_cast<int>(ui_view.getSize().x), static_cast<int>(ui_view.getSize().y), &world);

    minimap_view.reset(FloatRect(interfaces.minimap.xposition, interfaces.minimap.yposition,
                                           interfaces.minimap.panel_size, interfaces.minimap.panel_size));
    minimap_view.setViewport(FloatRect(static_cast<float>(interfaces.minimap.xposition)/window_width,
                                            0.75f + static_cast<float>(interfaces.minimap.yposition)/window_height,
                                                 static_cast<float>(interfaces.minimap.panel_size)/window_width,
                                                 static_cast<float>(interfaces.minimap.panel_size)/window_height));

    double speed = 20.0;

    //glm::mat4 worldMatrix = glm::rotate(glm::rotate(glm::mat4(1.0), -M_PI / 180 * 45.0, glm::vec3(0, 0, 1)), -M_PI / 180 * 45.0, glm::vec3(0, 1, 0));
    while (window.isOpen())
    {
        update();

        Vector2f movement = Vector2f(0.0, 0.0);

        if(mouse_mapping[Mouse::Left]->pressed) {
            Key *mouse = mouse_mapping[Mouse::Left];
            int curr_x = Mouse::getPosition(window).x;
            int curr_y = Mouse::getPosition(window).y;
            if(!mouse->dragging)
            {
                int diff_x = abs(mouse->mouse_x - curr_x);
                int diff_y = abs(mouse->mouse_y - curr_y);
                if(sqrt(pow(diff_x, 2) + pow(diff_y, 2)) > Key::MOUSE_DRAG_TOLERANCE)
                    mouse->dragging = true;
            }
            if(mouse->dragging) {
                /** Scaling accomadates for fact that world view height does not match window height */
                float height_scale = world_view.getSize().y / (window_height * 0.75f * window_zoom);

                /** Rotates center to simplify translation between world view and window coordinates */
                Vector2f center = rotatePoint(int(world_view.getCenter().x), int(world_view.getCenter().y), -M_PI_4);

                /** The pivot point for when the selection box is rotated. Always location of initial click */
                auto start_x = int(window_zoom * mouse->mouse_x + center.x - window_zoom * window_width/2.0);
                auto start_y = int(window_zoom * mouse->mouse_y * height_scale + center.y - window_zoom * window_height);

                /** Calculated to find the top left point of the box */
                auto end_x = int(window_zoom * curr_x + center.x - window_zoom * window_width/2.0);
                auto end_y = int(window_zoom * curr_y * height_scale + center.y - window_zoom * window_height);

                /** Offset (top left point) for the selection box so that it appears in the correct area */
                Vector2f point = rotatePoint(start_x, start_y, M_PI_4);

                /** Length of the box, adjusted to account for scaling differences */
                Vector2f length(abs(mouse->mouse_x - curr_x) * window_zoom, int(abs(mouse->mouse_y - curr_y) * window_zoom * height_scale));

                /** Determines how to rotate selection box */
                int rotation = 0;
                if(start_x > end_x) {
                    if(start_y > end_y)
                        rotation = 5;
                    else {
                        rotation = 3;
                        float temp = length.x;
                        length.x = length.y;
                        length.y = temp;
                    }
                }
                else {
                    if(start_y < end_y)
                        rotation = 1;
                    else {
                        rotation = 7;
                        float temp = length.x;
                        length.x = length.y;
                        length.y = temp;
                    }
                }

                /** Rotates and scales a box about the pivot to match orientation of window */
                Vector2f *points = rotateRectangle(point.x, point.y, 0, 0, length.x, length.y, rotation * M_PI_4);
                select_box[0].position = points[0];
                select_box[1].position = points[1];
                select_box[2].position = points[2];
                select_box[3].position = points[3];
            }
        }

        /** Allows scrolling of world view */
        else {
            if (input_mapping[Key::SCROLL_UP]->pressed) {
                movement.x += speed;
                movement.y -= speed;
            }

            if (input_mapping[Key::SCROLL_DOWN]->pressed) {
                movement.x -= speed;
                movement.y += speed;
            }

            if (input_mapping[Key::SCROLL_LEFT]->pressed) {
                movement.x -= speed;
                movement.y -= speed;
            }

            if (input_mapping[Key::SCROLL_RIGHT]->pressed) {
                movement.x += speed;
                movement.y += speed;
            }
        }

        if(mouse_mapping[Mouse::Left]->clicked) {
            Key *mouse = mouse_mapping[Mouse::Left];

            /** Scaling accomadates for fact that world view height does not match window height */
            float height_scale = world_view.getSize().y / (window_height * 0.75f * window_zoom);

            /** Rotates center to simplify translation between world view and window coordinates */
            Vector2f center = rotatePoint(int(world_view.getCenter().x), int(world_view.getCenter().y), -M_PI_4);

            /** The pivot point for when the selection box is rotated. Always location of initial click */
            auto start_x = int(window_zoom * mouse->mouse_x + center.x - window_zoom * window_width/2.0);
            auto start_y = int(window_zoom * mouse->mouse_y * height_scale + center.y - window_zoom * window_height);

            Vector2f point = rotatePoint(start_x, start_y, M_PI_4);
            world.select_entity(point);
        }

        world_view.move(movement.x, movement.y);

        /** Prevent world view from going too far off of the world */
        if(world_view.getCenter().x < 0)
            world_view.setCenter(0, world_view.getCenter().y);
        if(world_view.getCenter().x > world.world_width_tiles * TILE_SIZE)
            world_view.setCenter(world.world_width_tiles * TILE_SIZE, world_view.getCenter().y);
        if(world_view.getCenter().y < 0)
            world_view.setCenter(world_view.getCenter().x, 0);
        if(world_view.getCenter().y > world.world_height_tiles * TILE_SIZE)
            world_view.setCenter(world_view.getCenter().x, world.world_height_tiles * TILE_SIZE);

        /** Set the zoom on the world view */
        world_view.setSize(window_width * window_zoom,
                               window_height * window_zoom * 2);

        window.clear();

        world.update();
        interfaces.update();

        /** Switch to and draw every viewport for the window */
        window.setView(world_view);
        window.draw(world);

        if(mouse_mapping[Mouse::Left]->dragging) {
            RenderStates states(select_texture);
            window.draw(select_box, states);
        }

        window.setView(ui_view);
        window.draw(interfaces);

        /** Minimap has its own viewport drawn to prevent reticle from clipping into ui */
        window.setView(minimap_view);
        window.draw(interfaces.minimap);

        window.display();
    }

    //end of every process for rpmalloc
    rpmalloc_finalize();

    return 0;
}