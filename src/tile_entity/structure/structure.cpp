//
// Created by Killian Le Clainche on 5/31/2018.
//

#include "helper.hpp"

Structure::~Structure() {

}

void Structure::create_structure(World * world, int type, int x, int y, int w, int h, Texture * texture) {
    this->info.world = world;
    this->info.entity_type = type;

    this->x_coord = x;
    this->y_coord = y;

    this->width = w;
    this->height = h;

    this->info.curr_lifepoints = this->info.max_lifepoints;

    this->owned_tiles = (Tile ***) rpmalloc(w * sizeof(Tile **));

    for(int i = 0; i < w; i ++) {
        this->owned_tiles[i] = world->tiles[x + i] + y;

        for(int j = 0; j < h; j++) {
            this->owned_tiles[i][j]->structure = this;
        }
    }

    this->info.texture = texture;

    this->info.vao = generateVertices(static_cast<float>(this->x_coord * TILE_SIZE),
                                 static_cast<float>(this->y_coord * TILE_SIZE),
                                 static_cast<float>(this->width * TILE_SIZE),
                                 static_cast<float>(this->height * TILE_SIZE), *texture);
}