//
// Created by Killian Le Clainche on 6/2/2018.
//

#include "helper.hpp"

using namespace resources;

/** NOTE - xposition and yposition are in units of pixels */
Unit::Unit(double x, double y, int type) {
    Texture * texture;
    switch(type) {
        case Unit::UNIT_BUILDER:
            texture = textures[unit::PEASANT_TEXTURE];
            this->width = 16;
            this->height = 32;
            this->info.max_lifepoints = INT32_MAX;
            break;
        default:
            texture = textures[unit::PEASANT_TEXTURE];
            break;
    }
    this->info.entity_type = type;
    this->x_position = x;
    this->y_position = y;
    this->info.curr_lifepoints = this->info.max_lifepoints;

    this->info.vao = generateVertices(static_cast<float>(this->x_position),
                                 static_cast<float>(this->y_position),
                                 static_cast<float>(this->width),
                                 static_cast<float>(this->height), *texture);
}