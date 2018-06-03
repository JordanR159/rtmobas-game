//
// Created by Killian Le Clainche on 6/3/2018.
//

#ifndef RTMOBAS_GAME_TILE_ENTITY_HPP
#define RTMOBAS_GAME_TILE_ENTITY_HPP

#include "helper.hpp"

#define WIDTH_OF_RESOURCE 3
#define HEIGHT_OF_RESOURCE 3
#define WIDTH_OF_WOOD 1
#define HEIGHT_OF_WOOD 1

#define STRUCTURE_COLLECTOR_FARM 301

class TileEntity : public Drawable {
private:

    /** Allows window.draw(Entity) to be used in SFML */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

protected:

    /** Position of corners for entity, only needs to change just before rendering */
    VertexArray vao;

    Texture * texture;

public:

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

    static const int PRODUCER = 1;
    static const int RESEARCHER = 2;
    static const int COLLECTOR = 3;
    static const int RESOURCE = 4;
};

class Resource : public TileEntity {

private:

    void create_vao();

public:

    /** True if resource can run out, false otherwise */
    bool is_finite;

    /** Resource types */
    static const int RESOURCE_FOOD = 401;
    static const int RESOURCE_GOLD = 402;
    static const int RESOURCE_WOOD = 403;
    static const int RESOURCE_METAL = 404;
    static const int RESOURCE_CRYSTAL = 405;
    static const int RESOURCE_OIL = 406;

    /** Constructors */
    Resource() = default;
    Resource(int, int, int, Tile ***);

    /** Deconstructor */
    ~Resource();
};

class Structure : public TileEntity {
protected:

    void create_structure(int, int, int, int, int, Texture *, Tile ***);

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

    static const int COLLECTOR_FOOD = 301;
    static const int COLLECTOR_GOLD = 302;
    static const int COLLECTOR_WOOD = 303;
    static const int COLLECTOR_METAL = 304;
    static const int COLLECTOR_CRYSTAL = 305;
    static const int COLLECTOR_OIL = 306;

    /** Constructors */
    Structure() = default;
    Structure(int, int, int, int, int, Texture *, Tile ***);

    /** Deconstructor */
    ~Structure();
};

class Collector : public Structure {
    /** Resource that building is built on */
public:
    Resource * resource;

    Collector(int, int, int, Tile ***);
};

class Castle : public Structure {

public:
    Castle(int, int, Tile ***);
};

#endif //RTMOBAS_GAME_TILE_ENTITY_HPP
