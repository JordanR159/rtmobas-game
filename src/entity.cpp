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

Resource::Resource(int xposition, int yposition, int type) {
    switch(type) {
        case Entity::Types::RSRC_FOOD:
            texture.loadFromFile("../resources/sprites/food_resource.png");
            xsize = 2;
            ysize = 2;
            break;
        case Entity::Types::RSRC_GOLD:
            texture.loadFromFile("../resources/sprites/gold_resource.png");
            xsize = 2;
            ysize = 1;
            break;
        case Entity::Types::RSRC_WOOD:
            texture.loadFromFile("../resources/sprites/wood_resource.png");
            xsize = 1;
            ysize = 2;
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

Structure::Structure(int xposition, int yposition, int type) {
    switch(type) {
        case Entity::Types::PROD_CASTLE:
            texture.loadFromFile("../resources/sprites/castle.png");
            xsize = 3;
            ysize = 3;
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

Unit::Unit(int xposition, int yposition, int type) {
    switch(type) {
        default:
            texture.loadFromFile("../resources/sprites/pblock.png");
            break;
    }
    this->type = type;
    this->xposition = xposition;
    this->yposition = yposition;
    vertices = generateVertices(this->xposition, this->yposition, xsize, ysize, texture);
}
