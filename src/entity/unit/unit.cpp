//
// Created by Killian Le Clainche on 6/2/2018.
//

#include "helper.hpp"

/** NOTE - xposition and yposition are in units of pixels */
Unit::Unit(double x, double y, int type) {
    Texture * texture;
    switch(type) {
        case Unit::UNIT_BUILDER:
            texture = textures[unit::PEASANT_TEXTURE];
            this->width = 16;
            this->height = 32;
            max_lifepoints = INT32_MAX;
            break;
        default:
            texture = textures[unit::PEASANT_TEXTURE];
            break;
    }
    this->entity_type = type;
    this->x_position = x;
    this->y_position = y;
    this->curr_lifepoints = max_lifepoints;

    this->vao = generateVertices(static_cast<float>(this->x_position),
                                 static_cast<float>(this->y_position),
                                 static_cast<float>(this->width),
                                 static_cast<float>(this->height), *texture);
}