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

/** Defines of Resource sizes, expressed as "x, y" */
#define SIZE_OF_BASE_RESOURCE 3, 3
#define SIZE_OF_WOOD_RESOURCE 1, 1

/** Defines of Structure sizes, expressed as "x, y" */
#define SIZE_OF_CASTLE 3, 3
#define SIZE_OF_FARM 2, 2
#define SIZE_OF_LOGGER 3, 3
#define SIZE_OF_MINE 3, 3

/** Building Types */
#define PRODUCER_CASTLE PRODUCER_NEW_VALUE(0)

#define PRODUCER_LAST_VALUE PRODUCER_START_VALUE + 0

#define RESEARCHER_GROUND RESEARCHER_NEW_VALUE(0)
#define RESEARCHER_AIR RESEARCHER_NEW_VALUE(1)

#define RESEARCHER_LAST_VALUE RESEARCHER_START_VALUE + 1

/** Collector Types */
#define COLLECTOR_FOOD COLLECTOR_NEW_VALUE(0)

/** Technically the real collectors */
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

class Tile;
class World;

class TileEntity : public sf::Drawable {
private:

    /** Allows window.draw(Entity) to be used in SFML */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

protected:

    void create_held_entity(World * world, int tile_entity_type, int width, int height, sf::Texture * texture);
    void create_tile_entity(World * world, int tile_entity_type, int xpos, int ypos, int width, int height, sf::Texture * texture);

public:

    entity_info info;

    Tile *** owned_tiles;

    sf::VertexArray rally_line;

    /** Position of entity on the map */
    int x_coord;
    int y_coord;

    /** Size of rendering box for entity */
    int width;
    int height;

    /** Rally point for the structure, if it is a producer */
    int rally_x;
    int rally_y;
    bool rally_set;

    ~TileEntity();

    /**
     * Only called when placing a new structure down and from create_tile_entity
     * Obtains the tiles that this tile entity would be over.
     */
    virtual void claim_tiles();

    /** The default action taken when a right click occurs while tile entity is selected */
    void rightClickAction(sf::Vector2f point);

    void setRallyPoint(int x, int y);
};

class Resource : public TileEntity {
private:

    void create_vao();

public:

    /** Constructors */
    Resource() = default;
    Resource(World * world, int resource_type, int xpos, int ypos);

    /** Deconstructor */
    ~Resource();
};

class Structure : public TileEntity {
public:
    /** Units/Research that can be done at the building */
    // int *production = nullptr;

    /** Constructors */
    Structure() = default;

    void claim_tiles() override;

    virtual bool can_place();
};

class Farm : public Structure {
public:
    Farm(World *, int);
    Farm(World *, int, int, int);

    bool can_place();
};

/** Resource that building is built on */
class Collector : public Structure {
public:
    Resource * resource;

    Collector(World *, int);
    Collector(World *, int, int, int);

    bool can_place();
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
