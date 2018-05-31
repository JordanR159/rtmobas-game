//
// Created by jorda on 5/29/2018.
//

#include "helper.hpp"

using namespace std;

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
        case Types::WATER:
            texture.loadFromFile("../resources/textures/water.png");
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
    this->type = type;
    this->xposition = xposition;
    this->yposition = yposition;
    vertices = generateVertices(this->xposition, this->yposition, TILE_SIZE, TILE_SIZE, texture);
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

World::World(int xtiles, int ytiles) {
    this->xtiles = xtiles;
    this->ytiles = ytiles;
    tiles_size = xtiles * ytiles;
    tiles = new Tile[tiles_size];
    for(int i = 0; i < tiles_size; i++) {
        tiles[i] = Tile((i % xtiles) * Tile::TILE_SIZE, (i / xtiles) * Tile::TILE_SIZE, Tile::Types::PLAINS);
    }
    tiles_modified = true;
    xoffset = 0;
    yoffset = 0;
}

World::World(char *map_path, char *spawn_path) {
    int *tile_info = readBMP(map_path);
    this->xtiles = tile_info[0];
    this->ytiles = tile_info[1];
    tiles_size = xtiles * ytiles;
    tiles = new Tile[tiles_size];
    for(int i = 0; i < tiles_size; i++) {
        tiles[i] = Tile((i % xtiles) * Tile::TILE_SIZE, (i / xtiles) * Tile::TILE_SIZE, tile_info[i + 2]);
    }
    spawnEntities(spawn_path);
    tiles_modified = true;
    xoffset = 0;
    yoffset = 0;
    free(map_path);
    free(spawn_path);
}

void World::spawnEntities(char *spawn_path) {
    FILE *spawn_file = fopen(spawn_path, "rb");
    char spawn_info[100];
    while(fgets(spawn_info, 100, spawn_file) != nullptr) {
        char *data = strtok(spawn_info, ",");
        int subtype = atoi(data);
        int type = subtype/100;
        data = strtok(NULL, ",");
        int xposition = atoi(data);
        data = strtok(NULL, ",");
        int yposition = atoi(data);
        switch(type){
            case Entity::Types::PROD:
            case Entity::Types::RSCH:
            case Entity::Types::COLL:
                structures.push_front(Structure(xposition, yposition, subtype));
                break;
            case Entity::Types::RSRC:
                resources.push_front(Resource(xposition, yposition, subtype));
                break;
            case Entity::Types::UNIT:
                units.push_front(Unit(xposition, yposition, subtype));
                break;
            default:
                break;
        }
    }
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
    for(Resource r : resources) {
        if(isOnScreen(r, startx, starty, endx, endy)) {
            r.offsetEntity(xoffset, yoffset);
            target.draw(r);
            r.offsetEntity(-1 * xoffset, -1 * yoffset);
            printf("resource detected\n");
        }
    }
    for(Structure s : structures) {
        if(isOnScreen(s, startx, starty, endx, endy)) {
            s.offsetEntity(xoffset, yoffset);
            target.draw(s);
            s.offsetEntity(-1 * xoffset, -1 * yoffset);
            printf("structure detected\n");
        }
    }
    for(Unit u : units) {
        if(isOnScreen(u, startx, starty, endx, endy)) {
            u.offsetEntity(xoffset, yoffset);
            target.draw(u);
            u.offsetEntity(-1 * xoffset, -1 * yoffset);
            printf("unit detected\n");
        }
    }
}