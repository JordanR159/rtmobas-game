//
// Created by Killian Le Clainche on 5/31/2018.
//

#include "helper.hpp"

void Structure::claim_tiles() {
    TileEntity::claim_tiles();

    for(int i = 0; i < this->width; i++) {
        for(int j = 0; j < this->height; j++) {
            this->owned_tiles[i][j]->structure = this;
        }
    }
}

bool Structure::can_place() {
    return true;
}