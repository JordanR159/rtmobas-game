//
// Created by jorda on 6/1/2018.
//

#ifndef RTMOBAS_GAME_INTERFACE_PANELS_HPP
#define RTMOBAS_GAME_INTERFACE_PANELS_HPP

class CommandButton;
class EntityPanel;
class MinimapPanel;
class InterfacePanels;

class CommandButton : public Drawable {
private:
    /** Allows window.draw(CommandButton) to be used in SFML */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    Texture * get_texture();

    VertexArray vertices;

    Texture * texture;

    sf::RectangleShape highlight;

public:

    /** Position of the button on the ui view */
    int xposition;
    int yposition;

    int button_size;

    int type;

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
    CommandButton(int xposition, int yposition, int size, int type);

    void set(int type, int key);

    void press();

    int click(EntityPanel * panel);

};

class EntityPanel : public Drawable {
private:
    /** Allows window.draw(EntityPanel) to be used in SFML */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void set_options();
    void clear_options();

    Texture texture;

    VertexArray vertices;

protected:
    World * world;

public:
    /** Position of the panel on the ui view */
    int xposition;
    int yposition;

    /** Size of the panel in pixels. Panel is rectangular with constant width but variable height */
    int panel_size_x;
    int panel_size_y;

    /** Buttons contained in the EntityPanel */
    vector<CommandButton> commands;

    static const int BASE = 1;
    static const int BASE_BUILD_COLLECTORS = 2;

    int type;

    /** Constructors */
    EntityPanel() = default;
    EntityPanel(int xposition, int yposition, int size, int type, World * world);

    void update();

};

class MinimapPanel : public Drawable {
private:
    /** Allows window.draw(EntityPanel) to be used in SFML */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    Texture texture;
    Texture map_layout;
    Texture camera_reticle;

    VertexArray vertices;
    VertexArray vertices_map;
    VertexArray vertices_reticle;

protected:

    World * world;

public:
    /** Position of the panel on the ui view */
    int xposition;
    int yposition;

    /** Size of the panel in pixels. Panel is square */
    int panel_size;

    /** Buttons contained in the EntityPanel */
    list<CommandButton> commands;

    /** Constructors */
    MinimapPanel() = default;
    MinimapPanel(int xposition, int yposition, int size, World * world);

    void update();
};

class InterfacePanels : public Drawable {
private:
    /** Allows window.draw(InterfacePanels) to be used in SFML */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    VertexArray vertices;

    Texture * texture;

protected:
    World * world;

public:
    MinimapPanel minimap;
    EntityPanel entity_panel;

    /** Width and height for the interface panels */
    int interface_width;
    int interface_height;

    /** Constructors */
    InterfacePanels() = default;
    InterfacePanels(int width, int height, World * world);

    ~InterfacePanels();

    void update();
};

#endif //RTMOBAS_GAME_INTERFACE_PANELS_HPP


