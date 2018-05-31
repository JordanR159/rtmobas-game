//
// Created by jorda on 5/29/2018.
//

#include <world.hpp>

using namespace std;

Tile::Tile() {
    Tile(0, 0, Types::PLAINS);
}

Tile::Tile(int xposition, int yposition, int type) {
    switch (type) {
        case Types::PLAINS:
            texture.loadFromFile("../resources/textures/plains.png");
            is_passable = true;
            movement_multiplier = 1.0;
            damage_factor = 0;
            break;
        case Types::DESERT:
            texture.loadFromFile("../resources/textures/desert.png");
            is_passable = true;
            movement_multiplier = 0.5;
            damage_factor = 10;
            break;
        case Types::MOUNTAINS:
            texture.loadFromFile("../resources/textures/mountains.png");
            is_passable = false;
            movement_multiplier = 1.0;
            damage_factor = 0;
            break;
        default:
            texture.loadFromFile("../resources/textures/pblock.png");
            is_passable = true;
            movement_multiplier = 1.0;
            damage_factor = INT32_MAX;
            break;
    }
    this->xposition = xposition;
    this->yposition = yposition;
    vertices = VertexArray(Quads, 4);

    /** Corner positions for the rendering box */
    vertices[0].position = Vector2f(xposition, yposition);
    vertices[1].position = Vector2f(xposition, yposition + TILE_SIZE);
    vertices[2].position = Vector2f(xposition + TILE_SIZE, yposition + TILE_SIZE);
    vertices[3].position = Vector2f(xposition + TILE_SIZE, yposition);

    /** Designates area of the texture that is used */
    vertices[0].texCoords = Vector2f(0, 0);
    vertices[1].texCoords = Vector2f(0, texture.getSize().y);
    vertices[2].texCoords = Vector2f(texture.getSize().x, texture.getSize().y);
    vertices[3].texCoords = Vector2f(texture.getSize().x, 0);
}

void Tile::offsetTile(int xoffset, int yoffset) {
    xposition -= xoffset;
    yposition -= yoffset;
    vertices[0].position = Vector2f(xposition, yposition);
    vertices[1].position = Vector2f(xposition, yposition + TILE_SIZE);
    vertices[2].position = Vector2f(xposition + TILE_SIZE, yposition + TILE_SIZE);
    vertices[3].position = Vector2f(xposition + TILE_SIZE, yposition);
}

void Tile::draw(RenderTarget &target, RenderStates states) const {
    states.texture = &texture;
    target.draw(vertices, states);
}

World::World(int *tile_info) {
    this->xtiles = tile_info[0];
    this->ytiles = tile_info[1];
    tiles_size = xtiles * ytiles;
    tiles = new Tile[tiles_size];
    for(int i = 0; i < tiles_size; i++) {
        tiles[i] = Tile((i % xtiles) * Tile::TILE_SIZE, (i / xtiles) * Tile::TILE_SIZE, tile_info[i + 2]);
    }
    tiles_modified = true;
    xoffset = 0;
    yoffset = 0;
}

void World::draw(RenderTarget &target, RenderStates states) const {
    int startx = max((xoffset / Tile::TILE_SIZE) - 1, 0);
    int starty = max((yoffset / Tile::TILE_SIZE) - 1, 0);
    int tempx = xoffset + target.getSize().x;
    int tempy = yoffset + target.getSize().y;
    int endx = min((tempx / Tile::TILE_SIZE) + 1, xtiles);
    int endy = min((tempy / Tile::TILE_SIZE) + 1, ytiles);
    for(int x = startx; x < endx; x++) {
        for(int y = starty; y < endy; y++) {
            Tile selected = tiles[x + y * xtiles];
            selected.offsetTile(xoffset, yoffset);
            target.draw(selected);
            selected.offsetTile(-1 * xoffset, -1 * yoffset);
        }
    }
}