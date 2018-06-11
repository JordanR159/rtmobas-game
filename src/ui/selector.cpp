//
// Created by jorda on 6/11/2018.
//

#include "helper.hpp"

Selector::Selector() {
    this->select_texture = resources::load(resources::ui::SELECT_BOX_TEXTURE);
    this->select_box = generateVertices(0, 0, 1, 1, *this->select_texture);
}

void Selector::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.texture = this->select_texture;
    target.draw(select_box, states);
}
