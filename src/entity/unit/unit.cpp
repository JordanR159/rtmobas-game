//
// Created by Killian Le Clainche on 6/2/2018.
//

#include "helper.hpp"

/** NOTE - xposition and yposition are in units of pixels */
Unit::Unit(float x, float y, int type) {
    sf::Texture * texture;
    switch(type) {
        case Unit::UNIT_BUILDER:
            texture = resources::textures[resources::unit::PEASANT_TEXTURE];
            this->width = 8;
            this->height = 32;
            this->speed = 0.75f;
            this->info.max_lifepoints = INT32_MAX;
            break;
        default:
            texture = resources::textures[resources::unit::PEASANT_TEXTURE];
            break;
    }
    this->info.entity_type = type;
    this->x_position = x;
    this->y_position = y;
    this->info.curr_lifepoints = this->info.max_lifepoints;

    this->info.vao = generateVertices(this->x_position, this->y_position, this->width, this->height, *texture);

    sf::Vector2f pivot(this->x_position + this->width/2, this->y_position + this->height/2);
    sf::Vector2f * points = rotateRectangle(pivot, &this->info.vao, M_PI_4);
    this->info.vao[0].position = points[0];
    this->info.vao[1].position = points[1];
    this->info.vao[2].position= points[2];
    this->info.vao[3].position = points[3];

    rpfree(points);
}