//
// Created by Killian Le Clainche on 6/3/2018.
//

#ifndef RTMOBAS_GAME_TILE_ENTITY_HPP
#define RTMOBAS_GAME_TILE_ENTITY_HPP

#include "helper.hpp"

#define TILE_ENTITY_START_VALUE 10000
#define TILE_ENTITY_TYPE_DIFF 1000
#define PRODUCER_START_VALUE 11000
#define RESEARCHER_START_VALUE 12000
#define COLLECTOR_START_VALUE 13000
#define RESOURCE_START_VALUE 14000
#define PRODUCER_VALUE_CALC(value) 11000 + value
#define RESEARCHER_VALUE_CALC(value) 12000 + value
#define COLLECTOR_VALUE_CALC(value) 13000 + value
#define RESOURCE_VALUE_CALC(value) 14000 + value

#define WIDTH_OF_RESOURCE 3
#define HEIGHT_OF_RESOURCE 3
#define WIDTH_OF_WOOD 1
#define HEIGHT_OF_WOOD 1

#define STRUCTURE_COLLECTOR_FARM 301

class World;

class TileEntity : public Drawable {
private:

    /** Allows window.draw(Entity) to be used in SFML */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

protected:

    /** Position of corners for entity, only needs to change just before rendering */
    VertexArray vao;

    Texture * texture;

public:

    World * world;

    Tile *** owned_tiles;

    /** Position of entity on the map */
    int x_coord;
    int y_coord;

    /** Size of rendering box for entity */
    int width;
    int height;

    /** Remaining lifepoints for an entity. For Resources, this is number of resources left */
    int curr_lifepoints;

    /** Maximum lifepoints that the entity can have */
    int max_lifepoints;

    /** Subtype for the entity, as defined in the subclasses */
    int tile_entity_type;

    static const int TILE_ENTITY = 1;

    static const int PRODUCER = 1;
    static const int RESEARCHER = 2;
    static const int COLLECTOR = 3;
    static const int RESOURCE = 4;
};

class Resource : public TileEntity {
private:

    void create_vao();

public:

    static Texture * textures[6] = {
            resources::textures[resources::resource::FOOD_TEXTURE],
            resources::textures[resources::resource::GOLD_TEXTURE],
            resources::textures[resources::resource::TREE_TEXTURE],
            resources::textures[resources::resource::METAL_TEXTURE],
            resources::textures[resources::resource::CRYSTAL_TEXTURE],
            resources::textures[resources::resource::OIL_TEXTURE]
    };

    /** Resource types */
    static const int RESOURCE_FOOD = RESOURCE_VALUE_CALC(0);
    static const int RESOURCE_GOLD = RESOURCE_VALUE_CALC(1);
    static const int RESOURCE_WOOD = RESOURCE_VALUE_CALC(2);
    static const int RESOURCE_METAL = RESOURCE_VALUE_CALC(3);
    static const int RESOURCE_CRYSTAL = RESOURCE_VALUE_CALC(4);
    static const int RESOURCE_OIL = RESOURCE_VALUE_CALC(5);

    /** Constructors */
    Resource() = default;
    Resource(World *, int, int, int);

    /** Deconstructor */
    ~Resource();

};

class Structure : public TileEntity {
protected:

    void create_structure(World *, int, int, int, int, int, Texture *);

public:
    /** Units/Research that can be done at the building */
    // int *production = nullptr;

    /** Rally point for the structure, if it is a producer */
    // int xrally;
    // int yrally;

    /** Building Types */
    static const int PRODUCER_CASTLE = 101;

    static const int RESEARCHER_GROUND = 201;
    static const int RESEARCHER_AIR = 202;

    /** Constructors */
    Structure() = default;

    /** Deconstructor */
    ~Structure();
};

class Collector : public Structure {
    /** Resource that building is built on */
public:
    Resource * resource;

    static const int COLLECTOR_FOOD = COLLECTOR_VALUE_CALC(0);
    static const int COLLECTOR_GOLD = COLLECTOR_VALUE_CALC(1);
    static const int COLLECTOR_WOOD = COLLECTOR_VALUE_CALC(2);
    static const int COLLECTOR_METAL = COLLECTOR_VALUE_CALC(3);
    static const int COLLECTOR_CRYSTAL = COLLECTOR_VALUE_CALC(4);
    static const int COLLECTOR_OIL = COLLECTOR_VALUE_CALC(5);

    Collector(World *, int, int, int);
};

class Castle : public Structure {

public:
    Castle(World *, int, int, int);
};

#endif //RTMOBAS_GAME_TILE_ENTITY_HPP
