#include <SFML/Graphics.hpp>
#include <rpmalloc.h>
#include <tile.hpp>

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
    Tile tiles[window.getSize().y/Tile::TILE_SIZE][window.getSize().x/Tile::TILE_SIZE];
    for(int r = 0; r < window.getSize().y/Tile::TILE_SIZE; r ++)
        for(int c = 0; c < window.getSize().x/Tile::TILE_SIZE; c ++)
            tiles[r][c] = Tile(r * Tile::TILE_SIZE, c * Tile::TILE_SIZE, Tile::PLAINS);
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            //Resizes drawing area of window, rescaling everything inside
            if (event.type == Event::Resized)
                window.setSize(Vector2u(event.size.width, event.size.height));

            window.clear();
            window.draw(shape);
            window.draw(text);
            for(int r = 0; r < window.getSize().y/Tile::TILE_SIZE; r ++)
                for(int c = 0; c < window.getSize().x/Tile::TILE_SIZE; c ++)
                    window.draw(tiles[r][c]);
            window.display();
        }
    }

    //end of every process for rpmalloc
    rpmalloc_finalize();

    return 0;
}