//
// Created by Killian Le Clainche on 5/31/2018.
//

#include "helper.hpp"

Collector::Collector(World * world, int type, int x, int y) {
    sf::Texture * texture;

    int w, h;

    switch(type) {
        /* case STRUCTURE_COLLECTOR_FARM:
            break; */
        default:
            texture = resources::textures[resources::structure::FARM_TEXTURE];
            w = 2;
            h = 2;
            this->info.max_lifepoints = 1000;
    }

    this->create_tile_entity(world, type, x, y, w, h, texture);
    this->rally_set = false;
}