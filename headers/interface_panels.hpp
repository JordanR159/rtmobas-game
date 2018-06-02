//
// Created by jorda on 6/1/2018.
//

#ifndef RTMOBAS_GAME_INTERFACE_PANELS_HPP
#define RTMOBAS_GAME_INTERFACE_PANELS_HPP

class CommandButton : public Drawable {
private:
    /** Allows window.draw(CommandButton) to be used in SFML */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    Texture texture;

    VertexArray vertices;
public:

    /** Position of the button on the ui view */
    int xposition;
    int yposition;

    int button_size;

    enum Types {
        MOVE
    };

    int type;

    /** Either directly affects the selected entity (production, hold position) or meant to be
     * pointed to by a function pointer so that the action can be done after a mouse click
     */
    void action(int xtarget = 0, int ytarget = 0);

    CommandButton() = default;
    CommandButton(int xposition, int yposition, int size, int type);

};

class EntityPanel : public Drawable {
private:
    /** Allows window.draw(EntityPanel) to be used in SFML */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    Texture texture;

    VertexArray vertices;
public:
    /** Position of the panel on the ui view */
    int xposition;
    int yposition;

    /** Size of the panel in pixels. Panel is rectangular with constant width but variable height */
    int panel_size_x;
    int panel_size_y;

    /** Buttons contained in the EntityPanel */
    vector<CommandButton> commands;

    enum Types {
        WORKER
    };

    int type;

    /** Constructors */
    EntityPanel() = default;
    EntityPanel(int xposition, int yposition, int size, int type);

};

class MinimapPanel : public Drawable {
private:
    /** Allows window.draw(EntityPanel) to be used in SFML */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    Texture texture;

    Texture map_layout;

    VertexArray vertices;

    VertexArray vertices_map;
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
    MinimapPanel(int xposition, int yposition, int size);
};

class InterfacePanels : public Drawable {
private:
    /** Allows window.draw(InterfacePanels) to be used in SFML */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    Texture texture;

    VertexArray vertices;

public:
    MinimapPanel minimap;
    EntityPanel entity_panel;

    /** Width and height for the interface panels */
    int interface_width;
    int interface_height;

    /** Constructors */
    InterfacePanels() = default;
    InterfacePanels(int width, int height);
};

#endif //RTMOBAS_GAME_INTERFACE_PANELS_HPP


