//
// Created by Killian Le Clainche on 6/3/2018.
//

#include "helper.hpp"

void TileEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if(selected) {
        states.blendMode = sf::BlendMode(sf::BlendMode::SrcColor, sf::BlendMode::SrcAlpha, sf::BlendMode::ReverseSubtract);
    }
    states.texture = info.texture;
    target.draw(info.vao, states);
}

namespace tile_entity {
    sf::Texture * resource_textures[6];

    std::map<int, Structure *(*)(World *, int, int, int)> structures;

    void init() {

        resource_textures[0] = resources::textures[resources::resource::FOOD_TEXTURE];
        resource_textures[1] = resources::textures[resources::resource::GOLD_TEXTURE];
        resource_textures[2] = resources::textures[resources::resource::TREE_TEXTURE];
        resource_textures[3] = resources::textures[resources::resource::METAL_TEXTURE];
        resource_textures[4] = resources::textures[resources::resource::CRYSTAL_TEXTURE];
        resource_textures[5] = resources::textures[resources::resource::OIL_TEXTURE];

        structures[PRODUCER_CASTLE] = &create_structure<Castle>;

        structures[COLLECTOR_FOOD] = &create_structure<Farm>;
        for(int i = COLLECTOR_START_VALUE + 1; i <= COLLECTOR_LAST_VALUE; i++) {
            structures[i] = &create_structure<Collector>;
        }
    }
}
