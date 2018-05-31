//
// Created by jorda on 5/30/2018.
//

#include "helper.hpp"

void Entity::offsetEntity(int xoffset, int yoffset) {
    xposition -= xoffset;
    yposition -= yoffset;
    vertices[0].position = Vector2f(xposition, yposition);
    vertices[1].position = Vector2f(xposition, yposition + ysize);
    vertices[2].position = Vector2f(xposition + xsize, yposition + ysize);
    vertices[3].position = Vector2f(xposition + xsize, yposition);
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.texture = &texture;
    target.draw(vertices, states);
}

/** NOTE - xposition and yposition are in units of tiles */
Resource::Resource(int xposition, int yposition, int type) {
    switch(type) {
        case Resource::RSRC_FOOD:
            texture.loadFromFile("../resources/sprites/food_resource.png");
            xsize = 2;
            ysize = 2;
            has_ground_collision = false;
            break;
        case Resource::RSRC_GOLD:
            texture.loadFromFile("../resources/sprites/gold_resource.png");
            xsize = 3;
            ysize = 1;
            has_ground_collision = false;
            break;
        case Resource::RSRC_WOOD:
            texture.loadFromFile("../resources/sprites/wood_resource.png");
            xsize = 1;
            ysize = 1;
            has_ground_collision = true;
            break;
        case Resource::RSRC_METAL:
            texture.loadFromFile("../resources/sprites/metal_resource.png");
            xsize = 2;
            ysize = 2;
            has_ground_collision = true;
            break;
        case Resource::RSRC_CRYSTAL:
            texture.loadFromFile("../resources/sprites/crystal_resource.png");
            xsize = 1;
            ysize = 3;
            has_ground_collision = true;
            break;
        case Resource::RSRC_OIL:
            texture.loadFromFile("../resources/sprites/oil_resource.png");
            xsize = 1;
            ysize = 1;
            has_ground_collision = false;
            break;
        default:
            texture.loadFromFile("../resources/sprites/pblock.png");
            break;
    }
    this->type = type;
    this->xposition = xposition * Tile::TILE_SIZE;
    this->yposition = yposition * Tile::TILE_SIZE;
    xsize *= Tile::TILE_SIZE;
    ysize *= Tile::TILE_SIZE;
    vertices = generateVertices(this->xposition, this->yposition, xsize, ysize, texture);
}

/** NOTE - xposition and yposition are in units of tiles */
Structure::Structure(int xposition, int yposition, int type, Resource *resource) {
    switch(type) {
        case Structure::PROD_CASTLE:
            texture.loadFromFile("../resources/sprites/castle.png");
            xsize = 3;
            ysize = 3;
            has_ground_collision = true;
            max_lifepoints = 1000;
            break;
        case Structure::COLL_FOOD:
            texture.loadFromFile("../resources/sprites/food_collector.png");
            xsize = 2;
            ysize = 2;
            has_ground_collision = true;
            max_lifepoints = 200;
            break;
        default:
            texture.loadFromFile("../resources/sprites/pblock.png");
            xsize = 1;
            ysize = 1;
            has_ground_collision = false;
            max_lifepoints = INT32_MAX;
            break;
    }
    this->type = type;
    this->xposition = xposition * Tile::TILE_SIZE;
    this->yposition = yposition * Tile::TILE_SIZE;
    xsize *= Tile::TILE_SIZE;
    ysize *= Tile::TILE_SIZE;
    xrally = xposition;
    yrally = yposition;
    curr_lifepoints = max_lifepoints;
    vertices = generateVertices(this->xposition, this->yposition, xsize, ysize, texture);
}

/** NOTE - xposition and yposition are in units of pixels */
Unit::Unit(int xposition, int yposition, int type) {
    switch(type) {
        case Unit::UNIT_BUILDER:
            texture.loadFromFile("../resources/sprites/peasant.png");
            xsize = 16;
            ysize = 32;
            max_lifepoints = INT32_MAX;
            break;
        default:
            texture.loadFromFile("../resources/sprites/pblock.png");
            break;
    }
    this->type = type;
    this->xposition = xposition;
    this->yposition = yposition;
    curr_lifepoints = max_lifepoints;
    vertices = generateVertices(this->xposition, this->yposition, xsize, ysize, texture);
}
