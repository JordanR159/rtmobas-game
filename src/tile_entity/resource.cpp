//
// Created by Killian Le Clainche on 6/2/2018.
//

#include "helper.hpp"

Resource::Resource(World * world, int type, int x, int y) {
    switch(type) {
        case RESOURCE_WOOD:
            this->create_tile_entity(world, type, x, y, SIZE_OF_WOOD_RESOURCE, tile_entity::resource_textures[(type) - (RESOURCE_START_VALUE)]);
            break;
        default:
            this->create_tile_entity(world, type, x, y, SIZE_OF_BASE_RESOURCE, tile_entity::resource_textures[(type) - (RESOURCE_START_VALUE)]);
            break;
    }

    for(int i = 0; i < this->width; i++) {
        for(int j = 0; j < this->height; j++) {
            this->owned_tiles[i][j]->resource = this;
        }
    }
}

Resource::~Resource() {
    rpfree(this->owned_tiles);
}

void Resource::create_vao() {
}
