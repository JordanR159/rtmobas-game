//
// Created by Killian Le Clainche on 5/31/2018.
//

#include "helper.hpp"

Structure::~Structure() {

}

void Structure::create_structure(int x, int y, int w, int h, int type, Texture * texture, Tile *** tiles) {
    this->tile_entity_type = type;

    this->x_coord = x;
    this->y_coord = y;

    this->width = w;
    this->height = h;

    this->curr_lifepoints = this->max_lifepoints;

    this->owned_tiles = (Tile ***) rpmalloc(w * sizeof(Tile **));

    for(int i = 0; i < w; i ++) {
        this->owned_tiles[i] = tiles[x + i] + y * sizeof(Tile *);

        for(int j = 0; j < h; j++) {
            this->owned_tiles[i][j]->structure = this;
        }
    }

    this->texture = texture;

    this->vao = generateVertices(static_cast<float>(this->x_coord * TILE_SIZE),
                                 static_cast<float>(this->y_coord * TILE_SIZE),
                                 static_cast<float>(this->width * TILE_SIZE),
                                 static_cast<float>(this->height * TILE_SIZE), *texture);
}