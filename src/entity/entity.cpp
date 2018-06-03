//
// Created by jorda on 5/30/2018.
//

#include "helper.hpp"

using namespace resources;

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.texture = texture;
    target.draw(vao, states);
}
