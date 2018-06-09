//
// Created by jorda on 6/1/2018.
//

#ifndef RTMOBAS_GAME_INTERFACE_PANELS_HPP
#define RTMOBAS_GAME_INTERFACE_PANELS_HPP

#include "helper.hpp"

class CommandButton;
class CommandPanel;
class MinimapPanel;

class Panel : public Drawable {
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

protected:
    World * world;

    /** Position of corners for entity, only needs to change just before rendering */
    sf::VertexArray vao;

    sf::Texture * texture;

    Panel * parent;

    std::vector<Panel *> children;

    void create_panel(World * world, Panel * parent, int type, int xpos, int ypos, int width, int height, Texture * texture);

public:

    /** Position of the button on the ui view */
    int x;
    int y;

    int width;
    int height;

    /** Subtype for the panel, as defined in the subclasses */
    int panel_type;

    virtual void update();

    ~Panel();

};

class CommandButton : public Panel {
private:
    /** Allows window.draw(CommandButton) to be used in SFML */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::RectangleShape highlight;

    Texture * get_texture();

    void press();

    void click();

public:

    int key;

    bool pressed;

    //Used to represent any empty location within the EntityPanel.
    static const int NULL_BUTTON = 0;

    //Used among many EntityPanel states, so kept as a reuse option.
    static const int BACK_BUTTON = 1;

    //Base Commands (given when nothing is selected).
    static const int BUILD_COLLECTORS = 100;

    //Build Collectors commands
    static const int BUILD_FARM = 201;

    CommandButton() = default;
    CommandButton(World * world, Panel * parent, int type, int xpos, int ypos, int size);

    void set(int type, int key);

    void update();
};

class CommandPanel : public Panel {
private:

    void set_options();
    void clear_options();

public:

    static const int BASE = 1;
    static const int BASE_BUILD_COLLECTORS = 2;

    /** Constructors */
    CommandPanel() = default;
    CommandPanel(World * world, Panel * panel, int type, int xpos, int ypos, int size);

};

class MinimapPanel : public Panel {
private:
    /** Allows window.draw(CommandButton) to be used in SFML */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    Texture * minimap_texture;
    sf::ConvexShape camera_view_box;

    VertexArray minimap_vao;

public:

    int inner_x;
    int inner_y;

    int inner_width;
    int inner_height;

    /** Constructors */
    MinimapPanel() = default;
    MinimapPanel(World * world, Panel * parent, int xpos, int ypos, int size);

    void update();
};

class UserInterface : public Panel {
public:
    /** Constructors */
    UserInterface() = default;
    UserInterface(World *, int, int);
};

#endif //RTMOBAS_GAME_INTERFACE_PANELS_HPP


