//
// Created by Killian Le Clainche on 5/31/2018.
//

#include "helper.hpp"

using namespace resources;

Collector::Collector(World * world, int type, int x, int y) {
    Texture * texture;

    int w, h;

    switch(type) {
        /* case STRUCTURE_COLLECTOR_FARM:
            break; */
        default:
            texture = textures[structure::FARM_TEXTURE];
            w = 2;
            h = 2;
            this->max_lifepoints = 1000;
    }

    this->create_structure(world, type, x, y, w, h, texture);
}