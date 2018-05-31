#include "helper.hpp"

using namespace sf;

int main()
{
    //start of every process for rpmalloc
    rpmalloc_initialize();

    RenderWindow window(VideoMode(800, 600), "rtmobas-game");
    RectangleShape shape;
    shape.setSize(Vector2f(300, 75));
    shape.setFillColor(Color::Blue);

    Font font;
    if(!font.loadFromFile("../resources/fonts/BadhouseLight.ttf"))
        return -1;

    Text text("rtmobas-game", font, 60);
    text.setFillColor(Color::Green);
    char *map_path = strdup("../resources/maps/basic.bmp");
    char *spawn_path = strdup("../resources/maps/basic.txt");
    World world(map_path, spawn_path);
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if(event.type == Event::KeyPressed) {
                if (Keyboard::isKeyPressed(Keyboard::Up)) {
                    world.yoffset -= 20;
                    world.tiles_modified = true;
                }
                if (Keyboard::isKeyPressed(Keyboard::Down)) {
                    world.yoffset += 20;
                    world.tiles_modified = true;
                }
                if (Keyboard::isKeyPressed(Keyboard::Left)) {
                    world.xoffset -= 20;
                    world.tiles_modified = true;
                }
                if (Keyboard::isKeyPressed(Keyboard::Right)) {
                    world.xoffset += 20;
                    world.tiles_modified = true;
                }
            }

            window.clear();
            window.draw(world);
            window.draw(shape);
            window.draw(text);
            window.display();
        }
    }

    //end of every process for rpmalloc
    rpmalloc_finalize();

    return 0;
}