//
// Created by jorda on 5/29/2018.
//

#include "helper.hpp"

using namespace std;

Tile::Tile(int xposition, int yposition, int type) {
    this->tile_type = type;
    Texture *texture;
    switch (type) {
        case PLAINS:
            texture = resources::textures[resources::PLAINS_TEXTURE];
            is_passable = true;
            movement_multiplier = 1.0;
            damage_factor = 0;
            break;
        case DESERT:
            texture = resources::textures[resources::DESERT_TEXTURE];
            is_passable = true;
            movement_multiplier = 0.5;
            damage_factor = 10;
            break;
        case MOUNTAINS:
            texture = resources::textures[resources::MOUNTAINS_TEXTURE];
            is_passable = false;
            movement_multiplier = 1.0;
            damage_factor = 0;
            break;
        case WATER:
            texture = resources::textures[resources::WATER_TEXTURE];
            is_passable = false;
            movement_multiplier = 1.0;
            damage_factor = 0;
            break;
        default:
            texture = resources::textures[resources::WATER_TEXTURE];
            is_passable = true;
            movement_multiplier = 1.0;
            damage_factor = INT32_MAX;
            break;
    }
    this->xposition = xposition;
    this->yposition = yposition;
    vertices = generateVertices(this->xposition, this->yposition, TILE_SIZE, TILE_SIZE, *texture);
}

void Tile::draw(RenderTarget &target, RenderStates states) const {
    target.draw(vertices, states);
}

World::World(char *map_path, char *spawn_path) {
    resources::load(resources::PLAINS_TEXTURE);
    resources::load(resources::DESERT_TEXTURE);
    resources::load(resources::MOUNTAINS_TEXTURE);
    resources::load(resources::WATER_TEXTURE);

    int *tile_info = readBMP(map_path);

    this->world_width_tiles = tile_info[0];
    this->world_height_tiles = tile_info[1];
    this->world_height = this->world_height_tiles * Tile::TILE_SIZE;
    this->world_width = this->world_width_tiles * Tile::TILE_SIZE;

    this->tiles_size = this->world_width_tiles * this->world_height_tiles;
    this->tiles = new Tile[tiles_size];

    for(int i = 0; i < tiles_size; i++) {
        this->tiles[i] = Tile((i % this->world_width_tiles) * Tile::TILE_SIZE, (i / this->world_height_tiles) * Tile::TILE_SIZE, tile_info[i + 2]);
    }

    spawnEntities(spawn_path);
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
        int alt_xposition;
        int alt_yposition;
        switch(type){
            case Entity::PRODUCER:
            case Entity::RESEARCHER:
            case Entity::COLLECTOR:
                structures.emplace_back(Structure(xposition, yposition, subtype));
                alt_xposition = this->world_width_tiles - xposition - (structures.back().xsize / Tile::TILE_SIZE);
                alt_yposition = this->world_height_tiles - yposition - (structures.back().ysize / Tile::TILE_SIZE);
                structures.emplace_back(Structure(alt_xposition, alt_yposition, subtype));
                break;
            case Entity::RESOURCE:
                resources.emplace_back(Resource(xposition, yposition, subtype));
                alt_xposition = this->world_width_tiles - xposition - (resources.back().xsize / Tile::TILE_SIZE);
                alt_yposition = this->world_height_tiles - yposition - (resources.back().ysize / Tile::TILE_SIZE);
                resources.emplace_back(Resource(alt_xposition, alt_yposition, subtype));
                break;
            case Entity::UNIT:
                xposition *= Tile::TILE_SIZE;
                yposition *= Tile::TILE_SIZE;
                units.emplace_back(Unit(xposition, yposition, subtype));
                alt_xposition = (this->world_width_tiles * Tile::TILE_SIZE) - xposition - units.back().xsize;
                alt_yposition = (this->world_height_tiles * Tile::TILE_SIZE) - yposition - units.back().ysize;
                units.emplace_back(Unit(alt_xposition, alt_yposition, subtype));
                break;
            default:
                break;
        }
    }
}
/*
void World::draw(RenderTarget &target, RenderStates states) const {
    int startx = max((xoffset / Tile::TILE_SIZE) - 1, 0);
    int starty = max((yoffset / Tile::TILE_SIZE) - 1, 0);
    int tempx = xoffset + target.getSize().x;
    int tempy = yoffset + target.getSize().y;
    int endx = min((tempx / Tile::TILE_SIZE) + 1, xtiles);
    int endy = min((tempy / Tile::TILE_SIZE) + 1, ytiles);
    for (int x = startx; x < endx; x++) {
        for (int y = starty; y < endy; y++) {
            Tile selected = tiles[x + y * xtiles];
            selected.offsetTile(xoffset, yoffset);
            target.draw(selected);
            selected.offsetTile(-1 * xoffset, -1 * yoffset);
        }
    }
    for (Resource r : resources) {
        if (isOnScreen(r, startx, starty, endx, endy)) {
            r.offsetEntity(xoffset, yoffset);
            target.draw(r);
            r.offsetEntity(-1 * xoffset, -1 * yoffset);
        }
    }
    for (Structure s : structures) {
        if (isOnScreen(s, startx, starty, endx, endy)) {
            s.offsetEntity(xoffset, yoffset);
            target.draw(s);
            s.offsetEntity(-1 * xoffset, -1 * yoffset);
        }
    }
    for (Unit u : units) {
        if (isOnScreen(u, startx, starty, endx, endy)) {
            u.offsetEntity(xoffset, yoffset);
            target.draw(u);
            u.offsetEntity(-1 * xoffset, -1 * yoffset);
        }
    }
}*/
void World::draw(RenderTarget &target, RenderStates states) const {
    states.texture = resources::textures[resources::PLAINS_TEXTURE];

    for (int i = 0; i < tiles_size; i++) {
        if(this->tiles[i].tile_type == Tile::PLAINS)
            target.draw(tiles[i], states);
    }

    states.texture = resources::textures[resources::DESERT_TEXTURE];

    for (int i = 0; i < tiles_size; i++) {
        if(this->tiles[i].tile_type == Tile::DESERT)
            target.draw(tiles[i], states);
    }

    states.texture = resources::textures[resources::MOUNTAINS_TEXTURE];

    for (int i = 0; i < tiles_size; i++) {
        if(this->tiles[i].tile_type == Tile::MOUNTAINS)
            target.draw(tiles[i], states);
    }

    states.texture = resources::textures[resources::WATER_TEXTURE];

    for (int i = 0; i < tiles_size; i++) {
        if(this->tiles[i].tile_type == Tile::WATER)
            target.draw(tiles[i], states);
    }

    for (Resource r : resources) {
        target.draw(r);
    }
    for (Structure s : structures) {
        target.draw(s);
    }
    for (Unit u : units) {
        target.draw(u);
    }
}