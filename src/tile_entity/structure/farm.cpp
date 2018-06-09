//
// Created by Killian Le Clainche on 6/7/2018.
//

#include "helper.hpp"

Farm::Farm(World * world, int type, int x, int y) {
    this->create_structure(world, type, x, y, SIZE_OF_FARM, SIZE_OF_FARM, resources::textures[resources::structure::FARM_TEXTURE]);
}