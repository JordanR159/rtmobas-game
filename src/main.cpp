#include <helper.hpp>
#include <world.hpp>

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
    int *tile_info = readBMP(map_path);
    World world(tile_info);
    for(int i = 0; i < (tile_info[0]*tile_info[1]) + 2; i++){
        printf("%d\n", tile_info[i]);
    }
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