//
// Created by Killian Le Clainche on 6/2/2018.
//

#include "helper.hpp"

Resource::textures

/** NOTE - xposition and yposition are in units of tiles */
Resource::Resource(World * world, int type, int x, int y) {
    this->world = world;
    this->tile_entity_type = type;

    int w = WIDTH_OF_RESOURCE;
    int h = HEIGHT_OF_RESOURCE;

    this->texture = textures[type - RESOURCE_START_VALUE];

    switch(type) {
        case Resource::RESOURCE_GOLD:
            this->texture = textures[resource::GOLD_TEXTURE];
            break;
        case Resource::RESOURCE_WOOD:
            this->texture = textures[resource::TREE_TEXTURE];
            w = WIDTH_OF_WOOD;
            h = HEIGHT_OF_WOOD;
            break;
        case Resource::RESOURCE_METAL:
            this->texture = textures[resource::METAL_TEXTURE];
            break;
        case Resource::RESOURCE_CRYSTAL:
            this->texture = textures[resource::CRYSTAL_TEXTURE];
            break;
        /* case Resource::RESOURCE_OIL:
            texture = textures[resource::OIL_TEXTURE];
            break; */
        default:
            this->texture = textures[resource::OIL_TEXTURE];
            break;
    }

    this->x_coord = x;
    this->y_coord = y;

    this->width = w;
    this->height = h;

    this->owned_tiles = (Tile ***) rpmalloc(w * sizeof(Tile **));

    for(int i = 0; i < w; i ++) {
        this->owned_tiles[i] = world->tiles[x + i] + y;

        for(int j = 0; j < h; j++) {
            this->owned_tiles[i][j]->resource = this;
        }
    }

    this->vao = generateVertices(static_cast<float>(this->x_coord * TILE_SIZE),
                                 static_cast<float>(this->y_coord * TILE_SIZE),
                                 static_cast<float>(this->width * TILE_SIZE),
                                 static_cast<float>(this->height * TILE_SIZE), *texture);
}

Resource::~Resource() {
    rpfree(this->owned_tiles);
}

void Resource::create_vao() {
}
