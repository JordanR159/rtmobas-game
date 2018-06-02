//
// Created by jorda on 6/1/2018.
//

#include "helper.hpp"

CommandButton::CommandButton(int xposition, int yposition, int size, int type) {
    this->type = type;
    switch(type) {
        case MOVE:
            texture.loadFromFile("../resources/textures/move_command.png");
            break;
        default:
            texture.loadFromFile("../resources/textures/move_command.png");
            break;
    }
    button_size = size;
    this->xposition = xposition;
    this->yposition = yposition;
    vertices = generateVertices(this->xposition, this->yposition, button_size, button_size, texture);
}

void CommandButton::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.texture = &texture;
    target.draw(vertices, states);
}

EntityPanel::EntityPanel(int xposition, int yposition, int size, int type) {
    this->type = type;
    this->xposition = xposition;
    this->yposition = yposition;
    panel_size_x = 2 * size;
    panel_size_y = size;
    switch(type) {
        case WORKER:
            for(int x = xposition + panel_size_x / 16; x < xposition + panel_size_x; x += panel_size_x * 3/16) {
                for (int y = yposition + panel_size_y / 16; y < yposition + panel_size_y; y += panel_size_y * 5/16) {
                    commands.emplace_back(CommandButton(x, y, size / 4, CommandButton::MOVE));
                }
            }
            break;
        default:
            break;
    }
    texture.loadFromFile("../resources/textures/entity_panel.png");
    vertices = generateVertices(this->xposition, this->yposition, panel_size_x, panel_size_y, texture);
}

void EntityPanel::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.texture = &texture;
    target.draw(vertices, states);
    for(CommandButton c : commands) {
        target.draw(c);
    }
}

MinimapPanel::MinimapPanel(int xposition, int yposition, int size) {
    this->xposition = xposition;
    this->yposition = yposition;
    this->panel_size = size;
    texture.loadFromFile("../resources/textures/entity_panel.png");
    map_layout.loadFromFile("../resources/maps/basic.bmp");
    vertices = generateVertices(this->xposition, this->yposition, panel_size, panel_size, texture);
    vertices_map = generateVertices(this->xposition + 2, this->yposition + 2, panel_size - 4, panel_size - 4, map_layout);
}

void MinimapPanel::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.texture = &texture;
    target.draw(vertices, states);
    states.texture = &map_layout;
    target.draw(vertices_map, states);
}

InterfacePanels::InterfacePanels(int width, int height) {
    texture.loadFromFile("../resources/textures/interface_panels.png");
    interface_width = width;
    interface_height = height;
    entity_panel = EntityPanel(531, 11, 128, EntityPanel::WORKER);
    minimap = MinimapPanel(11, 11, 128);
    vertices = generateVertices(0, 0, interface_width, interface_height, texture);
}

void InterfacePanels::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.texture = &texture;
    target.draw(vertices, states);
    target.draw(minimap);
    target.draw(entity_panel);
}