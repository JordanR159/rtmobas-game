//
// Created by jorda on 6/1/2018.
//

#ifndef RTMOBAS_GAME_INTERFACE_PANELS_HPP
#define RTMOBAS_GAME_INTERFACE_PANELS_HPP

#include "helper.hpp"

class Panel : public sf::Drawable {
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

protected:
    World * world;

    /** Position of corners for entity, only needs to change just before rendering */
    sf::VertexArray vao;

    sf::Texture * texture;

    Panel * parent;

    std::vector<Panel *> children;

    void create_panel(World * world, Panel * parent, int type, int xpos, int ypos, int width, int height, sf::Texture * texture);

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

    virtual void set_panel_type(int new_panel_type);

};

class CommandButton : public Panel {
private:
    /** Allows window.draw(CommandButton) to be used in SFML */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::RectangleShape highlight;

    sf::Texture * get_texture();

    int get_key();

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

    void set_panel_type(int new_panel_type);
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

    void set_panel_type(int new_panel_type);

};

class MinimapPanel : public Panel {
private:
    /** Allows window.draw(CommandButton) to be used in SFML */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Texture * minimap_texture;
    sf::ConvexShape camera_view_box;

    sf::VertexArray minimap_vao;

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

class Selector {
public:
    /** Vertices of the box being drawn by dragging the mouse, given in reference to the world view */
    sf::VertexArray select_box;

    /** Texture for the selection box */
    sf::Texture * select_texture;

    /** List of entities selected by the mouse */
    std::vector<Entity *> selected_entities;

    /** List of tile bound entities selected by the mouse */
    std::vector<TileEntity *> selected_tile_entities;

    /** Constructor */
    Selector() = default;
};

#endif //RTMOBAS_GAME_INTERFACE_PANELS_HPP


