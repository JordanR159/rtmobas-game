#include <cmath>
#include <gtc/matrix_transform.hpp>
#include <helper.hpp>

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

    if((key = get_set_key(SCROLL_UP)) != nullptr) {
        settings::keyboard_mapping[sf::Keyboard::W] = key;
        settings::keyboard_mapping[sf::Keyboard::Up] = key;
    }

    if((key = get_set_key(SCROLL_DOWN)) != nullptr) {
        settings::keyboard_mapping[sf::Keyboard::S] = key;
        settings::keyboard_mapping[sf::Keyboard::Down] = key;
    }

    if((key = get_set_key(SCROLL_LEFT)) != nullptr) {
        settings::keyboard_mapping[sf::Keyboard::A] = key;
        settings::keyboard_mapping[sf::Keyboard::Left] = key;
    }

    if((key = get_set_key(SCROLL_RIGHT)) != nullptr) {
        settings::keyboard_mapping[sf::Keyboard::D] = key;
        settings::keyboard_mapping[sf::Keyboard::Right] = key;
    }

    settings::save();


    char *map_path = strdup("../resources/maps/basic.bmp");
    int *tile_info = readBMP(map_path);
    World world(tile_info);
    for(int i = 0; i < (tile_info[0]*tile_info[1]) + 2; i++){
        printf("%d\n", tile_info[i]);
    }

    double speed = 10.0;

    //glm::mat4 worldMatrix = glm::rotate(glm::rotate(glm::mat4(1.0), -M_PI / 180 * 45.0, glm::vec3(0, 0, 1)), -M_PI / 180 * 45.0, glm::vec3(0, 1, 0));

    while (settings::window.isOpen())
    {
        if(settings::update()) {

            Vector2f movement = Vector2f(0.0, 0.0);

            if(settings::input_mapping[SCROLL_UP]->pressed)
                movement.y -= speed;

            if(settings::input_mapping[SCROLL_DOWN]->pressed)
                movement.y += speed;

            if(settings::input_mapping[SCROLL_LEFT]->pressed)
                movement.x -= speed;

            if(settings::input_mapping[SCROLL_RIGHT]->pressed)
                movement.x += speed;

            if(fabs(movement.x) + fabs(movement.y) > speed)
                movement.y *= .7071067;

            world.xoffset += movement.x;

            world.yoffset += movement.y;

            settings::window.clear();
            settings::window.draw(world);
            settings::window.display();
        }
    }

    //end of every process for rpmalloc
    rpmalloc_finalize();

    return 0;
}