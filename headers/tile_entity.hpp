//
// Created by Killian Le Clainche on 6/3/2018.
//

#ifndef RTMOBAS_GAME_TILE_ENTITY_HPP
#define RTMOBAS_GAME_TILE_ENTITY_HPP

#include "helper.hpp"

#define TILE_ENTITY 1
#define PRODUCER 1
#define RESEARCHER 2
#define COLLECTOR 3
#define RESOURCE 4

#define TILE_ENTITY_START_VALUE 10000
#define TILE_ENTITY_TYPE_DIFF 1000

#define PRODUCER_START_VALUE TILE_ENTITY_START_VALUE + TILE_ENTITY_TYPE_DIFF * PRODUCER
#define RESEARCHER_START_VALUE TILE_ENTITY_START_VALUE + TILE_ENTITY_TYPE_DIFF * RESEARCHER
#define COLLECTOR_START_VALUE TILE_ENTITY_START_VALUE + TILE_ENTITY_TYPE_DIFF * COLLECTOR
#define RESOURCE_START_VALUE TILE_ENTITY_START_VALUE + TILE_ENTITY_TYPE_DIFF * RESOURCE

#define PRODUCER_NEW_VALUE(i) PRODUCER_START_VALUE + i
#define RESEARCHER_NEW_VALUE(i) RESEARCHER_START_VALUE + i
#define COLLECTOR_NEW_VALUE(i) COLLECTOR_START_VALUE + i
#define RESOURCE_NEW_VALUE(i) RESOURCE_START_VALUE + i

#define WIDTH_OF_RESOURCE 3
#define HEIGHT_OF_RESOURCE 3
#define WIDTH_OF_WOOD 1
#define HEIGHT_OF_WOOD 1

#define SIZE_OF_CASTLE 3
#define SIZE_OF_FARM 2

/** Building Types */
#define PRODUCER_CASTLE PRODUCER_NEW_VALUE(0)

#define PRODUCER_LAST_VALUE PRODUCER_START_VALUE + 0

#define RESEARCHER_GROUND RESEARCHER_NEW_VALUE(0)
#define RESEARCHER_AIR RESEARCHER_NEW_VALUE(1)

#define RESEARCHER_LAST_VALUE RESEARCHER_START_VALUE + 1

/** Collector Types */
#define COLLECTOR_FOOD COLLECTOR_NEW_VALUE(0)
#define COLLECTOR_GOLD COLLECTOR_NEW_VALUE(1)
#define COLLECTOR_WOOD COLLECTOR_NEW_VALUE(2)
#define COLLECTOR_METAL COLLECTOR_NEW_VALUE(3)
#define COLLECTOR_CRYSTAL COLLECTOR_NEW_VALUE(4)
#define COLLECTOR_OIL COLLECTOR_NEW_VALUE(5)

#define COLLECTOR_LAST_VALUE COLLECTOR_START_VALUE + 5

/** Resource types */
#define RESOURCE_FOOD RESOURCE_NEW_VALUE(0)
#define RESOURCE_GOLD RESOURCE_NEW_VALUE(1)
#define RESOURCE_WOOD RESOURCE_NEW_VALUE(2)
#define RESOURCE_METAL RESOURCE_NEW_VALUE(3)
#define RESOURCE_CRYSTAL RESOURCE_NEW_VALUE(4)
#define RESOURCE_OIL RESOURCE_NEW_VALUE(5)

#define RESOURCE_LAST_VALUE RESOURCE_START_VALUE + 5


class World;

class TileEntity : public Drawable {
private:

    /** Allows window.draw(Entity) to be used in SFML */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:

    entity_info info;

    Tile *** owned_tiles;

    /** Position of entity on the map */
    int x_coord;
    int y_coord;

    /** Size of rendering box for entity */
    int width;
    int height;
};

class Resource : public TileEntity {
private:

    void create_vao();

public:

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

    /** Constructors */
    Structure() = default;

    /** Deconstructor */
    ~Structure();
};

class Farm : public Structure {
public:
    Farm(World *, int, int, int);
};

/** Resource that building is built on */
class Collector : public Structure {
public:
    Resource * resource;

    Collector(World *, int, int, int);
};

class Castle : public Structure {

public:
    Castle(World *, int, int, int);
};

namespace tile_entity {
    extern sf::Texture * resource_textures[];
    extern std::map<int, Structure *(*)(World *, int, int, int)> structures;

    template<typename T> Structure * create_structure(World * world, int type, int x, int y) {
        void * mem = rpmalloc(sizeof(T));
        return new(mem) T(world, type, x, y);
    }

    void init();
}

#endif //RTMOBAS_GAME_TILE_ENTITY_HPP
