//
// Created by Killian Le Clainche on 6/3/2018.
//

#include "helper.hpp"

Castle::Castle(World * world, int type, int x, int y) {
    this->create_structure(world, type, x, y, 3, 3, resources::textures[resources::structure::CASTLE_TEXTURE]);

}
