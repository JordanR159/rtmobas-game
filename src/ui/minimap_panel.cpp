//
// Created by Killian Le Clainche on 6/1/2018.
//

#include "helper.hpp"

MinimapPanel::MinimapPanel(int xposition, int yposition, int size, World * world) {
    this->world = world;
    this->xposition = xposition + 2;
    this->yposition = yposition + 2;
    this->panel_size = size - 4;

    texture = textures[ui::MINIMAP_PANEL_TEXTURE];
    camera_reticle = textures[ui::MINIMAP_RETICLE_TEXTURE];
    vertices = generateVertices(this->xposition - 2, this->yposition - 2, panel_size + 4, panel_size + 4, *texture);
    vertices_reticle = generateVertices(this->xposition, this->yposition, panel_size, panel_size, *camera_reticle);

    void *mem = rpmalloc(sizeof(Texture));
    map_layout = new(mem) Texture();
    (*map_layout).loadFromFile(world->map_layout_path);
    vertices_map = generateVertices(this->xposition, this->yposition, panel_size, panel_size, *map_layout);
}

void MinimapPanel::update() {
    auto new_x_position = static_cast<int>(settings::world_view.getCenter().x);
    auto new_y_position = static_cast<int>(settings::world_view.getCenter().y);
    auto new_x_view = static_cast<int>(settings::world_view.getSize().x * 2);
    auto new_y_view = static_cast<int>(settings::world_view.getSize().y);

    float map_length_x = vertices_map[2].position.x - vertices_map[0].position.x;
    float map_length_y = vertices_map[2].position.y - vertices_map[0].position.y;

    int world_width = world->world_width_tiles * TILE_SIZE;
    int world_height = world->world_height_tiles * TILE_SIZE;

    auto map_x = static_cast<int>(vertices_map[0].position.x + ((new_x_position - new_x_view / 2.0f) / (world_width / map_length_x)));
    auto map_y = static_cast<int>(vertices_map[0].position.y + ((new_y_position - new_y_view / 2.0f) / (world_height / map_length_y)));
    auto map_size_x = static_cast<int>(new_x_view / (world_width / map_length_x));
    auto map_size_y = static_cast<int>(new_y_view / (world_height / map_length_y));
    VertexArray box = generateVertices(map_x, map_y, map_size_x, map_size_y);
    Vector2f *points = rotateRectangle(Vector2f(map_x + map_size_x/2, map_y + map_size_y/2), &box, M_PI_4);
    vertices_reticle[0].position = points[0];
    vertices_reticle[1].position = points[1];
    vertices_reticle[2].position = points[2];
    vertices_reticle[3].position = points[3];
}

void MinimapPanel::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.texture = map_layout;
    target.draw(vertices_map, states);
    states.texture = camera_reticle;
    target.draw(vertices_reticle, states);
}