#include <SFML/Graphics.hpp>
#include <rpmalloc.h>
#include <world.hpp>

using namespace sf;

int main()
{
    //start of every process for rpmalloc
    rpmalloc_initialize();

    RenderWindow window(VideoMode(800, 600), "rtmobas-game");
    RectangleShape shape;
    shape.setSize(Vector2f(400, 100));
    shape.setFillColor(Color::Blue);

    Font font;
    if(!font.loadFromFile("../resources/fonts/BadhouseLight.ttf"))
        return -1;

    Text text("rtmobas-game", font, 80);
    text.setFillColor(Color::Green);
    World world(50, 50);
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if(event.type == Event::KeyPressed) {
                if (Keyboard::isKeyPressed(Keyboard::Up)) {
                    world.yoffset -= 10;
                    world.tiles_modified = true;
                }
                if (Keyboard::isKeyPressed(Keyboard::Down)) {
                    world.yoffset += 10;
                    world.tiles_modified = true;
                }
                if (Keyboard::isKeyPressed(Keyboard::Left)) {
                    world.xoffset -= 10;
                    world.tiles_modified = true;
                }
                if (Keyboard::isKeyPressed(Keyboard::Right)) {
                    world.xoffset += 10;
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