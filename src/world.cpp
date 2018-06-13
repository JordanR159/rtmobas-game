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

    this->held_entity = nullptr;

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
    for(auto &entity : selector->selected_entities) {
        entity->info.selected = false;
    }
    selector->selected_entities.clear();
    for(auto &entity : selector->selected_tile_entities) {
        entity->info.selected = false;
    }
    selector->selected_tile_entities.clear();

    for(auto &unit : units) {
        if (intersectPointRect(point, &unit->info.vao)) {
            selector->selected_entities.emplace_back(unit);
            unit->info.selected = true;
            return;
        }
    }
    for(auto &structure : structures) {
        if (intersectPointRect(point, &structure->info.vao)) {
            selector->selected_tile_entities.emplace_back(structure);
            structure->info.selected = true;
            return;
        }
    }
    for(auto &resource : resources) {
        if (intersectPointRect(point, &resource->info.vao)) {
            selector->selected_tile_entities.emplace_back(resource);
            resource->info.selected = true;
            return;
        }
    }
}

void World::selectEntities(sf::VertexArray points) {
    for(auto &entity : selector->selected_entities) {
        entity->info.selected = false;
    }
    selector->selected_entities.clear();
    for (auto &entity : selector->selected_tile_entities) {
        entity->info.selected = false;
    }
    selector->selected_tile_entities.clear();
    bool selection_made = false;

    for (auto &unit : units) {
        if (intersectRectRect(&points, &unit->info.vao)) {
            selector->selected_entities.emplace_back(unit);
            unit->info.selected = true;
            selection_made = true;
        }
    }
    if(selection_made) return;

    for (auto &structure : structures) {
        if (intersectRectRect(&points, &structure->info.vao)) {
            selector->selected_tile_entities.emplace_back(structure);
            structure->info.selected = true;
            selection_made = true;
        }
    }
    if(selection_made) return;

    for (auto &resource : resources) {
        if (intersectRectRect(&points, &resource->info.vao)) {
            selector->selected_tile_entities.emplace_back(resource);
            resource->info.selected = true;
            selection_made = true;
        }
    }
    if(selection_made) return;
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
                    mem = rpmalloc(sizeof(Unit));

                    this->units.emplace_back(new(mem) Unit(team1_x * TILE_SIZE, team1_y * TILE_SIZE, type));

                    team2_x = static_cast<int>(this->world_width_tiles * TILE_SIZE - team1_x * TILE_SIZE - this->units.back()->width);
                    team2_y = static_cast<int>(this->world_height_tiles * TILE_SIZE - team1_y * TILE_SIZE - this->units.back()->height);

                    mem = rpmalloc(sizeof(Unit));

                    this->units.emplace_back(new(mem) Unit(team2_x, team2_y, type));
                    break;
            }

        }
        spawn_file.close();
    }
}

void World::update() {
    if(this->held_entity != nullptr) {
        sf::Vector2i mouse = sf::Mouse::getPosition(settings::window);

        sf::Vector2f float_point = alignMouseCursor(mouse.x, mouse.y);

        clamp_vec(float_point, 0, 0, (this->world_width_tiles - this->held_entity->width) * TILE_SIZE, (this->world_height_tiles - this->held_entity->height) * TILE_SIZE);

        sf::Vector2i point(static_cast<int>(float_point.x / TILE_SIZE) * TILE_SIZE, static_cast<int>(float_point.y / TILE_SIZE) * TILE_SIZE);

        sf::VertexArray * vao = &this->held_entity->info.vao;

        auto width = this->held_entity->width * TILE_SIZE;
        auto height = this->held_entity->height * TILE_SIZE;

        (*vao)[0].position = sf::Vector2f(point.x, point.y);
        (*vao)[1].position = sf::Vector2f(point.x, point.y + height);
        (*vao)[2].position = sf::Vector2f(point.x + width, point.y + height);
        (*vao)[3].position = sf::Vector2f(point.x + width, point.y);

        this->held_entity->x_coord = point.x / TILE_SIZE;
        this->held_entity->y_coord = point.y / TILE_SIZE;

        bool overlaps_tile_entity = false;

        for (auto &structure : structures) {
            if (intersectRectRect(vao, &structure->info.vao)) {
                overlaps_tile_entity = true;
                break;
            }
        }
        if(!overlaps_tile_entity) {
            for (auto &resource : resources) {
                if (intersectRectRect(vao, &resource->info.vao)) {
                    overlaps_tile_entity = true;
                    break;
                }
            }
        }

        this->held_entity->info.selected = overlaps_tile_entity || !this->held_entity->can_place();

        if(settings::input_mapping[MOUSE_SELECT_CLICK]->clicked && !this->held_entity->info.selected) {

            this->held_entity->claim_tiles();

            sf::Color color(255, 255, 255, 255);

            (*vao)[0].color = color;
            (*vao)[1].color = color;
            (*vao)[2].color = color;
            (*vao)[3].color = color;

            this->structures.emplace_back(this->held_entity);
            this->held_entity = nullptr;
        }

        //if(settings::input_mapping[])

        //std::cout << point.x << " " << point.y << " " << point.x / TILE_SIZE << " " << point.y / TILE_SIZE << std::endl;
    }

    for(auto &unit : units)
        unit->update(this);
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

    for (auto &r : this->resources) {
        target.draw(*r);
    }
    for (auto &s : this->structures) {
        target.draw(*s);
    }
    for (auto &u : this->units) {
        target.draw(*u);
    }

    if(this->held_entity) {
        states.blendMode = sf::BlendMode(sf::BlendMode::SrcAlpha, sf::BlendMode::OneMinusSrcAlpha);

        sf::VertexArray * vao = &this->held_entity->info.vao;
        sf::Color color(255, 255, 255, 128);

        if(this->held_entity->info.selected)
            color = sf::Color(239, 4, 4, 128);

        (*vao)[0].color = color;
        (*vao)[1].color = color;
        (*vao)[2].color = color;
        (*vao)[3].color = color;

        target.draw(*this->held_entity, states);
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