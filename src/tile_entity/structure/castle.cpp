//
// Created by Killian Le Clainche on 6/3/2018.
//

#include "helper.hpp"

Castle::Castle(int x, int y, Tile *** tiles) {
    this->create_structure(x, y, 3, 3, PRODUCER_CASTLE, resources::textures[resources::structure::CASTLE_TEXTURE], tiles);

}
