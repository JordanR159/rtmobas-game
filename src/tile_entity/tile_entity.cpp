//
// Created by Killian Le Clainche on 6/3/2018.
//

#include "helper.hpp"

void TileEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if(selected) {
        states.blendMode = BlendMode(BlendMode::SrcColor, BlendMode::SrcAlpha, BlendMode::ReverseSubtract);
    }
    states.texture = texture;
    target.draw(vao, states);
}
