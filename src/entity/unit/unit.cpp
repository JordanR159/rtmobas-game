//
// Created by Killian Le Clainche on 6/2/2018.
//

#include "helper.hpp"

/** NOTE - xposition and yposition are in units of pixels */
Unit::Unit(float x, float y, int type) {
    switch(type) {
        case Unit::UNIT_BUILDER:
            this->info.texture = resources::textures[resources::unit::PEASANT_TEXTURE];
            this->width = 8;
            this->height = 32;
            this->speed = 1.5f;
            this->info.max_lifepoints = INT32_MAX;
            break;
        default:
            this->info.texture = resources::textures[resources::unit::PEASANT_TEXTURE];
            break;
    }
    this->info.entity_type = type;
    this->info.curr_lifepoints = this->info.max_lifepoints;

    this->info.vao = generateVertices(x, y, this->width, this->height, *this->info.texture);

    sf::Vector2f pivot(x + this->width/2, y + this->height/2);
    sf::Vector2f * points = rotateRectangle(pivot, &this->info.vao, M_PI_4);
    this->x_position = points[0].x;
    this->y_position = points[0].y;
    this->info.vao[0].position = points[0];
    this->info.vao[1].position = points[1];
    this->info.vao[2].position= points[2];
    this->info.vao[3].position = points[3];

    this->moving = false;
    this->destination_point = sf::VertexArray(sf::Points, 1);
    this->destination_point[0].position = sf::Vector2f(this->x_position, this->y_position);
    this->destination_point[0].color = sf::Color::Cyan;

    rpfree(points);
}