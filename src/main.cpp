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
    UserInterface interfaces(&world, static_cast<int>(ui_view.getSize().x), static_cast<int>(ui_view.getSize().y));
    initMinimap(&interfaces);

    double speed = 20.0;

    //glm::mat4 worldMatrix = glm::rotate(glm::rotate(glm::mat4(1.0), -M_PI / 180 * 45.0, glm::vec3(0, 0, 1)), -M_PI / 180 * 45.0, glm::vec3(0, 1, 0));
    while (window.isOpen())
    {
        update();

        Vector2f movement = Vector2f(0.0, 0.0);

        if(input_mapping[MOUSE_CLICK]->pressed) {
            Key *mouse = input_mapping[MOUSE_CLICK];
            int curr_x = Mouse::getPosition(window).x;
            int curr_y = Mouse::getPosition(window).y;
            if(!mouse->dragging)
            {
                int diff_x = abs(mouse->mouse_x - curr_x);
                int diff_y = abs(mouse->mouse_y - curr_y);
                if(sqrt(pow(diff_x, 2) + pow(diff_y, 2)) > SETTINGS_MOUSE_DRAG_TOLERANCE)
                    mouse->dragging = true;
            }
            if(mouse->dragging) {
                /** Scaling accomadates for fact that world view height does not match window height */
                float height_scale = world_view.getSize().y / (window_height * 0.75f * window_zoom);

                /** Rotates center to simplify translation between world view and window coordinates */
                Vector2f center;

                rotate(center, world_view.getCenter().x, world_view.getCenter().y, -M_PI_4);

                /** The pivot point for when the selection box is rotated. Always location of initial click */
                auto start_x = int(window_zoom * mouse->mouse_x + center.x - window_zoom * window_width/2.0);
                auto start_y = int(window_zoom * mouse->mouse_y * height_scale + center.y - window_zoom * window_height);

                /** Offset (top left point) for the selection box so that it appears in the correct area */
                Vector2f pivot;
                rotate(pivot, start_x, start_y, M_PI_4);

                /** Length of the box, adjusted to account for scaling differences */
                Vector2f length((curr_x - mouse->mouse_x) * window_zoom, (curr_y - mouse->mouse_y) * window_zoom * height_scale);

                /** Rotates and scales a box about the pivot to match orientation of window */
                VertexArray box = generateVertices(pivot.x, pivot.y, length.x, length.y);
                Vector2f *points = rotateRectangle(pivot, &box, M_PI_4);
                selector->select_box[0].position = points[0];
                selector->select_box[1].position = points[1];
                selector->select_box[2].position = points[2];
                selector->select_box[3].position = points[3];
            }
        }

        /** Allows scrolling of world view */
        else {
            if (input_mapping[KEY_SCROLL_UP]->pressed) {
                movement.x += speed;
                movement.y -= speed;
            }

            if (input_mapping[KEY_SCROLL_DOWN]->pressed) {
                movement.x -= speed;
                movement.y += speed;
            }

            if (input_mapping[KEY_SCROLL_LEFT]->pressed) {
                movement.x -= speed;
                movement.y -= speed;
            }

            if (input_mapping[KEY_SCROLL_RIGHT]->pressed) {
                movement.x += speed;
                movement.y += speed;
            }
        }

        if(input_mapping[MOUSE_CLICK]->clicked) {
            Key *mouse = input_mapping[MOUSE_CLICK];
            if(mouse->dragging) {
                world.selectEntities(selector->select_box);
                mouse->dragging = false;
            }
            else {
                /** Scaling accomadates for fact that world view height does not match window height */
                float height_scale = world_view.getSize().y / (window_height * 0.75f * window_zoom);

                /** Rotates center to simplify translation between world view and window coordinates */
                Vector2f center;
                rotate(center, world_view.getCenter().x, world_view.getCenter().y, -M_PI_4);

                /** The pivot point for when the selection box is rotated. Always location of initial click */
                auto start_x = window_zoom * mouse->mouse_x + center.x - window_zoom * window_width / 2.0f;
                auto start_y = window_zoom * mouse->mouse_y * height_scale + center.y - window_zoom * window_height;

                Vector2f point;
                rotate(point, start_x, start_y, M_PI_4);
                world.selectEntity(point);
            }
        }

        handleControlGroups();

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
        world_view.setSize(window_width * window_zoom, window_height * window_zoom * 2);

        window.clear();

        world.update();
        interfaces.update();

        /** Switch to and draw every viewport for the window */
        window.setView(world_view);
        window.draw(world);

        if(mouse_mapping[Mouse::Left]->dragging) {
            window.draw(*selector);
        }

        window.setView(ui_view);
        window.draw(interfaces);

        window.setView(minimap_view);
        window.draw(*interfaces.getPanel(MINIMAP_PANEL));

        window.display();
    }

    //end of every process for rpmalloc
    rpmalloc_finalize();

    return 0;
}