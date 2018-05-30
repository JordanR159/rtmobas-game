//
// Created by jorda on 5/27/2018.
//

#ifndef RTMOBAS_GAME_TILE_H
#define RTMOBAS_GAME_TILE_H

#include <SFML/Graphics.hpp>
#include <entity.hpp>

class Tile : public Drawable {

private:
    /** Allows window.draw(Tile) to be used in SFML */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    /** Position of corners for tile */
    sf::VertexArray vertices;

    /** Path to the texture for the entity */
    sf::Texture texture;
public:
    /** Size of tiles, which is the same for all tiles */
    static const int TILE_SIZE = 25;

    /** Position of top left corner of tile */
    int xposition;
    int yposition;

    /** True if an entity can be drawn on top of this tile, false otherwise */
    bool is_passable;

    /** Modifier the the speed that entities move over this tile. Standard is 1.0 */
    double movement_multiplier;

    /** Amount of damage tile inflicts to units every tick */
    int damage_factor;

    /** Used in constructor for assigning several properties for each tile type */
    enum Types{
        PLAINS, DESERT, MOUNTAIN
    };

    /** Constructors */
    Tile();
    Tile(int xposition, int yposition, int type);

    void offsetTile(int xoffset, int yoffset);
};

class World : public Drawable {

private:
    /** Allows window.draw(World) to be used in SFML */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    /** Array of all tiles contained in the world */
    Tile* tiles = nullptr;

    /** Number of tiles in the world */
    int tiles_size;

    /** Keeps track of whether or not a tile was modified */
    bool tiles_modified;

    /** Dimensions of the world, in units of tiles */
    int xtiles;
    int ytiles;

    /** Offset of where to start rendering world */
    int xoffset;
    int yoffset;

    /** Constructors */
    World();
    World(int xtiles, int ytiles);
    //World(int width, int height, Entity first_entities[]);
};


#endif //RTMOBAS_GAME_TILE_H
