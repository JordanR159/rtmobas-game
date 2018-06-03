//
// Created by Killian Le Clainche on 5/31/2018.
//

#include "helper.hpp"

using namespace resources;

Collector::Collector(int x, int y, int type, Tile *** tiles) {
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

    this->create_structure(x, y, w, h, type, texture, tiles);
}