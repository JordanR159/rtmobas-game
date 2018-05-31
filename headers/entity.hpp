//
// Created by jorda on 5/29/2018.
//

#ifndef RTMOBAS_GAME_ENTITY_HPP
#define RTMOBAS_GAME_ENTITY_HPP

using namespace sf;

class Entity : public Drawable {

private:
    /** Allows window.draw(Entity) to be used in SFML */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

protected:
    /** Position of corners for entity, only needs to change just before rendering */
    VertexArray vertices;

    /** Texture that entity is rendered with */
    Texture texture;

public:

    /** Position of entity on the map */
    int xposition;
    int yposition;

    /** Size of rendering box for entity */
    int xsize;
    int ysize;

    /** Remaining lifepoints for an entity. For Resources, this is number of resources left */
    int curr_lifepoints;

    /** Maximum lifepoints that the entity can have */
    int max_lifepoints;

    /** True entity can collide with other ground entities, false otherwise.
     * Both entities must have this set to true for collision to occur */
    bool has_ground_collision;

    /** Subtype for the entity, as defined in the subclasses */
    int type;

    static const int PROD = 1;
    static const int RSCH = 2;
    static const int COLL = 3;
    static const int RSRC = 4;
    static const int UNIT = 5;

    void offsetEntity(int xoffset, int yoffset);
};

class Resource : public Entity {

private:

public:
    /** True if resource can run out, false otherwise */
    bool is_finite;

    /** Resource types */
    static const int RSRC_FOOD = 401;
    static const int RSRC_GOLD = 402;
    static const int RSRC_WOOD = 403;
    static const int RSRC_METAL = 404;
    static const int RSRC_CRYSTAL = 405;
    static const int RSRC_OIL = 406;

    /** Constructors */
    Resource() = default;
    Resource(int xposition, int yposition, int type);
};

class Structure : public Entity {

private:

public:
    /** Units/Research that can be done at the building */
    int *production = nullptr;

    /** Resource that building is built on, if it is a collector */
    Resource resource;

    /** Rally point for the structure, if it is a producer */
    int xrally;
    int yrally;

    /** Building Types */
    static const int PROD_CASTLE = 101;

    static const int RSCH_GROUND = 201;
    static const int RSCH_AIR = 202;

    static const int COLL_FOOD = 301;
    static const int COLL_GOLD = 302;
    static const int COLL_WOOD = 303;
    static const int COLL_METAL = 304;
    static const int COLL_CRYSTAL = 305;
    static const int COLL_OIL = 306;

    /** Constructors */
    Structure() = default;
    Structure(int xposition, int yposition, int type, Resource *resource = nullptr);
};

class Unit : public Entity {

private:

public:
    /** True if unit can fly, thus collision detection doesn't apply to unit, false otherwise*/
    bool is_flying;

    /** Unit Types */
    static const int UNIT_BUILDER = 501;
    static const int UNIT_SQUIRE = 502;

    /** Constructors */
    Unit() = default;
    Unit(int xposition, int yposition, int type);
};


#endif //RTMOBAS_GAME_ENTITY_HPP
