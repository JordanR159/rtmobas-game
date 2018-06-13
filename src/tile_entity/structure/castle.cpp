//
// Created by Killian Le Clainche on 6/3/2018.
//

#include "helper.hpp"

Castle::Castle(World * world, int type, int x, int y) {
    this->create_tile_entity(world, type, x, y, SIZE_OF_CASTLE, resources::textures[resources::structure::CASTLE_TEXTURE]);
}
