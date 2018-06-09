//
// Created by Killian Le Clainche on 6/2/2018.
//

#include "helper.hpp"

/** NOTE - xposition and yposition are in units of tiles */
Resource::Resource(World * world, int type, int x, int y) {
    this->info.world = world;
    this->info.entity_type = type;

    this->info.texture = tile_entity::resource_textures[(type) - (RESOURCE_START_VALUE)];

    switch(type) {
        case RESOURCE_WOOD:
            this->width = WIDTH_OF_WOOD;
            this->height = HEIGHT_OF_WOOD;
            break;
        default:
            this->width = WIDTH_OF_RESOURCE;
            this->height = HEIGHT_OF_RESOURCE;
            break;
    }

    this->x_coord = x;
    this->y_coord = y;

    this->owned_tiles = (Tile ***) rpmalloc(this->width * sizeof(Tile **));

    for(int i = 0; i < this->width; i ++) {
        this->owned_tiles[i] = world->tiles[x + i] + y;

        for(int j = 0; j < this->height; j++) {
            this->owned_tiles[i][j]->resource = this;
        }
    }

    this->info.vao = generateVertices(static_cast<float>(this->x_coord * TILE_SIZE),
                                 static_cast<float>(this->y_coord * TILE_SIZE),
                                 static_cast<float>(this->width * TILE_SIZE),
                                 static_cast<float>(this->height * TILE_SIZE), *info.texture);
}

Resource::~Resource() {
    rpfree(this->owned_tiles);
}

void Resource::create_vao() {
}
