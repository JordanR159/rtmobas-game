//
// Created by jorda on 6/1/2018.
//

#ifndef RTMOBAS_GAME_INTERFACE_PANELS_HPP
#define RTMOBAS_GAME_INTERFACE_PANELS_HPP

#include "helper.hpp"

/** Major panel type macros */
#define MINIMAP_PANEL -1
#define BASE_PANEL 2
#define BASE_BUILD_COLLECTORS 3

#define WIDTH_OF_BUTTON_TEXTURE 32

#define COMMAND_NULL 0
#define COMMAND_BACK 1
#define COMMAND_BUILD_COLLECTORS 2
#define COMMAND_BUILD_FARM 3
#define COMMAND_BUILD_GOLD_MINE 4
#define COMMAND_BUILD_METAL_MINE 5
#define COMMAND_BUILD_CRYSTAL_HARVESTER 6
#define COMMAND_BUILD_OIL_DRILL 7

#define NUMBER_CONTROL_GROUPS 10

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

    int get_key();

    void press();

    void click();

public:

    int key;

    bool pressed;

    CommandButton() = default;
    CommandButton(World * world, Panel * parent, int type, int xpos, int ypos, int size);

    void update();

    void set_panel_type(int new_panel_type);
};

class CommandPanel : public Panel {
private:

    int current_state;

    void set_options();
    void clear_options();

public:
    /** Constructors */
    CommandPanel() = default;
    CommandPanel(World * world, Panel * panel, int type, int xpos, int ypos, int size);

    void update();

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
    /** Used to retrieve a major panel on the interface */
    Panel * getPanel(int panel_type);

    /** Constructors */
    UserInterface() = default;
    UserInterface(World *, int, int);
};

class Selector : public sf::Drawable{
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    /** Texture for the selection box */
    sf::Texture * select_texture;
public:
    /** Vertices of the box being drawn by dragging the mouse, given in reference to the world view */
    sf::VertexArray select_box;

    /** List of entities selected by the mouse */
    std::vector<Entity *> selected_entities;

    /** Control groups for regular entities */
    std::vector<Entity *> * control_groups_entities;

    /** List of tile bound entities currently selected */
    std::vector<TileEntity *> selected_tile_entities;

    /** Control groups for tile entities */
    std::vector<TileEntity *> * control_groups_tile_entities;

    /** Constructor */
    Selector();
};

#endif //RTMOBAS_GAME_INTERFACE_PANELS_HPP


