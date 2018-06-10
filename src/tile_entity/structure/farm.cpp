//
// Created by Killian Le Clainche on 6/7/2018.
//

#include "helper.hpp"

Farm::Farm(World * world, int type) {
    this->create_held_entity(world, type, SIZE_OF_FARM, resources::textures[resources::structure::FARM_TEXTURE]);
}

Farm::Farm(World * world, int type, int x, int y) {
    this->create_tile_entity(world, type, x, y, SIZE_OF_FARM, resources::textures[resources::structure::FARM_TEXTURE]);
}

bool Farm::can_place() {
    for(int i = this->x_coord; i < this->x_coord + this->width; i++) {
        for(int j = this->y_coord; j < this->y_coord + this->height; j++) {
            if(this->info.world->tiles[i][j]->tile_type != TERRAIN_PLAINS)
                return false;
        }
    }
    return true;
}