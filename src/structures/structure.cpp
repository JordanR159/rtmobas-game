//
// Created by Killian Le Clainche on 5/31/2018.
//

#include "helper.hpp"

using namespace resources;

/** NOTE - xposition and yposition are in units of tiles */
Structure::Structure(int xposition, int yposition, int type) {
    Texture * texture;
    switch(type) {
        case Structure::PRODUCER_CASTLE:
            texture = textures[structure::CASTLE_TEXTURE];
            xsize = 3;
            ysize = 3;
            has_ground_collision = true;
            max_lifepoints = 1000;
            break;
        case Structure::COLLECTOR_FOOD:
            texture = textures[structure::FARM_TEXTURE];
            xsize = 2;
            ysize = 2;
            has_ground_collision = true;
            max_lifepoints = 200;
            break;
        default:
            texture = textures[structure::FARM_TEXTURE];
            xsize = 1;
            ysize = 1;
            has_ground_collision = false;
            max_lifepoints = INT32_MAX;
            break;
    }
    this->type = type;
    this->xposition = xposition * Tile::TILE_SIZE;
    this->yposition = yposition * Tile::TILE_SIZE;
    xsize *= Tile::TILE_SIZE;
    ysize *= Tile::TILE_SIZE;
    xrally = xposition;
    yrally = yposition;
    curr_lifepoints = max_lifepoints;
    vertices = generateVertices(this->xposition, this->yposition, xsize, ysize, *texture);
}