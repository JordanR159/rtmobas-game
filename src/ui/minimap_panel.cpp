//
// Created by Killian Le Clainche on 6/1/2018.
//

#include "helper.hpp"

MinimapPanel::MinimapPanel(World * world, Panel * parent, int xpos, int ypos, int size) {

    this->minimap_texture = new(rpmalloc(sizeof(Texture))) Texture();

    this->minimap_texture->loadFromFile(world->map_layout_path);

    int border_width = static_cast<int>(size * .0625);

    this->inner_x = xpos + border_width;
    this->inner_y = ypos + border_width;

    this->inner_width = this->inner_height = size - border_width * 2;

    this->minimap_vao = generateVertices(this->inner_x, this->inner_y, this->inner_width, this->inner_height, *(this->minimap_texture));

    this->camera_view_box.setPointCount(4);

    this->camera_view_box.setFillColor(Color::Transparent);
    this->camera_view_box.setOutlineColor(Color::White);
    this->camera_view_box.setOutlineThickness(2.0f);

    this->create_panel(world, parent, 0, xpos, ypos, size, size, resources::textures[resources::ui::MINIMAP_PANEL_TEXTURE]);
}

void MinimapPanel::update() {
    auto world_center_x = settings::world_view.getCenter().x;
    auto world_center_y = settings::world_view.getCenter().y;
    auto world_size_x = settings::world_view.getSize().x * 2;
    auto world_size_y = settings::world_view.getSize().y;

    int world_width = (world->world_width_tiles) * (TILE_SIZE);
    int world_height = (world->world_height_tiles) * (TILE_SIZE);

    auto map_x = x + ((world_center_x - world_size_x / 2.0f) / (world_width / this->width));
    auto map_y = y + ((world_center_y - world_size_y / 2.0f) / (world_height / this->height));
    auto map_xsize = (world_size_x / 2) / (world_width / this->width);
    auto map_ysize = (world_size_y / 2) / (world_height / this->height);

    Vector2f point1, point2, point3, point4;

    rotate(point1, map_x - map_xsize, map_y - map_ysize, M_PI_4);
    rotate(point2, map_x - map_xsize, map_y + map_ysize, M_PI_4);
    rotate(point3, map_x + map_xsize, map_y + map_ysize, M_PI_4);
    rotate(point4, map_x + map_xsize, map_y - map_ysize, M_PI_4);

    /*clamp_vec(point1, this->inner_x, this->inner_y, this->inner_width, this->inner_height);
    clamp_vec(point2, this->inner_x, this->inner_y, this->inner_width, this->inner_height);
    clamp_vec(point3, this->inner_x, this->inner_y, this->inner_width, this->inner_height);
    clamp_vec(point4, this->inner_x, this->inner_y, this->inner_width, this->inner_height);*/

    this->camera_view_box.setPoint(0, point1);
    this->camera_view_box.setPoint(1, point2);
    this->camera_view_box.setPoint(2, point3);
    this->camera_view_box.setPoint(3, point4);

}

void MinimapPanel::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.texture = this->texture;
    target.draw(this->vao, states);

    states.texture = this->minimap_texture;
    target.draw(this->minimap_vao, states);

    target.draw(this->camera_view_box);
}