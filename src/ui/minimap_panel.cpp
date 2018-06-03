//
// Created by Killian Le Clainche on 6/1/2018.
//

#include "helper.hpp"

using namespace resources;

MinimapPanel::MinimapPanel(int xposition, int yposition, int size) {
    this->xposition = xposition;
    this->yposition = yposition;
    this->panel_size = size;
    texture.loadFromFile("../resources/textures/entity_panel.png");
    map_layout.loadFromFile("../resources/maps/basic.bmp");
    vertices = generateVertices(this->xposition, this->yposition, panel_size, panel_size, texture);
    vertices_map = generateVertices(this->xposition + 2, this->yposition + 2, panel_size - 4, panel_size - 4, map_layout);
}

void MinimapPanel::update() {

}

void MinimapPanel::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.texture = &texture;
    target.draw(vertices, states);
    states.texture = &map_layout;
    target.draw(vertices_map, states);
}