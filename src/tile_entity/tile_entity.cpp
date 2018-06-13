//
// Created by Killian Le Clainche on 6/3/2018.
//

#include "helper.hpp"

TileEntity::~TileEntity() {
    rpfree(&this->info.vao);
    rpfree(this->owned_tiles);
}

void TileEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if(this->info.selected) {
        states.blendMode = sf::BlendMode(sf::BlendMode::SrcColor, sf::BlendMode::SrcAlpha, sf::BlendMode::ReverseSubtract);
    }
    states.texture = info.texture;
    target.draw(info.vao, states);
    if(this->info.selected && this->rally_set) {
        target.draw(rally_line);
    }
}

void TileEntity::create_held_entity(World * world, int tile_entity_type, int width, int height, sf::Texture * texture) {
    this->info.world = world;
    this->info.entity_type = tile_entity_type;
    this->info.texture = texture;

    this->info.selected = false;

    this->x_coord = 0;
    this->y_coord = 0;
    this->width = width;
    this->height = height;

    this->info.vao = sf::VertexArray(sf::Quads, 4);

    gen_vao(this->info.vao, this->x_coord, this->y_coord, this->width * TILE_SIZE, this->height * TILE_SIZE, this->info.texture);
}

void TileEntity::create_tile_entity(World * world, int tile_entity_type, int xpos, int ypos, int width, int height, sf::Texture * texture) {
    this->info.world = world;
    this->info.entity_type = tile_entity_type;
    this->info.texture = texture;

    this->info.selected = false;

    this->x_coord = xpos;
    this->y_coord = ypos;

    this->width = width;
    this->height = height;

    this->claim_tiles();

    this->info.vao = sf::VertexArray(sf::Quads, 4);

    this->rally_line = sf::VertexArray(sf::Lines, 2);
    this->rally_line[0] = sf::Vector2f(TILE_SIZE * (this->x_coord + this->width/2.0f), TILE_SIZE * (this->y_coord + this->height/2.0f));
    this->rally_line[0].color = sf::Color::White;
    this->rally_line[1] = this->rally_line[0];
    this->rally_line[1].color = sf::Color::White;

    gen_vao(this->info.vao, this->x_coord * TILE_SIZE, this->y_coord * TILE_SIZE, this->width * TILE_SIZE, this->height * TILE_SIZE, this->info.texture);
}

void TileEntity::claim_tiles() {
    this->owned_tiles = (Tile ***) rpmalloc(this->width * sizeof(Tile **));

    for(int i = 0; i < this->width; i ++) {
        this->owned_tiles[i] = this->info.world->tiles[this->x_coord + i] + this->y_coord;
    }
}

void TileEntity::setRallyPoint(int x, int y) {
    this->rally_x = x;
    this->rally_y = y;
    this->rally_set = true;
    this->rally_line[1] = sf::Vector2f(this->rally_x, this->rally_y);
}

void TileEntity::rightClickAction(sf::Vector2f point) {
    if(this->info.entity_type >= PRODUCER_START_VALUE && this->info.entity_type <= PRODUCER_LAST_VALUE) {
        setRallyPoint(static_cast<int>(point.x), static_cast<int>(point.y));
    }
}

namespace tile_entity {
    sf::Texture * resource_textures[6];

    std::map<int, Structure *(*)(World *, int, int, int)> structures;

    void init() {

        resource_textures[0] = resources::textures[resources::resource::FOOD_TEXTURE];
        resource_textures[1] = resources::textures[resources::resource::GOLD_TEXTURE];
        resource_textures[2] = resources::textures[resources::resource::TREE_TEXTURE];
        resource_textures[3] = resources::textures[resources::resource::METAL_TEXTURE];
        resource_textures[4] = resources::textures[resources::resource::CRYSTAL_TEXTURE];
        resource_textures[5] = resources::textures[resources::resource::OIL_TEXTURE];

        structures[PRODUCER_CASTLE] = &create_structure<Castle>;

        structures[COLLECTOR_FOOD] = &create_structure<Farm>;
        for(int i = COLLECTOR_START_VALUE + 1; i <= COLLECTOR_LAST_VALUE; i++) {
            structures[i] = &create_structure<Collector>;
        }
    }
}
