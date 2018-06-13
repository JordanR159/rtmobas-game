//
// Created by Killian Le Clainche on 5/31/2018.
//

#include "helper.hpp"

using namespace resources::structure;

Collector::Collector(World * world, int type) {
    switch(type) {
        case COLLECTOR_GOLD:
            this->create_held_entity(world, type, SIZE_OF_MINE, GOLD_MINE.get_texture());
            break;
        case COLLECTOR_METAL:
            this->create_held_entity(world, type, SIZE_OF_MINE, METAL_MINE.get_texture());
            break;
        case COLLECTOR_CRYSTAL:
            this->create_held_entity(world, type, SIZE_OF_MINE, CRYSTAL_HARVESTER.get_texture());
            break;
        case COLLECTOR_OIL:
            this->create_held_entity(world, type, SIZE_OF_MINE, OIL_DRILL.get_texture());
            break;
        default:
            this->create_held_entity(world, type, SIZE_OF_LOGGER, nullptr);
    }
}

Collector::Collector(World * world, int type, int x, int y) {
    switch(type) {
         case COLLECTOR_GOLD:
             this->create_tile_entity(world, type, x, y, SIZE_OF_MINE, GOLD_MINE.get_texture());
            break;
        case COLLECTOR_METAL:
            this->create_tile_entity(world, type, x, y, SIZE_OF_MINE, METAL_MINE.get_texture());
            break;
        case COLLECTOR_CRYSTAL:
            this->create_tile_entity(world, type, x, y, SIZE_OF_MINE, CRYSTAL_HARVESTER.get_texture());
            break;
        case COLLECTOR_OIL:
            this->create_tile_entity(world, type, x, y, SIZE_OF_MINE, OIL_DRILL.get_texture());
            break;
        default:
            this->create_tile_entity(world, type, x, y, SIZE_OF_LOGGER, nullptr);
    }
}

bool Collector::can_place() {
    return true;
}