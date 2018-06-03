//
// Created by Killian Le Clainche on 6/1/2018.
//

#include "helper.hpp"
#include <random>

using namespace std;
using namespace resources;

Tile::Tile(int x, int y, int type) {
    this->tile_type = type;

    switch (type) {
        case TERRAIN_PLAINS_COLOR:
            this->tile_type = TERRAIN_PLAINS;
            break;
        case TERRAIN_DESERT_COLOR:
            this->tile_type = TERRAIN_DESERT;
            break;
        case TERRAIN_MOUNTAINS_COLOR:
            this->tile_type = TERRAIN_MOUNTAINS;
            break;
        /* case WATER_COLOR:
            this->tile_type = WATER;
            break; */
        default:
            this->tile_type = TERRAIN_WATER;
            break;
    }

    this->x_coord = x;
    this->y_coord = y;

    this->structure = nullptr;
    this->resource = nullptr;

    this->create_vao();
}

void Tile::create_vao() {
    Texture * texture = textures[terrain::TERRAIN_TEXTURES];

    void * mem = rpmalloc(sizeof(VertexArray));
    this->vao = *(new (mem) VertexArray(Quads, 4));

    int x_position = this->x_coord * TILE_SIZE;
    int y_position = this->y_coord * TILE_SIZE;

    (this->vao)[0].position = Vector2f(x_position, y_position);
    this->vao[1].position = Vector2f(x_position, y_position + TILE_SIZE);
    this->vao[2].position = Vector2f(x_position + TILE_SIZE, y_position + TILE_SIZE);
    this->vao[3].position = Vector2f(x_position + TILE_SIZE, y_position);

    int random = rand() % (4);

    int x_tex1 = texture->getSize().x / NUMBER_OF_TERRAIN_VARIATIONS;
    int x_tex2 = x_tex1 * (random + 1);
    x_tex1 = x_tex2 - x_tex1;

    int y_tex1 = texture->getSize().y / NUMBER_OF_TERRAIN_TYPES;
    int y_tex2 = y_tex1 * (this->tile_type + 1);
    y_tex1 = y_tex2 - y_tex1;

    this->vao[0].texCoords = Vector2f(x_tex1, y_tex1);
    this->vao[1].texCoords = Vector2f(x_tex1, y_tex2);
    this->vao[2].texCoords = Vector2f(x_tex2, y_tex2);
    this->vao[3].texCoords = Vector2f(x_tex2, y_tex1);
}

void Tile::draw(RenderTarget &target, RenderStates states) const {
    target.draw(this->vao, states);
}