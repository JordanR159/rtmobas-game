//
// Created by jorda on 5/27/2018.
//

#ifndef RTMOBAS_GAME_TILE_H
#define RTMOBAS_GAME_TILE_H

using namespace sf;
using namespace std;

class Tile : public Drawable {

private:
    /** Allows window.draw(Tile) to be used in SFML */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    /** Position of corners for tile */
    VertexArray vertices;
public:
    /** Size of tiles, which is the same for all tiles */
    static const int TILE_SIZE = 32;

    int tile_type;

    /** Position of top left corner of tile */
    int xposition;
    int yposition;

    /** True if an entity can be drawn on top of this tile, false otherwise */
    bool is_passable;

    /** Modifier the the speed that entities move over this tile. Standard is 1.0 */
    double movement_multiplier;

    /** Amount of damage tile inflicts to units every tick */
    int damage_factor;

    /** Used in constructor for assigning several properties for each tile type
     * Type is based on the color associated with each tile for the bitmap layouts*/
    static const int PLAINS = 0x008000;
    static const int MOUNTAINS = 0x808040;
    static const int DESERT = 0xC0C000;
    static const int WATER = 0x004080;

    /** Constructors */
    Tile() = default;
    Tile(int xposition, int yposition, int type);
};

class World : public Drawable {

private:
    /** Allows window.draw(World) to be used in SFML */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    /** Array of all tiles contained in the world */
    Tile* tiles = nullptr;

    /** Lists of all entities in the world. Resources rendered first, then structures, then units */
    vector<Resource> resources;
    vector<Structure> structures;
    vector<Unit> units;

    /** Number of tiles in the world */
    int tiles_size;

    /** Dimensions of the world, in units of pixels */
    int world_width;
    int world_height;

    /** Dimensions of the world, in units of tiles */
    int world_width_tiles;
    int world_height_tiles;

    /** Constructor */
    World(char *map_path, char *spawn_path);

    /** Spawns initial entities for the world */
    void spawnEntities(char *spawn_path);
};


#endif //RTMOBAS_GAME_TILE_H
