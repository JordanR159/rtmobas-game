//
// Created by jorda on 6/11/2018.
//

#include "helper.hpp"

Selector::Selector() {
    this->select_texture = resources::load(resources::ui::SELECT_BOX_TEXTURE);
    this->select_box = generateVertices(0, 0, 1, 1, *this->select_texture);
    this->control_groups_tile_entities = (std::vector<TileEntity *> *)rpmalloc(NUMBER_TILE_ENTITY_GROUPS * sizeof(std::vector<TileEntity *>));
    this->control_groups_entities = (std::vector<Entity *> *)rpmalloc(NUMBER_ENTITY_GROUPS * sizeof(std::vector<Entity *>));
}

void Selector::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.texture = this->select_texture;
    target.draw(select_box, states);
}
