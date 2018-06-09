//
// Created by jorda on 5/29/2018.
//

#include "helper.hpp"

using namespace std;

World::World(char *map_path, char *spawn_path) {
    // TODO better loading so as not required to pre-load each individual.
    resources::load(resources::terrain::TERRAIN_TEXTURES);

    resources::load(resources::structure::CASTLE_TEXTURE);
    resources::load(resources::structure::FARM_TEXTURE);

    resources::load(resources::resource::GOLD_TEXTURE);
    resources::load(resources::resource::TREE_TEXTURE);
    resources::load(resources::resource::METAL_TEXTURE);
    resources::load(resources::resource::CRYSTAL_TEXTURE);
    resources::load(resources::resource::OIL_TEXTURE);

    resources::load(resources::unit::PEASANT_TEXTURE);

    resources::load(resources::pblock::pblocktexture);

    this->map_layout_path = map_path;
    int *tile_info = readBMP(map_path);

    this->world_width_tiles = tile_info[0];
    this->world_height_tiles = tile_info[1];

    this->tiles = (Tile ***) rpmalloc(this->world_width_tiles * sizeof(Tile **));

    Tile ** tile_column;
    void * mem;

    for(int i = 0; i < this->world_width_tiles; i++) {
        tile_column = (Tile **) rpmalloc(this->world_height_tiles * sizeof(Tile *));

        for(int j = 0; j < this->world_height_tiles; j++) {
            mem = rpmalloc(sizeof(Tile));

            // Image reads from top left to top right, then down a row.

            tile_column[j] = new(mem) Tile(i, j, tile_info[2 + i + j * this->world_width_tiles]);
        }

        this->tiles[i] = tile_column;
    }

    /* this->tiles = new Tile[tiles_size];

    for(int i = 0; i < tiles_size; i++) {
        this->tiles[i] = Tile((i % this->world_width_tiles) * Tile::TILE_SIZE, (i / this->world_height_tiles) * Tile::TILE_SIZE, tile_info[i + 2]);
    } */

    tile_entity::init();

    spawnEntities(spawn_path);
}

World::~World() {

    // This section is optimized, though there are small tricks to do inconsequential
    // speed-ups.
    Tile ** current_tile_column;
    Tile * current_tile;

    for(int i = 0; i < this->world_width_tiles; i++) {
        current_tile_column = this->tiles[i];

        for(int j = 0; j < this->world_height_tiles; j++) {
            current_tile = current_tile_column[j];

            // Free all the tiles
            current_tile->~Tile();
            rpfree(current_tile);
        }
    }

    for(auto resource : this->resources) {
        resource->~Resource();
        rpfree(resource);
    }

    for(auto structure : this->structures) {
        structure->~Structure();
        rpfree(structure);
    }

    for(auto unit : this->units) {
        unit->~Unit();
        rpfree(unit);
    }

    this->resources.clear();
    this->structures.clear();
    this->units.clear();

    resources::flush();
}

void World::selectEntity(sf::Vector2f point) {
    for(auto &entity : selector->selected_tile_entities) {
        entity->selected = false;
    }
    selector->selected_tile_entities.clear();
    for(auto &structure : structures) {
        if (intersectPointRect(point, &structure->vao)) {
            selector->selected_tile_entities.emplace_back(structure);
            structure->info.selected = true;
            return;
        }
    }
    for(auto &resource : resources) {
        if (intersectPointRect(point, &resource->vao)) {
            selector->selected_tile_entities.emplace_back(resource);
            resource->info.selected = true;
            return;
        }
    }
}

void World::selectEntities(sf::VertexArray points) {
    for (auto &entity : selector->selected_tile_entities) {
        entity->selected = false;
    }
    selector->selected_tile_entities.clear();
    for (auto &structure : structures) {
        if (intersectRectRect(&points, &structure->vao)) {
            selector->selected_tile_entities.emplace_back(structure);
            structure->info.selected = true;
        }
    }
    for (auto &resource : resources) {
        if (intersectRectRect(&points, &resource->vao)) {
            selector->selected_tile_entities.emplace_back(resource);
            resource->info.selected = true;
        }
    }
}

void World::spawnEntities(char *spawn_path) {
    // TODO simplify

    std::string line;
    std::ifstream spawn_file(spawn_path);

    std::string token;
    unsigned long long int delimiter_index;
    int type;
    int team1_x;
    int team1_y;
    int team2_x;
    int team2_y;

    void * mem;

    if(spawn_file.is_open()) {
        while(getline(spawn_file, line)) {

            TOKENIZE(line, token, ',', delimiter_index)

            type = stoi(token);

            TOKENIZE(line, token, ',', delimiter_index)

            team1_x = stoi(token);

            TOKENIZE(line, token, ',', delimiter_index)

            team1_y = stoi(token);

            switch(type / TILE_ENTITY_START_VALUE) {
                case TILE_ENTITY:
                    switch((type - TILE_ENTITY_START_VALUE) / TILE_ENTITY_TYPE_DIFF) {
                        case RESOURCE:
                            mem = rpmalloc(sizeof(Resource));

                            this->resources.emplace_back(new(mem) Resource(this, type, team1_x, team1_y));

                            team2_x = this->world_width_tiles - team1_x - this->resources.back()->width;
                            team2_y = this->world_height_tiles - team1_y - this->resources.back()->height;

                            mem = rpmalloc(sizeof(Resource));

                            this->resources.emplace_back(new(mem) Resource(this, type, team2_x, team2_y));
                            break;
                        default:
                            this->structures.emplace_back(tile_entity::structures[type](this, type, team1_x, team1_y));

                            team2_x = this->world_width_tiles - team1_x - this->structures.back()->width;
                            team2_y = this->world_height_tiles - team1_y - this->structures.back()->height;

                            this->structures.emplace_back(tile_entity::structures[type](this, type, team2_x, team2_y));
                            break;
                    }
                    break;
                default:
                    break;
            }

        }
        spawn_file.close();
    }

    /*FILE *spawn_file = fopen(spawn_path, "rb");
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
    }*/
}

void World::update() {

}

void World::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.texture = resources::textures[resources::terrain::TERRAIN_TEXTURES];

    Tile ** tile_column;

    for (int i = 0; i < this->world_width_tiles; i++) {
        tile_column = this->tiles[i];

        for(int j = 0; j < this->world_height_tiles; j++) {
            target.draw(*(tile_column[j]), states);
        }
    }

    for (auto &r : resources) {
        target.draw(*r);
    }
    for (auto &s : structures) {
        target.draw(*s);
    }
    for (auto &u : units) {
        target.draw(*u);
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
}*/