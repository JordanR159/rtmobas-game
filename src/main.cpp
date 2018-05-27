#include <SFML/Graphics.hpp>
#include <rpmalloc.h>

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
    if(!font.loadFromFile("../fonts/BadhouseLight.ttf"))
        return -1;

    Text text("rtmobas-game", font, 80);
    text.setFillColor(Color::Black);
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
            window.display();
        }
    }

    //end of every process for rpmalloc
    rpmalloc_finalize();

    return 0;
}