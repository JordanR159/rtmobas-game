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
    camera_reticle.loadFromFile("../resources/textures/reticle.png");
    vertices = generateVertices(this->xposition, this->yposition, panel_size, panel_size, texture);
    vertices_map = generateVertices(this->xposition + 2, this->yposition + 2, panel_size - 4, panel_size - 4, map_layout);
    vertices_reticle = generateVertices(this->xposition, this->yposition, panel_size, panel_size, camera_reticle);
}

void MinimapPanel::updateReticle(int xposition, int yposition, int xview, int yview, int xworld, int yworld) {
    float map_length_x = vertices_map[2].position.x - vertices_map[0].position.x;
    float map_length_y = vertices_map[2].position.y - vertices_map[0].position.y;
    int map_x = int(vertices_map[0].position.x + ((xposition - xview/2.0) / (xworld / map_length_x)));
    int map_y = int(vertices_map[0].position.y + ((yposition - yview/2.0) / (yworld / map_length_y)));
    int map_xsize = int(xview / (xworld / map_length_x));
    int map_ysize = int(yview / (yworld / map_length_y));
    int x = map_xsize / 2;
    int y = map_ysize / 2;
    Vector2f top_left = rotatePoint(-x, -y, M_PI_4);
    Vector2f top_right = rotatePoint(x, -y, M_PI_4);
    Vector2f bot_right = rotatePoint(x, y, M_PI_4);
    Vector2f bot_left = rotatePoint(-x, y, M_PI_4);
    vertices_reticle[0].position = Vector2f(map_x + x + top_left.x, map_y + y + top_left.y);
    vertices_reticle[1].position = Vector2f(map_x + x + top_right.x, map_y + y + top_right.y);
    vertices_reticle[2].position = Vector2f(map_x + x + bot_right.x, map_y + y + bot_right.y);
    vertices_reticle[3].position = Vector2f(map_x + x + bot_left.x, map_y + y + bot_left.y);
}

void MinimapPanel::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.texture = &texture;
    target.draw(vertices, states);
    states.texture = &map_layout;
    target.draw(vertices_map, states);
    states.texture = &camera_reticle;
    target.draw(vertices_reticle, states);
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
    target.draw(entity_panel);
}