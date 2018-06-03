//
// Created by jorda on 5/27/2018.
//

#ifndef RTMOBAS_GAME_TILE_H
#define RTMOBAS_GAME_TILE_H

#include "helper.hpp"

/** Size of tiles, which is the same for all tiles */
#define TILE_SIZE 32

#define NUMBER_OF_TERRAIN_TYPES 4
#define NUMBER_OF_TERRAIN_VARIATIONS 4

#define TERRAIN_PLAINS 0
#define TERRAIN_MOUNTAINS 1
#define TERRAIN_DESERT 2
#define TERRAIN_WATER 3

/** Used in constructor for assigning several properties for each tile type
 * Type is based on the color associated with each tile for the bitmap layouts*/
#define TERRAIN_PLAINS_COLOR 0x008000
#define TERRAIN_MOUNTAINS_COLOR 0x808040
#define TERRAIN_DESERT_COLOR 0xC0C000
#define TERRAIN_WATER_COLOR 0x004080

using namespace sf;
using namespace std;

class Tile : public Drawable {

private:

    /** Vertex Array Buffer that defines the render procedure (Vertices, Tex Coords, etc.)*/
    VertexArray vao;

    void create_vao();

    /** Allows window.draw(Tile) to be used in SFML */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:

    int tile_type;

    /** Index within the world->tiles 2-D array */
    int x_coord;
    /** Index within the world->tiles 2-D array */
    int y_coord;

    Structure * structure;
    Resource * resource;

    /** Constructors */
    Tile() = default;
    Tile(int x, int y, int type);
};

class World : public Drawable {

private:
    /** Allows window.draw(World) to be used in SFML */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:

    /** Array of all tiles contained in the world */
    Tile *** tiles = nullptr;

    /** Lists of all entities in the world. Resources rendered first, then structures, then units */
    vector<Resource *> resources;
    vector<Structure *> structures;
    vector<Unit *> units;

    /** Dimensions of the world, in units of tiles */
    int world_width_tiles;
    int world_height_tiles;

    static Structure * held_entity;

    /** Constructor */
    World(char *map_path, char *spawn_path);

    ~World();

    /** Spawns initial entities for the world */
    void spawn_entities(char *spawn_path);

    void update();
};


#endif //RTMOBAS_GAME_TILE_H
