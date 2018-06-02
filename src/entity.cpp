//
// Created by jorda on 5/30/2018.
//

#include "helper.hpp"

using namespace resources;

void Entity::offsetEntity(int xoffset, int yoffset) {
    xposition -= xoffset;
    yposition -= yoffset;
    vertices[0].position = Vector2f(xposition, yposition);
    vertices[1].position = Vector2f(xposition, yposition + ysize);
    vertices[2].position = Vector2f(xposition + xsize, yposition + ysize);
    vertices[3].position = Vector2f(xposition + xsize, yposition);
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(vertices, states);
}

/** NOTE - xposition and yposition are in units of tiles */
Resource::Resource(int xposition, int yposition, int type) {
    Texture * texture;
    switch(type) {
        case Resource::RESOURCE_FOOD:
            texture = textures[resource::FOOD_TEXTURE];
            xsize = 2;
            ysize = 2;
            has_ground_collision = false;
            break;
        case Resource::RESOURCE_GOLD:
            texture = textures[resource::GOLD_TEXTURE];
            xsize = 3;
            ysize = 1;
            has_ground_collision = false;
            break;
        case Resource::RESOURCE_WOOD:
            texture = textures[resource::TREE_TEXTURE];
            xsize = 1;
            ysize = 1;
            has_ground_collision = true;
            break;
        case Resource::RESOURCE_METAL:
            texture = textures[resource::METAL_TEXTURE];
            xsize = 2;
            ysize = 2;
            has_ground_collision = true;
            break;
        case Resource::RESOURCE_CRYSTAL:
            texture = textures[resource::CRYSTAL_TEXTURE];
            xsize = 1;
            ysize = 3;
            has_ground_collision = true;
            break;
        case Resource::RESOURCE_OIL:
            texture = textures[resource::OIL_TEXTURE];
            xsize = 1;
            ysize = 1;
            has_ground_collision = false;
            break;
        default:
            texture = textures[resource::OIL_TEXTURE];
            break;
    }
    this->type = type;
    this->xposition = xposition * Tile::TILE_SIZE;
    this->yposition = yposition * Tile::TILE_SIZE;
    xsize *= Tile::TILE_SIZE;
    ysize *= Tile::TILE_SIZE;
    vertices = generateVertices(this->xposition, this->yposition, xsize, ysize, *texture);
}

/** NOTE - xposition and yposition are in units of pixels */
Unit::Unit(int xposition, int yposition, int type) {
    Texture * texture;
    switch(type) {
        case Unit::UNIT_BUILDER:
            texture = textures[unit::PEASANT_TEXTURE];
            xsize = 16;
            ysize = 32;
            max_lifepoints = INT32_MAX;
            break;
        default:
            texture = textures[unit::PEASANT_TEXTURE];
            break;
    }
    this->type = type;
    this->xposition = xposition;
    this->yposition = yposition;
    curr_lifepoints = max_lifepoints;
    vertices = generateVertices(this->xposition, this->yposition, xsize, ysize, *texture);
}
