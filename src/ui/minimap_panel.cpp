//
// Created by Killian Le Clainche on 6/1/2018.
//

#include "helper.hpp"

using namespace resources;

MinimapPanel::MinimapPanel(int xposition, int yposition, int size, World * world) {
    this->world = world;
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

void MinimapPanel::update() {
    int new_x_position = static_cast<int>(settings::world_view.getCenter().x);
    int new_y_position = static_cast<int>(settings::world_view.getCenter().y);
    int new_x_view = static_cast<int>(settings::world_view.getSize().x * 2);
    int new_y_view = static_cast<int>(settings::world_view.getSize().y);

    float map_length_x = vertices_map[2].position.x - vertices_map[0].position.x;
    float map_length_y = vertices_map[2].position.y - vertices_map[0].position.y;

    int world_width = world->world_width_tiles * TILE_SIZE;
    int world_height = world->world_height_tiles * TILE_SIZE;

    int map_x = static_cast<int>(vertices_map[0].position.x + ((new_x_position - new_x_view / 2.0f) / (world_width / map_length_x)));
    int map_y = static_cast<int>(vertices_map[0].position.y + ((new_y_position - new_y_view / 2.0f) / (world_height / map_length_y)));
    int map_xsize = static_cast<int>(new_x_view / (world_width / map_length_x));
    int map_ysize = static_cast<int>(new_y_view / (world_height / map_length_y));
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